//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"

#define OPS_GPU

extern int xdim0_initialise_chunk_kernel_cellx;
extern int ydim0_initialise_chunk_kernel_cellx;
extern int xdim1_initialise_chunk_kernel_cellx;
extern int ydim1_initialise_chunk_kernel_cellx;
extern int xdim2_initialise_chunk_kernel_cellx;
extern int ydim2_initialise_chunk_kernel_cellx;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2

#define OPS_ACC0(x, y, z)                                                      \
  (x + xdim0_initialise_chunk_kernel_cellx * (y) +                             \
   xdim0_initialise_chunk_kernel_cellx * ydim0_initialise_chunk_kernel_cellx * \
       (z))
#define OPS_ACC1(x, y, z)                                                      \
  (x + xdim1_initialise_chunk_kernel_cellx * (y) +                             \
   xdim1_initialise_chunk_kernel_cellx * ydim1_initialise_chunk_kernel_cellx * \
       (z))
#define OPS_ACC2(x, y, z)                                                      \
  (x + xdim2_initialise_chunk_kernel_cellx * (y) +                             \
   xdim2_initialise_chunk_kernel_cellx * ydim2_initialise_chunk_kernel_cellx * \
       (z))

// user function

void initialise_chunk_kernel_cellx_c_wrapper(double *p_a0, int base0, int tot0,
                                             double *p_a1, int base1, int tot1,
                                             double *p_a2, int base2, int tot2,
                                             int x_size, int y_size,
                                             int z_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for num_teams(OPS_threads)        \
    thread_limit(OPS_threads_for_block) collapse(3) schedule(static, 1)
#endif
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {
        const double *vertexx =
            p_a0 + base0 + n_x * 1 * 1 +
            n_y * xdim0_initialise_chunk_kernel_cellx * 0 * 1 +
            n_z * xdim0_initialise_chunk_kernel_cellx *
                ydim0_initialise_chunk_kernel_cellx * 0;

        double *cellx = p_a1 + base1 + n_x * 1 * 1 +
                        n_y * xdim1_initialise_chunk_kernel_cellx * 0 * 1 +
                        n_z * xdim1_initialise_chunk_kernel_cellx *
                            ydim1_initialise_chunk_kernel_cellx * 0;

        double *celldx = p_a2 + base2 + n_x * 1 * 1 +
                         n_y * xdim2_initialise_chunk_kernel_cellx * 0 * 1 +
                         n_z * xdim2_initialise_chunk_kernel_cellx *
                             ydim2_initialise_chunk_kernel_cellx * 0;

        double d_x = (grid.xmax - grid.xmin) / (double)grid.x_cells;
        cellx[OPS_ACC1(0, 0, 0)] =
            0.5 * (vertexx[OPS_ACC0(0, 0, 0)] + vertexx[OPS_ACC0(1, 0, 0)]);
        celldx[OPS_ACC2(0, 0, 0)] = d_x;
      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2