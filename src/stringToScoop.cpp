#include <iostream>
#include <string>

int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		std::cout << "Error: incorrect number of arguments (Must be two)\n";
	}
	else
	{
		std::string toShow{""};
		char* ptr = argv[1];
		for (char c = *ptr; c; c=*++ptr) 
		{
			int charToInt = c;
			std::string toAdd{std::to_string(charToInt)};
			
			toShow += "set " + toAdd + " print\n";
		}
		std::cout << toShow;
	}

}
