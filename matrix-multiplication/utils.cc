#include<bits/stdc++.h>

using namespace std;

typedef unsigned long long c_id;

c_id gen_id() {
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(numeric_limits<c_id>::min(), numeric_limits<c_id>::max());
  return dis(gen);
}

vector<vector<double>> multiply(const vector<vector<double>> &Ma,const vector<vector<double>> &Mb) {
  int m = Ma.size();
  int n = Mb.size();
  int o = Mb[0].size();
  vector<vector<double>> ans(m, vector<double>(o, 0));

  for (int i = 0; i < m; ++i)
    for (int j = 0; j < o; ++j)
      for (int k = 0; k < n; ++k)
        ans[i][j] += Ma[i][k] * Mb[k][j];
  return ans;
}
