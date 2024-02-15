compile-run:
	g++ -std=c++20 -o juc.exe ../src/*.cpp
	winpty ./juc.exe

compile:
	g++ -std=c++20 -o juc.exe ../src/*.cpp

run:
	winpty ./juc.exe

lib:
	g++ -std=c++20 -c ../src/*.cpp
	ar rvs libjuc.a *.o
	rm *.o

clean:
	rm *.exe
	rm *.o
	rm *.a
	rm *.dll
	rm *.lib