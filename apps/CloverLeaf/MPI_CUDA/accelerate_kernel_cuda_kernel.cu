//
// auto-generated by ops.py on 2014-03-07 14:49
//

__constant__ int xdim0_accelerate_kernel;
__constant__ int xdim1_accelerate_kernel;
__constant__ int xdim2_accelerate_kernel;
__constant__ int xdim3_accelerate_kernel;
__constant__ int xdim4_accelerate_kernel;
__constant__ int xdim5_accelerate_kernel;
__constant__ int xdim6_accelerate_kernel;
__constant__ int xdim7_accelerate_kernel;
__constant__ int xdim8_accelerate_kernel;
__constant__ int xdim9_accelerate_kernel;
__constant__ int xdim10_accelerate_kernel;

#define OPS_ACC0(x,y) (x+xdim0_accelerate_kernel*(y))
#define OPS_ACC1(x,y) (x+xdim1_accelerate_kernel*(y))
#define OPS_ACC2(x,y) (x+xdim2_accelerate_kernel*(y))
#define OPS_ACC3(x,y) (x+xdim3_accelerate_kernel*(y))
#define OPS_ACC4(x,y) (x+xdim4_accelerate_kernel*(y))
#define OPS_ACC5(x,y) (x+xdim5_accelerate_kernel*(y))
#define OPS_ACC6(x,y) (x+xdim6_accelerate_kernel*(y))
#define OPS_ACC7(x,y) (x+xdim7_accelerate_kernel*(y))
#define OPS_ACC8(x,y) (x+xdim8_accelerate_kernel*(y))
#define OPS_ACC9(x,y) (x+xdim9_accelerate_kernel*(y))
#define OPS_ACC10(x,y) (x+xdim10_accelerate_kernel*(y))

//user function
__device__

void accelerate_kernel( const double *density0, const double *volume,
                double *stepbymass, const double *xvel0, double *xvel1,
                const double *xarea, const double *pressure,
                const double *yvel0, double *yvel1,
                const double *yarea, const double *viscosity) {

  double nodal_mass;

  nodal_mass = ( density0[OPS_ACC0(-1,-1)] * volume[OPS_ACC1(-1,-1)]
    + density0[OPS_ACC0(0,-1)] * volume[OPS_ACC1(0,-1)]
    + density0[OPS_ACC0(0,0)] * volume[OPS_ACC1(0,0)]
    + density0[OPS_ACC0(-1,0)] * volume[OPS_ACC1(-1,0)] ) * 0.25;

  stepbymass[OPS_ACC2(0,0)] = 0.5*dt / nodal_mass;



  xvel1[OPS_ACC4(0,0)] = xvel0[OPS_ACC3(0,0)] - stepbymass[OPS_ACC2(0,0)] *
            ( xarea[OPS_ACC5(0,0)]  * ( pressure[OPS_ACC6(0,0)] - pressure[OPS_ACC6(-1,0)] ) +
              xarea[OPS_ACC5(0,-1)] * ( pressure[OPS_ACC6(0,-1)] - pressure[OPS_ACC6(-1,-1)] ) );



  yvel1[OPS_ACC8(0,0)] = yvel0[OPS_ACC7(0,0)] - stepbymass[OPS_ACC2(0,0)] *
            ( yarea[OPS_ACC9(0,0)]  * ( pressure[OPS_ACC6(0,0)] - pressure[OPS_ACC6(0,-1)] ) +
              yarea[OPS_ACC9(-1,0)] * ( pressure[OPS_ACC6(-1,0)] - pressure[OPS_ACC6(-1,-1)] ) );



  xvel1[OPS_ACC4(0,0)] = xvel1[OPS_ACC4(0,0)] - stepbymass[OPS_ACC2(0,0)] *
            ( xarea[OPS_ACC5(0,0)] * ( viscosity[OPS_ACC10(0,0)] - viscosity[OPS_ACC10(-1,0)] ) +
              xarea[OPS_ACC5(0,-1)] * ( viscosity[OPS_ACC10(0,-1)] - viscosity[OPS_ACC10(-1,-1)] ) );



  yvel1[OPS_ACC8(0,0)] = yvel1[OPS_ACC8(0,0)] - stepbymass[OPS_ACC2(0,0)] *
            ( yarea[OPS_ACC9(0,0)] * ( viscosity[OPS_ACC10(0,0)] - viscosity[OPS_ACC10(0,-1)] ) +
              yarea[OPS_ACC9(-1,0)] * ( viscosity[OPS_ACC10(-1,0)] - viscosity[OPS_ACC10(-1,-1)] ) );

}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7
#undef OPS_ACC8
#undef OPS_ACC9
#undef OPS_ACC10


__global__ void ops_accelerate_kernel(
const double* __restrict arg0,
const double* __restrict arg1,
double* __restrict arg2,
const double* __restrict arg3,
double* __restrict arg4,
const double* __restrict arg5,
const double* __restrict arg6,
const double* __restrict arg7,
double* __restrict arg8,
const double* __restrict arg9,
const double* __restrict arg10,
int size0,
int size1 ){


  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_accelerate_kernel;
  arg1 += idx_x * 1 + idx_y * 1 * xdim1_accelerate_kernel;
  arg2 += idx_x * 1 + idx_y * 1 * xdim2_accelerate_kernel;
  arg3 += idx_x * 1 + idx_y * 1 * xdim3_accelerate_kernel;
  arg4 += idx_x * 1 + idx_y * 1 * xdim4_accelerate_kernel;
  arg5 += idx_x * 1 + idx_y * 1 * xdim5_accelerate_kernel;
  arg6 += idx_x * 1 + idx_y * 1 * xdim6_accelerate_kernel;
  arg7 += idx_x * 1 + idx_y * 1 * xdim7_accelerate_kernel;
  arg8 += idx_x * 1 + idx_y * 1 * xdim8_accelerate_kernel;
  arg9 += idx_x * 1 + idx_y * 1 * xdim9_accelerate_kernel;
  arg10 += idx_x * 1 + idx_y * 1 * xdim10_accelerate_kernel;

  if (idx_x < size0 && idx_y < size1) {
    accelerate_kernel(arg0, arg1, arg2, arg3,
                   arg4, arg5, arg6, arg7, arg8,
                   arg9, arg10);
  }

}

// host stub function
void ops_par_loop_accelerate_kernel(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7, ops_arg arg8,
 ops_arg arg9, ops_arg arg10) {

  ops_arg args[11] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10};


  int x_size = range[1]-range[0];
  int y_size = range[3]-range[2];

  int xdim0 = args[0].dat->block_size[0];
  int xdim1 = args[1].dat->block_size[0];
  int xdim2 = args[2].dat->block_size[0];
  int xdim3 = args[3].dat->block_size[0];
  int xdim4 = args[4].dat->block_size[0];
  int xdim5 = args[5].dat->block_size[0];
  int xdim6 = args[6].dat->block_size[0];
  int xdim7 = args[7].dat->block_size[0];
  int xdim8 = args[8].dat->block_size[0];
  int xdim9 = args[9].dat->block_size[0];
  int xdim10 = args[10].dat->block_size[0];


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(7,"accelerate_kernel");
  ops_timers_core(&c1,&t1);

  if (OPS_kernels[7].count == 0) {
    cudaMemcpyToSymbol( xdim0_accelerate_kernel, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( xdim1_accelerate_kernel, &xdim1, sizeof(int) );
    cudaMemcpyToSymbol( xdim2_accelerate_kernel, &xdim2, sizeof(int) );
    cudaMemcpyToSymbol( xdim3_accelerate_kernel, &xdim3, sizeof(int) );
    cudaMemcpyToSymbol( xdim4_accelerate_kernel, &xdim4, sizeof(int) );
    cudaMemcpyToSymbol( xdim5_accelerate_kernel, &xdim5, sizeof(int) );
    cudaMemcpyToSymbol( xdim6_accelerate_kernel, &xdim6, sizeof(int) );
    cudaMemcpyToSymbol( xdim7_accelerate_kernel, &xdim7, sizeof(int) );
    cudaMemcpyToSymbol( xdim8_accelerate_kernel, &xdim8, sizeof(int) );
    cudaMemcpyToSymbol( xdim9_accelerate_kernel, &xdim9, sizeof(int) );
    cudaMemcpyToSymbol( xdim10_accelerate_kernel, &xdim10, sizeof(int) );
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, 1);
  dim3 block(OPS_block_size_x,OPS_block_size_y,1);




  char *p_a[11];


  //set up initial pointers
  p_a[0] = &args[0].data_d[
  + args[0].dat->size * args[0].dat->block_size[0] * ( range[2] * 1 - args[0].dat->offset[1] )
  + args[0].dat->size * ( range[0] * 1 - args[0].dat->offset[0] ) ];

  p_a[1] = &args[1].data_d[
  + args[1].dat->size * args[1].dat->block_size[0] * ( range[2] * 1 - args[1].dat->offset[1] )
  + args[1].dat->size * ( range[0] * 1 - args[1].dat->offset[0] ) ];

  p_a[2] = &args[2].data_d[
  + args[2].dat->size * args[2].dat->block_size[0] * ( range[2] * 1 - args[2].dat->offset[1] )
  + args[2].dat->size * ( range[0] * 1 - args[2].dat->offset[0] ) ];

  p_a[3] = &args[3].data_d[
  + args[3].dat->size * args[3].dat->block_size[0] * ( range[2] * 1 - args[3].dat->offset[1] )
  + args[3].dat->size * ( range[0] * 1 - args[3].dat->offset[0] ) ];

  p_a[4] = &args[4].data_d[
  + args[4].dat->size * args[4].dat->block_size[0] * ( range[2] * 1 - args[4].dat->offset[1] )
  + args[4].dat->size * ( range[0] * 1 - args[4].dat->offset[0] ) ];

  p_a[5] = &args[5].data_d[
  + args[5].dat->size * args[5].dat->block_size[0] * ( range[2] * 1 - args[5].dat->offset[1] )
  + args[5].dat->size * ( range[0] * 1 - args[5].dat->offset[0] ) ];

  p_a[6] = &args[6].data_d[
  + args[6].dat->size * args[6].dat->block_size[0] * ( range[2] * 1 - args[6].dat->offset[1] )
  + args[6].dat->size * ( range[0] * 1 - args[6].dat->offset[0] ) ];

  p_a[7] = &args[7].data_d[
  + args[7].dat->size * args[7].dat->block_size[0] * ( range[2] * 1 - args[7].dat->offset[1] )
  + args[7].dat->size * ( range[0] * 1 - args[7].dat->offset[0] ) ];

  p_a[8] = &args[8].data_d[
  + args[8].dat->size * args[8].dat->block_size[0] * ( range[2] * 1 - args[8].dat->offset[1] )
  + args[8].dat->size * ( range[0] * 1 - args[8].dat->offset[0] ) ];

  p_a[9] = &args[9].data_d[
  + args[9].dat->size * args[9].dat->block_size[0] * ( range[2] * 1 - args[9].dat->offset[1] )
  + args[9].dat->size * ( range[0] * 1 - args[9].dat->offset[0] ) ];

  p_a[10] = &args[10].data_d[
  + args[10].dat->size * args[10].dat->block_size[0] * ( range[2] * 1 - args[10].dat->offset[1] )
  + args[10].dat->size * ( range[0] * 1 - args[10].dat->offset[0] ) ];


  ops_H_D_exchanges_cuda(args, 11);


  //call kernel wrapper function, passing in pointers to data
  ops_accelerate_kernel<<<grid, block >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2], (double *)p_a[3],
           (double *)p_a[4], (double *)p_a[5],
           (double *)p_a[6], (double *)p_a[7],
           (double *)p_a[8], (double *)p_a[9],
           (double *)p_a[10],x_size, y_size);

  if (OPS_diags>1) cudaDeviceSynchronize();
  ops_set_dirtybit_cuda(args, 11);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[7].count++;
  OPS_kernels[7].time += t2-t1;
  OPS_kernels[7].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[7].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[7].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[7].transfer += ops_compute_transfer(dim, range, &arg3);
  OPS_kernels[7].transfer += ops_compute_transfer(dim, range, &arg4);
  OPS_kernels[7].transfer += ops_compute_transfer(dim, range, &arg5);
  OPS_kernels[7].transfer += ops_compute_transfer(dim, range, &arg6);
  OPS_kernels[7].transfer += ops_compute_transfer(dim, range, &arg7);
  OPS_kernels[7].transfer += ops_compute_transfer(dim, range, &arg8);
  OPS_kernels[7].transfer += ops_compute_transfer(dim, range, &arg9);
  OPS_kernels[7].transfer += ops_compute_transfer(dim, range, &arg10);
}
