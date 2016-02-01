#!/bin/bash

#exit script if any error is encountered during the build or
#application executions.
set -e
echo $OPS_INSTALL_PATH
cd $OPS_INSTALL_PATH

echo "************Testing C Applications *****************"
cd ../apps/c/CloverLeaf/
cd ../CloverLeaf/
#./generate.sh
#./test.sh
#cd ../CloverLeaf_3D/
#./generate.sh
#./test.sh
#cd ../CloverLeaf_3D_HDF5/
#./generate.sh
#./test.sh
cd ../poisson/
../../../translator/python/c/ops.py poisson.cpp
./test.sh
cd ../multiDim/
../../../translator/python/c/ops.py multidim.cpp
./test.sh
cd ../shsgc/
../../../translator/python/c/ops.py shsgc.cpp
./test.sh
cd ../mb_shsgc/Max_datatransfer
../../../../translator/python/c/ops.py shsgc.cpp
./test.sh

echo "************Testing Fortran Applications *****************"
cd $OPS_INSTALL_PATH
cd ../apps/fortran/shsgc
./test.sh
cd ../poisson
./test.sh
cd ../multiDim
./test.sh
