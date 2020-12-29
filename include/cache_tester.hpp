//Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_CACHE_TESTER_HPP_
#define INCLUDE_CACHE_TESTER_HPP_

#include <iostream>
#include <vector>

class cache_tester {
 public:
  cache_tester(int Lmin, int Lmax);
  void tests();
  void count_experiments();

 private:
  int direct_test(int sizes_array);
  int reverse_test(int sizes_array);
  int random_test(int sizes_array);
  int get_random(int min, int max);
  void warmup(int sizes_array, int *array);
  void reverse_warmup(int sizes_array, int *array);
  void random_warmup(int sizes_array, int *array);


  int *generate_array(int size);
  void free_array(int *array);

  int _Lmin, _Lmax;
  const int step = 16;
  const int iter = 1000;
  int k = -1;
  std::vector<int> _sizes_array;

};

#endif // INCLUDE_CACHE_TESTER_HPP_
