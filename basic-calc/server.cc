#include <zmq.h>
#include <unistd.h>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <cassert>

const int MN = 1000;
char buffer[MN], line[MN], ans[MN];

int main () {
  void *context = zmq_ctx_new ();
  void *responder = zmq_socket (context, ZMQ_REP);
  int rc = zmq_bind (responder, "tcp://*:5555");
  assert (rc == 0);

  while (1) {
    zmq_recv (responder, buffer, 10, 0);
    printf ("Received : %s\n", buffer);

    int j = 0;
    for (int i = 0; i < MN and buffer[i] != '\0'; ++i)
      if (isdigit(buffer[i]) or buffer[i] == '+' or buffer[i] == '-' or buffer[i] == '*' or buffer[i] == '/')
        line[j++] = buffer[i];

    int op1 = 0;
    int i;
    for (i = 0; i < MN and isdigit(line[i]); ++i) {
      op1 *= 10;
      op1 += line[i] - '0';
    }

    char op = line[i++];

    int op2 = 0;
    for (; i < MN and isdigit(line[i]); ++i) {
      op2 *= 10;
      op2 += line[i] - '0';
    }

    if (op == '+') op1 += op2;
    if (op == '-') op1 -= op2;
    if (op == '*') op1 *= op2;
    if (op == '/') op1 /= op2;

    sprintf(ans,"%d", op1);

    zmq_send (responder, ans, MN, 0);
  }
  return 0;
}
