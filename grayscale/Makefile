OPENCV_FLAGS=-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs
GCC_FLAGS=-std=c++11 -fopenmp

build: handler.o reference.o student.o main.cpp rgb.h
	g++ $(GCC_FLAGS) main.cpp student.o reference.o handler.o $(OPENCV_FLAGS) -o runner 

handler.o: handler.cpp handler.h
	g++ -c handler.cpp

student.o: student.cpp student.h rgb.h
	g++ $(GCC_FLAGS) -c student.cpp

reference.o: reference.cpp reference.h rgb.h
	g++ -c reference.cpp

clean:
	rm *.o runner output.jpg reference.jpg difference.jpg
