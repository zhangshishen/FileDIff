CXX = g++

CXXFLAGS = --std=c++11
LDFLAGS = -lsqlite3

OBJS = main.o container.o detector.o diff.o diffGenerator.o \
	keyExtract.o linefilter.o parser.o preprocessor.o sqlDiff.o \
 	sqlitefilter.o sqLiteReader.o timestampfilter.o tools.o

TARGET = diff.out

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
 
all: $(TARGET)
