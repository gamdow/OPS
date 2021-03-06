//
// auto-generated by ops.py
//
#include "./MPI_inline/multidim_common.h"

int xdim0_multidim_kernel;
int ydim0_multidim_kernel;
int zdim0_multidim_kernel;

#define OPS_ACC_MD0(d, x, y, z)                                                \
  (n_x * 1 + n_y * xdim0_multidim_kernel * 1 +                                 \
   n_z * xdim0_multidim_kernel * ydim0_multidim_kernel * 1 + (x) +             \
   (d)*xdim0_multidim_kernel * ydim0_multidim_kernel * zdim0_multidim_kernel + \
   (xdim0_multidim_kernel * (y)) +                                             \
   (xdim0_multidim_kernel * ydim0_multidim_kernel * (z)))
// user function

void multidim_kernel_c_wrapper(double *restrict val, int *restrict idx,
                               int arg_idx0, int arg_idx1, int arg_idx2,
                               int x_size, int y_size, int z_size) {
#pragma omp parallel for
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {
        int idx[] = {arg_idx0 + n_x, arg_idx1 + n_y, arg_idx2 + n_z};

        val[OPS_ACC_MD0(0, 0, 0, 0)] = (double)(idx[0]);
        val[OPS_ACC_MD0(1, 0, 0, 0)] = (double)(idx[1]);
        val[OPS_ACC_MD0(2, 0, 0, 0)] = (double)(idx[2]);
      }
    }
  }
}

#undef OPS_ACC_MD0
