CXX 		= g++
CXXDEBUG 	= -g
CXXFLAGS 	= $(CXXDEBUG) -pedantic-errors -Wall -O2 -std=c++11 -fPIC
LDFLAGS		= $(shell pkg-config --libs Qt5Widgets Qt5Network Qt5Sql)
INC 		= -I./ -I./build/objects/ $(shell pkg-config --cflags Qt5Widgets Qt5Network Qt5Sql)
BUILD		= ./build
OBJ_DIR		= ./build/objects
APP_DIR		= ./build/app
TARGET		= client
SRC			= $(wildcard *.cpp)
OBJECTS		= $(SRC:%.cpp=$(OBJ_DIR)/%.o)
SRC_MOC		= $(wildcard *.h)
OBJECTS_MOC = $(SRC_MOC:%.h=$(OBJ_DIR)/moc_%.o)
SRC_UI		= $(wildcard *.ui)
INC_UI		= $(SRC_UI:%.ui=$(OBJ_DIR)/ui_%.h)
.PHONY: all clean

all: 
	make -j $(APP_DIR)/$(TARGET); $(info "Compiling with ${CXX} ...")

# create directory parent of target file
$(APP_DIR)/$(TARGET) : $(OBJECTS) $(OBJECTS_MOC)
					mkdir -p $(@D)
					$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o : %.cpp $(INC_UI)
					mkdir -p $(@D)
					$(CXX) -c $(CXXFLAGS) $(INC) $< -o $@

# create moc_*.cpp and moc_*.o for determination meta object in header file
$(OBJ_DIR)/%.o : $(OBJ_DIR)/%.cpp $(INC_UI)
					mkdir -p $(@D)
					$(CXX) -c $(CXXFLAGS) $(INC) $< -o $@

$(OBJ_DIR)/moc_%.cpp : %.h
					mkdir -p $(@D)
					moc $< -o $@

# compile ui files
$(OBJ_DIR)/ui_%.h : %.ui
					uic $< -o $@
clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(APP_DIR)/*

run: all;
		./$(APP_DIR)/$(TARGET)
