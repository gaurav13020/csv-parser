#ifndef CSVPARSERSTAGE1_H
#define CSVPARSERSTAGE1_H

#include "CSVParser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cmath>

class CSVParserStage1 : public CSVParser {
private:
    std::vector<RawRecord> records;

    // Helper function to convert date and time to epoch
    long convertToEpoch(const std::string& datetime) {
        std::tm tm = {};
        std::istringstream ss(datetime);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
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
            std::istringstream ss(line);
            std::string token;
            std::vector<std::string> fields;

            while (std::getline(ss, token, ',')) {
                fields.push_back(token);
            }

            try {
                RawRecord record(
                    fields[0], fields[1], fields[2], fields[3],
                    fields[4].empty() ? 0.0 : std::stod(fields[4]),
                    fields[5].empty() ? 0.0 : std::stod(fields[5]),
                    fields[6], fields[7], fields[8], fields[9],
                    fields[10].empty() ? 0 : std::stoi(fields[10]),
                    fields[11].empty() ? 0 : std::stoi(fields[11]),
                    fields[12].empty() ? 0 : std::stoi(fields[12]),
                    fields[13].empty() ? 0 : std::stoi(fields[13]),
                    fields[14].empty() ? 0 : std::stoi(fields[14]),
                    fields[15].empty() ? 0 : std::stoi(fields[15]),
                    fields[16].empty() ? 0 : std::stoi(fields[16]),
                    fields[17].empty() ? 0 : std::stoi(fields[17]),
                    fields[18], fields[19], fields[20], fields[21], fields[22],
                    fields[23].empty() ? 0 : std::stol(fields[23]),
                    fields[24], fields[25], fields[26], fields[27], fields[28]
                );
                records.push_back(record);
            } catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << line << " - " << e.what() << std::endl;
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

        for (const auto& record : records) {
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

            result.push_back(record);
        }

        return result;
    }
};

#endif // CSVPARSERSTAGE1_H