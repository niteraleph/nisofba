#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <stdio.h>

class Parser
{
  public: 
    Parser(int argc, std::vector<std::string>& r_user_arguments);
    ~Parser();
    int parse_user_arguments();
  private:
    int command_words_num;
    std::vector<std::string> command_words;
    int determine_user_command();
    std::string makePathAbsolute(std::string path);
    int o_command_index; //ADD, SET-DESTINATION, REMOVE, BACKUP 
    std::vector<std::string> o_add_paths;
    std::vector<std::string> o_remove_paths;
    std::string o_list [2];
    std::string o_destination [2];
    
};
