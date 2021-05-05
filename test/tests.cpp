// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(TextGenTest, PrefixGeneration) {
    std::string text = "a b c e f g";

    std::set<Prefix> expected_prefixes = {
        {"a", "b", "c"}, {"b", "c", "e"}, {"c", "e", "f"}
    };
    
    auto tg = TextGen(text, 3);
    auto prefix_map = tg.GetPrefixMap();

    std::set<Prefix> actual_prefixes;
    for (auto x : prefix_map) {
        actual_prefixes.insert(x.first);
    }

    ASSERT_EQ(expected_prefixes.size(), actual_prefixes.size());
    for (auto x : expected_prefixes) {
        ASSERT_TRUE(actual_prefixes.find(x) != actual_prefixes.end());
    }
}

TEST(TextGenTest, SuffixGeneration) {
    std::string text = "a b c e f g";
    auto tg = TextGen(text, 2);

    Prefix prefix = {"a", "b"};

    std::string expected_next = "c";
    std::string actual_next = tg.Next(prefix);

    ASSERT_EQ(expected_next, actual_next);
}

TEST(TextGenTest, SuffixGenerationMulti) {
    std::string text = "a b c a b e";
    auto tg = TextGen(text, 2);

    Prefix prefix = {"a", "b"};

    std::set<std::string> expected_next = {"c", "e"};
    std::string actual_next = tg.Next(prefix);

    ASSERT_TRUE(expected_next.find(actual_next) != expected_next.end());
}

TEST(TextGenTest, TextGeneration) {
    std::map<Prefix, std::vector<std::string>> prefix_map = {
        {
            {"a", "b"},
            {"c", "d", "e"}
        },
        {
            {"b", "c"},
            {"f", "g", "h"}
        },
        {
            {"c", "d"},
            {"i", "j", "k"}
        },
        {
            {"d", "e"},
            {"l", "m", "n"}
        }
    };

    auto tg = TextGen(prefix_map);
    std::string out = tg.Next(10);

    // Size of the output string is 19 (including spaces between words)
    ASSERT_EQ(19, out.size());
}
