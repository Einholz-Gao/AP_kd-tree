# Project: Kd-tree Version1

## Instruction

The k-d tree is a binary tree in which every node is a k-dimensional point. Every non-leaf node can be thought of as implicitly generating a splitting hyperplane that divides the space into two parts, known as half-spaces. Points to the left of this hyperplane are represented by the left subtree of that node and points to the right of the hyperplane are represented by the right subtree. The hyperplane direction is chosen in the following way: every node in the tree is associated with one of the k dimensions, with the hyperplane perpendicular to that dimension's axis. You can find more [here](https://en.wikipedia.org/wiki/K-d_tree)

![image](figures/kd-example.png)
(Source: https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kdtrees.pdf)

We have generated the following functions:
- Kd-tree construction
- Points addition and deletion
- Read data from a csv file

|Points|
|--------|
|2,5,0|
|3,8,-1|
|6,3,-2|
|8,9,-5|
|1,4,5|
|0,3,7|
|-3,5,11|
|-2,10,-6|
|9,10,-4|
|-3,3,3|
## Authors

|Name|Email|
|--------|--------|
|Haozheng Huang|haozheng.huang@tum.de|
|Yichao Gao|yichao.gao@tum.de|


## How to build and run
We have a `Makefile` in the folder `/src`.

Now go to the `/src` folder and run the command `make` in the terminal.

Then you will get a executable file `main`.

Run it. You will get the output:

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



