Balancer01
==========

This is my first attempt to make a load-balancer broker using 0mq and
0mzpp binding.

Read [the ZMQ Guide (chapter two)](http://zguide.zeromq.org/page:all#header-25) to understand what I'm trying to do.

In this case, clients send any text to the broker and after that the
worker responsible for carrying out the task will respond with its own id.

The strategy to assign the work is given by the socket type (Round-robin for this case).

### Compile

    make


### Dependencies

- To install the 0mq 'highlevel' C++ binding go to [zmqpp Repository](https://github.com/zeromq/zmqpp)


_____
Manuel Pineda
