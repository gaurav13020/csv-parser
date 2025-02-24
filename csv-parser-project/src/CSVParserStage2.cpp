// #include "CSVParserStage2.h"
// #include <iostream>
// #include <fstream>
// #include <sstream>

// CSVParserStage2::CSVParserStage2(const std::string& filename) : CSVParser(filename) {}

// void CSVParserStage2::loadCSV() {
//     std::ifstream file(filename);
//     if (!file.is_open()) {
//         std::cerr << "Error opening file: " << filename << std::endl;
//         return;
//     }

//     std::string line;
//     while (std::getline(file, line)) {
//         parseRecord(line);
//     }
//     file.close();
// }

// void CSVParserStage2::parseRecord(const std::string& line) {
//     std::istringstream ss(line);
//     std::string field;

//     // Example parsing logic for stage 2
//     CrashRecord record;
//     std::getline(ss, field, ','); // Assuming first field is latitude
//     record.setLatitude(std::stod(field));
//     std::getline(ss, field, ','); // Assuming second field is longitude
//     record.setLongitude(std::stod(field));
//     std::getline(ss, field, ','); // Assuming third field is crash date/time
//     record.setCrashDateTime(field);

//     records.push_back(record);
// }