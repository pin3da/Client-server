using namespace std;
#include <bits/stdc++.h>
#include "../utils.cc"

int main() {
  int m, n, o;
  while (cin >> m >> n >> o) {
    vector<vector<double>> Ma(m, vector<double>(n)), Mb(n, vector<double> (o));
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
        cin >> Ma[i][j];

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < o; ++j)
        cin >> Mb[i][j];

    vector<vector<double>>  ans = multiply(Ma, Mb);

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < o; j++)
        cout << ans[i][j] << " ";
      cout << endl;
    }
  }
  return 0;
}
