# Change Log for hipSOLVER

Full documentation for hipSOLVER is available at [hipsolver.readthedocs.io](https://hipsolver.readthedocs.io/en/latest/).


## [(Unreleased) hipSOLVER for ROCm 4.5.0]
### Added
- Added functions
  - gesv
    - hipsolverSSgesv_bufferSize, hipsolverDDgesv_bufferSize, hipsolverCCgesv_bufferSize, hipsolverZZgesv_bufferSize
    - hipsolverSSgesv, hipsolverDDgesv, hipsolverCCgesv, hipsolverZZgesv

### Optimizations

### Changed

### Removed

### Fixed

### Known Issues


## [hipSOLVER 1.0.0 for ROCm 4.4.0]
### Added
- Added functions
  - orgbr/ungbr
    - hipsolverSorgbr_bufferSize, hipsolverDorgbr_bufferSize, hipsolverCungbr_bufferSize, hipsolverZungbr_bufferSize
    - hipsolverSorgbr, hipsolverDorgbr, hipsolverCungbr, hipsolverZungbr
  - orgqr/ungqr
    - hipsolverSorgqr_bufferSize, hipsolverDorgqr_bufferSize, hipsolverCungqr_bufferSize, hipsolverZungqr_bufferSize
    - hipsolverSorgqr, hipsolverDorgqr, hipsolverCungqr, hipsolverZungqr
  - orgtr/ungtr
    - hipsolverSorgtr_bufferSize, hipsolverDorgtr_bufferSize, hipsolverCungtr_bufferSize, hipsolverZungtr_bufferSize
    - hipsolverSorgtr, hipsolverDorgtr, hipsolverCungtr, hipsolverZungtr
  - ormqr/unmqr
    - hipsolverSormqr_bufferSize, hipsolverDormqr_bufferSize, hipsolverCunmqr_bufferSize, hipsolverZunmqr_bufferSize
    - hipsolverSormqr, hipsolverDormqr, hipsolverCunmqr, hipsolverZunmqr
  - ormtr/unmtr
    - hipsolverSormtr_bufferSize, hipsolverDormtr_bufferSize, hipsolverCunmtr_bufferSize, hipsolverZunmtr_bufferSize
    - hipsolverSormtr, hipsolverDormtr, hipsolverCunmtr, hipsolverZunmtr
  - gebrd
    - hipsolverSgebrd_bufferSize, hipsolverDgebrd_bufferSize, hipsolverCgebrd_bufferSize, hipsolverZgebrd_bufferSize
    - hipsolverSgebrd, hipsolverDgebrd, hipsolverCgebrd, hipsolverZgebrd
  - geqrf
    - hipsolverSgeqrf_bufferSize, hipsolverDgeqrf_bufferSize, hipsolverCgeqrf_bufferSize, hipsolverZgeqrf_bufferSize
    - hipsolverSgeqrf, hipsolverDgeqrf, hipsolverCgeqrf, hipsolverZgeqrf
  - gesvd
    - hipsolverSgesvd_bufferSize, hipsolverDgesvd_bufferSize, hipsolverCgesvd_bufferSize, hipsolverZgesvd_bufferSize
    - hipsolverSgesvd, hipsolverDgesvd, hipsolverCgesvd, hipsolverZgesvd
  - getrs
    - hipsolverSgetrs_bufferSize, hipsolverDgetrs_bufferSize, hipsolverCgetrs_bufferSize, hipsolverZgetrs_bufferSize
    - hipsolverSgetrs, hipsolverDgetrs, hipsolverCgetrs, hipsolverZgetrs
  - potrf
    - hipsolverSpotrf_bufferSize, hipsolverDpotrf_bufferSize, hipsolverCpotrf_bufferSize, hipsolverZpotrf_bufferSize
    - hipsolverSpotrf, hipsolverDpotrf, hipsolverCpotrf, hipsolverZpotrf
  - potrfBatched
    - hipsolverSpotrfBatched_bufferSize, hipsolverDpotrfBatched_bufferSize, hipsolverCpotrfBatched_bufferSize, hipsolverZpotrfBatched_bufferSize
    - hipsolverSpotrfBatched, hipsolverDpotrfBatched, hipsolverCpotrfBatched, hipsolverZpotrfBatched
  - syevd/heevd
    - hipsolverSsyevd_bufferSize, hipsolverDsyevd_bufferSize, hipsolverCheevd_bufferSize, hipsolverZheevd_bufferSize
    - hipsolverSsyevd, hipsolverDsyevd, hipsolverCheevd, hipsolverZheevd
  - sygvd/hegvd
    - hipsolverSsygvd_bufferSize, hipsolverDsygvd_bufferSize, hipsolverChegvd_bufferSize, hipsolverZhegvd_bufferSize
    - hipsolverSsygvd, hipsolverDsygvd, hipsolverChegvd, hipsolverZhegvd
  - sytrd/hetrd
    - hipsolverSsytrd_bufferSize, hipsolverDsytrd_bufferSize, hipsolverChetrd_bufferSize, hipsolverZhetrd_bufferSize
    - hipsolverSsytrd, hipsolverDsytrd, hipsolverChetrd, hipsolverZhetrd
  - getrf
    - hipsolverSgetrf_bufferSize, hipsolverDgetrf_bufferSize, hipsolverCgetrf_bufferSize, hipsolverZgetrf_bufferSize
    - hipsolverSgetrf, hipsolverDgetrf, hipsolverCgetrf, hipsolverZgetrf
  - auxiliary
    - hipsolverCreate, hipsolverDestroy
    - hipsolverSetStream, hipsolverGetStream

### Changed
- hipSOLVER functions will now return HIPSOLVER_STATUS_INVALID_ENUM or HIPSOLVER_STATUS_UNKNOWN status codes rather than throw exceptions.
- hipsolverXgetrf functions now take lwork as an argument.

### Removed
- Removed unused HIPSOLVER_FILL_MODE_FULL enum value.
- Removed hipsolverComplex and hipsolverDoubleComplex from the library. Use hipFloatComplex and hipDoubleComplex instead.

