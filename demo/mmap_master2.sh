#!/bin/bash

cd ../user_program

echo "Demo mmap sample_input_2"
cd ../input/sample_input_2
sudo ../../user_program/master 1 target_file mmap

echo "dmesg results"
dmesg | grep master:
dmesg | grep slave:
dmesg | grep master: >> ../../dmesg/mmap_master_2
dmesg | grep -c slave: >> ../../dmesg/mmap_slave_2
