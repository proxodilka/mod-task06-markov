#include "textgen.h"

#include <iostream>

int main() {
	Generator gen("../../examples/source.txt", 2);
	std::cout << gen.generate(1000) << std::endl;
	return 0;
}
