#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "ze_parser.h"


ze_parser::ze_parser(std::string file) {
	std::ifstream infile;
	infile.open(file);
	std::string line;
	while(std::getline(infile, line)) {
		if (line == not_found) {
			std::cerr << "No ze.project found!" << std::endl;
			no_good = false;
			break;
		}
		auto p = get_pair(line);
		std::cout << p.first << " " << p.second << std::endl;
		if (p.first == Kw_lang)
			lang = p.second;
		else if (p.first == Kw_version)
			version = p.second;
		else if (p.first == Kw_project_name)
			project_name = p.second;
		else if (p.first == Kw_lib) {
			files = split(p.second, ',');
		}
	}
	infile.close();
}

ze_parser::ze_pair ze_parser::get_pair(std::string line) {
	auto sep_colon = line.find(":");
	if (sep_colon != std::string::npos) {
		return std::make_pair(line.substr(0, sep_colon), line.substr(sep_colon + 1));
	} else {
		std::cerr << "Error in this line: '" << line << "'" << std::endl;
		return std::make_pair("", "");
	}
}

std::vector<std::string> ze_parser::split(const std::string s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}
