#ifndef RNG_HELPERS
#define RNG_HELPERS

#include <vector>
#include <fstream>
#include <iostream>

using std::endl;

template <typename T>
void SaveVectorToFile(const std::vector<T> &vec, const std::string &file_name) {

    std::ofstream o;
    o.open(file_name);
 
    o << "type: d" << endl;
    o << "count: " << vec.size() << endl;
    o << "numbit: 32" << endl;
    for ( auto const &val : vec) o << val << std::endl;

    o.close();

}


#endif