#include <main.hh>

using namespace std;

 void gen_text(Cipher cipher, ostream &output)
 /** Generate cipher text */
 {
     int words_per_line = 5;

     map<string, int> dictionary = parse_dict(cipher.dict);

     for (int i = 0; i < cipher.num_lines; i++) {
       int rand_shift = rng(1, ALPHABET_SIZE);

       for (int j = 0; j < words_per_line; j++) {
         int rand_index = rng(1, dictionary.size()-1);
         auto iter = dictionary.begin();
         advance(iter, rand_index);
         string new_line = iter->first;

         string encoded = shift_right(new_line, rand_shift);
         output << encoded << " ";
       }
       output << "\n";
     }
 }

void encoder(Cipher cipher, istream &input, ostream &output)
{
    /* If the input is empty (default) generate random text */
    if (cipher.input == "") {
        cout << "GEN";
        gen_text(cipher, output);
    }
    /* Otherwise, encode the std input */
    else {
        string line;
        while (input >> line) {
            int rand_shift = rng(1, ALPHABET_SIZE);
            vector<string> words = split_line(line, cipher.min_len);
            vector<string> encoded = encode(words, rand_shift);
            vector<string> collect = collect_words(encoded, shift_right, rand_shift);
        }
    }
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
    Cipher cipher;

    /* Parse CLI */
    int option = parse_args(cipher, argc, argv);
    if (option == 0 || option == 1) exit(option);

    /* Handle IO */
    istream &input = in_stream(cipher.input);
    ostream &output = out_stream(cipher.output);

    encoder(cipher, input, output);

    return 0;
}
