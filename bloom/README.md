# Bloom Filter

## Compiling

- For now, run this:
    - `g++ -o bloom_filter bloom.cc -lcrypto`
    - Adds `libcrypto` library to linker

## Notes

- Optimal hash functions:
    - $k = (\frac{m}{n})*ln(2)$
    - $m = \frac{(-n * ln(p))}{(ln(2)^2)}$
