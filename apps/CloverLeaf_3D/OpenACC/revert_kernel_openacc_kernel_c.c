//
// auto-generated by ops.py on 2014-08-07 16:36
//

#include "./OpenACC/clover_leaf_common.h"

#define OPS_GPU

int xdim0_revert_kernel;
int ydim0_revert_kernel;
int xdim1_revert_kernel;
int ydim1_revert_kernel;
int xdim2_revert_kernel;
int ydim2_revert_kernel;
int xdim3_revert_kernel;
int ydim3_revert_kernel;

#define OPS_ACC0(x,y,z) (x+xdim0_revert_kernel*(y)+xdim0_revert_kernel*ydim0_revert_kernel*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_revert_kernel*(y)+xdim1_revert_kernel*ydim1_revert_kernel*(z))
#define OPS_ACC2(x,y,z) (x+xdim2_revert_kernel*(y)+xdim2_revert_kernel*ydim2_revert_kernel*(z))
#define OPS_ACC3(x,y,z) (x+xdim3_revert_kernel*(y)+xdim3_revert_kernel*ydim3_revert_kernel*(z))

//user function
inline 
void revert_kernel( const double *density0, double *density1,
                    const double *energy0,  double *energy1) {

  density1[OPS_ACC1(0,0,0)] = density0[OPS_ACC0(0,0,0)];
  energy1[OPS_ACC3(0,0,0)] = energy0[OPS_ACC2(0,0,0)];
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3


void revert_kernel_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  int x_size, int y_size, int z_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3)
  #pragma acc loop
  #endif
  for ( int n_z=0; n_z<z_size; n_z++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_y=0; n_y<y_size; n_y++ ){
      #ifdef OPS_GPU
      #pragma acc loop
      #endif
      for ( int n_x=0; n_x<x_size; n_x++ ){
        revert_kernel(  p_a0 + n_x*1 + n_y*xdim0_revert_kernel*1 + n_z*xdim0_revert_kernel*ydim0_revert_kernel*1,
           p_a1 + n_x*1 + n_y*xdim1_revert_kernel*1 + n_z*xdim1_revert_kernel*ydim1_revert_kernel*1,
           p_a2 + n_x*1 + n_y*xdim2_revert_kernel*1 + n_z*xdim2_revert_kernel*ydim2_revert_kernel*1,
           p_a3 + n_x*1 + n_y*xdim3_revert_kernel*1 + n_z*xdim3_revert_kernel*ydim3_revert_kernel*1 );

      }
    }
  }
}
