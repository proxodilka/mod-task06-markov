#include "textgen.h"

void Generator::parse(std::istream& input) {
    prefix current_prefix;
    std::string word;

    while (current_prefix.size() != NPREF && !input.eof()) {
        getline(input, word, ' ');
        current_prefix.push_back(word);
    }

    while (!input.eof()) {
        getline(input, word, ' ');
        statetab[current_prefix].push_back(word);

        current_prefix.pop_front();
        current_prefix.push_back(word);
    }
    if (statetab.find(current_prefix) != statetab.end()) {
        statetab[current_prefix].push_back(word);
    }
    else {
        statetab[current_prefix] = std::vector<std::string>();
    }
}

std::string Generator::generate(int n_words) {
    srand(time(NULL));
    int initial_prefix_idx = rand() % statetab.size();
    int i = 0;
    prefix cur_prefix;
    for (auto& pref : statetab) {
        if (i == initial_prefix_idx) {
            cur_prefix = pref.first;
        }
        i++;
    }

    std::string res = cur_prefix[0] + " " + cur_prefix[1];
    for (int i = 0; n_words; i++) {
        auto variants = statetab[cur_prefix];
        if (variants.size() == 0) {
            break;
        }
        int var_idx = rand() % variants.size();
        auto word = variants[var_idx];
        res += " " + word;
        cur_prefix.pop_front();
        cur_prefix.push_back(word);
    }

    return res;
}

std::string Generator::generate(prefix cur_prefix) {
    std::string res = cur_prefix[0] + " " + cur_prefix[1];
    for (int i = 0; true; i++) {
        auto variants = statetab[cur_prefix];
        if (variants.size() == 0) {
            break;
        }
        int var_idx = rand() % variants.size();
        auto word = variants[var_idx];
        res += " " + word;
        cur_prefix.pop_front();
        cur_prefix.push_back(word);
    }
    return res;
}
