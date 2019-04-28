/***********************************************************************
#   > File Name   : spin_lock.cpp
#   > Author      : ronaldo
#   > Description : 
#   > Create Time : 2019-04-28 11:12:36
***********************************************************************/

#include <atomic>
#include <iostream>
#include <thread>

// using atomic_flag
class SpinLock_1 {
 public:
  SpinLock_1() : flag(ATOMIC_FLAG_INIT) {}
  
  void lock() {
    while (!flag.test_and_set(std::memory_order_acquire)) {
      // do nothing
    }
  }

  void unlock() {
    flag.clear(std::memory_order_release);
  }
 private:
  std::atomic_flag flag;
};

// using atomic<bool>
class SpinLock_2 {
 public:
  SpinLock_2() : flag(ATOMIC_VAR_INIT(false)) {}
  
  void lock() {
    bool expect = false;
    while (!flag.compare_exchange_strong(expect, true)) {
      expect = false;  
    }
  }

  void unlock() {
    flag.store(false);
  }
 private:
  std::atomic<bool> flag;
};

// using Release-Acquire to enhance performance
class SpinLock_3 {
 public:
  SpinLock_3() : flag(ATOMIC_VAR_INIT(false)) {}
  
  void lock() {
    bool expect = false;
    while (!flag.compare_exchange_strong(expect, true, 
           std::memory_order_acquire, std::memory_order_relaxed)) {
      expect = false;  
    }
  }

  void unlock() {
    flag.store(false, std::memory_order_release);
  }
 private:
  std::atomic<bool> flag;
};

SpinLock_3 g_spinlock;
int g_num = 0;

void func() {
  for (int i = 0; i < 10000000; i++) {
    g_spinlock.lock();
    g_num++;
    g_spinlock.unlock();   
  }
}

int main(int argc, char** argv) {
  std::thread thrd_1(func), thrd_2(func);
  thrd_1.join();
  thrd_2.join();
  std::cout << "the result is: " << g_num << std::endl;

  return 0;
}
