#include <iostream>
#include "Parser.hpp"

Parser::Parser(const std::string &obj_path) {
    std::cout << "Obj path: " << obj_path << std::endl;
    this->obj_path = obj_path;
}

void Parser::parse_obj_file() {
    std::string line;
    std::string fac;
    std::ifstream myfile(this->obj_path);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            std::string delimiter = " ";
            size_t pos = 0;
            std::string token;
            pos = line.find(delimiter);
            std::cout << "pos: " << pos << std::endl;
            // if ((pos = line.find(delimiter)) != std::string::npos) {
            //     if \
            // }
            while ((pos = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, pos);
                std::cout << "token: " << token << std::endl;
                line.erase(0, pos + delimiter.length());
                if (token == "v") {
                    std::cout << "v: " << token << std::endl;
                } else if (token == "f") {
                    std::cout << "f: " << token << std::endl;
                }
            }
        }
        myfile.close();
    } else {
        std::cout << "Error: Failed to open the obj file" << std::endl;
    }
}
