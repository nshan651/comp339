#include <main.hh>

using namespace std;

int parse_args(Cipher &cipher, int argc, char **argv)
/** Collect CLI args */
{
    int option;

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
    return option;
}
