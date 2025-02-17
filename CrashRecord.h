#ifndef CRASHRECORD_H
#define CRASHRECORD_H

#include <string>
#include <vector>

class CrashRecord {
private:
    double latitude;
    double longitude;
    std::string crash_datetime;  // Combined crash date and time in UTC as string

public:
    // Constructor to initialize the relevant fields
    CrashRecord(double lat, double lon, const std::string& datetime);

    // Getters
    double getLatitude() const;
    double getLongitude() const;
    std::string getCrashDateTime() const;

    // Methods to filter records
    bool isWithinTimeRange(const std::string& start_datetime, const std::string& end_datetime) const;
    bool isWithinLocation(double min_lat, double max_lat, double min_lon, double max_lon) const;
};

class CSVParser {
private:
    std::vector<CrashRecord> records;

    // Helper function to split a CSV line into fields
    std::vector<std::string> parseCSVLine(const std::string& line);

public:
    // Constructor to load the CSV file
    CSVParser(const std::string& filename);

    // Method to load the data from the CSV file
    void loadCSV();

    // Queries based on lat/long and time
    std::vector<CrashRecord> getRecordsByLocationAndTime(double min_lat, double max_lat, double min_lon, double max_lon, const std::string& start_datetime, const std::string& end_datetime) const;
};

#endif
