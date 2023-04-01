/**
 * @file bloom.cc
 * @brief Implementation of a bloom filter in C++.
 */

#include <bloom.hh>
#include <hash.hh>
#include <CLI/CLI.hpp>

using namespace std;

class BloomFilter 
{
public:
    int m, k, n;
    int *data;
    vector<lamb_hash> hash_set;
    int collisions;
    vector<string> collision_words;

    BloomFilter(const int m, const int k, const vector<lamb_hash> hash_set) 
    /**
     * @brief Bloom Filter constructor. 
     * @param m number of bits
     * @param k number of hash functions
     * @param hash_set set of all hash functions
     */
    {
        this->m = m;
        this->k = k;
        this->n = 0;
        this->hash_set = hash_set;
        this->collisions = 0;
        this->collision_words;

        this->data = new int[m];
        memset(this->data, 0, m*sizeof(int));
    }

    void insert(const string& element)
    /** 
     * @brief Insert hash into Bloom Filter. 
     * @param element is the word to insert
     */
    {
        bool collision = true;
        for (auto fun : hash_set) {
            size_t hash = fun(element, m) % m;
            /* If all hashes are 1, a collision has occured */
            if (data[hash] == 0) collision = false;
            data[hash] = 1;
        }
        if (collision == true) {
            collision_words.push_back(element);
            collisions++;
        }
        n++;
    }

    double search(const string& element)
    /** 
     * @brief Search for a hash in the Bloom Filter.
     * @param element is the word to search
     * @return The false probability
     */
    {
        for (auto fun : hash_set) {
            size_t hash = fun(element, m) % m;
            if (data[hash] == 0) return -1.0;
        }
        double prob = pow(1.0 - pow(1.0 - 1.0/m, k*n), k);
        return prob;
    }

    ~BloomFilter() 
    /** Destructor. */
    {
        delete[] data;
    }
};

int bloom(const int m, const int k, const string& search_query, const string& input)
/** 
 * @brief Initializes a Bloom Filter
 * @param m is the number of bits 
 * @param k is the number of hash functions
 * @param search_query is the comma-separated string of words to search
 * @param input is the input stream
 * @returns The number of collisions
 */
{
    vector<lamb_hash> hash_set = get_hashset(k);

    /* Put bf on the heap */
    BloomFilter* bf = new BloomFilter(m, k, hash_set);

    /* Insert all words in the dictionary */
    ifstream infile(input);
    string word;
    while (infile >> word)
        bf->insert(word);
    infile.close();

    /* Log the number of collisions */
    spdlog::info("Collisions: {}", bf->collisions);

    /* If there are searches, get the false positive probability for each query */
    if (!search_query.empty()) {
        stringstream ss(search_query);
        ostringstream f_pos;
        string keyword;
        while (getline(ss, keyword, ','))
            f_pos << bf->search(keyword) << " ";

        spdlog::info("False positive probabilities: {}", f_pos.str());
    }

    ostringstream collision_inf;
    for (auto cw : bf->collision_words)
            collision_inf << cw << " ";

    spdlog::debug("Collision words: {}", collision_inf.str());

    /* Deallocate when finished */
    int collisions = bf->collisions;
    delete bf; 

    return collisions;
}

#ifdef BLOOM
int main(int argc, char **argv) 
{

    spdlog::set_level(spdlog::level::debug);
    /* spdlog::set_level(spdlog::level::info); */

    int m;
    int k;
    string input; 
    string search_query;

    CLI::App app("BloomFilter CLI");
    app.add_option("-m", m, "Number of bits")->default_val(100);
    app.add_option("-k", k, "Number of hash functions")->default_val(2);
    app.add_option("-i", input, "Input method")->default_val("./data/american-english");
    app.add_option("-s", search_query, "Comma-separated list of search terms")->default_val("");
    // TODO: Add option for list of hash functions
    CLI11_PARSE(app, argc, argv);

    /* Init bloom filter */
    bloom(m, k, search_query, input);

    return 0;
}
#endif
