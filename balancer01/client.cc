#include <zmqpp/zmqpp.hpp>
#include <bits/stdc++.h>

using namespace std;


// Basic req-rep client using REQ socket.
void process(zmqpp::socket &socket, string &order) {
  zmqpp::message message;
  message << order;
  socket.send(message);
  string answer;
  socket.receive(answer);
  cout << "Answer : " << answer << endl;
}

int main(int argc, char *argv[]) {
  const string endpoint = "tcp://localhost:6666";
  zmqpp::context context;
  zmqpp::socket socket (context, zmqpp::socket_type::request);
  cout << "Connecting to : " << endpoint << endl;
  socket.connect(endpoint);

  string order;
  while (cin >> order) {
    process(socket, order);
  }

  cout << "Finished." << endl;
  return 0;
}
