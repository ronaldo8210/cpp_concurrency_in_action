/***********************************************************************
#   > File Name   : code_4_7.cpp
#   > Author      : ronaldo
#   > Description : 
#   > Create Time : 2019-05-23 11:07:47
***********************************************************************/

#include <future>
#include <iostream>
#include <string>

using namespace std;

struct X {
  int foo(int m, const string &s) {
    return m;
  }

  string bar(const string &s) {
    return s;  
  }
};

X x;

int main(int argc, char **argv) {
  auto f1 = async(&X::foo, &x, 50, "hello");
  auto f2 = async(&X::bar, x, "world");

  cout << f1.get() << endl;
  cout << f2.get() << endl;

  return 0;
}
