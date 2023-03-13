#include <lib.hh>

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

map<string, int> parse_dict(string &dict)
/** Read and parse dictionary, excluding any non-Ascii letters */
{
    ifstream file(dict);
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
