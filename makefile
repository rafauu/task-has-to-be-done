GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /usr/local/include

G++ = g++
G++_FLAGS = -c -Wall -I $(GOOGLE_TEST_INCLUDE) -std=c++1z
LD_FLAGS = -L /usr/local/lib -l $(GOOGLE_TEST_LIB) -l pthread -L/usr/local/boost/boost_1_39_0/stage/lib -lboost_filesystem

OBJECTS = MultipleActionsHandlerTestSuite.o
TARGET = MultipleActionsHandlerTestSuite

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LD_FLAGS)

%.o : %.cpp
	$(G++) $(G++_FLAGS) $<

clean:
	rm -f $(TARGET) $(OBJECTS)
                    
.PHONY: all clean
