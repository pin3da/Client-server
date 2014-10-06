Matrix Multiplication
=====================

Distributed matrix multiplication example in 0mqpp

At this moment, the broker just forward the whole matrix and the available worker will solve the problem.

The tasks are round-robined among all connected workers.

### Input format

One line with the dimensions of the matrices:

    m n o

Followed by m X n and n X o matrices.

Example:

    3 4 2

    1 4 5 6
    2 3 4 6
    4 5 2 6

    7 4
    8 1
    7 4
    7 2

### Compile

    make


### Dependencies

- To install the 0mq 'highlevel' C++ binding go to [zmqpp Repository](https://github.com/zeromq/zmqpp)


_____
MP
