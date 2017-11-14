#include "parser.h"

Parser::Parser(int argc,std::vector<std::string>& r_user_arguments)
    {
        command_words_num = argc;
        command_words = r_user_arguments;
        
    }
Parser::~Parser()
    {
    }
    
    int Parser::parse_user_arguments()
    {
        if(determine_user_command())
        {
            if(o_command_index == 0)
            {
                return 0;
            }
            if(o_command_index == 1) //ADD
            {
                bool next_word_is_list = false;
                for(int i=2;i<command_words_num;i++)
                {
                    if(command_words.at(i).at(0) == '-')
                    {
                        std::cout << "detected option" << std::endl;
                        switch(command_words.at(i).at(1))
                        {
                            case 'l':
                                next_word_is_list = true;
                                break;
                            case 's' :
                                std::cout << "Just specifying sources cause why not lol" << std::endl;
                                break;
                            case 'p' :
                                std::cout << "Preserve option enabled" << std::endl;
                                break;
                            case 'n' :
                                std::cout << "No-preserve option enabled" << std::endl;
                                break;
                            default:
                                std::cout << "unknown option" << std::endl;

                        }
                    }
                    else
                    {
                        //TODO check if file exists if it's about specifying file
                        if(next_word_is_list == false)
                        {
                           command_words.at(i) = makePathAbsolute(command_words.at(i));
                           std::cout << "Absolute path is:" << command_words.at(i) << std::endl;
                           o_add_paths.push_back(command_words.at(i)); 
                        }
                        else
                        {
                            o_list[0] = "true";
                            o_list[1] = command_words.at(i);
                            next_word_is_list = false;
                        }
                    }
                }
            }
            if(o_command_index == 2) //SET-DESTINATION
            {
               o_destination[0] = "false";
               bool next_word_is_list = false;
               for(int i=2;i<command_words_num;i++)
               {
                   if(command_words.at(i).at(0) == '-')
                   {
                       switch(command_words.at(i).at(1))
                       {
                           case 'l' :
                               std::cout << "option list" << std::endl;
                               next_word_is_list = true;
                               break;
                           case 'p' :
                               std::cout << "Preserve option enabled" << std::endl;
                               break;
                           case 'n' :
                               std::cout << "No-preserve option enabled" << std::endl;
                               break;
                           default :
                               std::cout << "unknown option" << std::endl;
                                   break;

                       }
                   }
                   else
                   {
                       if(next_word_is_list == true)
                       {
                           o_list[0] = "true";
                           o_list[1] = command_words.at(i);
                           next_word_is_list = false;
                       }
                       else
                       {
                           command_words.at(i) = makePathAbsolute(command_words.at(i));
                           o_destination[0] = "true"; //
                           o_destination[1] = command_words.at(i);
                       }
                   }
               } 
            }
            if(o_command_index == 3) //REMOVE
            {
                bool next_word_is_list = false;
                for(int i=2;i<command_words_num;i++)
                {
                    if(command_words.at(i).at(0) == '-')
                    {
                        std::cout << "detected option" << std::endl;
                        switch(command_words.at(i).at(1))
                        {
                            case 'l':
                                next_word_is_list = true;
                                break;
                            case 's' :
                                std::cout << "Just specifying sources cause why not lol" << std::endl;
                                break;
                            case 'p' :
                                std::cout << "Preserve option enabled" << std::endl;
                                break;
                            case 'n' :
                                std::cout << "No-preserve option enabled" << std::endl;
                                break;
                            default:
                                std::cout << "unknown option" << std::endl;

                        }
                    }
                    else
                    {
                        //TODO check if file is on the list if it's about specifying file
                        if(next_word_is_list == false)
                        {
                           o_remove_paths.push_back(command_words.at(i)); 
                        }
                        else
                        {
                            o_list[0] = "true";
                            o_list[1] = command_words.at(i);
                            next_word_is_list = false;
                        }
                    }
                }
            }
            if(o_command_index == 4) //BACKUP
            {
                for(int i=2;i<command_words_num;i++)
                {
                    if(command_words.at(i).at(0) == '-')
                    {
                        std::cout << "detected option" << std::endl;
                        switch(command_words.at(i).at(1))
                        {
                            case 'l' :
                                std::cout << "list option detected, nothing changes anwyay" << std::endl;
                                break;
                            case 'p' :
                                std::cout << "Preserve option enabled" << std::endl;
                                break;
                            case 'n' :
                                std::cout << "No-preserve option enabled" << std::endl;
                                break;
                            default:
                                std::cout << "unknown option" << std::endl;
                        }
                    }
                    else
                    {
                        o_list[0] = "true";
                        o_list[1] = command_words.at(i);
                    }
                }
            }
        }
        else
        {
            std::cout << "Invalid command. Please use one of the following: 'add', 'set-destination', 'remove', 'backup'" << std::endl;
        }

        return 1;
    }

    int Parser::determine_user_command()
    {
    try {
            if(command_words.at(1) == "add")
            {
                o_command_index = 1;
            }
            else if(command_words.at(1) == "set-destination")
            {
                o_command_index = 2;
            }
            else if(command_words.at(1) == "remove")
            {
                o_command_index = 3;
            }
            else if(command_words.at(1) == "backup")
            {
                o_command_index = 4;
            }
            else
            {
                o_command_index = 0;
            }
        }
    catch (std::out_of_range& e)
        {
                return 0;
        }
            return 1;
    }

    std::string Parser::makePathAbsolute(std::string path)
    {
        if(path.at(0) == '/')
        {
            return path;
        }
        else
        {
            std::string prepend_string;
            char buffer[100000]; //Yes. Hardcoded. You know why? Cause MAX_PATH is broken and using it would be no guarantee whatsoever (unless it's fixed). Hardcoding this at least
                                //does not imply safety where it does not exist.
            prepend_string.assign(getcwd(buffer, sizeof(buffer)));
            path.insert(0, prepend_string);
            return path;
        }
    }
