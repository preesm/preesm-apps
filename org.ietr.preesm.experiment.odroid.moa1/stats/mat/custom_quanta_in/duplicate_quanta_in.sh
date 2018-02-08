#!/bin/bash
        
for i in `seq 65 318`;
do
    cp quanta_in_TestComPC_64.xls quanta_in_TestComPC_$i.xls
    echo "generated 64 -> $i"
done

for i in `seq 606 860`;
do
    cp quanta_in_TestComPC_319.xls quanta_in_TestComPC_$i.xls
    echo "generated 319 -> $i"
done

for i in `seq 861 1115`;
do
    cp quanta_in_TestComPC_327.xls quanta_in_TestComPC_$i.xls
    echo "generated 327 -> $i"
done

for i in `seq 1116 1370`;
do
    cp quanta_in_TestComPC_335.xls quanta_in_TestComPC_$i.xls
    echo "generated 335 -> $i"
done

for i in `seq 1371 1625`;
do
    cp quanta_in_TestComPC_343.xls quanta_in_TestComPC_$i.xls
    echo "generated 343 -> $i"
done

for i in `seq 1626 1880`;
do
    cp quanta_in_TestComPC_351.xls quanta_in_TestComPC_$i.xls
    echo "generated 351 -> $i"
done
