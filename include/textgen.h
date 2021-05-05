#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <list>

typedef std::list<std::string> Prefix;

class TextGen {
public:
    TextGen(
        const std::map<Prefix, std::vector<std::string>>& prefix_map
    ) : prefix_map(prefix_map) {}

    TextGen(
        std::map<Prefix, std::vector<std::string>>&& prefix_map
    ) : prefix_map(std::move(prefix_map)) {}

    TextGen(std::string& src, int npref=2) {
        std::stringstream stream;
        stream << src;
        parse_stream(stream, npref);
    }

    TextGen(std::basic_iostream<char>& stream, int npref=2) {
        parse_stream(stream, npref);
    }

    const std::map<Prefix, std::vector<std::string>>& GetPrefixMap() { 
        return prefix_map;
    }

    std::string Next() { return Next(false); }
    std::string Next(int n) { return Next(n, false); }
    std::string Next(const Prefix& prefix);
    std::string Next(const Prefix& prefix, int n);

private:
    void parse_stream(std::basic_iostream<char>& ss, int npref=2);
    std::string Next(bool ignore_prefix);
    std::string Next(int n, bool ignore_prefix);

    std::map<Prefix, std::vector<std::string>> prefix_map;
    std::list<std::string> output_queue;
    Prefix last_prefix;
};
