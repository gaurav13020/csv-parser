#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

string convertToUTC(const string& date, const string& time) {
    struct tm tm = {};
    stringstream ss(date + " " + time);
    ss >> get_time(&tm, "%m/%d/%Y %H:%M");

    time_t local_time = mktime(&tm);
    tm = *gmtime(&local_time);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
    return string(buffer);
}

int main() {
    ifstream file("crash_data.csv");
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    // Read the header line
    getline(file, line);

    int count = 0;
    while (getline(file, line) && count < 10) {
        stringstream ss(line);
        string item;
        vector<string> row;

        while (getline(ss, item, ',')) {
            row.push_back(item);
        }

        if (row.size() >= 6) {
            string crash_date = row[0];
            string crash_time = row[1];
            string latitude = row[4];
            string longitude = row[5];

            string utc_time = convertToUTC(crash_date, crash_time);

            cout << "Crash Time (UTC): " << utc_time << ", Longitude: " << longitude << ", Latitude: " << latitude << endl;
            count++;
        }
    }

    file.close();
    return 0;
}
