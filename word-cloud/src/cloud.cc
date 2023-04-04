#include <cloud.hh>
#include <bloom.hh>
#include <hash.hh>
#include <CLI/CLI.hpp>
#include <queue>
#include <unordered_map>

using namespace std;

#ifdef CLOUD
int main(int argc, char* argv[])
{

    /* spdlog::set_level(spdlog::level::debug); */
    spdlog::set_level(spdlog::level::info);

    int m;
    int k;
    string input; 
    string search_query;

    CLI::App app("BloomFilter CLI");
    app.add_option("-m", m, "Number of bits")->default_val(100);
    app.add_option("-k", k, "Number of hash functions")->default_val(2);
    app.add_option("-i", input, "Input method")->default_val("./data/american-english");
    app.add_option("-s", search_query, "Comma-separated list of search terms")->default_val("");
    // TODO: Add option for list of hash functions
    CLI11_PARSE(app, argc, argv);

    // Init bloom filter 
    bloom(m, k, search_query, input);

    return 0;
}
#endif
