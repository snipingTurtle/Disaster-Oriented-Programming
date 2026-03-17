#ifndef STUDENTDAT_H
#define STUDENTDAT_H
#include <string>
#include <iostream>
#include <unordered_map>
#include "student.hpp"
using namespace std;
class studentDatabase{
    private:
        unordered_map<string, student> studentDatabase;
        string rosterFile = "../data.csv";
    public:
        void loadStudentsFromFile();
        bool isExistingStudent(const string& loginID);
        void registerNewStudent(const std::string& password);

        unordered_map<string, student> get_sd();
};
#endif