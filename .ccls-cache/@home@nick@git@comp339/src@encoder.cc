#include <main.hh>

using namespace std;

int main()
/**
The encoder does the following:
    - Loads the dictionary into a data structure (map/set). As words are loaded in, any words containing characters not in the alphabet will be discarded.
    - Words are all converted to upper case.
    - Generates ”sentences”. You may generate sentences with whitespace or punctuation. Just keep in mind that the decoder must be able to exclude any text not in the input alphabet.
    - Each line of text must be encrypted using the Caesar cipher with a randomly chosen shift key. No information about the key is written to the output.
    -The output lines may either be directed to standard output or to a file.
*/
{
    Cipher cipher;

    // NOTE: Hard-coded, remove later!!!
    cipher.min_len = 1;

    parse_args(cipher, argc, argv);

    ifstream file(cipher.input_file);
    string line;
    if (!file.is_open()) {
        cerr << "Error opening file.";
        return 1;
    }
    
    while (getline(file, line)) {
        vector<string> words = split_line(line, cipher.min_len);
        /* Seed rng */
        srand(time(0));
        int shift = rand() % 25 + 1;
        int result = encode(words, shift);
        cout << "Shift Value: " << result << "\n";
    }

    return 0;
}
