#include <iostream>
#include <map>     // Map<K,V> interface, HashMap<K,V> and TreeMap<K,V>
#include <ostream> // <- java.io
#include <set>     // Set<T> interface, HashSet<T>
#include <vector>  // <- List interface, ArrayList<T>

using namespace std; // Better practice to keep local not global
int main(int argc, char **argv) {
  // Dictionary? I am confused about this part of the assignment
  set<string> dictionary = {"DEBUG", "THIS", "A", "IS"};

  string decipher = "Estd td l opmfr."; // Default
  if (argc > 1) {
    decipher = argv[1];
  }
  // Forces all chars to be uppercase
  for (int i = 0; i < decipher.length(); i++) {
    if (decipher[i] >= 'a' && decipher[i] <= 'z') {
      decipher[i] -= 32;
    }
  }

  int key = 0;
  bool isCracked = false;
  string res = decipher;
  cout << "Input: " << decipher << endl;
  // Iterate through each key until cipher cracked
  while (key <= 26 && !isCracked) {
    key += 1;
    res = decipher;
    set<string> words = {}; // Holds found possible words
    int marker = -1;        // Marks start of possible word

    // Apply cipher to each letter
    for (int i = 0; i < res.length(); i++) {
      char ptr = res[i];
      // Verifies is in alphabet
      if (ptr >= 'A' && ptr <= 'Z') {
        ptr += key;
        // Loops back to start of alphabet if overextends
        if (ptr > 'Z') {
          ptr -= 26;
        }
        if (marker == -1) {
          // Sets index marker if found start of word
          marker = i;
        }

      } else if (marker != -1) { // Possible word found
        string foundWord = "";
        for (int j = marker; j < i; j++) {
          foundWord += res[j];
        }
        words.insert(foundWord);
        marker = -1;
      }
      res[i] = ptr;
    }
    cout << "Key #" << key << ": " << res << endl;
    // Checks if all words found are real- if so, cipher cracked
    isCracked = true;
    for (const auto w : words) {
      if (dictionary.find(w) == dictionary.end()) {
        isCracked = false;
        break;
      }
    }
  }

  if (isCracked) {
    cout << "Cracked \"" << res << "\" with Key #" << key << endl;
  } else {
    cout << "Unable to verify if cracked. Check dictionary?" << endl;
  }

  return 0;
}