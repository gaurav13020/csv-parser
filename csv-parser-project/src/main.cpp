#include <iostream>
#include <memory>
#include <string>
#include "CSVParser.h"
#include "CSVParserStage1.h"
#include "CSVParserStage2.h"
#include "CSVParserStage3.h"

using namespace std;

string FILENAME = "/Users/spartan/work/Projects/csv-parser/crash_data.csv";

int main(int argc, char *argv[]) {
    if (argc < 3 || string(argv[1]) != "--stage") {
        cerr << "Usage: " << argv[0] << " --stage <1|2|3>" << endl;
        return 1;
    }

    unique_ptr<CSVParser> parser;

    int stage = stoi(argv[2]);
    switch (stage) {
        case 1:
            parser = make_unique<CSVParserStage1>();
            break;
        case 2:
            parser = make_unique<CSVParserStage2>();
            break;
        case 3:
            parser = make_unique<CSVParserStage3>();
            break;
        default:
            cerr << "Invalid stage: " << stage << endl;
            return 1;
    }

    parser->load(FILENAME);

    // Define query parameters
    std::string start_datetime = "2021-02-14 12:00";
    std::string end_datetime = "2026-02-14 14:00";
    std::string borough_list = "BROOKLYN,QUEENS";
    float lat = 40.7;
    float lon = -73.9;
    float distance = 10000.0; // in meters
    std::string pincode_list = "11208,11354";

    // Calculate performance
    double avg_time = parser->calculatePerformance(start_datetime, end_datetime, borough_list, lat, lon, distance, pincode_list);
    cout << "Average query execution time: " << avg_time << " seconds" << endl;

    return 0;
}