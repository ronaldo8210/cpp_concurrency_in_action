/***********************************************************************
#   > File Name   : example_2_2.cpp
#   > Author      : ronaldo
#   > Description : 
#   > Create Time : 2019-05-14 16:33:08
***********************************************************************/

#include <iostream>
#include <thread>

using namespace std;

void func(int x, const string &s) {
  // TODO  
}

// bad example!!
void oops(int param) {
  char buff[32] = {0};
  sprintf(buff, "%i", param);
  thread t(func, 3, buff);
  t.detach();
}

void not_oops(int param) {
  char buff[32] = {0};
  sprintf(buff, "%i", param);
  thread t(func, 3, string(buff));  // avoid dangling pointer
  t.detach();
}

struct widget_data {
  int x;
};

typedef int widget_id;

void update_data_for_widget(int widget_id, widget_data &data) {
  // TODO
}

void oops_again() {
  widget_id w;
  widget_data data_local;
  //thread t1(update_data_for_widget, w, data_local);  // error!! local data wont be modified
  thread t2(update_data_for_widget, w, ref(data_local));  // correct
  //t1.join();
  t2.join();
}

int main(int argc, char **argv) {
  
    
  return 0;
}
