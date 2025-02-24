#ifndef CSVPARSERSTAGE3_H
#define CSVPARSERSTAGE3_H

#include "CSVParser.h"
#include "CrashRecordPolished.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <omp.h>

class CSVParserStage3 : public CSVParser {
private:
    CrashRecordPolished polishedRecords;

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
                float latitude = fields.size() > 4 && !fields[4].empty() ? std::stof(fields[4]) : 0.0f;
                float longitude = fields.size() > 5 && !fields[5].empty() ? std::stof(fields[5]) : 0.0f;
                short zipCode = fields.size() > 3 && !fields[3].empty() && std::all_of(fields[3].begin(), fields[3].end(), ::isdigit) ? static_cast<short>(std::stoi(fields[3])) : 0;
                std::string borough = fields.size() > 2 ? fields[2] : "";

                polishedRecords.addRecord(
                    fields.size() > 0 ? fields[0] : "",
                    fields.size() > 1 ? fields[1] : "",
                    borough,
                    zipCode,
                    latitude,
                    longitude,
                    fields.size() > 6 ? fields[6] : "",
                    fields.size() > 7 ? fields[7] : "",
                    fields.size() > 8 ? fields[8] : "",
                    fields.size() > 9 && !fields[9].empty() && std::all_of(fields[9].begin(), fields[9].end(), ::isdigit) ? std::stoi(fields[9]) : 0,
                    fields.size() > 10 && !fields[10].empty() && std::all_of(fields[10].begin(), fields[10].end(), ::isdigit) ? std::stoi(fields[10]) : 0,
                    fields.size() > 11 && !fields[11].empty() && std::all_of(fields[11].begin(), fields[11].end(), ::isdigit) ? std::stoi(fields[11]) : 0,
                    fields.size() > 12 && !fields[12].empty() && std::all_of(fields[12].begin(), fields[12].end(), ::isdigit) ? std::stoi(fields[12]) : 0,
                    fields.size() > 13 && !fields[13].empty() && std::all_of(fields[13].begin(), fields[13].end(), ::isdigit) ? std::stoi(fields[13]) : 0,
                    fields.size() > 14 && !fields[14].empty() && std::all_of(fields[14].begin(), fields[14].end(), ::isdigit) ? std::stoi(fields[14]) : 0,
                    fields.size() > 15 && !fields[15].empty() && std::all_of(fields[15].begin(), fields[15].end(), ::isdigit) ? std::stoi(fields[15]) : 0,
                    fields.size() > 16 && !fields[16].empty() && std::all_of(fields[16].begin(), fields[16].end(), ::isdigit) ? std::stoi(fields[16]) : 0,
                    fields.size() > 17 ? fields[17] : "",
                    fields.size() > 18 ? fields[18] : "",
                    fields.size() > 19 ? fields[19] : "",
                    fields.size() > 20 ? fields[20] : "",
                    fields.size() > 21 ? fields[21] : "",
                    fields.size() > 22 && !fields[22].empty() && std::all_of(fields[22].begin(), fields[22].end(), ::isdigit) ? std::stol(fields[22]) : 0,
                    fields.size() > 23 ? fields[23] : "",
                    fields.size() > 24 ? fields[24] : "",
                    fields.size() > 25 ? fields[25] : "",
                    fields.size() > 26 ? fields[26] : "",
                    fields.size() > 27 ? fields[27] : ""
                );
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

        std::vector<Borough> boroughs;
        std::istringstream ssBorough(commaSeparatedBoroughList);
        std::string borough;
        while (std::getline(ssBorough, borough, ',')) {
            boroughs.push_back(CrashRecordPolished::getBoroughCode(borough));
        }

        std::vector<short> pincodes;
        std::istringstream ssPincode(commaSeparatedPincodeList);
        std::string pincode;
        while (std::getline(ssPincode, pincode, ',')) {
            pincodes.push_back(static_cast<short>(std::stoi(pincode)));
        }

        #pragma omp parallel for
        for (size_t i = 0; i < polishedRecords.crashDates.size(); ++i) {
            try {
                long recordEpoch = convertToEpoch(polishedRecords.crashDates[i] + " " + polishedRecords.crashTimes[i]);
                if (recordEpoch < startEpoch || recordEpoch > endEpoch) {
                    continue;
                }

                if (!commaSeparatedBoroughList.empty() && 
                    std::find(boroughs.begin(), boroughs.end(), polishedRecords.boroughs[i]) == boroughs.end()) {
                    continue;
                }

                if (lat != 0.0f && lon != 0.0f && distance != 0.0f) {
                    double recordDistance = calculateDistance(lat, lon, polishedRecords.latitudes[i], polishedRecords.longitudes[i]);
                    if (recordDistance > distance) {
                        continue;
                    }
                }

                if (!commaSeparatedPincodeList.empty() && 
                    std::find(pincodes.begin(), pincodes.end(), polishedRecords.zipCodes[i]) == pincodes.end()) {
                    continue;
                }

                #pragma omp critical
                result.push_back(RawRecord(
                    polishedRecords.crashDates[i],
                    polishedRecords.crashTimes[i],
                    "", // Location column is redundant
                    "", // Location column is redundant
                    polishedRecords.latitudes[i],
                    polishedRecords.longitudes[i],
                    "", // Borough column is replaced by enumerated list
                    "", // Borough column is replaced by enumerated list
                    "", // Borough column is replaced by enumerated list
                    "", // Borough column is replaced by enumerated list
                    polishedRecords.numPersonsInjured[i],
                    polishedRecords.numPersonsKilled[i],
                    polishedRecords.numPedestriansInjured[i],
                    polishedRecords.numPedestriansKilled[i],
                    polishedRecords.numCyclistsInjured[i],
                    polishedRecords.numCyclistsKilled[i],
                    polishedRecords.numMotoristsInjured[i],
                    polishedRecords.numMotoristsKilled[i],
                    polishedRecords.contributingFactorVehicle1[i],
                    polishedRecords.contributingFactorVehicle2[i],
                    polishedRecords.contributingFactorVehicle3[i],
                    polishedRecords.contributingFactorVehicle4[i],
                    polishedRecords.contributingFactorVehicle5[i],
                    polishedRecords.collisionIds[i],
                    polishedRecords.vehicleTypeCode1[i],
                    polishedRecords.vehicleTypeCode2[i],
                    polishedRecords.vehicleTypeCode3[i],
                    polishedRecords.vehicleTypeCode4[i],
                    polishedRecords.vehicleTypeCode5[i]
                ));
            } catch (const std::exception& e) {
                // std::cerr << "Error processing record: " << e.what() << std::endl;
                continue;
            }
        }

        return result;
    }
};

#endif // CSVPARSERSTAGE3_H