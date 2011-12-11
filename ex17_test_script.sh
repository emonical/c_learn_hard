#!/bin/bash

set -e

make clean
make ex17 

./ex17 db.dat c
./ex17 db.dat s 1 bob bob@email.com
./ex17 db.dat s 2 bob bob@email.com for_teh_awesome
./ex17 db.dat l
./ex17 db.dat d 1
./ex17 db.dat f name bob
./ex17 db.dat f email bob@email.com
./ex17 db.dat f interests for_teh_awesome
