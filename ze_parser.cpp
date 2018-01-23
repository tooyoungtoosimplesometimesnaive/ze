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
	int line_no = 0;
	while(std::getline(infile, line)) {
		if (line == not_found) {
			std::cerr << "No ze.project found!" << std::endl;
			no_good = true;
			break;
		}
		line_no++;

		auto p = get_pair(line, line_no);
		std::cout << p.first << " " << p.second << std::endl;

		if (p.first == Kw_lang)
			lang = p.second;
		else if (p.first == Kw_version)
			version = p.second;
		else if (p.first == Kw_project_name)
			project_name = p.second;
		else if (p.first == Kw_lib)
			files = split(p.second, ',');
		else if (p.first == Kw_dependencies)
			deps = split(p.second, ',');
	}
	infile.close();
}

ze_parser::ze_pair ze_parser::get_pair(std::string line, int line_no) {
	line = trim_space(line);
	auto sep_colon = line.find(":");
	if (sep_colon != std::string::npos) {
		return std::make_pair(trim_space(line.substr(0, sep_colon)), trim_space(line.substr(sep_colon + 1)));
	} else {
		if (line != "")
			std::cerr << "Invalid ze.project syntax at Line " << line_no << "." << std::endl;
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
		tokens.push_back(trim_space(token));
	}
	return tokens;
}

// Remove leading and trailing space chars.
std::string trim_space(std::string s) {
	std::string::size_type i = 0, j = s.size() - 1;
	while(isspace(s[i]))
		i++;
	if (i == s.size())
		return "";
	while(isspace(s[j]) && i < j)
		j--;
	return s.substr(i, j + 1);
}

