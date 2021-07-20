# hipSOLVER
hipSOLVER is a LAPACK marshalling library, with multiple supported backends.  It sits between the application and a 'worker' LAPACK library, marshalling inputs into the backend library and marshalling results back to the application.  hipSOLVER exports an interface that does not require the client to change, regardless of the chosen backend.  Currently, hipSOLVER supports [rocSOLVER](https://github.com/ROCmSoftwarePlatform/rocSOLVER) and [cuSOLVER](https://developer.nvidia.com/cusolver) as backends.

## Installing hipSOLVER

### Install Pre-built Packages
Download pre-built packages from [ROCm's package servers](https://rocmdocs.amd.com/en/latest/Installation_Guide/Installation-Guide.html). Release notes are available on the releases tab of the [library's github page](https://github.com/ROCmSoftwarePlatform/hipSOLVER).
* `sudo apt update && sudo apt install hipsolver`

### Build & Install Library Using Script (Ubuntu only)
The root of this repository has a helper bash script `install.sh` to build and install hipSOLVER on Ubuntu with a single command.  It does not take a lot of options and hard-codes configuration that can be specified through invoking cmake directly, but it's a great way to get started quickly and can serve as an example of how to build/install.  A few commands in the script need sudo access, so it may prompt you for a password.
* `./install.sh -id` -- build library, build dependencies, and install (-d flag only needs to be passed once on a system).
* `./install.sh -ic` -- build library, build clients (tests, benchmarks, and samples), and install.

To see more options, use the help option of the install script.
* `./install.sh -h`

### Build & Install Library Manually
For a standard library installation, follow these steps:

```sh
mkdir -p <HIPSOLVER_BUILD_DIR_PATH>/release
cd <HIPSOLVER_BUILD_DIR_PATH>/release
CXX=/opt/rocm/bin/hipcc cmake <HIPSOLVER_SOURCE_DIR_PATH>
make -j$(nproc)
sudo make install
```
sudo is required if installing into a system directory such as /opt/rocm, which is the default option.
* Use `-DCMAKE_INSTALL_PREFIX=<other_path>` to specify a different install directory.
* Use `-DCMAKE_BUILD_TYPE=<other_configuration>` to specify a build configuration, such as 'Debug'. The default build configuration is 'Release'.

### Build Library + Tests + Benchmarks + Samples Manually
The repository contains source code for client programs that serve as tests, benchmarks, and samples. Client source code can be found in the clients subdirectory.

#### Dependencies (only necessary for hipSOLVER clients)
The hipSOLVER samples have no external dependencies, but our unit test and benchmarking applications do. These clients introduce the following dependencies:

1. [boost](https://www.boost.org/)
2. [lapack](https://github.com/Reference-LAPACK/lapack-release) (lapack itself brings a dependency on a fortran compiler)
3. [googletest](https://github.com/google/googletest)

Linux distros typically have an easy installation mechanism for boost through the native package manager.

* Ubuntu: `sudo apt install libboost-program-options-dev`
* Fedora: `sudo dnf install boost-program-options`

Unfortunately, googletest and lapack are not as easy to install. Many distros do not provide a googletest package with pre-compiled libraries, and the lapack packages do not have the necessary cmake config files for cmake to configure linking the cblas library. hipSOLVER provide a cmake script that builds the above dependencies from source. This is an optional step; users can provide their own builds of these dependencies and help cmake find them by setting the `CMAKE_PREFIX_PATH` definition. The following is a sequence of steps to build dependencies and install them to the cmake default, /usr/local.

```sh
mkdir -p <HIPSOLVER_BUILD_DIR_PATH>/release/deps
cd <HIPSOLVER_BUILD_DIR_PATH>/release/deps
cmake -DBUILD_BOOST=OFF <HIPSOLVER_SOURCE_PATH>/deps   #assuming boost is installed through package manager as above
make -j$(nproc) install
```
#### Library and clients
Once dependencies are available on the system, it is possible to configure the clients to build. This requires a few extra cmake flags to the library's cmake configure script. If the dependencies are not installed into system defaults (like /usr/local), you should pass the `CMAKE_PREFIX_PATH` to cmake to help find them.
* `-DCMAKE_PREFIX_PATH="<semicolon separated paths>"`

```sh
CXX=/opt/rocm/bin/hcc cmake -DBUILD_CLIENTS_TESTS=ON -DBUILD_CLIENTS_BENCHMARKS=ON [HIPSOLVER_SOURCE]
make -j$(nproc)
sudo make install   # sudo required if installing into system directory such as /opt/rocm
```

## Using the hipSOLVER Interface
The hipSOLVER interface is compatible with rocSOLVER and cuBLAS-v11 APIs. Porting a CUDA application that originally calls the cuSOLVER API to an application calling the hipSOLVER API should be relatively straightforward. For example, the hipSOLVER SGETRF interface is

```c
hipsolverStatus_t
hipsolverSgetrf_bufferSize(hipsolverHandle_t handle,
                           int m,
                           int n,
                           float* A,
                           int lda,
                           int* lwork);
```

```c
hipsolverStatus_t
hipsolverSgetrf(hipsolverHandle_t handle,
                int               m,
                int               n,
                float*            A,
                int               lda,
                float*            work,
                int*              devIpiv,
                int*              devInfo);
```

## Notes on API Differences
While the API of hipSOLVER is, overall, modeled after that of cuSOLVER, there are some notable differences. In particular:

* hipsolverXXgesv_bufferSize does not require `dwork` as an argument
* hipsolverXgesvd_bufferSize requires `jobu` and `jobv` as arguments
* hipsolverXgetrf requires `lwork` as an argument
* hipsolverXgetrs requires `work` and `lwork` as arguments, and
* hipsolverXpotrfBatched requires `work` and `lwork` as arguments.

In order to support these changes, hipSOLVER adds the following functions as well:

* hipsolverXgetrs_bufferSize
* hipsolverXpotrfBatched_bufferSize

Furthermore, due to differences in implementation and API design between rocSOLVER and cuSOLVER, not all arguments are handled identically between the two backends. When using the rocSOLVER backend, keep in mind the following differences:

* While many cuSOLVER functions (and, consequently, hipSOLVER functions) take a workspace pointer and size as arguments, rocSOLVER maintains its own internal device workspace by default. In order to take advantage of this feature, users may pass a null pointer for the `work` argument of any function when using the rocSOLVER backend, and the workspace will be automatically managed behind-the-scenes. It is recommended to use a consistent strategy for workspace management, as performance issues may arise if the internal workspace is made to flip-flop between user-provided and automatically allocated workspaces.

* Additionally, unlike cuSOLVER, rocSOLVER does not provide information on invalid arguments in its `info` arguments, though it will provide info on singularities and algorithm convergence. As a result, the `info` argument of many functions will not be referenced or altered by the rocSOLVER backend, excepting those that provide info on singularities or convergence.

* The `niters` argument of `hipsolverXXgesv` is not referenced by the rocSOLVER backend.

## Supported Functionality
For a complete description of all the supported functions, see the corresponding backends' documentation
at [rocSOLVER API](https://rocsolver.readthedocs.io/en/latest/userguide_api.html) and/or [cuSOLVER API](https://docs.nvidia.com/cuda/cusolver/index.html#cuds-api).

### Auxiliary functions

| Function |
| -------- |
| hipsolverCreate |
| hipsolverDestroy |
| hipsolverSetStream |
| hipsolverGetStream |

### LAPACK functions

| Function | single | double | single complex | double complex |
| -------- | ------ | ------ | -------------- | -------------- |
| hipsolverXorgbr_bufferSize | x | x |   |   |
| hipsolverXorgbr | x | x |   |   |
| hipsolverXungbr_bufferSize |   |   | x | x |
| hipsolverXungbr |   |   | x | x |
| hipsolverXorgqr_bufferSize | x | x |   |   |
| hipsolverXorgqr | x | x |   |   |
| hipsolverXungqr_bufferSize |   |   | x | x |
| hipsolverXungqr |   |   | x | x |
| hipsolverXorgtr_bufferSize | x | x |   |   |
| hipsolverXorgtr | x | x |   |   |
| hipsolverXungtr_bufferSize |   |   | x | x |
| hipsolverXungtr |   |   | x | x |
| hipsolverXormqr_bufferSize | x | x |   |   |
| hipsolverXormqr | x | x |   |   |
| hipsolverXunmqr_bufferSize |   |   | x | x |
| hipsolverXunmqr |   |   | x | x |
| hipsolverXormtr_bufferSize | x | x |   |   |
| hipsolverXormtr | x | x |   |   |
| hipsolverXunmtr_bufferSize |   |   | x | x |
| hipsolverXunmtr |   |   | x | x |
| hipsolverXgebrd_bufferSize | x | x | x | x |
| hipsolverXgebrd | x | x | x | x |
| hipsolverXgeqrf_bufferSize | x | x | x | x |
| hipsolverXgeqrf | x | x | x | x |
| hipsolverXXgesv_bufferSize | x | x | x | x |
| hipsolverXXgesv | x | x | x | x |
| hipsolverXgesvd_bufferSize | x | x | x | x |
| hipsolverXgesvd | x | x | x | x |
| hipsolverXgetrf_bufferSize | x | x | x | x |
| hipsolverXgetrf | x | x | x | x |
| hipsolverXgetrs_bufferSize | x | x | x | x |
| hipsolverXgetrs | x | x | x | x |
| hipsolverXpotrf_bufferSize | x | x | x | x |
| hipsolverXpotrf | x | x | x | x |
| hipsolverXpotrfBatched_bufferSize | x | x | x | x |
| hipsolverXpotrfBatched | x | x | x | x |
| hipsolverXsyevd_bufferSize | x | x |   |   |
| hipsolverXsyevd | x | x |   |   |
| hipsolverXheevd_bufferSize |   |   | x | x |
| hipsolverXheevd |   |   | x | x |
| hipsolverXsygvd_bufferSize | x | x |   |   |
| hipsolverXsygvd | x | x |   |   |
| hipsolverXhegvd_bufferSize |   |   | x | x |
| hipsolverXhegvd |   |   | x | x |
| hipsolverXsytrd_bufferSize | x | x |   |   |
| hipsolverXsytrd | x | x |   |   |
| hipsolverXhetrd_bufferSize |   |   | x | x |
| hipsolverXhetrd |   |   | x | x |
