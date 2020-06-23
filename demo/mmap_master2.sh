#!/bin/bash

cd ../user_program

echo "Demo mmap sample_input_2"
cd ../input/sample_input_2
sudo ../../user_program/master 1 target_file mmap #>> result_mmap_2
