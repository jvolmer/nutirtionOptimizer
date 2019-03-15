CXX      = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS  = -lm 
LDFLAGSTEST = -lboost_unit_test_framework

TARGETS = main.x
TESTS = food.test
TESTOBJECTS = food_test.o

all: $(TARGETS)

tests : $(TESTS)
# @for testfile in $(TESTS);do \
# 	echo Running $$testfile; \
# 	./$$testfile; \
# 	echo; \
# done

# create targets
main.x : main.o food.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# create tests
%.test : %_test.o %.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGSTEST) $(LDFLAGS)
	@echo Running $@
	@./$@ #--log_level=test_suite
	@echo 

# create test objetcs
%_test.o : %.hpp

# create objects
food.o : food.hpp


clean : 
	rm -f *.x *.o

# targets that are not files
.PHONY : all tests clean

# prevents that intermediate files are removed automatically
# (testobjects are never used explicitly as target or prerequisite)
.SECONDARY : $(TESTOBJECTS)
