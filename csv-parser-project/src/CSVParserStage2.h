#ifndef CSVPARSERSTAGE2_H
#define CSVPARSERSTAGE2_H

#include "CSVParser.h"

class CSVParserStage2 : public CSVParser {
public:
    CSVParserStage2(const std::string& filename);
    void loadCSV(const std::string& filename) override;
    std::vector<CrashRecord> getRecordsByLocationAndTime(double min_lat, double max_lat, double min_lon, double max_lon, const std::string& start_datetime, const std::string& end_datetime) override;
};

#endif // CSVPARSERSTAGE2_H