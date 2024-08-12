#FLAGS=-Wall -Wextra -Werror -std=c++17 -I /opt/goinfre/${USER}/homebrew/include
FLAGS=-Wall -Wextra -Werror -std=c++17 
#GTEST=-lgtest -L/opt/goinfre/${USER}/homebrew/lib
GTEST=-lgtest 
COVER=-fprofile-arcs -ftest-coverage

all: gcov_report

install: 
	mkdir build && cd build && cmake .. 
	cd build && make

install2:
	mkdir build && cd build && qmake ..
	cd build && make

open:
	./build/SmartCalc_v2.app/Contents/MacOS/SmartCalc_v2

dvi:
	open about.html

dist: install
	tar -czf SmartCalc_v2.tar.gz --directory=build/ .

uninstall:
	rm -rf build

clean:
	rm -rf build
	rm -f SmartCalc_v2.tar.gz
	rm -f ./*.info ./*.gcda ./*.gcno ./*.gcov
	rm -rf ./coverage
	rm -f test

tests: clean
	g++ $(FLAGS) $(GTEST) $(COVER) Tests/tests.cc -o test
	./test

gcov_report: clean tests
	geninfo . -b . -o ./coverage.info --no-external
	genhtml coverage.info -o ./coverage
	open coverage/index.html

check:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.h *.cc *.cpp 
	clang-format -i View/*.h View/*.cc
	clang-format -i Model/*.h Model/*.cc
	clang-format -i Controller/*.h Controller/*.cc
	rm -rf .clang-format

leaks: 
	g++ $(FLAGS) $(GTEST) $(COVER) Tests/tests.cc -o test
	leaks -atExit -- ./test

 # --ignore-errors mismatch