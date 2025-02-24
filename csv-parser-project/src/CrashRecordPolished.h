#ifndef CRASHRECORDPOLISHED_H
#define CRASHRECORDPOLISHED_H

#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <ctime>

enum Borough {
    MANHATTAN,
    BROOKLYN,
    QUEENS,
    BRONX,
    STATEN_ISLAND,
    UNKNOWN_BOROUGH
};

class CrashRecordPolished {
public:
    std::vector<std::string> crashDates;
    std::vector<std::string> crashTimes;
    std::vector<long> crashEpochs;
    std::vector<Borough> boroughs;
    std::vector<short> zipCodes;
    std::vector<float> latitudes;
    std::vector<float> longitudes;
    std::vector<std::string> onStreetNames;
    std::vector<std::string> crossStreetNames;
    std::vector<std::string> offStreetNames;
    std::vector<int> numPersonsInjured;
    std::vector<int> numPersonsKilled;
    std::vector<int> numPedestriansInjured;
    std::vector<int> numPedestriansKilled;
    std::vector<int> numCyclistsInjured;
    std::vector<int> numCyclistsKilled;
    std::vector<int> numMotoristsInjured;
    std::vector<int> numMotoristsKilled;
    std::vector<std::string> contributingFactorVehicle1;
    std::vector<std::string> contributingFactorVehicle2;
    std::vector<std::string> contributingFactorVehicle3;
    std::vector<std::string> contributingFactorVehicle4;
    std::vector<std::string> contributingFactorVehicle5;
    std::vector<int> collisionIds;
    std::vector<std::string> vehicleTypeCode1;
    std::vector<std::string> vehicleTypeCode2;
    std::vector<std::string> vehicleTypeCode3;
    std::vector<std::string> vehicleTypeCode4;
    std::vector<std::string> vehicleTypeCode5;

    // Enumerate boroughs
    static std::unordered_map<std::string, Borough> boroughMap;
    static Borough getBoroughCode(const std::string& borough) {
        if (boroughMap.find(borough) == boroughMap.end()) {
            return UNKNOWN_BOROUGH;
        }
        return boroughMap[borough];
    }

    long convertToEpoch(const std::string& date, const std::string& time) {
        std::tm tm = {};
        std::istringstream ss(date + " " + time);
        ss >> std::get_time(&tm, "%m/%d/%Y %H:%M");
        if (ss.fail()) {
            throw std::runtime_error("Failed to parse date time: " + date + " " + time);
        }
        return std::mktime(&tm);
    }

    void addRecord(const std::string& crashDate, const std::string& crashTime, const std::string& borough, short zipCode, float latitude, float longitude,
                   const std::string& onStreetName, const std::string& crossStreetName, const std::string& offStreetName,
                   int numPersonsInjured, int numPersonsKilled, int numPedestriansInjured, int numPedestriansKilled,
                   int numCyclistsInjured, int numCyclistsKilled, int numMotoristsInjured, int numMotoristsKilled,
                   const std::string& contributingFactorVehicle1, const std::string& contributingFactorVehicle2,
                   const std::string& contributingFactorVehicle3, const std::string& contributingFactorVehicle4,
                   const std::string& contributingFactorVehicle5, long collisionId, const std::string& vehicleTypeCode1,
                   const std::string& vehicleTypeCode2, const std::string& vehicleTypeCode3, const std::string& vehicleTypeCode4,
                   const std::string& vehicleTypeCode5) {
        crashDates.push_back(crashDate);
        crashTimes.push_back(crashTime);
        crashEpochs.push_back(convertToEpoch(crashDate, crashTime));
        boroughs.push_back(getBoroughCode(borough));
        zipCodes.push_back(zipCode);
        latitudes.push_back(latitude);
        longitudes.push_back(longitude);
        onStreetNames.push_back(onStreetName);
        crossStreetNames.push_back(crossStreetName);
        offStreetNames.push_back(offStreetName);
        this->numPersonsInjured.push_back(numPersonsInjured);
        this->numPersonsKilled.push_back(numPersonsKilled);
        this->numPedestriansInjured.push_back(numPedestriansInjured);
        this->numPedestriansKilled.push_back(numPedestriansKilled);
        this->numCyclistsInjured.push_back(numCyclistsInjured);
        this->numCyclistsKilled.push_back(numCyclistsKilled);
        this->numMotoristsInjured.push_back(numMotoristsInjured);
        this->numMotoristsKilled.push_back(numMotoristsKilled);
        this->contributingFactorVehicle1.push_back(contributingFactorVehicle1);
        this->contributingFactorVehicle2.push_back(contributingFactorVehicle2);
        this->contributingFactorVehicle3.push_back(contributingFactorVehicle3);
        this->contributingFactorVehicle4.push_back(contributingFactorVehicle4);
        this->contributingFactorVehicle5.push_back(contributingFactorVehicle5);
        this->collisionIds.push_back(collisionId);
        this->vehicleTypeCode1.push_back(vehicleTypeCode1);
        this->vehicleTypeCode2.push_back(vehicleTypeCode2);
        this->vehicleTypeCode3.push_back(vehicleTypeCode3);
        this->vehicleTypeCode4.push_back(vehicleTypeCode4);
        this->vehicleTypeCode5.push_back(vehicleTypeCode5);
    }
};

std::unordered_map<std::string, Borough> CrashRecordPolished::boroughMap = {
    {"MANHATTAN", MANHATTAN},
    {"BROOKLYN", BROOKLYN},
    {"QUEENS", QUEENS},
    {"BRONX", BRONX},
    {"STATEN ISLAND", STATEN_ISLAND}
};

#endif // CRASHRECORDPOLISHED_H