gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1)

Use command "make" to build binary file named m11152013
Use command "make clean" to delete binary file

For ML-RCS, use command "list -l *.bilf AND_num, OR_num, and NOT_num", output the scheduled result under resource constraints.

For MR-LCS, use command "list -r *.bilf latency_num ", output the scheduled result under latency constraint.

"*" is mean input your .bilf file name


list -l case1.blif 30 20 8
list -r case1.blif 20

list -l case2.blif 5 3 1
list -r case2.blif 7