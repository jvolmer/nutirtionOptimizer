CXX      = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS  = -lm 
LDFLAGSTEST = -lboost_unit_test_framework

TARGETS = main.x
OBJECTS = food.o store.o person.o

TESTS = food.test store.test person.test
TESTOBJECTS = food_test.o store_test.o person_test.o

all: $(TARGETS)

tests : $(TESTS)
# @for testfile in $(TESTS);do \
# 	echo Running $$testfile; \
# 	./$$testfile; \
# 	echo; \
# done

# create targets
main.x : main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# create tests
%.test : %_test.o %.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGSTEST) $(LDFLAGS)
	@echo Running $@
	@./$@ #--log_level=test_suite
	@echo 

store.test : store_test.o store.o food.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGSTEST) $(LDFLAGS)
	@echo Running $@
	@./$@ #--log_level=test_suite
	@echo 

person.test : person_test.o person.o food.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGSTEST) $(LDFLAGS)
	@echo Running $@
	@./$@ #--log_level=test_suite
	@echo 


# create test objetcs
food_test.o : food.hpp
store_test.o : store.hpp food.hpp
person_test.o : person.hpp food.hpp

# create objects
food.o : food.hpp
store.o : store.hpp food.hpp
person.o : person.hpp food.hpp

clean : 
	rm -f *.x *.o *.test

# targets that are not files
.PHONY : all tests clean

# prevents that intermediate files are removed automatically
# (testobjects are never used explicitly as target or prerequisite)
.SECONDARY : $(TESTOBJECTS)
