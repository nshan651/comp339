#include <main.hh>

using namespace std;

int main(int argc, char **argv)
{
    Cipher cipher;
    parse_args(cipher, argc, argv);

    cipher.input_file = PROJ_DIR + "decrypt.txt";
    /* cipher.input_file = PROJ_DIR + "encrypt.txt"; */

    cipher.encrypt = true; 

    map<string, int> dictionary = parse_dict(cipher.dict_file);
    cipher.min_len = 1;

    ifstream file(cipher.input_file);
    string line;
    if (!file.is_open()) {
        cerr << "Error opening file.";
        return 1;
    }
    
    while (getline(file, line)) {
        vector<string> words = split_line(line, cipher.min_len);
        int result;
        if (cipher.encrypt) {
             /* Seed rng */
             srand(time(0));
             int shift = rand() % 25 + 1;
             result = encode(words, shift);
        }
        else
            result = decode(words, dictionary);
        cout << "Shift Value: " << result << "\n";
    }
    return 0;
}
