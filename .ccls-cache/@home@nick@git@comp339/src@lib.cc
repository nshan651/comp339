#include <main.hh>

using namespace std;

int rng(const int min, const int max) 
/** Generates a random number given an upper and lower bound */
{
    // Create a random_device to generate a random seed
    random_device rd;
    // Use the seed to create a Mersenne Twister engine
    mt19937 eng(rd());
    uniform_int_distribution<> dist(min, max);

    return dist(eng);
}

string convert_alpha(string &word)
/** Convert each character to an upper-case american english letter */ 
{
    string alpha;
    for (char &c : word) {
        if (isalnum(c, locale()))
            alpha += toupper(c, locale());
        else {
            alpha = "";
            break;
        }
    }
    return alpha;
}

vector<string> split_line(string &line, const int min_len)
/** Split and parse the words in each line of a file, maing sure they are alphanumeric */
{
    stringstream ss(line);
    vector<string> words; 
    
    while (ss >> line) {
        /* Ensure min word length */
        if (line.length() < min_len) {
            cerr << "Error, the minimum word length must be " << min_len;
            exit(1);
        }

        string alpha = convert_alpha(line);
        if (!alpha.empty())
            words.push_back(alpha);
    }
    return words;
}

map<string, int> parse_dict(const Cipher &cipher)
/** Read and parse dictionary, excluding any non-Ascii letters */
{
    ifstream file(cipher.dict);
    string line;
    map<string, int> words;

    int counter = 0;
    while (file >> line) {
        string alpha = convert_alpha(line);
        if (!alpha.empty() && alpha.length() >= cipher.min_len)
            words[alpha] = counter;
            counter++;
    }
    return words;
}

int decode(vector<string> &words, map<string, int> &dictionary)
/** Decodes a single line using a word dictionary */
{
    int threshold = words.size()-1;
    int shift = 0;
    for (shift = 1; shift <= ALPHABET_SIZE; shift++) {
        int matches = 0;
        for (string &word : words) {
            string candidate = shift_left(word, shift);
            if (dictionary.count(candidate) > 0) {
                matches++;
                if (matches >= threshold) {
                    return shift;
                }
            }
        }
    }
    return shift;
}

string shift_left(const string word, const int shift)
/** Shift a word left */
{
    string candidate;
    for (size_t i = 0; i < word.length(); i++) {
        char c = word[i];
        if(c >= 'A' && c <= 'Z') {
            c -= shift;
            if(c < 'A')
               c = c + 'Z' - 'A' + 1;
            candidate += c;
        }
    }
    return candidate;
}

string shift_right(const string word, const int shift)
/** Shift a word left */
{
    string candidate;
    for (size_t i = 0; i < word.length(); i++) {
        char c = word[i];
        if(c >= 'A' && c <= 'Z') {
            c += shift;
            if(c > 'Z')
               c = c - 'Z' + 'A' - 1;
            candidate += c;
        }
    }
    return candidate;
}

vector<string> collect_words(vector<string> &words, 
                             Shifter func,
                             ostream &output,
                             const int shift)
/** Collect result */
{
    vector<string> collect;
    for (string &word: words) {
        string shifted = func(word, shift);
        collect.push_back(shifted);
        cout << shifted << " ";
    }
    return collect;
}

/* void output_words(vector<string> &words, ostream &output) */
/** Prints the words of a vec */
/*
{
    for (string &word: words)
        output << word << " ";
    output << "\n";
}
*/
