#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
using namespace chrono;

void initialize(vector<int> &x)
{
    auto seed = system_clock::now().time_since_epoch().count();
    default_random_engine dre(seed);
    uniform_int_distribution<int> di(0 ,100);

    generate(x.begin(), x.end(), [&]{ return di(dre); });
}