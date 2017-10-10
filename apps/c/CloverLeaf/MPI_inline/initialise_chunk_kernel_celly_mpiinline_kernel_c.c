//
// auto-generated by ops.py
//
#include "./MPI_inline/clover_leaf_common.h"

int xdim0_initialise_chunk_kernel_celly;
int xdim1_initialise_chunk_kernel_celly;
int xdim2_initialise_chunk_kernel_celly;

#define OPS_ACC0(x,y) (n_x*0+n_y*xdim0_initialise_chunk_kernel_celly*1+x+xdim0_initialise_chunk_kernel_celly*(y))
#define OPS_ACC1(x,y) (n_x*0+n_y*xdim1_initialise_chunk_kernel_celly*1+x+xdim1_initialise_chunk_kernel_celly*(y))
#define OPS_ACC2(x,y) (n_x*0+n_y*xdim2_initialise_chunk_kernel_celly*1+x+xdim2_initialise_chunk_kernel_celly*(y))

//user function



void initialise_chunk_kernel_celly_c_wrapper(
  const double * restrict vertexy,
  double * restrict celly,
  double * restrict celldy,
  int x_size, int y_size) {
  #pragma omp parallel for
  for ( int n_y=0; n_y<y_size; n_y++ ){
    for ( int n_x=0; n_x<x_size; n_x++ ){
      

  double d_y;
  d_y = (grid.ymax - grid.ymin)/(double)grid.y_cells;

  celly[OPS_ACC1(0,0)] = 0.5*( vertexy[OPS_ACC0(0,0)]+ vertexy[OPS_ACC0(0,1)] );
  celldy[OPS_ACC2(0,0)] = d_y;



    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
