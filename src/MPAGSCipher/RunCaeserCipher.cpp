#include "RunCaeserCipher.hpp"

// function to give same modulo result as in python
int pymod(int a, int b) { return ((a % b) + b) % b; }

// Caeser Cipher Function
std::string runCaeserCipher( const std::string& inputText, const size_t key, const bool encrypt)
{

  // Create the alphabet container and output string
  const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
  std::string crypted {""};

  // Loop over the input text
  for(const char& c : inputText) {
    if (encrypt){
      int alph_pos = pymod((alphabet.find(c) + key),alphabet.length());
      crypted += alphabet[alph_pos];
    }
    else {
      int alph_pos = pymod((alphabet.find(c) - key),alphabet.length());
      crypted += alphabet[alph_pos];
      }
  }
  return crypted;
}