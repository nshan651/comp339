#include <lib.hh>

using namespace std;

Cipher build_cipher(int argc, char **argv)
/** Collect CLI args and build a cipher struct*/
{
    int option;

    int num_lines = 10;
    int min_len = 3;
    string dict = PROJ_DIR + "american-english";
    string std_in = ""; 
    string std_out = ""; 

    while ((option = getopt(argc, argv, "n:l:d:i:o:h")) != -1) {
        switch (option) {
            case 'n':
                num_lines = atoi(optarg);
                cout << "Line number option selected.\n";
                break;
            case 'l':
                min_len = atoi(optarg);
                cout << "Length of min word option selected.\n";
                break;
            case 'd':
                dict = optarg;
                cout << "Dict option selected.\n";
                break;
            case 'i':
                std_in = optarg;
                cout << "Input option selected.\n";
                break;
            case 'o':
                std_out = optarg;
                cout << "Output option selected.\n";
                break;
            case 'h':
                cout << 
                    "=============\n"
                    "CAESER CIPHER\n"
                    "=============\n"
                    "Usage: \n\n"
                    "Arguments:"
                    "\n\t-n,|-lines number of lines of text to generate (default 10)"
                    "\n\t-l,|-length minimum word length (default 3)"
                    "\n\t-d,|-dict location of dictionary containing the word list" 
                    "\n\t-i,|-input filename input text from filename (if absent, write to standard output)"
                    "\n\t-o,|-output filename output text (of shift values) to filename (if absent, write to standard output)"
                    "\n\t-h,|-help pull up a list of options";
                exit(0);
            default: 
                cerr << "Unknown option. See -h for a list of options.";
                exit(1);
        }
    }
    
    /* Set IO */
    istream &input = in_stream(std_in);
    ostream &output = out_stream(std_out);
    /* Create a cipher struct */
    Cipher cipher(input, output, num_lines, min_len, dict, std_in, std_out);

    return cipher;
}

