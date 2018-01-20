#ifndef ZE_PARSER_H
#define ZE_PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class ze_parser {
public:
	typedef std::pair<std::string, std::string> ze_pair;
	typedef std::vector<std::string> ze_files;

	ze_parser(std::string file) {
		std::ifstream infile;
		infile.open(file);
		std::string line;
		while(std::getline(infile, line)) {
			auto p = get_pair(line);
			std::cout << p.first << " " << p.second << std::endl;
		}
		infile.close();
	}

	ze_files files;
private:
	ze_pair get_pair(std::string line) {
		auto sep_colon = line.find(":");
		if (sep_colon != std::string::npos) {
			return std::make_pair(line.substr(0, sep_colon), line.substr(sep_colon + 1));
		} else {
			std::cerr << "Error in this line: '" << line << "'" << std::endl;
			return std::make_pair("", "");
		}
	}
};

#endif
