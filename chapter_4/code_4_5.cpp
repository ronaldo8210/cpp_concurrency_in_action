/***********************************************************************
#   > File Name   : code_4_5.cpp
#   > Author      : ronaldo
#   > Description : 
#   > Create Time : 2019-05-23 09:39:11
***********************************************************************/

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>

using namespace std;

template<typename T>
class thread_safe_queue {
 public:
  thread_safe_queue() : data_(queue<T>()) {}

  thread_safe_queue(const thread_safe_queue<T> &other) {
    lock_guard<mutex> lock(other.m_);
    data_ = other.data_;
  }

  void push(const T &new_value) {
    lock_guard<mutex> lock(m_);
    data_.push(new_value);
    cond_.notify_one();
  }

  shared_ptr<T> wait_and_pop() {
    unique_lock<mutex> lock(m_);
    cond_.wait(lock, [this]{return !data_.empty();});
    shared_ptr<T> res(make_shared<T>(data_.front()));
    data_.pop();
    return res;
  }

  void wait_and_pop(T &ret) {
    unique_lock<mutex> lock(m_);
    cond_.wait(lock, [this]{return !data_.empty();});
    ret = data_.front();
    data_.pop();
  }

  shared_ptr<T> try_pop() {
    lock_guard<mutex> lock(m_);
    if (data_.empty()) {
      return shared_ptr<T>();
    }
    shared_ptr<T> res(make_shared<T>(data_.front()));
    data_.pop();
    return res;
  }

  bool try_pop(T &ret) {
    lock_guard<mutex> lock(m_);
    if (data_.empty()) {
      return false;
    }
    ret = data_.front();
    data_.pop();
    return true;
  }

  bool empty() const {
    lock_guard<mutex> lock(m_);
    return data_.empty();
  }

 private:
  mutable mutex m_;  // why mutable?
  condition_variable cond_;
  queue<T> data_;
};

int main(int argc, char **argv) {
  thread_safe_queue<int> my_queue;
  my_queue.push(1);
  my_queue.push(2);
  my_queue.push(3);
  my_queue.push(4);
  
  int m, n;
  my_queue.try_pop(m);
  my_queue.wait_and_pop(n);
  cout << m << endl;
  cout << n << endl;
  cout << *(my_queue.wait_and_pop()) << endl;
  cout << *(my_queue.try_pop()) << endl;

  return 0;  
}
