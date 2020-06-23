#!/bin/bash

cd ../user_program

echo "Demo fcntl sample_input_1"
cd ../input/sample_input_1
sudo ../../user_program/master 10 target_file fcntl #>> result_fcntl_1
