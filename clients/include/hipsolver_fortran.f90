! ************************************************************************
!  Copyright 2020 Advanced Micro Devices, Inc.
! ************************************************************************

module hipsolver_interface
    use iso_c_binding
    use hipsolver

    contains

    !------------!
    !   LAPACK   !
    !------------!

    ! ******************** ORGBR/UNGBR ********************
    function hipsolverSorgbr_bufferSizeFortran(handle, side, m, n, k, A, lda, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSorgbr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverSorgbr_bufferSize(handle, side, m, n, k, A, lda, tau, lwork)
    end function hipsolverSorgbr_bufferSizeFortran
    
    function hipsolverDorgbr_bufferSizeFortran(handle, side, m, n, k, A, lda, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDorgbr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverDorgbr_bufferSize(handle, side, m, n, k, A, lda, tau, lwork)
    end function hipsolverDorgbr_bufferSizeFortran
    
    function hipsolverCungbr_bufferSizeFortran(handle, side, m, n, k, A, lda, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverCungbr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverCungbr_bufferSize(handle, side, m, n, k, A, lda, tau, lwork)
    end function hipsolverCungbr_bufferSizeFortran
    
    function hipsolverZungbr_bufferSizeFortran(handle, side, m, n, k, A, lda, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZungbr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverZungbr_bufferSize(handle, side, m, n, k, A, lda, tau, lwork)
    end function hipsolverZungbr_bufferSizeFortran
    
    function hipsolverSorgbrFortran(handle, side, m, n, k, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverSorgbrFortran')
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
        integer(c_int) :: res
        res = hipsolverSorgbr(handle, side, m, n, k, A, lda, tau, work, lwork, info)
    end function hipsolverSorgbrFortran
    
    function hipsolverDorgbrFortran(handle, side, m, n, k, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverDorgbrFortran')
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
        integer(c_int) :: res
        res = hipsolverDorgbr(handle, side, m, n, k, A, lda, tau, work, lwork, info)
    end function hipsolverDorgbrFortran
    
    function hipsolverCungbrFortran(handle, side, m, n, k, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverCungbrFortran')
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
        integer(c_int) :: res
        res = hipsolverCungbr(handle, side, m, n, k, A, lda, tau, work, lwork, info)
    end function hipsolverCungbrFortran
    
    function hipsolverZungbrFortran(handle, side, m, n, k, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverZungbrFortran')
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
        integer(c_int) :: res
        res = hipsolverZungbr(handle, side, m, n, k, A, lda, tau, work, lwork, info)
    end function hipsolverZungbrFortran

    ! ******************** ORGQR/UNGQR ********************
    function hipsolverSorgqr_bufferSizeFortran(handle, m, n, k, A, lda, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSorgqr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverSorgqr_bufferSize(handle, m, n, k, A, lda, tau, lwork)
    end function hipsolverSorgqr_bufferSizeFortran
    
    function hipsolverDorgqr_bufferSizeFortran(handle, m, n, k, A, lda, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDorgqr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverDorgqr_bufferSize(handle, m, n, k, A, lda, tau, lwork)
    end function hipsolverDorgqr_bufferSizeFortran
    
    function hipsolverCungqr_bufferSizeFortran(handle, m, n, k, A, lda, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverCungqr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverCungqr_bufferSize(handle, m, n, k, A, lda, tau, lwork)
    end function hipsolverCungqr_bufferSizeFortran
    
    function hipsolverZungqr_bufferSizeFortran(handle, m, n, k, A, lda, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZungqr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverZungqr_bufferSize(handle, m, n, k, A, lda, tau, lwork)
    end function hipsolverZungqr_bufferSizeFortran
    
    function hipsolverSorgqrFortran(handle, m, n, k, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverSorgqrFortran')
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
        integer(c_int) :: res
        res = hipsolverSorgqr(handle, m, n, k, A, lda, tau, work, lwork, info)
    end function hipsolverSorgqrFortran
    
    function hipsolverDorgqrFortran(handle, m, n, k, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverDorgqrFortran')
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
        integer(c_int) :: res
        res = hipsolverDorgqr(handle, m, n, k, A, lda, tau, work, lwork, info)
    end function hipsolverDorgqrFortran
    
    function hipsolverCungqrFortran(handle, m, n, k, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverCungqrFortran')
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
        integer(c_int) :: res
        res = hipsolverCungqr(handle, m, n, k, A, lda, tau, work, lwork, info)
    end function hipsolverCungqrFortran
    
    function hipsolverZungqrFortran(handle, m, n, k, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverZungqrFortran')
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
        integer(c_int) :: res
        res = hipsolverZungqr(handle, m, n, k, A, lda, tau, work, lwork, info)
    end function hipsolverZungqrFortran

    ! ******************** ORGTR/UNGTR ********************
    function hipsolverSorgtr_bufferSizeFortran(handle, uplo, n, A, lda, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSorgtr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverSorgtr_bufferSize(handle, uplo, n, A, lda, tau, lwork)
    end function hipsolverSorgtr_bufferSizeFortran
    
    function hipsolverDorgtr_bufferSizeFortran(handle, uplo, n, A, lda, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDorgtr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverDorgtr_bufferSize(handle, uplo, n, A, lda, tau, lwork)
    end function hipsolverDorgtr_bufferSizeFortran
    
    function hipsolverCungtr_bufferSizeFortran(handle, uplo, n, A, lda, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverCungtr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverCungtr_bufferSize(handle, uplo, n, A, lda, tau, lwork)
    end function hipsolverCungtr_bufferSizeFortran
    
    function hipsolverZungtr_bufferSizeFortran(handle, uplo, n, A, lda, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZungtr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverZungtr_bufferSize(handle, uplo, n, A, lda, tau, lwork)
    end function hipsolverZungtr_bufferSizeFortran
    
    function hipsolverSorgtrFortran(handle, uplo, n, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverSorgtrFortran')
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
        integer(c_int) :: res
        res = hipsolverSorgtr(handle, uplo, n, A, lda, tau, work, lwork, info)
    end function hipsolverSorgtrFortran
    
    function hipsolverDorgtrFortran(handle, uplo, n, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverDorgtrFortran')
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
        integer(c_int) :: res
        res = hipsolverDorgtr(handle, uplo, n, A, lda, tau, work, lwork, info)
    end function hipsolverDorgtrFortran
    
    function hipsolverCungtrFortran(handle, uplo, n, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverCungtrFortran')
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
        integer(c_int) :: res
        res = hipsolverCungtr(handle, uplo, n, A, lda, tau, work, lwork, info)
    end function hipsolverCungtrFortran
    
    function hipsolverZungtrFortran(handle, uplo, n, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverZungtrFortran')
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
        integer(c_int) :: res
        res = hipsolverZungtr(handle, uplo, n, A, lda, tau, work, lwork, info)
    end function hipsolverZungtrFortran

    ! ******************** ORMQR/UNMQR ********************
    function hipsolverSormqr_bufferSizeFortran(handle, side, trans, m, n, k, A, lda, tau, C, ldc, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSormqr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverSormqr_bufferSize(handle, side, trans, m, n, k, A, lda, tau, C, ldc, lwork)
    end function hipsolverSormqr_bufferSizeFortran
    
    function hipsolverDormqr_bufferSizeFortran(handle, side, trans, m, n, k, A, lda, tau, C, ldc, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDormqr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverDormqr_bufferSize(handle, side, trans, m, n, k, A, lda, tau, C, ldc, lwork)
    end function hipsolverDormqr_bufferSizeFortran
    
    function hipsolverCunmqr_bufferSizeFortran(handle, side, trans, m, n, k, A, lda, tau, C, ldc, lwork) &
            result(res) &
            bind(c, name = 'hipsolverCunmqr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverCunmqr_bufferSize(handle, side, trans, m, n, k, A, lda, tau, C, ldc, lwork)
    end function hipsolverCunmqr_bufferSizeFortran
    
    function hipsolverZunmqr_bufferSizeFortran(handle, side, trans, m, n, k, A, lda, tau, C, ldc, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZunmqr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverZunmqr_bufferSize(handle, side, trans, m, n, k, A, lda, tau, C, ldc, lwork)
    end function hipsolverZunmqr_bufferSizeFortran
    
    function hipsolverSormqrFortran(handle, side, trans, m, n, k, A, lda, tau, C, ldc, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverSormqrFortran')
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
        integer(c_int) :: res
        res = hipsolverSormqr(handle, side, trans, m, n, k, A, lda, tau, C, ldc, work, lwork, info)
    end function hipsolverSormqrFortran
    
    function hipsolverDormqrFortran(handle, side, trans, m, n, k, A, lda, tau, C, ldc, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverDormqrFortran')
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
        integer(c_int) :: res
        res = hipsolverDormqr(handle, side, trans, m, n, k, A, lda, tau, C, ldc, work, lwork, info)
    end function hipsolverDormqrFortran
    
    function hipsolverCunmqrFortran(handle, side, trans, m, n, k, A, lda, tau, C, ldc, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverCunmqrFortran')
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
        integer(c_int) :: res
        res = hipsolverCunmqr(handle, side, trans, m, n, k, A, lda, tau, C, ldc, work, lwork, info)
    end function hipsolverCunmqrFortran
    
    function hipsolverZunmqrFortran(handle, side, trans, m, n, k, A, lda, tau, C, ldc, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverZunmqrFortran')
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
        integer(c_int) :: res
        res = hipsolverZunmqr(handle, side, trans, m, n, k, A, lda, tau, C, ldc, work, lwork, info)
    end function hipsolverZunmqrFortran

    ! ******************** ORMTR/UNMTR ********************
    function hipsolverSormtr_bufferSizeFortran(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSormtr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverSormtr_bufferSize(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, lwork)
    end function hipsolverSormtr_bufferSizeFortran
    
    function hipsolverDormtr_bufferSizeFortran(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDormtr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverDormtr_bufferSize(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, lwork)
    end function hipsolverDormtr_bufferSizeFortran
    
    function hipsolverCunmtr_bufferSizeFortran(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, lwork) &
            result(res) &
            bind(c, name = 'hipsolverCunmtr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverCunmtr_bufferSize(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, lwork)
    end function hipsolverCunmtr_bufferSizeFortran
    
    function hipsolverZunmtr_bufferSizeFortran(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZunmtr_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverZunmtr_bufferSize(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, lwork)
    end function hipsolverZunmtr_bufferSizeFortran
    
    function hipsolverSormtrFortran(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverSormtrFortran')
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
        integer(c_int) :: res
        res = hipsolverSormtr(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, work, lwork, info)
    end function hipsolverSormtrFortran
    
    function hipsolverDormtrFortran(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverDormtrFortran')
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
        integer(c_int) :: res
        res = hipsolverDormtr(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, work, lwork, info)
    end function hipsolverDormtrFortran
    
    function hipsolverCunmtrFortran(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverCunmtrFortran')
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
        integer(c_int) :: res
        res = hipsolverCunmtr(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, work, lwork, info)
    end function hipsolverCunmtrFortran
    
    function hipsolverZunmtrFortran(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverZunmtrFortran')
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
        integer(c_int) :: res
        res = hipsolverZunmtr(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, work, lwork, info)
    end function hipsolverZunmtrFortran

    ! ******************** GEBRD ********************
    function hipsolverSgebrd_bufferSizeFortran(handle, m, n, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSgebrd_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverSgebrd_bufferSize(handle, m, n, lwork)
    end function hipsolverSgebrd_bufferSizeFortran
    
    function hipsolverDgebrd_bufferSizeFortran(handle, m, n, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDgebrd_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverDgebrd_bufferSize(handle, m, n, lwork)
    end function hipsolverDgebrd_bufferSizeFortran
    
    function hipsolverCgebrd_bufferSizeFortran(handle, m, n, lwork) &
            result(res) &
            bind(c, name = 'hipsolverCgebrd_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverCgebrd_bufferSize(handle, m, n, lwork)
    end function hipsolverCgebrd_bufferSizeFortran
    
    function hipsolverZgebrd_bufferSizeFortran(handle, m, n, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZgebrd_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverZgebrd_bufferSize(handle, m, n, lwork)
    end function hipsolverZgebrd_bufferSizeFortran

    function hipsolverSgebrdFortran(handle, m, n, A, lda, D, E, tauq, taup, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverSgebrdFortran')
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
        integer(c_int) :: res
        res = hipsolverSgebrd(handle, m, n, A, lda, D, E, tauq, taup, work, lwork, info)
    end function hipsolverSgebrdFortran

    function hipsolverDgebrdFortran(handle, m, n, A, lda, D, E, tauq, taup, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverDgebrdFortran')
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
        integer(c_int) :: res
        res = hipsolverDgebrd(handle, m, n, A, lda, D, E, tauq, taup, work, lwork, info)
    end function hipsolverDgebrdFortran

    function hipsolverCgebrdFortran(handle, m, n, A, lda, D, E, tauq, taup, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverCgebrdFortran')
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
        integer(c_int) :: res
        res = hipsolverCgebrd(handle, m, n, A, lda, D, E, tauq, taup, work, lwork, info)
    end function hipsolverCgebrdFortran

    function hipsolverZgebrdFortran(handle, m, n, A, lda, D, E, tauq, taup, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverZgebrdFortran')
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
        integer(c_int) :: res
        res = hipsolverZgebrd(handle, m, n, A, lda, D, E, tauq, taup, work, lwork, info)
    end function hipsolverZgebrdFortran

    ! ******************** GEQRF ********************
    function hipsolverSgeqrf_bufferSizeFortran(handle, m, n, A, lda, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSgeqrf_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: A
        integer(c_int), value :: lda
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverSgeqrf_bufferSize(handle, m, n, A, lda, lwork)
    end function hipsolverSgeqrf_bufferSizeFortran
    
    function hipsolverDgeqrf_bufferSizeFortran(handle, m, n, A, lda, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDgeqrf_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: A
        integer(c_int), value :: lda
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverDgeqrf_bufferSize(handle, m, n, A, lda, lwork)
    end function hipsolverDgeqrf_bufferSizeFortran
    
    function hipsolverCgeqrf_bufferSizeFortran(handle, m, n, A, lda, lwork) &
            result(res) &
            bind(c, name = 'hipsolverCgeqrf_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: A
        integer(c_int), value :: lda
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverCgeqrf_bufferSize(handle, m, n, A, lda, lwork)
    end function hipsolverCgeqrf_bufferSizeFortran
    
    function hipsolverZgeqrf_bufferSizeFortran(handle, m, n, A, lda, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZgeqrf_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: A
        integer(c_int), value :: lda
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverZgeqrf_bufferSize(handle, m, n, A, lda, lwork)
    end function hipsolverZgeqrf_bufferSizeFortran

    function hipsolverSgeqrfFortran(handle, m, n, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverSgeqrfFortran')
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
        integer(c_int) :: res
        res = hipsolverSgeqrf(handle, m, n, A, lda, tau, work, lwork, info)
    end function hipsolverSgeqrfFortran

    function hipsolverDgeqrfFortran(handle, m, n, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverDgeqrfFortran')
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
        integer(c_int) :: res
        res = hipsolverDgeqrf(handle, m, n, A, lda, tau, work, lwork, info)
    end function hipsolverDgeqrfFortran

    function hipsolverCgeqrfFortran(handle, m, n, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverCgeqrfFortran')
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
        integer(c_int) :: res
        res = hipsolverCgeqrf(handle, m, n, A, lda, tau, work, lwork, info)
    end function hipsolverCgeqrfFortran

    function hipsolverZgeqrfFortran(handle, m, n, A, lda, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverZgeqrfFortran')
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
        integer(c_int) :: res
        res = hipsolverZgeqrf(handle, m, n, A, lda, tau, work, lwork, info)
    end function hipsolverZgeqrfFortran

    ! ******************** GESVD ********************
    function hipsolverSgesvd_bufferSizeFortran(handle, jobu, jobv, m, n, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSgesvd_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_signed_char), value :: jobu
        integer(c_signed_char), value :: jobv
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverSgesvd_bufferSize(handle, jobu, jobv, m, n, lwork)
    end function hipsolverSgesvd_bufferSizeFortran
    
    function hipsolverDgesvd_bufferSizeFortran(handle, jobu, jobv, m, n, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDgesvd_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_signed_char), value :: jobu
        integer(c_signed_char), value :: jobv
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverDgesvd_bufferSize(handle, jobu, jobv, m, n, lwork)
    end function hipsolverDgesvd_bufferSizeFortran
    
    function hipsolverCgesvd_bufferSizeFortran(handle, jobu, jobv, m, n, lwork) &
            result(res) &
            bind(c, name = 'hipsolverCgesvd_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_signed_char), value :: jobu
        integer(c_signed_char), value :: jobv
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverCgesvd_bufferSize(handle, jobu, jobv, m, n, lwork)
    end function hipsolverCgesvd_bufferSizeFortran
    
    function hipsolverZgesvd_bufferSizeFortran(handle, jobu, jobv, m, n, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZgesvd_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_signed_char), value :: jobu
        integer(c_signed_char), value :: jobv
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverZgesvd_bufferSize(handle, jobu, jobv, m, n, lwork)
    end function hipsolverZgesvd_bufferSizeFortran

    function hipsolverSgesvdFortran(handle, jobu, jobv, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, rwork, info) &
            result(res) &
            bind(c, name = 'hipsolverSgesvdFortran')
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
        integer(c_int) :: res
        res = hipsolverSgesvd(handle, jobu, jobv, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, rwork, info)
    end function hipsolverSgesvdFortran

    function hipsolverDgesvdFortran(handle, jobu, jobv, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, rwork, info) &
            result(res) &
            bind(c, name = 'hipsolverDgesvdFortran')
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
        integer(c_int) :: res
        res = hipsolverDgesvd(handle, jobu, jobv, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, rwork, info)
    end function hipsolverDgesvdFortran

    function hipsolverCgesvdFortran(handle, jobu, jobv, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, rwork, info) &
            result(res) &
            bind(c, name = 'hipsolverCgesvdFortran')
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
        integer(c_int) :: res
        res = hipsolverCgesvd(handle, jobu, jobv, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, rwork, info)
    end function hipsolverCgesvdFortran

    function hipsolverZgesvdFortran(handle, jobu, jobv, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, rwork, info) &
            result(res) &
            bind(c, name = 'hipsolverZgesvdFortran')
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
        integer(c_int) :: res
        res = hipsolverZgesvd(handle, jobu, jobv, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, rwork, info)
    end function hipsolverZgesvdFortran

    ! ******************** GETRF ********************
    function hipsolverSgetrf_bufferSizeFortran(handle, m, n, A, lda, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSgetrf_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: A
        integer(c_int), value :: lda
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverSgetrf_bufferSize(handle, m, n, A, lda, lwork)
    end function hipsolverSgetrf_bufferSizeFortran
    
    function hipsolverDgetrf_bufferSizeFortran(handle, m, n, A, lda, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDgetrf_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: A
        integer(c_int), value :: lda
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverDgetrf_bufferSize(handle, m, n, A, lda, lwork)
    end function hipsolverDgetrf_bufferSizeFortran
    
    function hipsolverCgetrf_bufferSizeFortran(handle, m, n, A, lda, lwork) &
            result(res) &
            bind(c, name = 'hipsolverCgetrf_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: A
        integer(c_int), value :: lda
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverCgetrf_bufferSize(handle, m, n, A, lda, lwork)
    end function hipsolverCgetrf_bufferSizeFortran
    
    function hipsolverZgetrf_bufferSizeFortran(handle, m, n, A, lda, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZgetrf_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(c_int), value :: m
        integer(c_int), value :: n
        type(c_ptr), value :: A
        integer(c_int), value :: lda
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverZgetrf_bufferSize(handle, m, n, A, lda, lwork)
    end function hipsolverZgetrf_bufferSizeFortran

    function hipsolverSgetrfFortran(handle, m, n, A, lda, work, lwork, ipiv, info) &
            result(res) &
            bind(c, name = 'hipsolverSgetrfFortran')
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
        integer(c_int) :: res
        res = hipsolverSgetrf(handle, m, n, A, lda, work, lwork, ipiv, info)
    end function hipsolverSgetrfFortran
    
    function hipsolverDgetrfFortran(handle, m, n, A, lda, work, lwork, ipiv, info) &
            result(res) &
            bind(c, name = 'hipsolverDgetrfFortran')
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
        integer(c_int) :: res
        res = hipsolverDgetrf(handle, m, n, A, lda, work, lwork, ipiv, info)
    end function hipsolverDgetrfFortran
    
    function hipsolverCgetrfFortran(handle, m, n, A, lda, work, lwork, ipiv, info) &
            result(res) &
            bind(c, name = 'hipsolverCgetrfFortran')
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
        integer(c_int) :: res
        res = hipsolverCgetrf(handle, m, n, A, lda, work, lwork, ipiv, info)
    end function hipsolverCgetrfFortran

    function hipsolverZgetrfFortran(handle, m, n, A, lda, work, lwork, ipiv, info) &
            result(res) &
            bind(c, name = 'hipsolverZgetrfFortran')
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
        integer(c_int) :: res
        res = hipsolverZgetrf(handle, m, n, A, lda, work, lwork, ipiv, info)
    end function hipsolverZgetrfFortran
    
    ! ******************** GETRS ********************
    function hipsolverSgetrs_bufferSizeFortran(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSgetrs_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverSgetrs_bufferSize(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, lwork)
    end function hipsolverSgetrs_bufferSizeFortran
    
    function hipsolverDgetrs_bufferSizeFortran(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDgetrs_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverDgetrs_bufferSize(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, lwork)
    end function hipsolverDgetrs_bufferSizeFortran
    
    function hipsolverCgetrs_bufferSizeFortran(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, lwork) &
            result(res) &
            bind(c, name = 'hipsolverCgetrs_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverCgetrs_bufferSize(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, lwork)
    end function hipsolverCgetrs_bufferSizeFortran
    
    function hipsolverZgetrs_bufferSizeFortran(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZgetrs_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverZgetrs_bufferSize(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, lwork)
    end function hipsolverZgetrs_bufferSizeFortran

    function hipsolverSgetrsFortran(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverSgetrsFortran')
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
        integer(c_int) :: res
        res = hipsolverSgetrs(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, work, lwork, info)
    end function hipsolverSgetrsFortran
    
    function hipsolverDgetrsFortran(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverDgetrsFortran')
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
        integer(c_int) :: res
        res = hipsolverDgetrs(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, work, lwork, info)
    end function hipsolverDgetrsFortran
    
    function hipsolverCgetrsFortran(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverCgetrsFortran')
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
        integer(c_int) :: res
        res = hipsolverCgetrs(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, work, lwork, info)
    end function hipsolverCgetrsFortran
    
    function hipsolverZgetrsFortran(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverZgetrsFortran')
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
        integer(c_int) :: res
        res = hipsolverZgetrs(handle, trans, n, nrhs, A, lda, ipiv, B, ldb, work, lwork, info)
    end function hipsolverZgetrsFortran

    ! ******************** POTRF ********************
    function hipsolverSpotrf_bufferSizeFortran(handle, uplo, n, A, lda, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSpotrf_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
        integer(c_int), value :: n
        type(c_ptr), value :: A
        integer(c_int), value :: lda
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverSpotrf_bufferSize(handle, uplo, n, A, lda, lwork)
    end function hipsolverSpotrf_bufferSizeFortran
    
    function hipsolverDpotrf_bufferSizeFortran(handle, uplo, n, A, lda, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDpotrf_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
        integer(c_int), value :: n
        type(c_ptr), value :: A
        integer(c_int), value :: lda
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverDpotrf_bufferSize(handle, uplo, n, A, lda, lwork)
    end function hipsolverDpotrf_bufferSizeFortran
    
    function hipsolverCpotrf_bufferSizeFortran(handle, uplo, n, A, lda, lwork) &
            result(res) &
            bind(c, name = 'hipsolverCpotrf_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
        integer(c_int), value :: n
        type(c_ptr), value :: A
        integer(c_int), value :: lda
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverCpotrf_bufferSize(handle, uplo, n, A, lda, lwork)
    end function hipsolverCpotrf_bufferSizeFortran
    
    function hipsolverZpotrf_bufferSizeFortran(handle, uplo, n, A, lda, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZpotrf_bufferSizeFortran')
        use iso_c_binding
        use hipsolver_enums
        implicit none
        type(c_ptr), value :: handle
        integer(kind(HIPSOLVER_FILL_MODE_LOWER)), value :: uplo
        integer(c_int), value :: n
        type(c_ptr), value :: A
        integer(c_int), value :: lda
        type(c_ptr), value :: lwork
        integer(c_int) :: res
        res = hipsolverZpotrf_bufferSize(handle, uplo, n, A, lda, lwork)
    end function hipsolverZpotrf_bufferSizeFortran

    function hipsolverSpotrfFortran(handle, uplo, n, A, lda, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverSpotrfFortran')
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
        integer(c_int) :: res
        res = hipsolverSpotrf(handle, uplo, n, A, lda, work, lwork, info)
    end function hipsolverSpotrfFortran

    function hipsolverDpotrfFortran(handle, uplo, n, A, lda, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverDpotrfFortran')
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
        integer(c_int) :: res
        res = hipsolverDpotrf(handle, uplo, n, A, lda, work, lwork, info)
    end function hipsolverDpotrfFortran

    function hipsolverCpotrfFortran(handle, uplo, n, A, lda, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverCpotrfFortran')
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
        integer(c_int) :: res
        res = hipsolverCpotrf(handle, uplo, n, A, lda, work, lwork, info)
    end function hipsolverCpotrfFortran

    function hipsolverZpotrfFortran(handle, uplo, n, A, lda, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverZpotrfFortran')
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
        integer(c_int) :: res
        res = hipsolverZpotrf(handle, uplo, n, A, lda, work, lwork, info)
    end function hipsolverZpotrfFortran
    
    ! ******************** POTRF_BATCHED ********************
    function hipsolverSpotrfBatched_bufferSizeFortran(handle, uplo, n, A, lda, lwork, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverSpotrfBatched_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverSpotrfBatched_bufferSize(handle, uplo, n, A, lda, lwork, batch_count)
    end function hipsolverSpotrfBatched_bufferSizeFortran
    
    function hipsolverDpotrfBatched_bufferSizeFortran(handle, uplo, n, A, lda, lwork, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverDpotrfBatched_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverDpotrfBatched_bufferSize(handle, uplo, n, A, lda, lwork, batch_count)
    end function hipsolverDpotrfBatched_bufferSizeFortran
    
    function hipsolverCpotrfBatched_bufferSizeFortran(handle, uplo, n, A, lda, lwork, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverCpotrfBatched_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverCpotrfBatched_bufferSize(handle, uplo, n, A, lda, lwork, batch_count)
    end function hipsolverCpotrfBatched_bufferSizeFortran
    
    function hipsolverZpotrfBatched_bufferSizeFortran(handle, uplo, n, A, lda, lwork, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverZpotrfBatched_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverZpotrfBatched_bufferSize(handle, uplo, n, A, lda, lwork, batch_count)
    end function hipsolverZpotrfBatched_bufferSizeFortran

    function hipsolverSpotrfBatchedFortran(handle, uplo, n, A, lda, work, lwork, info, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverSpotrfBatchedFortran')
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
        integer(c_int) :: res
        res = hipsolverSpotrfBatched(handle, uplo, n, A, lda, work, lwork, info, batch_count)
    end function hipsolverSpotrfBatchedFortran
    
    function hipsolverDpotrfBatchedFortran(handle, uplo, n, A, lda, work, lwork, info, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverDpotrfBatchedFortran')
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
        integer(c_int) :: res
        res = hipsolverDpotrfBatched(handle, uplo, n, A, lda, work, lwork, info, batch_count)
    end function hipsolverDpotrfBatchedFortran
    
    function hipsolverCpotrfBatchedFortran(handle, uplo, n, A, lda, work, lwork, info, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverCpotrfBatchedFortran')
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
        integer(c_int) :: res
        res = hipsolverCpotrfBatched(handle, uplo, n, A, lda, work, lwork, info, batch_count)
    end function hipsolverCpotrfBatchedFortran
    
    function hipsolverZpotrfBatchedFortran(handle, uplo, n, A, lda, work, lwork, info, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverZpotrfBatchedFortran')
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
        integer(c_int) :: res
        res = hipsolverZpotrfBatched(handle, uplo, n, A, lda, work, lwork, info, batch_count)
    end function hipsolverZpotrfBatchedFortran

    ! ******************** POTRS ********************
    function hipsolverSpotrs_bufferSizeFortran(handle, uplo, n, nrhs, A, lda, B, ldb, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSpotrs_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverSpotrs_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork)
    end function hipsolverSpotrs_bufferSizeFortran
    
    function hipsolverDpotrs_bufferSizeFortran(handle, uplo, n, nrhs, A, lda, B, ldb, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDpotrs_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverDpotrs_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork)
    end function hipsolverDpotrs_bufferSizeFortran
    
    function hipsolverCpotrs_bufferSizeFortran(handle, uplo, n, nrhs, A, lda, B, ldb, lwork) &
            result(res) &
            bind(c, name = 'hipsolverCpotrs_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverCpotrs_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork)
    end function hipsolverCpotrs_bufferSizeFortran
    
    function hipsolverZpotrs_bufferSizeFortran(handle, uplo, n, nrhs, A, lda, B, ldb, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZpotrs_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverZpotrs_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork)
    end function hipsolverZpotrs_bufferSizeFortran

    function hipsolverSpotrsFortran(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverSpotrsFortran')
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
        integer(c_int) :: res
        res = hipsolverSpotrs(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info)
    end function hipsolverSpotrsFortran

    function hipsolverDpotrsFortran(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverDpotrsFortran')
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
        integer(c_int) :: res
        res = hipsolverDpotrs(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info)
    end function hipsolverDpotrsFortran

    function hipsolverCpotrsFortran(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverCpotrsFortran')
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
        integer(c_int) :: res
        res = hipsolverCpotrs(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info)
    end function hipsolverCpotrsFortran

    function hipsolverZpotrsFortran(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverZpotrsFortran')
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
        integer(c_int) :: res
        res = hipsolverZpotrs(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info)
    end function hipsolverZpotrsFortran

    ! ******************** POTRS_BATCHED ********************
    function hipsolverSpotrsBatched_bufferSizeFortran(handle, uplo, n, nrhs, A, lda, B, ldb, lwork, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverSpotrsBatched_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverSpotrsBatched_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork, batch_count)
    end function hipsolverSpotrsBatched_bufferSizeFortran
    
    function hipsolverDpotrsBatched_bufferSizeFortran(handle, uplo, n, nrhs, A, lda, B, ldb, lwork, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverDpotrsBatched_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverDpotrsBatched_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork, batch_count)
    end function hipsolverDpotrsBatched_bufferSizeFortran
    
    function hipsolverCpotrsBatched_bufferSizeFortran(handle, uplo, n, nrhs, A, lda, B, ldb, lwork, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverCpotrsBatched_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverCpotrsBatched_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork, batch_count)
    end function hipsolverCpotrsBatched_bufferSizeFortran
    
    function hipsolverZpotrsBatched_bufferSizeFortran(handle, uplo, n, nrhs, A, lda, B, ldb, lwork, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverZpotrsBatched_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverZpotrsBatched_bufferSize(handle, uplo, n, nrhs, A, lda, B, ldb, lwork, batch_count)
    end function hipsolverZpotrsBatched_bufferSizeFortran

    function hipsolverSpotrsBatchedFortran(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverSpotrsBatchedFortran')
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
        integer(c_int) :: res
        res = hipsolverSpotrsBatched(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info, batch_count)
    end function hipsolverSpotrsBatchedFortran

    function hipsolverDpotrsBatchedFortran(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverDpotrsBatchedFortran')
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
        integer(c_int) :: res
        res = hipsolverDpotrsBatched(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info, batch_count)
    end function hipsolverDpotrsBatchedFortran

    function hipsolverCpotrsBatchedFortran(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverCpotrsBatchedFortran')
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
        integer(c_int) :: res
        res = hipsolverCpotrsBatched(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info, batch_count)
    end function hipsolverCpotrsBatchedFortran

    function hipsolverZpotrsBatchedFortran(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info, batch_count) &
            result(res) &
            bind(c, name = 'hipsolverZpotrsBatchedFortran')
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
        integer(c_int) :: res
        res = hipsolverZpotrsBatched(handle, uplo, n, nrhs, A, lda, B, ldb, work, lwork, info, batch_count)
    end function hipsolverZpotrsBatchedFortran

    ! ******************** SYEVD/HEEVD ********************
    function hipsolverSsyevd_bufferSizeFortran(handle, jobz, uplo, n, A, lda, D, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSsyevd_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverSsyevd_bufferSize(handle, jobz, uplo, n, A, lda, D, lwork)
    end function hipsolverSsyevd_bufferSizeFortran
    
    function hipsolverDsyevd_bufferSizeFortran(handle, jobz, uplo, n, A, lda, D, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDsyevd_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverDsyevd_bufferSize(handle, jobz, uplo, n, A, lda, D, lwork)
    end function hipsolverDsyevd_bufferSizeFortran
    
    function hipsolverCheevd_bufferSizeFortran(handle, jobz, uplo, n, A, lda, D, lwork) &
            result(res) &
            bind(c, name = 'hipsolverCheevd_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverCheevd_bufferSize(handle, jobz, uplo, n, A, lda, D, lwork)
    end function hipsolverCheevd_bufferSizeFortran
    
    function hipsolverZheevd_bufferSizeFortran(handle, jobz, uplo, n, A, lda, D, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZheevd_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverZheevd_bufferSize(handle, jobz, uplo, n, A, lda, D, lwork)
    end function hipsolverZheevd_bufferSizeFortran

    function hipsolverSsyevdFortran(handle, jobz, uplo, n, A, lda, D, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverSsyevdFortran')
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
        integer(c_int) :: res
        res = hipsolverSsyevd(handle, jobz, uplo, n, A, lda, D, work, lwork, info)
    end function hipsolverSsyevdFortran

    function hipsolverDsyevdFortran(handle, jobz, uplo, n, A, lda, D, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverDsyevdFortran')
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
        integer(c_int) :: res
        res = hipsolverDsyevd(handle, jobz, uplo, n, A, lda, D, work, lwork, info)
    end function hipsolverDsyevdFortran

    function hipsolverCheevdFortran(handle, jobz, uplo, n, A, lda, D, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverCheevdFortran')
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
        integer(c_int) :: res
        res = hipsolverCheevd(handle, jobz, uplo, n, A, lda, D, work, lwork, info)
    end function hipsolverCheevdFortran

    function hipsolverZheevdFortran(handle, jobz, uplo, n, A, lda, D, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverZheevdFortran')
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
        integer(c_int) :: res
        res = hipsolverZheevd(handle, jobz, uplo, n, A, lda, D, work, lwork, info)
    end function hipsolverZheevdFortran

    ! ******************** SYGVD/HEGVD ********************
    function hipsolverSsygvd_bufferSizeFortran(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSsygvd_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverSsygvd_bufferSize(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, lwork)
    end function hipsolverSsygvd_bufferSizeFortran
    
    function hipsolverDsygvd_bufferSizeFortran(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDsygvd_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverDsygvd_bufferSize(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, lwork)
    end function hipsolverDsygvd_bufferSizeFortran
    
    function hipsolverChegvd_bufferSizeFortran(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, lwork) &
            result(res) &
            bind(c, name = 'hipsolverChegvd_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverChegvd_bufferSize(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, lwork)
    end function hipsolverChegvd_bufferSizeFortran
    
    function hipsolverZhegvd_bufferSizeFortran(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZhegvd_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverZhegvd_bufferSize(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, lwork)
    end function hipsolverZhegvd_bufferSizeFortran

    function hipsolverSsygvdFortran(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverSsygvdFortran')
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
        integer(c_int) :: res
        res = hipsolverSsygvd(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, work, lwork, info)
    end function hipsolverSsygvdFortran

    function hipsolverDsygvdFortran(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverDsygvdFortran')
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
        integer(c_int) :: res
        res = hipsolverDsygvd(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, work, lwork, info)
    end function hipsolverDsygvdFortran

    function hipsolverChegvdFortran(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverChegvdFortran')
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
        integer(c_int) :: res
        res = hipsolverChegvd(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, work, lwork, info)
    end function hipsolverChegvdFortran

    function hipsolverZhegvdFortran(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverZhegvdFortran')
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
        integer(c_int) :: res
        res = hipsolverZhegvd(handle, itype, jobz, uplo, n, A, lda, B, ldb, D, work, lwork, info)
    end function hipsolverZhegvdFortran

    ! ******************** SYTRD/HETRD ********************
    function hipsolverSsytrd_bufferSizeFortran(handle, uplo, n, A, lda, D, E, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverSsytrd_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverSsytrd_bufferSize(handle, uplo, n, A, lda, D, E, tau, lwork)
    end function hipsolverSsytrd_bufferSizeFortran
    
    function hipsolverDsytrd_bufferSizeFortran(handle, uplo, n, A, lda, D, E, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverDsytrd_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverDsytrd_bufferSize(handle, uplo, n, A, lda, D, E, tau, lwork)
    end function hipsolverDsytrd_bufferSizeFortran
    
    function hipsolverChetrd_bufferSizeFortran(handle, uplo, n, A, lda, D, E, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverChetrd_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverChetrd_bufferSize(handle, uplo, n, A, lda, D, E, tau, lwork)
    end function hipsolverChetrd_bufferSizeFortran
    
    function hipsolverZhetrd_bufferSizeFortran(handle, uplo, n, A, lda, D, E, tau, lwork) &
            result(res) &
            bind(c, name = 'hipsolverZhetrd_bufferSizeFortran')
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
        integer(c_int) :: res
        res = hipsolverZhetrd_bufferSize(handle, uplo, n, A, lda, D, E, tau, lwork)
    end function hipsolverZhetrd_bufferSizeFortran

    function hipsolverSsytrdFortran(handle, uplo, n, A, lda, D, E, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverSsytrdFortran')
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
        integer(c_int) :: res
        res = hipsolverSsytrd(handle, uplo, n, A, lda, D, E, tau, work, lwork, info)
    end function hipsolverSsytrdFortran

    function hipsolverDsytrdFortran(handle, uplo, n, A, lda, D, E, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverDsytrdFortran')
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
        integer(c_int) :: res
        res = hipsolverDsytrd(handle, uplo, n, A, lda, D, E, tau, work, lwork, info)
    end function hipsolverDsytrdFortran

    function hipsolverChetrdFortran(handle, uplo, n, A, lda, D, E, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverChetrdFortran')
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
        integer(c_int) :: res
        res = hipsolverChetrd(handle, uplo, n, A, lda, D, E, tau, work, lwork, info)
    end function hipsolverChetrdFortran

    function hipsolverZhetrdFortran(handle, uplo, n, A, lda, D, E, tau, work, lwork, info) &
            result(res) &
            bind(c, name = 'hipsolverZhetrdFortran')
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
        integer(c_int) :: res
        res = hipsolverZhetrd(handle, uplo, n, A, lda, D, E, tau, work, lwork, info)
    end function hipsolverZhetrdFortran
    
end module hipsolver_interface
