#include <iostream>
#include "hw1.h"

void __print(int x) {std::cerr << x;}
void __print(long x) {std::cerr << x;}
void __print(long long x) {std::cerr << x;}
void __print(unsigned x) {std::cerr << x;}
void __print(unsigned long x) {std::cerr << x;}
void __print(unsigned long long x) {std::cerr << x;}
void __print(float x) {std::cerr << x;}
void __print(double x) {std::cerr << x;}
void __print(long double x) {std::cerr << x;}
void __print(char x) {std::cerr << '\'' << x << '\'';}
void __print(const char *x) {std::cerr << '\"' << x << '\"';}
void __print(const std::string &x) {std::cerr << '\"' << x << '\"';}
void __print(bool x) {std::cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const std::pair<T, V> &x) {std::cerr << '{'; __print(x.first); std::cerr << ','; __print(x.second); std::cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; std::cerr << '{'; for (auto &i: x) std::cerr << (f++ ? "," : ""), __print(i); std::cerr << "}";}
void _print() {std::cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) std::cerr << ", "; _print(v...);}
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(x...) std::cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

int main() {
    auto x = algebra::zeros(5, 5);
    algebra::show(x);
    std::cout << '\n';
    x = algebra::random(5, 5, 1.1, 10.2);
    algebra::show(x);
    return 0;
}