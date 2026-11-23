// SPDX-License-Identifier: MIT
#ifndef ERRNO_TEST_HPP
#define ERRNO_TEST_HPP

#include <cerrno>
#include <gtest/gtest.h>

class ERRNO_TEST : public ::testing::Test {
  protected:
	void SetUp() override { errno = 0; }

	void TearDown() override { errno = 0; }
};

#endif
