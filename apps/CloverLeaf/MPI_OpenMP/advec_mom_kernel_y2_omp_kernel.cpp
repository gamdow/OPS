//
// auto-generated by ops.py on 2014-07-10 14:54
//

#ifdef _OPENMP
#include <omp.h>
#endif

//user function

inline void advec_mom_kernel_y2( double *pre_vol, double *post_vol,
                          const double *volume,
                          const double *vol_flux_x) {

  post_vol[OPS_ACC1(0,0)]  = volume[OPS_ACC2(0,0)] ;
  pre_vol[OPS_ACC0(0,0)]   = post_vol[OPS_ACC1(0,0)]  + vol_flux_x[OPS_ACC3(1,0)] - vol_flux_x[OPS_ACC3(0,0)];

}



// host stub function
void ops_par_loop_advec_mom_kernel_y2(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {

  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(18,"advec_mom_kernel_y2");
  ops_timers_core(&c1,&t1);


  int  offs[4][2];
  ops_arg args[4] = { arg0, arg1, arg2, arg3};


  //compute locally allocated range for the sub-block

  int start[2];
  int end[2];

  #ifdef OPS_MPI
  #error this is not block, but dataset
  sub_block_list sb = OPS_sub_block_list[block->index];
  for ( int n=0; n<2; n++ ){
    start[n] = sb->gbl_disp[n];end[n] = sb->gbl_disp[n]+sb->gbl_size[n];
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->gbl_disp[n];
    }
    else {
      end[n] = sb->gbl_size[n];
    }
  }
  #else //OPS_MPI
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif //OPS_MPI
  #ifdef OPS_DEBUG
  ops_register_args(args, "advec_mom_kernel_y2");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off2D(1, &start[0],
      &end[0],args[0].dat->size, args[0].stencil->stride) - offs[0][0];

  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  offs[1][1] = off2D(1, &start[0],
      &end[0],args[1].dat->size, args[1].stencil->stride) - offs[1][0];

  offs[2][0] = args[2].stencil->stride[0]*1;  //unit step in x dimension
  offs[2][1] = off2D(1, &start[0],
      &end[0],args[2].dat->size, args[2].stencil->stride) - offs[2][0];

  offs[3][0] = args[3].stencil->stride[0]*1;  //unit step in x dimension
  offs[3][1] = off2D(1, &start[0],
      &end[0],args[3].dat->size, args[3].stencil->stride) - offs[3][0];



  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int dat0 = args[0].dat->elem_size;
  int off1_0 = offs[1][0];
  int off1_1 = offs[1][1];
  int dat1 = args[1].dat->elem_size;
  int off2_0 = offs[2][0];
  int off2_1 = offs[2][1];
  int dat2 = args[2].dat->elem_size;
  int off3_0 = offs[3][0];
  int off3_1 = offs[3][1];
  int dat3 = args[3].dat->elem_size;


  #ifdef _OPENMP
  int nthreads = omp_get_max_threads( );
  #else
  int nthreads = 1;
  #endif
  xdim0 = args[0].dat->size[0]*args[0].dat->dim;
  xdim1 = args[1].dat->size[0]*args[1].dat->dim;
  xdim2 = args[2].dat->size[0]*args[2].dat->dim;
  xdim3 = args[3].dat->size[0]*args[3].dat->dim;

  //Halo Exchanges
  ops_halo_exchanges(args,4,range);

  ops_H_D_exchanges_host(args, 4);


  ops_timers_core(&c2,&t2);
  OPS_kernels[18].mpi_time += t2-t1;


  #pragma omp parallel for
  for ( int thr=0; thr<nthreads; thr++ ){

    int y_size = end[1]-start[1];
    char *p_a[4];

    int start_i = start[1] + ((y_size-1)/nthreads+1)*thr;
    int finish_i = start[1] + MIN(((y_size-1)/nthreads+1)*(thr+1),y_size);

    //get address per thread
    int start0 = start[0];
    int start1 = start_i;

    //set up initial pointers 
    int base0 = dat0 * 1 * 
    (start0 * args[0].stencil->stride[0] - args[0].dat->base[0] - args[0].dat->d_m[0]);
    base0 = base0+ dat0 *
      args[0].dat->size[0] *
      (start1 * args[0].stencil->stride[1] - args[0].dat->base[1] - args[0].dat->d_m[1]);
    p_a[0] = (char *)args[0].data + base0;

    int base1 = dat1 * 1 * 
    (start0 * args[1].stencil->stride[0] - args[1].dat->base[0] - args[1].dat->d_m[0]);
    base1 = base1+ dat1 *
      args[1].dat->size[0] *
      (start1 * args[1].stencil->stride[1] - args[1].dat->base[1] - args[1].dat->d_m[1]);
    p_a[1] = (char *)args[1].data + base1;

    int base2 = dat2 * 1 * 
    (start0 * args[2].stencil->stride[0] - args[2].dat->base[0] - args[2].dat->d_m[0]);
    base2 = base2+ dat2 *
      args[2].dat->size[0] *
      (start1 * args[2].stencil->stride[1] - args[2].dat->base[1] - args[2].dat->d_m[1]);
    p_a[2] = (char *)args[2].data + base2;

    int base3 = dat3 * 1 * 
    (start0 * args[3].stencil->stride[0] - args[3].dat->base[0] - args[3].dat->d_m[0]);
    base3 = base3+ dat3 *
      args[3].dat->size[0] *
      (start1 * args[3].stencil->stride[1] - args[3].dat->base[1] - args[3].dat->d_m[1]);
    p_a[3] = (char *)args[3].data + base3;


    for ( int n_y=start_i; n_y<finish_i; n_y++ ){
      for ( int n_x=start[0]; n_x<start[0]+(end[0]-start[0])/SIMD_VEC; n_x++ ){
        //call kernel function, passing in pointers to data -vectorised
        #pragma simd
        for ( int i=0; i<SIMD_VEC; i++ ){
          advec_mom_kernel_y2(  (double * )p_a[0]+ i*1, (double * )p_a[1]+ i*1, (const double * )p_a[2]+ i*1,
           (const double * )p_a[3]+ i*1 );

        }

        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_0)*SIMD_VEC;
        p_a[1]= p_a[1] + (dat1 * off1_0)*SIMD_VEC;
        p_a[2]= p_a[2] + (dat2 * off2_0)*SIMD_VEC;
        p_a[3]= p_a[3] + (dat3 * off3_0)*SIMD_VEC;
      }

      for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
        //call kernel function, passing in pointers to data - remainder
        advec_mom_kernel_y2(  (double * )p_a[0], (double * )p_a[1], (const double * )p_a[2],
           (const double * )p_a[3] );


        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_0);
        p_a[1]= p_a[1] + (dat1 * off1_0);
        p_a[2]= p_a[2] + (dat2 * off2_0);
        p_a[3]= p_a[3] + (dat3 * off3_0);
      }

      //shift pointers to data y direction
      p_a[0]= p_a[0] + (dat0 * off0_1);
      p_a[1]= p_a[1] + (dat1 * off1_1);
      p_a[2]= p_a[2] + (dat2 * off2_1);
      p_a[3]= p_a[3] + (dat3 * off3_1);
    }
  }

  ops_timers_core(&c1,&t1);
  OPS_kernels[18].time += t1-t2;

  ops_set_dirtybit_host(args, 4);

  ops_set_halo_dirtybit3(&args[0],range);
  ops_set_halo_dirtybit3(&args[1],range);

  #ifdef OPS_DEBUG
  ops_dump3(arg0.dat,"advec_mom_kernel_y2");
  ops_dump3(arg1.dat,"advec_mom_kernel_y2");
  #endif

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[18].count++;
  OPS_kernels[18].mpi_time += t2-t1;
  OPS_kernels[18].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[18].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[18].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[18].transfer += ops_compute_transfer(dim, range, &arg3);
}
