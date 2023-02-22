#include <lib.hh>
#include <gtest/gtest.h>

using namespace std;

TEST(CaeserTest, Encoder)
{
    Cipher cipher;

    cipher.input = "./data/plaintext.txt";
    cipher.output = "./data/pipe";
    /* Handle IO */
    istream &input = in_stream(cipher.input);
    ostream &output = out_stream(cipher.output);

    /* encoder(cipher, input, output); */

    ASSERT_EQ(1, 1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
