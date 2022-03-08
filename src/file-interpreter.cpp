#include "scoopstd.hpp"
#include <iostream>
#include <fstream>

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

int main(int argc, char * args[]){
    if(argc == 2){
        std::cout << "Running: " << args[argc - 1] << std::endl << std::endl;
	    std::ifstream codeFile;
	    codeFile.open(args[argc - 1]);

	    std::string tmp, code;
        bool count{false};

	    while(codeFile >> tmp){
            if (!count){
		        code += tmp;
                count = true;
            } else {
                code += " " + tmp;
            }
	    }
        uint8_t a{0};

        interpret(a, code);
        if(tmp != "printline"){
            cout << "\n";
        }
    }
    else{
        cout << "Error: Number of files too low or too high (Must be 1)" << std::endl;
    }
}