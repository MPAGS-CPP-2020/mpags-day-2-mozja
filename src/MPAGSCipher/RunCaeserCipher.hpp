#ifndef MPAGSCIPHER_RUNCAESERCIPHER_HPP
#define MPAGSCIPHER_RUNCAESERCIPHER_HPP

#include <string>

// function to give same modulo result as in python
int pymod(int a, int b);

// Caeser Cipher Function
std::string runCaeserCipher( const std::string& inputText, const size_t key, const bool encrypt );

#endif // MPAGSCIPHER_RUNCAESERCIPHER_HPP