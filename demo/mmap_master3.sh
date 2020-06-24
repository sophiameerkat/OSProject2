#!/bin/bash

cd ../user_program

echo "Demo mmap my_input"
cd ../input/my_input
sudo ../../user_program/master 5 in mmap

echo "dmesg results"
dmesg | grep master:
dmesg | grep slave:
dmesg | grep master: >> ../../dmesg/mmap_master_3
dmesg | grep -c slave: >> ../../dmesg/mmap_slave_3
