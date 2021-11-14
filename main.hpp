#include <cmath>
#include <climits>
#include <iostream>
using namespace std;
#include <vector>
using namespace std;
#include <map>
using namespace std;
#include <list>
using namespace std;
#include <algorithm>
using namespace std;
#include <stack>
using namespace std;

#ifndef CITY_H
#define CITY_H

struct city_t {
  double x;
  double y;
};

inline bool TIME_TEN(clock_t t1, clock_t t2) { return  double(t1-t2)/CLOCKS_PER_SEC < 0.20; }
inline bool TIME_HALF(clock_t t1, clock_t t2) { return  double(t1-t2)/CLOCKS_PER_SEC < 0.99; }
inline bool TIME_MAX(clock_t t1, clock_t t2) { return  double(t1-t2)/CLOCKS_PER_SEC < 1.99; }
inline bool TIME_U(clock_t t1, clock_t t2) { return  double(t1-t2)/CLOCKS_PER_SEC > 1.99; }

#endif