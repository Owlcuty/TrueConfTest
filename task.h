#pragma once

#define ARG_NAME(arg) #arg

#include <iostream>
#include <map>
#include <vector>

#include <cstdio>

#include <algorithm>

#include <cassert>
#include <cerrno>


typedef int errno_t;

template <typename Type>
bool is_num_in_vec(std::vector<Type> &cont, Type num)
{
    typename std::vector<Type>::const_iterator it_end = cont.end();

    typename std::vector<Type>::const_iterator left = cont.begin();
    typename std::vector<Type>::const_iterator right = it_end;

    if (!cont.size())
    {
        return true;
    }

    while (distance(left, right))
    {
        typename std::vector<Type>::const_iterator mid = left +
                                             distance(left, right) / 2;

        if (num <= *mid)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    return (num == *right);
}

template <typename T_key, typename T_val>
bool is_num_in_map(std::map<T_key, T_val> &cont, T_val num)
{
    typename std::map<T_key, T_val>::const_iterator it = cont.begin();

    if (!cont.size())
    {
        return false;
    }

    for (; it != cont.end(); ++it)
    {
        if (it->second == num)
        {
            return true;
        }
    }

    return false;
}

template <typename Type>
void dump_vec(const std::vector<Type> &container, char* name_cont)
{
    typename std::vector<Type>::const_iterator it = container.begin();

    printf("%s [%X]--[%d] {\n", name_cont, container, container.size());
    for (; it != container.end(); ++it)
    {
        std::cout << *it << "; ";
    }
    std::cout << "\n}\n";
}

template <typename T_key, typename T_val>
void dump_map(const std::map<T_key, T_val> &container, char* name_cont)
{
    typename std::map<T_key, T_val>::const_iterator it = container.begin();

    printf("%s [%X]--[%d] {\n", name_cont, container, container.size());
    for (; it != container.end(); ++it)
    {
        std::cout << it->second << "; ";
    }
    std::cout << "\n}\n";
}

template <typename Container>
errno_t fill_rand_cont(Container &container, size_t size)
{
  assert(0 <= size);

  srand(time(0) + rand());
  for (int el = 0; el < size; ++el)
  {
    container[el] = rand() % 9 + 1;
  }

  return 0;
}

template <typename Container>
errno_t delete_some(Container &container)
{
  typename Container::const_iterator it = container.begin();

  srand(time(0));
  for (size_t times = 0; times < std::min(container.size() - 1, (size_t)(rand() % 15 + 1)) && it != container.end(); ++times)
  {
    container.erase(it++);
  }

  return 0;
}

template <typename T_vec, typename T_key, typename T_val>
errno_t synch_vec_map(std::vector<T_vec> &cvec, std::map<T_key, T_val> &cmap)
{

  std::sort(cvec.begin(), cvec.end());

  typename std::map<T_key, T_val>::const_iterator it_map = cmap.begin();
  for (; it_map != cmap.end();)
  {
      if (!is_num_in_vec(cvec, it_map->second))
      {
          cmap.erase(it_map++);
      }
      else
      {
          ++it_map;
      }
  }

  typename std::vector<T_vec>::const_iterator it_vec = cvec.begin();
  typename std::vector<T_vec>::const_iterator it_min = cvec.begin();
  while (it_vec != cvec.end())
  {
      if (!is_num_in_map(cmap, *it_vec))
      {
          cvec.erase(std::remove(cvec.begin(), cvec.end(), *it_vec), cvec.end());

          it_vec = it_min;
      }
      else
      {
        it_min = ++it_vec;
      }
  }

  return 0;
}
