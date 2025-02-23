#include "CSVParserStage1.h"
#include <iostream>
#include <fstream>
#include <sstream>

CSVParserStage1::CSVParserStage1(const std::string& filename) : CSVParser(filename) {}

void CSVParserStage1::loadCSV() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        parseRecord(line);
    }
    file.close();
}

void CSVParserStage1::parseRecord(const std::string& line) {
    std::istringstream ss(line);
    std::string token;

    // Example parsing logic for stage 1
    CrashRecord record;
    std::getline(ss, token, ','); // Assuming first column is latitude
    record.setLatitude(std::stod(token));
    std::getline(ss, token, ','); // Assuming second column is longitude
    record.setLongitude(std::stod(token));
    std::getline(ss, token, ','); // Assuming third column is datetime
    record.setCrashDateTime(token);

    records.push_back(record);
}