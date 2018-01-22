#include <iostream>
#include "../ze_parser.h"

int main() {
	ze_parser zp("ze.project");
	std::cout << zp.version << std::endl;
	std::cout << zp.lang << std::endl;
	for (auto f : zp.files)
		std::cout << f << std::endl;

	return 0;
}
