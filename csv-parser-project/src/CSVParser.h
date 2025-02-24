#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <string>
#include <vector>
#include <chrono>
#include "RawRecord.h"

class CSVParser {
public:
    virtual ~CSVParser() = default;

    // Load the CSV file
    virtual void load(const std::string& filename) = 0;

    // Query the records
    virtual std::vector<RawRecord> query(const std::string& startDateUTC, const std::string& endDateUTC, 
                                         const std::string& commaSeparatedBoroughList, float lat, float lon, 
                                         float distance, const std::string& commaSeparatedPincodeList) = 0;

    // Calculate performance
    double calculatePerformance(const std::string& startDateUTC, const std::string& endDateUTC, 
                                const std::string& commaSeparatedBoroughList, float lat, float lon, 
                                float distance, const std::string& commaSeparatedPincodeList) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10; ++i) {
            std::cout << "query execution iteration :  " << i << std::endl;
            query(startDateUTC, endDateUTC, commaSeparatedBoroughList, lat, lon, distance, commaSeparatedPincodeList);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        return duration.count() / 10.0;
    }
};

#endif // CSVPARSER_H