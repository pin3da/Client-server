#include <bits/stdc++.h>
#include <zmqpp/zmqpp.hpp>
#include "./utils.cc"
#define D(x) cout << #x " = " << (x) << endl

using namespace std;


struct entry {
  string client_id;
  vector<vector<double>> ans;
  int missing;
  bool operator < (const entry &o) const {
    return client_id < o.client_id;
  }
};

void process_client(zmqpp::message &req, zmqpp::socket &backend) {
  string address, empty;
  req >> address >> empty;
  assert(empty.size() == 0);
  int m, n, o;
  req >> m >> n >> o;
  vector<vector<double>> Ma(m, vector<double> (n)), Mb(n, vector<double>(o));

  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      req >> Ma[i][j];

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < o; ++j)
      req >> Mb[i][j];


  zmqpp::message message;
  message << address << empty;
  message << m << n << o;

  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      message << Ma[i][j];

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < o; ++j)
      message << Mb[i][j];

  backend.send(message);
  cout << "Message forwarded to backend, waiting for an answer" << endl;
}

void process_worker(zmqpp::message &req, zmqpp::message &res) {
  // jus streaming answer from worker
  res.copy(req);
}

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
        zmqpp::message req, res;
        frontend.receive(req);
        process_client(req, backend);
      }

      if (poller.has_input(backend)) {
        cout << "Reading message from worker" << endl;
        zmqpp::message req, res;
        backend.receive(req);
        process_worker(req, res);
        frontend.send(res);
      }
    }
  }

  return 0;
}
