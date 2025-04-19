#! /bin/bash
bsub -b -J fengjw_Ag8192 -o runlog -exclu  -share_size 15000 -host_stack 2048 -n 32768 -cgsp 64 -q  q_ustc1  ../examples/dghf
