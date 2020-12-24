// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_CACHE_TESTER_HPP_
#define INCLUDE_CACHE_TESTER_HPP_

#include <iostream>
#include <vector>

class cache_tester {
 public:
  cache_tester(int Lmin, int Lmax);
  void tests();

 private:
  int direct_test(int sizes_array);
  int reverse_test(int sizes_array);
  int random_test(int sizes_array);
  int get_random(int min, int max);

  int *generate_array(int size);
  void free_array(int *array);

  int _Lmin, _Lmax;

  std::vector<int> _sizes_array;

};

#endif // INCLUDE_CACHE_TESTER_HPP_
