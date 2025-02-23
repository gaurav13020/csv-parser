#ifndef RAWRECORD_H
#define RAWRECORD_H

#include <string>

class RawRecord {
private:
    std::string crash_date;
    std::string crash_time;
    std::string borough;
    std::string zip_code;
    double latitude;
    double longitude;
    std::string location;
    std::string on_street_name;
    std::string cross_street_name;
    std::string off_street_name;
    int number_of_persons_injured;
    int number_of_persons_killed;
    int number_of_pedestrians_injured;
    int number_of_pedestrians_killed;
    int number_of_cyclists_injured;
    int number_of_cyclists_killed;
    int number_of_motorists_injured;
    int number_of_motorists_killed;
    std::string contributing_factor_vehicle_1;
    std::string contributing_factor_vehicle_2;
    std::string contributing_factor_vehicle_3;
    std::string contributing_factor_vehicle_4;
    std::string contributing_factor_vehicle_5;
    long collision_id;
    std::string vehicle_type_code_1;
    std::string vehicle_type_code_2;
    std::string vehicle_type_code_3;
    std::string vehicle_type_code_4;
    std::string vehicle_type_code_5;

public:
    // Constructor to initialize the relevant fields
    RawRecord(const std::string& crash_date, const std::string& crash_time, const std::string& borough, const std::string& zip_code,
              double latitude, double longitude, const std::string& location, const std::string& on_street_name,
              const std::string& cross_street_name, const std::string& off_street_name, int number_of_persons_injured,
              int number_of_persons_killed, int number_of_pedestrians_injured, int number_of_pedestrians_killed,
              int number_of_cyclists_injured, int number_of_cyclists_killed, int number_of_motorists_injured,
              int number_of_motorists_killed, const std::string& contributing_factor_vehicle_1,
              const std::string& contributing_factor_vehicle_2, const std::string& contributing_factor_vehicle_3,
              const std::string& contributing_factor_vehicle_4, const std::string& contributing_factor_vehicle_5,
              long collision_id, const std::string& vehicle_type_code_1, const std::string& vehicle_type_code_2,
              const std::string& vehicle_type_code_3, const std::string& vehicle_type_code_4, const std::string& vehicle_type_code_5)
        : crash_date(crash_date), crash_time(crash_time), borough(borough), zip_code(zip_code), latitude(latitude),
          longitude(longitude), location(location), on_street_name(on_street_name), cross_street_name(cross_street_name),
          off_street_name(off_street_name), number_of_persons_injured(number_of_persons_injured), number_of_persons_killed(number_of_persons_killed),
          number_of_pedestrians_injured(number_of_pedestrians_injured), number_of_pedestrians_killed(number_of_pedestrians_killed),
          number_of_cyclists_injured(number_of_cyclists_injured), number_of_cyclists_killed(number_of_cyclists_killed),
          number_of_motorists_injured(number_of_motorists_injured), number_of_motorists_killed(number_of_motorists_killed),
          contributing_factor_vehicle_1(contributing_factor_vehicle_1), contributing_factor_vehicle_2(contributing_factor_vehicle_2),
          contributing_factor_vehicle_3(contributing_factor_vehicle_3), contributing_factor_vehicle_4(contributing_factor_vehicle_4),
          contributing_factor_vehicle_5(contributing_factor_vehicle_5), collision_id(collision_id), vehicle_type_code_1(vehicle_type_code_1),
          vehicle_type_code_2(vehicle_type_code_2), vehicle_type_code_3(vehicle_type_code_3), vehicle_type_code_4(vehicle_type_code_4),
          vehicle_type_code_5(vehicle_type_code_5) {}

    // Getters
    std::string getCrashDate() const { return crash_date; }
    std::string getCrashTime() const { return crash_time; }
    std::string getBorough() const { return borough; }
    std::string getZipCode() const { return zip_code; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    std::string getLocation() const { return location; }
    std::string getOnStreetName() const { return on_street_name; }
    std::string getCrossStreetName() const { return cross_street_name; }
    std::string getOffStreetName() const { return off_street_name; }
    int getNumberOfPersonsInjured() const { return number_of_persons_injured; }
    int getNumberOfPersonsKilled() const { return number_of_persons_killed; }
    int getNumberOfPedestriansInjured() const { return number_of_pedestrians_injured; }
    int getNumberOfPedestriansKilled() const { return number_of_pedestrians_killed; }
    int getNumberOfCyclistsInjured() const { return number_of_cyclists_injured; }
    int getNumberOfCyclistsKilled() const { return number_of_cyclists_killed; }
    int getNumberOfMotoristsInjured() const { return number_of_motorists_injured; }
    int getNumberOfMotoristsKilled() const { return number_of_motorists_killed; }
    std::string getContributingFactorVehicle1() const { return contributing_factor_vehicle_1; }
    std::string getContributingFactorVehicle2() const { return contributing_factor_vehicle_2; }
    std::string getContributingFactorVehicle3() const { return contributing_factor_vehicle_3; }
    std::string getContributingFactorVehicle4() const { return contributing_factor_vehicle_4; }
    std::string getContributingFactorVehicle5() const { return contributing_factor_vehicle_5; }
    long getCollisionId() const { return collision_id; }
    std::string getVehicleTypeCode1() const { return vehicle_type_code_1; }
    std::string getVehicleTypeCode2() const { return vehicle_type_code_2; }
    std::string getVehicleTypeCode3() const { return vehicle_type_code_3; }
    std::string getVehicleTypeCode4() const { return vehicle_type_code_4; }
    std::string getVehicleTypeCode5() const { return vehicle_type_code_5; }
};

#endif // RAWRECORD_H