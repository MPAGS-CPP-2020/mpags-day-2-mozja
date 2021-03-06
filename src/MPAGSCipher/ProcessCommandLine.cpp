#include "ProcessCommandLine.hpp"

// process the command line arguments
bool processCommandLine(
  const std::vector<std::string>& cmdLineArgs,
  bool& helpRequested,
  bool& versionRequested,
  std::string& inputFile,
  std::string& outputFile,
  size_t& key,
  bool& encrypt) 
{
  // Add a typedef that assigns another name for the given type for clarity
  typedef std::vector<std::string>::size_type size_type;
  const size_type nCmdLineArgs {cmdLineArgs.size()};

  // Process command line arguments - ignore zeroth element, as we know this to
  // be the program name and don't need to worry about it
  for (size_type i {1}; i < nCmdLineArgs; ++i) {

    if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
      helpRequested = true;
    }
    else if (cmdLineArgs[i] == "--version") {
      versionRequested = true;
    }
    else if (cmdLineArgs[i] == "-i") {
      // Handle input file option
      // Next element is filename unless -i is the last argument
      if (i == nCmdLineArgs-1) {
	      std::cerr << "[error] -i requires a filename argument" << std::endl;
	      // exit main with non-zero return to indicate failure
	      return 1;
      }
      else {
	      // Got filename, so assign value and advance past it
	      inputFile = cmdLineArgs[i+1];
	      ++i;
      }
    }
    else if (cmdLineArgs[i] == "-o") {
      // Handle output file option
      // Next element is filename unless -o is the last argument
      if (i == nCmdLineArgs-1) {
	      std::cerr << "[error] -o requires a filename argument" << std::endl;
	      // exit main with non-zero return to indicate failure
	      return 1;
      }
      else {
	      // Got filename, so assign value and advance past it
	      outputFile = cmdLineArgs[i+1];
	      ++i;
      }
    }
    else if (cmdLineArgs[i] == "-k") {
      // Handle key option
      if (i == nCmdLineArgs - 1) {
        // No key after -k, give error
        std::cout << "[error] -k requires a key argument" << std::endl;
        return 1;
      }
      else {
        // Key provided, advance
        key = std::stol(cmdLineArgs[i+1]);
        ++i;
      }
    }
    else if (cmdLineArgs[i] == "--encrypt"){
      encrypt = true;
    }
    else if (cmdLineArgs[i] == "--decrypt"){
      encrypt = false;
    }
    else {
      // Have an unknown flag to output error message and return non-zero
      // exit status to indicate failure
      std::cerr << "[error] unknown argument '" << cmdLineArgs[i] << "'\n";
      return 1;
    }
  }
return 0;
}