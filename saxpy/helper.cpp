#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
using namespace chrono;

void initialize(vector<int> &y,
    vector<int> &x,
    int &a)
{
    auto seed = system_clock::now().time_since_epoch().count();
    default_random_engine dre(seed);
    uniform_int_distribution<int> di(0 ,100);

    generate(x.begin(), x.end(), [&]{ return di(dre); });
    generate(y.begin(), y.end(), [&]{ return di(dre); });

    a = di(dre);
}

void validate(vector<int> reference,
    vector<int> test,
    size_t n)
{
    for(size_t i = 0; i < n; i++)
    {
        if(reference[i] != test[i])
        {
            cerr << "Failed at pos " << i << endl;
            exit(EXIT_FAILURE);
        }
    }

    cout << "Sucess" << endl;
}