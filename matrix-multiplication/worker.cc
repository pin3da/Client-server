using namespace std;
#include <zmqpp/zmqpp.hpp>
#include <bits/stdc++.h>
#include "utils.cc"
#define D(x) cout << #x " = " << (x) << endl


void dispatch(zmqpp::message &req, zmqpp::message &res) {
  int m, n, o;
  string address;
  int part;
  req >> address >> part;

  req >> m >> n >> o;
  vector<vector<double>> Ma(m, vector<double> (n)), Mb(n, vector<double>(o));

  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      req >> Ma[i][j];

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < o; ++j)
      req >> Mb[i][j];

  vector<vector<double>> ans = multiply(Ma, Mb);

  res << address << part;
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < o; ++j)
      res << ans[i][j];
}


int main(int argc, char *argv[]) {
  const string endpoint = "tcp://localhost:6667";
  zmqpp::context context;
  zmqpp::socket socket (context, zmqpp::socket_type::reply );
  cout << "Connecting to : " << endpoint << endl;
  socket.connect(endpoint);



  while (true) {
    cout << "Receiving message..." << endl;
    zmqpp::message message;
    socket.receive(message);
    zmqpp::message response;
    dispatch(message, response);
    socket.send(response);
    cout << "Responded" << endl;
  }
  cout << "Finished." << endl;
  return 0;
}
