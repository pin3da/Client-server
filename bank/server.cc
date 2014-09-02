using namespace std;
#include <zmqpp/zmqpp.hpp>
#include <bits/stdc++.h>


void check(zmqpp::message &request, string & response) {

}

void add(zmqpp::message &request, string & response) {

}

void withdraw(zmqpp::message &request, string & response) {

}
void transfer(zmqpp::message &request, string & response) {

}

void dispatch(zmqpp::message &request, string &response) {
  response = "Manuel was here";
  string command;
  request >> command;
  if      (command == "check") check(request, response);
  else if (command == "add") add(request, response);
  else if (command == "withdraw") withdraw(request, response);
  else if (command == "transfer") transfer(request, response);
  else response = "Not supported";
}


int main(int argc, char *argv[]) {
  const string endpoint = "tcp://*:4242";
  zmqpp::context context;
  zmqpp::socket socket (context, zmqpp::socket_type::reply );
  cout << "Binding to " << endpoint << "..." << endl;
  socket.bind(endpoint);

  while (true) {
    cout << "Receiving message..." << endl;
    zmqpp::message message;
    socket.receive(message);
    string response;
    dispatch(message, response);
    zmqpp::message message2;
    message2.copy(message);
    string command;
    int id;
    message2 >> command >> id;
    cout << "Received command :\"" << command << "\" from id : " << id << endl;
    socket.send(response);
  }
  cout << "Finished." << endl;
  return 0;
}
