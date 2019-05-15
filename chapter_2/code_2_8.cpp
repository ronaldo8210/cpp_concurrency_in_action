/***********************************************************************
#   > File Name   : code_2_8.cpp
#   > Author      : ronaldo
#   > Description : 
#   > Create Time : 2019-05-14 21:30:29
***********************************************************************/

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

using namespace std;

template<typename Iterator, typename T>
class accumulate_block {
 public:
  void operator()(Iterator first, Iterator last, T &result) {
    result = accumulate(first, last, 0);
  }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
  cout << "hardware concurrency: " << thread::hardware_concurrency() << endl;
  const unsigned int total_length = distance(first, last);
  cout << "total lengh: " << total_length << endl;
  
  if (total_length == 0) {
    return init;
  }

  const unsigned int thread_num = 4;  // main thread + worker thread
  const unsigned int block_size = total_length / (thread_num-1);
  cout << "block size: " << block_size << endl;

  vector<thread> threads(thread_num-1);
  vector<T> results(thread_num);  // how to initialize?

  Iterator block_begin = first;
  for (unsigned int i = 0; i < (thread_num-1); ++i) {
    Iterator block_end = block_begin;
    advance(block_end, block_size);
    threads[i] = thread(accumulate_block<Iterator, T>(), block_begin, block_end, ref(results[i]));
    block_begin = block_end;
  }
  accumulate_block<Iterator, T>()(block_begin, last, results[thread_num-1]);
  for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
  return accumulate(results.begin(), results.end(), init);
}

int main(int argc, char **argv) {
  vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int sum = accumulate(vec.begin(), vec.end(), 0);
  cout << sum << endl;
  cout << "----------" << endl;

  int parallel_sum = parallel_accumulate<vector<int>::iterator, int>(
      vec.begin(), vec.end(), 0);
  cout << "parallel sum: " << parallel_sum << endl;

  return 0;  
}
