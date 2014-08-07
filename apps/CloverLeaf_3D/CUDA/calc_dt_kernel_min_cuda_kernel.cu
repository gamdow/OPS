//
// auto-generated by ops.py on 2014-08-07 16:36
//

__constant__ int xdim0_calc_dt_kernel_min;
__constant__ int ydim0_calc_dt_kernel_min;

#define OPS_ACC0(x,y,z) (x+xdim0_calc_dt_kernel_min*(y)+xdim0_calc_dt_kernel_min*ydim0_calc_dt_kernel_min*(z))

//user function
__device__

void calc_dt_kernel_min(const double* dt_min ,
                    double* dt_min_val) {
  *dt_min_val = MIN(*dt_min_val, dt_min[OPS_ACC0(0,0,0)]);

}



#undef OPS_ACC0


__global__ void ops_calc_dt_kernel_min(
const double* __restrict arg0,
double* __restrict arg1,
int size0,
int size1,
int size2 ){

  double arg1_l[1];
  for (int d=0; d<1; d++) arg1_l[d] = INFINITY_double;

  int idx_z = blockDim.z * blockIdx.z + threadIdx.z;
  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_calc_dt_kernel_min + idx_z * 1 * xdim0_calc_dt_kernel_min * ydim0_calc_dt_kernel_min;

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    calc_dt_kernel_min(arg0, arg1_l);
  }
  for (int d=0; d<1; d++)
    ops_reduction<OPS_MIN>(&arg1[d+blockIdx.x + blockIdx.y*gridDim.x + blockIdx.z*gridDim.x*gridDim.y],arg1_l[d]);

}

// host stub function
void ops_par_loop_calc_dt_kernel_min(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  ops_arg args[2] = { arg0, arg1};

  //compute locally allocated range for the sub-block
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

  int xdim0 = args[0].dat->size[0]*args[0].dat->dim;
  int ydim0 = args[0].dat->size[1];


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(127,"calc_dt_kernel_min");
  ops_timers_core(&c2,&t2);

  if (OPS_kernels[127].count == 0) {
    cudaMemcpyToSymbol( xdim0_calc_dt_kernel_min, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( ydim0_calc_dt_kernel_min, &ydim0, sizeof(int) );
  }


  double *arg1h = (double *)arg1.data;

  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, z_size);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,1);

  int nblocks = ((x_size-1)/OPS_block_size_x+ 1)*((y_size-1)/OPS_block_size_y + 1)*z_size;
  int maxblocks = nblocks;
  int reduct_bytes = 0;
  int reduct_size = 0;

  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));
  reduct_size = MAX(reduct_size,sizeof(double)*1);

  reallocReductArrays(reduct_bytes);
  reduct_bytes = 0;

  arg1.data = OPS_reduct_h + reduct_bytes;
  arg1.data_d = OPS_reduct_d + reduct_bytes;
  for (int b=0; b<maxblocks; b++)
  for (int d=0; d<1; d++) ((double *)arg1.data)[d+b*1] = INFINITY_double;
  reduct_bytes += ROUND_UP(maxblocks*1*sizeof(double));


  mvReductArraysToDevice(reduct_bytes);
  int dat0 = args[0].dat->elem_size;

  char *p_a[2];

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
  p_a[0] = (char *)args[0].data_d + base0;


  ops_H_D_exchanges_device(args, 2);
  ops_halo_exchanges(args,2,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[127].mpi_time += t1-t2;

  int nshared = 0;
  int nthread = OPS_block_size_x*OPS_block_size_y;

  nshared = MAX(nshared,sizeof(double)*1);

  nshared = MAX(nshared*nthread,reduct_size*nthread);

  //call kernel wrapper function, passing in pointers to data
  ops_calc_dt_kernel_min<<<grid, tblock, nshared >>> (  (double *)p_a[0], (double *)arg1.data_d,x_size, y_size, z_size);

  mvReductArraysToHost(reduct_bytes);
  for ( int b=0; b<maxblocks; b++ ){
    for ( int d=0; d<1; d++ ){
      arg1h[d] = MIN(arg1h[d],((double *)arg1.data)[d+b*1]);
    }
  }
  arg1.data = (char *)arg1h;

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
  }
  ops_timers_core(&c2,&t2);
  OPS_kernels[127].time += t2-t1;
  ops_mpi_reduce(&arg1,(double *)p_a[1]);
  ops_timers_core(&c1,&t1);
  OPS_kernels[127].mpi_time += t1-t2;
  ops_set_dirtybit_device(args, 2);

  //Update kernel record
  OPS_kernels[127].count++;
  OPS_kernels[127].transfer += ops_compute_transfer(dim, range, &arg0);
}
