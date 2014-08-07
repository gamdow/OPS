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

void ops_par_loop_viscosity_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );



#include "data.h"
#include "definitions.h"

//#include "viscosity_kernel.h"

void viscosity_func()
{

  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;
  int z_min = field.z_min;
  int z_max = field.z_max;

  int rangexyz_inner[] = {x_min,x_max,y_min,y_max,z_min,z_max};

  ops_par_loop_viscosity_kernel("viscosity_kernel", clover_grid, 3, rangexyz_inner,
               ops_arg_dat(xvel0, S3D_000_fP1P1P1, "double", OPS_READ),
               ops_arg_dat(yvel0, S3D_000_fP1P1P1, "double", OPS_READ),
               ops_arg_dat(celldx, S3D_000_P100_STRID3D_X, "double", OPS_READ),
               ops_arg_dat(celldy, S3D_000_0P10_STRID3D_Y, "double", OPS_READ),
               ops_arg_dat(pressure, S3D_P100_M100_0P10_0M10_00P1_00M1, "double", OPS_READ),
               ops_arg_dat(density0, S3D_000, "double", OPS_READ),
               ops_arg_dat(viscosity, S3D_000, "double", OPS_WRITE),
               ops_arg_dat(zvel0, S3D_000_fP1P1P1, "double", OPS_READ),
               ops_arg_dat(celldz, S3D_000_00P1_STRID3D_Z, "double", OPS_READ),
               ops_arg_dat(xarea, S3D_000, "double", OPS_READ),
               ops_arg_dat(yarea, S3D_000, "double", OPS_READ),
               ops_arg_dat(zarea, S3D_000, "double", OPS_READ));
}
