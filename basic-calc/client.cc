#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int MN = 1000;
char buffer[MN];
char ans[MN];

int main () {
  printf ("Welcome to the cool-calc\nConnecting to the server…\n");
  void *context = zmq_ctx_new ();
  void *requester = zmq_socket (context, ZMQ_REQ);
  zmq_connect (requester, "tcp://localhost:5555");

  while (true) {
    system("clear");
    printf("Cool-Cal : Perform an operation (q for quit) \n");
    //scanf("%[0-9 +*/-]s", buffer);
    fgets(buffer, MN, stdin);
    if (buffer[0] == 'q')
      break;
    zmq_send (requester, buffer, MN, 0);
    zmq_recv (requester, ans, 10, 0);
    printf ("The answer for this operation is  %s\nEnter to continue", ans);
    fgets(buffer, MN, stdin);
  }

  printf("\nBye bye (:\n");
  zmq_close (requester);
  zmq_ctx_destroy (context);
  return 0;
}
