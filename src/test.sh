#!/bin/sh


run_test()
{
    local k=$1
    local list_size=$2
    echo -n "size = $list_size / k = $k: "
    $binary $k $list_size
}


max_list_size=20
binary=./k-reverse-list
set -e


run_test 1 $max_list_size

for list_size in $(seq 1 $max_list_size); do
    for k in $(seq 2 $list_size); do
        run_test $k $list_size
    done
done
echo All tests passed
