#include <zmqpp/zmqpp.hpp>
#include <bits/stdc++.h>

using namespace std;


// Basic req-rep client using REQ socket.
void process(zmqpp::socket &socket, string &order, int op1, int op2) {
  zmqpp::message message;
  message << order << op1 << op2;
  socket.send(message);
  zmqpp::message answer;
  socket.receive(answer);
  string text;
  answer >> text;
  cout << "Answer : " << text << endl;
}

int main(int argc, char *argv[]) {
  const string endpoint = "tcp://localhost:6666";
  zmqpp::context context;
  zmqpp::socket socket (context, zmqpp::socket_type::request);
  cout << "Connecting to : " << endpoint << endl;
  socket.connect(endpoint);

  string order;
  int op1, op2;
  while (cin >> order) {
    if (order == "exit")
      break;
    cin >> op1 >> op2;
    process(socket, order, op1, op2);
  }

  cout << "Finished." << endl;
  return 0;
}
