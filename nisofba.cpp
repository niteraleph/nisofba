#include <iostream>
#include <string>
#include <vector>
#include "parser.h"
#include "nisofba.h"

int main(int argc, char **argv)
{
    std::vector<std::string> user_arguments;
    std::cout << "Hello World\n";
    fillUserArguments(argc, user_arguments, argv);
    Parser parser(argc, user_arguments); 
    parser.parse_user_arguments();
    //std::cout << "folder destynacji to: " << parser.o_destination[1] << std::endl;
    return 0; 
}

int fillUserArguments(int argumentNum, std::vector<std::string>& r_user_arguments, char **argumentVal)
{
    for(int i=0; i<argumentNum;i++)
    {
        r_user_arguments.push_back(argumentVal[i]);
    } 
    return 0;
}

