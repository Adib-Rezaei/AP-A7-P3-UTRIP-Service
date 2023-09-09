CC=g++
STD=-std=c++11
CF=$(STD)
BUILD_DIR=build
SOURCE_DIR=Source
TEMPLATE_DIR=.template

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/main.o: $(SOURCE_DIR)/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp $(SOURCE_DIR)/Utrip.hpp
	$(CC) $(CF) -c $(SOURCE_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/handlers.o: $(SOURCE_DIR)/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c $(SOURCE_DIR)/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/Utrip.o: $(SOURCE_DIR)/Utrip.cpp $(SOURCE_DIR)/Utrip.hpp $(SOURCE_DIR)/Filter.hpp $(SOURCE_DIR)/ImportException.hpp $(SOURCE_DIR)/Hotel.hpp $(SOURCE_DIR)/User.hpp
	$(CC) $(CF) -c $(SOURCE_DIR)/Utrip.cpp -o $(BUILD_DIR)/Utrip.o

$(BUILD_DIR)/Hotel.o: $(SOURCE_DIR)/Hotel.cpp $(SOURCE_DIR)/Hotel.hpp $(SOURCE_DIR)/Room.hpp
	$(CC) $(CF) -c $(SOURCE_DIR)/Hotel.cpp -o $(BUILD_DIR)/Hotel.o

$(BUILD_DIR)/User.o: $(SOURCE_DIR)/User.cpp $(SOURCE_DIR)/User.hpp 
	$(CC) $(CF) -c $(SOURCE_DIR)/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Filter.o: $(SOURCE_DIR)/Filter.cpp $(SOURCE_DIR)/Filter.hpp $(SOURCE_DIR)/ImportException.hpp
	$(CC) $(CF) -c $(SOURCE_DIR)/Filter.cpp -o $(BUILD_DIR)/Filter.o

$(BUILD_DIR)/IO.o: $(SOURCE_DIR)/IO.cpp $(SOURCE_DIR)/IO.hpp 
	$(CC) $(CF) -c $(SOURCE_DIR)/IO.cpp -o $(BUILD_DIR)/IO.o

$(BUILD_DIR)/Room.o: $(SOURCE_DIR)/Room.cpp $(SOURCE_DIR)/Room.hpp 
	$(CC) $(CF) -c $(SOURCE_DIR)/Room.cpp -o $(BUILD_DIR)/Room.o

myserver.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Utrip.o $(BUILD_DIR)/Hotel.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Room.o $(BUILD_DIR)/Filter.o $(BUILD_DIR)/IO.o
	$(CC) $(CF) $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Utrip.o $(BUILD_DIR)/Hotel.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Room.o $(BUILD_DIR)/Filter.o $(BUILD_DIR)/IO.o -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
