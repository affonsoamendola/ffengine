/*  
	Copyright Affonso Amendola 2019

	Fofonso's Standard Library

	This is part of my standard library of functions and stuff.

	Distributed under GPLv3, use it to your hearts content,
	just remember the number one rule:

	Be Excellent to Each Other.
*/

#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Loads a binary file into a memory locations, reads byte_count bytes into it.
void load_bin_file(string bin_location, vector<char> * mem_location, unsigned int byte_count)
{
	ifstream file(bin_location, ios::in | ios::binary);
	file.read(mem_location->data(), byte_count);

	file.close();
}

bool condition_vector_true(std::vector<bool> condition_vector)
{
	bool answer = true;

	for(int i = 0; i < condition_vector.size(); i++)
	{
		if(condition_vector[i] == false) answer = false;
	}

	return answer;
}

bool condition_vector_false(std::vector<bool> condition_vector)
{
	bool answer = false;

	for(int i = 0; i < condition_vector.size(); i++)
	{
		if(condition_vector[i] == true) answer = true;
	}

	return answer;
}




