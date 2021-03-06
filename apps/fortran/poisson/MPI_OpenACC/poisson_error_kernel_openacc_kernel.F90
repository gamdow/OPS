!
! auto-generated by ops_fortran.py
!
MODULE POISSON_ERROR_KERNEL_MODULE
USE OPS_FORTRAN_DECLARATIONS
USE OPS_FORTRAN_RT_SUPPORT

USE OPS_CONSTANTS
USE ISO_C_BINDING

INTEGER(KIND=4) xdim1
#define OPS_ACC1(x,y) (x+xdim1*(y)+1)
INTEGER(KIND=4) xdim2
#define OPS_ACC2(x,y) (x+xdim2*(y)+1)


contains

!user function
subroutine poisson_error_kernel(u, ref, err)

  real (kind=8), DIMENSION(1), intent(in):: u, ref
  real (kind=8) :: err

    err = err + (u(OPS_ACC1(0,0))-ref(OPS_ACC2(0,0)))* &
        & (u(OPS_ACC1(0,0))-ref(OPS_ACC2(0,0)))

end subroutine


#undef OPS_ACC1
#undef OPS_ACC2



subroutine poisson_error_kernel_wrap( &
& opsDat1Local, &
& opsDat2Local, &
& opsDat3Local, &
& dat1_base, &
& dat2_base, &
& dat3_base, &
& start, &
& end )
  IMPLICIT NONE
  real(8), INTENT(IN) :: opsDat1Local(*)
  real(8), INTENT(IN) :: opsDat2Local(*)
  real(8) :: opsDat3Local
  integer :: dat1_base
  integer :: dat2_base
  integer :: dat3_base
  integer(4) start(2)
  integer(4) end(2)
  integer n_x, n_y

  !$acc parallel deviceptr(opsDat1Local,opsDat2Local) reduction(+:opsDat3Local)
  !$acc loop reduction(+:opsDat3Local)
  DO n_y = 1, end(2)-start(2)+1
    !$acc loop
    DO n_x = 1, end(1)-start(1)+1
      call poisson_error_kernel( &
      & opsDat1Local(dat1_base+(n_x-1)*1 + (n_y-1)*xdim1*1), &
      & opsDat2Local(dat2_base+(n_x-1)*1 + (n_y-1)*xdim2*1), &
      & opsDat3Local )
    END DO
  END DO
  !$acc end parallel
end subroutine

!host subroutine
subroutine poisson_error_kernel_host( userSubroutine, block, dim, range, &
& opsArg1, &
& opsArg2, &
& opsArg3)
  IMPLICIT NONE
  character(kind=c_char,len=*), INTENT(IN) :: userSubroutine
  type ( ops_block ), INTENT(IN) :: block
  integer(kind=4), INTENT(IN):: dim
  integer(kind=4)   , DIMENSION(dim), INTENT(IN) :: range
  real(kind=8) t1,t2,t3
  real(kind=4) transfer_total, transfer

  type ( ops_arg )  , INTENT(IN) :: opsArg1
  real(8), DIMENSION(:), POINTER :: opsDat1Local
  integer(kind=4) :: opsDat1Cardinality
  integer(kind=4), POINTER, DIMENSION(:)  :: dat1_size
  integer(kind=4) :: dat1_base
  integer ydim1

  type ( ops_arg )  , INTENT(IN) :: opsArg2
  real(8), DIMENSION(:), POINTER :: opsDat2Local
  integer(kind=4) :: opsDat2Cardinality
  integer(kind=4), POINTER, DIMENSION(:)  :: dat2_size
  integer(kind=4) :: dat2_base
  integer ydim2

  type ( ops_arg )  , INTENT(IN) :: opsArg3
  real(8), POINTER, DIMENSION(:) :: opsDat3Local
  integer(kind=4):: dat3_base

  integer n_x, n_y
  integer start(2)
  integer end(2)
  integer(kind=4) :: n

  type ( ops_arg ) , DIMENSION(3) :: opsArgArray

  opsArgArray(1) = opsArg1
  opsArgArray(2) = opsArg2
  opsArgArray(3) = opsArg3

  call setKernelTime(4,userSubroutine//char(0),0.0_8,0.0_8,0.0_4,0)
  call ops_timers_core(t1)

#ifdef OPS_MPI
  IF (getRange(block, start, end, range) < 0) THEN
    return
  ENDIF
#else
  DO n = 1, 2
    start(n) = range(2*n-1)
    end(n) = range(2*n);
  END DO
#endif

  call c_f_pointer(getDatSizeFromOpsArg(opsArg1),dat1_size,(/dim/))
  xdim1 = dat1_size(1)
  ydim1 = dat1_size(2)
  opsDat1Cardinality = opsArg1%dim * xdim1 * ydim1
  dat1_base = getDatBaseFromOpsArg2D(opsArg1,start,1)
  call c_f_pointer(opsArg1%data_d,opsDat1Local,(/opsDat1Cardinality/))

  call c_f_pointer(getDatSizeFromOpsArg(opsArg2),dat2_size,(/dim/))
  xdim2 = dat2_size(1)
  ydim2 = dat2_size(2)
  opsDat2Cardinality = opsArg2%dim * xdim2 * ydim2
  dat2_base = getDatBaseFromOpsArg2D(opsArg2,start,1)
  call c_f_pointer(opsArg2%data_d,opsDat2Local,(/opsDat2Cardinality/))

  call c_f_pointer(getReductionPtrFromOpsArg(opsArg3,block),opsDat3Local, (/opsArg3%dim/))
  dat3_base = 1

  call ops_H_D_exchanges_device(opsArgArray,3)
  call ops_halo_exchanges(opsArgArray,3,range)
  call ops_H_D_exchanges_device(opsArgArray,3)

  call ops_timers_core(t2)

  call poisson_error_kernel_wrap( &
  & opsDat1Local, &
  & opsDat2Local, &
  & opsDat3Local(1), &
  & dat1_base, &
  & dat2_base, &
  & dat3_base, &
  & start, &
  & end )

  call ops_timers_core(t3)
  call ops_set_dirtybit_device(opsArgArray, 3)

  !Timing and data movement
  transfer_total = 0.0_4
  call ops_compute_transfer(2, start, end, opsArg1,transfer)
  transfer_total = transfer_total + transfer
  call ops_compute_transfer(2, start, end, opsArg2,transfer)
  transfer_total = transfer_total + transfer
  call setKernelTime(4,userSubroutine,t3-t2,t2-t1,transfer_total,1)
end subroutine
END MODULE
