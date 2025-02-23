class CrashRecord {
public:
    CrashRecord(double latitude, double longitude, const std::string& crashDateTime)
        : latitude(latitude), longitude(longitude), crashDateTime(crashDateTime) {}

    double getLatitude() const {
        return latitude;
    }

    double getLongitude() const {
        return longitude;
    }

    std::string getCrashDateTime() const {
        return crashDateTime;
    }

private:
    double latitude;
    double longitude;
    std::string crashDateTime;
};