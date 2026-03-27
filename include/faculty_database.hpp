#ifndef FACULTYDAT_H
#define FACULTYDAT_H
#include <string>
#include <iostream>
#include <unordered_map>
#include "faculty.hpp"
using namespace std;
class facultyDatabase{
    private:
        unordered_map<string, faculty> facultyMap;
        string rosterFile = "../database/faculty.csv";
    public:
        void loadFacultyFromFile();
        bool isExistingFaculty(const string& loginID);
        void registerNewFaculty(const std::string& password);

        unordered_map<string, faculty> get_sd();
};
#endif