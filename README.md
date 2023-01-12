# Project: Kd-tree Version1

## Authors

|Name|Email|
|--------|--------|
|Haozheng Huang|haozheng.huang@tum.de|
|Yichao Gao|yichao.gao@tum.de|

## Instruction

The k-d tree is a binary tree in which every node is a k-dimensional point. Every non-leaf node can be thought of as implicitly generating a splitting hyperplane that divides the space into two parts, known as half-spaces. Points to the left of this hyperplane are represented by the left subtree of that node and points to the right of the hyperplane are represented by the right subtree. The hyperplane direction is chosen in the following way: every node in the tree is associated with one of the k dimensions, with the hyperplane perpendicular to that dimension's axis. You can find more [here](https://en.wikipedia.org/wiki/K-d_tree)

![image](figures/kd-example.png)
(Source: https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kdtrees.pdf)

We have generated the following functions:
- Kd-tree construction
- Points addition and deletion
- Read data from a csv file

## How to build and run
From the csv file we can get the following data:

|Points| |
|--------|--------|
|2,5,0|3,8,-1|
|6,3,-2|8,9,-5|
|1,4,5|0,3,7|
|-3,5,11|-2,10,-6|
|9,10,-4|-3,3,3|

Now we have a `Cmakelist.txt`. To build and run:

1. Run the command `cmake .` in the terminal.

   Then you will get a `Makefile` in the folder.

2. Run `make` in the terminal. You will get the exe file: `main`

3. Run it. You will get this result on the terminal.

```bash
              /-----(9, 10, -4)
       /-----(8, 9, -5)
/-----(3, 8, -1)
|      \-----(6, 3, -2)
(2, 5, 0)
|      /-----(-3, 5, 11)
|      |      \-----(-2, 10, -6)
\-----(1, 4, 5)
       \-----(0, 3, 7)
              \-----(-3, 3, 3)
after deletion of point: (1, 4, 5)
              /-----(9, 10, -4)
       /-----(8, 9, -5)
/-----(3, 8, -1)
|      \-----(6, 3, -2)
(2, 5, 0)
|      /-----(-2, 10, -6)
\-----(-3, 5, 11)
       \-----(0, 3, 7)
              \-----(-3, 3, 3)

```
Judging by the results, we accomplished our stated goals of reading data from file, constructiong, addition and deleting trees well.

## How to test our search function

In the folder `test` we have a `kd-search-test.cpp` based on the Gtest frame.

To test the function of KNN:

1. Go to the folder `test` and run these commands:
```bash
cmake .
make
```
2. Run the exe file
```bash
./kd-search-test
```
3. If all is right, you will see:
```bash
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from treetest
[ RUN      ] treetest.KNN_search
point overlap at dimension 0
[       OK ] treetest.KNN_search (0 ms)
[----------] 1 test from treetest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
```
