#include <lib.hh>

using namespace std;

istream &in_stream(string &input)
{
    if (input == "")
        return cin;

    static ifstream file;
    file.open(input);

    if (!file.is_open()) {
        cerr << "Error opening file.";
        static stringstream error_stream;
        error_stream.setstate(ios_base::failbit);
        return error_stream;
    }
    return file;
}

ostream &out_stream(string &output)
{
    if (output == "")
        return cout;

    static ofstream file;
    file.open(output);

    if (!file.is_open()) {
        cerr << "Error opening file.";
        static stringstream error_stream;
        error_stream.setstate(ios_base::failbit);
        return error_stream;
    }
    return file;
}
