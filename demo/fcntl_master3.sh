#!/bin/bash

cd ../user_program

echo "Demo fcntl my_input"
cd ../input/my_input
sudo ../../user_program/master 5 in fcntl #>> result_fcntl_3
