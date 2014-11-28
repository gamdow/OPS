//
// auto-generated by ops.py
//
__constant__ int xdim0_initialize_kernel;
int xdim0_initialize_kernel_h = -1;
int ydim0_initialize_kernel_h = -1;
__constant__ int xdim1_initialize_kernel;
int xdim1_initialize_kernel_h = -1;
int ydim1_initialize_kernel_h = -1;
__constant__ int xdim2_initialize_kernel;
int xdim2_initialize_kernel_h = -1;
int ydim2_initialize_kernel_h = -1;
__constant__ int xdim3_initialize_kernel;
int xdim3_initialize_kernel_h = -1;
int ydim3_initialize_kernel_h = -1;
__constant__ int xdim4_initialize_kernel;
int xdim4_initialize_kernel_h = -1;
int ydim4_initialize_kernel_h = -1;

#define OPS_ACC0(x) (x)
#define OPS_ACC1(x) (x)
#define OPS_ACC2(x) (x)
#define OPS_ACC3(x) (x)
#define OPS_ACC4(x) (x)

//user function
__device__

void initialize_kernel(double *x,double *rho_new, double *rhou_new, double *rhoE_new,
                       double* rhoin, int *idx) {
  x[OPS_ACC0(0)] = xmin + (idx[0]-2) * dx;
  if (x[OPS_ACC0(0)] >= -4.0){
		rho_new[OPS_ACC1(0)] = 1.0 + eps * sin(lambda *x[OPS_ACC0(0)]);
		rhou_new[OPS_ACC2(0)] = ur * rho_new[OPS_ACC1(0)];
		rhoE_new[OPS_ACC3(0)] = (pr / gam1) + 0.5 * pow(rhou_new[OPS_ACC2(0)],2)/rho_new[OPS_ACC1(0)];
	}
	else {
		rho_new[OPS_ACC1(0)] = rhol;
		rhou_new[OPS_ACC2(0)] = ul * rho_new[OPS_ACC1(0)];
		rhoE_new[OPS_ACC3(0)] = (pl / gam1) + 0.5 * pow(rhou_new[OPS_ACC2(0)],2)/rho_new[OPS_ACC1(0)];
	}

	rhoin[OPS_ACC4(0)] = gam1 * (rhoE_new[OPS_ACC3(0)] - 0.5 * rhou_new[OPS_ACC2(0)] * rhou_new[OPS_ACC2(0)] / rho_new[OPS_ACC1(0)]);

}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4


__global__ void ops_initialize_kernel(
double* __restrict arg0,
double* __restrict arg1,
double* __restrict arg2,
double* __restrict arg3,
double* __restrict arg4,
int arg_idx0,
int size0 ){


  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  int arg_idx[1];
  arg_idx[0] = arg_idx0+idx_x;
  arg0 += idx_x * 1*1;
  arg1 += idx_x * 1*1;
  arg2 += idx_x * 1*1;
  arg3 += idx_x * 1*1;
  arg4 += idx_x * 1*1;

  if (idx_x < size0) {
    initialize_kernel(arg0, arg1, arg2, arg3,
                   arg4, arg_idx);
  }

}

// host stub function
void ops_par_loop_initialize_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5) {

  ops_arg args[6] = { arg0, arg1, arg2, arg3, arg4, arg5};


  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,6,range,0)) return;
  #endif

  ops_timing_realloc(0,"initialize_kernel");
  OPS_kernels[0].count++;

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

  int arg_idx[1];
  #ifdef OPS_MPI
  arg_idx[0] = sb->decomp_disp[0]+start[0];
  #else //OPS_MPI
  arg_idx[0] = start[0];
  #endif //OPS_MPI
  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];
  int xdim2 = args[2].dat->size[0];
  int xdim3 = args[3].dat->size[0];
  int xdim4 = args[4].dat->size[0];


  //Timing
  double t1,t2,c1,c2;
  ops_timers_core(&c2,&t2);

  if (xdim0 != xdim0_initialize_kernel_h || xdim1 != xdim1_initialize_kernel_h || xdim2 != xdim2_initialize_kernel_h || xdim3 != xdim3_initialize_kernel_h || xdim4 != xdim4_initialize_kernel_h) {
    cudaMemcpyToSymbol( xdim0_initialize_kernel, &xdim0, sizeof(int) );
    xdim0_initialize_kernel_h = xdim0;
    cudaMemcpyToSymbol( xdim1_initialize_kernel, &xdim1, sizeof(int) );
    xdim1_initialize_kernel_h = xdim1;
    cudaMemcpyToSymbol( xdim2_initialize_kernel, &xdim2, sizeof(int) );
    xdim2_initialize_kernel_h = xdim2;
    cudaMemcpyToSymbol( xdim3_initialize_kernel, &xdim3, sizeof(int) );
    xdim3_initialize_kernel_h = xdim3;
    cudaMemcpyToSymbol( xdim4_initialize_kernel, &xdim4, sizeof(int) );
    xdim4_initialize_kernel_h = xdim4;
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, 1, 1);
  dim3 tblock(OPS_block_size_x,1,1);



  int dat0 = args[0].dat->elem_size;
  int dat1 = args[1].dat->elem_size;
  int dat2 = args[2].dat->elem_size;
  int dat3 = args[3].dat->elem_size;
  int dat4 = args[4].dat->elem_size;

  char *p_a[6];

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

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[2].dat->d_m[d] + OPS_sub_dat_list[args[2].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[2].dat->d_m[d];
  #endif //OPS_MPI
  int base2 = dat2 * 1 * 
  (start[0] * args[2].stencil->stride[0] - args[2].dat->base[0] - d_m[0]);
  p_a[2] = (char *)args[2].data_d + base2;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[3].dat->d_m[d] + OPS_sub_dat_list[args[3].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[3].dat->d_m[d];
  #endif //OPS_MPI
  int base3 = dat3 * 1 * 
  (start[0] * args[3].stencil->stride[0] - args[3].dat->base[0] - d_m[0]);
  p_a[3] = (char *)args[3].data_d + base3;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[4].dat->d_m[d] + OPS_sub_dat_list[args[4].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[4].dat->d_m[d];
  #endif //OPS_MPI
  int base4 = dat4 * 1 * 
  (start[0] * args[4].stencil->stride[0] - args[4].dat->base[0] - d_m[0]);
  p_a[4] = (char *)args[4].data_d + base4;


  ops_H_D_exchanges_device(args, 6);
  ops_halo_exchanges(args,6,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[0].mpi_time += t1-t2;


  //call kernel wrapper function, passing in pointers to data
  ops_initialize_kernel<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],
           (double *)p_a[4], arg_idx[0],x_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
  }
  ops_timers_core(&c2,&t2);
  OPS_kernels[0].time += t2-t1;
  ops_set_dirtybit_device(args, 6);
  ops_set_halo_dirtybit3(&args[0],range);
  ops_set_halo_dirtybit3(&args[1],range);
  ops_set_halo_dirtybit3(&args[2],range);
  ops_set_halo_dirtybit3(&args[3],range);
  ops_set_halo_dirtybit3(&args[4],range);

  //Update kernel record
  OPS_kernels[0].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[0].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[0].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[0].transfer += ops_compute_transfer(dim, range, &arg3);
  OPS_kernels[0].transfer += ops_compute_transfer(dim, range, &arg4);
}
