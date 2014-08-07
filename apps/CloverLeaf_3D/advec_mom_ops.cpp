//
// auto-generated by ops.py on 2014-08-07 16:36
//



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define OPS_3D
#include  "ops_lib_cpp.h"

//
// ops_par_loop declarations
//

void ops_par_loop_advec_mom_kernel_x1(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel_z1(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel_x2(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel_y2(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel_x3(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel_z3(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel_mass_flux_x(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel_post_pre_advec_x(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel1_x_nonvector(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel2_x(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel_mass_flux_y(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel_post_pre_advec_y(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel1_y_nonvector(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel2_y(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel_mass_flux_z(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel_post_pre_advec_z(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel1_z_nonvector(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_advec_mom_kernel2_z(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );



#include "data.h"
#include "definitions.h"
//#include "advec_mom_kernel.h"

void advec_mom(int which_vel, int sweep_number, int dir)
{

  int x_cells = grid.x_cells;
  int y_cells = grid.y_cells;
  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;
  int z_min = field.z_min;
  int z_max = field.z_max;

  int rangexyz[] = {x_min-2,x_max+2,y_min-2,y_max+2,z_min-2,z_max+2};

  int mom_sweep;
  ops_dat vel1;

  if( which_vel == 1) {
    vel1 = xvel1;
  }
  else if( which_vel == 2) {
    vel1 = yvel1;
  }
  else if( which_vel == 3) {
    vel1 = zvel1;
  }

  if(sweep_number==1 && dir == 1) {
      ops_par_loop_advec_mom_kernel_x1("advec_mom_kernel_x1", clover_grid, 3, rangexyz,
                   ops_arg_dat(work_array6, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(work_array7, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(volume, S3D_000, "double", OPS_READ),
                   ops_arg_dat(vol_flux_x, S3D_000_P100, "double", OPS_READ),
                   ops_arg_dat(vol_flux_y, S3D_000_0P10, "double", OPS_READ),
                   ops_arg_dat(vol_flux_z, S3D_000_00P1, "double", OPS_READ));
  }
  else if(sweep_number==1 && dir == 3) {
    ops_par_loop_advec_mom_kernel_z1("advec_mom_kernel_z1", clover_grid, 3, rangexyz,
                 ops_arg_dat(work_array6, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array7, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(volume, S3D_000, "double", OPS_READ),
                 ops_arg_dat(vol_flux_x, S3D_000_P100, "double", OPS_READ),
                 ops_arg_dat(vol_flux_y, S3D_000_0P10, "double", OPS_READ),
                 ops_arg_dat(vol_flux_z, S3D_000_00P1, "double", OPS_READ));
  }
  else if (sweep_number==2 && advect_x) {
    ops_par_loop_advec_mom_kernel_x2("advec_mom_kernel_x2", clover_grid, 3, rangexyz,
                 ops_arg_dat(work_array6, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array7, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(volume, S3D_000, "double", OPS_READ),
                 ops_arg_dat(vol_flux_y, S3D_000_0P10, "double", OPS_READ),
                 ops_arg_dat(vol_flux_z, S3D_000_00P1, "double", OPS_READ));
  }
  else if (sweep_number==2 && !advect_x) {
    ops_par_loop_advec_mom_kernel_y2("advec_mom_kernel_y2", clover_grid, 3, rangexyz,
                 ops_arg_dat(work_array6, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array7, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(volume, S3D_000, "double", OPS_READ),
                 ops_arg_dat(vol_flux_x, S3D_000_P100, "double", OPS_READ),
                 ops_arg_dat(vol_flux_y, S3D_000_0P10, "double", OPS_READ));
  }
  else if (sweep_number==3 && dir == 1) {
    ops_par_loop_advec_mom_kernel_x3("advec_mom_kernel_x3", clover_grid, 3, rangexyz,
                 ops_arg_dat(work_array6, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array7, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(volume, S3D_000, "double", OPS_READ),
                 ops_arg_dat(vol_flux_x, S3D_000_P100, "double", OPS_READ));
  }
  else if (sweep_number==3 && dir == 3) {
    ops_par_loop_advec_mom_kernel_z3("advec_mom_kernel_z3", clover_grid, 3, rangexyz,
                 ops_arg_dat(work_array6, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(work_array7, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(volume, S3D_000, "double", OPS_READ),
                 ops_arg_dat(vol_flux_z, S3D_000_00P1, "double", OPS_READ));
  }

  int range_partx_party_1[] = {x_min-1,x_max+2,y_min,y_max+1};

  int range_fully_party_1[] = {x_min,x_max+1,y_min-2,y_max+2};
  int range_partx_party_2[] = {x_min,x_max+1,y_min-1,y_max+2};

  if (dir == 1) {
    if (which_vel == 1) {

      int range_fullx_party_partz_1[] = {x_min-2,x_max+2,y_min,y_max+1,z_min,z_max+1};
      ops_par_loop_advec_mom_kernel_mass_flux_x("advec_mom_kernel_mass_flux_x", clover_grid, 3, range_fullx_party_partz_1,
                   ops_arg_dat(work_array1, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(mass_flux_x, S3D_000_fP1M1M1, "double", OPS_READ));

      int range_partx_party_partz_1[] = {x_min-1,x_max+2,y_min,y_max+1,z_min,z_max+1};
      ops_par_loop_advec_mom_kernel_post_pre_advec_x("advec_mom_kernel_post_pre_advec_x", clover_grid, 3, range_partx_party_partz_1,
                   ops_arg_dat(work_array2, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(work_array7, S3D_000_fM1M1M1, "double", OPS_READ),
                   ops_arg_dat(density1, S3D_000_fM1M1M1, "double", OPS_READ),
                   ops_arg_dat(work_array3, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(work_array1, S3D_000_M100, "double", OPS_READ));
    }

    int range_innder_plus1xyz_minus1x[] = {x_min-1,x_max+1,y_min,y_max+1,z_min,z_max+1};
    ops_par_loop_advec_mom_kernel1_x_nonvector("advec_mom_kernel1_x", clover_grid, 3, range_innder_plus1xyz_minus1x,
                 ops_arg_dat(work_array1, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array3, S3D_000_P100, "double", OPS_READ),
                 ops_arg_dat(work_array5, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(celldx, S3D_000_P100_M100_STRID3D_X, "double", OPS_READ),
                 ops_arg_dat(vel1, S3D_000_P100_P200_M100, "double", OPS_READ));

    int range_partx_party_partz_2[] = {x_min,x_max+1,y_min,y_max+1,z_min,z_max+1};
    ops_par_loop_advec_mom_kernel2_x("advec_mom_kernel2_x", clover_grid, 3, range_partx_party_partz_2,
                 ops_arg_dat(vel1, S3D_000, "double", OPS_RW),
                 ops_arg_dat(work_array2, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array3, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array5, S3D_000_M100, "double", OPS_READ));
  }
  else if (dir == 2) {
    if (which_vel == 1) {

      int range_fully_partx_partz_1[] = {x_min,x_max+1,y_min-2,y_max+2,z_min,z_max+1};
      ops_par_loop_advec_mom_kernel_mass_flux_y("advec_mom_kernel_mass_flux_y", clover_grid, 3, range_fully_partx_partz_1,
                   ops_arg_dat(work_array1, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(mass_flux_y, S3D_000_fM1P1M1, "double", OPS_READ));

      int range_party_partx_partz_1[] = {x_min,x_max+1,y_min-1,y_max+2,z_min,z_max+1};
      ops_par_loop_advec_mom_kernel_post_pre_advec_y("advec_mom_kernel_post_pre_advec_y", clover_grid, 3, range_party_partx_partz_1,
                   ops_arg_dat(work_array2, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(work_array7, S3D_000_fM1M1M1, "double", OPS_READ),
                   ops_arg_dat(density1, S3D_000_fM1M1M1, "double", OPS_READ),
                   ops_arg_dat(work_array3, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(work_array1, S3D_000_0M10, "double", OPS_READ));
    }
    int range_plus1xyz_minus1y[] = {x_min,x_max+1,y_min-1,y_max+1,z_min,z_max+1};
    ops_par_loop_advec_mom_kernel1_y_nonvector("advec_mom_kernel1_y", clover_grid, 3, range_plus1xyz_minus1y,
                 ops_arg_dat(work_array1, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array3, S3D_000_0P10, "double", OPS_READ),
                 ops_arg_dat(work_array5, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(celldy, S3D_000_0P10_0M10_STRID3D_Y, "double", OPS_READ),
                 ops_arg_dat(vel1, S3D_000_0P10_0P20_0M10, "double", OPS_READ));

    int range_partx_party_partz_2[] = {x_min,x_max+1,y_min,y_max+1,z_min,z_max+1};
    ops_par_loop_advec_mom_kernel2_y("advec_mom_kernel2_y", clover_grid, 3, range_partx_party_partz_2,
                 ops_arg_dat(vel1, S3D_000, "double", OPS_RW),
                 ops_arg_dat(work_array2, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array3, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array5, S3D_000_0M10, "double", OPS_READ));

  }
  else if (dir == 3) {
    if (which_vel == 1) {

      int range_fullz_partx_party_1[] = {x_min,x_max+1,y_min,y_max+1,z_min-2,z_max+2};
      ops_par_loop_advec_mom_kernel_mass_flux_z("advec_mom_kernel_mass_flux_z", clover_grid, 3, range_fullz_partx_party_1,
                   ops_arg_dat(work_array1, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(mass_flux_z, S3D_000_fM1M1P1, "double", OPS_READ));

      int range_party_partx_partz_1[] = {x_min,x_max+1,y_min,y_max+1,z_min-1,z_max+2};
      ops_par_loop_advec_mom_kernel_post_pre_advec_z("advec_mom_kernel_post_pre_advec_z", clover_grid, 3, range_party_partx_partz_1,
                   ops_arg_dat(work_array2, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(work_array7, S3D_000_fM1M1M1, "double", OPS_READ),
                   ops_arg_dat(density1, S3D_000_fM1M1M1, "double", OPS_READ),
                   ops_arg_dat(work_array3, S3D_000, "double", OPS_WRITE),
                   ops_arg_dat(work_array1, S3D_000_00M1, "double", OPS_READ));
    }
    int range_plus1xyz_minus1z[] = {x_min,x_max+1,y_min,y_max+1,z_min-1,z_max+1};
    ops_par_loop_advec_mom_kernel1_z_nonvector("advec_mom_kernel1_z", clover_grid, 3, range_plus1xyz_minus1z,
                 ops_arg_dat(work_array1, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array3, S3D_000_00P1, "double", OPS_READ),
                 ops_arg_dat(work_array5, S3D_000, "double", OPS_WRITE),
                 ops_arg_dat(celldz, S3D_000_00P1_00M1_STRID3D_Z, "double", OPS_READ),
                 ops_arg_dat(vel1, S3D_000_00P1_00P2_00M1, "double", OPS_READ));

    int range_partx_party_partz_2[] = {x_min,x_max+1,y_min,y_max+1,z_min,z_max+1};
    ops_par_loop_advec_mom_kernel2_z("advec_mom_kernel2_z", clover_grid, 3, range_partx_party_partz_2,
                 ops_arg_dat(vel1, S3D_000, "double", OPS_RW),
                 ops_arg_dat(work_array2, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array3, S3D_000, "double", OPS_READ),
                 ops_arg_dat(work_array5, S3D_000_00M1, "double", OPS_READ));

  }

}
