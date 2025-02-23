# csv-parser-project/csv-parser-project/README.md

# CSV Parser Project

This project implements a CSV parser with multiple stages, allowing users to select a specific version of the parser via command line arguments. The project is structured to provide an abstract base class for the CSV parser, which is then extended by three concrete implementations.

## Project Structure

```
csv-parser-project
├── src
│   ├── main.cpp                # Entry point of the application
│   ├── CSVParser.h             # Abstract class for CSV parsing
│   ├── CSVParser.cpp           # Common functionality for CSVParser
│   ├── CSVParserStage1.h       # Stage 1 specific parser
│   ├── CSVParserStage1.cpp     # Implementation of Stage 1 parser
│   ├── CSVParserStage2.h       # Stage 2 specific parser
│   ├── CSVParserStage2.cpp     # Implementation of Stage 2 parser
│   ├── CSVParserStage3.h       # Stage 3 specific parser
│   ├── CSVParserStage3.cpp     # Implementation of Stage 3 parser
│   └── CrashRecord.h           # Class representing individual crash records
├── Makefile                     # Build instructions for the project
└── README.md                    # Project documentation
```

## Building the Project

To build the project, navigate to the project directory and run the following command:

```
make
```

This will compile the source files and create an executable.

## Running the Application

To run the application, use the following command format:

```
./main --stage <stage_number>
```

Replace `<stage_number>` with `1`, `2`, or `3` to select the desired CSV parser stage. For example:

```
./main --stage 1
```

## CSV Parser Stages

- **Stage 1**: Basic CSV parsing functionality.
- **Stage 2**: Enhanced CSV parsing with additional features.
- **Stage 3**: Advanced CSV parsing with optimizations and extended capabilities.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.