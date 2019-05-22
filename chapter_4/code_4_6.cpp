/***********************************************************************
#   > File Name   : code_4_6.cpp
#   > Author      : ronaldo
#   > Description : 
#   > Create Time : 2019-05-22 21:53:40
***********************************************************************/

#include <unistd.h>
#include <future>
#include <iostream>

using namespace std;

int func() {
  sleep(5); 
  return 500;    
}

void do_something() {
    
}

int main(int argc, char **argv) {
  future<int> answer = async(func);
  do_something();
  int res = answer.get();
  cout << res << endl;

  return 0;  
}
