Executable := main \

Code := main.cpp \

CXXFLAGS := -std=c++11 -ggdb -O0

.PHONY : all

.PHONY : clean

all : 
		make $(Executable)

clean :
		rm -f $(Executable)

main : main.cpp
		$(CXX) $(CXXFLAGS) $< -o $@		

