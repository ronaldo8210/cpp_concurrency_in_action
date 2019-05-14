/***********************************************************************
#   > File Name   : code_2_2.cpp
#   > Author      : ronaldo
#   > Description : 
#   > Create Time : 2019-05-14 11:42:16
***********************************************************************/

#include <iostream>
#include <thread>

using namespace std;

class func {
 public:
  func(const int &i) : i_(i) {}
  // must be public
  void operator()() {
    for (unsigned int j = 0; j < 1000; ++j) {
      // danger!! 'i' may be dangling referance!!
      cout << "thread func: " << i_ << endl;
    }
  }
 private:
  const int &i_;
};

void f() {
  int local_state = 666;
  func my_func(local_state);
  thread my_thread(my_func);

  try {
    // assume some exception occur in here
    // TODO
  } catch (...) {
    my_thread.join();
    throw;
  }

  my_thread.join();
}

int main(int argc, char **argv) {
  f();

  return 0;
}
