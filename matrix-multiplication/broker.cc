#include <bits/stdc++.h>
#include <zmqpp/zmqpp.hpp>
#include "./utils.cc"
#define D(x) cout << #x " = " << (x) << endl

using namespace std;

struct entry {
  vector<vector<double>> ans;
  int m,o;
  int parts;
  entry(){}
  entry(int m, int o, int p) : m(m), o(o), parts(p) {
    ans.assign(m, vector<double> (o, 0));
  }

  /*
  bool operator < (const entry &o) const {
    return client_id < o.client_id;
  }*/
};

map<string, entry> state;
const int rows_per_worker = 10;

void process_client(zmqpp::message &req, zmqpp::socket &backend) {
  string address, empty;
  req >> address >> empty;
  cout << "Message from : " << address << endl;
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

  int parts = (m + rows_per_worker - 1) / rows_per_worker;
  state[address] = entry(m, o, parts);

  for (int k = 0; k < parts; ++k) {
    zmqpp::message message;
    message << address << empty;
    message << address << k;
    message << rows_per_worker << n << o;

    for (int i = 0; i < rows_per_worker; ++i)
      for (int j = 0; j < n; ++j)
        if (i + rows_per_worker * k < m)
          message << Ma[i + rows_per_worker * k][j];
        else
          message << 0; //dummy zeroes

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < o; ++j)
        message << Mb[i][j];

    backend.send(message);
    cout << "Part forwarded to backend, waiting for an answer" << endl;
  }

}

bool process_worker(zmqpp::message &req, zmqpp::message &res) {
  string address, empty;
  int part;
  req >> address >> empty;
  assert(empty.size() == 0);
  req >> address >> part;
  if (state.count(address) == 0)
    cout << "Error : client not found" << endl;

  int o = state[address].o;
  int m = state[address].m;
  double tmp;
  vector<vector<double>> &ans = state[address].ans;
  for (int i = 0; i < rows_per_worker; ++i) {
    for (int j = 0; j < o; ++j) {
      if (i + part * rows_per_worker < m)
        req >> ans[i + part * rows_per_worker][j];
      else
        req >> tmp;
    }
  }

  state[address].parts--;
  if (state[address].parts > 0)
    return false;
  res << address << empty;

  for (int i = 0; i < m; ++i)
    for (int j = 0; j < o; ++j)
      res << ans[i][j];

  return true;

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
        if (process_worker(req, res))
          frontend.send(res);
      }
    }
  }

  return 0;
}
