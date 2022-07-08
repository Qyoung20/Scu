#!/bin/bash
echo "----------Make--------"
make; 

echo
echo "----------Creating Files----------"
# cat /dev/random | head -c <bytecount>
cat /dev/random | head -c 100000 > src.dat
cat /dev/random | head -c 1000000 > src_.dat


echo  "----------Running steps----------"
echo "Step 3"
./1 src.dat dst.dat

echo "Step 4"
./2 src.dat dst.dat

echo "Step 5"
./3 src.dat dst.dat
./3 src_.dat dst.dat

make clean;
echo
