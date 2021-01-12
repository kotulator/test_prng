#include <fstream>
#include <iostream>
#include <random>
#include <functional>
#include <algorithm>

#include "helper_functions.hpp" 

using namespace std;


void GenerateWithRand(std::vector<uint> &vec, const int &no_of_samples ) {
    
    vec.clear();

    srand (time(NULL));

    vec.reserve(no_of_samples);
    for (int i = 0; i < no_of_samples; i++) {
        vec.push_back(rand());
        }
}

void GenerateWithMT(std::vector<uint> &vec, const int &no_of_samples) {

    vec.clear();    
    std::mt19937 gen;
    // std::mersenne_twister_engine<std::uint_fast32_t, 32, 624, 397, 31,
                            //  0x9908b0df, 11,
                            //  0xffffffff, 7,
                            //  0x9d2c5680, 15,
                            //  0xefc60000, 18, 1812433253> gen;
    gen.seed(time(NULL));

    vec.reserve(no_of_samples);
    for (int i = 0; i < no_of_samples; i++) {
        vec.push_back(gen());
        }
}


void GenerateWithF(std::vector<uint> &vec, const int &no_of_samples, std::function<uint()> generator) {

    vec.clear();   
    vec.reserve(no_of_samples);
    for (int i = 0; i < no_of_samples; i++) {
        vec.push_back(generator());
        }
}

int main(int argc, char* argv[]) {

    cout << "PRNG generator" << endl;

    std::mt19937 mt;
    // std::mersenne_twister_engine<std::uint_fast32_t, 32, 624, 397, 31,
                            //  0x9908b0df, 11,
                            //  0xffffffff, 7,
                            //  0x9d2c5680, 15,
                            //  0xefc60000, 18, 1812433253> gen;
    mt.seed(time(NULL));

    srand(time(NULL));

    vector<uint> v(100, 0.);
    // GenerateWithMT(v, 100);
    // SaveVectorToFile(v, "test_prng_mt.txt");

    // GenerateWithRand(v, 100);
    // SaveVectorToFile(v, "test_prng_rand.txt");

    // auto f = [&gen]() -> uint {
    //     return gen();
    // };
    // GenerateWithF(v, 100, f);
    // SaveVectorToFile(v, "test_prng_wf.txt");

    std::generate(v.begin(), v.end(), mt);
    SaveVectorToFile(v, "test_prng_mt.txt");

    std::generate(v.begin(), v.end(), std::rand);
    SaveVectorToFile(v, "test_prng_rand.txt");

    return 0;
}