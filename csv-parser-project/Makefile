CC = g++
CFLAGS = -I./src -std=c++11
SRC = src/main.cpp src/CSVParser.cpp src/CSVParserStage1.cpp src/CSVParserStage2.cpp src/CSVParserStage3.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = csv_parser

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)