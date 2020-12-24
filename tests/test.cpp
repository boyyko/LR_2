// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include <chrono>
#include <cache_tester.hpp>

TEST(Example, EmptyTest) {

  cache_tester test(128,6144);
  test.tests();
    EXPECT_TRUE(true);
}
