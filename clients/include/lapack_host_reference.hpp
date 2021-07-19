/* ************************************************************************
 * Copyright 2020-2021 Advanced Micro Devices, Inc.
 * ************************************************************************/

#pragma once

#include "hipsolver.h"
#include "hipsolver_datatype2string.hpp"

// BLAS

template <typename T>
void cblas_gemm(hipsolverOperation_t transA,
                hipsolverOperation_t transB,
                int                  m,
                int                  n,
                int                  k,
                T                    alpha,
                T*                   A,
                int                  lda,
                T*                   B,
                int                  ldb,
                T                    beta,
                T*                   C,
                int                  ldc);

template <typename T>
void cblas_symm_hemm(hipsolverSideMode_t side,
                     hipsolverFillMode_t uplo,
                     int                 m,
                     int                 n,
                     T                   alpha,
                     T*                  A,
                     int                 lda,
                     T*                  B,
                     int                 ldb,
                     T                   beta,
                     T*                  C,
                     int                 ldc);

template <typename T>
void cblas_symv_hemv(hipsolverFillMode_t uplo,
                     int                 n,
                     T                   alpha,
                     T*                  A,
                     int                 lda,
                     T*                  x,
                     int                 incx,
                     T                   beta,
                     T*                  y,
                     int                 incy);

// LAPACK

template <typename T>
void cblas_lacgv(int n, T* x, int incx);

template <typename T>
void cblas_larf(
    hipsolverSideMode_t side, int m, int n, T* x, int incx, T* alpha, T* A, int lda, T* work);

template <typename T>
void cblas_orgbr_ungbr(
    hipsolverSideMode_t side, int m, int n, int k, T* A, int lda, T* Ipiv, T* work, int size_w);

template <typename T>
void cblas_orgqr_ungqr(int m, int n, int k, T* A, int lda, T* Ipiv, T* work, int sizeW);

template <typename T>
void cblas_orgtr_ungtr(
    hipsolverFillMode_t uplo, int n, T* A, int lda, T* Ipiv, T* work, int size_w);

template <typename T>
void cblas_ormqr_unmqr(hipsolverSideMode_t  side,
                       hipsolverOperation_t trans,
                       int                  m,
                       int                  n,
                       int                  k,
                       T*                   A,
                       int                  lda,
                       T*                   Ipiv,
                       T*                   C,
                       int                  ldc,
                       T*                   work,
                       int                  sizeW);

template <typename T>
void cblas_ormtr_unmtr(hipsolverSideMode_t  side,
                       hipsolverFillMode_t  uplo,
                       hipsolverOperation_t trans,
                       int                  m,
                       int                  n,
                       T*                   A,
                       int                  lda,
                       T*                   Ipiv,
                       T*                   C,
                       int                  ldc,
                       T*                   work,
                       int                  sizeW);

template <typename T, typename S>
void cblas_gebrd(int m, int n, T* A, int lda, S* D, S* E, T* tauq, T* taup, T* work, int size_w);

template <typename T>
void cblas_geqrf(int m, int n, T* A, int lda, T* ipiv, T* work, int sizeW);

template <typename T, typename W>
void cblas_gesvd(char leftv,
                 char rightv,
                 int  m,
                 int  n,
                 T*   A,
                 int  lda,
                 W*   S,
                 T*   U,
                 int  ldu,
                 T*   V,
                 int  ldv,
                 T*   work,
                 int  lwork,
                 W*   E,
                 int* info);

template <typename T>
void cblas_getrf(int m, int n, T* A, int lda, int* ipiv, int* info);

template <typename T>
void cblas_getrs(
    hipsolverOperation_t trans, int n, int nrhs, T* A, int lda, int* ipiv, T* B, int ldb);

template <typename T>
void cblas_potrf(hipsolverFillMode_t uplo, int n, T* A, int lda, int* info);

template <typename T>
void cblas_potrs(hipsolverFillMode_t uplo, int n, int nrhs, T* A, int lda, T* B, int ldb);

template <typename T, typename S>
void cblas_syevd_heevd(hipsolverEigMode_t  evect,
                       hipsolverFillMode_t uplo,
                       int                 n,
                       T*                  A,
                       int                 lda,
                       S*                  D,
                       T*                  work,
                       int                 lwork,
                       S*                  rwork,
                       int                 lrwork,
                       int*                iwork,
                       int                 liwork,
                       int*                info);

template <typename T, typename S>
void cblas_sygvd_hegvd(hipsolverEigType_t  itype,
                       hipsolverEigMode_t  evect,
                       hipsolverFillMode_t uplo,
                       int                 n,
                       T*                  A,
                       int                 lda,
                       T*                  B,
                       int                 ldb,
                       S*                  W,
                       T*                  work,
                       int                 lwork,
                       S*                  rwork,
                       int                 lrwork,
                       int*                iwork,
                       int                 liwork,
                       int*                info);

template <typename T, typename S>
void cblas_sytrd_hetrd(
    hipsolverFillMode_t uplo, int n, T* A, int lda, S* D, S* E, T* tau, T* work, int size_w);
