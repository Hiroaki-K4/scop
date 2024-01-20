#include <iostream>
#include "Parser.hpp"

Parser::Parser(const std::string &obj_path) {
    std::cout << "obj path: " << obj_path << std::endl;
    this->obj_path = obj_path;
}

void Parser::parse_vertice_coordinate(
    std::string &line, const std::string &delimiter, std::vector<double> &vertice) {
    size_t pos;
    std::string token;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        vertice.push_back(stod(token));
        line.erase(0, pos + delimiter.length());
    }
    if (line.length() != 0) {
        vertice.push_back(stod(line));
    }

}

void Parser::parse_face_element(
    std::string &line, const std::string &delimiter, std::vector<int> &face_element) {
    size_t pos;
    std::string token;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        face_element.push_back(stoi(token));
        line.erase(0, pos + delimiter.length());
    }
    if (line.length() != 0) {
        face_element.push_back(stoi(line));
    }
}

void Parser::parse_obj_file(
    std::vector<std::vector<double>> &vertices,
    std::vector<std::vector<int>> &face_elements) {
    std::string line;
    std::ifstream myfile(this->obj_path);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            std::string delimiter = " ";
            size_t pos = 0;
            std::string token;
            if ((pos = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                if (token == "v") {
                    std::vector<double> vertice;
                    parse_vertice_coordinate(line, delimiter, vertice);
                    if (vertice.size() == 3) {
                        vertices.push_back(vertice);
                        continue;
                    }
                } else if (token == "f") {
                    std::vector<int> face_element;
                    parse_face_element(line, delimiter, face_element);
                    if (face_element.size() >= 3) {
                        face_elements.push_back(face_element);
                        continue;
                    }
                    continue;
                }
            }
        }
        myfile.close();
        std::cout << "Parsed obj file." << std::endl;
        std::cout << "vertices size: " << vertices.size() << std::endl;
        std::cout << "face_elements size: " << face_elements.size() << std::endl;
    } else {
        std::cout << "Error: Failed to open the obj file" << std::endl;
    }
}

void Parser::create_polygons(
    const std::vector<std::vector<double>> &vertices,
    const std::vector<std::vector<int>> &face_elements,
    std::vector<std::vector<double>> &polygons) {
    std::vector<double> vert;
    for (int i = 0; i < face_elements.size(); i++) {
        std::vector<int> face_elem = face_elements[i];
        if (face_elem.size() >= 3) {
            for (int j = 0; j < 3; j++) {
                vert = vertices[face_elem[j]];
                vert.push_back(0.0f);
                vert.push_back(0.0f);
                polygons.push_back(vert);
            }
            if (face_elem.size() == 4) {
                vert = vertices[face_elem[0]];
                vert.push_back(0.0f);
                vert.push_back(0.0f);
                polygons.push_back(vert);
                vert = vertices[face_elem[2]];
                vert.push_back(0.0f);
                vert.push_back(0.0f);
                polygons.push_back(vert);
                vert = vertices[face_elem[3]];
                vert.push_back(0.0f);
                vert.push_back(0.0f);
                polygons.push_back(vert);
            }
        }
    }
    std::cout << "polygons size: " << polygons.size() << std::endl;
}

float* Parser::convert_polygons_vector_to_float_vertices(
    const std::vector<std::vector<double>> &polygons,
    const int info_num) {
    float vertices[polygons.size() * info_num];
    std::cout << "size: " << sizeof(vertices) << std::endl;
    for (int i = 0; i < polygons.size(); i++) {
        for (int j = 0; j < polygons.size(); j++) {
            vertices[i * info_num + j] = polygons[i][j];
            // std::cout << "helo" << std::endl;
        }
    }
    // TODO: Fix float arr to store vertex value
    for (int i = 0; i < 30; i++) {
        std::cout << "Float: " << vertices[i] << std::endl;
    }
    return {};
}
