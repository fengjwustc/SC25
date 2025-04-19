#! /bin/bash
bsub -b -J fengjw_Ag32768 -o runlog -exclu  -share_size 15000 -host_stack 2048 -n 524288 -cgsp 64 -q  q_ustc1  ../examples/dghf
