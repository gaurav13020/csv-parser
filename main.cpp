#include "CrashRecord.h"
#include <iostream>

int main() {
    // Create CSV parser and load data
    CSVParser parser = CSVParser("crash_data.csv");
    parser.loadCSV();

    // Define geographic location (latitude and longitude range)
    double min_lat = 40.5, max_lat = 40.9;
    double min_lon = -74.0, max_lon = -73.7;

    // Define time range (in UTC) with both date and time
    std::string start_datetime = "2021-02-14 12:00";
    std::string end_datetime = "2026-02-14 14:00";

    // Get filtered records
    std::vector<CrashRecord> results = parser.getRecordsByLocationAndTime(min_lat, max_lat, min_lon, max_lon, start_datetime, end_datetime);
    std::cout << "Number of records found: " << results.size() << std::endl;
    // Display results
    
    for (const auto& record : results) {
        std::cout << "Lat: " << record.getLatitude() 
                  << ", Lon: " << record.getLongitude() 
                  << ", DateTime: " << record.getCrashDateTime() 
                  << std::endl;
    }

    return 0;
}
