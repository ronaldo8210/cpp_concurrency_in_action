/***********************************************************************
#   > File Name   : code_3_1.cpp
#   > Author      : ronaldo
#   > Description : 
#   > Create Time : 2019-05-22 10:23:00
***********************************************************************/

#include <algorithm>
#include <iostream>
#include <list>
#include <mutex>

using namespace std;

list<int> g_list;
mutex g_mutex;

void add_to_list(int value) {
  lock_guard<mutex> lock(g_mutex);
  g_list.push_back(value);
}

bool list_contains(int value_to_find) {
  lock_guard<mutex> lock(g_mutex);
  return find(g_list.begin(), g_list.end(), value_to_find) != g_list.end();
}

int main(int argc, char **argv) {
  
  
  return 0;
}
