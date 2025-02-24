#include "CrashRecord.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

// CrashRecord constructor define
CrashRecord::CrashRecord(double lat, double lon, const std::string& datetime) 
    : latitude(lat), longitude(lon), crash_datetime(datetime) {}

// Getters
double CrashRecord::getLatitude() const {
    return latitude;
}

double CrashRecord::getLongitude() const {
    return longitude;
}

std::string CrashRecord::getCrashDateTime() const {
    return crash_datetime;
}

// Check if the crash time is within the given time range
bool CrashRecord::isWithinTimeRange(const std::string& start_datetime, const std::string& end_datetime) const {
    return (crash_datetime >= start_datetime && crash_datetime <= end_datetime);
}

// Check if the crash location is within the given lat/lon range
bool CrashRecord::isWithinLocation(double min_lat, double max_lat, double min_lon, double max_lon) const {
    return (latitude >= min_lat && latitude <= max_lat && longitude >= min_lon && longitude <= max_lon);
}

// CSVParser constructor
CSVParser::CSVParser(const std::string& filename) {
    // Parse the CSV when object is created
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

// Split a CSV line into individual fields
std::vector<std::string> CSVParser::parseCSVLine(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;

    while (getline(ss, field, ',')) {
        fields.push_back(field);
    }

    return fields;
}

// Load CSV file data and store only latitude, longitude, and combined date and time
void CSVParser::loadCSV() {
    std::ifstream file("crash_data.csv");
    if (!file.is_open()) {
        std::cerr << "Could not open file!" << std::endl;
        return;
    }

    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<std::string> fields = parseCSVLine(line);

        // Ensure we have enough fields and check if lat/lon fields are not empty
        if (fields.size() > 5 && !fields[4].empty() && !fields[5].empty()) {
            try {
                // Convert latitude and longitude to doubles
                double lat = std::stod(fields[4]);
                double lon = std::stod(fields[5]);
                
                // Combine crash date and time
                std::string datetime = fields[0] + " " + fields[1];
                // std::cout << "Latitude: " << lat << ", Longitude: " << lon << ", DateTime: " << datetime << std::endl;
                // Emplace new record into the records vector
                records.emplace_back(lat, lon, datetime);

            } catch (const std::invalid_argument& e) {
                // Handle invalid numeric conversion
                // std::cerr << "Invalid data for lat/lon: " << fields[4] << ", " << fields[5] << " - Skipping record." << std::endl;
                continue;  // Skip this record
            } catch (const std::out_of_range& e) {
                // Handle out-of-range numeric conversion
                std::cerr << "Out of range lat/lon: " << fields[4] << ", " << fields[5] << " - Skipping record." << std::endl;
                continue;  // Skip this record
            }
        } else {
            // std::cerr << "Incomplete data in line: " << line << " - Skipping record." << std::endl;
        }
    }
}

// Query records by geographic location and time range
std::vector<CrashRecord> CSVParser::getRecordsByLocationAndTime(double min_lat, double max_lat, double min_lon, double max_lon, const std::string& start_datetime, const std::string& end_datetime) const {
    std::vector<CrashRecord> filtered_records;

    for (const auto& record : records) {
        // std::cout << "Checking record: Lat: " << record.getLatitude() << ", Lon: " << record.getLongitude() << ", DateTime: " << record.getCrashDateTime() << std::endl;
        // if (record.isWithinLocation(min_lat, max_lat, min_lon, max_lon) && 
        //     record.isWithinTimeRange(start_datetime, end_datetime)) {
        //     filtered_records.push_back(record);
        // }
        filtered_records.push_back(record);
    }

    return filtered_records;
}
