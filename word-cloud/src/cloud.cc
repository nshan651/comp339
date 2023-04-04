/* #include <cloud.hh> */
#include <bloom.hh>
#include <hash.hh>
#include <CLI/CLI.hpp>
#include <queue>
#include <unordered_map>

using namespace std;

/*
vector<pair<string, size_t>> top_n_words(const vector<string>& words, const size_t k, const int m)
{
    vector<size_t> word_counts(256, 0); // initialize with a default size of 256, to cover all ASCII characters
    vector<pair<string, size_t>> top_n;

    for (const auto& word : words) {
        // size_t hashed_value = sha512(word, m);
        ++word_counts[hashed_value];

        // Check if the word is already in the top_n vector
        auto it = find_if(top_n.begin(), top_n.end(), [word](const pair<string, size_t>& p) { return p.first == word; });

        if (it != top_n.end()) {
            it->second = word_counts[hashed_value];
        }
        else {
            top_n.emplace_back(make_pair(word, word_counts[hashed_value]));
        }

        // Sort the top_n vector in descending order based on the count
        sort(top_n.begin(), top_n.end(), [](const pair<string, size_t>& p1, const pair<string, size_t>& p2) {
            return p1.second > p2.second;
        });

        // Keep only the top k words
        if (top_n.size() > k) {
            top_n.pop_back();
        }
    }

    return top_n;
}
*/

/* int main(int argc, char* argv[]) { */
/*     return 0; */
/* } */

    /*
    int window_size;
    string input;

    CLI::App app("Word Cloud");
    app.add_option("-n", window_size, "The top n words")->default_val(10);
    app.add_option("-i", input, "Input method")->default_val("./data/hamlet.txt");
    
    ifstream infile(input);

    if (!infile.is_open()) {
        cout << "Error opening file\n";
        return 1;
    }
    
    // TODO: add these as args
    long m = 1000000;
    int n = 1000000;
    int k = 2;
    vector<size_t> word_count;
    vector<string> lookup;
    vector<string> words;
    // queue<pair<string, int>> sliding;
    queue<size_t> sliding;
    // Zero out both vecs
    for (int i = 0; i < n; i++) {
        word_count.push_back(0);
        lookup.push_back("");
    }

    vector<lamb_hash> hash_set = get_hashset(k);

    priority_queue<size_t> sliding_queue;

    string word;
    while (infile >> word) {
        words.push_back(word);
        for (auto fun : hash_set) {
            size_t hash = fun(word, m) % m;
            word_count.insert(word_count.begin() + hash, 
                word_count[hash]+1);
            lookup.insert(lookup.begin() + hash, 
                word);
            sliding.push(hash);
        }

        if (sliding.size() > window_size)
            sliding.pop();
    }

    auto top_n = top_n_words(words, 10, m);

    cout << "The top " << top_n.size() << " most frequent words are:" << endl;

    for (const auto& p : top_n) {
        cout << p.first << ": " << p.second << endl;
    }

    */
