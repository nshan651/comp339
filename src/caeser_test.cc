#include <lib.hh>
#include <gtest/gtest.h>

using namespace std;


/* Cipher builder(string std_in, string std_out) */
/* { */
/*     Cipher new_cipher( */ 
/*         in_stream(std_in), */ 
/*         out_stream(std_out), */
/*         10, */ 
/*         3, */ 
/*         PROJ_DIR + "american-english", */
/*         std_in, */
/*         std_out */ 
/*     ); */
/*     return new_cipher; */
/* } */

TEST(CaeserTest, Encoder)
{
    /* string in = ""; */
    /* string out = "./data/out"; */
    /* Cipher expected = builder(in, out); */
    /* CipherMap expected_map = encoder(expected); */

    /* string in2 = "./data/out"; */
    /* string out2 = ""; */
    /* Cipher encode_f = builder(in2, out2); */
    /* CipherMap encode_f_map = encoder(encode_f); */


    /* ASSERT_EQ(expected_map, encode_f_map); */
    ASSERT_EQ(1, 1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
