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
	string remote {"https://raw.githubusercontent.com/tooyoungtoosimplesometimesnaive/" + project_name + "/master/"};

	// mkdir project
	int mkdir_result = boost::process::system("mkdir ./lib/" + project_name);
	if (mkdir_result) {
		std::cerr << "Error when creating the directory: " << project_name << std::endl;
		return 1;
	}

	// Get the ze.project
	string ze_project_command {"curl -o ./lib/" + project_name + "/ze.project" + " " + remote + "ze.project"};
	int ze_project_result = boost::process::system(ze_project_command);
	if (ze_project_result) {
		std::cerr << "Error when getting the ze.project" << std::endl;
		return 1;
	}

	// parse ze.project
	ze_parser parser("./lib/" + project_name + "/ze.project");
	if (parser.no_good) {
		return 1;
	}

	for (auto file : parser.files) {
		string command {"curl -o ./lib/" + project_name + "/" + file + " " + remote + file};
		int result = boost::process::system(command);
		std::cout << result << std::endl;
	}
	/*
	string command {"curl -o ./lib/" + project_name + ".cpp" + " " + remote + project_name + ".cpp"};
	int result = boost::process::system(command);
	std::cout << result << std::endl;
	*/
	return 0;
}

