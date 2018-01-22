#ifndef ZE_PARSER_H
#define ZE_PARSER_H

#include <fstream>
#include <string>
#include <vector>

/**
 * ze.project file keywords:
 */
const std::string Kw_lang = "lang";
const std::string Kw_version = "version";
const std::string Kw_lib = "lib";
const std::string Kw_project_name = "project_name";

const std::string not_found = "404: Not Found";

class ze_parser {
public:
	typedef std::pair<std::string, std::string> ze_pair;
	typedef std::vector<std::string> ze_files;

	ze_parser(std::string file);

	bool no_good = false;
	ze_files files;
	std::string version;
	std::string lang;
	std::string project_name;

private:
	ze_pair get_pair(std::string line);
	std::vector<std::string> split(const std::string s, char delimiter);
};

#endif
