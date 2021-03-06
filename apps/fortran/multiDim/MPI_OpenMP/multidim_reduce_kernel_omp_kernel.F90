!
! auto-generated by ops_fortran.py
!
MODULE MULTIDIM_REDUCE_KERNEL_MODULE
USE OPS_FORTRAN_DECLARATIONS
USE OPS_FORTRAN_RT_SUPPORT

USE OPS_CONSTANTS
USE ISO_C_BINDING


INTEGER(KIND=4) multi_d1
INTEGER(KIND=4) xdim1
INTEGER(KIND=4) ydim1
#define OPS_ACC_MD1(d,x,y) ((x)*2+(d)+(xdim1*(y)*2))

contains

!user function
!DEC$ ATTRIBUTES FORCEINLINE :: multidim_reduce_kernel
subroutine multidim_reduce_kernel(val, redu_dat1)
  IMPLICIT NONE
  REAL   (kind=8), DIMENSION(2), INTENT(IN) :: val
  REAL(kind=8), DIMENSION(2) :: redu_dat1
  redu_dat1(1) = redu_dat1(1) + val(OPS_ACC_MD1(1,0,0))
  redu_dat1(2) = redu_dat1(2) + val(OPS_ACC_MD1(2,0,0))
end subroutine



#undef OPS_ACC_MD1


subroutine multidim_reduce_kernel_wrap( &
& opsDat1Local, &
& opsDat2Local, &
& dat1_base, &
& dat2_base, &
& start, &
& end )
  IMPLICIT NONE
  real(8), INTENT(IN) :: opsDat1Local(*)
  real(8) opsDat2Local(2)
  integer dat1_base
  integer dat2_base
  integer(4) start(2)
  integer(4) end(2)
  integer n_x, n_y

  !$OMP PARALLEL DO PRIVATE(n_x) REDUCTION(+:opsDat2Local)
  DO n_y = 1, end(2)-start(2)+1
    !DIR$ IVDEP
    DO n_x = 1, end(1)-start(1)+1
      call multidim_reduce_kernel( &
      & opsDat1Local(dat1_base+(n_x-1)*2 + (n_y-1)*xdim1*2), &
      & opsDat2Local(dat2_base) )
    END DO
  END DO
end subroutine

!host subroutine
subroutine multidim_reduce_kernel_host( userSubroutine, block, dim, range, &
& opsArg1, &
& opsArg2)
  IMPLICIT NONE
  character(kind=c_char,len=*), INTENT(IN) :: userSubroutine
  type ( ops_block ), INTENT(IN) :: block
  integer(kind=4), INTENT(IN):: dim
  integer(kind=4)   , DIMENSION(dim), INTENT(IN) :: range
  real(kind=8) t1,t2,t3
  real(kind=4) transfer_total, transfer

  type ( ops_arg )  , INTENT(IN) :: opsArg1
  real(8), POINTER, DIMENSION(:) :: opsDat1Local
  integer(kind=4) :: opsDat1Cardinality
  integer(kind=4) , POINTER, DIMENSION(:)  :: dat1_size
  integer(kind=4) :: dat1_base
  integer ydim1

  type ( ops_arg )  , INTENT(IN) :: opsArg2
  real(8), POINTER, DIMENSION(:) :: opsDat2Local
  integer(kind=4) :: dat2_base

  integer n_x, n_y
  integer start(2)
  integer end(2)
  integer(kind=4) :: n

  type ( ops_arg ) , DIMENSION(2) :: opsArgArray

  opsArgArray(1) = opsArg1
  opsArgArray(2) = opsArg2

  call setKernelTime(3,userSubroutine//char(0),0.0_8,0.0_8,0.0_4,0)
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
  multi_d1 = getDatDimFromOpsArg(opsArg1) ! dimension of the dat
  dat1_base = getDatBaseFromOpsArg2D(opsArg1,start,multi_d1)
  call c_f_pointer(opsArg1%data,opsDat1Local,(/opsDat1Cardinality/))

  call c_f_pointer(getReductionPtrFromOpsArg(opsArg2,block),opsDat2Local, (/opsArg2%dim/))
  dat2_base = 1

  call ops_H_D_exchanges_host(opsArgArray,2)
  call ops_halo_exchanges(opsArgArray,2,range)
  call ops_H_D_exchanges_host(opsArgArray,2)

  call ops_timers_core(t2)

  call multidim_reduce_kernel_wrap( &
  & opsDat1Local, &
  & opsDat2Local, &
  & dat1_base, &
  & dat2_base, &
  & start, &
  & end )

  call ops_timers_core(t3)

  call ops_set_dirtybit_host(opsArgArray, 2)

  !Timing and data movement
  transfer_total = 0.0_4
  call ops_compute_transfer(2, start, end, opsArg1,transfer)
  transfer_total = transfer_total + transfer
  call setKernelTime(3,userSubroutine,t3-t2,t2-t1,transfer_total,1)
end subroutine
END MODULE
