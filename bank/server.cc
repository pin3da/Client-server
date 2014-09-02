using namespace std;
#include <zmqpp/zmqpp.hpp>
#include <bits/stdc++.h>

template <class T>
string to_string(T t) {
  stringstream ss;
  ss<<t;
  return t.str();
}

unordered_map<int, int> accounts;

void regis(zmqpp::message &request, string &response) {
  int id;
  request >> id;
  if (accounts.count(id))
    response = "The account is already taken";
  else {
    accounts[id] = 0;
    response = "The account was successfully created";
  }
}

void check(zmqpp::message &request, string &response) {
  int id;
  request >> id;
  if (accounts.count(id))
    response = to_string(accounts[id]);
  else
    response = "This account does not exist";
}

void add(zmqpp::message &request, string &response) {
  int id, value;
  request >> id >> value;
  if (accounts.count(id)) {
    accounts[id] += value;
    response = "Value added, new amount : " + to_string(accounts[id]);
  } else
    response = "This account does not exist";
}

void withdraw(zmqpp::message &request, string &response) {
  int id, value;
  request >> id >> value;
  if (accounts.count(id)) {
    if (accounts[id] >= value) {
      accounts[id] -= value;
      response = "Value withdrawn, new amount : " + to_string(accounts[id]);
    } else {
      response = "Not enough Funds, Operation Canceled";
    }
  } else
    response = "This account does not exist";
}

void transfer(zmqpp::message &request, string &response) {
  int id, value, dest_id;
  request >> id >> value >> dest_id;
  if (accounts.count(id)) {
    if (accounts[id] >= value) {
      accounts[id] -= value;
      accounts[dest_id] += value;
      response = "Transaction done, new amount : " + to_string(accounts[id]);
    } else {
      response = "Not enough Funds, Operation Canceled";
    }
  } else
    response = "This account does not exist";
}

void dispatch(zmqpp::message &request, string &response) {
  response = "Manuel was here";
  string command;
  request >> command;
  if      (command == "register") regis(request, response);
  else if (command == "check") check(request, response);
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
