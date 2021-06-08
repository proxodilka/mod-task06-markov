#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <map>
#include <vector>
#include <sstream>

class Generator {
public:
    typedef std::deque<std::string> prefix;

    Generator(std::string filename, int prefix_size) {
        auto stream = std::ifstream(filename);
        NPREF = prefix_size;
        parse(stream);
    }

    Generator(int prefix_size, std::string source_text) {
        std::stringstream stream;
        NPREF = prefix_size;
        stream << source_text;
        parse(stream);
    }

    std::string generate(int n_words);
    std::vector<prefix> get_prefixes() {
        std::vector<prefix> res;
        for (auto& x : statetab) {
            res.push_back(x.first);
        }
        return res;
    }

private:
    int NPREF = 2;
    const int MAXGEN = 1000;
    std::map<prefix, std::vector<std::string> > statetab;

    void parse(std::istream& input);
};
