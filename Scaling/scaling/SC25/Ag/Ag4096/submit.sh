#! /bin/bash
bsub -b -J fengjw_LAOSTO -o runlog -exclu  -share_size 15000 -host_stack 2048 -n 8192 -cgsp 64 -q  q_ustc1  /home/export/online1/mdt00/shisuan/swustcfd/fengjw/DG-TDDF/DGTDDFT-MFFT-Slave/DGTDDFT/examples/dghf
