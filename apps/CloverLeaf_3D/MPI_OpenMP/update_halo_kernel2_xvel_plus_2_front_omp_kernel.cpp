//
// auto-generated by ops.py on 2014-08-07 16:36
//

#ifdef _OPENMP
#include <omp.h>
#endif

//user function

inline void update_halo_kernel2_xvel_plus_2_front(double *xvel0, double *xvel1, const int* fields)
{
  if(fields[FIELD_XVEL0] == 1) xvel0[OPS_ACC0(0,0,0)] = xvel0[OPS_ACC0(0,0,-2)];
  if(fields[FIELD_XVEL1] == 1) xvel1[OPS_ACC1(0,0,0)] = xvel1[OPS_ACC1(0,0,-2)];
}



// host stub function
void ops_par_loop_update_halo_kernel2_xvel_plus_2_front(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {

  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(64,"update_halo_kernel2_xvel_plus_2_front");
  ops_timers_core(&c1,&t1);


  int  offs[3][3];
  ops_arg args[3] = { arg0, arg1, arg2};


  //compute locally allocated range for the sub-block

  int start[3];
  int end[3];

  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  for ( int n=0; n<3; n++ ){
    start[n] = sb->decomp_disp[n];end[n] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      end[n] = sb->decomp_size[n];
    }
  }
  #else //OPS_MPI
  for ( int n=0; n<3; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif //OPS_MPI
  #ifdef OPS_DEBUG
  ops_register_args(args, "update_halo_kernel2_xvel_plus_2_front");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off3D(1, &start[0],
      &end[0],args[0].dat->size, args[0].stencil->stride) - offs[0][0];
  offs[0][2] = off3D(2, &start[0],
      &end[0],args[0].dat->size, args[0].stencil->stride) - offs[0][1] - offs[0][0];

  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  offs[1][1] = off3D(1, &start[0],
      &end[0],args[1].dat->size, args[1].stencil->stride) - offs[1][0];
  offs[1][2] = off3D(2, &start[0],
      &end[0],args[1].dat->size, args[1].stencil->stride) - offs[1][1] - offs[1][0];



  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int off0_2 = offs[0][2];
  int dat0 = args[0].dat->elem_size;
  int off1_0 = offs[1][0];
  int off1_1 = offs[1][1];
  int off1_2 = offs[1][2];
  int dat1 = args[1].dat->elem_size;

  int*arg2h = (int *)arg2.data;

  #ifdef _OPENMP
  int nthreads = omp_get_max_threads( );
  #else
  int nthreads = 1;
  #endif
  //allocate and initialise arrays for global reduction
  //assumes a max of MAX_REDUCT_THREADS threads with a cacche line size of 64 bytes
  int arg_gbl2[MAX(NUM_FIELDS , 64) * MAX_REDUCT_THREADS];
  for ( int thr=0; thr<nthreads; thr++ ){
    for ( int d=0; d<NUM_FIELDS; d++ ){
      arg_gbl2[d+64*thr] = arg2h[d];
    }
  }
  xdim0 = args[0].dat->size[0]*args[0].dat->dim;
  ydim0 = args[0].dat->size[1];
  xdim1 = args[1].dat->size[0]*args[1].dat->dim;
  ydim1 = args[1].dat->size[1];

  ops_H_D_exchanges_host(args, 3);

  //Halo Exchanges
  ops_halo_exchanges(args,3,range);


  ops_timers_core(&c2,&t2);
  OPS_kernels[64].mpi_time += t2-t1;


  #pragma omp parallel for
  for ( int thr=0; thr<nthreads; thr++ ){

    int z_size = end[2]-start[2];
    char *p_a[3];

    int start_i = start[2] + ((z_size-1)/nthreads+1)*thr;
    int finish_i = start[2] + MIN(((z_size-1)/nthreads+1)*(thr+1),z_size);

    //get address per thread
    int start0 = start[0];
    int start1 = start[1];
    int start2 = start_i;

    //set up initial pointers 
    int base0 = dat0 * 1 * 
    (start0 * args[0].stencil->stride[0] - args[0].dat->base[0] - args[0].dat->d_m[0]);
    base0 = base0+ dat0 *
      args[0].dat->size[0] *
      (start1 * args[0].stencil->stride[1] - args[0].dat->base[1] - args[0].dat->d_m[1]);
    base0 = base0+ dat0 *
      args[0].dat->size[0] *
      args[0].dat->size[1] *
      (start2 * args[0].stencil->stride[2] - args[0].dat->base[2] - args[0].dat->d_m[2]);
    p_a[0] = (char *)args[0].data + base0;

    int base1 = dat1 * 1 * 
    (start0 * args[1].stencil->stride[0] - args[1].dat->base[0] - args[1].dat->d_m[0]);
    base1 = base1+ dat1 *
      args[1].dat->size[0] *
      (start1 * args[1].stencil->stride[1] - args[1].dat->base[1] - args[1].dat->d_m[1]);
    base1 = base1+ dat1 *
      args[1].dat->size[0] *
      args[1].dat->size[1] *
      (start2 * args[1].stencil->stride[2] - args[1].dat->base[2] - args[1].dat->d_m[2]);
    p_a[1] = (char *)args[1].data + base1;

    p_a[2] = (char *)args[2].data;


    for ( int n_z=start_i; n_z<finish_i; n_z++ ){
      for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
        for ( int n_x=start[0]; n_x<start[0]+(end[0]-start[0])/SIMD_VEC; n_x++ ){
          //call kernel function, passing in pointers to data -vectorised
          for ( int i=0; i<SIMD_VEC; i++ ){
            update_halo_kernel2_xvel_plus_2_front(  (double * )p_a[0]+ i*1, (double * )p_a[1]+ i*1, &arg_gbl2[64*thr] );

          }

          //shift pointers to data x direction
          p_a[0]= p_a[0] + (dat0 * off0_0)*SIMD_VEC;
          p_a[1]= p_a[1] + (dat1 * off1_0)*SIMD_VEC;
        }

        for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
          //call kernel function, passing in pointers to data - remainder
          update_halo_kernel2_xvel_plus_2_front(  (double * )p_a[0], (double * )p_a[1], &arg_gbl2[64*thr] );


          //shift pointers to data x direction
          p_a[0]= p_a[0] + (dat0 * off0_0);
          p_a[1]= p_a[1] + (dat1 * off1_0);
        }

        //shift pointers to data y direction
        p_a[0]= p_a[0] + (dat0 * off0_1);
        p_a[1]= p_a[1] + (dat1 * off1_1);
      }
      //shift pointers to data z direction
      p_a[0]= p_a[0] + (dat0 * off0_2);
      p_a[1]= p_a[1] + (dat1 * off1_2);
    }
  }

  ops_timers_core(&c1,&t1);
  OPS_kernels[64].time += t1-t2;


  // combine reduction data
  for ( int thr=0; thr<nthreads; thr++ ){
    for ( int d=0; d<NUM_FIELDS; d++ ){
    }
  }
  ops_set_dirtybit_host(args, 3);

  ops_set_halo_dirtybit3(&args[0],range);
  ops_set_halo_dirtybit3(&args[1],range);

  #ifdef OPS_DEBUG
  ops_dump3(arg0.dat,"update_halo_kernel2_xvel_plus_2_front");
  ops_dump3(arg1.dat,"update_halo_kernel2_xvel_plus_2_front");
  #endif

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[64].count++;
  OPS_kernels[64].mpi_time += t2-t1;
  OPS_kernels[64].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[64].transfer += ops_compute_transfer(dim, range, &arg1);
}
