GCC_FLAGS=-std=c++11 -fopenmp

build: student.o serial.o helper.o main.cpp
	g++ $(GCC_FLAGS) serial.o student.o helper.o main.cpp -o runner

student.o: student.cpp student.h
	g++ $(GCC_FLAGS) -c student.cpp

serial.o: serial.cpp serial.h
	g++ -c serial.cpp

helper.o: helper.cpp helper.h
	g++ $(GCC_FLAGS) -c helper.cpp

clean:
	rm *.o runner