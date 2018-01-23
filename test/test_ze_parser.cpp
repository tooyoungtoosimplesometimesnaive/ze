#include <iostream>
#include "../ze_parser.h"


int main() {

	std::cout << trim_space("") << std::endl;
	std::cout << trim_space("      ccccc") << std::endl;
	std::cout << trim_space("aaaa     ") << std::endl;
	std::cout << trim_space("    dddd  ") << std::endl;
	
	ze_parser zp("ze.project");
	std::cout << zp.version << std::endl;
	std::cout << zp.lang << std::endl;
	for (auto f : zp.files)
		std::cout << f << std::endl;

	for (auto f : zp.deps)
		std::cout << f << std::endl;


	return 0;
}
