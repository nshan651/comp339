#include <lib.hh>
#include <gtest/gtest.h>

using namespace std;


Cipher builder(string std_in, string std_out)
{
    Cipher new_cipher( 
        in_stream(std_in), 
        out_stream(std_out),
        10, 
        3, 
        PROJ_DIR + "american-english",
        std_in,
        std_out 
    );
    return new_cipher;
}

TEST(CaeserTest, Full)
{
    string in = "";
    string out = "./data/plaintext";
    Cipher expected( 
        in_stream(in), 
        out_stream(out),
        10, 
        3, 
        PROJ_DIR + "american-english",
        in,
        out 
    );
    CipherIter iter = gen_text(expected);
    CipherMap encoded = encoder(expected, iter);

    string in2 = "./data/plaintext";
    string out2 = "";
    Cipher decode_test( 
        in_stream(in2), 
        out_stream(out2),
        10, 
        3, 
        PROJ_DIR + "american-english",
        in,
        out 
    );

    CipherMap decoded = decoder(decode_test);

    cout << "DECODED: " << decoded;

    /* ASSERT_EQ(expected, decoded); */
}

/*
TEST(CaeserTest, Encoder)
{
    string in = "";
    string out = "./data/out";
    Cipher expected( 
        in_stream(in), 
        out_stream(out),
        10, 
        3, 
        PROJ_DIR + "american-english",
        in,
        out 
    );
    CipherMap expected_map = encoder(expected);

    string in2 = "./data/out";
    string out2 = "";
    Cipher encode_f( 
        in_stream(in), 
        out_stream(out),
        10, 
        3, 
        PROJ_DIR + "american-english",
        in,
        out 
    );
    CipherMap encode_f_map = encoder(encode_f);

    ASSERT_EQ(expected_map, encode_f_map);
}
*/
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
