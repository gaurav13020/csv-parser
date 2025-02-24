#ifndef CSVPARSERSTAGE1_H
#define CSVPARSERSTAGE1_H

#include "CSVParserBase.h"
#include <algorithm>

class CSVParserStage1 : public CSVParserBase {
public:
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
            try {
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
            } catch (const std::exception& e) {
                // std::cerr << "Error processing record: " << e.what() << std::endl;
                continue;
            }
        }

        return result;
    }
};

#endif // CSVPARSERSTAGE1_H