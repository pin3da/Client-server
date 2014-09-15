Balancer02
==========

Quite similar to [balancer01](https://github.com/pin3da/Client-server/tree/master/balancer01)


In this case, clients perform an arithmetic operation with the below format:

    [ADD | SUB | MUL | DIV] op1 op2
    or "exit" to finish

Should be several workers for any operation, with this in mind the broker will select some worker (designated for the current operation) randomly.

### Compile

    make


### Dependencies

- To install the 0mq 'highlevel' C++ binding go to [zmqpp Repository](https://github.com/zeromq/zmqpp)


_____
Manuel Pineda
