#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <typeinfo>

//Read as CSV file - default separator is ';'
std::vector<std::vector<std::string>> readCSV(std::string);
//Read as CSV file - specifies separator
std::vector<std::vector<std::string>> readCSV(std::string, char);
//Casts vector of strings from readCSV() as doubles
std::vector<std::vector<double>> doubleVector(std::vector<std::vector<std::string>>);

