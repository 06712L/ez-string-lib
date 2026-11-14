#ifndef INIT_ERRNO_H
#define INIT_ERRNO_H

#include <gtest/gtest.h>
#include <cerrno>

class ERRNO_TEST : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            errno = 0;
        }

        void TearDown() override
        {
            errno = 0;
        }
};

#endif