#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

vector<pair<string, size_t>> top_k_words(const vector<string>& words, const size_t k) {
    vector<size_t> word_counts(256, 0); // initialize with a default size of 256, to cover all ASCII characters
    vector<pair<string, size_t>> top_k;

    for (const auto& word : words) {
        size_t hashed_value = hash<string>{}(word);
        ++word_counts[hashed_value];

        // Check if the word is already in the top_k vector
        auto it = find_if(top_k.begin(), top_k.end(), [word](const pair<string, size_t>& p) { return p.first == word; });

        if (it != top_k.end()) {
            it->second = word_counts[hashed_value];
        }
        else {
            top_k.emplace_back(make_pair(word, word_counts[hashed_value]));
        }

        // Sort the top_k vector in descending order based on the count
        sort(top_k.begin(), top_k.end(), [](const pair<string, size_t>& p1, const pair<string, size_t>& p2) {
            return p1.second > p2.second;
        });

        // Keep only the top k words
        if (top_k.size() > k) {
            top_k.pop_back();
        }
    }

    return top_k;
}


int main() 
{
    vector<string> words{ "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog",
                          "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog",
                          "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog",
                          "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog",
                          "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog",
                          "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog",
                          "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog",
                          "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog",
                          "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog",
                          "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog",
                          "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog" };

    auto top_k = top_k_words(words, 10);

    cout << "The top " << top_k.size() << " most frequent words are:" << endl;

    for (const auto& p : top_k) {
        cout << p.first << ": " << p.second << endl;
    }

    return 0;
}
