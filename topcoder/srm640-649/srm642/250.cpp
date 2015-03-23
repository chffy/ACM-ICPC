#include <iostream> 
#include <cstdio> 
#include <cstring> 
#include <algorithm> 
#include <vector> 
#include <cmath> 
using namespace std; 

const int N = 1e5 + 5; 
double f[N]; 

class WaitingForBus { 
public: 
    double whenWillBusArrive(vector <int> time, vector <int> prob, int s) { 
  if (s == 0) return 0.0; 
  int n = time.size(); 
  f[0] = 1; 
  double ans = 0; 
  for (int i = 0; i < s; ++i) { 
      for (int j = 0; j < n; ++j) { 
    double p = 1.0 * prob[j] / 100.0; 
    if (i + time[j] >= s) ans += f[i] * p * (i + time[j] - s); 
    else f[i + time[j]] += p * f[i]; 
      } 
  } 
  return ans; 
    } 
};
