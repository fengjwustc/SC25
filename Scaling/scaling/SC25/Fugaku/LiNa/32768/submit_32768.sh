#!/bin/bash
#PJM -L  "node=32768"                          # Number of assign node 8 (1 dimention format)
#PJM -L  "freq=2200,eco_state=2"                         
#PJM -L  "rscgrp=middle"         # Specify resource group
#PJM -L  "elapse=00:60:00"                 # Elapsed time limit 1 hour
#PJM -x "PJM_LLIO_GFSCACHE=/vol0004:/vol0002"
#PJM --mpi "max-proc-per-node=4"          # Maximum number of MPI processes created per node
#PJM -s                                    # Statistical information output
#PJM -g hp230257
#PJM --name dg-26wLiNa

set -x
mkdir ./log
/home/system/tool/dir_transfer -l ./log  /home/u12219/data/guozhuoqiang/DG/DGTEST/lib /home/u12219/data/zhangxiangyu/DG/libs/heffte/lib /home/u12219/data/guozhuoqiang/DG/DGTEST/software
export OMPI_MCA_plm_ple_memory_allocation_policy=bind_local
export PLE_MPI_STD_EMPTYFILE=off
export OMP_NUM_THREADS=12
. /vol0004/apps/oss/spack/share/spack/setup-env.sh
spack load elpa
export LD_LIBRARY_PATH=/home/u12219/data/guozhuoqiang/DG/DGTEST/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/home/u12219/data/zhangxiangyu/DG/libs/heffte/lib:$LD_LIBRARY_PATH
mpiexec -stdout-proc ./output.%j/%/1000r/stdout -stderr-proc /home/u12219/vol2/zhangxiangyu/output/output.%j/%/1000r/stderr /home/u12219/scratch/zhangxiangyu/Forfugaku/examples/dghf 