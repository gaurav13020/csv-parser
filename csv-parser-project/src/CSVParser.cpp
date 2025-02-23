#include "CSVParser.h"

// Implementation of common functionality for the CSVParser class

CSVParser::CSVParser(const std::string& filename) : filename(filename) {}

std::string CSVParser::getFilename() const {
    return filename;
}

// You can add shared utility functions here if needed.