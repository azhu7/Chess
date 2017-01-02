# Makefile
#
# Build rules of Chess project
#
# Alexander Zhu <alexzhu@umich.edu>
# December 26, 2016
#
# Run "make help" for usage notes

CC = g++-4.9
CXXFLAGS = -std=c++11 -Wall -Werror -pedantic
TARGET = bin/chess
SRCDIR = src
TESTDIR = test
TEST_EXE = bin/test
OBJDIR = .obj
DEPDIR = .d

# Ensure bin, ODIR, and DEPDIR always exist
$(shell mkdir -p bin $(OBJDIR) $(DEPDIR) >/dev/null)

# Flags to convince compiler to generate dependency file (.Td).
# We generate (.Td) first so that failed compilation doesn't leave
# corrupted dependency file.
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

# Rename the (.Td) to (.d)
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
DEPS = $(addprefix $(DEPDIR)/, $(notdir $(OBJECTS:.o=.d)))

# Build target executable
$(TARGET): $(OBJECTS)
	$(CC) $(CXXFLAGS) -o $@ $^
	@echo "Successfully built chess!"

# Run target executable
run: $(TARGET)
	./$(TARGET)

# Build and run test executable
test: $(TEST_EXE)
$(TEST_EXE): $(TESTDIR)/function_tests.cpp
	$(CC) $(CXXFLAGS) $^ -o $@
	./$(TEST_EXE)

# Suffix replacement rule for building (.o) from (.cpp)'s
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPDIR)/%.d
	$(CC) $(CXXFLAGS) $(DEPFLAGS) -c -o $@ $<
	$(POSTCOMPILE)

# Pattern rule so that make won't fail if (.d) file doesn't exist
$(DEPDIR)/%.d: ;
# Mark .d files "precious" to make, so they won't be automatically deleted
.PRECIOUS: $(DEPDIR)/%.d

# Include the (.d) files
-include $(DEPS)

define MAKEFILE_HELP
Chess Makefile Usage
Usage:
  "make" - build chess exe
  "make run" - build and run chess exe
  "make test" - build and run test files
  "make clean" - delete executables and temporary files
endef
export MAKEFILE_HELP

help:
	@echo "$$MAKEFILE_HELP"

clean:
	$(RM) $(TARGET) $(TEST_EXE) $(OBJDIR)/*.o $(DEPDIR)/*.d