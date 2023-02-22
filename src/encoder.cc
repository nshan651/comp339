#include <main.hh>

using namespace std;

/* void gen_text(const Cipher &cipher, ostream &output) */
CipherIter gen_text(const Cipher &cipher)
/** Return an iterator of generated text. */
{
    // TODO: parameterize this
    int words_per_line = 5;

    map<string, int> dictionary = parse_dict(cipher);
    CipherIter plaintext;
    for (int i = 0; i < cipher.num_lines; i++) {
        vector<string> line;
        for (int j = 0; j < words_per_line; j++) {
            int rand_index = rng(1, dictionary.size()-1);
            auto iter = dictionary.begin();
            advance(iter, rand_index);
            line.push_back(iter->first);
        }
        plaintext.push_back(line);
    }
    return plaintext;
}

/* CipherIter read_text(Cipher cipher, istream &input) */
CipherIter read_text(Cipher cipher)
/** Return an iterator of text read from stdin */
{
    vector<vector<string>> lines;
    string line;
    while (getline(cipher.input, line)) 
        lines.push_back(split_line(line, cipher.min_len));
    return lines;
}

/* CipherMap encoder(const Cipher &cipher, istream &input, ostream &output) */
CipherMap encoder(const Cipher &cipher)
{
    /* CipherIter iter; */
    /* if (cipher.std_in) */ 
    /*     iter = gen_text(cipher); */
    /* else */ 
    /*     iter = read_text(cipher); */

    /* Iterater over input */
    CipherIter iter = (cipher.std_in == "") ? gen_text(cipher) 
                                        : read_text(cipher);
    
    /* Populate mapping */
    CipherMap encoded;
    for_each(iter.begin(), iter.end(), [&](auto &words) {
        int shift = rng(1, ALPHABET_SIZE);
        /* Output header if output is cout */
        if (cipher.std_out == "")
            cipher.output << "\nSHIFT => " << shift << " WORDS => ";
        vector<string> encode_line = collect_words(words, 
                                        shift_right,
                                        cipher.output,
                                        shift);
        encoded[encode_line] = shift;
    });
    return encoded;
}

int main(int argc, char **argv)
/**
The encoder does the following:
    - Loads the dictionary into a data structure (map/set). As words are loaded in, any words containing characters not in the alphabet will be discarded.
    - Words are all converted to upper case.
    - Generates ”sentences”. You may generate sentences with whitespace or punctuation. Just keep in mind that the decoder must be able to exclude any text not in the input alphabet.
    - Each line of text must be encrypted using the Caesar cipher with a randomly chosen shift key. No information about the key is written to the output.
    -The output lines may either be directed to standard output or to a file.
*/
{
    Cipher cipher(cin, cout);

    /* Parse CLI */
    int option = parse_args(cipher, argc, argv);
    if (option == 0 || option == 1) exit(option);

    /* Handle IO */
    /* istream &input = in_stream(cipher.input); */
    /* ostream &output = out_stream(cipher.output); */

    CipherMap cmap = encoder(cipher);

    return 0;
}
