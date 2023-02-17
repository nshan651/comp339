#include <main.hh>

using namespace std;

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

map<string, int> parse_dict(const string &filename)
/** Read and parse dictionary, excluding any non-Ascii letters */
{
    ifstream file(filename);
    string line;
    map<string, int> words;

    int counter = 0;
    while (file >> line) {
        string alpha = convert_alpha(line);
        if (!alpha.empty())
            words[alpha] = counter;
            counter++;
    }
    return words;
}

int encode(vector<string> &words, int shift)
/** Encodes a single line using a given shift value **/
{
    for (string &word : words) {
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
    }
    return shift;
}

int decode(vector<string> &words, map<string, int> &dictionary)
/** Decodes a single line using a word dictionary */
{
    int threshold = words.size();
    int shift = 0;

    for (shift = 1; shift <= ALPHABET_SIZE; shift++) {
        int matches = 0;
        for (string &word : words) {
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
            if (dictionary.count(candidate) > 0) {
                matches++;
                //cout << candidate << "\n";
                if (matches >= threshold)
                    return shift;
            }
        }
    }
    return shift;
}
