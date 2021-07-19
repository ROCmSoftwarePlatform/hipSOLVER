! ************************************************************************
!  Copyright 2020 Advanced Micro Devices, Inc.
! ************************************************************************

module hipsolver_enums
    use iso_c_binding

    !---------------------!
    !   hipSOLVER types   !
    !---------------------!

    enum, bind(c)
        enumerator :: HIPSOLVER_OP_N = 111
        enumerator :: HIPSOLVER_OP_T = 112
        enumerator :: HIPSOLVER_OP_C = 113
    end enum

    enum, bind(c)
        enumerator :: HIPSOLVER_FILL_MODE_UPPER = 121
        enumerator :: HIPSOLVER_FILL_MODE_LOWER = 122
    end enum

    enum, bind(c)
        enumerator :: HIPSOLVER_SIDE_LEFT  = 141
        enumerator :: HIPSOLVER_SIDE_RIGHT = 142
    end enum

    enum, bind(c)
        enumerator :: HIPSOLVER_EIG_MODE_NOVECTOR = 201
        enumerator :: HIPSOLVER_EIG_MODE_VECTOR   = 202
    end enum

    enum, bind(c)
        enumerator :: HIPSOLVER_EIG_TYPE_1 = 211
        enumerator :: HIPSOLVER_EIG_TYPE_2 = 212
        enumerator :: HIPSOLVER_EIG_TYPE_3 = 213
    end enum

    enum, bind(c)
        enumerator :: HIPSOLVER_STATUS_SUCCESS           = 0
        enumerator :: HIPSOLVER_STATUS_NOT_INITIALIZED   = 1
        enumerator :: HIPSOLVER_STATUS_ALLOC_FAILED      = 2
        enumerator :: HIPSOLVER_STATUS_INVALID_VALUE     = 3
        enumerator :: HIPSOLVER_STATUS_MAPPING_ERROR     = 4
        enumerator :: HIPSOLVER_STATUS_EXECUTION_FAILED  = 5
        enumerator :: HIPSOLVER_STATUS_INTERNAL_ERROR    = 6
        enumerator :: HIPSOLVER_STATUS_NOT_SUPPORTED     = 7
        enumerator :: HIPSOLVER_STATUS_ARCH_MISMATCH     = 8
        enumerator :: HIPSOLVER_STATUS_HANDLE_IS_NULLPTR = 9
        enumerator :: HIPSOLVER_STATUS_INVALID_ENUM      = 10
        enumerator :: HIPSOLVER_STATUS_UNKNOWN           = 11
    end enum

end module hipsolver_enums

module hipsolver
    use iso_c_binding

    !---------!
    !   Aux   !
    !---------!
    
    interface
        function hipsolverCreate(handle) &
                result(c_int) &
                bind(c, name = 'hipsolverCreate')
            use iso_c_binding
            implicit none
            type(c_ptr), value :: handle
        end function hipsolverCreate
    end interface

    interface
        function hipsolverDestroy(handle) &
                result(c_int) &
                bind(c, name = 'hipsolverDestroy')
            use iso_c_binding
            implicit none
            type(c_ptr), value :: handle
        end function hipsolverDestroy
    end interface

    interface
        function hipsolverSetStream(handle, streamId) &
                result(c_int) &
                bind(c, name = 'hipsolverSetStream')
            use iso_c_binding
            implicit none
            type(c_ptr), value :: handle
            type(c_ptr), value :: streamId
        end function hipsolverSetStream
    end interface

    interface
        function hipsolverGetStream(handle, streamId) &
                result(c_int) &
                bind(c, name = 'hipsolverGetStream')
            use iso_c_binding
            implicit none
            type(c_ptr), value :: handle
            type(c_ptr), value :: streamId
        end function hipsolverGetStream
    end interface

    !------------!
    !   LAPACK   !
    !------------!
    
    ! ******************** ORGBR/UNGBR ********************
    interface
        function hipsolverSorgbr_bufferSize(handle, side, m, n, k, A, lda, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSorgbr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverSorgbr_bufferSize
    end interface
    
    interface
        function hipsolverDorgbr_bufferSize(handle, side, m, n, k, A, lda, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDorgbr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverDorgbr_bufferSize
    end interface
    
    interface
        function hipsolverCungbr_bufferSize(handle, side, m, n, k, A, lda, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverCungbr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverCungbr_bufferSize
    end interface
    
    interface
        function hipsolverZungbr_bufferSize(handle, side, m, n, k, A, lda, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZungbr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverZungbr_bufferSize
    end interface
    
    interface
        function hipsolverSorgbr(handle, side, m, n, k, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSorgbr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverSorgbr
    end interface
    
    interface
        function hipsolverDorgbr(handle, side, m, n, k, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDorgbr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverDorgbr
    end interface
    
    interface
        function hipsolverCungbr(handle, side, m, n, k, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverCungbr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverCungbr
    end interface
    
    interface
        function hipsolverZungbr(handle, side, m, n, k, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZungbr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverZungbr
    end interface
    
    ! ******************** ORGQR/UNGQR ********************
    interface
        function hipsolverSorgqr_bufferSize(handle, m, n, k, A, lda, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSorgqr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverSorgqr_bufferSize
    end interface
    
    interface
        function hipsolverDorgqr_bufferSize(handle, m, n, k, A, lda, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDorgqr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverDorgqr_bufferSize
    end interface
    
    interface
        function hipsolverCungqr_bufferSize(handle, m, n, k, A, lda, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverCungqr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverCungqr_bufferSize
    end interface
    
    interface
        function hipsolverZungqr_bufferSize(handle, m, n, k, A, lda, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZungqr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverZungqr_bufferSize
    end interface
    
    interface
        function hipsolverSorgqr(handle, m, n, k, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSorgqr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverSorgqr
    end interface
    
    interface
        function hipsolverDorgqr(handle, m, n, k, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDorgqr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverDorgqr
    end interface
    
    interface
        function hipsolverCungqr(handle, m, n, k, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverCungqr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverCungqr
    end interface
    
    interface
        function hipsolverZungqr(handle, m, n, k, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZungqr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverZungqr
    end interface
    
    ! ******************** ORGTR/UNGTR ********************
    interface
        function hipsolverSorgtr_bufferSize(handle, uplo, n, A, lda, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSorgtr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverSorgtr_bufferSize
    end interface
    
    interface
        function hipsolverDorgtr_bufferSize(handle, uplo, n, A, lda, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDorgtr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverDorgtr_bufferSize
    end interface
    
    interface
        function hipsolverCungtr_bufferSize(handle, uplo, n, A, lda, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverCungtr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverCungtr_bufferSize
    end interface
    
    interface
        function hipsolverZungtr_bufferSize(handle, uplo, n, A, lda, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZungtr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverZungtr_bufferSize
    end interface
    
    interface
        function hipsolverSorgtr(handle, uplo, n, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSorgtr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverSorgtr
    end interface
    
    interface
        function hipsolverDorgtr(handle, uplo, n, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDorgtr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverDorgtr
    end interface
    
    interface
        function hipsolverCungtr(handle, uplo, n, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverCungtr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverCungtr
    end interface
    
    interface
        function hipsolverZungtr(handle, uplo, n, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZungtr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverZungtr
    end interface
    
    ! ******************** ORMQR/UNMQR ********************
    interface
        function hipsolverSormqr_bufferSize(handle, side, trans, m, n, k, A, lda, tau, C, ldc, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSormqr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: lwork
        end function hipsolverSormqr_bufferSize
    end interface
    
    interface
        function hipsolverDormqr_bufferSize(handle, side, trans, m, n, k, A, lda, tau, C, ldc, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDormqr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: lwork
        end function hipsolverDormqr_bufferSize
    end interface
    
    interface
        function hipsolverCunmqr_bufferSize(handle, side, trans, m, n, k, A, lda, tau, C, ldc, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverCunmqr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: lwork
        end function hipsolverCunmqr_bufferSize
    end interface
    
    interface
        function hipsolverZunmqr_bufferSize(handle, side, trans, m, n, k, A, lda, tau, C, ldc, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZunmqr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: lwork
        end function hipsolverZunmqr_bufferSize
    end interface
    
    interface
        function hipsolverSormqr(handle, side, trans, m, n, k, A, lda, tau, C, ldc, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSormqr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverSormqr
    end interface
    
    interface
        function hipsolverDormqr(handle, side, trans, m, n, k, A, lda, tau, C, ldc, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDormqr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverDormqr
    end interface
    
    interface
        function hipsolverCunmqr(handle, side, trans, m, n, k, A, lda, tau, C, ldc, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverCunmqr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverCunmqr
    end interface
    
    interface
        function hipsolverZunmqr(handle, side, trans, m, n, k, A, lda, tau, C, ldc, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZunmqr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            integer(c_int), value :: k
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverZunmqr
    end interface
    
    ! ******************** ORMTR/UNMTR ********************
    interface
        function hipsolverSormtr_bufferSize(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSormtr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: lwork
        end function hipsolverSormtr_bufferSize
    end interface
    
    interface
        function hipsolverDormtr_bufferSize(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDormtr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: lwork
        end function hipsolverDormtr_bufferSize
    end interface
    
    interface
        function hipsolverCunmtr_bufferSize(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverCunmtr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: lwork
        end function hipsolverCunmtr_bufferSize
    end interface
    
    interface
        function hipsolverZunmtr_bufferSize(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZunmtr_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: lwork
        end function hipsolverZunmtr_bufferSize
    end interface
    
    interface
        function hipsolverSormtr(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSormtr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverSormtr
    end interface
    
    interface
        function hipsolverDormtr(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDormtr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverDormtr
    end interface
    
    interface
        function hipsolverCunmtr(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverCunmtr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverCunmtr
    end interface
    
    interface
        function hipsolverZunmtr(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZunmtr')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_SIDE_LEFT)), value :: side
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: C
            integer(c_int), value :: ldc
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverZunmtr
    end interface
    
    ! ******************** GEBRD ********************
    interface
        function hipsolverSgebrd_bufferSize(handle, m, n, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSgebrd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: lwork
        end function hipsolverSgebrd_bufferSize
    end interface
    
    interface
        function hipsolverDgebrd_bufferSize(handle, m, n, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDgebrd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: lwork
        end function hipsolverDgebrd_bufferSize
    end interface
    
    interface
        function hipsolverCgebrd_bufferSize(handle, m, n, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverCgebrd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: lwork
        end function hipsolverCgebrd_bufferSize
    end interface
    
    interface
        function hipsolverZgebrd_bufferSize(handle, m, n, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZgebrd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: lwork
        end function hipsolverZgebrd_bufferSize
    end interface

    interface
        function hipsolverSgebrd(handle, m, n, A, lda, D, E, tauq, taup, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSgebrd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: E
            type(c_ptr), value :: tauq
            type(c_ptr), value :: taup
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverSgebrd
    end interface

    interface
        function hipsolverDgebrd(handle, m, n, A, lda, D, E, tauq, taup, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDgebrd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: E
            type(c_ptr), value :: tauq
            type(c_ptr), value :: taup
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverDgebrd
    end interface

    interface
        function hipsolverCgebrd(handle, m, n, A, lda, D, E, tauq, taup, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverCgebrd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: E
            type(c_ptr), value :: tauq
            type(c_ptr), value :: taup
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverCgebrd
    end interface

    interface
        function hipsolverZgebrd(handle, m, n, A, lda, D, E, tauq, taup, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZgebrd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: E
            type(c_ptr), value :: tauq
            type(c_ptr), value :: taup
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverZgebrd
    end interface
    
    ! ******************** GEQRF ********************
    interface
        function hipsolverSgeqrf_bufferSize(handle, m, n, A, lda, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSgeqrf_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
        end function hipsolverSgeqrf_bufferSize
    end interface

    interface
        function hipsolverDgeqrf_bufferSize(handle, m, n, A, lda, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDgeqrf_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
        end function hipsolverDgeqrf_bufferSize
    end interface

    interface
        function hipsolverCgeqrf_bufferSize(handle, m, n, A, lda, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverCgeqrf_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
        end function hipsolverCgeqrf_bufferSize
    end interface

    interface
        function hipsolverZgeqrf_bufferSize(handle, m, n, A, lda, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZgeqrf_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
        end function hipsolverZgeqrf_bufferSize
    end interface

    interface
        function hipsolverSgeqrf(handle, m, n, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSgeqrf')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverSgeqrf
    end interface

    interface
        function hipsolverDgeqrf(handle, m, n, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDgeqrf')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverDgeqrf
    end interface

    interface
        function hipsolverCgeqrf(handle, m, n, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverCgeqrf')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverCgeqrf
    end interface

    interface
        function hipsolverZgeqrf(handle, m, n, A, lda, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZgeqrf')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverZgeqrf
    end interface
    
    ! ******************** GESVD ********************
    interface
        function hipsolverSgesvd_bufferSize(handle, jobu, jobv, m, n, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSgesvd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_signed_char), value :: jobu
            integer(c_signed_char), value :: jobv
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: lwork
        end function hipsolverSgesvd_bufferSize
    end interface
    
    interface
        function hipsolverDgesvd_bufferSize(handle, jobu, jobv, m, n, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDgesvd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_signed_char), value :: jobu
            integer(c_signed_char), value :: jobv
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: lwork
        end function hipsolverDgesvd_bufferSize
    end interface
    
    interface
        function hipsolverCgesvd_bufferSize(handle, jobu, jobv, m, n, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverCgesvd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_signed_char), value :: jobu
            integer(c_signed_char), value :: jobv
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: lwork
        end function hipsolverCgesvd_bufferSize
    end interface
    
    interface
        function hipsolverZgesvd_bufferSize(handle, jobu, jobv, m, n, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZgesvd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_signed_char), value :: jobu
            integer(c_signed_char), value :: jobv
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: lwork
        end function hipsolverZgesvd_bufferSize
    end interface

    interface
        function hipsolverSgesvd(handle, jobu, jobv, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, rwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSgesvd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_signed_char), value :: jobu
            integer(c_signed_char), value :: jobv
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: S
            type(c_ptr), value :: U
            integer(c_int), value :: ldu
            type(c_ptr), value :: V
            integer(c_int), value :: ldv
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: rwork
            type(c_ptr), value :: info
        end function hipsolverSgesvd
    end interface

    interface
        function hipsolverDgesvd(handle, jobu, jobv, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, rwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDgesvd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_signed_char), value :: jobu
            integer(c_signed_char), value :: jobv
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: S
            type(c_ptr), value :: U
            integer(c_int), value :: ldu
            type(c_ptr), value :: V
            integer(c_int), value :: ldv
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: rwork
            type(c_ptr), value :: info
        end function hipsolverDgesvd
    end interface

    interface
        function hipsolverCgesvd(handle, jobu, jobv, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, rwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverCgesvd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_signed_char), value :: jobu
            integer(c_signed_char), value :: jobv
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: S
            type(c_ptr), value :: U
            integer(c_int), value :: ldu
            type(c_ptr), value :: V
            integer(c_int), value :: ldv
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: rwork
            type(c_ptr), value :: info
        end function hipsolverCgesvd
    end interface

    interface
        function hipsolverZgesvd(handle, jobu, jobv, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, rwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZgesvd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_signed_char), value :: jobu
            integer(c_signed_char), value :: jobv
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: S
            type(c_ptr), value :: U
            integer(c_int), value :: ldu
            type(c_ptr), value :: V
            integer(c_int), value :: ldv
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: rwork
            type(c_ptr), value :: info
        end function hipsolverZgesvd
    end interface

    ! ******************** GETRF ********************
    interface
        function hipsolverSgetrf_bufferSize(handle, m, n, A, lda, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSgetrf_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
        end function hipsolverSgetrf_bufferSize
    end interface
    
    interface
        function hipsolverDgetrf_bufferSize(handle, m, n, A, lda, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDgetrf_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
        end function hipsolverDgetrf_bufferSize
    end interface
    
    interface
        function hipsolverCgetrf_bufferSize(handle, m, n, A, lda, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverCgetrf_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
        end function hipsolverCgetrf_bufferSize
    end interface
    
    interface
        function hipsolverZgetrf_bufferSize(handle, m, n, A, lda, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZgetrf_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
        end function hipsolverZgetrf_bufferSize
    end interface

    interface
        function hipsolverSgetrf(handle, m, n, A, lda, work, lwork, ipiv, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSgetrf')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: ipiv
            type(c_ptr), value :: info
        end function hipsolverSgetrf
    end interface
    
    interface
        function hipsolverDgetrf(handle, m, n, A, lda, work, lwork, ipiv, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDgetrf')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: ipiv
            type(c_ptr), value :: info
        end function hipsolverDgetrf
    end interface
    
    interface
        function hipsolverCgetrf(handle, m, n, A, lda, work, lwork, ipiv, info) &
                result(c_int) &
                bind(c, name = 'hipsolverCgetrf')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: ipiv
            type(c_ptr), value :: info
        end function hipsolverCgetrf
    end interface
    
    interface
        function hipsolverZgetrf(handle, m, n, A, lda, work, lwork, ipiv, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZgetrf')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(c_int), value :: m
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: ipiv
            type(c_ptr), value :: info
        end function hipsolverZgetrf
    end interface

    ! ******************** GETRS ********************
    interface
        function hipsolverSgetrs_bufferSize(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSgetrs_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: ipiv
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: lwork
        end function hipsolverSgetrs_bufferSize
    end interface
    
    interface
        function hipsolverDgetrs_bufferSize(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDgetrs_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: ipiv
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: lwork
        end function hipsolverDgetrs_bufferSize
    end interface
    
    interface
        function hipsolverCgetrs_bufferSize(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverCgetrs_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: ipiv
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: lwork
        end function hipsolverCgetrs_bufferSize
    end interface
    
    interface
        function hipsolverZgetrs_bufferSize(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZgetrs_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: ipiv
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: lwork
        end function hipsolverZgetrs_bufferSize
    end interface

    interface
        function hipsolverSgetrs(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSgetrs')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: ipiv
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverSgetrs
    end interface
    
    interface
        function hipsolverDgetrs(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDgetrs')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: ipiv
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverDgetrs
    end interface
    
    interface
        function hipsolverCgetrs(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverCgetrs')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: ipiv
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverCgetrs
    end interface
    
    interface
        function hipsolverZgetrs(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZgetrs')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_OP_N)), value :: trans
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: ipiv
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverZgetrs
    end interface

    ! ******************** POTRF ********************
    interface
        function hipsolverSpotrf_bufferSize(handle, uplo, n, A, lda, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSpotrf_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
        end function hipsolverSpotrf_bufferSize
    end interface
    
    interface
        function hipsolverDpotrf_bufferSize(handle, uplo, n, A, lda, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDpotrf_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
        end function hipsolverDpotrf_bufferSize
    end interface
    
    interface
        function hipsolverCpotrf_bufferSize(handle, uplo, n, A, lda, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverCpotrf_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
        end function hipsolverCpotrf_bufferSize
    end interface
    
    interface
        function hipsolverZpotrf_bufferSize(handle, uplo, n, A, lda, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZpotrf_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
        end function hipsolverZpotrf_bufferSize
    end interface

    interface
        function hipsolverSpotrf(handle, uplo, n, A, lda, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSpotrf')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverSpotrf
    end interface

    interface
        function hipsolverDpotrf(handle, uplo, n, A, lda, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDpotrf')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverDpotrf
    end interface

    interface
        function hipsolverCpotrf(handle, uplo, n, A, lda, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverCpotrf')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverCpotrf
    end interface

    interface
        function hipsolverZpotrf(handle, uplo, n, A, lda, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZpotrf')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverZpotrf
    end interface
    
    ! ******************** POTRF_BATCHED ********************
    interface
        function hipsolverSpotrfBatched_bufferSize(handle, uplo, n, A, lda, lwork, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverSpotrfBatched_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
            integer(c_int), value :: batch_count
        end function hipsolverSpotrfBatched_bufferSize
    end interface
    
    interface
        function hipsolverDpotrfBatched_bufferSize(handle, uplo, n, A, lda, lwork, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverDpotrfBatched_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
            integer(c_int), value :: batch_count
        end function hipsolverDpotrfBatched_bufferSize
    end interface
    
    interface
        function hipsolverCpotrfBatched_bufferSize(handle, uplo, n, A, lda, lwork, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverCpotrfBatched_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
            integer(c_int), value :: batch_count
        end function hipsolverCpotrfBatched_bufferSize
    end interface
    
    interface
        function hipsolverZpotrfBatched_bufferSize(handle, uplo, n, A, lda, lwork, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverZpotrfBatched_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: lwork
            integer(c_int), value :: batch_count
        end function hipsolverZpotrfBatched_bufferSize
    end interface

    interface
        function hipsolverSpotrfBatched(handle, uplo, n, A, lda, work, lwork, info, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverSpotrfBatched')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
            integer(c_int), value :: batch_count
        end function hipsolverSpotrfBatched
    end interface
    
    interface
        function hipsolverDpotrfBatched(handle, uplo, n, A, lda, work, lwork, info, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverDpotrfBatched')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
            integer(c_int), value :: batch_count
        end function hipsolverDpotrfBatched
    end interface
    
    interface
        function hipsolverCpotrfBatched(handle, uplo, n, A, lda, work, lwork, info, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverCpotrfBatched')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
            integer(c_int), value :: batch_count
        end function hipsolverCpotrfBatched
    end interface
    
    interface
        function hipsolverZpotrfBatched(handle, uplo, n, A, lda, work, lwork, info, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverZpotrfBatched')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
            integer(c_int), value :: batch_count
        end function hipsolverZpotrfBatched
    end interface

    ! ******************** POTRS ********************
    interface
        function hipsolverSpotrs_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSpotrs_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: lwork
        end function hipsolverSpotrs_bufferSize
    end interface
    
    interface
        function hipsolverDpotrs_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDpotrs_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: lwork
        end function hipsolverDpotrs_bufferSize
    end interface
    
    interface
        function hipsolverCpotrs_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverCpotrs_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: lwork
        end function hipsolverCpotrs_bufferSize
    end interface
    
    interface
        function hipsolverZpotrs_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZpotrs_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: lwork
        end function hipsolverZpotrs_bufferSize
    end interface

    interface
        function hipsolverSpotrs(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSpotrs')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverSpotrs
    end interface

    interface
        function hipsolverDpotrs(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDpotrs')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverDpotrs
    end interface

    interface
        function hipsolverCpotrs(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverCpotrs')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverCpotrs
    end interface

    interface
        function hipsolverZpotrs(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZpotrs')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverZpotrs
    end interface

    ! ******************** POTRS_BATCHED ********************
    interface
        function hipsolverSpotrsBatched_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverSpotrsBatched_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: lwork
            integer(c_int), value :: batch_count
        end function hipsolverSpotrsBatched_bufferSize
    end interface
    
    interface
        function hipsolverDpotrsBatched_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverDpotrsBatched_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: lwork
            integer(c_int), value :: batch_count
        end function hipsolverDpotrsBatched_bufferSize
    end interface
    
    interface
        function hipsolverCpotrsBatched_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverCpotrsBatched_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: lwork
            integer(c_int), value :: batch_count
        end function hipsolverCpotrsBatched_bufferSize
    end interface
    
    interface
        function hipsolverZpotrsBatched_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverZpotrsBatched_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: lwork
            integer(c_int), value :: batch_count
        end function hipsolverZpotrsBatched_bufferSize
    end interface

    interface
        function hipsolverSpotrsBatched(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverSpotrsBatched')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
            integer(c_int), value :: batch_count
        end function hipsolverSpotrsBatched
    end interface

    interface
        function hipsolverDpotrsBatched(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverDpotrsBatched')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
            integer(c_int), value :: batch_count
        end function hipsolverDpotrsBatched
    end interface

    interface
        function hipsolverCpotrsBatched(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverCpotrsBatched')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
            integer(c_int), value :: batch_count
        end function hipsolverCpotrsBatched
    end interface

    interface
        function hipsolverZpotrsBatched(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info, batch_count) &
                result(c_int) &
                bind(c, name = 'hipsolverZpotrsBatched')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            integer(c_int), value :: nrhs
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
            integer(c_int), value :: batch_count
        end function hipsolverZpotrsBatched
    end interface

    ! ******************** SYEVD/HEEVD ********************
    interface
        function hipsolverSsyevd_bufferSize(handle, jobz, uplo, n, A, lda, D, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSsyevd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: lwork
        end function hipsolverSsyevd_bufferSize
    end interface
    
    interface
        function hipsolverDsyevd_bufferSize(handle, jobz, uplo, n, A, lda, D, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDsyevd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: lwork
        end function hipsolverDsyevd_bufferSize
    end interface
    
    interface
        function hipsolverCheevd_bufferSize(handle, jobz, uplo, n, A, lda, D, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverCheevd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: lwork
        end function hipsolverCheevd_bufferSize
    end interface
    
    interface
        function hipsolverZheevd_bufferSize(handle, jobz, uplo, n, A, lda, D, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZheevd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: lwork
        end function hipsolverZheevd_bufferSize
    end interface

    interface
        function hipsolverSsyevd(handle, jobz, uplo, n, A, lda, D, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSsyevd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverSsyevd
    end interface

    interface
        function hipsolverDsyevd(handle, jobz, uplo, n, A, lda, D, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDsyevd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverDsyevd
    end interface

    interface
        function hipsolverCheevd(handle, jobz, uplo, n, A, lda, D, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverCheevd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverCheevd
    end interface

    interface
        function hipsolverZheevd(handle, jobz, uplo, n, A, lda, D, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZheevd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverZheevd
    end interface

    ! ******************** SYGVD/HEGVD ********************
    interface
        function hipsolverSsygvd_bufferSize(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSsygvd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_TYPE_1)), value :: itype
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: D
            type(c_ptr), value :: lwork
        end function hipsolverSsygvd_bufferSize
    end interface
    
    interface
        function hipsolverDsygvd_bufferSize(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDsygvd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_TYPE_1)), value :: itype
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: D
            type(c_ptr), value :: lwork
        end function hipsolverDsygvd_bufferSize
    end interface
    
    interface
        function hipsolverChegvd_bufferSize(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverChegvd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_TYPE_1)), value :: itype
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: D
            type(c_ptr), value :: lwork
        end function hipsolverChegvd_bufferSize
    end interface
    
    interface
        function hipsolverZhegvd_bufferSize(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZhegvd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_TYPE_1)), value :: itype
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: D
            type(c_ptr), value :: lwork
        end function hipsolverZhegvd_bufferSize
    end interface

    interface
        function hipsolverSsygvd(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSsygvd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_TYPE_1)), value :: itype
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: D
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverSsygvd
    end interface

    interface
        function hipsolverDsygvd(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDsygvd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_TYPE_1)), value :: itype
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: D
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverDsygvd
    end interface

    interface
        function hipsolverChegvd(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverChegvd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_TYPE_1)), value :: itype
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: D
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverChegvd
    end interface

    interface
        function hipsolverZhegvd(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZhegvd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_EIG_TYPE_1)), value :: itype
            integer(kind(HIPSOLVER_EIG_MODE_NOVECTOR)), value :: jobz
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: B
            integer(c_int), value :: ldb
            type(c_ptr), value :: D
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverZhegvd
    end interface

    ! ******************** SYTRD/HETRD ********************
    interface
        function hipsolverSsytrd_bufferSize(handle, uplo, n, A, lda, D, E, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverSsytrd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: E
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverSsytrd_bufferSize
    end interface
    
    interface
        function hipsolverDsytrd_bufferSize(handle, uplo, n, A, lda, D, E, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverDsytrd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: E
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverDsytrd_bufferSize
    end interface
    
    interface
        function hipsolverChetrd_bufferSize(handle, uplo, n, A, lda, D, E, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverChetrd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: E
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverChetrd_bufferSize
    end interface
    
    interface
        function hipsolverZhetrd_bufferSize(handle, uplo, n, A, lda, D, E, tau, lwork) &
                result(c_int) &
                bind(c, name = 'hipsolverZhetrd_bufferSize')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: E
            type(c_ptr), value :: tau
            type(c_ptr), value :: lwork
        end function hipsolverZhetrd_bufferSize
    end interface

    interface
        function hipsolverSsytrd(handle, uplo, n, A, lda, D, E, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverSsytrd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: E
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverSsytrd
    end interface

    interface
        function hipsolverDsytrd(handle, uplo, n, A, lda, D, E, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverDsytrd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: E
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverDsytrd
    end interface

    interface
        function hipsolverChetrd(handle, uplo, n, A, lda, D, E, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverChetrd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: E
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverChetrd
    end interface

    interface
        function hipsolverZhetrd(handle, uplo, n, A, lda, D, E, tau, work, lwork, info) &
                result(c_int) &
                bind(c, name = 'hipsolverZhetrd')
            use iso_c_binding
            use hipsolver_enums
            implicit none
            type(c_ptr), value :: handle
            integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
            integer(c_int), value :: n
            type(c_ptr), value :: A
            integer(c_int), value :: lda
            type(c_ptr), value :: D
            type(c_ptr), value :: E
            type(c_ptr), value :: tau
            type(c_ptr), value :: work
            integer(c_int), value :: lwork
            type(c_ptr), value :: info
        end function hipsolverZhetrd
    end interface
    
end module hipsolver
