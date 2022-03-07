#!/bin/bash

while true; do
    ./data > data.in
    ./C < data.in > ans.out
    ./C-baoli < data.in > baoli.out
    if diff ans.out baoli.out; then
        printf AC
    else 
        echo WA
        exit 0
    fi
done