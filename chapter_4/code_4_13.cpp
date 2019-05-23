/***********************************************************************
#   > File Name   : code_4_13.cpp
#   > Author      : ronaldo
#   > Description : 
#   > Create Time : 2019-05-23 17:27:31
***********************************************************************/

#include <algorithm>
#include <future>
#include <iostream>
#include <list>

using namespace std;

template<typename T>
list<T> parallel_quick_sort(list<T> input) {
  if (input.empty() || input.size() == 1) {
    return input;
  }

  list<T> result;
  result.splice(result.begin(), input, input.begin());
  const T& pivot = *(result.begin());
  auto divide_point = partition(input.begin(), input.end(), 
      [&](const T& t){return t < pivot;});

  list<T> lower_part;
  lower_part.splice(lower_part.begin(), input, input.begin(), divide_point);
  
  future<list<T>> new_lower_list = async(&parallel_quick_sort<T>, std::move(lower_part));
  list<T> new_higher_list = parallel_quick_sort(std::move(input));
  result.splice(result.begin(), new_lower_list.get());
  result.splice(result.end(), new_higher_list);

  return result;
}

int main(int argc, char **argv) {
  list<int> my_list;
  my_list.push_back(2);
  my_list.push_back(4);
  my_list.push_back(6);
  my_list.push_back(8);
  my_list.push_back(10);
  my_list.push_back(1);
  my_list.push_back(3);
  my_list.push_back(5);
  my_list.push_back(7);
  my_list.push_back(9);

  list<int> sort_list = parallel_quick_sort(my_list);
  list<int>::iterator it;
  for (it = sort_list.begin(); it != sort_list.end(); ++it) {
    cout << *it << endl;
  }

  return 0;  
}
