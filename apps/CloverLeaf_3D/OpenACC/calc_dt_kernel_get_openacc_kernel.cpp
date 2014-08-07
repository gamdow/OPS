//
// auto-generated by ops.py on 2014-08-07 16:36
//

#include "./OpenACC/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_calc_dt_kernel_get;
extern int ydim0_calc_dt_kernel_get;
extern int xdim1_calc_dt_kernel_get;
extern int ydim1_calc_dt_kernel_get;
extern int xdim4_calc_dt_kernel_get;
extern int ydim4_calc_dt_kernel_get;

#ifdef __cplusplus
extern "C" {
#endif
void calc_dt_kernel_get_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  int x_size, int y_size, int z_size);

#ifdef __cplusplus
}
#endif

// host stub function
void ops_par_loop_calc_dt_kernel_get(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3, ops_arg arg4, ops_arg arg5) {

  ops_arg args[6] = { arg0, arg1, arg2, arg3, arg4, arg5};

  sub_block_list sb = OPS_sub_block_list[Block->index];
  //compute localy allocated range for the sub-block
  int start[3];
  int end[3];
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  for ( int n=0; n<3; n++ ){
    start[n] = sb->decomp_disp[n];end[n] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      end[n] = sb->decomp_size[n];
    }
  }
  #else //OPS_MPI
  for ( int n=0; n<3; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif //OPS_MPI

  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);
  int z_size = MAX(0,end[2]-start[2]);


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(128,"calc_dt_kernel_get");
  ops_timers_core(&c2,&t2);

  if (OPS_kernels[128].count == 0) {
    xdim0_calc_dt_kernel_get = args[0].dat->size[0]*args[0].dat->dim;
    ydim0_calc_dt_kernel_get = args[0].dat->size[1];
    xdim1_calc_dt_kernel_get = args[1].dat->size[0]*args[1].dat->dim;
    ydim1_calc_dt_kernel_get = args[1].dat->size[1];
    xdim4_calc_dt_kernel_get = args[4].dat->size[0]*args[4].dat->dim;
    ydim4_calc_dt_kernel_get = args[4].dat->size[1];
  }

  int dat0 = args[0].dat->elem_size;
  int dat1 = args[1].dat->elem_size;
  int dat4 = args[4].dat->elem_size;


  //set up initial pointers
  int base0 = dat0 * 1 * 
    (start[0] * args[0].stencil->stride[0] - args[0].dat->base[0] - args[0].dat->d_m[0]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1] - args[0].dat->base[1] - args[0].dat->d_m[1]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    args[0].dat->size[1] *
    (start[2] * args[0].stencil->stride[2] - args[0].dat->base[2] - args[0].dat->d_m[2]);
  #ifdef OPS_GPU
  double *p_a0 = (double *)((char *)args[0].data_d + base0);
  #else
  double *p_a0 = (double *)((char *)args[0].data + base0);
  #endif

  int base1 = dat1 * 1 * 
    (start[0] * args[1].stencil->stride[0] - args[1].dat->base[0] - args[1].dat->d_m[0]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    (start[1] * args[1].stencil->stride[1] - args[1].dat->base[1] - args[1].dat->d_m[1]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    args[1].dat->size[1] *
    (start[2] * args[1].stencil->stride[2] - args[1].dat->base[2] - args[1].dat->d_m[2]);
  #ifdef OPS_GPU
  double *p_a1 = (double *)((char *)args[1].data_d + base1);
  #else
  double *p_a1 = (double *)((char *)args[1].data + base1);
  #endif

  double *p_a2 = (double *)args[2].data;

  double *p_a3 = (double *)args[3].data;

  int base4 = dat4 * 1 * 
    (start[0] * args[4].stencil->stride[0] - args[4].dat->base[0] - args[4].dat->d_m[0]);
  base4 = base4+ dat4 *
    args[4].dat->size[0] *
    (start[1] * args[4].stencil->stride[1] - args[4].dat->base[1] - args[4].dat->d_m[1]);
  base4 = base4+ dat4 *
    args[4].dat->size[0] *
    args[4].dat->size[1] *
    (start[2] * args[4].stencil->stride[2] - args[4].dat->base[2] - args[4].dat->d_m[2]);
  #ifdef OPS_GPU
  double *p_a4 = (double *)((char *)args[4].data_d + base4);
  #else
  double *p_a4 = (double *)((char *)args[4].data + base4);
  #endif

  double *p_a5 = (double *)args[5].data;


  #ifdef OPS_GPU
  ops_H_D_exchanges_device(args, 6);
  #else
  ops_H_D_exchanges_host(args, 6);
  #endif
  ops_halo_exchanges(args,6,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[128].mpi_time += t1-t2;

  calc_dt_kernel_get_c_wrapper(
    p_a0,
    p_a1,
    p_a2,
    p_a3,
    p_a4,
    p_a5,
    x_size, y_size, z_size);
  *(double *)args[2].data = *p_a2;
  *(double *)args[3].data = *p_a3;
  *(double *)args[5].data = *p_a5;

  ops_timers_core(&c2,&t2);
  OPS_kernels[128].time += t2-t1;
  ops_mpi_reduce(&arg2,(double *)args[2].data);
  ops_mpi_reduce(&arg3,(double *)args[3].data);
  ops_mpi_reduce(&arg5,(double *)args[5].data);
  ops_timers_core(&c1,&t1);
  OPS_kernels[128].mpi_time += t1-t2;
  #ifdef OPS_GPU
  ops_set_dirtybit_cuda(args, 6);
  #else
  ops_set_dirtybit_host(args, 6);
  #endif

  //Update kernel record
  OPS_kernels[128].count++;
  OPS_kernels[128].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[128].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[128].transfer += ops_compute_transfer(dim, range, &arg4);
}
