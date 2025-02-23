#include "CSVParserStage3.h"
#include <iostream>
#include <fstream>
#include <sstream>

CSVParserStage3::CSVParserStage3(const std::string& filename) : CSVParser(filename) {}

void CSVParserStage3::loadCSV() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        parseRecord(line);
    }
    file.close();
}

void CSVParserStage3::parseRecord(const std::string& line) {
    std::istringstream ss(line);
    std::string token;

    // Example parsing logic for stage 3
    CrashRecord record;
    std::getline(ss, token, ',');
    record.setLatitude(std::stod(token));
    std::getline(ss, token, ',');
    record.setLongitude(std::stod(token));
    std::getline(ss, token, ',');
    record.setCrashDateTime(token);

    records.push_back(record);
}