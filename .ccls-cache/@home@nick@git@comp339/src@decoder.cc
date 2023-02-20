#include <main.hh>

using namespace std;

int decode_lines(Cipher cipher, istream& input)
{
    map<string, int> dictionary = parse_dict(cipher.dict_file);
    string line;
    while (getline(input, line)) {
        vector<string> words = split_line(line, cipher.min_len);
        int shift = decode(words, dictionary);
        /* cout << shift << "\n"; */
        handle_io(shift_left, words, shift);
    }
    return 0;
}

int main(int argc, char **argv)
/** 
name output text (of shift values) to filename (if absent, write to standard output)
The decoder does the following:
    - Reads one line of input at a time.
    - Parses the line of input into words. A word is any continuous sequence of letters from the alphabet.
    - Characters not in a word should be preserved to the fullest extent possible (e.g. whitespace and any punctuation.)
    - Try all shift values with your Caesar cipher to see if all words in a line of input can be decoded. You will know if they can be decoded by looking up the words in the dictionary. Thus the decoder must be able to load the dictionary as well.
    - Output the shift value on success. If for any reason an input line cannot be decoded, output a -1. This would never happen if your encoder and decoder are both working, but it is entirely possible a file generated by someone else could present problems.
    - You can also write the decoder to succeed if most of the words are decoded. This could be an additional command line option, e.g. --threshold=percentage.
*/
{
    Cipher cipher;

    // NOTE: Hard-coded, remove later!!!
    cipher.min_len = 1;

    parse_args(cipher, argc, argv);

    /* cipher.input_file = "./data/ciphertext.txt"; */


    if (cipher.input_file == "") {
        decode_lines(cipher, cin);
        return 0;
    }

    ifstream file(cipher.input_file);
    if (!file.is_open()) {
        cerr << "Error opening file.";
        return 1;
    }
    decode_lines(cipher, file);
    file.close();

    return 0;
}
