#include <fstream>
#include <iostream>
#include <random>
#include <functional>
#include <algorithm>
#include <chrono>
#include <list>

#include "helper_functions.hpp" 

using namespace std;

/* Seed variables */
static uint x=123456789,y=362436000,z=521288629,c=7654321; 

uint KISS(){ 
    unsigned long long t, x=69069*x+12345; /* multiply with carry */
    y^=(y<<13);         /* xor shift */
    y^=(y>>17);         /* xor shift */
    y^=(y<<5);          /* xor shift */
    t=698769069ULL*z+c; /* lcg */
    c=(t>>32); 
    z = t;
    return x+y+z;       /* add all 3 */
}

int main(int argc, char* argv[]) {

    cout << "PRNG generator started" << endl;

    // samples
    uint samples_size = 10000; //default size
    int generators_count = 5 + 4; /*4 is for kiss*/
    
    // vector<uint> v;
    
    try{
        if (argc > 1) 
            samples_size = static_cast<uint>(stoi(argv[1]));
        // v.resize(samples_size);
    } catch (std::out_of_range &b) {
        cout << "Bad alloc of size " << argv[1] << endl;
        cout << b.what() << endl;
        return 1;
    }

    // seeds

    cout << "time " << time(NULL) << endl;
    uint time_ = time(NULL);
    std::vector<std::uint32_t> seeds(generators_count);
    std::vector<uint> ints_;
    for (uint i = 0; i < generators_count; ++i)
        ints_.push_back(time_ + i);
    
    PrintVectorSpaced(ints_, "Sequence");

    std::seed_seq seq(ints_.cbegin(), ints_.cend());
    seq.generate(seeds.begin(), seeds.end());

    PrintVectorSpaced(seeds, "Seeds   ");

    auto seeds_it = seeds.begin();
    auto take_seed = [&seeds_it]() -> uint { return *(seeds_it++);};

    // generators init
    std::mt19937 mt;
    // std::mersenne_twister_engine<std::uint_fast32_t, 32, 624, 397, 31,
                            //  0x9908b0df, 11,
                            //  0xffffffff, 7,
                            //  0x9d2c5680, 15,
                            //  0xefc60000, 18, 1812433253> gen;
    mt.seed(take_seed()); // seed MT

    srand(take_seed()); // seed rand

    std::minstd_rand0 minst; // linear_congruential_engine
    minst.seed(take_seed()); // seed minst

    std::ranlux24_base ranlux; // subtract_with_carry_engine
    ranlux.seed(take_seed());

    std::knuth_b knuth; // Knuth algo
    knuth.seed(take_seed());

    // algorithm containers

    auto info = "_" + std::to_string(samples_size); 
    std::list<std::function<uint()>> gen_list;
    std::vector<std::string> algo_list;

    gen_list.push_back(mt);
    algo_list.push_back("MerTw" + info);

    gen_list.push_back(minst);
    algo_list.push_back("MinSt" + info);

    gen_list.push_back(std::rand);
    algo_list.push_back("Rand" + info);

    gen_list.push_back(ranlux);
    algo_list.push_back("RanLux" + info);

    gen_list.push_back(knuth);
    algo_list.push_back("Knuth" + info);

    x = take_seed();
    y = take_seed();    
    z = take_seed();
    c = take_seed();

    gen_list.push_back(KISS);
    algo_list.push_back("kiss" + info);

    // generation
    int i = 0;
    for (auto &generator : gen_list) {
            
        auto file_name = "prng_" + algo_list.at(i++) + ".txt";
        auto start_t = std::chrono::steady_clock::now();
        SaveGenerationToFile(file_name, samples_size, generator);
        auto end_t = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end_t-start_t;
        cout << "PRNG generator processed " + file_name << " in time " << elapsed_seconds.count() << endl;
        
    }

    cout << "PRNG generator ended" << endl;
    return 0;
}