#include <iostream>
#include <boost/process.hpp>

using std::string;

int main(int argc, char* argv[]) {
	if (argc <= 2) {
		std::cerr << "Need more args!" << std::endl;
		return 1;
	}

	string name {argv[2]};
	string remote {"https://raw.githubusercontent.com/tooyoungtoosimplesometimesnaive/code_base_snapshot/master/"};
	string command {"curl -o ./lib/" + name + ".cpp" + " " + remote + name + ".cpp"};
	int result = boost::process::system(command);
	std::cout << result << std::endl;
	return 0;
}

