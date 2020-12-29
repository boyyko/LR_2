
#include <cache_tester.hpp>
#include <iostream>
#include <chrono>

cache_tester::cache_tester(int Lmin, int Lmax)
    : _Lmin(Lmin),
      _Lmax(Lmax)
{}

int cache_tester::direct_test(int sizes_array)
{
  int *array = generate_array(sizes_array);
  warmup(sizes_array, array);

  int time = 0;
  for (int j = 0; j < iter; ++j)
  {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < sizes_array; i += step)
    {
      k = array[i];
    }
    auto finish = std::chrono::high_resolution_clock::now();
    time += std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
  }
  free_array(array);
  time/=iter;
  return time;
}

void cache_tester::tests() {
  std::cout << "investigation:" << std::endl
            << "  travel_variant: direct" << std::endl
            << "  experiments:" << std::endl;

  for (size_t i = 0; i < _sizes_array.size(); i++)
  {
    std::cout << "- experiment:" << std::endl
              << "    number: " << i + 1 << std::endl
              << "    input data:" << std::endl
              << "      buffer_size: " << _sizes_array[i] / 256 << " KiB" << std::endl
              << "    results:" << std::endl
              << "      duration: " << direct_test(_sizes_array[i]) << "mcs" << std::endl;
  }

  std::cout << "investigation:" << std::endl
            << "  travel_variant: reverse" << std::endl
            << "  experiments:" << std::endl;

  for (size_t i = 0; i < _sizes_array.size(); i++)
  {
    std::cout << "- experiment:" << std::endl
              << "    number: " << i + 1 << std::endl
              << "    input data:" << std::endl
              << "      buffer_size: " << _sizes_array[i] / 256 << " KiB" << std::endl
              << "    results:" << std::endl
              << "      duration: " << reverse_test(_sizes_array[i]) << " mcs" << std::endl;
  }

  std::cout << "investigation:" << std::endl
            << "  travel_variant: random" << std::endl
            << "  experiments:" << std::endl;

  for (size_t i = 0; i < _sizes_array.size(); ++i)
  {
    std::cout << "- experiment:" << std::endl
              << "    number: " << i + 1 << std::endl
              << "    input data:" << std::endl
              << "      buffer_size: " << _sizes_array[i] / 256 << " KiB" << std::endl
              << "    results:" << std::endl
              << "      duration: " << random_test(_sizes_array[i]) << "mcs" << std::endl;
  }
}
int* cache_tester::generate_array(int size)
{
    int *array = new int[size];
    for (int i = 0;i < size; ++i)
    {
      array[i] = random();
    }
  return array;
}
void cache_tester::free_array(int *array)
{
  delete[] array;
}

int cache_tester::reverse_test(int sizes_array)
{
  int *array = generate_array(sizes_array);
  reverse_warmup(sizes_array,array);

  int time = 0;
  for (int j = 0; j < iter; ++j)
  {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < sizes_array; i += step) {
      k = array[sizes_array - i - 1];
    }
    auto finish = std::chrono::high_resolution_clock::now();
    time +=
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
            .count();
  }
    free_array(array);
    time/=iter;
  return time ;
}
int cache_tester::random_test(int sizes_array)
{
  int *array = generate_array(sizes_array);
  random_warmup(sizes_array,array);

  int time = 0;
  for (int j = 0; j < iter; ++j)
  {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < sizes_array/step; ++i) {
      k = array[get_random(0, sizes_array - 1)];
    }
    auto finish = std::chrono::high_resolution_clock::now();
    time += std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
  }
  free_array(array);
  time/=iter;
  return time;
}
int cache_tester::get_random(int min, int max)
{
  int rand = min + random() % (max - min +1);
  return rand;
}

void cache_tester::count_experiments()
{
  int cur_size = 0;
  cur_size = _Lmin/2;
  while (cur_size < 3/2 * _Lmax)
  {
    _sizes_array.push_back(cur_size * 256);
    cur_size*=2;
  }
  _sizes_array.push_back(3 * _Lmax/2 * 256);
}

void cache_tester::warmup(int sizes_array, int *array)
{
  for (int i = 0; i < sizes_array; i += step)
  {
    k = array[i];
  }
}

void cache_tester::reverse_warmup(int sizes_array, int *array)
{
  for (int i = 0; i < sizes_array; i += step)
  {
    k = array[sizes_array - i - 1];
  }
}

void cache_tester::random_warmup(int sizes_array, int *array)
{

  for (int i = 0; i < sizes_array; i += step)
  {
    k = array[get_random(0, sizes_array - 1)];
  }
}
