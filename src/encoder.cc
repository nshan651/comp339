#include <main.hh>

using namespace std;

int encoder(vector<string> &words, int shift)
/**
The encoder does the following:
    - Loads the dictionary into a data structure (map/set). As words are loaded in, any words containing characters not in the alphabet will be discarded.
    - Words are all converted to upper case.
    - Generates ”sentences”. You may generate sentences with whitespace or punctuation. Just keep in mind that the decoder must be able to exclude any text not in the input alphabet.
    - Each line of text must be encrypted using the Caesar cipher with a randomly chosen shift key. No information about the key is written to the output.
    -The output lines may either be directed to standard output or to a file.
*/
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
        //cout << candidate << "\n";
    }
    return shift;
}
