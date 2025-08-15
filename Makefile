CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -g -MMD -MP -Iinclude -Ivendor/libserialport
LDFLAGS  :=
LDLIBS   := -ludev
SRC_PATH := src
INC_PATH := include
BLD_PATH := build
VENDOR   := vendor/libserialport
VOBJS    := $(VENDOR)/serialport.o
SRCS     := $(wildcard $(SRC_PATH)/*.cpp)
OBJS     := $(patsubst $(SRC_PATH)/%.cpp,$(BLD_PATH)/%.o,$(SRCS))
DEPS     := $(OBJS:.o=.d)
EXE      := $(BLD_PATH)/orea

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJS) $(VOBJS) | $(BLD_PATH)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BLD_PATH)/%.o: $(SRC_PATH)/%.cpp | $(BLD_PATH)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(VOBJS): $(VENDOR)/%.o: $(VENDOR)/%.c | $(BLD_PATH)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BLD_PATH):
	mkdir -p $(BLD_PATH)

clean:
	rm -rf $(BLD_PATH)

-include $(DEPS)
