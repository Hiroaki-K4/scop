#ifndef PARSER_HPP
# define PARSER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Parser
{
    private:
        std::string obj_path;

    public:
        Parser(const std::string &obj_path);
        void parse_obj_file(
            std::vector<std::vector<double>> &vertices,
            std::vector<std::vector<int>> &face_elements);
        void parse_vertice_coordinate(
            std::string &line, const std::string &delimiter,
            std::vector<double> &vertice);
        void parse_face_element(
            std::string &line, const std::string &delimiter,
            std::vector<int> &face_element);
        void create_polygons(
            const std::vector<std::vector<double>> &vertices,
            const std::vector<std::vector<int>> &face_elements,
            std::vector<std::vector<double>> &polygons);
        float* convert_polygons_vector_to_float_vertices(
            const std::vector<std::vector<double>> &polygons,
            const int info_num);
};

#endif
