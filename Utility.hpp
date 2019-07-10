#pragma once
/*  
	Copyright Affonso Amendola 2019

	Fofonso's Standard Library

	This is part of my standard library of functions and stuff.

	Distributed under GPLv3, use it to your hearts content,
	just remember the number one rule:

	Be Excellent to Each Other.
*/

#include <string>
#include <vector>

void load_bin_file(std::string bin_location, std::vector<char> * mem_location, unsigned int byte_count);

//My hate for templates doesn't extend to this case, this is what that shit was meant to do.
//This, is perfect.
//Typesafe Sign function, stolen from some rando on the internet, but it's pretty common, dont know who came
//up with this.
template <typename T> 
int sign(T val) 
{
    return (T(0) < val) - (val < T(0));
}
