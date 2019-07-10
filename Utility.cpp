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