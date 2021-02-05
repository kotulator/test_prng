#ifndef RNG_HELPERS
#define RNG_HELPERS

#include <vector>
#include <fstream>
#include <iostream>

using std::cout;
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

template <typename T>
void PrintVector(const std::vector<T> &vec, const std::string &name) {
    cout << "Vector " << name << endl;
    for ( auto const &val : vec) cout << val << std::endl;
}

template <typename T>
void PrintVectorSpaced(const std::vector<T> &vec, const std::string &name) {
    cout << "Vector " << name ;
    for ( auto const &val : vec) cout << ' ' << val ;
    cout << endl;
}

void SaveGenerationToFile(const std::string &file_name, const int number_of_samples, std::function<uint()> f) {
    // more efficient, no allocation
    std::ofstream o;
    o.open(file_name);
    // dieharder format
    o << "type: d" << endl;
    o << "count: " << number_of_samples << endl;
    o << "numbit: 32" << endl;
    for (int i = 0 ; i < number_of_samples; ++i)
        o << f() << std::endl;

    o.close();
}

#endif