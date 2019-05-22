/***********************************************************************
#   > File Name   : code_3_5.cpp
#   > Author      : ronaldo
#   > Description : 
#   > Create Time : 2019-05-22 17:18:50
***********************************************************************/

#include <exception>
#include <iostream>
#include <memory>
#include <mutex>
#include <stack>

using namespace std;

template<typename T>
class thread_safe_stack {
 public:
  thread_safe_stack() : data_(stack<T>()) {}
  thread_safe_stack(const thread_safe_stack<T> &other) {  // '<T>' is needed?
    lock_guard<mutex> lock(other.m_);
    data_ = other.data_;
  }

  void push(const T &new_value) {
    lock_guard<mutex> lock(m_);
    data_.push(new_value);
  }

  shared_ptr<T> pop() {
    lock_guard<mutex> lock(m_);
    if (data_.empty()) {
      //TODO  
    }

    shared_ptr<T> const res(make_shared<T>(data_.top()));  // why const?
    data_.pop();
    return res;
  }

  void pop(T &value) {
    lock_guard<mutex> lock(m_);
    if (data_.empty()) {
      //TODO  
    }
    
    value = data_.top();
    data_.pop();
  }

  bool empty() const {
    lock_guard<mutex> lock(m_);
    return data_.empty();
  }

  mutex m_;
 private:
  stack<T> data_;
  // mutable mutex m_;
};

int main(int argc, char **argv) {
  thread_safe_stack<int> s;
  s.push(1);
  s.push(2);
  shared_ptr<int> ptr = s.pop();
  int a;
  s.pop(a);
  
  cout << *ptr << endl;
  cout << a << endl;
  return 0;
}
