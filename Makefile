CXX      = g++
CXXFLAGS = -Wall -std=c++14
#-Wno-deprecated-declarations
LDFLAGS  = -lm -lglpk -ljsoncpp
LDFLAGSTEST = -lboost_unit_test_framework
# INCTEST = -I /home/jvolmer/bin/turtle_1.3.1/include

TARGETS = main.x
OBJECTS = food.o store.o person.o solver.o analyzer.o specialFunctions.o

TESTS = food.test store.test person.test solver.test analyzer.test
INTTESTS = analyzer_integration.test
TESTOBJECTS = food_test.o store_test.o person_test.o solver_test.o analyzer_test.o analyzer_integrationtest.o

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
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGSTEST) $(LDFLAGS) $(INCTEST)
	@echo Running $@
	@./$@ #--log_level=test_suite
	@echo 

food.test : food_test.o food.o specialFunctions.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGSTEST) $(LDFLAGS) $(INCTEST)
	@echo Running $@
	@./$@ #--log_level=test_suite
	@echo 

store.test : store_test.o store.o food.o specialFunctions.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGSTEST) $(LDFLAGS) $(INCTEST)
	@echo Running $@
	@./$@ #--log_level=test_suite
	@echo 

person.test : person_test.o person.o specialFunctions.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGSTEST) $(LDFLAGS) $(INCTEST)
	@echo Running $@
	@./$@ #--log_level=test_suite
	@echo 

analyzer.test : analyzer_test.o analyzer.o person.o store.o solver.o food.o specialFunctions.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGSTEST) $(LDFLAGS) $(INCTEST)
	@echo Running $@
	@./$@ #--log_level=test_suite
	@echo 

analyzer_integration.test : analyzer_integrationtest.o analyzer.o person.o store.o solver.o food.o specialFunctions.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGSTEST) $(LDFLAGS) $(INCTEST)
	@echo Running $@
	@./$@ #--log_level=test_suite
	@echo 



# create test objetcs
food_test.o : food.hpp specialFunctions.hpp
store_test.o : store.hpp food.hpp specialFunctions.hpp
person_test.o : person.hpp
solver_test.o : solver.hpp
analyzer_integrationtest.o : analyzer.hpp store.hpp solver.hpp person.hpp food.hpp specialFunctions.hpp
analyzer_test.o : analyzer.hpp solver.hpp store.hpp person.hpp food.hpp specialFunctions.hpp

# $(CXX) $(CXXFLAGS) -c $< -o $@ $(INCTEST)

# create objects
food.o : food.hpp specialFunctions.hpp
store.o : store.hpp food.hpp specialFunctions.hpp
person.o : person.hpp specialFunctions.hpp
solver.o : solver.hpp
analyzer.o : analyzer.hpp store.hpp person.hpp solver.hpp food.hpp specialFunctions.hpp
specialFunctions.o : specialFunctions.hpp

clean : 
	rm -f *.x *.o *.test

# targets that are not files
.PHONY : all tests clean

# prevents that intermediate files are removed automatically
# (testobjects are never used explicitly as target or prerequisite)
.SECONDARY : $(TESTOBJECTS)
