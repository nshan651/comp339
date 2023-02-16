#include <main.hh>

using namespace std;

int main(int argc, char **argv)
{
    int option;
    Cipher cipher;

    while ((option = getopt(argc, argv, "edn:l:x:i:o:h")) != -1) {
        switch (option) {
            case 'e':
                cout << "Encrypt selected.";
                cipher.encrypt = true; 
                break;
            case 'd':
                cout << "Decrypt selected";
                cipher.encrypt = false; 
                break;
            case 'n':
                cipher.num_lines = atoi(optarg);
                cout << "Line number option selected.";
                break;
            case 'l':
                cipher.min_len = atoi(optarg);
                cout << "Length of min word option selected.";
                break;
            case 'x':
                cipher.dict_file = optarg;
                cout << "Dict option selected.";
                break;
            case 'i':
                cipher.input_file = optarg;
                cout << "Input option selected.";
                break;
            case 'o':
                cipher.output_file = optarg;
                cout << "Output option selected.";
                break;
            case 'h':
                cout << 
                    "=============\n"
                    "CAESER CIPHER\n"
                    "=============\n"
                    "Usage: \n\n"
                    "Arguments:"
                    "\n\t-e,|-encrypt encode the file"
                    "\n\t-d,|-decrypt decode the file"
                    "\n\t-n,|-lines number of lines of text to generate"
                    "\n\t-l,|-length minimum word length (default 3)"
                    "\n\t-x,|-dict location of dictionary containing the word list" 
                    "\n\t-i,|-input filename input text from filename (if absent, write to standard output)"
                    "\n\t-o,|-output filename output text (of shift values) to filename (if absent, write to standard output)"
                    "\n\t-h,|-help pull up a list of options";
                return 0;
            default: 
                cerr << "Unknown option. See -h for a list of options.";
                return 1;
        }
    }

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
             srand(time(0));  // seed the random number generator
             int shift = rand() % 25 + 1;
             result = encoder(words, shift);
        }
        else
            result = decoder(words, dictionary);
        cout << "Shift Value: " << result << "\n";
    }
    return 0;
}