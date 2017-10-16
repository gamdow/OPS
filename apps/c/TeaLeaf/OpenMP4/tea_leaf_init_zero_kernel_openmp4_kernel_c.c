//
// auto-generated by ops.py
//
#include "./OpenMP4/tea_leaf_common.h"

#define OPS_GPU

extern int xdim0_tea_leaf_init_zero_kernel;

#undef OPS_ACC0

#define OPS_ACC0(x, y) (x + xdim0_tea_leaf_init_zero_kernel * (y))

// user function

void tea_leaf_init_zero_kernel_c_wrapper(double *p_a0, int base0, int tot0,
                                         int x_size, int y_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for num_teams(OPS_threads)        \
    thread_limit(OPS_threads_for_block) schedule(static, 1)
#endif
  for (int i = 0; i < y_size * x_size; i++) {
    int n_x = i % x_size;
    int n_y = i / x_size;
    double *p = p_a0 + base0 + n_x * 1 * 1 +
                n_y * xdim0_tea_leaf_init_zero_kernel * 1 * 1;

    p[OPS_ACC0(0, 0)] = 0.0;
  }
}
#undef OPS_ACC0