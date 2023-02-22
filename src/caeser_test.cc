#include <lib.hh>
#include <gtest/gtest.h>

using namespace std;

/* Cipher gen_cipher(const string &input, const string &output) */
/** Generator function for a new Cipher instance */
/* { */
/*     Cipher gc; */
/*     gc.input = input; */
/*     gc.output = output; */
/*     return gc; */
/* } */

TEST(CaeserTest, Encoder)
{
    /* Cipher plaintext = gen_cipher("./data/plaintext.txt", */
    /*                               "./data/pipe"); */

    /* Handle IO */
    /* istream &input = in_stream(cipher.input); */
    /* ostream &output = out_stream(cipher.output); */

    /* CipherMap cmap = encoder(cipher, input, output); */

    ASSERT_EQ(1, 1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
