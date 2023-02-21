#include <main.hh>
#include <gtest/gtest.h>

using namespace std;

TEST(CaeserTest, Encoder)
{
    /*
    ifstream file_in("./data/plaintext.txt");
    if (!file_in.is_open()) {
        cerr << "Error opening file.";
        return 1;
    }
    while (getline(input, line)) {
    }
    */

    ASSERT_EQ(1, 1);
}

int main(int argc, char **argv)
{
    /*
    ofstream file_out("./data/plaintext.txt");
    if (!file_out.is_open()) {
      cerr << "Failed to open file";
      return 1;
    }

    ifstream file_in("./data/plaintext.txt");
    if (!file_in.is_open()) {
        cerr << "Error opening file.";
        return 1;
    }
    */

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
