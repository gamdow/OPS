//
// auto-generated by ops.py
//
__constant__ int xdim0_drhoudx_kernel;
int xdim0_drhoudx_kernel_h = -1;
int ydim0_drhoudx_kernel_h = -1;
__constant__ int xdim1_drhoudx_kernel;
int xdim1_drhoudx_kernel_h = -1;
int ydim1_drhoudx_kernel_h = -1;

#undef OPS_ACC0
#undef OPS_ACC1


#define OPS_ACC0(x) (x)
#define OPS_ACC1(x) (x)

//user function
__device__

void drhoudx_kernel(const double *rhou_new, double *rho_res) {
        double fni = rhou_new[OPS_ACC0(0)];
        double fnim1 = rhou_new[OPS_ACC0(-1)];
        double fnim2 = rhou_new[OPS_ACC0(-2)];
        double fnip1 = rhou_new[OPS_ACC0(1)];
        double fnip2 = rhou_new[OPS_ACC0(2)];

        double deriv = (fnim2 - fnip2 + 8.0* (fnip1 - fnim1))/(12.00*dx);
        rho_res[OPS_ACC1(0)] = deriv;
}



#undef OPS_ACC0
#undef OPS_ACC1


__global__ void ops_drhoudx_kernel(
const double* __restrict arg0,
double* __restrict arg1,
int size0 ){


  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1*1;
  arg1 += idx_x * 1*1;

  if (idx_x < size0) {
    drhoudx_kernel(arg0, arg1);
  }

}

// host stub function
void ops_par_loop_drhoudx_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[2] = { arg0, arg1};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,2,range,3)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(3,"drhoudx_kernel");
    OPS_kernels[3].count++;
    ops_timers_core(&c1,&t1);
  }

  //compute locally allocated range for the sub-block
  int start[1];
  int end[1];
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<1; n++ ){
    start[n] = sb->decomp_disp[n];end[n] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (sb->id_m[n]==MPI_PROC_NULL && range[2*n] < 0) start[n] = range[2*n];
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n]==MPI_PROC_NULL && (range[2*n+1] > sb->decomp_disp[n]+sb->decomp_size[n]))
      end[n] += (range[2*n+1]-sb->decomp_disp[n]-sb->decomp_size[n]);
  }
  #else //OPS_MPI
  for ( int n=0; n<1; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif //OPS_MPI

  int x_size = MAX(0,end[0]-start[0]);

  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];

  if (xdim0 != xdim0_drhoudx_kernel_h || xdim1 != xdim1_drhoudx_kernel_h) {
    cudaMemcpyToSymbol( xdim0_drhoudx_kernel, &xdim0, sizeof(int) );
    xdim0_drhoudx_kernel_h = xdim0;
    cudaMemcpyToSymbol( xdim1_drhoudx_kernel, &xdim1, sizeof(int) );
    xdim1_drhoudx_kernel_h = xdim1;
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, 1, 1);
  dim3 tblock(OPS_block_size_x,1,1);



  int dat0 = args[0].dat->elem_size;
  int dat1 = args[1].dat->elem_size;

  char *p_a[2];

  //set up initial pointers
  int d_m[OPS_MAX_DIM];
  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d];
  #endif //OPS_MPI
  int base0 = dat0 * 1 *
  (start[0] * args[0].stencil->stride[0] - args[0].dat->base[0] - d_m[0]);
  p_a[0] = (char *)args[0].data_d + base0;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d] + OPS_sub_dat_list[args[1].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d];
  #endif //OPS_MPI
  int base1 = dat1 * 1 *
  (start[0] * args[1].stencil->stride[0] - args[1].dat->base[0] - d_m[0]);
  p_a[1] = (char *)args[1].data_d + base1;


  ops_H_D_exchanges_device(args, 2);
  ops_halo_exchanges(args,2,range);

  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[3].mpi_time += t2-t1;
  }


  //call kernel wrapper function, passing in pointers to data
  ops_drhoudx_kernel<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],x_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1,&t1);
    OPS_kernels[3].time += t1-t2;
  }

  ops_set_dirtybit_device(args, 2);
  ops_set_halo_dirtybit3(&args[1],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c2,&t2);
    OPS_kernels[3].mpi_time += t2-t1;
    OPS_kernels[3].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[3].transfer += ops_compute_transfer(dim, start, end, &arg1);
  }
}
