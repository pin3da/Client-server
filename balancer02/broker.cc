#include <bits/stdc++.h>
#include <zmqpp/zmqpp.hpp>

using namespace std;


int main() {
  zmqpp::context context;
  zmqpp::socket frontend(context, zmqpp::socket_type::router);
  zmqpp::socket backend(context, zmqpp::socket_type::dealer);

  frontend.bind("tcp://*:6666");
  backend.bind("tcp://*:6667");

  zmqpp::poller poller;
  poller.add(frontend, zmqpp::poller::poll_in);
  poller.add(backend , zmqpp::poller::poll_in);

  while (true) {
    if (poller.poll()) {
      if (poller.has_input(frontend)) {
        cout << "Reading message from client " << endl;
        do {
          zmqpp::message message;
          frontend.receive(message);
          backend.send(message);
        } while(frontend.has_more_parts());
      }

      if (poller.has_input(backend)) {
        cout << "Reading message from worker" << endl;

        zmqpp::message message, copy;
        backend.receive(message);
        copy.copy(message);
        string text;
        copy >> text;
        if (text == "HI") {
          string type;
          copy >> type;
          cout << "New worker with type : " << type << endl;
        } else {
          frontend.send(message);
          while (backend.has_more_parts()) {
            backend.receive(message);
            frontend.send(message);
          }
        }
      }
    }
  }

  return 0;
}
