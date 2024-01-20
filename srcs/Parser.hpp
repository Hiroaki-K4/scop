#ifndef PARSER_HPP
# define PARSER_HPP

#include <fstream>
#include <iostream>
#include <string>

class Parser
{
    private:
        std::string obj_path;

    public:
        Parser(const std::string &obj_path);
        void parse_obj_file();
};

#endif
