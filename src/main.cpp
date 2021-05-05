
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "textgen.h"

int main(int argc, char* argv[]) {
    srand(time(0));
    std::fstream fin;
    std::string default_fname = "test_text.txt";

    if (argc == 1) {
        fin.open(default_fname);
        if (!fin.is_open()){
            std::cout << "File with source text is not specified!\nUsage:\n\t" << argv[0] << " <source_text_file_path>\n";
            return 0;
        }
    } else {
        fin.open(argv[1]);
        if (!fin.is_open()) {
            std::cout << "Can not open file " << argv[1] << "\n";
        }
    }

    TextGen tg(fin);

    std::cout << tg.Next(200) << std::endl;
    return 0;
}
