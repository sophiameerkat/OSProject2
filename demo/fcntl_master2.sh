#!/bin/bash

cd ../user_program

echo "Demo fcntl sample_input_2"
cd ../input/sample_input_2
sudo ../../user_program/master 1 target_file fcntl #>> result_fcntl_2
