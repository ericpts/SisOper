#!/bin/bash

make -j`nproc`
./random_ints | ./main | ./acum
