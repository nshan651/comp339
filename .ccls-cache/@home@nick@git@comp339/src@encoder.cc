#include <main.hh>

using namespace std;

 int gen_text(Cipher cipher, ostream& output)
 /** Generate cipher text */
 {
     int words_per_line = 5;

     map<string, int> dictionary = parse_dict(cipher.dict_file);

     for (int i = 0; i < cipher.num_lines; i++) {
       int rand_shift = rng(1, 26);

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
     return 0;
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

    // NOTE: Hard-coded, remove later!!!
    cipher.min_len = 1;
    cipher.num_lines = 10;
    /* cipher.output_file = "./data/ciphertext.txt"; */

    parse_args(cipher, argc, argv);

    if (cipher.output_file == "") {
        gen_text(cipher, cout);
        return 0;
    }

    ofstream file(cipher.output_file);
    if (!file.is_open()) {
      cerr << "Failed to open file";
      return 1;
    }
    gen_text(cipher, file);
    file.close();


    return 0;
}
