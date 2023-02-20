#include <main.hh>

using namespace std;

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

    int num_lines = 10;
    int words_per_line = 5;
    parse_args(cipher, argc, argv);

    ofstream file("./data/test.txt");
    if (!file.is_open()) {
      cerr << "Failed to open file";
      return 1;
    }

    if (file.is_open()) {
      map<string, int> dictionary = parse_dict(cipher.dict_file);
      /* vector<vector<string>> values; */

      for (int i = 0; i < num_lines; i++) {
        /* vector<string> new_line; // To add to values */
        string new_line;
        for (int j = 0; j < words_per_line; j++) {
          // Create a random_device to generate a random seed
          random_device rd;
          // Use the seed to create a Mersenne Twister engine
          mt19937 eng(rd());
          // Generate a random integer between 1 and dict size inclusive
          uniform_int_distribution<> dist(1, dictionary.size()-1);

          int random_index = dist(eng);

          auto iter = dictionary.begin();
          advance(iter, random_index);
          new_line = iter->first;
          file << new_line << " ";
        }
        file << "\n";
      }
    }

    /*
    if (!file.is_open()) {
        cerr << "Error opening file.";
        return 1;
    }
    
    while (getline(file, line)) {
        vector<string> words = split_line(line, cipher.min_len);
        srand(time(0));
        int shift = rand() % 26;
        int result = encode(words, shift);
    }
    */

    return 0;
}
