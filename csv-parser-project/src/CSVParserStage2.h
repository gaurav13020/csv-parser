#ifndef CSVPARSERSTAGE2_H
#define CSVPARSERSTAGE2_H

#include "CSVParser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <omp.h>

class CSVParserStage2 : public CSVParser {
private:
    std::vector<RawRecord> records;

    // Helper function to convert date and time to epoch
    long convertToEpoch(const std::string& datetime) {
        std::tm tm = {};
        std::istringstream ss(datetime);
        ss >> std::get_time(&tm, "%m/%d/%Y %H:%M");
        if (ss.fail()) {
            throw std::runtime_error("Failed to parse date time: " + datetime);
        }
        return std::mktime(&tm);
    }

    // Helper function to calculate distance between two lat/lon points
    double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
        const double R = 6371000; // Radius of the Earth in meters
        double dLat = (lat2 - lat1) * M_PI / 180.0;
        double dLon = (lon2 - lon1) * M_PI / 180.0;
        double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
                   std::cos(lat1 * M_PI / 180.0) * std::cos(lat2 * M_PI / 180.0) *
                   std::sin(dLon / 2) * std::sin(dLon / 2);
        double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
        return R * c;
    }

    // Helper function to split a CSV line into fields, considering quoted fields
    std::vector<std::string> parseCSVLine(const std::string& line) {
        std::vector<std::string> fields;
        std::istringstream ss(line);
        std::string field;
        bool inQuotes = false;
        char prevChar = '\0';

        while (ss.good()) {
            char c = ss.get();
            if (c == '"' && prevChar != '\\') {
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                fields.push_back(field);
                field.clear();
            } else {
                field += c;
            }
            prevChar = c;
        }
        fields.push_back(field); // Add the last field
        return fields;
    }

public:
    void load(const std::string& filename) override {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        std::getline(file, line); // Skip header line

        while (std::getline(file, line)) {
            std::vector<std::string> fields = parseCSVLine(line);

            try {
                long collision_id = 0;
                try {
                    collision_id = fields.size() > 23 && !fields[23].empty() ? std::stol(fields[23]) : 0;
                } catch (const std::exception& e) {
                    std::cerr << "Error parsing collision_id: " << fields[23] << " - " << e.what() << std::endl;
                }

                RawRecord record(
                    fields.size() > 0 ? fields[0] : "",
                    fields.size() > 1 ? fields[1] : "",
                    fields.size() > 2 ? fields[2] : "",
                    fields.size() > 3 ? fields[3] : "",
                    fields.size() > 4 && !fields[4].empty() ? std::stod(fields[4]) : 0.0,
                    fields.size() > 5 && !fields[5].empty() ? std::stod(fields[5]) : 0.0,
                    fields.size() > 6 ? fields[6] : "",
                    fields.size() > 7 ? fields[7] : "",
                    fields.size() > 8 ? fields[8] : "",
                    fields.size() > 9 ? fields[9] : "",
                    fields.size() > 10 && !fields[10].empty() ? std::stoi(fields[10]) : 0,
                    fields.size() > 11 && !fields[11].empty() ? std::stoi(fields[11]) : 0,
                    fields.size() > 12 && !fields[12].empty() ? std::stoi(fields[12]) : 0,
                    fields.size() > 13 && !fields[13].empty() ? std::stoi(fields[13]) : 0,
                    fields.size() > 14 && !fields[14].empty() ? std::stoi(fields[14]) : 0,
                    fields.size() > 15 && !fields[15].empty() ? std::stoi(fields[15]) : 0,
                    fields.size() > 16 && !fields[16].empty() ? std::stoi(fields[16]) : 0,
                    fields.size() > 17 && !fields[17].empty() ? std::stoi(fields[17]) : 0,
                    fields.size() > 18 ? fields[18] : "",
                    fields.size() > 19 ? fields[19] : "",
                    fields.size() > 20 ? fields[20] : "",
                    fields.size() > 21 ? fields[21] : "",
                    fields.size() > 22 ? fields[22] : "",
                    collision_id,
                    fields.size() > 24 ? fields[24] : "",
                    fields.size() > 25 ? fields[25] : "",
                    fields.size() > 26 ? fields[26] : "",
                    fields.size() > 27 ? fields[27] : "",
                    fields.size() > 28 ? fields[28] : ""
                );
                records.push_back(record);
            } catch (const std::exception& e) {
                // std::cerr << "Error parsing line: " << line << " - " << e.what() << std::endl;
            }
        }

        std::cout << "Loading data... filename: " << filename << std::endl;
    }

    std::vector<RawRecord> query(const std::string& startDateUTC, const std::string& endDateUTC, 
                                 const std::string& commaSeparatedBoroughList, float lat, float lon, 
                                 float distance, const std::string& commaSeparatedPincodeList) override {
        std::vector<RawRecord> result;
        long startEpoch = convertToEpoch(startDateUTC);
        long endEpoch = convertToEpoch(endDateUTC);

        std::vector<std::string> boroughs;
        std::istringstream ssBorough(commaSeparatedBoroughList);
        std::string borough;
        while (std::getline(ssBorough, borough, ',')) {
            boroughs.push_back(borough);
        }

        std::vector<std::string> pincodes;
        std::istringstream ssPincode(commaSeparatedPincodeList);
        std::string pincode;
        while (std::getline(ssPincode, pincode, ',')) {
            pincodes.push_back(pincode);
        }

        #pragma omp parallel for
        for (size_t i = 0; i < records.size(); ++i) {
            try {
                const auto& record = records[i];
                long recordEpoch = convertToEpoch(record.getCrashDate() + " " + record.getCrashTime());
                if (recordEpoch < startEpoch || recordEpoch > endEpoch) {
                    continue;
                }

                if (!commaSeparatedBoroughList.empty() && 
                    std::find(boroughs.begin(), boroughs.end(), record.getBorough()) == boroughs.end()) {
                    continue;
                }

                if (lat != 0.0 && lon != 0.0 && distance != 0.0) {
                    double recordDistance = calculateDistance(lat, lon, record.getLatitude(), record.getLongitude());
                    if (recordDistance > distance) {
                        continue;
                    }
                }

                if (!commaSeparatedPincodeList.empty() && 
                    std::find(pincodes.begin(), pincodes.end(), record.getZipCode()) == pincodes.end()) {
                    continue;
                }

                #pragma omp critical
                result.push_back(record);
            } catch (const std::exception& e) {
                // std::cerr << "Error processing record: " << e.what() << std::endl;
                continue;
            }
        }

        return result;
    }
};

#endif // CSVPARSERSTAGE2_H