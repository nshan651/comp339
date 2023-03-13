#include <lib.hh>

using namespace std;

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

CipherIter read_text(const Cipher &cipher)
/** Return an iterator of text read from stdin */
{
    CipherIter lines;
    string nline;

    while (getline(cipher.input, nline)) {
        if (nline == "")
            continue;
        string line = strip_metadata(nline);
        lines.push_back(split_line(nline, cipher.min_len));
    }
    return lines;
}

CipherMap encoder(const Cipher &cipher, CipherIter &iter)
{
    /* Populate mapping */
    CipherMap encoded;
    for_each(iter.begin(), iter.end(), [&](auto &words) {
        int shift = rng(1, ALPHABET_SIZE);
        /* Output header if output is cout */
        if (cipher.std_out == "")
            cout << "SHIFT => " << shift << " WORDS => ";
        vector<string> collect = collect_words(words, 
                                        shift_right,
                                        cipher.output,
                                        shift);
        cipher.output << "\n";
        encoded[collect] = shift;
    });
    return encoded;
}

#ifdef ENCODER
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
    /* Create a cipher based on CLI */
    Cipher cipher = build_cipher(argc, argv);

    /* Iterater over input */
    CipherIter iter = (cipher.std_in == "") ? gen_text(cipher) 
                                        : read_text(cipher);
    /* Create a cipher mapping */
    CipherMap cmap = encoder(cipher, iter);

    return 0;
}
#endif
