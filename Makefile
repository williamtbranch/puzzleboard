CXXFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

runner: src/runner.cpp board.o geometry.o ./include/*.hpp
	$(CXX) $(CXXFLAGS) ./src/runner.cpp board.o geometry.o -o runner 

board.o: src/board.cpp include/board.hpp ./include/*.hpp
	$(CXX) $(CXXFLAGS) -c ./src/board.cpp ./include/board.hpp

geometry.o: src/geometry.cpp include/geometry.hpp ./include/*.hpp
	$(CXX) $(CXXFLAGS) -c ./src/geometry.cpp ./include/geometry.hpp

run: runner
	./runner

clean:
	rm runner board.o geometry.o 
