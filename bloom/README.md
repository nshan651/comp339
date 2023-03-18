# Bloom Filter

## Compiling

- For now, run this:
    - `g++ -o bloom_filter bloom.cc -lcrypto`
    - Adds `libcrypto` library to linker

## Notes

- Optimal hash functions:
    - $k = (\frac{m}{n})*ln(2)$
    - $m = \frac{(-n * ln(p))}{(ln(2)^2)}$

### Available Hash Functions

- Here are all the hash functions available in openssl:
    - MD2
    - MD4
    - MD5
    - SHA-1
    - SHA-224
    - SHA-256
    - SHA-384
    - SHA-512
    - SHA-512/224
    - SHA-512/256
    - SHA3-224
    - SHA3-256
    - SHA3-384
    - SHA3-512
    - BLAKE2b-512
    - BLAKE2s-256
