#include <iostream>
#include <fstream>
#include <boost/process.hpp>
#include "ze_parser.h"

using std::string;

/*
First check ze.project file,
from there determine the file path, and file name, check the versions,
then download the designated files to local.
*/

string remote(string project_name) {
	return "https://raw.githubusercontent.com/tooyoungtoosimplesometimesnaive/" + project_name + "/master/";
}

/**
 * project_dir has the trailing /
 * project_name does not have leading or trailing /
 */
int fetch(string project_name, string project_dir) {
	// mkdir project
	int mkdir_result = boost::process::system("mkdir " + project_dir + project_name);
	if (mkdir_result) {
		std::cerr << "Error when creating the directory: " << project_dir + project_name << std::endl;
		return 1;
	}

	string remote_url = remote(project_name);

	// Get the ze.project
	string ze_project_command {"curl -o " + project_dir + project_name + "/ze.project" + " " + remote_url + "ze.project"};
	int ze_project_result = boost::process::system(ze_project_command);
	if (ze_project_result) {
		std::cerr << "Error when getting the ze.project for " << project_name << "." << std::endl;
		return 1;
	}

	// parse ze.project
	ze_parser parser(project_dir + project_name + "/ze.project");
	if (parser.no_good) {
		return 1;
	}

	for (auto file : parser.files) {
		string command {"curl -o " + project_dir + project_name + "/" + file + " " + remote_url + file};
		int result = boost::process::system(command);
		std::cout << result << std::endl;
		if (result)
			return result;
	}

	int fetch_result = 0;
	// Recursively download all the dependencies.
	for (auto d : parser.deps) {
		fetch_result = fetch_result || fetch(d, project_dir + "lib/" + d + "/");
	}
	return fetch_result;
}

int main(int argc, char* argv[]) {
	if (argc <= 2) {
		std::cerr << "Need more args!" << std::endl;
		return 1;
	}

	string directive {argv[1]};
	if (directive != "install") {
		std::cerr << "Currently only support `install` directive." << std::endl;
		return 1;
	}
	string project_name {argv[2]};

	int result = fetch(project_name, "./lib/");
	if (result)
		return result;
	
	/*
	string command {"curl -o ./lib/" + project_name + ".cpp" + " " + remote + project_name + ".cpp"};
	int result = boost::process::system(command);
	std::cout << result << std::endl;
	*/

	std::cout << "Done!" << std::endl;
	return 0;
}

