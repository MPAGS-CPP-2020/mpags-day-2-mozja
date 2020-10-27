// Standard Library includes
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// For std::isalpha and std::isupper
#include <cctype>

// Our project headers
#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"

// Main function of the mpags-cipher program
int main(int argc, char* argv[])
{
  // Convert the command-line arguments into a more easily usable form
  const std::vector<std::string> cmdLineArgs {argv, argv+argc};

  // Options that might be set by the command-line arguments
  bool helpRequested {false};
  bool versionRequested {false};
  std::string inputFile {""};
  std::string outputFile {""};

  // Process the command line arguments
  processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile);

  // Handle help, if requested
  if (helpRequested) {
    // Line splitting for readability
    std::cout
      << "Usage: mpags-cipher [-i <file>] [-o <file>]\n\n"
      << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      << "Available options:\n\n"
      << "  -h|--help        Print this help message and exit\n\n"
      << "  --version        Print version information\n\n"
      << "  -i FILE          Read text to be processed from FILE\n"
      << "                   Stdin will be used if not supplied\n\n"
      << "  -o FILE          Write processed text to FILE\n"
      << "                   Stdout will be used if not supplied\n\n";
    // Help requires no further action, so return from main
    // with 0 used to indicate success
    return 0;
  }

  // Handle version, if requested
  // Like help, requires no further action,
  // so return from main with zero to indicate success
  if (versionRequested) {
    std::cout << "0.1.0" << std::endl;
    return 0;
  }

  // Initialise variables for processing input text
  char inputChar {'x'};
  std::string inputText {""};

  // Read in user input from stdin/file
  // Warn that input file option not yet implemented
  if (!inputFile.empty()) {

    std::ifstream in_file{inputFile};
    bool okay_to_read = in_file.good();

    if (okay_to_read){
      while(in_file >> inputChar){
        inputText += transformChar(inputChar);
      }
    }
    else {
      std::cout << "[warning] input file ('"
              << inputFile
              << "') could not be opened\n";
      return 1;
    }
  }
  else {
        // Loop over each character from user input
    // (until Return then CTRL-D (EOF) pressed)
    std::cout << "[warning] no input file given, using cin. Press CTRL-D to run after entering input.\n" << std::endl;
    while(std::cin >> inputChar)
    { 
      inputText += transformChar( inputChar );
    }
  }



  // Output the transliterated text
  // Warn that output file option not yet implemented
  if (!outputFile.empty()) {
    std::ofstream out_file {outputFile};
    bool okay_to_write = out_file.good();

    if (okay_to_write){
      out_file << inputText;
    }
    else
    {
      std::cout << "[warning] output file ('"
              << outputFile
              << "') could not be opened\n";
      return 1;
    }
  }
  else
  {
    std::cout << "[warning] no output file given, using stdout\n" << std::endl;
    std::cout << inputText << std::endl;
  }

  // No requirement to return from main, but we do so for clarity
  // and for consistency with other functions
  return 0;
}