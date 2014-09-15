using namespace std;
#include <zmqpp/zmqpp.hpp>
#include <bits/stdc++.h>

string worker_type = "ADD";

template<class T>
string to_string(T t) {
  stringstream ss;
  ss << t;
  return ss.str();
}

void dispatch(zmqpp::message &request, zmqpp::message &response) {
  string type;
  int op1, op2, ans;
  request >> type >> op1 >> op2;
  cout << "Received request : " << type << " " << op1 << " " << op2 << endl;
  if (type == "ADD")
    ans = op1 + op2;
  if (type == "SUB")
    ans = op1 - op2;
  if (type == "MUL")
    ans = op1 * op2;
  if (type == "DIV")
    ans = op1 / op2;

  response << ("Hi! I'm a worker type : " + worker_type + " and your answer is : " + to_string(ans));
}


int main(int argc, char *argv[]) {
  const string endpoint = "tcp://localhost:6667";
  zmqpp::context context;
  zmqpp::socket socket (context, zmqpp::socket_type::reply );
  cout << "Connecting to : " << endpoint << endl;
  socket.connect(endpoint);

  if (argc > 1)
    worker_type = argv[1];

  // Notify: worker arises.
  /*zmqpp::message greeting;
  greeting << "HI" << worker_type;
  socket.send(greeting);*/

  while (true) {
    cout << "Receiving message..." << endl;
    zmqpp::message message;
    socket.receive(message);
    zmqpp::message response;
    dispatch(message, response);
    socket.send(response);
  }
  cout << "Finished." << endl;
  return 0;
}
