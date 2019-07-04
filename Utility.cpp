#include <fstream>
#include <string>
#include <vector>

using namespace std;

void load_bin_file(string bin_location, vector<char> * mem_location)
{
	ifstream file(bin_location, ios::in | ios::binary);
	file.read(mem_location->data(), 768);

	file.close();
}

template <typename T> 
int sign(T val) 
{
    return (T(0) < val) - (val < T(0));
}
