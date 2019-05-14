/***********************************************************************
#   > File Name   : code_2_3.cpp
#   > Author      : ronaldo
#   > Description : 
#   > Create Time : 2019-05-14 15:34:04
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

// RAII
class thread_guard {
 public:
  thread_guard(thread &t) : t_(t) {}
  ~thread_guard() {
    if (t_.joinable())  {
      t_.join();
    }
  }
 private:
  thread &t_;
};

void f() {
  int local_state = 666;
  func my_func(local_state);
  thread my_thread(my_func);  // my_func will be copied into thread memory stack
  thread_guard g(my_thread);

  // assume some exception will occur in here
  // TODO
}

int main(int argc, char **argv) {
  f();

  return 0;
}
