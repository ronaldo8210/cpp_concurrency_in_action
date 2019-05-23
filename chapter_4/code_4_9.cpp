/***********************************************************************
#   > File Name   : code_4_9.cpp
#   > Author      : ronaldo
#   > Description : 
#   > Create Time : 2019-05-23 13:29:26
***********************************************************************/

#include <deque>
#include <future>
#include <mutex>
#include <thread>

using namespace std;

bool gui_shutdown_message_received() {
  //TODO  
}

bool get_and_process_gui_message() {
  //TODO  
}

mutex m;
deque<packaged_task<void()>> tasks;

void gui_thread() {
  while (!gui_shutdown_message_received()) {
    // get_and_process_gui_message();
    packaged_task<void()> task;
    {
      lock_guard<mutex> lock(m);
      if (tasks.empty()) {
        continue;
      }
      task = std::move(tasks.front());
      tasks.pop_front();
    }
    task();
  }
}

template<typename Func>
future<void> post_task_to_gui_thread(Func f) {
  packaged_task<void()> task(f);
  future<void> res = task.get_future();
  {
    lock_guard<mutex> lock(m);
    tasks.push_back(std::move(task));
  }
  return res;
}

int main(int argc, char **argv) {
  thread gui_bg_thread(gui_thread);

  return 0;  
}
