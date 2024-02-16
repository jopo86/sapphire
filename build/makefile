compile-run:
	g++ -std=c++20 -o sapphire.exe ../src/*.cpp
	./sapphire.exe

compile:
	g++ -std=c++20 -o sapphire.exe ../src/*.cpp

run:
	./sapphire.exe

lib:
	g++ -std=c++20 -c ../src/*.cpp
	ar rvs libsapphire.a *.o
	rm *.o

clean:
	rm *.exe
	rm *.o
	rm *.a
	rm *.dll
	rm *.lib