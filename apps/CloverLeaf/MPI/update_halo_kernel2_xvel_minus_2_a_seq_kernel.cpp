//
// auto-generated by ops.py on 2014-07-25 20:10
//

//user function
#include "update_halo_kernel.h"

// host stub function
void ops_par_loop_update_halo_kernel2_xvel_minus_2_a(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {

  char *p_a[3];
  int  offs[3][2];
  ops_arg args[3] = { arg0, arg1, arg2};


  sub_block_list sb = OPS_sub_block_list[block->index];
  //compute localy allocated range for the sub-block
  int start[2];
  int end[2];

  for ( int n=0; n<2; n++ ){
    start[n] = sb->istart[n];end[n] = sb->iend[n]+1;
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      end[n] = sb->sizes[n];
    }
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "update_halo_kernel2_xvel_minus_2_a");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off2D(1, &start[0],
      &end[0],args[0].dat->block_size, args[0].stencil->stride) - offs[0][0];

  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  offs[1][1] = off2D(1, &start[0],
      &end[0],args[1].dat->block_size, args[1].stencil->stride) - offs[1][0];



  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(43,"update_halo_kernel2_xvel_minus_2_a");
  ops_timers_core(&c2,&t2);

  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int dat0 = args[0].dat->size;
  int off1_0 = offs[1][0];
  int off1_1 = offs[1][1];
  int dat1 = args[1].dat->size;

  //set up initial pointers and exchange halos if nessasary
  int base0 = dat0 * 1 * 
  (start[0] * args[0].stencil->stride[0] - args[0].dat->offset[0]);
  base0 = base0+ dat0 *
    args[0].dat->block_size[0] *
    (start[1] * args[0].stencil->stride[1] - args[0].dat->offset[1]);
  p_a[0] = (char *)args[0].data + base0;

  int base1 = dat1 * 1 * 
  (start[0] * args[1].stencil->stride[0] - args[1].dat->offset[0]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    (start[1] * args[1].stencil->stride[1] - args[1].dat->offset[1]);
  p_a[1] = (char *)args[1].data + base1;

  p_a[2] = (char *)args[2].data;



  ops_halo_exchanges(args,3,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[43].mpi_time += t1-t2;

  xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;
  xdim1 = args[1].dat->block_size[0]*args[1].dat->dim;

  int n_x;
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
    #pragma novector
    for( n_x=start[0]; n_x<start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x+=SIMD_VEC ) {
      //call kernel function, passing in pointers to data -vectorised
      #pragma simd
      for ( int i=0; i<SIMD_VEC; i++ ){
        update_halo_kernel2_xvel_minus_2_a(  (double *)p_a[0]+ i*1, (double *)p_a[1]+ i*1, (int *)p_a[2] );

      }

      //shift pointers to data x direction
      p_a[0]= p_a[0] + (dat0 * off0_0)*SIMD_VEC;
      p_a[1]= p_a[1] + (dat1 * off1_0)*SIMD_VEC;
    }

    for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
        //call kernel function, passing in pointers to data - remainder
        update_halo_kernel2_xvel_minus_2_a(  (double *)p_a[0], (double *)p_a[1], (int *)p_a[2] );


        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_0);
        p_a[1]= p_a[1] + (dat1 * off1_0);
      }

      //shift pointers to data y direction
      p_a[0]= p_a[0] + (dat0 * off0_1);
      p_a[1]= p_a[1] + (dat1 * off1_1);
    }
    ops_timers_core(&c2,&t2);
    OPS_kernels[43].time += t2-t1;
    ops_set_halo_dirtybit3(&args[0],range);
    ops_set_halo_dirtybit3(&args[1],range);

    #ifdef OPS_DEBUG
    ops_dump3(arg0.dat,"update_halo_kernel2_xvel_minus_2_a");
    ops_dump3(arg1.dat,"update_halo_kernel2_xvel_minus_2_a");
    #endif

    //Update kernel record
    OPS_kernels[43].count++;
    OPS_kernels[43].transfer += ops_compute_transfer(dim, range, &arg0);
    OPS_kernels[43].transfer += ops_compute_transfer(dim, range, &arg1);
  }
