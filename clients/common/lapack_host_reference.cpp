/* ************************************************************************
 * Copyright 2020-2021 Advanced Micro Devices, Inc.
 * ************************************************************************/

#include "../include/lapack_host_reference.hpp"
#include "cblas.h"
#include "hipsolver.h"

/*!\file
 * \brief provide template functions interfaces to BLAS and LAPACK interfaces, it is
 * only used for testing, not part of the GPU library
 */

/*************************************************************************/
// These are C wrapper calls to CBLAS and fortran LAPACK

#ifdef __cplusplus
extern "C" {
#endif

void ssymm_(char*  side,
            char*  uplo,
            int*   m,
            int*   n,
            float* alpha,
            float* A,
            int*   lda,
            float* B,
            int*   ldb,
            float* beta,
            float* C,
            int*   ldc);
void dsymm_(char*   side,
            char*   uplo,
            int*    m,
            int*    n,
            double* alpha,
            double* A,
            int*    lda,
            double* B,
            int*    ldb,
            double* beta,
            double* C,
            int*    ldc);
void chemm_(char*             side,
            char*             uplo,
            int*              m,
            int*              n,
            hipsolverComplex* alpha,
            hipsolverComplex* A,
            int*              lda,
            hipsolverComplex* B,
            int*              ldb,
            hipsolverComplex* beta,
            hipsolverComplex* C,
            int*              ldc);
void zhemm_(char*                   side,
            char*                   uplo,
            int*                    m,
            int*                    n,
            hipsolverDoubleComplex* alpha,
            hipsolverDoubleComplex* A,
            int*                    lda,
            hipsolverDoubleComplex* B,
            int*                    ldb,
            hipsolverDoubleComplex* beta,
            hipsolverDoubleComplex* C,
            int*                    ldc);

void ssymv_(char*  uplo,
            int*   n,
            float* alpha,
            float* A,
            int*   lda,
            float* x,
            int*   incx,
            float* beta,
            float* y,
            int*   incy);
void dsymv_(char*   uplo,
            int*    n,
            double* alpha,
            double* A,
            int*    lda,
            double* x,
            int*    incx,
            double* beta,
            double* y,
            int*    incy);
void chemv_(char*             uplo,
            int*              n,
            hipsolverComplex* alpha,
            hipsolverComplex* A,
            int*              lda,
            hipsolverComplex* x,
            int*              incx,
            hipsolverComplex* beta,
            hipsolverComplex* y,
            int*              incy);
void zhemv_(char*                   uplo,
            int*                    n,
            hipsolverDoubleComplex* alpha,
            hipsolverDoubleComplex* A,
            int*                    lda,
            hipsolverDoubleComplex* x,
            int*                    incx,
            hipsolverDoubleComplex* beta,
            hipsolverDoubleComplex* y,
            int*                    incy);

void clacgv_(int* n, hipsolverComplex* x, int* incx);
void zlacgv_(int* n, hipsolverDoubleComplex* x, int* incx);

void slarf_(
    char* side, int* m, int* n, float* x, int* incx, float* alpha, float* A, int* lda, float* work);
void dlarf_(char*   side,
            int*    m,
            int*    n,
            double* x,
            int*    incx,
            double* alpha,
            double* A,
            int*    lda,
            double* work);
void clarf_(char*             side,
            int*              m,
            int*              n,
            hipsolverComplex* x,
            int*              incx,
            hipsolverComplex* alpha,
            hipsolverComplex* A,
            int*              lda,
            hipsolverComplex* work);
void zlarf_(char*                   side,
            int*                    m,
            int*                    n,
            hipsolverDoubleComplex* x,
            int*                    incx,
            hipsolverDoubleComplex* alpha,
            hipsolverDoubleComplex* A,
            int*                    lda,
            hipsolverDoubleComplex* work);

void sorgbr_(char*  vect,
             int*   m,
             int*   n,
             int*   k,
             float* A,
             int*   lda,
             float* Ipiv,
             float* work,
             int*   size_w,
             int*   info);
void dorgbr_(char*   vect,
             int*    m,
             int*    n,
             int*    k,
             double* A,
             int*    lda,
             double* Ipiv,
             double* work,
             int*    size_w,
             int*    info);
void cungbr_(char*             vect,
             int*              m,
             int*              n,
             int*              k,
             hipsolverComplex* A,
             int*              lda,
             hipsolverComplex* Ipiv,
             hipsolverComplex* work,
             int*              size_w,
             int*              info);
void zungbr_(char*                   vect,
             int*                    m,
             int*                    n,
             int*                    k,
             hipsolverDoubleComplex* A,
             int*                    lda,
             hipsolverDoubleComplex* Ipiv,
             hipsolverDoubleComplex* work,
             int*                    size_w,
             int*                    info);

void sorgqr_(
    int* m, int* n, int* k, float* A, int* lda, float* ipiv, float* work, int* lwork, int* info);
void dorgqr_(
    int* m, int* n, int* k, double* A, int* lda, double* ipiv, double* work, int* lwork, int* info);
void cungqr_(int*              m,
             int*              n,
             int*              k,
             hipsolverComplex* A,
             int*              lda,
             hipsolverComplex* ipiv,
             hipsolverComplex* work,
             int*              lwork,
             int*              info);
void zungqr_(int*                    m,
             int*                    n,
             int*                    k,
             hipsolverDoubleComplex* A,
             int*                    lda,
             hipsolverDoubleComplex* ipiv,
             hipsolverDoubleComplex* work,
             int*                    lwork,
             int*                    info);

void sorgtr_(
    char* uplo, int* n, float* A, int* lda, float* Ipiv, float* work, int* size_w, int* info);
void dorgtr_(
    char* uplo, int* n, double* A, int* lda, double* Ipiv, double* work, int* size_w, int* info);
void cungtr_(char*             uplo,
             int*              n,
             hipsolverComplex* A,
             int*              lda,
             hipsolverComplex* Ipiv,
             hipsolverComplex* work,
             int*              size_w,
             int*              info);
void zungtr_(char*                   uplo,
             int*                    n,
             hipsolverDoubleComplex* A,
             int*                    lda,
             hipsolverDoubleComplex* Ipiv,
             hipsolverDoubleComplex* work,
             int*                    size_w,
             int*                    info);

void sormqr_(char*  side,
             char*  trans,
             int*   m,
             int*   n,
             int*   k,
             float* A,
             int*   lda,
             float* ipiv,
             float* C,
             int*   ldc,
             float* work,
             int*   sizeW,
             int*   info);
void dormqr_(char*   side,
             char*   trans,
             int*    m,
             int*    n,
             int*    k,
             double* A,
             int*    lda,
             double* ipiv,
             double* C,
             int*    ldc,
             double* work,
             int*    sizeW,
             int*    info);
void cunmqr_(char*             side,
             char*             trans,
             int*              m,
             int*              n,
             int*              k,
             hipsolverComplex* A,
             int*              lda,
             hipsolverComplex* ipiv,
             hipsolverComplex* C,
             int*              ldc,
             hipsolverComplex* work,
             int*              sizeW,
             int*              info);
void zunmqr_(char*                   side,
             char*                   trans,
             int*                    m,
             int*                    n,
             int*                    k,
             hipsolverDoubleComplex* A,
             int*                    lda,
             hipsolverDoubleComplex* ipiv,
             hipsolverDoubleComplex* C,
             int*                    ldc,
             hipsolverDoubleComplex* work,
             int*                    sizeW,
             int*                    info);

void sormtr_(char*  side,
             char*  uplo,
             char*  trans,
             int*   m,
             int*   n,
             float* A,
             int*   lda,
             float* ipiv,
             float* C,
             int*   ldc,
             float* work,
             int*   sizeW,
             int*   info);
void dormtr_(char*   side,
             char*   uplo,
             char*   trans,
             int*    m,
             int*    n,
             double* A,
             int*    lda,
             double* ipiv,
             double* C,
             int*    ldc,
             double* work,
             int*    sizeW,
             int*    info);
void cunmtr_(char*             side,
             char*             uplo,
             char*             trans,
             int*              m,
             int*              n,
             hipsolverComplex* A,
             int*              lda,
             hipsolverComplex* ipiv,
             hipsolverComplex* C,
             int*              ldc,
             hipsolverComplex* work,
             int*              sizeW,
             int*              info);
void zunmtr_(char*                   side,
             char*                   uplo,
             char*                   trans,
             int*                    m,
             int*                    n,
             hipsolverDoubleComplex* A,
             int*                    lda,
             hipsolverDoubleComplex* ipiv,
             hipsolverDoubleComplex* C,
             int*                    ldc,
             hipsolverDoubleComplex* work,
             int*                    sizeW,
             int*                    info);

void sgebrd_(int*   m,
             int*   n,
             float* A,
             int*   lda,
             float* D,
             float* E,
             float* tauq,
             float* taup,
             float* work,
             int*   size_w,
             int*   info);
void dgebrd_(int*    m,
             int*    n,
             double* A,
             int*    lda,
             double* D,
             double* E,
             double* tauq,
             double* taup,
             double* work,
             int*    size_w,
             int*    info);
void cgebrd_(int*              m,
             int*              n,
             hipsolverComplex* A,
             int*              lda,
             float*            D,
             float*            E,
             hipsolverComplex* tauq,
             hipsolverComplex* taup,
             hipsolverComplex* work,
             int*              size_w,
             int*              info);
void zgebrd_(int*                    m,
             int*                    n,
             hipsolverDoubleComplex* A,
             int*                    lda,
             double*                 D,
             double*                 E,
             hipsolverDoubleComplex* tauq,
             hipsolverDoubleComplex* taup,
             hipsolverDoubleComplex* work,
             int*                    size_w,
             int*                    info);

void sgeqrf_(int* m, int* n, float* A, int* lda, float* ipiv, float* work, int* lwork, int* info);
void dgeqrf_(
    int* m, int* n, double* A, int* lda, double* ipiv, double* work, int* lwork, int* info);
void cgeqrf_(int*              m,
             int*              n,
             hipsolverComplex* A,
             int*              lda,
             hipsolverComplex* ipiv,
             hipsolverComplex* work,
             int*              lwork,
             int*              info);
void zgeqrf_(int*                    m,
             int*                    n,
             hipsolverDoubleComplex* A,
             int*                    lda,
             hipsolverDoubleComplex* ipiv,
             hipsolverDoubleComplex* work,
             int*                    lwork,
             int*                    info);

void sgesv_(int* n, int* nrhs, float* A, int* lda, int* ipiv, float* B, int* ldb, int* info);
void dgesv_(int* n, int* nrhs, double* A, int* lda, int* ipiv, double* B, int* ldb, int* info);
void cgesv_(int*              n,
            int*              nrhs,
            hipsolverComplex* A,
            int*              lda,
            int*              ipiv,
            hipsolverComplex* B,
            int*              ldb,
            int*              info);
void zgesv_(int*                    n,
            int*                    nrhs,
            hipsolverDoubleComplex* A,
            int*                    lda,
            int*                    ipiv,
            hipsolverDoubleComplex* B,
            int*                    ldb,
            int*                    info);

void sgesvd_(char*  jobu,
             char*  jobv,
             int*   m,
             int*   n,
             float* A,
             int*   lda,
             float* S,
             float* U,
             int*   ldu,
             float* V,
             int*   ldv,
             float* E,
             int*   lwork,
             int*   info);
void dgesvd_(char*   jobu,
             char*   jobv,
             int*    m,
             int*    n,
             double* A,
             int*    lda,
             double* S,
             double* U,
             int*    ldu,
             double* V,
             int*    ldv,
             double* E,
             int*    lwork,
             int*    info);
void cgesvd_(char*             jobu,
             char*             jobv,
             int*              m,
             int*              n,
             hipsolverComplex* A,
             int*              lda,
             float*            S,
             hipsolverComplex* U,
             int*              ldu,
             hipsolverComplex* V,
             int*              ldv,
             hipsolverComplex* work,
             int*              lwork,
             float*            E,
             int*              info);
void zgesvd_(char*                   jobu,
             char*                   jobv,
             int*                    m,
             int*                    n,
             hipsolverDoubleComplex* A,
             int*                    lda,
             double*                 S,
             hipsolverDoubleComplex* U,
             int*                    ldu,
             hipsolverDoubleComplex* V,
             int*                    ldv,
             hipsolverDoubleComplex* work,
             int*                    lwork,
             double*                 E,
             int*                    info);

void sgetrf_(int* m, int* n, float* A, int* lda, int* ipiv, int* info);
void dgetrf_(int* m, int* n, double* A, int* lda, int* ipiv, int* info);
void cgetrf_(int* m, int* n, hipsolverComplex* A, int* lda, int* ipiv, int* info);
void zgetrf_(int* m, int* n, hipsolverDoubleComplex* A, int* lda, int* ipiv, int* info);

void sgetrs_(
    char* trans, int* n, int* nrhs, float* A, int* lda, int* ipiv, float* B, int* ldb, int* info);
void dgetrs_(
    char* trans, int* n, int* nrhs, double* A, int* lda, int* ipiv, double* B, int* ldb, int* info);
void cgetrs_(char*             trans,
             int*              n,
             int*              nrhs,
             hipsolverComplex* A,
             int*              lda,
             int*              ipiv,
             hipsolverComplex* B,
             int*              ldb,
             int*              info);
void zgetrs_(char*                   trans,
             int*                    n,
             int*                    nrhs,
             hipsolverDoubleComplex* A,
             int*                    lda,
             int*                    ipiv,
             hipsolverDoubleComplex* B,
             int*                    ldb,
             int*                    info);

void spotrf_(char* uplo, int* m, float* A, int* lda, int* info);
void dpotrf_(char* uplo, int* m, double* A, int* lda, int* info);
void cpotrf_(char* uplo, int* m, hipsolverComplex* A, int* lda, int* info);
void zpotrf_(char* uplo, int* m, hipsolverDoubleComplex* A, int* lda, int* info);

void ssyevd_(char*  evect,
             char*  uplo,
             int*   n,
             float* A,
             int*   lda,
             float* D,
             float* work,
             int*   lwork,
             int*   iwork,
             int*   liwork,
             int*   info);
void dsyevd_(char*   evect,
             char*   uplo,
             int*    n,
             double* A,
             int*    lda,
             double* D,
             double* work,
             int*    lwork,
             int*    iwork,
             int*    liwork,
             int*    info);
void cheevd_(char*             evect,
             char*             uplo,
             int*              n,
             hipsolverComplex* A,
             int*              lda,
             float*            D,
             hipsolverComplex* work,
             int*              lwork,
             float*            rwork,
             int*              lrwork,
             int*              iwork,
             int*              liwork,
             int*              info);
void zheevd_(char*                   evect,
             char*                   uplo,
             int*                    n,
             hipsolverDoubleComplex* A,
             int*                    lda,
             double*                 D,
             hipsolverDoubleComplex* work,
             int*                    lwork,
             double*                 rwork,
             int*                    lrwork,
             int*                    iwork,
             int*                    liwork,
             int*                    info);

void ssygvd_(int*   itype,
             char*  evect,
             char*  uplo,
             int*   n,
             float* A,
             int*   lda,
             float* B,
             int*   ldb,
             float* W,
             float* work,
             int*   lwork,
             int*   iwork,
             int*   liwork,
             int*   info);
void dsygvd_(int*    itype,
             char*   evect,
             char*   uplo,
             int*    n,
             double* A,
             int*    lda,
             double* B,
             int*    ldb,
             double* W,
             double* work,
             int*    lwork,
             int*    iwork,
             int*    liwork,
             int*    info);
void chegvd_(int*              itype,
             char*             evect,
             char*             uplo,
             int*              n,
             hipsolverComplex* A,
             int*              lda,
             hipsolverComplex* B,
             int*              ldb,
             float*            W,
             hipsolverComplex* work,
             int*              lwork,
             float*            rwork,
             int*              lrwork,
             int*              iwork,
             int*              liwork,
             int*              info);
void zhegvd_(int*                    itype,
             char*                   evect,
             char*                   uplo,
             int*                    n,
             hipsolverDoubleComplex* A,
             int*                    lda,
             hipsolverDoubleComplex* B,
             int*                    ldb,
             double*                 W,
             hipsolverDoubleComplex* work,
             int*                    lwork,
             double*                 rwork,
             int*                    lrwork,
             int*                    iwork,
             int*                    liwork,
             int*                    info);

void ssytrd_(char*  uplo,
             int*   n,
             float* A,
             int*   lda,
             float* D,
             float* E,
             float* tau,
             float* work,
             int*   size_w,
             int*   info);
void dsytrd_(char*   uplo,
             int*    n,
             double* A,
             int*    lda,
             double* D,
             double* E,
             double* tau,
             double* work,
             int*    size_w,
             int*    info);
void chetrd_(char*             uplo,
             int*              n,
             hipsolverComplex* A,
             int*              lda,
             float*            D,
             float*            E,
             hipsolverComplex* tau,
             hipsolverComplex* work,
             int*              size_w,
             int*              info);
void zhetrd_(char*                   uplo,
             int*                    n,
             hipsolverDoubleComplex* A,
             int*                    lda,
             double*                 D,
             double*                 E,
             hipsolverDoubleComplex* tau,
             hipsolverDoubleComplex* work,
             int*                    size_w,
             int*                    info);

#ifdef __cplusplus
}
#endif
/************************************************************************/

/************************************************************************/
// These are templated BLAS functions used in hipSOLVER clients code

// gemm
template <>
void cblas_gemm<float>(hipsolverOperation_t transA,
                       hipsolverOperation_t transB,
                       int                  m,
                       int                  n,
                       int                  k,
                       float                alpha,
                       float*               A,
                       int                  lda,
                       float*               B,
                       int                  ldb,
                       float                beta,
                       float*               C,
                       int                  ldc)
{
    cblas_sgemm(CblasColMajor,
                (CBLAS_TRANSPOSE)transA,
                (CBLAS_TRANSPOSE)transB,
                m,
                n,
                k,
                alpha,
                A,
                lda,
                B,
                ldb,
                beta,
                C,
                ldc);
}

template <>
void cblas_gemm<double>(hipsolverOperation_t transA,
                        hipsolverOperation_t transB,
                        int                  m,
                        int                  n,
                        int                  k,
                        double               alpha,
                        double*              A,
                        int                  lda,
                        double*              B,
                        int                  ldb,
                        double               beta,
                        double*              C,
                        int                  ldc)
{
    cblas_dgemm(CblasColMajor,
                (CBLAS_TRANSPOSE)transA,
                (CBLAS_TRANSPOSE)transB,
                m,
                n,
                k,
                alpha,
                A,
                lda,
                B,
                ldb,
                beta,
                C,
                ldc);
}

template <>
void cblas_gemm<hipsolverComplex>(hipsolverOperation_t transA,
                                  hipsolverOperation_t transB,
                                  int                  m,
                                  int                  n,
                                  int                  k,
                                  hipsolverComplex     alpha,
                                  hipsolverComplex*    A,
                                  int                  lda,
                                  hipsolverComplex*    B,
                                  int                  ldb,
                                  hipsolverComplex     beta,
                                  hipsolverComplex*    C,
                                  int                  ldc)
{
    cblas_cgemm(CblasColMajor,
                (CBLAS_TRANSPOSE)transA,
                (CBLAS_TRANSPOSE)transB,
                m,
                n,
                k,
                &alpha,
                A,
                lda,
                B,
                ldb,
                &beta,
                C,
                ldc);
}

template <>
void cblas_gemm<hipsolverDoubleComplex>(hipsolverOperation_t    transA,
                                        hipsolverOperation_t    transB,
                                        int                     m,
                                        int                     n,
                                        int                     k,
                                        hipsolverDoubleComplex  alpha,
                                        hipsolverDoubleComplex* A,
                                        int                     lda,
                                        hipsolverDoubleComplex* B,
                                        int                     ldb,
                                        hipsolverDoubleComplex  beta,
                                        hipsolverDoubleComplex* C,
                                        int                     ldc)
{
    cblas_zgemm(CblasColMajor,
                (CBLAS_TRANSPOSE)transA,
                (CBLAS_TRANSPOSE)transB,
                m,
                n,
                k,
                &alpha,
                A,
                lda,
                B,
                ldb,
                &beta,
                C,
                ldc);
}

// symm & hemm
template <>
void cblas_symm_hemm<float>(hipsolverSideMode_t side,
                            hipsolverFillMode_t uplo,
                            int                 m,
                            int                 n,
                            float               alpha,
                            float*              A,
                            int                 lda,
                            float*              B,
                            int                 ldb,
                            float               beta,
                            float*              C,
                            int                 ldc)
{
    char sideC = hipsolver2char_side(side);
    char uploC = hipsolver2char_fill(uplo);
    ssymm_(&sideC, &uploC, &m, &n, &alpha, A, &lda, B, &ldb, &beta, C, &ldc);
}

template <>
void cblas_symm_hemm<double>(hipsolverSideMode_t side,
                             hipsolverFillMode_t uplo,
                             int                 m,
                             int                 n,
                             double              alpha,
                             double*             A,
                             int                 lda,
                             double*             B,
                             int                 ldb,
                             double              beta,
                             double*             C,
                             int                 ldc)
{
    char sideC = hipsolver2char_side(side);
    char uploC = hipsolver2char_fill(uplo);
    dsymm_(&sideC, &uploC, &m, &n, &alpha, A, &lda, B, &ldb, &beta, C, &ldc);
}

template <>
void cblas_symm_hemm<hipsolverComplex>(hipsolverSideMode_t side,
                                       hipsolverFillMode_t uplo,
                                       int                 m,
                                       int                 n,
                                       hipsolverComplex    alpha,
                                       hipsolverComplex*   A,
                                       int                 lda,
                                       hipsolverComplex*   B,
                                       int                 ldb,
                                       hipsolverComplex    beta,
                                       hipsolverComplex*   C,
                                       int                 ldc)
{
    char sideC = hipsolver2char_side(side);
    char uploC = hipsolver2char_fill(uplo);
    chemm_(&sideC, &uploC, &m, &n, &alpha, A, &lda, B, &ldb, &beta, C, &ldc);
}

template <>
void cblas_symm_hemm<hipsolverDoubleComplex>(hipsolverSideMode_t     side,
                                             hipsolverFillMode_t     uplo,
                                             int                     m,
                                             int                     n,
                                             hipsolverDoubleComplex  alpha,
                                             hipsolverDoubleComplex* A,
                                             int                     lda,
                                             hipsolverDoubleComplex* B,
                                             int                     ldb,
                                             hipsolverDoubleComplex  beta,
                                             hipsolverDoubleComplex* C,
                                             int                     ldc)
{
    char sideC = hipsolver2char_side(side);
    char uploC = hipsolver2char_fill(uplo);
    zhemm_(&sideC, &uploC, &m, &n, &alpha, A, &lda, B, &ldb, &beta, C, &ldc);
}

// symv/hemv
template <>
void cblas_symv_hemv<float>(hipsolverFillMode_t uplo,
                            int                 n,
                            float               alpha,
                            float*              A,
                            int                 lda,
                            float*              x,
                            int                 incx,
                            float               beta,
                            float*              y,
                            int                 incy)
{
    char uploC = hipsolver2char_fill(uplo);
    ssymv_(&uploC, &n, &alpha, A, &lda, x, &incx, &beta, y, &incy);
}

template <>
void cblas_symv_hemv<double>(hipsolverFillMode_t uplo,
                             int                 n,
                             double              alpha,
                             double*             A,
                             int                 lda,
                             double*             x,
                             int                 incx,
                             double              beta,
                             double*             y,
                             int                 incy)
{
    char uploC = hipsolver2char_fill(uplo);
    dsymv_(&uploC, &n, &alpha, A, &lda, x, &incx, &beta, y, &incy);
}

template <>
void cblas_symv_hemv<hipsolverComplex>(hipsolverFillMode_t uplo,
                                       int                 n,
                                       hipsolverComplex    alpha,
                                       hipsolverComplex*   A,
                                       int                 lda,
                                       hipsolverComplex*   x,
                                       int                 incx,
                                       hipsolverComplex    beta,
                                       hipsolverComplex*   y,
                                       int                 incy)
{
    char uploC = hipsolver2char_fill(uplo);
    chemv_(&uploC, &n, &alpha, A, &lda, x, &incx, &beta, y, &incy);
}

template <>
void cblas_symv_hemv<hipsolverDoubleComplex>(hipsolverFillMode_t     uplo,
                                             int                     n,
                                             hipsolverDoubleComplex  alpha,
                                             hipsolverDoubleComplex* A,
                                             int                     lda,
                                             hipsolverDoubleComplex* x,
                                             int                     incx,
                                             hipsolverDoubleComplex  beta,
                                             hipsolverDoubleComplex* y,
                                             int                     incy)
{
    char uploC = hipsolver2char_fill(uplo);
    zhemv_(&uploC, &n, &alpha, A, &lda, x, &incx, &beta, y, &incy);
}

/************************************************************************/
// These are templated LAPACK functions used in hipSOLVER clients code

// lacgv
template <>
void cblas_lacgv<hipsolverComplex>(int n, hipsolverComplex* x, int incx)
{
    clacgv_(&n, x, &incx);
}

template <>
void cblas_lacgv<hipsolverDoubleComplex>(int n, hipsolverDoubleComplex* x, int incx)
{
    zlacgv_(&n, x, &incx);
}

// larf
template <>
void cblas_larf<float>(hipsolverSideMode_t sideR,
                       int                 m,
                       int                 n,
                       float*              x,
                       int                 incx,
                       float*              alpha,
                       float*              A,
                       int                 lda,
                       float*              work)
{
    char side = hipsolver2char_side(sideR);
    slarf_(&side, &m, &n, x, &incx, alpha, A, &lda, work);
}

template <>
void cblas_larf<double>(hipsolverSideMode_t sideR,
                        int                 m,
                        int                 n,
                        double*             x,
                        int                 incx,
                        double*             alpha,
                        double*             A,
                        int                 lda,
                        double*             work)
{
    char side = hipsolver2char_side(sideR);
    dlarf_(&side, &m, &n, x, &incx, alpha, A, &lda, work);
}

template <>
void cblas_larf<hipsolverComplex>(hipsolverSideMode_t sideR,
                                  int                 m,
                                  int                 n,
                                  hipsolverComplex*   x,
                                  int                 incx,
                                  hipsolverComplex*   alpha,
                                  hipsolverComplex*   A,
                                  int                 lda,
                                  hipsolverComplex*   work)
{
    char side = hipsolver2char_side(sideR);
    clarf_(&side, &m, &n, x, &incx, alpha, A, &lda, work);
}

template <>
void cblas_larf<hipsolverDoubleComplex>(hipsolverSideMode_t     sideR,
                                        int                     m,
                                        int                     n,
                                        hipsolverDoubleComplex* x,
                                        int                     incx,
                                        hipsolverDoubleComplex* alpha,
                                        hipsolverDoubleComplex* A,
                                        int                     lda,
                                        hipsolverDoubleComplex* work)
{
    char side = hipsolver2char_side(sideR);
    zlarf_(&side, &m, &n, x, &incx, alpha, A, &lda, work);
}

// orgbr & ungbr
template <>
void cblas_orgbr_ungbr<float>(hipsolverSideMode_t side,
                              int                 m,
                              int                 n,
                              int                 k,
                              float*              A,
                              int                 lda,
                              float*              Ipiv,
                              float*              work,
                              int                 size_w)
{
    int  info;
    char vect;
    if(side == HIPSOLVER_SIDE_LEFT)
        vect = 'Q';
    else
        vect = 'P';
    sorgbr_(&vect, &m, &n, &k, A, &lda, Ipiv, work, &size_w, &info);
}

template <>
void cblas_orgbr_ungbr<double>(hipsolverSideMode_t side,
                               int                 m,
                               int                 n,
                               int                 k,
                               double*             A,
                               int                 lda,
                               double*             Ipiv,
                               double*             work,
                               int                 size_w)
{
    int  info;
    char vect;
    if(side == HIPSOLVER_SIDE_LEFT)
        vect = 'Q';
    else
        vect = 'P';
    dorgbr_(&vect, &m, &n, &k, A, &lda, Ipiv, work, &size_w, &info);
}

template <>
void cblas_orgbr_ungbr<hipsolverComplex>(hipsolverSideMode_t side,
                                         int                 m,
                                         int                 n,
                                         int                 k,
                                         hipsolverComplex*   A,
                                         int                 lda,
                                         hipsolverComplex*   Ipiv,
                                         hipsolverComplex*   work,
                                         int                 size_w)
{
    int  info;
    char vect;
    if(side == HIPSOLVER_SIDE_LEFT)
        vect = 'Q';
    else
        vect = 'P';
    cungbr_(&vect, &m, &n, &k, A, &lda, Ipiv, work, &size_w, &info);
}

template <>
void cblas_orgbr_ungbr<hipsolverDoubleComplex>(hipsolverSideMode_t     side,
                                               int                     m,
                                               int                     n,
                                               int                     k,
                                               hipsolverDoubleComplex* A,
                                               int                     lda,
                                               hipsolverDoubleComplex* Ipiv,
                                               hipsolverDoubleComplex* work,
                                               int                     size_w)
{
    int  info;
    char vect;
    if(side == HIPSOLVER_SIDE_LEFT)
        vect = 'Q';
    else
        vect = 'P';
    zungbr_(&vect, &m, &n, &k, A, &lda, Ipiv, work, &size_w, &info);
}

// orgqr & ungqr
template <>
void cblas_orgqr_ungqr<float>(
    int m, int n, int k, float* A, int lda, float* ipiv, float* work, int lwork)
{
    int info;
    sorgqr_(&m, &n, &k, A, &lda, ipiv, work, &lwork, &info);
}

template <>
void cblas_orgqr_ungqr<double>(
    int m, int n, int k, double* A, int lda, double* ipiv, double* work, int lwork)
{
    int info;
    dorgqr_(&m, &n, &k, A, &lda, ipiv, work, &lwork, &info);
}

template <>
void cblas_orgqr_ungqr<hipsolverComplex>(int               m,
                                         int               n,
                                         int               k,
                                         hipsolverComplex* A,
                                         int               lda,
                                         hipsolverComplex* ipiv,
                                         hipsolverComplex* work,
                                         int               lwork)
{
    int info;
    cungqr_(&m, &n, &k, A, &lda, ipiv, work, &lwork, &info);
}

template <>
void cblas_orgqr_ungqr<hipsolverDoubleComplex>(int                     m,
                                               int                     n,
                                               int                     k,
                                               hipsolverDoubleComplex* A,
                                               int                     lda,
                                               hipsolverDoubleComplex* ipiv,
                                               hipsolverDoubleComplex* work,
                                               int                     lwork)
{
    int info;
    zungqr_(&m, &n, &k, A, &lda, ipiv, work, &lwork, &info);
}

// orgtr & ungtr
template <>
void cblas_orgtr_ungtr<float>(
    hipsolverFillMode_t uplo, int n, float* A, int lda, float* Ipiv, float* work, int size_w)
{
    int  info;
    char uploC = hipsolver2char_fill(uplo);
    sorgtr_(&uploC, &n, A, &lda, Ipiv, work, &size_w, &info);
}

template <>
void cblas_orgtr_ungtr<double>(
    hipsolverFillMode_t uplo, int n, double* A, int lda, double* Ipiv, double* work, int size_w)
{
    int  info;
    char uploC = hipsolver2char_fill(uplo);
    dorgtr_(&uploC, &n, A, &lda, Ipiv, work, &size_w, &info);
}

template <>
void cblas_orgtr_ungtr<hipsolverComplex>(hipsolverFillMode_t uplo,
                                         int                 n,
                                         hipsolverComplex*   A,
                                         int                 lda,
                                         hipsolverComplex*   Ipiv,
                                         hipsolverComplex*   work,
                                         int                 size_w)
{
    int  info;
    char uploC = hipsolver2char_fill(uplo);
    cungtr_(&uploC, &n, A, &lda, Ipiv, work, &size_w, &info);
}

template <>
void cblas_orgtr_ungtr<hipsolverDoubleComplex>(hipsolverFillMode_t     uplo,
                                               int                     n,
                                               hipsolverDoubleComplex* A,
                                               int                     lda,
                                               hipsolverDoubleComplex* Ipiv,
                                               hipsolverDoubleComplex* work,
                                               int                     size_w)
{
    int  info;
    char uploC = hipsolver2char_fill(uplo);
    zungtr_(&uploC, &n, A, &lda, Ipiv, work, &size_w, &info);
}

// ormqr & unmqr
template <>
void cblas_ormqr_unmqr<float>(hipsolverSideMode_t  side,
                              hipsolverOperation_t trans,
                              int                  m,
                              int                  n,
                              int                  k,
                              float*               A,
                              int                  lda,
                              float*               ipiv,
                              float*               C,
                              int                  ldc,
                              float*               work,
                              int                  lwork)
{
    int  info;
    char sideC  = hipsolver2char_side(side);
    char transC = hipsolver2char_operation(trans);

    sormqr_(&sideC, &transC, &m, &n, &k, A, &lda, ipiv, C, &ldc, work, &lwork, &info);
}

template <>
void cblas_ormqr_unmqr<double>(hipsolverSideMode_t  side,
                               hipsolverOperation_t trans,
                               int                  m,
                               int                  n,
                               int                  k,
                               double*              A,
                               int                  lda,
                               double*              ipiv,
                               double*              C,
                               int                  ldc,
                               double*              work,
                               int                  lwork)
{
    int  info;
    char sideC  = hipsolver2char_side(side);
    char transC = hipsolver2char_operation(trans);

    dormqr_(&sideC, &transC, &m, &n, &k, A, &lda, ipiv, C, &ldc, work, &lwork, &info);
}

template <>
void cblas_ormqr_unmqr<hipsolverComplex>(hipsolverSideMode_t  side,
                                         hipsolverOperation_t trans,
                                         int                  m,
                                         int                  n,
                                         int                  k,
                                         hipsolverComplex*    A,
                                         int                  lda,
                                         hipsolverComplex*    ipiv,
                                         hipsolverComplex*    C,
                                         int                  ldc,
                                         hipsolverComplex*    work,
                                         int                  lwork)
{
    int  info;
    char sideC  = hipsolver2char_side(side);
    char transC = hipsolver2char_operation(trans);

    cunmqr_(&sideC, &transC, &m, &n, &k, A, &lda, ipiv, C, &ldc, work, &lwork, &info);
}

template <>
void cblas_ormqr_unmqr<hipsolverDoubleComplex>(hipsolverSideMode_t     side,
                                               hipsolverOperation_t    trans,
                                               int                     m,
                                               int                     n,
                                               int                     k,
                                               hipsolverDoubleComplex* A,
                                               int                     lda,
                                               hipsolverDoubleComplex* ipiv,
                                               hipsolverDoubleComplex* C,
                                               int                     ldc,
                                               hipsolverDoubleComplex* work,
                                               int                     lwork)
{
    int  info;
    char sideC  = hipsolver2char_side(side);
    char transC = hipsolver2char_operation(trans);

    zunmqr_(&sideC, &transC, &m, &n, &k, A, &lda, ipiv, C, &ldc, work, &lwork, &info);
}

// ormtr & unmtr
template <>
void cblas_ormtr_unmtr<float>(hipsolverSideMode_t  side,
                              hipsolverFillMode_t  uplo,
                              hipsolverOperation_t trans,
                              int                  m,
                              int                  n,
                              float*               A,
                              int                  lda,
                              float*               ipiv,
                              float*               C,
                              int                  ldc,
                              float*               work,
                              int                  lwork)
{
    int  info;
    char sideC  = hipsolver2char_side(side);
    char uploC  = hipsolver2char_fill(uplo);
    char transC = hipsolver2char_operation(trans);

    sormtr_(&sideC, &uploC, &transC, &m, &n, A, &lda, ipiv, C, &ldc, work, &lwork, &info);
}

template <>
void cblas_ormtr_unmtr<double>(hipsolverSideMode_t  side,
                               hipsolverFillMode_t  uplo,
                               hipsolverOperation_t trans,
                               int                  m,
                               int                  n,
                               double*              A,
                               int                  lda,
                               double*              ipiv,
                               double*              C,
                               int                  ldc,
                               double*              work,
                               int                  lwork)
{
    int  info;
    char sideC  = hipsolver2char_side(side);
    char uploC  = hipsolver2char_fill(uplo);
    char transC = hipsolver2char_operation(trans);

    dormtr_(&sideC, &uploC, &transC, &m, &n, A, &lda, ipiv, C, &ldc, work, &lwork, &info);
}

template <>
void cblas_ormtr_unmtr<hipsolverComplex>(hipsolverSideMode_t  side,
                                         hipsolverFillMode_t  uplo,
                                         hipsolverOperation_t trans,
                                         int                  m,
                                         int                  n,
                                         hipsolverComplex*    A,
                                         int                  lda,
                                         hipsolverComplex*    ipiv,
                                         hipsolverComplex*    C,
                                         int                  ldc,
                                         hipsolverComplex*    work,
                                         int                  lwork)
{
    int  info;
    char sideC  = hipsolver2char_side(side);
    char uploC  = hipsolver2char_fill(uplo);
    char transC = hipsolver2char_operation(trans);

    cunmtr_(&sideC, &uploC, &transC, &m, &n, A, &lda, ipiv, C, &ldc, work, &lwork, &info);
}

template <>
void cblas_ormtr_unmtr<hipsolverDoubleComplex>(hipsolverSideMode_t     side,
                                               hipsolverFillMode_t     uplo,
                                               hipsolverOperation_t    trans,
                                               int                     m,
                                               int                     n,
                                               hipsolverDoubleComplex* A,
                                               int                     lda,
                                               hipsolverDoubleComplex* ipiv,
                                               hipsolverDoubleComplex* C,
                                               int                     ldc,
                                               hipsolverDoubleComplex* work,
                                               int                     lwork)
{
    int  info;
    char sideC  = hipsolver2char_side(side);
    char uploC  = hipsolver2char_fill(uplo);
    char transC = hipsolver2char_operation(trans);

    zunmtr_(&sideC, &uploC, &transC, &m, &n, A, &lda, ipiv, C, &ldc, work, &lwork, &info);
}

// gebrd
template <>
void cblas_gebrd<float, float>(int    m,
                               int    n,
                               float* A,
                               int    lda,
                               float* D,
                               float* E,
                               float* tauq,
                               float* taup,
                               float* work,
                               int    size_w)
{
    int info;
    sgebrd_(&m, &n, A, &lda, D, E, tauq, taup, work, &size_w, &info);
}

template <>
void cblas_gebrd<double, double>(int     m,
                                 int     n,
                                 double* A,
                                 int     lda,
                                 double* D,
                                 double* E,
                                 double* tauq,
                                 double* taup,
                                 double* work,
                                 int     size_w)
{
    int info;
    dgebrd_(&m, &n, A, &lda, D, E, tauq, taup, work, &size_w, &info);
}

template <>
void cblas_gebrd<hipsolverComplex, float>(int               m,
                                          int               n,
                                          hipsolverComplex* A,
                                          int               lda,
                                          float*            D,
                                          float*            E,
                                          hipsolverComplex* tauq,
                                          hipsolverComplex* taup,
                                          hipsolverComplex* work,
                                          int               size_w)
{
    int info;
    cgebrd_(&m, &n, A, &lda, D, E, tauq, taup, work, &size_w, &info);
}

template <>
void cblas_gebrd<hipsolverDoubleComplex, double>(int                     m,
                                                 int                     n,
                                                 hipsolverDoubleComplex* A,
                                                 int                     lda,
                                                 double*                 D,
                                                 double*                 E,
                                                 hipsolverDoubleComplex* tauq,
                                                 hipsolverDoubleComplex* taup,
                                                 hipsolverDoubleComplex* work,
                                                 int                     size_w)
{
    int info;
    zgebrd_(&m, &n, A, &lda, D, E, tauq, taup, work, &size_w, &info);
}

// geqrf
template <>
void cblas_geqrf<float>(int m, int n, float* A, int lda, float* ipiv, float* work, int lwork)
{
    int info;
    sgeqrf_(&m, &n, A, &lda, ipiv, work, &lwork, &info);
}

template <>
void cblas_geqrf<double>(int m, int n, double* A, int lda, double* ipiv, double* work, int lwork)
{
    int info;
    dgeqrf_(&m, &n, A, &lda, ipiv, work, &lwork, &info);
}

template <>
void cblas_geqrf<hipsolverComplex>(int               m,
                                   int               n,
                                   hipsolverComplex* A,
                                   int               lda,
                                   hipsolverComplex* ipiv,
                                   hipsolverComplex* work,
                                   int               lwork)
{
    int info;
    cgeqrf_(&m, &n, A, &lda, ipiv, work, &lwork, &info);
}

template <>
void cblas_geqrf<hipsolverDoubleComplex>(int                     m,
                                         int                     n,
                                         hipsolverDoubleComplex* A,
                                         int                     lda,
                                         hipsolverDoubleComplex* ipiv,
                                         hipsolverDoubleComplex* work,
                                         int                     lwork)
{
    int info;
    zgeqrf_(&m, &n, A, &lda, ipiv, work, &lwork, &info);
}

// gesv
template <>
void cblas_gesv<float>(int n, int nrhs, float* A, int lda, int* ipiv, float* B, int ldb, int* info)
{
    sgesv_(&n, &nrhs, A, &lda, ipiv, B, &ldb, info);
}

template <>
void cblas_gesv<double>(
    int n, int nrhs, double* A, int lda, int* ipiv, double* B, int ldb, int* info)
{
    dgesv_(&n, &nrhs, A, &lda, ipiv, B, &ldb, info);
}

template <>
void cblas_gesv<hipsolverComplex>(int               n,
                                  int               nrhs,
                                  hipsolverComplex* A,
                                  int               lda,
                                  int*              ipiv,
                                  hipsolverComplex* B,
                                  int               ldb,
                                  int*              info)
{
    cgesv_(&n, &nrhs, A, &lda, ipiv, B, &ldb, info);
}

template <>
void cblas_gesv<hipsolverDoubleComplex>(int                     n,
                                        int                     nrhs,
                                        hipsolverDoubleComplex* A,
                                        int                     lda,
                                        int*                    ipiv,
                                        hipsolverDoubleComplex* B,
                                        int                     ldb,
                                        int*                    info)
{
    zgesv_(&n, &nrhs, A, &lda, ipiv, B, &ldb, info);
}

// gesvd
template <>
void cblas_gesvd(char   jobu,
                 char   jobv,
                 int    m,
                 int    n,
                 float* A,
                 int    lda,
                 float* S,
                 float* U,
                 int    ldu,
                 float* V,
                 int    ldv,
                 float* work,
                 int    lwork,
                 float* E,
                 int*   info)
{
    sgesvd_(&jobu, &jobv, &m, &n, A, &lda, S, U, &ldu, V, &ldv, E, &lwork, info);
}

template <>
void cblas_gesvd(char    jobu,
                 char    jobv,
                 int     m,
                 int     n,
                 double* A,
                 int     lda,
                 double* S,
                 double* U,
                 int     ldu,
                 double* V,
                 int     ldv,
                 double* work,
                 int     lwork,
                 double* E,
                 int*    info)
{
    dgesvd_(&jobu, &jobv, &m, &n, A, &lda, S, U, &ldu, V, &ldv, E, &lwork, info);
}

template <>
void cblas_gesvd(char              jobu,
                 char              jobv,
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
                 float*            E,
                 int*              info)
{
    cgesvd_(&jobu, &jobv, &m, &n, A, &lda, S, U, &ldu, V, &ldv, work, &lwork, E, info);
}

template <>
void cblas_gesvd(char                    jobu,
                 char                    jobv,
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
                 double*                 E,
                 int*                    info)
{
    zgesvd_(&jobu, &jobv, &m, &n, A, &lda, S, U, &ldu, V, &ldv, work, &lwork, E, info);
}

// getrf
template <>
void cblas_getrf<float>(int m, int n, float* A, int lda, int* ipiv, int* info)
{
    sgetrf_(&m, &n, A, &lda, ipiv, info);
}

template <>
void cblas_getrf<double>(int m, int n, double* A, int lda, int* ipiv, int* info)
{
    dgetrf_(&m, &n, A, &lda, ipiv, info);
}

template <>
void cblas_getrf<hipsolverComplex>(int m, int n, hipsolverComplex* A, int lda, int* ipiv, int* info)
{
    cgetrf_(&m, &n, A, &lda, ipiv, info);
}

template <>
void cblas_getrf<hipsolverDoubleComplex>(
    int m, int n, hipsolverDoubleComplex* A, int lda, int* ipiv, int* info)
{
    zgetrf_(&m, &n, A, &lda, ipiv, info);
}

// getrs
template <>
void cblas_getrs<float>(
    hipsolverOperation_t trans, int n, int nrhs, float* A, int lda, int* ipiv, float* B, int ldb)
{
    int  info;
    char transC = hipsolver2char_operation(trans);
    sgetrs_(&transC, &n, &nrhs, A, &lda, ipiv, B, &ldb, &info);
}

template <>
void cblas_getrs<double>(
    hipsolverOperation_t trans, int n, int nrhs, double* A, int lda, int* ipiv, double* B, int ldb)
{
    int  info;
    char transC = hipsolver2char_operation(trans);
    dgetrs_(&transC, &n, &nrhs, A, &lda, ipiv, B, &ldb, &info);
}

template <>
void cblas_getrs<hipsolverComplex>(hipsolverOperation_t trans,
                                   int                  n,
                                   int                  nrhs,
                                   hipsolverComplex*    A,
                                   int                  lda,
                                   int*                 ipiv,
                                   hipsolverComplex*    B,
                                   int                  ldb)
{
    int  info;
    char transC = hipsolver2char_operation(trans);
    cgetrs_(&transC, &n, &nrhs, A, &lda, ipiv, B, &ldb, &info);
}

template <>
void cblas_getrs<hipsolverDoubleComplex>(hipsolverOperation_t    trans,
                                         int                     n,
                                         int                     nrhs,
                                         hipsolverDoubleComplex* A,
                                         int                     lda,
                                         int*                    ipiv,
                                         hipsolverDoubleComplex* B,
                                         int                     ldb)
{
    int  info;
    char transC = hipsolver2char_operation(trans);
    zgetrs_(&transC, &n, &nrhs, A, &lda, ipiv, B, &ldb, &info);
}

// potrf
template <>
void cblas_potrf<float>(hipsolverFillMode_t uplo, int n, float* A, int lda, int* info)
{
    char uploC = hipsolver2char_fill(uplo);
    spotrf_(&uploC, &n, A, &lda, info);
}

template <>
void cblas_potrf<double>(hipsolverFillMode_t uplo, int n, double* A, int lda, int* info)
{
    char uploC = hipsolver2char_fill(uplo);
    dpotrf_(&uploC, &n, A, &lda, info);
}

template <>
void cblas_potrf<hipsolverComplex>(
    hipsolverFillMode_t uplo, int n, hipsolverComplex* A, int lda, int* info)
{
    char uploC = hipsolver2char_fill(uplo);
    cpotrf_(&uploC, &n, A, &lda, info);
}

template <>
void cblas_potrf<hipsolverDoubleComplex>(
    hipsolverFillMode_t uplo, int n, hipsolverDoubleComplex* A, int lda, int* info)
{
    char uploC = hipsolver2char_fill(uplo);
    zpotrf_(&uploC, &n, A, &lda, info);
}

// syevd & heevd
template <>
void cblas_syevd_heevd<float, float>(hipsolverEigMode_t  evect,
                                     hipsolverFillMode_t uplo,
                                     int                 n,
                                     float*              A,
                                     int                 lda,
                                     float*              D,
                                     float*              work,
                                     int                 lwork,
                                     float*              rwork,
                                     int                 lrwork,
                                     int*                iwork,
                                     int                 liwork,
                                     int*                info)
{
    char evectC = hipsolver2char_evect(evect);
    char uploC  = hipsolver2char_fill(uplo);
    ssyevd_(&evectC, &uploC, &n, A, &lda, D, rwork, &lrwork, iwork, &liwork, info);
}

template <>
void cblas_syevd_heevd<double, double>(hipsolverEigMode_t  evect,
                                       hipsolverFillMode_t uplo,
                                       int                 n,
                                       double*             A,
                                       int                 lda,
                                       double*             D,
                                       double*             work,
                                       int                 lwork,
                                       double*             rwork,
                                       int                 lrwork,
                                       int*                iwork,
                                       int                 liwork,
                                       int*                info)
{
    char evectC = hipsolver2char_evect(evect);
    char uploC  = hipsolver2char_fill(uplo);
    dsyevd_(&evectC, &uploC, &n, A, &lda, D, rwork, &lrwork, iwork, &liwork, info);
}

template <>
void cblas_syevd_heevd<hipsolverComplex, float>(hipsolverEigMode_t  evect,
                                                hipsolverFillMode_t uplo,
                                                int                 n,
                                                hipsolverComplex*   A,
                                                int                 lda,
                                                float*              D,
                                                hipsolverComplex*   work,
                                                int                 lwork,
                                                float*              rwork,
                                                int                 lrwork,
                                                int*                iwork,
                                                int                 liwork,
                                                int*                info)
{
    char evectC = hipsolver2char_evect(evect);
    char uploC  = hipsolver2char_fill(uplo);
    cheevd_(&evectC, &uploC, &n, A, &lda, D, work, &lwork, rwork, &lrwork, iwork, &liwork, info);
}

template <>
void cblas_syevd_heevd<hipsolverDoubleComplex, double>(hipsolverEigMode_t      evect,
                                                       hipsolverFillMode_t     uplo,
                                                       int                     n,
                                                       hipsolverDoubleComplex* A,
                                                       int                     lda,
                                                       double*                 D,
                                                       hipsolverDoubleComplex* work,
                                                       int                     lwork,
                                                       double*                 rwork,
                                                       int                     lrwork,
                                                       int*                    iwork,
                                                       int                     liwork,
                                                       int*                    info)
{
    char evectC = hipsolver2char_evect(evect);
    char uploC  = hipsolver2char_fill(uplo);
    zheevd_(&evectC, &uploC, &n, A, &lda, D, work, &lwork, rwork, &lrwork, iwork, &liwork, info);
}

// sygvd & hegvd
template <>
void cblas_sygvd_hegvd<float, float>(hipsolverEigType_t  itype,
                                     hipsolverEigMode_t  evect,
                                     hipsolverFillMode_t uplo,
                                     int                 n,
                                     float*              A,
                                     int                 lda,
                                     float*              B,
                                     int                 ldb,
                                     float*              W,
                                     float*              work,
                                     int                 lwork,
                                     float*              rwork,
                                     int                 lrwork,
                                     int*                iwork,
                                     int                 liwork,
                                     int*                info)
{
    int  itypeI = hipsolver2char_eform(itype) - '0';
    char evectC = hipsolver2char_evect(evect);
    char uploC  = hipsolver2char_fill(uplo);
    ssygvd_(
        &itypeI, &evectC, &uploC, &n, A, &lda, B, &ldb, W, rwork, &lrwork, iwork, &liwork, info);
}

template <>
void cblas_sygvd_hegvd<double, double>(hipsolverEigType_t  itype,
                                       hipsolverEigMode_t  evect,
                                       hipsolverFillMode_t uplo,
                                       int                 n,
                                       double*             A,
                                       int                 lda,
                                       double*             B,
                                       int                 ldb,
                                       double*             W,
                                       double*             work,
                                       int                 lwork,
                                       double*             rwork,
                                       int                 lrwork,
                                       int*                iwork,
                                       int                 liwork,
                                       int*                info)
{
    int  itypeI = hipsolver2char_eform(itype) - '0';
    char evectC = hipsolver2char_evect(evect);
    char uploC  = hipsolver2char_fill(uplo);
    dsygvd_(
        &itypeI, &evectC, &uploC, &n, A, &lda, B, &ldb, W, rwork, &lrwork, iwork, &liwork, info);
}

template <>
void cblas_sygvd_hegvd<hipsolverComplex, float>(hipsolverEigType_t  itype,
                                                hipsolverEigMode_t  evect,
                                                hipsolverFillMode_t uplo,
                                                int                 n,
                                                hipsolverComplex*   A,
                                                int                 lda,
                                                hipsolverComplex*   B,
                                                int                 ldb,
                                                float*              W,
                                                hipsolverComplex*   work,
                                                int                 lwork,
                                                float*              rwork,
                                                int                 lrwork,
                                                int*                iwork,
                                                int                 liwork,
                                                int*                info)
{
    int  itypeI = hipsolver2char_eform(itype) - '0';
    char evectC = hipsolver2char_evect(evect);
    char uploC  = hipsolver2char_fill(uplo);
    chegvd_(&itypeI,
            &evectC,
            &uploC,
            &n,
            A,
            &lda,
            B,
            &ldb,
            W,
            work,
            &lwork,
            rwork,
            &lrwork,
            iwork,
            &liwork,
            info);
}

template <>
void cblas_sygvd_hegvd<hipsolverDoubleComplex, double>(hipsolverEigType_t      itype,
                                                       hipsolverEigMode_t      evect,
                                                       hipsolverFillMode_t     uplo,
                                                       int                     n,
                                                       hipsolverDoubleComplex* A,
                                                       int                     lda,
                                                       hipsolverDoubleComplex* B,
                                                       int                     ldb,
                                                       double*                 W,
                                                       hipsolverDoubleComplex* work,
                                                       int                     lwork,
                                                       double*                 rwork,
                                                       int                     lrwork,
                                                       int*                    iwork,
                                                       int                     liwork,
                                                       int*                    info)
{
    int  itypeI = hipsolver2char_eform(itype) - '0';
    char evectC = hipsolver2char_evect(evect);
    char uploC  = hipsolver2char_fill(uplo);
    zhegvd_(&itypeI,
            &evectC,
            &uploC,
            &n,
            A,
            &lda,
            B,
            &ldb,
            W,
            work,
            &lwork,
            rwork,
            &lrwork,
            iwork,
            &liwork,
            info);
}

// sytrd & hetrd
template <>
void cblas_sytrd_hetrd<float, float>(hipsolverFillMode_t uplo,
                                     int                 n,
                                     float*              A,
                                     int                 lda,
                                     float*              D,
                                     float*              E,
                                     float*              tau,
                                     float*              work,
                                     int                 size_w)
{
    int  info;
    char uploC = hipsolver2char_fill(uplo);
    ssytrd_(&uploC, &n, A, &lda, D, E, tau, work, &size_w, &info);
}

template <>
void cblas_sytrd_hetrd<double, double>(hipsolverFillMode_t uplo,
                                       int                 n,
                                       double*             A,
                                       int                 lda,
                                       double*             D,
                                       double*             E,
                                       double*             tau,
                                       double*             work,
                                       int                 size_w)
{
    int  info;
    char uploC = hipsolver2char_fill(uplo);
    dsytrd_(&uploC, &n, A, &lda, D, E, tau, work, &size_w, &info);
}

template <>
void cblas_sytrd_hetrd<hipsolverComplex, float>(hipsolverFillMode_t uplo,
                                                int                 n,
                                                hipsolverComplex*   A,
                                                int                 lda,
                                                float*              D,
                                                float*              E,
                                                hipsolverComplex*   tau,
                                                hipsolverComplex*   work,
                                                int                 size_w)
{
    int  info;
    char uploC = hipsolver2char_fill(uplo);
    chetrd_(&uploC, &n, A, &lda, D, E, tau, work, &size_w, &info);
}

template <>
void cblas_sytrd_hetrd<hipsolverDoubleComplex, double>(hipsolverFillMode_t     uplo,
                                                       int                     n,
                                                       hipsolverDoubleComplex* A,
                                                       int                     lda,
                                                       double*                 D,
                                                       double*                 E,
                                                       hipsolverDoubleComplex* tau,
                                                       hipsolverDoubleComplex* work,
                                                       int                     size_w)
{
    int  info;
    char uploC = hipsolver2char_fill(uplo);
    zhetrd_(&uploC, &n, A, &lda, D, E, tau, work, &size_w, &info);
}
