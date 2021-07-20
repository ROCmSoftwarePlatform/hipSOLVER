/* ************************************************************************
 * Copyright 2020-2021 Advanced Micro Devices, Inc.
 * ************************************************************************ */

#include "hipsolver.h"
#include "exceptions.hpp"
#include <cuda_runtime.h>
#include <cusolverDn.h>
#include <hip/hip_runtime.h>

extern "C" {

/******************** HELPERS ********************/
cublasOperation_t hip2cuda_operation(hipsolverOperation_t op)
{
    switch(op)
    {
    case HIPSOLVER_OP_N:
        return CUBLAS_OP_N;
    case HIPSOLVER_OP_T:
        return CUBLAS_OP_T;
    case HIPSOLVER_OP_C:
        return CUBLAS_OP_C;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

hipsolverOperation_t cuda2hip_operation(cublasOperation_t op)
{
    switch(op)
    {
    case CUBLAS_OP_N:
        return HIPSOLVER_OP_N;
    case CUBLAS_OP_T:
        return HIPSOLVER_OP_T;
    case CUBLAS_OP_C:
        return HIPSOLVER_OP_C;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

cublasFillMode_t hip2cuda_fill(hipsolverFillMode_t fill)
{
    switch(fill)
    {
    case HIPSOLVER_FILL_MODE_UPPER:
        return CUBLAS_FILL_MODE_UPPER;
    case HIPSOLVER_FILL_MODE_LOWER:
        return CUBLAS_FILL_MODE_LOWER;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

hipsolverFillMode_t cuda2hip_fill(cublasFillMode_t fill)
{
    switch(fill)
    {
    case CUBLAS_FILL_MODE_UPPER:
        return HIPSOLVER_FILL_MODE_UPPER;
    case CUBLAS_FILL_MODE_LOWER:
        return HIPSOLVER_FILL_MODE_LOWER;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

cublasSideMode_t hip2cuda_side(hipsolverSideMode_t side)
{
    switch(side)
    {
    case HIPSOLVER_SIDE_LEFT:
        return CUBLAS_SIDE_LEFT;
    case HIPSOLVER_SIDE_RIGHT:
        return CUBLAS_SIDE_RIGHT;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

hipsolverSideMode_t cuda2hip_side(cublasSideMode_t side)
{
    switch(side)
    {
    case CUBLAS_SIDE_LEFT:
        return HIPSOLVER_SIDE_LEFT;
    case CUBLAS_SIDE_RIGHT:
        return HIPSOLVER_SIDE_RIGHT;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

cusolverEigMode_t hip2cuda_evect(hipsolverEigMode_t eig)
{
    switch(eig)
    {
    case HIPSOLVER_EIG_MODE_NOVECTOR:
        return CUSOLVER_EIG_MODE_NOVECTOR;
    case HIPSOLVER_EIG_MODE_VECTOR:
        return CUSOLVER_EIG_MODE_VECTOR;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

hipsolverEigMode_t cuda2hip_evect(cusolverEigMode_t eig)
{
    switch(eig)
    {
    case CUSOLVER_EIG_MODE_NOVECTOR:
        return HIPSOLVER_EIG_MODE_NOVECTOR;
    case CUSOLVER_EIG_MODE_VECTOR:
        return HIPSOLVER_EIG_MODE_VECTOR;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

cusolverEigType_t hip2cuda_eform(hipsolverEigType_t eig)
{
    switch(eig)
    {
    case HIPSOLVER_EIG_TYPE_1:
        return CUSOLVER_EIG_TYPE_1;
    case HIPSOLVER_EIG_TYPE_2:
        return CUSOLVER_EIG_TYPE_2;
    case HIPSOLVER_EIG_TYPE_3:
        return CUSOLVER_EIG_TYPE_3;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

hipsolverEigType_t cuda2hip_eform(cusolverEigType_t eig)
{
    switch(eig)
    {
    case CUSOLVER_EIG_TYPE_1:
        return HIPSOLVER_EIG_TYPE_1;
    case CUSOLVER_EIG_TYPE_2:
        return HIPSOLVER_EIG_TYPE_2;
    case CUSOLVER_EIG_TYPE_3:
        return HIPSOLVER_EIG_TYPE_3;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

hipsolverStatus_t cuda2hip_status(cusolverStatus_t cuStatus)
{
    switch(cuStatus)
    {
    case CUSOLVER_STATUS_SUCCESS:
        return HIPSOLVER_STATUS_SUCCESS;
    case CUSOLVER_STATUS_NOT_INITIALIZED:
        return HIPSOLVER_STATUS_NOT_INITIALIZED;
    case CUSOLVER_STATUS_ALLOC_FAILED:
        return HIPSOLVER_STATUS_ALLOC_FAILED;
    case CUSOLVER_STATUS_INVALID_VALUE:
    case CUSOLVER_STATUS_IRS_PARAMS_INVALID:
        return HIPSOLVER_STATUS_INVALID_VALUE;
    case CUSOLVER_STATUS_MAPPING_ERROR:
        return HIPSOLVER_STATUS_MAPPING_ERROR;
    case CUSOLVER_STATUS_EXECUTION_FAILED:
        return HIPSOLVER_STATUS_EXECUTION_FAILED;
    case CUSOLVER_STATUS_INTERNAL_ERROR:
    case CUSOLVER_STATUS_IRS_INTERNAL_ERROR:
        return HIPSOLVER_STATUS_INTERNAL_ERROR;
    case CUSOLVER_STATUS_NOT_SUPPORTED:
    case CUSOLVER_STATUS_IRS_NOT_SUPPORTED:
        return HIPSOLVER_STATUS_NOT_SUPPORTED;
    case CUSOLVER_STATUS_ARCH_MISMATCH:
        return HIPSOLVER_STATUS_ARCH_MISMATCH;
    default:
        return HIPSOLVER_STATUS_UNKNOWN;
    }
}

/******************** AUXLIARY ********************/
hipsolverStatus_t hipsolverCreate(hipsolverHandle_t* handle)
try
{
    return cuda2hip_status(cusolverDnCreate((cusolverDnHandle_t*)handle));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDestroy(hipsolverHandle_t handle)
try
{
    return cuda2hip_status(cusolverDnDestroy((cusolverDnHandle_t)handle));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSetStream(hipsolverHandle_t handle, hipStream_t streamId)
try
{
    return cuda2hip_status(cusolverDnSetStream((cusolverDnHandle_t)handle, streamId));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverGetStream(hipsolverHandle_t handle, hipStream_t* streamId)
try
{
    return cuda2hip_status(cusolverDnGetStream((cusolverDnHandle_t)handle, streamId));
}
catch(...)
{
    return exception2hip_status();
}

/******************** ORGBR/UNGBR ********************/
hipsolverStatus_t hipsolverSorgbr_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverSideMode_t side,
                                             int                 m,
                                             int                 n,
                                             int                 k,
                                             float*              A,
                                             int                 lda,
                                             float*              tau,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnSorgbr_bufferSize(
        (cusolverDnHandle_t)handle, hip2cuda_side(side), m, n, k, A, lda, tau, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDorgbr_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverSideMode_t side,
                                             int                 m,
                                             int                 n,
                                             int                 k,
                                             double*             A,
                                             int                 lda,
                                             double*             tau,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnDorgbr_bufferSize(
        (cusolverDnHandle_t)handle, hip2cuda_side(side), m, n, k, A, lda, tau, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCungbr_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverSideMode_t side,
                                             int                 m,
                                             int                 n,
                                             int                 k,
                                             hipFloatComplex*    A,
                                             int                 lda,
                                             hipFloatComplex*    tau,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnCungbr_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_side(side),
                                                       m,
                                                       n,
                                                       k,
                                                       (cuComplex*)A,
                                                       lda,
                                                       (cuComplex*)tau,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZungbr_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverSideMode_t side,
                                             int                 m,
                                             int                 n,
                                             int                 k,
                                             hipDoubleComplex*   A,
                                             int                 lda,
                                             hipDoubleComplex*   tau,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnZungbr_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_side(side),
                                                       m,
                                                       n,
                                                       k,
                                                       (cuDoubleComplex*)A,
                                                       lda,
                                                       (cuDoubleComplex*)tau,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSorgbr(hipsolverHandle_t   handle,
                                  hipsolverSideMode_t side,
                                  int                 m,
                                  int                 n,
                                  int                 k,
                                  float*              A,
                                  int                 lda,
                                  float*              tau,
                                  float*              work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnSorgbr((cusolverDnHandle_t)handle,
                                            hip2cuda_side(side),
                                            m,
                                            n,
                                            k,
                                            A,
                                            lda,
                                            tau,
                                            work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDorgbr(hipsolverHandle_t   handle,
                                  hipsolverSideMode_t side,
                                  int                 m,
                                  int                 n,
                                  int                 k,
                                  double*             A,
                                  int                 lda,
                                  double*             tau,
                                  double*             work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnDorgbr((cusolverDnHandle_t)handle,
                                            hip2cuda_side(side),
                                            m,
                                            n,
                                            k,
                                            A,
                                            lda,
                                            tau,
                                            work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCungbr(hipsolverHandle_t   handle,
                                  hipsolverSideMode_t side,
                                  int                 m,
                                  int                 n,
                                  int                 k,
                                  hipFloatComplex*    A,
                                  int                 lda,
                                  hipFloatComplex*    tau,
                                  hipFloatComplex*    work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnCungbr((cusolverDnHandle_t)handle,
                                            hip2cuda_side(side),
                                            m,
                                            n,
                                            k,
                                            (cuComplex*)A,
                                            lda,
                                            (cuComplex*)tau,
                                            (cuComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZungbr(hipsolverHandle_t   handle,
                                  hipsolverSideMode_t side,
                                  int                 m,
                                  int                 n,
                                  int                 k,
                                  hipDoubleComplex*   A,
                                  int                 lda,
                                  hipDoubleComplex*   tau,
                                  hipDoubleComplex*   work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnZungbr((cusolverDnHandle_t)handle,
                                            hip2cuda_side(side),
                                            m,
                                            n,
                                            k,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            (cuDoubleComplex*)tau,
                                            (cuDoubleComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

/******************** ORGQR/UNGQR ********************/
hipsolverStatus_t hipsolverSorgqr_bufferSize(
    hipsolverHandle_t handle, int m, int n, int k, float* A, int lda, float* tau, int* lwork)
try
{
    return cuda2hip_status(
        cusolverDnSorgqr_bufferSize((cusolverDnHandle_t)handle, m, n, k, A, lda, tau, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDorgqr_bufferSize(
    hipsolverHandle_t handle, int m, int n, int k, double* A, int lda, double* tau, int* lwork)
try
{
    return cuda2hip_status(
        cusolverDnDorgqr_bufferSize((cusolverDnHandle_t)handle, m, n, k, A, lda, tau, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCungqr_bufferSize(hipsolverHandle_t handle,
                                             int               m,
                                             int               n,
                                             int               k,
                                             hipFloatComplex*  A,
                                             int               lda,
                                             hipFloatComplex*  tau,
                                             int*              lwork)
try
{
    return cuda2hip_status(cusolverDnCungqr_bufferSize(
        (cusolverDnHandle_t)handle, m, n, k, (cuComplex*)A, lda, (cuComplex*)tau, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZungqr_bufferSize(hipsolverHandle_t handle,
                                             int               m,
                                             int               n,
                                             int               k,
                                             hipDoubleComplex* A,
                                             int               lda,
                                             hipDoubleComplex* tau,
                                             int*              lwork)
try
{
    return cuda2hip_status(cusolverDnZungqr_bufferSize((cusolverDnHandle_t)handle,
                                                       m,
                                                       n,
                                                       k,
                                                       (cuDoubleComplex*)A,
                                                       lda,
                                                       (cuDoubleComplex*)tau,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSorgqr(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  int               k,
                                  float*            A,
                                  int               lda,
                                  float*            tau,
                                  float*            work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(
        cusolverDnSorgqr((cusolverDnHandle_t)handle, m, n, k, A, lda, tau, work, lwork, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDorgqr(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  int               k,
                                  double*           A,
                                  int               lda,
                                  double*           tau,
                                  double*           work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(
        cusolverDnDorgqr((cusolverDnHandle_t)handle, m, n, k, A, lda, tau, work, lwork, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCungqr(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  int               k,
                                  hipFloatComplex*  A,
                                  int               lda,
                                  hipFloatComplex*  tau,
                                  hipFloatComplex*  work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnCungqr((cusolverDnHandle_t)handle,
                                            m,
                                            n,
                                            k,
                                            (cuComplex*)A,
                                            lda,
                                            (cuComplex*)tau,
                                            (cuComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZungqr(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  int               k,
                                  hipDoubleComplex* A,
                                  int               lda,
                                  hipDoubleComplex* tau,
                                  hipDoubleComplex* work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnZungqr((cusolverDnHandle_t)handle,
                                            m,
                                            n,
                                            k,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            (cuDoubleComplex*)tau,
                                            (cuDoubleComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

/******************** ORGTR/UNGTR ********************/
hipsolverStatus_t hipsolverSorgtr_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             float*              A,
                                             int                 lda,
                                             float*              tau,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnSorgtr_bufferSize(
        (cusolverDnHandle_t)handle, hip2cuda_fill(uplo), n, A, lda, tau, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDorgtr_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             double*             A,
                                             int                 lda,
                                             double*             tau,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnDorgtr_bufferSize(
        (cusolverDnHandle_t)handle, hip2cuda_fill(uplo), n, A, lda, tau, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCungtr_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             hipFloatComplex*    A,
                                             int                 lda,
                                             hipFloatComplex*    tau,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnCungtr_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_fill(uplo),
                                                       n,
                                                       (cuComplex*)A,
                                                       lda,
                                                       (cuComplex*)tau,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZungtr_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             hipDoubleComplex*   A,
                                             int                 lda,
                                             hipDoubleComplex*   tau,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnZungtr_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_fill(uplo),
                                                       n,
                                                       (cuDoubleComplex*)A,
                                                       lda,
                                                       (cuDoubleComplex*)tau,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSorgtr(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  float*              A,
                                  int                 lda,
                                  float*              tau,
                                  float*              work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnSorgtr(
        (cusolverDnHandle_t)handle, hip2cuda_fill(uplo), n, A, lda, tau, work, lwork, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDorgtr(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  double*             A,
                                  int                 lda,
                                  double*             tau,
                                  double*             work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnDorgtr(
        (cusolverDnHandle_t)handle, hip2cuda_fill(uplo), n, A, lda, tau, work, lwork, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCungtr(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  hipFloatComplex*    A,
                                  int                 lda,
                                  hipFloatComplex*    tau,
                                  hipFloatComplex*    work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnCungtr((cusolverDnHandle_t)handle,
                                            hip2cuda_fill(uplo),
                                            n,
                                            (cuComplex*)A,
                                            lda,
                                            (cuComplex*)tau,
                                            (cuComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZungtr(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  hipDoubleComplex*   A,
                                  int                 lda,
                                  hipDoubleComplex*   tau,
                                  hipDoubleComplex*   work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnZungtr((cusolverDnHandle_t)handle,
                                            hip2cuda_fill(uplo),
                                            n,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            (cuDoubleComplex*)tau,
                                            (cuDoubleComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

/******************** ORMQR/UNMQR ********************/
hipsolverStatus_t hipsolverSormqr_bufferSize(hipsolverHandle_t    handle,
                                             hipsolverSideMode_t  side,
                                             hipsolverOperation_t trans,
                                             int                  m,
                                             int                  n,
                                             int                  k,
                                             float*               A,
                                             int                  lda,
                                             float*               tau,
                                             float*               C,
                                             int                  ldc,
                                             int*                 lwork)
try
{
    return cuda2hip_status(cusolverDnSormqr_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_side(side),
                                                       hip2cuda_operation(trans),
                                                       m,
                                                       n,
                                                       k,
                                                       A,
                                                       lda,
                                                       tau,
                                                       C,
                                                       ldc,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDormqr_bufferSize(hipsolverHandle_t    handle,
                                             hipsolverSideMode_t  side,
                                             hipsolverOperation_t trans,
                                             int                  m,
                                             int                  n,
                                             int                  k,
                                             double*              A,
                                             int                  lda,
                                             double*              tau,
                                             double*              C,
                                             int                  ldc,
                                             int*                 lwork)
try
{
    return cuda2hip_status(cusolverDnDormqr_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_side(side),
                                                       hip2cuda_operation(trans),
                                                       m,
                                                       n,
                                                       k,
                                                       A,
                                                       lda,
                                                       tau,
                                                       C,
                                                       ldc,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCunmqr_bufferSize(hipsolverHandle_t    handle,
                                             hipsolverSideMode_t  side,
                                             hipsolverOperation_t trans,
                                             int                  m,
                                             int                  n,
                                             int                  k,
                                             hipFloatComplex*     A,
                                             int                  lda,
                                             hipFloatComplex*     tau,
                                             hipFloatComplex*     C,
                                             int                  ldc,
                                             int*                 lwork)
try
{
    return cuda2hip_status(cusolverDnCunmqr_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_side(side),
                                                       hip2cuda_operation(trans),
                                                       m,
                                                       n,
                                                       k,
                                                       (cuComplex*)A,
                                                       lda,
                                                       (cuComplex*)tau,
                                                       (cuComplex*)C,
                                                       ldc,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZunmqr_bufferSize(hipsolverHandle_t    handle,
                                             hipsolverSideMode_t  side,
                                             hipsolverOperation_t trans,
                                             int                  m,
                                             int                  n,
                                             int                  k,
                                             hipDoubleComplex*    A,
                                             int                  lda,
                                             hipDoubleComplex*    tau,
                                             hipDoubleComplex*    C,
                                             int                  ldc,
                                             int*                 lwork)
try
{
    return cuda2hip_status(cusolverDnZunmqr_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_side(side),
                                                       hip2cuda_operation(trans),
                                                       m,
                                                       n,
                                                       k,
                                                       (cuDoubleComplex*)A,
                                                       lda,
                                                       (cuDoubleComplex*)tau,
                                                       (cuDoubleComplex*)C,
                                                       ldc,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSormqr(hipsolverHandle_t    handle,
                                  hipsolverSideMode_t  side,
                                  hipsolverOperation_t trans,
                                  int                  m,
                                  int                  n,
                                  int                  k,
                                  float*               A,
                                  int                  lda,
                                  float*               tau,
                                  float*               C,
                                  int                  ldc,
                                  float*               work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    return cuda2hip_status(cusolverDnSormqr((cusolverDnHandle_t)handle,
                                            hip2cuda_side(side),
                                            hip2cuda_operation(trans),
                                            m,
                                            n,
                                            k,
                                            A,
                                            lda,
                                            tau,
                                            C,
                                            ldc,
                                            work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDormqr(hipsolverHandle_t    handle,
                                  hipsolverSideMode_t  side,
                                  hipsolverOperation_t trans,
                                  int                  m,
                                  int                  n,
                                  int                  k,
                                  double*              A,
                                  int                  lda,
                                  double*              tau,
                                  double*              C,
                                  int                  ldc,
                                  double*              work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    return cuda2hip_status(cusolverDnDormqr((cusolverDnHandle_t)handle,
                                            hip2cuda_side(side),
                                            hip2cuda_operation(trans),
                                            m,
                                            n,
                                            k,
                                            A,
                                            lda,
                                            tau,
                                            C,
                                            ldc,
                                            work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCunmqr(hipsolverHandle_t    handle,
                                  hipsolverSideMode_t  side,
                                  hipsolverOperation_t trans,
                                  int                  m,
                                  int                  n,
                                  int                  k,
                                  hipFloatComplex*     A,
                                  int                  lda,
                                  hipFloatComplex*     tau,
                                  hipFloatComplex*     C,
                                  int                  ldc,
                                  hipFloatComplex*     work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    return cuda2hip_status(cusolverDnCunmqr((cusolverDnHandle_t)handle,
                                            hip2cuda_side(side),
                                            hip2cuda_operation(trans),
                                            m,
                                            n,
                                            k,
                                            (cuComplex*)A,
                                            lda,
                                            (cuComplex*)tau,
                                            (cuComplex*)C,
                                            ldc,
                                            (cuComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZunmqr(hipsolverHandle_t    handle,
                                  hipsolverSideMode_t  side,
                                  hipsolverOperation_t trans,
                                  int                  m,
                                  int                  n,
                                  int                  k,
                                  hipDoubleComplex*    A,
                                  int                  lda,
                                  hipDoubleComplex*    tau,
                                  hipDoubleComplex*    C,
                                  int                  ldc,
                                  hipDoubleComplex*    work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    return cuda2hip_status(cusolverDnZunmqr((cusolverDnHandle_t)handle,
                                            hip2cuda_side(side),
                                            hip2cuda_operation(trans),
                                            m,
                                            n,
                                            k,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            (cuDoubleComplex*)tau,
                                            (cuDoubleComplex*)C,
                                            ldc,
                                            (cuDoubleComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

/******************** ORMTR/UNMTR ********************/
hipsolverStatus_t hipsolverSormtr_bufferSize(hipsolverHandle_t    handle,
                                             hipsolverSideMode_t  side,
                                             hipsolverFillMode_t  uplo,
                                             hipsolverOperation_t trans,
                                             int                  m,
                                             int                  n,
                                             float*               A,
                                             int                  lda,
                                             float*               tau,
                                             float*               C,
                                             int                  ldc,
                                             int*                 lwork)
try
{
    return cuda2hip_status(cusolverDnSormtr_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_side(side),
                                                       hip2cuda_fill(uplo),
                                                       hip2cuda_operation(trans),
                                                       m,
                                                       n,
                                                       A,
                                                       lda,
                                                       tau,
                                                       C,
                                                       ldc,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDormtr_bufferSize(hipsolverHandle_t    handle,
                                             hipsolverSideMode_t  side,
                                             hipsolverFillMode_t  uplo,
                                             hipsolverOperation_t trans,
                                             int                  m,
                                             int                  n,
                                             double*              A,
                                             int                  lda,
                                             double*              tau,
                                             double*              C,
                                             int                  ldc,
                                             int*                 lwork)
try
{
    return cuda2hip_status(cusolverDnDormtr_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_side(side),
                                                       hip2cuda_fill(uplo),
                                                       hip2cuda_operation(trans),
                                                       m,
                                                       n,
                                                       A,
                                                       lda,
                                                       tau,
                                                       C,
                                                       ldc,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCunmtr_bufferSize(hipsolverHandle_t    handle,
                                             hipsolverSideMode_t  side,
                                             hipsolverFillMode_t  uplo,
                                             hipsolverOperation_t trans,
                                             int                  m,
                                             int                  n,
                                             hipFloatComplex*     A,
                                             int                  lda,
                                             hipFloatComplex*     tau,
                                             hipFloatComplex*     C,
                                             int                  ldc,
                                             int*                 lwork)
try
{
    return cuda2hip_status(cusolverDnCunmtr_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_side(side),
                                                       hip2cuda_fill(uplo),
                                                       hip2cuda_operation(trans),
                                                       m,
                                                       n,
                                                       (cuComplex*)A,
                                                       lda,
                                                       (cuComplex*)tau,
                                                       (cuComplex*)C,
                                                       ldc,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZunmtr_bufferSize(hipsolverHandle_t    handle,
                                             hipsolverSideMode_t  side,
                                             hipsolverFillMode_t  uplo,
                                             hipsolverOperation_t trans,
                                             int                  m,
                                             int                  n,
                                             hipDoubleComplex*    A,
                                             int                  lda,
                                             hipDoubleComplex*    tau,
                                             hipDoubleComplex*    C,
                                             int                  ldc,
                                             int*                 lwork)
try
{
    return cuda2hip_status(cusolverDnZunmtr_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_side(side),
                                                       hip2cuda_fill(uplo),
                                                       hip2cuda_operation(trans),
                                                       m,
                                                       n,
                                                       (cuDoubleComplex*)A,
                                                       lda,
                                                       (cuDoubleComplex*)tau,
                                                       (cuDoubleComplex*)C,
                                                       ldc,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSormtr(hipsolverHandle_t    handle,
                                  hipsolverSideMode_t  side,
                                  hipsolverFillMode_t  uplo,
                                  hipsolverOperation_t trans,
                                  int                  m,
                                  int                  n,
                                  float*               A,
                                  int                  lda,
                                  float*               tau,
                                  float*               C,
                                  int                  ldc,
                                  float*               work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    return cuda2hip_status(cusolverDnSormtr((cusolverDnHandle_t)handle,
                                            hip2cuda_side(side),
                                            hip2cuda_fill(uplo),
                                            hip2cuda_operation(trans),
                                            m,
                                            n,
                                            A,
                                            lda,
                                            tau,
                                            C,
                                            ldc,
                                            work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDormtr(hipsolverHandle_t    handle,
                                  hipsolverSideMode_t  side,
                                  hipsolverFillMode_t  uplo,
                                  hipsolverOperation_t trans,
                                  int                  m,
                                  int                  n,
                                  double*              A,
                                  int                  lda,
                                  double*              tau,
                                  double*              C,
                                  int                  ldc,
                                  double*              work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    return cuda2hip_status(cusolverDnDormtr((cusolverDnHandle_t)handle,
                                            hip2cuda_side(side),
                                            hip2cuda_fill(uplo),
                                            hip2cuda_operation(trans),
                                            m,
                                            n,
                                            A,
                                            lda,
                                            tau,
                                            C,
                                            ldc,
                                            work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCunmtr(hipsolverHandle_t    handle,
                                  hipsolverSideMode_t  side,
                                  hipsolverFillMode_t  uplo,
                                  hipsolverOperation_t trans,
                                  int                  m,
                                  int                  n,
                                  hipFloatComplex*     A,
                                  int                  lda,
                                  hipFloatComplex*     tau,
                                  hipFloatComplex*     C,
                                  int                  ldc,
                                  hipFloatComplex*     work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    return cuda2hip_status(cusolverDnCunmtr((cusolverDnHandle_t)handle,
                                            hip2cuda_side(side),
                                            hip2cuda_fill(uplo),
                                            hip2cuda_operation(trans),
                                            m,
                                            n,
                                            (cuComplex*)A,
                                            lda,
                                            (cuComplex*)tau,
                                            (cuComplex*)C,
                                            ldc,
                                            (cuComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZunmtr(hipsolverHandle_t    handle,
                                  hipsolverSideMode_t  side,
                                  hipsolverFillMode_t  uplo,
                                  hipsolverOperation_t trans,
                                  int                  m,
                                  int                  n,
                                  hipDoubleComplex*    A,
                                  int                  lda,
                                  hipDoubleComplex*    tau,
                                  hipDoubleComplex*    C,
                                  int                  ldc,
                                  hipDoubleComplex*    work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    return cuda2hip_status(cusolverDnZunmtr((cusolverDnHandle_t)handle,
                                            hip2cuda_side(side),
                                            hip2cuda_fill(uplo),
                                            hip2cuda_operation(trans),
                                            m,
                                            n,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            (cuDoubleComplex*)tau,
                                            (cuDoubleComplex*)C,
                                            ldc,
                                            (cuDoubleComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

/******************** GEBRD ********************/
hipsolverStatus_t hipsolverSgebrd_bufferSize(hipsolverHandle_t handle, int m, int n, int* lwork)
try
{
    return cuda2hip_status(cusolverDnSgebrd_bufferSize((cusolverDnHandle_t)handle, m, n, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDgebrd_bufferSize(hipsolverHandle_t handle, int m, int n, int* lwork)
try
{
    return cuda2hip_status(cusolverDnDgebrd_bufferSize((cusolverDnHandle_t)handle, m, n, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgebrd_bufferSize(hipsolverHandle_t handle, int m, int n, int* lwork)
try
{
    return cuda2hip_status(cusolverDnCgebrd_bufferSize((cusolverDnHandle_t)handle, m, n, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgebrd_bufferSize(hipsolverHandle_t handle, int m, int n, int* lwork)
try
{
    return cuda2hip_status(cusolverDnZgebrd_bufferSize((cusolverDnHandle_t)handle, m, n, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSgebrd(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  float*            A,
                                  int               lda,
                                  float*            D,
                                  float*            E,
                                  float*            tauq,
                                  float*            taup,
                                  float*            work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnSgebrd(
        (cusolverDnHandle_t)handle, m, n, A, lda, D, E, tauq, taup, work, lwork, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDgebrd(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  double*           A,
                                  int               lda,
                                  double*           D,
                                  double*           E,
                                  double*           tauq,
                                  double*           taup,
                                  double*           work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnDgebrd(
        (cusolverDnHandle_t)handle, m, n, A, lda, D, E, tauq, taup, work, lwork, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgebrd(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  hipFloatComplex*  A,
                                  int               lda,
                                  float*            D,
                                  float*            E,
                                  hipFloatComplex*  tauq,
                                  hipFloatComplex*  taup,
                                  hipFloatComplex*  work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnCgebrd((cusolverDnHandle_t)handle,
                                            m,
                                            n,
                                            (cuComplex*)A,
                                            lda,
                                            D,
                                            E,
                                            (cuComplex*)tauq,
                                            (cuComplex*)taup,
                                            (cuComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgebrd(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  hipDoubleComplex* A,
                                  int               lda,
                                  double*           D,
                                  double*           E,
                                  hipDoubleComplex* tauq,
                                  hipDoubleComplex* taup,
                                  hipDoubleComplex* work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnZgebrd((cusolverDnHandle_t)handle,
                                            m,
                                            n,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            D,
                                            E,
                                            (cuDoubleComplex*)tauq,
                                            (cuDoubleComplex*)taup,
                                            (cuDoubleComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

/******************** GEQRF ********************/
hipsolverStatus_t hipsolverSgeqrf_bufferSize(
    hipsolverHandle_t handle, int m, int n, float* A, int lda, int* lwork)
try
{
    return cuda2hip_status(
        cusolverDnSgeqrf_bufferSize((cusolverDnHandle_t)handle, m, n, A, lda, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDgeqrf_bufferSize(
    hipsolverHandle_t handle, int m, int n, double* A, int lda, int* lwork)
try
{
    return cuda2hip_status(
        cusolverDnDgeqrf_bufferSize((cusolverDnHandle_t)handle, m, n, A, lda, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgeqrf_bufferSize(
    hipsolverHandle_t handle, int m, int n, hipFloatComplex* A, int lda, int* lwork)
try
{
    return cuda2hip_status(
        cusolverDnCgeqrf_bufferSize((cusolverDnHandle_t)handle, m, n, (cuComplex*)A, lda, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgeqrf_bufferSize(
    hipsolverHandle_t handle, int m, int n, hipDoubleComplex* A, int lda, int* lwork)
try
{
    return cuda2hip_status(cusolverDnZgeqrf_bufferSize(
        (cusolverDnHandle_t)handle, m, n, (cuDoubleComplex*)A, lda, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSgeqrf(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  float*            A,
                                  int               lda,
                                  float*            tau,
                                  float*            work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(
        cusolverDnSgeqrf((cusolverDnHandle_t)handle, m, n, A, lda, tau, work, lwork, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDgeqrf(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  double*           A,
                                  int               lda,
                                  double*           tau,
                                  double*           work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(
        cusolverDnDgeqrf((cusolverDnHandle_t)handle, m, n, A, lda, tau, work, lwork, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgeqrf(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  hipFloatComplex*  A,
                                  int               lda,
                                  hipFloatComplex*  tau,
                                  hipFloatComplex*  work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnCgeqrf((cusolverDnHandle_t)handle,
                                            m,
                                            n,
                                            (cuComplex*)A,
                                            lda,
                                            (cuComplex*)tau,
                                            (cuComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgeqrf(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  hipDoubleComplex* A,
                                  int               lda,
                                  hipDoubleComplex* tau,
                                  hipDoubleComplex* work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnZgeqrf((cusolverDnHandle_t)handle,
                                            m,
                                            n,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            (cuDoubleComplex*)tau,
                                            (cuDoubleComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

/******************** GESV ********************/
HIPSOLVER_EXPORT hipsolverStatus_t hipsolverSSgesv_bufferSize(hipsolverHandle_t handle,
                                                              int               n,
                                                              int               nrhs,
                                                              float*            A,
                                                              int               lda,
                                                              int*              devIpiv,
                                                              float*            B,
                                                              int               ldb,
                                                              float*            X,
                                                              int               ldx,
                                                              size_t*           lwork)
try
{
    return cuda2hip_status(cusolverDnSSgesv_bufferSize(
        (cusolverDnHandle_t)handle, n, nrhs, A, lda, devIpiv, B, ldb, X, ldx, nullptr, lwork));
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverDDgesv_bufferSize(hipsolverHandle_t handle,
                                                              int               n,
                                                              int               nrhs,
                                                              double*           A,
                                                              int               lda,
                                                              int*              devIpiv,
                                                              double*           B,
                                                              int               ldb,
                                                              double*           X,
                                                              int               ldx,
                                                              size_t*           lwork)
try
{
    return cuda2hip_status(cusolverDnDDgesv_bufferSize(
        (cusolverDnHandle_t)handle, n, nrhs, A, lda, devIpiv, B, ldb, X, ldx, nullptr, lwork));
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverCCgesv_bufferSize(hipsolverHandle_t handle,
                                                              int               n,
                                                              int               nrhs,
                                                              hipFloatComplex*  A,
                                                              int               lda,
                                                              int*              devIpiv,
                                                              hipFloatComplex*  B,
                                                              int               ldb,
                                                              hipFloatComplex*  X,
                                                              int               ldx,
                                                              size_t*           lwork)
try
{
    return cuda2hip_status(cusolverDnCCgesv_bufferSize((cusolverDnHandle_t)handle,
                                                       n,
                                                       nrhs,
                                                       (cuComplex*)A,
                                                       lda,
                                                       devIpiv,
                                                       (cuComplex*)B,
                                                       ldb,
                                                       (cuComplex*)X,
                                                       ldx,
                                                       nullptr,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverZZgesv_bufferSize(hipsolverHandle_t handle,
                                                              int               n,
                                                              int               nrhs,
                                                              hipDoubleComplex* A,
                                                              int               lda,
                                                              int*              devIpiv,
                                                              hipDoubleComplex* B,
                                                              int               ldb,
                                                              hipDoubleComplex* X,
                                                              int               ldx,
                                                              size_t*           lwork)
try
{
    return cuda2hip_status(cusolverDnZZgesv_bufferSize((cusolverDnHandle_t)handle,
                                                       n,
                                                       nrhs,
                                                       (cuDoubleComplex*)A,
                                                       lda,
                                                       devIpiv,
                                                       (cuDoubleComplex*)B,
                                                       ldb,
                                                       (cuDoubleComplex*)X,
                                                       ldx,
                                                       nullptr,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverSSgesv(hipsolverHandle_t handle,
                                                   int               n,
                                                   int               nrhs,
                                                   float*            A,
                                                   int               lda,
                                                   int*              devIpiv,
                                                   float*            B,
                                                   int               ldb,
                                                   float*            X,
                                                   int               ldx,
                                                   void*             work,
                                                   size_t            lwork,
                                                   int*              niters,
                                                   int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnSSgesv((cusolverDnHandle_t)handle,
                                            n,
                                            nrhs,
                                            A,
                                            lda,
                                            devIpiv,
                                            B,
                                            ldb,
                                            X,
                                            ldx,
                                            work,
                                            lwork,
                                            niters,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverDDgesv(hipsolverHandle_t handle,
                                                   int               n,
                                                   int               nrhs,
                                                   double*           A,
                                                   int               lda,
                                                   int*              devIpiv,
                                                   double*           B,
                                                   int               ldb,
                                                   double*           X,
                                                   int               ldx,
                                                   void*             work,
                                                   size_t            lwork,
                                                   int*              niters,
                                                   int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnDDgesv((cusolverDnHandle_t)handle,
                                            n,
                                            nrhs,
                                            A,
                                            lda,
                                            devIpiv,
                                            B,
                                            ldb,
                                            X,
                                            ldx,
                                            work,
                                            lwork,
                                            niters,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverCCgesv(hipsolverHandle_t handle,
                                                   int               n,
                                                   int               nrhs,
                                                   hipFloatComplex*  A,
                                                   int               lda,
                                                   int*              devIpiv,
                                                   hipFloatComplex*  B,
                                                   int               ldb,
                                                   hipFloatComplex*  X,
                                                   int               ldx,
                                                   void*             work,
                                                   size_t            lwork,
                                                   int*              niters,
                                                   int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnCCgesv((cusolverDnHandle_t)handle,
                                            n,
                                            nrhs,
                                            (cuComplex*)A,
                                            lda,
                                            devIpiv,
                                            (cuComplex*)B,
                                            ldb,
                                            (cuComplex*)X,
                                            ldx,
                                            work,
                                            lwork,
                                            niters,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverZZgesv(hipsolverHandle_t handle,
                                                   int               n,
                                                   int               nrhs,
                                                   hipDoubleComplex* A,
                                                   int               lda,
                                                   int*              devIpiv,
                                                   hipDoubleComplex* B,
                                                   int               ldb,
                                                   hipDoubleComplex* X,
                                                   int               ldx,
                                                   void*             work,
                                                   size_t            lwork,
                                                   int*              niters,
                                                   int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnZZgesv((cusolverDnHandle_t)handle,
                                            n,
                                            nrhs,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            devIpiv,
                                            (cuDoubleComplex*)B,
                                            ldb,
                                            (cuDoubleComplex*)X,
                                            ldx,
                                            work,
                                            lwork,
                                            niters,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

/******************** GESVD ********************/
hipsolverStatus_t hipsolverSgesvd_bufferSize(
    hipsolverHandle_t handle, signed char jobu, signed char jobv, int m, int n, int* lwork)
try
{
    return cuda2hip_status(cusolverDnSgesvd_bufferSize((cusolverDnHandle_t)handle, m, n, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDgesvd_bufferSize(
    hipsolverHandle_t handle, signed char jobu, signed char jobv, int m, int n, int* lwork)
try
{
    return cuda2hip_status(cusolverDnSgesvd_bufferSize((cusolverDnHandle_t)handle, m, n, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgesvd_bufferSize(
    hipsolverHandle_t handle, signed char jobu, signed char jobv, int m, int n, int* lwork)
try
{
    return cuda2hip_status(cusolverDnSgesvd_bufferSize((cusolverDnHandle_t)handle, m, n, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgesvd_bufferSize(
    hipsolverHandle_t handle, signed char jobu, signed char jobv, int m, int n, int* lwork)
try
{
    return cuda2hip_status(cusolverDnSgesvd_bufferSize((cusolverDnHandle_t)handle, m, n, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSgesvd(hipsolverHandle_t handle,
                                  signed char       jobu,
                                  signed char       jobv,
                                  int               m,
                                  int               n,
                                  float*            A,
                                  int               lda,
                                  float*            S,
                                  float*            U,
                                  int               ldu,
                                  float*            V,
                                  int               ldv,
                                  float*            work,
                                  int               lwork,
                                  float*            rwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnSgesvd((cusolverDnHandle_t)handle,
                                            jobu,
                                            jobv,
                                            m,
                                            n,
                                            A,
                                            lda,
                                            S,
                                            U,
                                            ldu,
                                            V,
                                            ldv,
                                            work,
                                            lwork,
                                            rwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDgesvd(hipsolverHandle_t handle,
                                  signed char       jobu,
                                  signed char       jobv,
                                  int               m,
                                  int               n,
                                  double*           A,
                                  int               lda,
                                  double*           S,
                                  double*           U,
                                  int               ldu,
                                  double*           V,
                                  int               ldv,
                                  double*           work,
                                  int               lwork,
                                  double*           rwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnDgesvd((cusolverDnHandle_t)handle,
                                            jobu,
                                            jobv,
                                            m,
                                            n,
                                            A,
                                            lda,
                                            S,
                                            U,
                                            ldu,
                                            V,
                                            ldv,
                                            work,
                                            lwork,
                                            rwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgesvd(hipsolverHandle_t handle,
                                  signed char       jobu,
                                  signed char       jobv,
                                  int               m,
                                  int               n,
                                  hipFloatComplex*  A,
                                  int               lda,
                                  float*            S,
                                  hipFloatComplex*  U,
                                  int               ldu,
                                  hipFloatComplex*  V,
                                  int               ldv,
                                  hipFloatComplex*  work,
                                  int               lwork,
                                  float*            rwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnCgesvd((cusolverDnHandle_t)handle,
                                            jobu,
                                            jobv,
                                            m,
                                            n,
                                            (cuComplex*)A,
                                            lda,
                                            S,
                                            (cuComplex*)U,
                                            ldu,
                                            (cuComplex*)V,
                                            ldv,
                                            (cuComplex*)work,
                                            lwork,
                                            rwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgesvd(hipsolverHandle_t handle,
                                  signed char       jobu,
                                  signed char       jobv,
                                  int               m,
                                  int               n,
                                  hipDoubleComplex* A,
                                  int               lda,
                                  double*           S,
                                  hipDoubleComplex* U,
                                  int               ldu,
                                  hipDoubleComplex* V,
                                  int               ldv,
                                  hipDoubleComplex* work,
                                  int               lwork,
                                  double*           rwork,
                                  int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnZgesvd((cusolverDnHandle_t)handle,
                                            jobu,
                                            jobv,
                                            m,
                                            n,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            S,
                                            (cuDoubleComplex*)U,
                                            ldu,
                                            (cuDoubleComplex*)V,
                                            ldv,
                                            (cuDoubleComplex*)work,
                                            lwork,
                                            rwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

/******************** GETRF ********************/
hipsolverStatus_t hipsolverSgetrf_bufferSize(
    hipsolverHandle_t handle, int m, int n, float* A, int lda, int* lwork)
try
{
    return cuda2hip_status(
        cusolverDnSgetrf_bufferSize((cusolverDnHandle_t)handle, m, n, A, lda, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDgetrf_bufferSize(
    hipsolverHandle_t handle, int m, int n, double* A, int lda, int* lwork)
try
{
    return cuda2hip_status(
        cusolverDnDgetrf_bufferSize((cusolverDnHandle_t)handle, m, n, A, lda, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgetrf_bufferSize(
    hipsolverHandle_t handle, int m, int n, hipFloatComplex* A, int lda, int* lwork)
try
{
    return cuda2hip_status(
        cusolverDnCgetrf_bufferSize((cusolverDnHandle_t)handle, m, n, (cuComplex*)A, lda, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgetrf_bufferSize(
    hipsolverHandle_t handle, int m, int n, hipDoubleComplex* A, int lda, int* lwork)
try
{
    return cuda2hip_status(cusolverDnZgetrf_bufferSize(
        (cusolverDnHandle_t)handle, m, n, (cuDoubleComplex*)A, lda, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSgetrf(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  float*            A,
                                  int               lda,
                                  float*            work,
                                  int               lwork,
                                  int*              devIpiv,
                                  int*              devInfo)
try
{
    return cuda2hip_status(
        cusolverDnSgetrf((cusolverDnHandle_t)handle, m, n, A, lda, work, devIpiv, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDgetrf(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  double*           A,
                                  int               lda,
                                  double*           work,
                                  int               lwork,
                                  int*              devIpiv,
                                  int*              devInfo)
try
{
    return cuda2hip_status(
        cusolverDnDgetrf((cusolverDnHandle_t)handle, m, n, A, lda, work, devIpiv, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgetrf(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  hipFloatComplex*  A,
                                  int               lda,
                                  hipFloatComplex*  work,
                                  int               lwork,
                                  int*              devIpiv,
                                  int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnCgetrf(
        (cusolverDnHandle_t)handle, m, n, (cuComplex*)A, lda, (cuComplex*)work, devIpiv, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgetrf(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  hipDoubleComplex* A,
                                  int               lda,
                                  hipDoubleComplex* work,
                                  int               lwork,
                                  int*              devIpiv,
                                  int*              devInfo)
try
{
    return cuda2hip_status(cusolverDnZgetrf((cusolverDnHandle_t)handle,
                                            m,
                                            n,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            (cuDoubleComplex*)work,
                                            devIpiv,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

/******************** GETRS ********************/
hipsolverStatus_t hipsolverSgetrs_bufferSize(hipsolverHandle_t    handle,
                                             hipsolverOperation_t trans,
                                             int                  n,
                                             int                  nrhs,
                                             float*               A,
                                             int                  lda,
                                             int*                 devIpiv,
                                             float*               B,
                                             int                  ldb,
                                             int*                 lwork)
try
{
    *lwork = 0;
    return HIPSOLVER_STATUS_SUCCESS;
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDgetrs_bufferSize(hipsolverHandle_t    handle,
                                             hipsolverOperation_t trans,
                                             int                  n,
                                             int                  nrhs,
                                             double*              A,
                                             int                  lda,
                                             int*                 devIpiv,
                                             double*              B,
                                             int                  ldb,
                                             int*                 lwork)
try
{
    *lwork = 0;
    return HIPSOLVER_STATUS_SUCCESS;
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgetrs_bufferSize(hipsolverHandle_t    handle,
                                             hipsolverOperation_t trans,
                                             int                  n,
                                             int                  nrhs,
                                             hipFloatComplex*     A,
                                             int                  lda,
                                             int*                 devIpiv,
                                             hipFloatComplex*     B,
                                             int                  ldb,
                                             int*                 lwork)
try
{
    *lwork = 0;
    return HIPSOLVER_STATUS_SUCCESS;
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgetrs_bufferSize(hipsolverHandle_t    handle,
                                             hipsolverOperation_t trans,
                                             int                  n,
                                             int                  nrhs,
                                             hipDoubleComplex*    A,
                                             int                  lda,
                                             int*                 devIpiv,
                                             hipDoubleComplex*    B,
                                             int                  ldb,
                                             int*                 lwork)
try
{
    *lwork = 0;
    return HIPSOLVER_STATUS_SUCCESS;
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSgetrs(hipsolverHandle_t    handle,
                                  hipsolverOperation_t trans,
                                  int                  n,
                                  int                  nrhs,
                                  float*               A,
                                  int                  lda,
                                  int*                 devIpiv,
                                  float*               B,
                                  int                  ldb,
                                  float*               work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    return cuda2hip_status(cusolverDnSgetrs((cusolverDnHandle_t)handle,
                                            hip2cuda_operation(trans),
                                            n,
                                            nrhs,
                                            A,
                                            lda,
                                            devIpiv,
                                            B,
                                            ldb,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDgetrs(hipsolverHandle_t    handle,
                                  hipsolverOperation_t trans,
                                  int                  n,
                                  int                  nrhs,
                                  double*              A,
                                  int                  lda,
                                  int*                 devIpiv,
                                  double*              B,
                                  int                  ldb,
                                  double*              work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    return cuda2hip_status(cusolverDnDgetrs((cusolverDnHandle_t)handle,
                                            hip2cuda_operation(trans),
                                            n,
                                            nrhs,
                                            A,
                                            lda,
                                            devIpiv,
                                            B,
                                            ldb,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgetrs(hipsolverHandle_t    handle,
                                  hipsolverOperation_t trans,
                                  int                  n,
                                  int                  nrhs,
                                  hipFloatComplex*     A,
                                  int                  lda,
                                  int*                 devIpiv,
                                  hipFloatComplex*     B,
                                  int                  ldb,
                                  hipFloatComplex*     work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    return cuda2hip_status(cusolverDnCgetrs((cusolverDnHandle_t)handle,
                                            hip2cuda_operation(trans),
                                            n,
                                            nrhs,
                                            (cuComplex*)A,
                                            lda,
                                            devIpiv,
                                            (cuComplex*)B,
                                            ldb,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgetrs(hipsolverHandle_t    handle,
                                  hipsolverOperation_t trans,
                                  int                  n,
                                  int                  nrhs,
                                  hipDoubleComplex*    A,
                                  int                  lda,
                                  int*                 devIpiv,
                                  hipDoubleComplex*    B,
                                  int                  ldb,
                                  hipDoubleComplex*    work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    return cuda2hip_status(cusolverDnZgetrs((cusolverDnHandle_t)handle,
                                            hip2cuda_operation(trans),
                                            n,
                                            nrhs,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            devIpiv,
                                            (cuDoubleComplex*)B,
                                            ldb,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

/******************** POTRF ********************/
hipsolverStatus_t hipsolverSpotrf_bufferSize(
    hipsolverHandle_t handle, hipsolverFillMode_t uplo, int n, float* A, int lda, int* lwork)
try
{
    return cuda2hip_status(cusolverDnSpotrf_bufferSize(
        (cusolverDnHandle_t)handle, hip2cuda_fill(uplo), n, A, lda, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDpotrf_bufferSize(
    hipsolverHandle_t handle, hipsolverFillMode_t uplo, int n, double* A, int lda, int* lwork)
try
{
    return cuda2hip_status(cusolverDnDpotrf_bufferSize(
        (cusolverDnHandle_t)handle, hip2cuda_fill(uplo), n, A, lda, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCpotrf_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             hipFloatComplex*    A,
                                             int                 lda,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnCpotrf_bufferSize(
        (cusolverDnHandle_t)handle, hip2cuda_fill(uplo), n, (cuComplex*)A, lda, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZpotrf_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             hipDoubleComplex*   A,
                                             int                 lda,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnZpotrf_bufferSize(
        (cusolverDnHandle_t)handle, hip2cuda_fill(uplo), n, (cuDoubleComplex*)A, lda, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSpotrf(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  float*              A,
                                  int                 lda,
                                  float*              work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnSpotrf(
        (cusolverDnHandle_t)handle, hip2cuda_fill(uplo), n, A, lda, work, lwork, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDpotrf(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  double*             A,
                                  int                 lda,
                                  double*             work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnDpotrf(
        (cusolverDnHandle_t)handle, hip2cuda_fill(uplo), n, A, lda, work, lwork, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCpotrf(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  hipFloatComplex*    A,
                                  int                 lda,
                                  hipFloatComplex*    work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnCpotrf((cusolverDnHandle_t)handle,
                                            hip2cuda_fill(uplo),
                                            n,
                                            (cuComplex*)A,
                                            lda,
                                            (cuComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZpotrf(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  hipDoubleComplex*   A,
                                  int                 lda,
                                  hipDoubleComplex*   work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnZpotrf((cusolverDnHandle_t)handle,
                                            hip2cuda_fill(uplo),
                                            n,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            (cuDoubleComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

/******************** POTRF_BATCHED ********************/
hipsolverStatus_t hipsolverSpotrfBatched_bufferSize(hipsolverHandle_t   handle,
                                                    hipsolverFillMode_t uplo,
                                                    int                 n,
                                                    float*              A[],
                                                    int                 lda,
                                                    int*                lwork,
                                                    int                 batch_count)
try
{
    *lwork = 0;
    return HIPSOLVER_STATUS_SUCCESS;
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDpotrfBatched_bufferSize(hipsolverHandle_t   handle,
                                                    hipsolverFillMode_t uplo,
                                                    int                 n,
                                                    double*             A[],
                                                    int                 lda,
                                                    int*                lwork,
                                                    int                 batch_count)
try
{
    *lwork = 0;
    return HIPSOLVER_STATUS_SUCCESS;
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCpotrfBatched_bufferSize(hipsolverHandle_t   handle,
                                                    hipsolverFillMode_t uplo,
                                                    int                 n,
                                                    hipFloatComplex*    A[],
                                                    int                 lda,
                                                    int*                lwork,
                                                    int                 batch_count)
try
{
    *lwork = 0;
    return HIPSOLVER_STATUS_SUCCESS;
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZpotrfBatched_bufferSize(hipsolverHandle_t   handle,
                                                    hipsolverFillMode_t uplo,
                                                    int                 n,
                                                    hipDoubleComplex*   A[],
                                                    int                 lda,
                                                    int*                lwork,
                                                    int                 batch_count)
try
{
    *lwork = 0;
    return HIPSOLVER_STATUS_SUCCESS;
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSpotrfBatched(hipsolverHandle_t   handle,
                                         hipsolverFillMode_t uplo,
                                         int                 n,
                                         float*              A[],
                                         int                 lda,
                                         float*              work,
                                         int                 lwork,
                                         int*                devInfo,
                                         int                 batch_count)
try
{
    return cuda2hip_status(cusolverDnSpotrfBatched(
        (cusolverDnHandle_t)handle, hip2cuda_fill(uplo), n, A, lda, devInfo, batch_count));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDpotrfBatched(hipsolverHandle_t   handle,
                                         hipsolverFillMode_t uplo,
                                         int                 n,
                                         double*             A[],
                                         int                 lda,
                                         double*             work,
                                         int                 lwork,
                                         int*                devInfo,
                                         int                 batch_count)
try
{
    return cuda2hip_status(cusolverDnDpotrfBatched(
        (cusolverDnHandle_t)handle, hip2cuda_fill(uplo), n, A, lda, devInfo, batch_count));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCpotrfBatched(hipsolverHandle_t   handle,
                                         hipsolverFillMode_t uplo,
                                         int                 n,
                                         hipFloatComplex*    A[],
                                         int                 lda,
                                         hipFloatComplex*    work,
                                         int                 lwork,
                                         int*                devInfo,
                                         int                 batch_count)
try
{
    return cuda2hip_status(cusolverDnCpotrfBatched((cusolverDnHandle_t)handle,
                                                   hip2cuda_fill(uplo),
                                                   n,
                                                   (cuComplex**)A,
                                                   lda,
                                                   devInfo,
                                                   batch_count));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZpotrfBatched(hipsolverHandle_t   handle,
                                         hipsolverFillMode_t uplo,
                                         int                 n,
                                         hipDoubleComplex*   A[],
                                         int                 lda,
                                         hipDoubleComplex*   work,
                                         int                 lwork,
                                         int*                devInfo,
                                         int                 batch_count)
try
{
    return cuda2hip_status(cusolverDnZpotrfBatched((cusolverDnHandle_t)handle,
                                                   hip2cuda_fill(uplo),
                                                   n,
                                                   (cuDoubleComplex**)A,
                                                   lda,
                                                   devInfo,
                                                   batch_count));
}
catch(...)
{
    return exception2hip_status();
}

/******************** SYEVD/HEEVD ********************/
hipsolverStatus_t hipsolverSsyevd_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverEigMode_t  jobz,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             float*              A,
                                             int                 lda,
                                             float*              D,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnSsyevd_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_evect(jobz),
                                                       hip2cuda_fill(uplo),
                                                       n,
                                                       A,
                                                       lda,
                                                       D,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDsyevd_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverEigMode_t  jobz,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             double*             A,
                                             int                 lda,
                                             double*             D,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnDsyevd_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_evect(jobz),
                                                       hip2cuda_fill(uplo),
                                                       n,
                                                       A,
                                                       lda,
                                                       D,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCheevd_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverEigMode_t  jobz,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             hipFloatComplex*    A,
                                             int                 lda,
                                             float*              D,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnCheevd_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_evect(jobz),
                                                       hip2cuda_fill(uplo),
                                                       n,
                                                       (cuComplex*)A,
                                                       lda,
                                                       D,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZheevd_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverEigMode_t  jobz,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             hipDoubleComplex*   A,
                                             int                 lda,
                                             double*             D,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnZheevd_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_evect(jobz),
                                                       hip2cuda_fill(uplo),
                                                       n,
                                                       (cuDoubleComplex*)A,
                                                       lda,
                                                       D,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSsyevd(hipsolverHandle_t   handle,
                                  hipsolverEigMode_t  jobz,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  float*              A,
                                  int                 lda,
                                  float*              D,
                                  float*              work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnSsyevd((cusolverDnHandle_t)handle,
                                            hip2cuda_evect(jobz),
                                            hip2cuda_fill(uplo),
                                            n,
                                            A,
                                            lda,
                                            D,
                                            work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDsyevd(hipsolverHandle_t   handle,
                                  hipsolverEigMode_t  jobz,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  double*             A,
                                  int                 lda,
                                  double*             D,
                                  double*             work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnDsyevd((cusolverDnHandle_t)handle,
                                            hip2cuda_evect(jobz),
                                            hip2cuda_fill(uplo),
                                            n,
                                            A,
                                            lda,
                                            D,
                                            work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCheevd(hipsolverHandle_t   handle,
                                  hipsolverEigMode_t  jobz,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  hipFloatComplex*    A,
                                  int                 lda,
                                  float*              D,
                                  hipFloatComplex*    work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnCheevd((cusolverDnHandle_t)handle,
                                            hip2cuda_evect(jobz),
                                            hip2cuda_fill(uplo),
                                            n,
                                            (cuComplex*)A,
                                            lda,
                                            D,
                                            (cuComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZheevd(hipsolverHandle_t   handle,
                                  hipsolverEigMode_t  jobz,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  hipDoubleComplex*   A,
                                  int                 lda,
                                  double*             D,
                                  hipDoubleComplex*   work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnZheevd((cusolverDnHandle_t)handle,
                                            hip2cuda_evect(jobz),
                                            hip2cuda_fill(uplo),
                                            n,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            D,
                                            (cuDoubleComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

/******************** SYGVD/HEGVD ********************/
HIPSOLVER_EXPORT hipsolverStatus_t hipsolverSsygvd_bufferSize(hipsolverHandle_t   handle,
                                                              hipsolverEigType_t  itype,
                                                              hipsolverEigMode_t  jobz,
                                                              hipsolverFillMode_t uplo,
                                                              int                 n,
                                                              float*              A,
                                                              int                 lda,
                                                              float*              B,
                                                              int                 ldb,
                                                              float*              D,
                                                              int*                lwork)
try
{
    return cuda2hip_status(cusolverDnSsygvd_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_eform(itype),
                                                       hip2cuda_evect(jobz),
                                                       hip2cuda_fill(uplo),
                                                       n,
                                                       A,
                                                       lda,
                                                       B,
                                                       ldb,
                                                       D,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverDsygvd_bufferSize(hipsolverHandle_t   handle,
                                                              hipsolverEigType_t  itype,
                                                              hipsolverEigMode_t  jobz,
                                                              hipsolverFillMode_t uplo,
                                                              int                 n,
                                                              double*             A,
                                                              int                 lda,
                                                              double*             B,
                                                              int                 ldb,
                                                              double*             D,
                                                              int*                lwork)
try
{
    return cuda2hip_status(cusolverDnDsygvd_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_eform(itype),
                                                       hip2cuda_evect(jobz),
                                                       hip2cuda_fill(uplo),
                                                       n,
                                                       A,
                                                       lda,
                                                       B,
                                                       ldb,
                                                       D,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverChegvd_bufferSize(hipsolverHandle_t   handle,
                                                              hipsolverEigType_t  itype,
                                                              hipsolverEigMode_t  jobz,
                                                              hipsolverFillMode_t uplo,
                                                              int                 n,
                                                              hipFloatComplex*    A,
                                                              int                 lda,
                                                              hipFloatComplex*    B,
                                                              int                 ldb,
                                                              float*              D,
                                                              int*                lwork)
try
{
    return cuda2hip_status(cusolverDnChegvd_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_eform(itype),
                                                       hip2cuda_evect(jobz),
                                                       hip2cuda_fill(uplo),
                                                       n,
                                                       (cuComplex*)A,
                                                       lda,
                                                       (cuComplex*)B,
                                                       ldb,
                                                       D,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverZhegvd_bufferSize(hipsolverHandle_t   handle,
                                                              hipsolverEigType_t  itype,
                                                              hipsolverEigMode_t  jobz,
                                                              hipsolverFillMode_t uplo,
                                                              int                 n,
                                                              hipDoubleComplex*   A,
                                                              int                 lda,
                                                              hipDoubleComplex*   B,
                                                              int                 ldb,
                                                              double*             D,
                                                              int*                lwork)
try
{
    return cuda2hip_status(cusolverDnZhegvd_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_eform(itype),
                                                       hip2cuda_evect(jobz),
                                                       hip2cuda_fill(uplo),
                                                       n,
                                                       (cuDoubleComplex*)A,
                                                       lda,
                                                       (cuDoubleComplex*)B,
                                                       ldb,
                                                       D,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverSsygvd(hipsolverHandle_t   handle,
                                                   hipsolverEigType_t  itype,
                                                   hipsolverEigMode_t  jobz,
                                                   hipsolverFillMode_t uplo,
                                                   int                 n,
                                                   float*              A,
                                                   int                 lda,
                                                   float*              B,
                                                   int                 ldb,
                                                   float*              D,
                                                   float*              work,
                                                   int                 lwork,
                                                   int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnSsygvd((cusolverDnHandle_t)handle,
                                            hip2cuda_eform(itype),
                                            hip2cuda_evect(jobz),
                                            hip2cuda_fill(uplo),
                                            n,
                                            A,
                                            lda,
                                            B,
                                            ldb,
                                            D,
                                            work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverDsygvd(hipsolverHandle_t   handle,
                                                   hipsolverEigType_t  itype,
                                                   hipsolverEigMode_t  jobz,
                                                   hipsolverFillMode_t uplo,
                                                   int                 n,
                                                   double*             A,
                                                   int                 lda,
                                                   double*             B,
                                                   int                 ldb,
                                                   double*             D,
                                                   double*             work,
                                                   int                 lwork,
                                                   int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnDsygvd((cusolverDnHandle_t)handle,
                                            hip2cuda_eform(itype),
                                            hip2cuda_evect(jobz),
                                            hip2cuda_fill(uplo),
                                            n,
                                            A,
                                            lda,
                                            B,
                                            ldb,
                                            D,
                                            work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverChegvd(hipsolverHandle_t   handle,
                                                   hipsolverEigType_t  itype,
                                                   hipsolverEigMode_t  jobz,
                                                   hipsolverFillMode_t uplo,
                                                   int                 n,
                                                   hipFloatComplex*    A,
                                                   int                 lda,
                                                   hipFloatComplex*    B,
                                                   int                 ldb,
                                                   float*              D,
                                                   hipFloatComplex*    work,
                                                   int                 lwork,
                                                   int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnChegvd((cusolverDnHandle_t)handle,
                                            hip2cuda_eform(itype),
                                            hip2cuda_evect(jobz),
                                            hip2cuda_fill(uplo),
                                            n,
                                            (cuComplex*)A,
                                            lda,
                                            (cuComplex*)B,
                                            ldb,
                                            D,
                                            (cuComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverZhegvd(hipsolverHandle_t   handle,
                                                   hipsolverEigType_t  itype,
                                                   hipsolverEigMode_t  jobz,
                                                   hipsolverFillMode_t uplo,
                                                   int                 n,
                                                   hipDoubleComplex*   A,
                                                   int                 lda,
                                                   hipDoubleComplex*   B,
                                                   int                 ldb,
                                                   double*             D,
                                                   hipDoubleComplex*   work,
                                                   int                 lwork,
                                                   int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnZhegvd((cusolverDnHandle_t)handle,
                                            hip2cuda_eform(itype),
                                            hip2cuda_evect(jobz),
                                            hip2cuda_fill(uplo),
                                            n,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            (cuDoubleComplex*)B,
                                            ldb,
                                            D,
                                            (cuDoubleComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

/******************** SYTRD/HETRD ********************/
hipsolverStatus_t hipsolverSsytrd_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             float*              A,
                                             int                 lda,
                                             float*              D,
                                             float*              E,
                                             float*              tau,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnSsytrd_bufferSize(
        (cusolverDnHandle_t)handle, hip2cuda_fill(uplo), n, A, lda, D, E, tau, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDsytrd_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             double*             A,
                                             int                 lda,
                                             double*             D,
                                             double*             E,
                                             double*             tau,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnDsytrd_bufferSize(
        (cusolverDnHandle_t)handle, hip2cuda_fill(uplo), n, A, lda, D, E, tau, lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverChetrd_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             hipFloatComplex*    A,
                                             int                 lda,
                                             float*              D,
                                             float*              E,
                                             hipFloatComplex*    tau,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnChetrd_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_fill(uplo),
                                                       n,
                                                       (cuComplex*)A,
                                                       lda,
                                                       D,
                                                       E,
                                                       (cuComplex*)tau,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZhetrd_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             hipDoubleComplex*   A,
                                             int                 lda,
                                             double*             D,
                                             double*             E,
                                             hipDoubleComplex*   tau,
                                             int*                lwork)
try
{
    return cuda2hip_status(cusolverDnZhetrd_bufferSize((cusolverDnHandle_t)handle,
                                                       hip2cuda_fill(uplo),
                                                       n,
                                                       (cuDoubleComplex*)A,
                                                       lda,
                                                       D,
                                                       E,
                                                       (cuDoubleComplex*)tau,
                                                       lwork));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSsytrd(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  float*              A,
                                  int                 lda,
                                  float*              D,
                                  float*              E,
                                  float*              tau,
                                  float*              work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnSsytrd((cusolverDnHandle_t)handle,
                                            hip2cuda_fill(uplo),
                                            n,
                                            A,
                                            lda,
                                            D,
                                            E,
                                            tau,
                                            work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDsytrd(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  double*             A,
                                  int                 lda,
                                  double*             D,
                                  double*             E,
                                  double*             tau,
                                  double*             work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnDsytrd((cusolverDnHandle_t)handle,
                                            hip2cuda_fill(uplo),
                                            n,
                                            A,
                                            lda,
                                            D,
                                            E,
                                            tau,
                                            work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverChetrd(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  hipFloatComplex*    A,
                                  int                 lda,
                                  float*              D,
                                  float*              E,
                                  hipFloatComplex*    tau,
                                  hipFloatComplex*    work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnChetrd((cusolverDnHandle_t)handle,
                                            hip2cuda_fill(uplo),
                                            n,
                                            (cuComplex*)A,
                                            lda,
                                            D,
                                            E,
                                            (cuComplex*)tau,
                                            (cuComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZhetrd(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  hipDoubleComplex*   A,
                                  int                 lda,
                                  double*             D,
                                  double*             E,
                                  hipDoubleComplex*   tau,
                                  hipDoubleComplex*   work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    return cuda2hip_status(cusolverDnZhetrd((cusolverDnHandle_t)handle,
                                            hip2cuda_fill(uplo),
                                            n,
                                            (cuDoubleComplex*)A,
                                            lda,
                                            D,
                                            E,
                                            (cuDoubleComplex*)tau,
                                            (cuDoubleComplex*)work,
                                            lwork,
                                            devInfo));
}
catch(...)
{
    return exception2hip_status();
}

} // extern C
