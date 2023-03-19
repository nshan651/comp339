#include <bloom.hh>
#include <hash.hh>
#include <CLI/CLI.hpp>

using namespace std;

class BloomFilter 
{
    int m, k, n;
    vector<lamb_hash> hash_set;
    int *data;

public:
    BloomFilter(const int m, const int k, const vector<lamb_hash> hash_set) 
    /** Bloom filter constructor.
        Arguments:
            m | the number of bits
            k | the number of hash functions
    */
    {
        this->m = m;
        this->k = k;
        this->n = 0;
        this->hash_set = hash_set;

        this->data = new int[m];
        memset(this->data, 0, m*sizeof(int));
    }

    /* void insert(const string& element, const vector<lamb_hash> &hs) */
    void insert(const string& element)
    /** Insert hash into Bloom Filter. */
    {
        for (auto fun : hash_set) {
            size_t hash = fun(element, m) % m;
            data[hash] = 1;
        }
        n++;
    }

    double search(const string& element)
    /* string search(const string& element, const vector<lamb_hash> &hs) */
    /** Search for a hash in the Bloom Filter. */
    {
        for (auto fun : hash_set) {
            size_t hash = fun(element, m) % m;
            if (data[hash] == 0) {
                cout << "Not in Bloom Filter\n";
                return -1.0;
                /* return "Not in Bloom Filter\n"; */
            }
        }
        double prob = pow(1.0 - pow(1.0 - 1.0/m, k*n), k);
        cout << "Might be in Bloom Filter with false positive probability " << to_string(prob) << "\n";
        return prob;
        /* return "Might be in Bloom Filter with false positive probability " + to_string(prob) + "\n"; */
    }

    /** Accessors */
    int *get_data()
    {
        return data;
    }
    int get_m()
    {
        return m;
    }
    int get_n()
    {
        return n;
    }
    int get_k()
    {
        return k;
    }

    ~BloomFilter() 
    /** Destructor. */
    {
        delete[] data;
    }
};

int init(const int m, 
         const int k, 
         const vector<lamb_hash> hash_set, 
         const string& input, 
         const vector<string> &keywords)
/** Initialize the Bloom Filter*/
{
    /* Put bf on the heap */
    BloomFilter* bf = new BloomFilter(m, k, hash_set);

    /* Insert all words in the dictionary */
    ifstream infile(input);
    string word;
    while (infile >> word) {
        bf->insert(word);
    }
    infile.close();
   
    /* Search all keywords */
    for (auto& keyword : keywords) 
        bf->search(keyword);

    /* Deallocate when finished */
    delete bf; 

    return 0;
}

int main(int argc, char **argv) 
{
    /* Define an array of hash functions to use */
    vector<lamb_hash> hashes;
    hashes.push_back(sha512);
    hashes.push_back(whirlpool);
    hashes.push_back(sha256);
    hashes.push_back(ripemd160);

    int m = 0;
    int k = 0;
    string input; 
    string search_query;
    vector<string> keywords;

    CLI::App app("BloomFilter CLI");

    /* app.add_option("-m", m, "Number of bits")->required(); */
    app.add_option("-m", m, "Number of bits")->default_val(100);
    app.add_option("-k", k, "Number of hash functions")->default_val(2);
    app.add_option("-i", input, "Input method")->default_val("./data/american-english");
    app.add_option("-s", search_query, "Comma-separated list of search terms")->default_val("Hello,No Way,ge");
    // TODO: Add option for list of hash functions

    CLI11_PARSE(app, argc, argv);

    stringstream ss(search_query);
    string keyword;
    while (getline(ss, keyword, ','))
        keywords.push_back(keyword);

    /* Slice the list of available hash functions according to k */
    int end_slice = k < hashes.size() ? k : hashes.size();
    const vector<lamb_hash> hash_set(hashes.begin(), hashes.begin() + end_slice);

    /* Init bloom filter */
    init(m, k, hash_set, input, keywords);

    return 0;
}

