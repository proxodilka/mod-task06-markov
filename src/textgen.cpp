#include "textgen.h"
#include "utils.h"
#include <iostream>

void TextGen::parse_stream(std::basic_iostream<char>& ss, int npref) {
    Prefix prefix_queue;
    std::string next_word;
    while (!ss.eof()) {
        while (prefix_queue.size() != npref && !ss.eof()) {
            getline(ss, next_word, ' ');
            prefix_queue.push_back(next_word);
        }

        if (ss.eof()) {
            throw std::runtime_error("Unexpected end of stream.");
        }

        getline(ss, next_word, ' ');
        prefix_map[prefix_queue].push_back(next_word);

        prefix_queue.pop_front();
        prefix_queue.push_back(next_word);
    }
}

std::string TextGen::Next(bool ignore_prefix) {
    if (last_prefix.size() == 0) {
        last_prefix = get_random_key(prefix_map);
    }

    auto available_elements_it = prefix_map.find(last_prefix);
    if (available_elements_it == prefix_map.end()) {
        output_queue.insert(
            output_queue.end(), last_prefix.begin(), last_prefix.end()
        );
        last_prefix.clear();
        return Next();
    }

    const std::vector<std::string>& available_elements = available_elements_it->second;
    int next_word_idx = random(0, available_elements.size() - 1);

    std::string next_word = available_elements[next_word_idx];
    if (ignore_prefix) {
        output_queue.push_back(next_word);
    } else {
        output_queue.push_back(last_prefix.front());
    }

    last_prefix.pop_front();
    last_prefix.push_back(next_word);

    std::string result = output_queue.front();
    output_queue.pop_front();
    return result;
}

std::string TextGen::Next(int n, bool ignore_prefix) {
    std::string out;
    out.reserve(n + (n - 1));
    for (int i=0; i<n; i++) {
        out += Next(ignore_prefix && !i);
        if (i != n - 1) {
            out += " ";
        }
    }
    return out;
}

std::string TextGen::Next(const Prefix& prefix) {
    last_prefix = prefix;
    output_queue.clear();
    return Next(true);
}

std::string TextGen::Next(const Prefix& prefix, int n) {
    last_prefix = prefix;
    output_queue.clear();
    return Next(n, true);
}
