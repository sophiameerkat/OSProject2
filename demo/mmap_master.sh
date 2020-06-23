#!/bin/bash

cd ../user_program

echo "Demo mmap sample_input_1"
cd ../input/sample_input_1
sudo ../../user_program/master 10 target_file_1 target_file_2 target_file_3 target_file_4 target_file_5 target_file_6 target_file_7 target_file_8 target_file_9 target_file_10 mmap

echo "Demo mmap sample_input_2"
cd ../sample_input_2
sudo ../../user_program/master 1 target_file mmap

echo "Demo mmap my_input"
cd ../my_input
sudo ../../user_program/master 5 in_1 in_2 in_3 in_4 in_5 mmap
