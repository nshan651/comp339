#include <bloom.hh>
#include <hash.hh>
#include <CLI/CLI.hpp>

#include <queue>
#include <unordered_map>
#include <bitset>
#include <fmt/core.h>

using namespace std;

vector<string> scan_words(const string& text)
{
    static vector<string> words; 
    std::ifstream file(text);
    if (!file.is_open()) {
        cerr << "Failed to open file" << endl;
        return words;
    }

    string word;
    while (file >> word)
        words.push_back(word);

    file.close();

    return words;
}

/* void cloud(const vector<string>& words) */
void cloud()
{
    int wsize = 10;
    const int m = 10000000;
    int k = 4;
    /* int everyK = 1000; */
    string word;
    priority_queue<string> slide;
    vector<lamb_hash> hash_set = get_hashset(k);

    ifstream file("./data/hamlet.txt");
    unordered_map<string, int> counts;
    bitset<m> bloom_filter;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> top_words;

    // Read the first WINDOW_SIZE words and initialize the bloom filter and counts
    for (int i = 0; i < wsize; i++) {
        file >> word;
        counts[word]++;
        for (auto fun : hash_set) {
            int hash = fun(word, m) % m;
            bloom_filter[hash] = 1;
        }
    }

    // Update the counts and priority queue for each new word in the corpus
    while (file >> word) {

        fmt::print("word is {}\n", word); 
        // Check if the word is in the bloom filter
        bool in_filter = true;

        for (auto fun : hash_set) {
            int hash = fun(word, m) % m;
            if (!bloom_filter[hash]) {
                in_filter = false;
                break;
            }
        }
        if (!in_filter) {
            // Update the bloom filter and counts for the new word
            for (auto fun : hash_set) {
                int hash = fun(word, m) % m;
                bloom_filter[hash] = 1;
            }
            counts[word]++;
            // Update the counts and priority queue for all words in the current sliding window
            for (auto& p : counts) {
                if (p.second > 0) {
                    top_words.push(make_pair(p.second, p.first));
                    if (top_words.size() > 10) {
                        top_words.pop();
                    }
                }
            }
        } 
        else {
            // Update the priority queue for the existing word
            while (!top_words.empty()) {
                auto p = top_words.top();
                top_words.pop();
                if (p.second == word) {
                    top_words.push(make_pair(p.first + 1, p.second));
                    break;
                }
            }
        }
        // Remove the oldest word from the sliding window
        counts[word]--;
        if (counts[word] == 0) {
            counts.erase(word);
        }
    }

    // Print the top 10 words in the sliding window
    while (!top_words.empty()) {
        cout << top_words.top().second << " " << top_words.top().first << endl;
        top_words.pop();
    }

    /* for_each(words.begin(), words.end(), [&](const string& word) { */
    /*     fmt::print("Word: {}", wsize); */
    /* }); */
}

#ifdef CLOUD
int main(int argc, char* argv[])
{
    /* spdlog::set_level(spdlog::level::debug); */
    spdlog::set_level(spdlog::level::info);

    int m;
    int k;
    string input; 
    string search_query;
    const string text = "./data/american-english";

    CLI::App app("BloomFilter CLI");
    app.add_option("-m", m, "Number of bits")->default_val(100);
    app.add_option("-k", k, "Number of hash functions")->default_val(2);
    app.add_option("-i", input, "Input method")->default_val("./data/american-english");
    app.add_option("-s", search_query, "Comma-separated list of search terms")->default_val("");
    // TODO: Add option for list of hash functions
    CLI11_PARSE(app, argc, argv);

    cloud();
    // Init bloom filter 
    /* bloom(m, k, search_query, input); */

    /* vector<string> words = scan_words(text); */

    /* map<string, int> cloud = countAndSort(words); */


    // Loop through words using for_each loop
    /* for_each(words.begin(), words.end(), processing); */

    return 0;
}
#endif
