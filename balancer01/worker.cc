using namespace std;
#include <zmqpp/zmqpp.hpp>
#include <bits/stdc++.h>

string worker_id = "-1";

void dispatch(zmqpp::message &request, string &response) {
  string message;
  request >> message;
  cout << "Received request : " << message << endl;
  response = "Hi! I'm the worker number : " + worker_id;
}


int main(int argc, char *argv[]) {
  const string endpoint = "tcp://localhost:6667";
  zmqpp::context context;
  zmqpp::socket socket (context, zmqpp::socket_type::reply );
  cout << "Connecting to : " << endpoint << endl;
  socket.connect(endpoint);

  if (argc > 1)
    worker_id = argv[1];

  while (true) {
    cout << "Receiving message..." << endl;
    zmqpp::message message;
    socket.receive(message);
    string response;
    dispatch(message, response);
    socket.send(response);
  }
  cout << "Finished." << endl;
  return 0;
}
