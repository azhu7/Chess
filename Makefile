CC = g++-4.9
CXXFLAGS = -std=c++11 -Wall -Werror -pedantic
TARGET = chess
SDIR = src
IDIR = include
ODIR = obj

SOURCES = $(wildcard $(SDIR)/*.cpp)
OBJECTS = $(addprefix $(ODIR)/, $(notdir $(SOURCES:.cpp=.o)))

# Build target executable
$(TARGET): $(OBJECTS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJECTS)

# Suffix replacement rule for building .o from .cpp's
$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(TARGET) $(ODIR)/*.o