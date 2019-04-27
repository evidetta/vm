CXX=g++
CXX_COMPILE_FLAGS= -std=c++17 -g -Wall -Ivm -D GTEST
CXX_TEST_FLAGS = -lpthread

GTEST_DIR= /usr/src/googletest/googletest
GMOCK_DIR= /usr/src/googletest/googlemock
BIN_DIR= ../bin

test: $(BIN_DIR)/gtest-all.o $(BIN_DIR)/gmock-all.o $(BIN_DIR)/gmock_main.o $(BIN_DIR)/processor.o $(BIN_DIR)/processor_test.o $(BIN_DIR)/memory.o $(BIN_DIR)/instruction.o $(BIN_DIR)/instruction_set.o $(BIN_DIR)/instruction_set_test.o
	mkdir -p $(BIN_DIR)
	$(CXX) $(BIN_DIR)/gmock_main.o $(BIN_DIR)/gmock-all.o $(BIN_DIR)/gtest-all.o $(BIN_DIR)/processor.o $(BIN_DIR)/processor_test.o $(BIN_DIR)/memory.o $(BIN_DIR)/instruction.o $(BIN_DIR)/instruction_set.o $(BIN_DIR)/instruction_set_test.o -o $(BIN_DIR)/test $(CXX_TEST_FLAGS)
	$(BIN_DIR)/test
$(BIN_DIR)/processor.o: vm/processor/processor.cpp
	$(CXX) $(CXX_COMPILE_FLAGS) -c vm/processor/processor.cpp -o $(BIN_DIR)/processor.o
$(BIN_DIR)/processor_test.o: vm/processor/processor_test.cpp
	$(CXX) $(CXX_COMPILE_FLAGS) -c vm/processor/processor_test.cpp -o $(BIN_DIR)/processor_test.o
$(BIN_DIR)/memory.o: vm/memory/memory.cpp
	$(CXX) $(CXX_COMPILE_FLAGS) -c vm/memory/memory.cpp -o $(BIN_DIR)/memory.o
$(BIN_DIR)/instruction.o: vm/instruction/instruction.cpp
	$(CXX) $(CXX_COMPILE_FLAGS) -c vm/instruction/instruction.cpp -o $(BIN_DIR)/instruction.o
$(BIN_DIR)/instruction_set.o: vm/instruction/instruction_set.cpp
	$(CXX) $(CXX_COMPILE_FLAGS) -c vm/instruction/instruction_set.cpp -o $(BIN_DIR)/instruction_set.o
$(BIN_DIR)/instruction_set_test.o: vm/instruction/instruction_set_test.cpp
	$(CXX) $(CXX_COMPILE_FLAGS) -c vm/instruction/instruction_set_test.cpp -o $(BIN_DIR)/instruction_set_test.o
$(BIN_DIR)/gtest-all.o: $(GTEST_DIR)/src/gtest-all.cc
	$(CXX) $(CXX_COMPILE_FLAGS) -c $(GTEST_DIR)/src/gtest-all.cc -I $(GTEST_DIR) -I $(GTEST_DIR)/include -o $(BIN_DIR)/gtest-all.o
$(BIN_DIR)/gmock-all.o: $(GMOCK_DIR)/src/gmock-all.cc
	$(CXX) $(CXX_COMPILE_FLAGS) -c $(GMOCK_DIR)/src/gmock-all.cc -I $(GMOCK_DIR) -I $(GTEST_MOCK)/include -o $(BIN_DIR)/gmock-all.o
$(BIN_DIR)/gmock_main.o: $(GMOCK_DIR)/src/gmock_main.cc
	$(CXX) $(CXX_COMPILE_FLAGS) -c $(GMOCK_DIR)/src/gmock_main.cc -I $(GMOCK_DIR) -I $(GTEST_MOCK)/include -o $(BIN_DIR)/gmock_main.o
clean:
	rm -f $(BIN_DIR)/*
