#!/bin/bash

cd ../user_program

echo "Demo mmap my_input"
cd ../input/my_input
sudo ../../user_program/master 5 in mmap #>> result_mmap_3
