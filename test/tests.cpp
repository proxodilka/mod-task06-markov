// Copyright 2021 GHA Test Team
#include "textgen.h"

#include <gtest/gtest.h>

TEST(TestGenerator, prefix) {
    std::string src = "one two three";

    std::vector<Generator::prefix> answer = {{"one", "two"}, {"two", "three"}};
    Generator gen(src, 2);
    auto result = gen.get_prefixes();

    ASSERT_EQ(result.size(), answer.size());
    for (int i=0; i<result.size(); i++) {
        ASSERT_EQ(result[i].size(), answer[i].size());
        for (int j=0; j<result[i].size(); j++) {
            ASSERT_TRUE(result[i][j] == answer[i][j]);
        }
    }
}

