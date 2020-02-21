#define ARG_NAME(arg) #arg

#include <iostream>
#include <map>
#include <vector>

#include "task.h"


int main()
{
  std::vector<int> first(10);
  std::map<size_t, int> second;

  fill_rand_cont<std::vector<int>> (first, 10);
  fill_rand_cont<std::map<size_t, int>> (second, 10);

  dump_vec<int> (first, (char*)ARG_NAME(first));
  dump_map<size_t, int> (second, (char*)ARG_NAME(second));
  std::cout << std::endl;

  delete_some<std::vector<int>> (first);
  delete_some<std::map<size_t, int>> (second);

  dump_vec<int> (first, (char*)ARG_NAME(first));
  dump_map<size_t, int> (second, (char*)ARG_NAME(second));
  std::cout << std::endl;

  synch_vec_map<int, size_t, int> (first, second);
  dump_vec<int> (first, (char*)ARG_NAME(first));
  dump_map<size_t, int> (second, (char*)ARG_NAME(second));
  std::cout << std::endl;
}
