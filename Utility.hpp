#pragma once

#include <string>
#include <vector>

void load_bin_file(std::string bin_location, std::vector<char> * mem_location);

template <typename T> 
int sign(T val);