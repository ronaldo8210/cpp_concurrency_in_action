/***********************************************************************
#   > File Name   : code_3_2.cpp
#   > Author      : ronaldo
#   > Description : 
#   > Create Time : 2019-05-15 20:52:00
***********************************************************************/

#include <iostream>
#include <mutex>

using namespace std;

class some_data {
 public:
  do_something();
 private:
  int a_;
  string str_;
};

class data_wrapper {
 public:
  template<typename Func>
  void process_data(Func func) {
    lock_guard<mutex> guard(m_);
    Func(data_);
  }
 private:
  some_data data_;
  mutex m_
};

some_data *unprotect_data_ptr;

void malicious_func(some_data &want_protected_data) {
  unprotect_data_ptr = &want_protected_data;  
}

data_wrapper x;

void foo() {
  x.process_data(malicious_func);
  unprotect_data_ptr->do_something();  // bad!!
}

int main(int argc, char **argv) {
  foo();
    
  return 0;  
}
