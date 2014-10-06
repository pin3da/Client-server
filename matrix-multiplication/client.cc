#include <zmqpp/zmqpp.hpp>
#include <bits/stdc++.h>

using namespace std;


// Basic req-rep client using REQ socket.
void process(zmqpp::socket &socket, int m, int n, int o, vector<vector<double>> Ma, vector<vector<double>> Mb) {
  zmqpp::message message;
  message << m << n << o;
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      message << Ma[i][j];

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < o; ++j)
      message << Mb[i][j];

  vector<vector<double>> result(n, vector<double>(o));
  socket.send(message);
  zmqpp::message answer;
  socket.receive(answer);

  for (int i = 0; i < m; ++i)
    for (int j = 0; j < o; ++j)
      answer >> result[i][j];


  cout << "Answer :\n";
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < o; ++j)
      cout << result[i][j] << " ";
    cout << '\n';
  }
}



int main(int argc, char *argv[]) {
  const string endpoint = "tcp://localhost:6666";
  zmqpp::context context;
  zmqpp::socket socket (context, zmqpp::socket_type::request);
  cout << "Connecting to : " << endpoint << endl;
  socket.connect(endpoint);

  int n, m, o;
  while (cin >> m >> n >> o) {
    vector<vector<double>> Ma(m, vector<double>(n));
    vector<vector<double>> Mb(n, vector<double>(o));

    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
        cin >> Ma[i][j];

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < o; ++j)
        cin >> Mb[i][j];

    process(socket, m, n, o, Ma, Mb);
  }

  cout << "Finished." << endl;
  return 0;
}
