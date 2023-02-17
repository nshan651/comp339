#include <main.hh>

using namespace std;

void gen_test(const string &filename, int num_lines, int words_per_line)
{
  /**
    Words per line,
    Number of lines,
    Random shift per each line,
  */
  srand(time(0));  // seed the random number generator

  ofstream file(filename);
  if (!file.is_open()) {
    cerr << "Failed to open file";
    //return 1;
  }
  
  map<string, int> dictionary = parse_dict(filename);
  vector<vector<string>> values;

  for (int i = 0; i < num_lines; i++) {
    vector<string> new_line; // To add to values
    for (int j = 0; j < words_per_line; j++) {
      srand(time(0));  // seed the random number generator
      int random_index = rand() % dictionary.size();
      auto iter = dictionary.begin();
      advance(iter, random_index);
      new_line.push_back(iter->first);
      /* new_line.push_back(dictionary[random_index]); */  
    }
    values.push_back(new_line);
  }
}

int test() 
{
  string dict_file = PROJ_DIR + "american-english";
  string test_file = PROJ_DIR + "test.txt";
  int num_lines = 10;
  int words_per_line = 5;
  gen_test(test_file, num_lines, words_per_line);

  /* run cipher.cc's main with test_file
  i'm not sure exactly how we do this but I did find this:
  https://stackoverflow.com/questions/38560971/how-to-call-main-from-other-functions-in-c
  If you know something simpler tho lmk, like printing to terminal from our code
    ./cipher -e -i test_file -o encrypt_t.txt
    ./cipher -d -i encrypt_t.txt -o decrypt_t.txt
  check if test.txt and decrypt_test.txt are equal*/

  string decrypt_file = PROJ_DIR + "decrypt_t.txt";

  // I am not used to file stuff, so if this looks weird you can mess with it
  /* Compare the contents of test.txt and decrypt_t.txt to test whether the encryption and decryption worked or not. */
  fstream testFile(test_file), resFile(decrypt_file);
  char testLine[256], resLine[256];
  int count = 0;
  int hit = 0;
  int miss = 0;
  while(!testFile.eof() && !resFile.eof()) {
    count += 1;
    testFile.getline(testLine, 256);
    resFile.getline(resLine, 256);
    if (strcmp(testLine, resLine) != 0) {
      miss += 1;
      cout << "line #" << count << " mismatch\n";
      cout << test_file << ": " << testLine << "\n";
      cout << decrypt_file << ": " << resLine << "\n";
    } else {
      hit += 1;
    }
  }
  cout << "total lines read: " << count << "\n";
  cout << "total hits: " << hit << "\n";
  cout << "total misses: " << miss << "\n";
  return 0;
}
