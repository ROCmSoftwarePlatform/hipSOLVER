# ########################################################################
# Copyright 2016-2021 Advanced Micro Devices, Inc.
# ########################################################################

# Linking lapack library requires fortran flags
enable_language( Fortran )
find_package( cblas CONFIG REQUIRED )
if( NOT cblas_FOUND )
  message( FATAL_ERROR "cblas is a required dependency and is not found;  try adding cblas path to CMAKE_PREFIX_PATH" )
endif( )

if( NOT TARGET hipsolver )
  find_package( hipsolver CONFIG PATHS /opt/rocm/hipsolver )

  if( NOT hipsolver_FOUND )
    message( FATAL_ERROR "hipSOLVER is a required dependency and is not found; try adding hipsolver path to CMAKE_PREFIX_PATH")
  endif( )
endif( )

find_package( GTest REQUIRED )
include_directories(${GTEST_INCLUDE_DIRS})

set(hipsolver_test_source
  hipsolver_gtest_main.cpp
  getrs_gtest.cpp
  getrf_gtest.cpp
  gebrd_gtest.cpp
  geqrf_gtest.cpp
  gesvd_gtest.cpp
  potrf_gtest.cpp
  potrs_gtest.cpp
  syevd_heevd_gtest.cpp
  sygvd_hegvd_gtest.cpp
  sytrd_hetrd_gtest.cpp
  orgbr_ungbr_gtest.cpp
  orgqr_ungqr_gtest.cpp
  orgtr_ungtr_gtest.cpp
  ormqr_unmqr_gtest.cpp
  ormtr_unmtr_gtest.cpp
)

set( hipsolver_test_common
  ../common/lapack_host_reference.cpp
  ../common/hipsolver_datatype2string.cpp
  ../common/utility.cpp
)

add_executable( hipsolver-test ${hipsolver_f90_source} ${hipsolver_test_source} ${hipsolver_test_common} )

target_include_directories( hipsolver-test
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
)

set( THREADS_PREFER_PTHREAD_FLAG ON )
find_package( Threads REQUIRED )
target_link_libraries( hipsolver-test PRIVATE Threads::Threads )

add_armor_flags( hipsolver-test "${ARMOR_LEVEL}" )

target_compile_definitions( hipsolver-test PRIVATE GOOGLE_TEST )

# External header includes included as SYSTEM files
target_include_directories( hipsolver-test
  SYSTEM PRIVATE
    $<BUILD_INTERFACE:${CBLAS_INCLUDE_DIRS}>
    $<BUILD_INTERFACE:${GTEST_INCLUDE_DIRS}>
    $<BUILD_INTERFACE:${HIP_INCLUDE_DIRS}>
    ${ROCM_PATH}/hsa/include
)

target_link_libraries( hipsolver-test PRIVATE roc::hipsolver cblas lapack ${GTEST_LIBRARIES} ${Boost_LIBRARIES} hipsolver_fortran_client )

# need mf16c flag for float->half convertion
target_compile_options( hipsolver-test PRIVATE -mf16c )

if( NOT USE_CUDA )
  target_link_libraries( hipsolver-test PRIVATE hip::host )

  if( CUSTOM_TARGET )
    target_link_libraries( hipsolver-test PRIVATE hip::${CUSTOM_TARGET} )
  endif( )

  if( CMAKE_CXX_COMPILER MATCHES ".*/hcc$|.*/hipcc$" )
    # hip-clang needs specific flag to turn on pthread and m
    target_link_libraries( hipsolver-test PRIVATE -lpthread -lm )
  endif()
else( )
  target_compile_definitions( hipsolver-test PRIVATE __HIP_PLATFORM_NVCC__ )

  target_include_directories( hipsolver-test
    PRIVATE
      $<BUILD_INTERFACE:${CUDA_INCLUDE_DIRS}>
  )

  target_link_libraries( hipsolver-test PRIVATE ${CUDA_LIBRARIES} Threads::Threads )
endif( )

set_target_properties( hipsolver-test PROPERTIES DEBUG_POSTFIX "-d" CXX_EXTENSIONS NO )
set_target_properties( hipsolver-test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/staging" )
