#!/bin/bash

cd ../user_program

echo "Demo mmap sample_input_1"
cd ../input/sample_input_1
sudo ../../user_program/master 10 target_file mmap #>> result_mmap_1
