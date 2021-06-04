/* ************************************************************************
 * Copyright 2020-2021 Advanced Micro Devices, Inc.
 * ************************************************************************ */

#include "hipsolver.h"
#include "exceptions.hpp"
#include "internal/rocblas_device_malloc.hpp"
#include "rocblas.h"
#include "rocsolver.h"
#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <math.h>

using namespace std;

extern "C" {

/******************** HELPERS ********************/
rocblas_operation_ hip2rocblas_operation(hipsolverOperation_t op)
{
    switch(op)
    {
    case HIPSOLVER_OP_N:
        return rocblas_operation_none;
    case HIPSOLVER_OP_T:
        return rocblas_operation_transpose;
    case HIPSOLVER_OP_C:
        return rocblas_operation_conjugate_transpose;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

hipsolverOperation_t rocblas2hip_operation(rocblas_operation_ op)
{
    switch(op)
    {
    case rocblas_operation_none:
        return HIPSOLVER_OP_N;
    case rocblas_operation_transpose:
        return HIPSOLVER_OP_T;
    case rocblas_operation_conjugate_transpose:
        return HIPSOLVER_OP_C;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

rocblas_fill_ hip2rocblas_fill(hipsolverFillMode_t fill)
{
    switch(fill)
    {
    case HIPSOLVER_FILL_MODE_UPPER:
        return rocblas_fill_upper;
    case HIPSOLVER_FILL_MODE_LOWER:
        return rocblas_fill_lower;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

hipsolverFillMode_t rocblas2hip_fill(rocblas_fill_ fill)
{
    switch(fill)
    {
    case rocblas_fill_upper:
        return HIPSOLVER_FILL_MODE_UPPER;
    case rocblas_fill_lower:
        return HIPSOLVER_FILL_MODE_LOWER;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

rocblas_side_ hip2rocblas_side(hipsolverSideMode_t side)
{
    switch(side)
    {
    case HIPSOLVER_SIDE_LEFT:
        return rocblas_side_left;
    case HIPSOLVER_SIDE_RIGHT:
        return rocblas_side_right;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

hipsolverSideMode_t rocblas2hip_side(rocblas_side_ side)
{
    switch(side)
    {
    case rocblas_side_left:
        return HIPSOLVER_SIDE_LEFT;
    case rocblas_side_right:
        return HIPSOLVER_SIDE_RIGHT;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

rocblas_evect_ hip2rocblas_evect(hipsolverEigMode_t eig)
{
    switch(eig)
    {
    case HIPSOLVER_EIG_MODE_NOVECTOR:
        return rocblas_evect_none;
    case HIPSOLVER_EIG_MODE_VECTOR:
        return rocblas_evect_original;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

hipsolverEigMode_t rocblas2hip_evect(rocblas_evect_ eig)
{
    switch(eig)
    {
    case rocblas_evect_none:
        return HIPSOLVER_EIG_MODE_NOVECTOR;
    case rocblas_evect_original:
        return HIPSOLVER_EIG_MODE_VECTOR;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

rocblas_eform_ hip2rocblas_eform(hipsolverEigType_t eig)
{
    switch(eig)
    {
    case HIPSOLVER_EIG_TYPE_1:
        return rocblas_eform_ax;
    case HIPSOLVER_EIG_TYPE_2:
        return rocblas_eform_abx;
    case HIPSOLVER_EIG_TYPE_3:
        return rocblas_eform_bax;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

hipsolverEigType_t rocblas2hip_eform(rocblas_eform_ eig)
{
    switch(eig)
    {
    case rocblas_eform_ax:
        return HIPSOLVER_EIG_TYPE_1;
    case rocblas_eform_abx:
        return HIPSOLVER_EIG_TYPE_2;
    case rocblas_eform_bax:
        return HIPSOLVER_EIG_TYPE_3;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

rocblas_storev_ hip2rocblas_side2storev(hipsolverSideMode_t side)
{
    switch(side)
    {
    case HIPSOLVER_SIDE_LEFT:
        return rocblas_column_wise;
    case HIPSOLVER_SIDE_RIGHT:
        return rocblas_row_wise;
    default:
        throw HIPSOLVER_STATUS_INVALID_ENUM;
    }
}

rocblas_svect_ char2rocblas_svect(signed char svect)
{
    switch(svect)
    {
    case 'N':
        return rocblas_svect_none;
    case 'A':
        return rocblas_svect_all;
    case 'S':
        return rocblas_svect_singular;
    case 'O':
        return rocblas_svect_overwrite;
    default:
        throw HIPSOLVER_STATUS_INVALID_VALUE;
    }
}

hipsolverStatus_t rocblas2hip_status(rocblas_status_ error)
{
    switch(error)
    {
    case rocblas_status_size_unchanged:
    case rocblas_status_size_increased:
    case rocblas_status_success:
        return HIPSOLVER_STATUS_SUCCESS;
    case rocblas_status_invalid_handle:
        return HIPSOLVER_STATUS_NOT_INITIALIZED;
    case rocblas_status_not_implemented:
        return HIPSOLVER_STATUS_NOT_SUPPORTED;
    case rocblas_status_invalid_pointer:
    case rocblas_status_invalid_size:
    case rocblas_status_invalid_value:
        return HIPSOLVER_STATUS_INVALID_VALUE;
    case rocblas_status_memory_error:
        return HIPSOLVER_STATUS_ALLOC_FAILED;
    case rocblas_status_internal_error:
        return HIPSOLVER_STATUS_INTERNAL_ERROR;
    default:
        return HIPSOLVER_STATUS_UNKNOWN;
    }
}

#define CHECK_ROCBLAS_ERROR(STATUS)             \
    do                                          \
    {                                           \
        rocblas_status _status = (STATUS);      \
        if(_status != rocblas_status_success)   \
            return rocblas2hip_status(_status); \
    } while(0)

inline rocblas_status hipsolverManageWorkspace(rocblas_handle handle, int lwork)
{
    size_t current_size;
    if(rocblas_is_user_managing_device_memory(handle))
        rocblas_get_device_memory_size(handle, &current_size);

    if(lwork > current_size)
        return rocblas_set_device_memory_size(handle, lwork);
    else
        return rocblas_status_success;
}

/******************** AUXLIARY ********************/
hipsolverStatus_t hipsolverCreate(hipsolverHandle_t* handle)
try
{
    if(!handle)
        return HIPSOLVER_STATUS_HANDLE_IS_NULLPTR;

    // Create the rocBLAS handle
    return rocblas2hip_status(rocblas_create_handle((rocblas_handle*)handle));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDestroy(hipsolverHandle_t handle)
try
{
    return rocblas2hip_status(rocblas_destroy_handle((rocblas_handle)handle));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverSetStream(hipsolverHandle_t handle, hipStream_t streamId)
try
{
    if(!handle)
        return HIPSOLVER_STATUS_NOT_INITIALIZED;

    return rocblas2hip_status(rocblas_set_stream((rocblas_handle)handle, streamId));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverGetStream(hipsolverHandle_t handle, hipStream_t* streamId)
try
{
    if(!handle)
        return HIPSOLVER_STATUS_NOT_INITIALIZED;

    return rocblas2hip_status(rocblas_get_stream((rocblas_handle)handle, streamId));
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_sorgbr(
        (rocblas_handle)handle, hip2rocblas_side2storev(side), m, n, k, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_dorgbr(
        (rocblas_handle)handle, hip2rocblas_side2storev(side), m, n, k, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
                                             hipsolverComplex*   A,
                                             int                 lda,
                                             hipsolverComplex*   tau,
                                             int*                lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_cungbr(
        (rocblas_handle)handle, hip2rocblas_side2storev(side), m, n, k, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZungbr_bufferSize(hipsolverHandle_t       handle,
                                             hipsolverSideMode_t     side,
                                             int                     m,
                                             int                     n,
                                             int                     k,
                                             hipsolverDoubleComplex* A,
                                             int                     lda,
                                             hipsolverDoubleComplex* tau,
                                             int*                    lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_zungbr(
        (rocblas_handle)handle, hip2rocblas_side2storev(side), m, n, k, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverSorgbr_bufferSize((rocblas_handle)handle, side, m, n, k, A, lda, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_sorgbr(
        (rocblas_handle)handle, hip2rocblas_side2storev(side), m, n, k, A, lda, tau));
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverDorgbr_bufferSize((rocblas_handle)handle, side, m, n, k, A, lda, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_dorgbr(
        (rocblas_handle)handle, hip2rocblas_side2storev(side), m, n, k, A, lda, tau));
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
                                  hipsolverComplex*   A,
                                  int                 lda,
                                  hipsolverComplex*   tau,
                                  hipsolverComplex*   work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverCungbr_bufferSize((rocblas_handle)handle, side, m, n, k, A, lda, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_cungbr((rocblas_handle)handle,
                                               hip2rocblas_side2storev(side),
                                               m,
                                               n,
                                               k,
                                               (rocblas_float_complex*)A,
                                               lda,
                                               (rocblas_float_complex*)tau));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZungbr(hipsolverHandle_t       handle,
                                  hipsolverSideMode_t     side,
                                  int                     m,
                                  int                     n,
                                  int                     k,
                                  hipsolverDoubleComplex* A,
                                  int                     lda,
                                  hipsolverDoubleComplex* tau,
                                  hipsolverDoubleComplex* work,
                                  int                     lwork,
                                  int*                    devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverZungbr_bufferSize((rocblas_handle)handle, side, m, n, k, A, lda, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_zungbr((rocblas_handle)handle,
                                               hip2rocblas_side2storev(side),
                                               m,
                                               n,
                                               k,
                                               (rocblas_double_complex*)A,
                                               lda,
                                               (rocblas_double_complex*)tau));
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status
        = rocsolver_sorgqr((rocblas_handle)handle, m, n, k, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDorgqr_bufferSize(
    hipsolverHandle_t handle, int m, int n, int k, double* A, int lda, double* tau, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status
        = rocsolver_dorgqr((rocblas_handle)handle, m, n, k, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCungqr_bufferSize(hipsolverHandle_t handle,
                                             int               m,
                                             int               n,
                                             int               k,
                                             hipsolverComplex* A,
                                             int               lda,
                                             hipsolverComplex* tau,
                                             int*              lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status
        = rocsolver_cungqr((rocblas_handle)handle, m, n, k, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZungqr_bufferSize(hipsolverHandle_t       handle,
                                             int                     m,
                                             int                     n,
                                             int                     k,
                                             hipsolverDoubleComplex* A,
                                             int                     lda,
                                             hipsolverDoubleComplex* tau,
                                             int*                    lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status
        = rocsolver_zungqr((rocblas_handle)handle, m, n, k, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverSorgqr_bufferSize((rocblas_handle)handle, m, n, k, A, lda, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_sorgqr((rocblas_handle)handle, m, n, k, A, lda, tau));
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverDorgqr_bufferSize((rocblas_handle)handle, m, n, k, A, lda, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_dorgqr((rocblas_handle)handle, m, n, k, A, lda, tau));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCungqr(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  int               k,
                                  hipsolverComplex* A,
                                  int               lda,
                                  hipsolverComplex* tau,
                                  hipsolverComplex* work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverCungqr_bufferSize((rocblas_handle)handle, m, n, k, A, lda, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_cungqr((rocblas_handle)handle,
                                               m,
                                               n,
                                               k,
                                               (rocblas_float_complex*)A,
                                               lda,
                                               (rocblas_float_complex*)tau));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZungqr(hipsolverHandle_t       handle,
                                  int                     m,
                                  int                     n,
                                  int                     k,
                                  hipsolverDoubleComplex* A,
                                  int                     lda,
                                  hipsolverDoubleComplex* tau,
                                  hipsolverDoubleComplex* work,
                                  int                     lwork,
                                  int*                    devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverZungqr_bufferSize((rocblas_handle)handle, m, n, k, A, lda, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_zungqr((rocblas_handle)handle,
                                               m,
                                               n,
                                               k,
                                               (rocblas_double_complex*)A,
                                               lda,
                                               (rocblas_double_complex*)tau));
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_sorgtr(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_dorgtr(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCungtr_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             hipsolverComplex*   A,
                                             int                 lda,
                                             hipsolverComplex*   tau,
                                             int*                lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_cungtr(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZungtr_bufferSize(hipsolverHandle_t       handle,
                                             hipsolverFillMode_t     uplo,
                                             int                     n,
                                             hipsolverDoubleComplex* A,
                                             int                     lda,
                                             hipsolverDoubleComplex* tau,
                                             int*                    lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_zungtr(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverSorgtr_bufferSize((rocblas_handle)handle, uplo, n, A, lda, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(
        rocsolver_sorgtr((rocblas_handle)handle, hip2rocblas_fill(uplo), n, A, lda, tau));
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverDorgtr_bufferSize((rocblas_handle)handle, uplo, n, A, lda, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(
        rocsolver_dorgtr((rocblas_handle)handle, hip2rocblas_fill(uplo), n, A, lda, tau));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCungtr(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  hipsolverComplex*   A,
                                  int                 lda,
                                  hipsolverComplex*   tau,
                                  hipsolverComplex*   work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverCungtr_bufferSize((rocblas_handle)handle, uplo, n, A, lda, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_cungtr((rocblas_handle)handle,
                                               hip2rocblas_fill(uplo),
                                               n,
                                               (rocblas_float_complex*)A,
                                               lda,
                                               (rocblas_float_complex*)tau));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZungtr(hipsolverHandle_t       handle,
                                  hipsolverFillMode_t     uplo,
                                  int                     n,
                                  hipsolverDoubleComplex* A,
                                  int                     lda,
                                  hipsolverDoubleComplex* tau,
                                  hipsolverDoubleComplex* work,
                                  int                     lwork,
                                  int*                    devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverZungtr_bufferSize((rocblas_handle)handle, uplo, n, A, lda, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_zungtr((rocblas_handle)handle,
                                               hip2rocblas_fill(uplo),
                                               n,
                                               (rocblas_double_complex*)A,
                                               lda,
                                               (rocblas_double_complex*)tau));
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_sormqr((rocblas_handle)handle,
                                             hip2rocblas_side(side),
                                             hip2rocblas_operation(trans),
                                             m,
                                             n,
                                             k,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             ldc);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_dormqr((rocblas_handle)handle,
                                             hip2rocblas_side(side),
                                             hip2rocblas_operation(trans),
                                             m,
                                             n,
                                             k,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             ldc);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
                                             hipsolverComplex*    A,
                                             int                  lda,
                                             hipsolverComplex*    tau,
                                             hipsolverComplex*    C,
                                             int                  ldc,
                                             int*                 lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_cunmqr((rocblas_handle)handle,
                                             hip2rocblas_side(side),
                                             hip2rocblas_operation(trans),
                                             m,
                                             n,
                                             k,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             ldc);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZunmqr_bufferSize(hipsolverHandle_t       handle,
                                             hipsolverSideMode_t     side,
                                             hipsolverOperation_t    trans,
                                             int                     m,
                                             int                     n,
                                             int                     k,
                                             hipsolverDoubleComplex* A,
                                             int                     lda,
                                             hipsolverDoubleComplex* tau,
                                             hipsolverDoubleComplex* C,
                                             int                     ldc,
                                             int*                    lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_zunmqr((rocblas_handle)handle,
                                             hip2rocblas_side(side),
                                             hip2rocblas_operation(trans),
                                             m,
                                             n,
                                             k,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             ldc);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverSormqr_bufferSize(
            (rocblas_handle)handle, side, trans, m, n, k, A, lda, tau, C, ldc, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_sormqr((rocblas_handle)handle,
                                               hip2rocblas_side(side),
                                               hip2rocblas_operation(trans),
                                               m,
                                               n,
                                               k,
                                               A,
                                               lda,
                                               tau,
                                               C,
                                               ldc));
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverDormqr_bufferSize(
            (rocblas_handle)handle, side, trans, m, n, k, A, lda, tau, C, ldc, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_dormqr((rocblas_handle)handle,
                                               hip2rocblas_side(side),
                                               hip2rocblas_operation(trans),
                                               m,
                                               n,
                                               k,
                                               A,
                                               lda,
                                               tau,
                                               C,
                                               ldc));
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
                                  hipsolverComplex*    A,
                                  int                  lda,
                                  hipsolverComplex*    tau,
                                  hipsolverComplex*    C,
                                  int                  ldc,
                                  hipsolverComplex*    work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverCunmqr_bufferSize(
            (rocblas_handle)handle, side, trans, m, n, k, A, lda, tau, C, ldc, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_cunmqr((rocblas_handle)handle,
                                               hip2rocblas_side(side),
                                               hip2rocblas_operation(trans),
                                               m,
                                               n,
                                               k,
                                               (rocblas_float_complex*)A,
                                               lda,
                                               (rocblas_float_complex*)tau,
                                               (rocblas_float_complex*)C,
                                               ldc));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZunmqr(hipsolverHandle_t       handle,
                                  hipsolverSideMode_t     side,
                                  hipsolverOperation_t    trans,
                                  int                     m,
                                  int                     n,
                                  int                     k,
                                  hipsolverDoubleComplex* A,
                                  int                     lda,
                                  hipsolverDoubleComplex* tau,
                                  hipsolverDoubleComplex* C,
                                  int                     ldc,
                                  hipsolverDoubleComplex* work,
                                  int                     lwork,
                                  int*                    devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverZunmqr_bufferSize(
            (rocblas_handle)handle, side, trans, m, n, k, A, lda, tau, C, ldc, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_zunmqr((rocblas_handle)handle,
                                               hip2rocblas_side(side),
                                               hip2rocblas_operation(trans),
                                               m,
                                               n,
                                               k,
                                               (rocblas_double_complex*)A,
                                               lda,
                                               (rocblas_double_complex*)tau,
                                               (rocblas_double_complex*)C,
                                               ldc));
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_sormtr((rocblas_handle)handle,
                                             hip2rocblas_side(side),
                                             hip2rocblas_fill(uplo),
                                             hip2rocblas_operation(trans),
                                             m,
                                             n,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             ldc);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_dormtr((rocblas_handle)handle,
                                             hip2rocblas_side(side),
                                             hip2rocblas_fill(uplo),
                                             hip2rocblas_operation(trans),
                                             m,
                                             n,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             ldc);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
                                             hipsolverComplex*    A,
                                             int                  lda,
                                             hipsolverComplex*    tau,
                                             hipsolverComplex*    C,
                                             int                  ldc,
                                             int*                 lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_cunmtr((rocblas_handle)handle,
                                             hip2rocblas_side(side),
                                             hip2rocblas_fill(uplo),
                                             hip2rocblas_operation(trans),
                                             m,
                                             n,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             ldc);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZunmtr_bufferSize(hipsolverHandle_t       handle,
                                             hipsolverSideMode_t     side,
                                             hipsolverFillMode_t     uplo,
                                             hipsolverOperation_t    trans,
                                             int                     m,
                                             int                     n,
                                             hipsolverDoubleComplex* A,
                                             int                     lda,
                                             hipsolverDoubleComplex* tau,
                                             hipsolverDoubleComplex* C,
                                             int                     ldc,
                                             int*                    lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_zunmtr((rocblas_handle)handle,
                                             hip2rocblas_side(side),
                                             hip2rocblas_fill(uplo),
                                             hip2rocblas_operation(trans),
                                             m,
                                             n,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             ldc);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverSormtr_bufferSize(
            (rocblas_handle)handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_sormtr((rocblas_handle)handle,
                                               hip2rocblas_side(side),
                                               hip2rocblas_fill(uplo),
                                               hip2rocblas_operation(trans),
                                               m,
                                               n,
                                               A,
                                               lda,
                                               tau,
                                               C,
                                               ldc));
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverDormtr_bufferSize(
            (rocblas_handle)handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_dormtr((rocblas_handle)handle,
                                               hip2rocblas_side(side),
                                               hip2rocblas_fill(uplo),
                                               hip2rocblas_operation(trans),
                                               m,
                                               n,
                                               A,
                                               lda,
                                               tau,
                                               C,
                                               ldc));
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
                                  hipsolverComplex*    A,
                                  int                  lda,
                                  hipsolverComplex*    tau,
                                  hipsolverComplex*    C,
                                  int                  ldc,
                                  hipsolverComplex*    work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverCunmtr_bufferSize(
            (rocblas_handle)handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_cunmtr((rocblas_handle)handle,
                                               hip2rocblas_side(side),
                                               hip2rocblas_fill(uplo),
                                               hip2rocblas_operation(trans),
                                               m,
                                               n,
                                               (rocblas_float_complex*)A,
                                               lda,
                                               (rocblas_float_complex*)tau,
                                               (rocblas_float_complex*)C,
                                               ldc));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZunmtr(hipsolverHandle_t       handle,
                                  hipsolverSideMode_t     side,
                                  hipsolverFillMode_t     uplo,
                                  hipsolverOperation_t    trans,
                                  int                     m,
                                  int                     n,
                                  hipsolverDoubleComplex* A,
                                  int                     lda,
                                  hipsolverDoubleComplex* tau,
                                  hipsolverDoubleComplex* C,
                                  int                     ldc,
                                  hipsolverDoubleComplex* work,
                                  int                     lwork,
                                  int*                    devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverZunmtr_bufferSize(
            (rocblas_handle)handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_zunmtr((rocblas_handle)handle,
                                               hip2rocblas_side(side),
                                               hip2rocblas_fill(uplo),
                                               hip2rocblas_operation(trans),
                                               m,
                                               n,
                                               (rocblas_double_complex*)A,
                                               lda,
                                               (rocblas_double_complex*)tau,
                                               (rocblas_double_complex*)C,
                                               ldc));
}
catch(...)
{
    return exception2hip_status();
}

/******************** GEBRD ********************/
hipsolverStatus_t hipsolverSgebrd_bufferSize(hipsolverHandle_t handle, int m, int n, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_sgebrd(
        (rocblas_handle)handle, m, n, nullptr, m, nullptr, nullptr, nullptr, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDgebrd_bufferSize(hipsolverHandle_t handle, int m, int n, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_dgebrd(
        (rocblas_handle)handle, m, n, nullptr, m, nullptr, nullptr, nullptr, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgebrd_bufferSize(hipsolverHandle_t handle, int m, int n, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_cgebrd(
        (rocblas_handle)handle, m, n, nullptr, m, nullptr, nullptr, nullptr, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgebrd_bufferSize(hipsolverHandle_t handle, int m, int n, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_zgebrd(
        (rocblas_handle)handle, m, n, nullptr, m, nullptr, nullptr, nullptr, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverSgebrd_bufferSize((rocblas_handle)handle, m, n, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(
        rocsolver_sgebrd((rocblas_handle)handle, m, n, A, lda, D, E, tauq, taup));
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverDgebrd_bufferSize((rocblas_handle)handle, m, n, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(
        rocsolver_dgebrd((rocblas_handle)handle, m, n, A, lda, D, E, tauq, taup));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgebrd(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  hipsolverComplex* A,
                                  int               lda,
                                  float*            D,
                                  float*            E,
                                  hipsolverComplex* tauq,
                                  hipsolverComplex* taup,
                                  hipsolverComplex* work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverCgebrd_bufferSize((rocblas_handle)handle, m, n, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_cgebrd((rocblas_handle)handle,
                                               m,
                                               n,
                                               (rocblas_float_complex*)A,
                                               lda,
                                               D,
                                               E,
                                               (rocblas_float_complex*)tauq,
                                               (rocblas_float_complex*)taup));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgebrd(hipsolverHandle_t       handle,
                                  int                     m,
                                  int                     n,
                                  hipsolverDoubleComplex* A,
                                  int                     lda,
                                  double*                 D,
                                  double*                 E,
                                  hipsolverDoubleComplex* tauq,
                                  hipsolverDoubleComplex* taup,
                                  hipsolverDoubleComplex* work,
                                  int                     lwork,
                                  int*                    devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverZgebrd_bufferSize((rocblas_handle)handle, m, n, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_zgebrd((rocblas_handle)handle,
                                               m,
                                               n,
                                               (rocblas_double_complex*)A,
                                               lda,
                                               D,
                                               E,
                                               (rocblas_double_complex*)tauq,
                                               (rocblas_double_complex*)taup));
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_sgeqrf((rocblas_handle)handle, m, n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDgeqrf_bufferSize(
    hipsolverHandle_t handle, int m, int n, double* A, int lda, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_dgeqrf((rocblas_handle)handle, m, n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgeqrf_bufferSize(
    hipsolverHandle_t handle, int m, int n, hipsolverComplex* A, int lda, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_cgeqrf((rocblas_handle)handle, m, n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgeqrf_bufferSize(
    hipsolverHandle_t handle, int m, int n, hipsolverDoubleComplex* A, int lda, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_zgeqrf((rocblas_handle)handle, m, n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverSgeqrf_bufferSize((rocblas_handle)handle, m, n, A, lda, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_sgeqrf((rocblas_handle)handle, m, n, A, lda, tau));
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverDgeqrf_bufferSize((rocblas_handle)handle, m, n, A, lda, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_dgeqrf((rocblas_handle)handle, m, n, A, lda, tau));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgeqrf(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  hipsolverComplex* A,
                                  int               lda,
                                  hipsolverComplex* tau,
                                  hipsolverComplex* work,
                                  int               lwork,
                                  int*              devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverCgeqrf_bufferSize((rocblas_handle)handle, m, n, A, lda, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_cgeqrf(
        (rocblas_handle)handle, m, n, (rocblas_float_complex*)A, lda, (rocblas_float_complex*)tau));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgeqrf(hipsolverHandle_t       handle,
                                  int                     m,
                                  int                     n,
                                  hipsolverDoubleComplex* A,
                                  int                     lda,
                                  hipsolverDoubleComplex* tau,
                                  hipsolverDoubleComplex* work,
                                  int                     lwork,
                                  int*                    devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverZgeqrf_bufferSize((rocblas_handle)handle, m, n, A, lda, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_zgeqrf((rocblas_handle)handle,
                                               m,
                                               n,
                                               (rocblas_double_complex*)A,
                                               lda,
                                               (rocblas_double_complex*)tau));
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_sgesvd((rocblas_handle)handle,
                                             char2rocblas_svect(jobu),
                                             char2rocblas_svect(jobv),
                                             m,
                                             n,
                                             nullptr,
                                             m,
                                             nullptr,
                                             nullptr,
                                             m,
                                             nullptr,
                                             n,
                                             nullptr,
                                             rocblas_outofplace,
                                             nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDgesvd_bufferSize(
    hipsolverHandle_t handle, signed char jobu, signed char jobv, int m, int n, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_dgesvd((rocblas_handle)handle,
                                             char2rocblas_svect(jobu),
                                             char2rocblas_svect(jobv),
                                             m,
                                             n,
                                             nullptr,
                                             m,
                                             nullptr,
                                             nullptr,
                                             m,
                                             nullptr,
                                             n,
                                             nullptr,
                                             rocblas_outofplace,
                                             nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgesvd_bufferSize(
    hipsolverHandle_t handle, signed char jobu, signed char jobv, int m, int n, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_cgesvd((rocblas_handle)handle,
                                             char2rocblas_svect(jobu),
                                             char2rocblas_svect(jobv),
                                             m,
                                             n,
                                             nullptr,
                                             m,
                                             nullptr,
                                             nullptr,
                                             m,
                                             nullptr,
                                             n,
                                             nullptr,
                                             rocblas_outofplace,
                                             nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgesvd_bufferSize(
    hipsolverHandle_t handle, signed char jobu, signed char jobv, int m, int n, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_zgesvd((rocblas_handle)handle,
                                             char2rocblas_svect(jobu),
                                             char2rocblas_svect(jobv),
                                             m,
                                             n,
                                             nullptr,
                                             m,
                                             nullptr,
                                             nullptr,
                                             m,
                                             nullptr,
                                             n,
                                             nullptr,
                                             rocblas_outofplace,
                                             nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverSgesvd_bufferSize((rocblas_handle)handle, jobu, jobv, m, n, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_sgesvd((rocblas_handle)handle,
                                               char2rocblas_svect(jobu),
                                               char2rocblas_svect(jobv),
                                               m,
                                               n,
                                               A,
                                               lda,
                                               S,
                                               U,
                                               ldu,
                                               V,
                                               ldv,
                                               rwork,
                                               rocblas_outofplace,
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverDgesvd_bufferSize((rocblas_handle)handle, jobu, jobv, m, n, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_dgesvd((rocblas_handle)handle,
                                               char2rocblas_svect(jobu),
                                               char2rocblas_svect(jobv),
                                               m,
                                               n,
                                               A,
                                               lda,
                                               S,
                                               U,
                                               ldu,
                                               V,
                                               ldv,
                                               rwork,
                                               rocblas_outofplace,
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
                                  hipsolverComplex* A,
                                  int               lda,
                                  float*            S,
                                  hipsolverComplex* U,
                                  int               ldu,
                                  hipsolverComplex* V,
                                  int               ldv,
                                  hipsolverComplex* work,
                                  int               lwork,
                                  float*            rwork,
                                  int*              devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverCgesvd_bufferSize((rocblas_handle)handle, jobu, jobv, m, n, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_cgesvd((rocblas_handle)handle,
                                               char2rocblas_svect(jobu),
                                               char2rocblas_svect(jobv),
                                               m,
                                               n,
                                               (rocblas_float_complex*)A,
                                               lda,
                                               S,
                                               (rocblas_float_complex*)U,
                                               ldu,
                                               (rocblas_float_complex*)V,
                                               ldv,
                                               rwork,
                                               rocblas_outofplace,
                                               devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgesvd(hipsolverHandle_t       handle,
                                  signed char             jobu,
                                  signed char             jobv,
                                  int                     m,
                                  int                     n,
                                  hipsolverDoubleComplex* A,
                                  int                     lda,
                                  double*                 S,
                                  hipsolverDoubleComplex* U,
                                  int                     ldu,
                                  hipsolverDoubleComplex* V,
                                  int                     ldv,
                                  hipsolverDoubleComplex* work,
                                  int                     lwork,
                                  double*                 rwork,
                                  int*                    devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverZgesvd_bufferSize((rocblas_handle)handle, jobu, jobv, m, n, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_zgesvd((rocblas_handle)handle,
                                               char2rocblas_svect(jobu),
                                               char2rocblas_svect(jobv),
                                               m,
                                               n,
                                               (rocblas_double_complex*)A,
                                               lda,
                                               S,
                                               (rocblas_double_complex*)U,
                                               ldu,
                                               (rocblas_double_complex*)V,
                                               ldv,
                                               rwork,
                                               rocblas_outofplace,
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status
        = rocsolver_sgetrf((rocblas_handle)handle, m, n, nullptr, lda, nullptr, nullptr);
    rocsolver_sgetrf_npvt((rocblas_handle)handle, m, n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDgetrf_bufferSize(
    hipsolverHandle_t handle, int m, int n, double* A, int lda, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status
        = rocsolver_dgetrf((rocblas_handle)handle, m, n, nullptr, lda, nullptr, nullptr);
    rocsolver_dgetrf_npvt((rocblas_handle)handle, m, n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgetrf_bufferSize(
    hipsolverHandle_t handle, int m, int n, hipsolverComplex* A, int lda, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status
        = rocsolver_cgetrf((rocblas_handle)handle, m, n, nullptr, lda, nullptr, nullptr);
    rocsolver_cgetrf_npvt((rocblas_handle)handle, m, n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgetrf_bufferSize(
    hipsolverHandle_t handle, int m, int n, hipsolverDoubleComplex* A, int lda, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status
        = rocsolver_zgetrf((rocblas_handle)handle, m, n, nullptr, lda, nullptr, nullptr);
    rocsolver_zgetrf_npvt((rocblas_handle)handle, m, n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverSgetrf_bufferSize((rocblas_handle)handle, m, n, A, lda, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    if(devIpiv != nullptr)
        return rocblas2hip_status(
            rocsolver_sgetrf((rocblas_handle)handle, m, n, A, lda, devIpiv, devInfo));
    else
        return rocblas2hip_status(
            rocsolver_sgetrf_npvt((rocblas_handle)handle, m, n, A, lda, devInfo));
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverDgetrf_bufferSize((rocblas_handle)handle, m, n, A, lda, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    if(devIpiv != nullptr)
        return rocblas2hip_status(
            rocsolver_dgetrf((rocblas_handle)handle, m, n, A, lda, devIpiv, devInfo));
    else
        return rocblas2hip_status(
            rocsolver_dgetrf_npvt((rocblas_handle)handle, m, n, A, lda, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgetrf(hipsolverHandle_t handle,
                                  int               m,
                                  int               n,
                                  hipsolverComplex* A,
                                  int               lda,
                                  hipsolverComplex* work,
                                  int               lwork,
                                  int*              devIpiv,
                                  int*              devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverCgetrf_bufferSize((rocblas_handle)handle, m, n, A, lda, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    if(devIpiv != nullptr)
        return rocblas2hip_status(rocsolver_cgetrf(
            (rocblas_handle)handle, m, n, (rocblas_float_complex*)A, lda, devIpiv, devInfo));
    else
        return rocblas2hip_status(rocsolver_cgetrf_npvt(
            (rocblas_handle)handle, m, n, (rocblas_float_complex*)A, lda, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgetrf(hipsolverHandle_t       handle,
                                  int                     m,
                                  int                     n,
                                  hipsolverDoubleComplex* A,
                                  int                     lda,
                                  hipsolverDoubleComplex* work,
                                  int                     lwork,
                                  int*                    devIpiv,
                                  int*                    devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverZgetrf_bufferSize((rocblas_handle)handle, m, n, A, lda, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    if(devIpiv != nullptr)
        return rocblas2hip_status(rocsolver_zgetrf(
            (rocblas_handle)handle, m, n, (rocblas_double_complex*)A, lda, devIpiv, devInfo));
    else
        return rocblas2hip_status(rocsolver_zgetrf_npvt(
            (rocblas_handle)handle, m, n, (rocblas_double_complex*)A, lda, devInfo));
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_sgetrs((rocblas_handle)handle,
                                             hip2rocblas_operation(trans),
                                             n,
                                             nrhs,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             ldb);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_dgetrs((rocblas_handle)handle,
                                             hip2rocblas_operation(trans),
                                             n,
                                             nrhs,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             ldb);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgetrs_bufferSize(hipsolverHandle_t    handle,
                                             hipsolverOperation_t trans,
                                             int                  n,
                                             int                  nrhs,
                                             hipsolverComplex*    A,
                                             int                  lda,
                                             int*                 devIpiv,
                                             hipsolverComplex*    B,
                                             int                  ldb,
                                             int*                 lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_cgetrs((rocblas_handle)handle,
                                             hip2rocblas_operation(trans),
                                             n,
                                             nrhs,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             ldb);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgetrs_bufferSize(hipsolverHandle_t       handle,
                                             hipsolverOperation_t    trans,
                                             int                     n,
                                             int                     nrhs,
                                             hipsolverDoubleComplex* A,
                                             int                     lda,
                                             int*                    devIpiv,
                                             hipsolverDoubleComplex* B,
                                             int                     ldb,
                                             int*                    lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_zgetrs((rocblas_handle)handle,
                                             hip2rocblas_operation(trans),
                                             n,
                                             nrhs,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             ldb);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverSgetrs_bufferSize(
            (rocblas_handle)handle, trans, n, nrhs, A, lda, devIpiv, B, ldb, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_sgetrs(
        (rocblas_handle)handle, hip2rocblas_operation(trans), n, nrhs, A, lda, devIpiv, B, ldb));
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverDgetrs_bufferSize(
            (rocblas_handle)handle, trans, n, nrhs, A, lda, devIpiv, B, ldb, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_dgetrs(
        (rocblas_handle)handle, hip2rocblas_operation(trans), n, nrhs, A, lda, devIpiv, B, ldb));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCgetrs(hipsolverHandle_t    handle,
                                  hipsolverOperation_t trans,
                                  int                  n,
                                  int                  nrhs,
                                  hipsolverComplex*    A,
                                  int                  lda,
                                  int*                 devIpiv,
                                  hipsolverComplex*    B,
                                  int                  ldb,
                                  hipsolverComplex*    work,
                                  int                  lwork,
                                  int*                 devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverCgetrs_bufferSize(
            (rocblas_handle)handle, trans, n, nrhs, A, lda, devIpiv, B, ldb, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_cgetrs((rocblas_handle)handle,
                                               hip2rocblas_operation(trans),
                                               n,
                                               nrhs,
                                               (rocblas_float_complex*)A,
                                               lda,
                                               devIpiv,
                                               (rocblas_float_complex*)B,
                                               ldb));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZgetrs(hipsolverHandle_t       handle,
                                  hipsolverOperation_t    trans,
                                  int                     n,
                                  int                     nrhs,
                                  hipsolverDoubleComplex* A,
                                  int                     lda,
                                  int*                    devIpiv,
                                  hipsolverDoubleComplex* B,
                                  int                     ldb,
                                  hipsolverDoubleComplex* work,
                                  int                     lwork,
                                  int*                    devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverZgetrs_bufferSize(
            (rocblas_handle)handle, trans, n, nrhs, A, lda, devIpiv, B, ldb, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_zgetrs((rocblas_handle)handle,
                                               hip2rocblas_operation(trans),
                                               n,
                                               nrhs,
                                               (rocblas_double_complex*)A,
                                               lda,
                                               devIpiv,
                                               (rocblas_double_complex*)B,
                                               ldb));
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_spotrf(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverDpotrf_bufferSize(
    hipsolverHandle_t handle, hipsolverFillMode_t uplo, int n, double* A, int lda, int* lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_dpotrf(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCpotrf_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             hipsolverComplex*   A,
                                             int                 lda,
                                             int*                lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_cpotrf(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZpotrf_bufferSize(hipsolverHandle_t       handle,
                                             hipsolverFillMode_t     uplo,
                                             int                     n,
                                             hipsolverDoubleComplex* A,
                                             int                     lda,
                                             int*                    lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_zpotrf(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverSpotrf_bufferSize((rocblas_handle)handle, uplo, n, A, lda, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(
        rocsolver_spotrf((rocblas_handle)handle, hip2rocblas_fill(uplo), n, A, lda, devInfo));
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverDpotrf_bufferSize((rocblas_handle)handle, uplo, n, A, lda, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(
        rocsolver_dpotrf((rocblas_handle)handle, hip2rocblas_fill(uplo), n, A, lda, devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCpotrf(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  hipsolverComplex*   A,
                                  int                 lda,
                                  hipsolverComplex*   work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverCpotrf_bufferSize((rocblas_handle)handle, uplo, n, A, lda, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_cpotrf((rocblas_handle)handle,
                                               hip2rocblas_fill(uplo),
                                               n,
                                               (rocblas_float_complex*)A,
                                               lda,
                                               devInfo));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZpotrf(hipsolverHandle_t       handle,
                                  hipsolverFillMode_t     uplo,
                                  int                     n,
                                  hipsolverDoubleComplex* A,
                                  int                     lda,
                                  hipsolverDoubleComplex* work,
                                  int                     lwork,
                                  int*                    devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverZpotrf_bufferSize((rocblas_handle)handle, uplo, n, A, lda, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_zpotrf((rocblas_handle)handle,
                                               hip2rocblas_fill(uplo),
                                               n,
                                               (rocblas_double_complex*)A,
                                               lda,
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_spotrf_batched(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr, batch_count);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_dpotrf_batched(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr, batch_count);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCpotrfBatched_bufferSize(hipsolverHandle_t   handle,
                                                    hipsolverFillMode_t uplo,
                                                    int                 n,
                                                    hipsolverComplex*   A[],
                                                    int                 lda,
                                                    int*                lwork,
                                                    int                 batch_count)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_cpotrf_batched(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr, batch_count);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZpotrfBatched_bufferSize(hipsolverHandle_t       handle,
                                                    hipsolverFillMode_t     uplo,
                                                    int                     n,
                                                    hipsolverDoubleComplex* A[],
                                                    int                     lda,
                                                    int*                    lwork,
                                                    int                     batch_count)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_zpotrf_batched(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr, batch_count);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverSpotrfBatched_bufferSize(
            (rocblas_handle)handle, uplo, n, A, lda, &lwork, batch_count);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_spotrf_batched(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, A, lda, devInfo, batch_count));
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverDpotrfBatched_bufferSize(
            (rocblas_handle)handle, uplo, n, A, lda, &lwork, batch_count);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_dpotrf_batched(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, A, lda, devInfo, batch_count));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCpotrfBatched(hipsolverHandle_t   handle,
                                         hipsolverFillMode_t uplo,
                                         int                 n,
                                         hipsolverComplex*   A[],
                                         int                 lda,
                                         hipsolverComplex*   work,
                                         int                 lwork,
                                         int*                devInfo,
                                         int                 batch_count)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverCpotrfBatched_bufferSize(
            (rocblas_handle)handle, uplo, n, A, lda, &lwork, batch_count);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_cpotrf_batched((rocblas_handle)handle,
                                                       hip2rocblas_fill(uplo),
                                                       n,
                                                       (rocblas_float_complex**)A,
                                                       lda,
                                                       devInfo,
                                                       batch_count));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZpotrfBatched(hipsolverHandle_t       handle,
                                         hipsolverFillMode_t     uplo,
                                         int                     n,
                                         hipsolverDoubleComplex* A[],
                                         int                     lda,
                                         hipsolverDoubleComplex* work,
                                         int                     lwork,
                                         int*                    devInfo,
                                         int                     batch_count)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverZpotrfBatched_bufferSize(
            (rocblas_handle)handle, uplo, n, A, lda, &lwork, batch_count);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_zpotrf_batched((rocblas_handle)handle,
                                                       hip2rocblas_fill(uplo),
                                                       n,
                                                       (rocblas_double_complex**)A,
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_ssyevd((rocblas_handle)handle,
                                             hip2rocblas_evect(jobz),
                                             hip2rocblas_fill(uplo),
                                             n,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    // space for E array
    sz += sizeof(float) * n;

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_dsyevd((rocblas_handle)handle,
                                             hip2rocblas_evect(jobz),
                                             hip2rocblas_fill(uplo),
                                             n,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    // space for E array
    sz += sizeof(double) * n;

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCheevd_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverEigMode_t  jobz,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             hipsolverComplex*   A,
                                             int                 lda,
                                             float*              D,
                                             int*                lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_cheevd((rocblas_handle)handle,
                                             hip2rocblas_evect(jobz),
                                             hip2rocblas_fill(uplo),
                                             n,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    // space for E array
    sz += sizeof(float) * n;

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZheevd_bufferSize(hipsolverHandle_t       handle,
                                             hipsolverEigMode_t      jobz,
                                             hipsolverFillMode_t     uplo,
                                             int                     n,
                                             hipsolverDoubleComplex* A,
                                             int                     lda,
                                             double*                 D,
                                             int*                    lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_zheevd((rocblas_handle)handle,
                                             hip2rocblas_evect(jobz),
                                             hip2rocblas_fill(uplo),
                                             n,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             nullptr,
                                             nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    // space for E array
    sz += sizeof(double) * n;

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
    {
        float* E = work;
        work     = E + n;

        rocblas_set_workspace((rocblas_handle)handle, work, lwork);

        return rocblas2hip_status(rocsolver_ssyevd((rocblas_handle)handle,
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   A,
                                                   lda,
                                                   D,
                                                   E,
                                                   devInfo));
    }
    else
    {
        hipsolverSsyevd_bufferSize((rocblas_handle)handle, jobz, uplo, n, A, lda, D, &lwork);
        CHECK_ROCBLAS_ERROR(
            hipsolverManageWorkspace((rocblas_handle)handle, lwork + sizeof(float) * n));

        rocblas_device_malloc mem((rocblas_handle)handle, sizeof(float) * n);
        if(!mem)
            return HIPSOLVER_STATUS_ALLOC_FAILED;
        float* E = (float*)mem[0];

        return rocblas2hip_status(rocsolver_ssyevd((rocblas_handle)handle,
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   A,
                                                   lda,
                                                   D,
                                                   E,
                                                   devInfo));
    }
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
    if(work != nullptr)
    {
        double* E = work;
        work      = E + n;

        rocblas_set_workspace((rocblas_handle)handle, work, lwork);

        return rocblas2hip_status(rocsolver_dsyevd((rocblas_handle)handle,
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   A,
                                                   lda,
                                                   D,
                                                   E,
                                                   devInfo));
    }
    else
    {
        hipsolverDsyevd_bufferSize((rocblas_handle)handle, jobz, uplo, n, A, lda, D, &lwork);
        CHECK_ROCBLAS_ERROR(
            hipsolverManageWorkspace((rocblas_handle)handle, lwork + sizeof(double) * n));

        rocblas_device_malloc mem((rocblas_handle)handle, sizeof(double) * n);
        if(!mem)
            return HIPSOLVER_STATUS_ALLOC_FAILED;
        double* E = (double*)mem[0];

        return rocblas2hip_status(rocsolver_dsyevd((rocblas_handle)handle,
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   A,
                                                   lda,
                                                   D,
                                                   E,
                                                   devInfo));
    }
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverCheevd(hipsolverHandle_t   handle,
                                  hipsolverEigMode_t  jobz,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  hipsolverComplex*   A,
                                  int                 lda,
                                  float*              D,
                                  hipsolverComplex*   work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    if(work != nullptr)
    {
        float* E = (float*)work;
        work     = (hipsolverComplex*)(E + n);

        rocblas_set_workspace((rocblas_handle)handle, work, lwork);

        return rocblas2hip_status(rocsolver_cheevd((rocblas_handle)handle,
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   (rocblas_float_complex*)A,
                                                   lda,
                                                   D,
                                                   E,
                                                   devInfo));
    }
    else
    {
        hipsolverCheevd_bufferSize((rocblas_handle)handle, jobz, uplo, n, A, lda, D, &lwork);
        CHECK_ROCBLAS_ERROR(
            hipsolverManageWorkspace((rocblas_handle)handle, lwork + sizeof(float) * n));

        rocblas_device_malloc mem((rocblas_handle)handle, sizeof(float) * n);
        if(!mem)
            return HIPSOLVER_STATUS_ALLOC_FAILED;
        float* E = (float*)mem[0];

        return rocblas2hip_status(rocsolver_cheevd((rocblas_handle)handle,
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   (rocblas_float_complex*)A,
                                                   lda,
                                                   D,
                                                   E,
                                                   devInfo));
    }
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZheevd(hipsolverHandle_t       handle,
                                  hipsolverEigMode_t      jobz,
                                  hipsolverFillMode_t     uplo,
                                  int                     n,
                                  hipsolverDoubleComplex* A,
                                  int                     lda,
                                  double*                 D,
                                  hipsolverDoubleComplex* work,
                                  int                     lwork,
                                  int*                    devInfo)
try
{
    if(work != nullptr)
    {
        double* E = (double*)work;
        work      = (hipsolverDoubleComplex*)(E + n);

        rocblas_set_workspace((rocblas_handle)handle, work, lwork);

        return rocblas2hip_status(rocsolver_zheevd((rocblas_handle)handle,
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   (rocblas_double_complex*)A,
                                                   lda,
                                                   D,
                                                   E,
                                                   devInfo));
    }
    else
    {
        hipsolverZheevd_bufferSize((rocblas_handle)handle, jobz, uplo, n, A, lda, D, &lwork);
        CHECK_ROCBLAS_ERROR(
            hipsolverManageWorkspace((rocblas_handle)handle, lwork + sizeof(double) * n));

        rocblas_device_malloc mem((rocblas_handle)handle, sizeof(double) * n);
        if(!mem)
            return HIPSOLVER_STATUS_ALLOC_FAILED;
        double* E = (double*)mem[0];

        return rocblas2hip_status(rocsolver_zheevd((rocblas_handle)handle,
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   (rocblas_double_complex*)A,
                                                   lda,
                                                   D,
                                                   E,
                                                   devInfo));
    }
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_ssygvd((rocblas_handle)handle,
                                             hip2rocblas_eform(itype),
                                             hip2rocblas_evect(jobz),
                                             hip2rocblas_fill(uplo),
                                             n,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             ldb,
                                             nullptr,
                                             nullptr,
                                             nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    // space for E array
    sz += sizeof(float) * n;

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_dsygvd((rocblas_handle)handle,
                                             hip2rocblas_eform(itype),
                                             hip2rocblas_evect(jobz),
                                             hip2rocblas_fill(uplo),
                                             n,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             ldb,
                                             nullptr,
                                             nullptr,
                                             nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    // space for E array
    sz += sizeof(double) * n;

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
                                                              hipsolverComplex*   A,
                                                              int                 lda,
                                                              hipsolverComplex*   B,
                                                              int                 ldb,
                                                              float*              D,
                                                              int*                lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_chegvd((rocblas_handle)handle,
                                             hip2rocblas_eform(itype),
                                             hip2rocblas_evect(jobz),
                                             hip2rocblas_fill(uplo),
                                             n,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             ldb,
                                             nullptr,
                                             nullptr,
                                             nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    // space for E array
    sz += sizeof(float) * n;

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverZhegvd_bufferSize(hipsolverHandle_t       handle,
                                                              hipsolverEigType_t      itype,
                                                              hipsolverEigMode_t      jobz,
                                                              hipsolverFillMode_t     uplo,
                                                              int                     n,
                                                              hipsolverDoubleComplex* A,
                                                              int                     lda,
                                                              hipsolverDoubleComplex* B,
                                                              int                     ldb,
                                                              double*                 D,
                                                              int*                    lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_zhegvd((rocblas_handle)handle,
                                             hip2rocblas_eform(itype),
                                             hip2rocblas_evect(jobz),
                                             hip2rocblas_fill(uplo),
                                             n,
                                             nullptr,
                                             lda,
                                             nullptr,
                                             ldb,
                                             nullptr,
                                             nullptr,
                                             nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    // space for E array
    sz += sizeof(double) * n;

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
    {
        float* E = work;
        work     = E + n;

        rocblas_set_workspace((rocblas_handle)handle, work, lwork);

        return rocblas2hip_status(rocsolver_ssygvd((rocblas_handle)handle,
                                                   hip2rocblas_eform(itype),
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   A,
                                                   lda,
                                                   B,
                                                   ldb,
                                                   D,
                                                   E,
                                                   devInfo));
    }
    else
    {
        hipsolverSsygvd_bufferSize(
            (rocblas_handle)handle, itype, jobz, uplo, n, A, lda, B, ldb, D, &lwork);
        CHECK_ROCBLAS_ERROR(
            hipsolverManageWorkspace((rocblas_handle)handle, lwork + sizeof(float) * n));

        rocblas_device_malloc mem((rocblas_handle)handle, sizeof(float) * n);
        if(!mem)
            return HIPSOLVER_STATUS_ALLOC_FAILED;
        float* E = (float*)mem[0];

        return rocblas2hip_status(rocsolver_ssygvd((rocblas_handle)handle,
                                                   hip2rocblas_eform(itype),
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   A,
                                                   lda,
                                                   B,
                                                   ldb,
                                                   D,
                                                   E,
                                                   devInfo));
    }
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
    if(work != nullptr)
    {
        double* E = work;
        work      = E + n;

        rocblas_set_workspace((rocblas_handle)handle, work, lwork);

        return rocblas2hip_status(rocsolver_dsygvd((rocblas_handle)handle,
                                                   hip2rocblas_eform(itype),
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   A,
                                                   lda,
                                                   B,
                                                   ldb,
                                                   D,
                                                   E,
                                                   devInfo));
    }
    else
    {
        hipsolverDsygvd_bufferSize(
            (rocblas_handle)handle, itype, jobz, uplo, n, A, lda, B, ldb, D, &lwork);
        CHECK_ROCBLAS_ERROR(
            hipsolverManageWorkspace((rocblas_handle)handle, lwork + sizeof(double) * n));

        rocblas_device_malloc mem((rocblas_handle)handle, sizeof(double) * n);
        if(!mem)
            return HIPSOLVER_STATUS_ALLOC_FAILED;
        double* E = (double*)mem[0];

        return rocblas2hip_status(rocsolver_dsygvd((rocblas_handle)handle,
                                                   hip2rocblas_eform(itype),
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   A,
                                                   lda,
                                                   B,
                                                   ldb,
                                                   D,
                                                   E,
                                                   devInfo));
    }
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
                                                   hipsolverComplex*   A,
                                                   int                 lda,
                                                   hipsolverComplex*   B,
                                                   int                 ldb,
                                                   float*              D,
                                                   hipsolverComplex*   work,
                                                   int                 lwork,
                                                   int*                devInfo)
try
{
    if(work != nullptr)
    {
        float* E = (float*)work;
        work     = (hipsolverComplex*)(E + n);

        rocblas_set_workspace((rocblas_handle)handle, work, lwork);

        return rocblas2hip_status(rocsolver_chegvd((rocblas_handle)handle,
                                                   hip2rocblas_eform(itype),
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   (rocblas_float_complex*)A,
                                                   lda,
                                                   (rocblas_float_complex*)B,
                                                   ldb,
                                                   D,
                                                   E,
                                                   devInfo));
    }
    else
    {
        hipsolverChegvd_bufferSize(
            (rocblas_handle)handle, itype, jobz, uplo, n, A, lda, B, ldb, D, &lwork);
        CHECK_ROCBLAS_ERROR(
            hipsolverManageWorkspace((rocblas_handle)handle, lwork + sizeof(float) * n));

        rocblas_device_malloc mem((rocblas_handle)handle, sizeof(float) * n);
        if(!mem)
            return HIPSOLVER_STATUS_ALLOC_FAILED;
        float* E = (float*)mem[0];

        return rocblas2hip_status(rocsolver_chegvd((rocblas_handle)handle,
                                                   hip2rocblas_eform(itype),
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   (rocblas_float_complex*)A,
                                                   lda,
                                                   (rocblas_float_complex*)B,
                                                   ldb,
                                                   D,
                                                   E,
                                                   devInfo));
    }
}
catch(...)
{
    return exception2hip_status();
}

HIPSOLVER_EXPORT hipsolverStatus_t hipsolverZhegvd(hipsolverHandle_t       handle,
                                                   hipsolverEigType_t      itype,
                                                   hipsolverEigMode_t      jobz,
                                                   hipsolverFillMode_t     uplo,
                                                   int                     n,
                                                   hipsolverDoubleComplex* A,
                                                   int                     lda,
                                                   hipsolverDoubleComplex* B,
                                                   int                     ldb,
                                                   double*                 D,
                                                   hipsolverDoubleComplex* work,
                                                   int                     lwork,
                                                   int*                    devInfo)
try
{
    if(work != nullptr)
    {
        double* E = (double*)work;
        work      = (hipsolverDoubleComplex*)(E + n);

        rocblas_set_workspace((rocblas_handle)handle, work, lwork);

        return rocblas2hip_status(rocsolver_zhegvd((rocblas_handle)handle,
                                                   hip2rocblas_eform(itype),
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   (rocblas_double_complex*)A,
                                                   lda,
                                                   (rocblas_double_complex*)B,
                                                   ldb,
                                                   D,
                                                   E,
                                                   devInfo));
    }
    else
    {
        hipsolverZhegvd_bufferSize(
            (rocblas_handle)handle, itype, jobz, uplo, n, A, lda, B, ldb, D, &lwork);
        CHECK_ROCBLAS_ERROR(
            hipsolverManageWorkspace((rocblas_handle)handle, lwork + sizeof(double) * n));

        rocblas_device_malloc mem((rocblas_handle)handle, sizeof(double) * n);
        if(!mem)
            return HIPSOLVER_STATUS_ALLOC_FAILED;
        double* E = (double*)mem[0];

        return rocblas2hip_status(rocsolver_zhegvd((rocblas_handle)handle,
                                                   hip2rocblas_eform(itype),
                                                   hip2rocblas_evect(jobz),
                                                   hip2rocblas_fill(uplo),
                                                   n,
                                                   (rocblas_double_complex*)A,
                                                   lda,
                                                   (rocblas_double_complex*)B,
                                                   ldb,
                                                   D,
                                                   E,
                                                   devInfo));
    }
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_ssytrd(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr, nullptr, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_dsytrd(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr, nullptr, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverChetrd_bufferSize(hipsolverHandle_t   handle,
                                             hipsolverFillMode_t uplo,
                                             int                 n,
                                             hipsolverComplex*   A,
                                             int                 lda,
                                             float*              D,
                                             float*              E,
                                             hipsolverComplex*   tau,
                                             int*                lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_chetrd(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr, nullptr, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZhetrd_bufferSize(hipsolverHandle_t       handle,
                                             hipsolverFillMode_t     uplo,
                                             int                     n,
                                             hipsolverDoubleComplex* A,
                                             int                     lda,
                                             double*                 D,
                                             double*                 E,
                                             hipsolverDoubleComplex* tau,
                                             int*                    lwork)
try
{
    size_t sz;

    rocblas_start_device_memory_size_query((rocblas_handle)handle);
    rocblas_status status = rocsolver_zhetrd(
        (rocblas_handle)handle, hip2rocblas_fill(uplo), n, nullptr, lda, nullptr, nullptr, nullptr);
    rocblas_stop_device_memory_size_query((rocblas_handle)handle, &sz);

    if(sz > INT_MAX)
        return HIPSOLVER_STATUS_INTERNAL_ERROR;

    *lwork = (int)sz;
    return rocblas2hip_status(status);
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverSsytrd_bufferSize((rocblas_handle)handle, uplo, n, A, lda, D, E, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(
        rocsolver_ssytrd((rocblas_handle)handle, hip2rocblas_fill(uplo), n, A, lda, D, E, tau));
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
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverDsytrd_bufferSize((rocblas_handle)handle, uplo, n, A, lda, D, E, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(
        rocsolver_dsytrd((rocblas_handle)handle, hip2rocblas_fill(uplo), n, A, lda, D, E, tau));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverChetrd(hipsolverHandle_t   handle,
                                  hipsolverFillMode_t uplo,
                                  int                 n,
                                  hipsolverComplex*   A,
                                  int                 lda,
                                  float*              D,
                                  float*              E,
                                  hipsolverComplex*   tau,
                                  hipsolverComplex*   work,
                                  int                 lwork,
                                  int*                devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverChetrd_bufferSize((rocblas_handle)handle, uplo, n, A, lda, D, E, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_chetrd((rocblas_handle)handle,
                                               hip2rocblas_fill(uplo),
                                               n,
                                               (rocblas_float_complex*)A,
                                               lda,
                                               D,
                                               E,
                                               (rocblas_float_complex*)tau));
}
catch(...)
{
    return exception2hip_status();
}

hipsolverStatus_t hipsolverZhetrd(hipsolverHandle_t       handle,
                                  hipsolverFillMode_t     uplo,
                                  int                     n,
                                  hipsolverDoubleComplex* A,
                                  int                     lda,
                                  double*                 D,
                                  double*                 E,
                                  hipsolverDoubleComplex* tau,
                                  hipsolverDoubleComplex* work,
                                  int                     lwork,
                                  int*                    devInfo)
try
{
    if(work != nullptr)
        rocblas_set_workspace((rocblas_handle)handle, work, lwork);
    else
    {
        hipsolverZhetrd_bufferSize((rocblas_handle)handle, uplo, n, A, lda, D, E, tau, &lwork);
        CHECK_ROCBLAS_ERROR(hipsolverManageWorkspace((rocblas_handle)handle, lwork));
    }

    return rocblas2hip_status(rocsolver_zhetrd((rocblas_handle)handle,
                                               hip2rocblas_fill(uplo),
                                               n,
                                               (rocblas_double_complex*)A,
                                               lda,
                                               D,
                                               E,
                                               (rocblas_double_complex*)tau));
}
catch(...)
{
    return exception2hip_status();
}

} // extern C
