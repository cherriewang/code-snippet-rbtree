BIN_DIR = bin
CXX = g++
CPPFLAGS = -g -Wall
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread
 
 
all: $(BIN_DIR)/.dirstamp $(BIN_DIR)/test $(BIN_DIR)/color

 
$(BIN_DIR)/4color.o: 4color.cpp 4color.h $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c 4color.cpp -o $(BIN_DIR)/4color.o 

$(BIN_DIR)/test: test.cpp bst.h rbbst.h
	$(CXX) $(CPPFLAGS) test.cpp -o $(BIN_DIR)/test

$(BIN_DIR)/color: color.cpp bst.h rbbst.h $(BIN_DIR)/4color.o
	$(CXX) $(CPPFLAGS) color.cpp $(BIN_DIR)/4color.o -o $(BIN_DIR)/color

#$(BIN_DIR)/bsttest: bsttest.cpp bst.h
#	$(CXX) $(CPPFLAGS) $^ $(GTEST_LL) -o $@


#$(BIN_DIR)/rbtest: rbtest.cpp bst.h
#	$(CXX) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

#bsttest: $(BIN_DIR)/bsttest
#	-@$(BIN_DIR)/bsttest
#	-@echo "--- All Tested!---"

#stacktest: $(BIN_DIR)/rbtest
#	-@$(BIN_DIR)/rbtest
#	-@echo "--- All Tested!---"

#make a bin directory if it doesnt exist
 
$(BIN_DIR)/.dirstamp:
	mkdir $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp
 
.PHONY: clean 
#rbtest
#PHONY: clean
 
clean:
	rm -rf bin