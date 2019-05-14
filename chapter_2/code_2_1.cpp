/***********************************************************************
#   > File Name   : code_2_1.cpp
#   > Author      : ronaldo
#   > Description : 
#   > Create Time : 2019-05-14 09:39:48
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
      // error!! 'i' will be dangling referance!!
      cout << "thread func: " << i_ << endl;
    }
  }
 private:
  const int &i_;
};

// this is a bad example!!
void oops() {
  int local_state = 666;
  func my_func(local_state);
  thread my_thread(my_func);  // my_func will be copied to thread memory stack
  my_thread.detach();  // !!
}

int main(int argc, char **argv) {
  oops();

  return 0;
}
