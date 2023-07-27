CXX = g++
STD = -std=c++17
CFLAG = -Wall -Werror -Wextra
GTEST_LIBS := -lgtest

all: compile run

install: compile
	@mkdir MLP_app
	@cp Mlp MLP_app/Mlp
	@rm Mlp

uninstall:
	@rm -rf MLP_app

dist: install
	tar --create --file MLP_app.tar.gzip MLP_app

dvi:
	texi2dvi foo.texi

clean:
	@rm -rf build Mlp *.gcda *.gcno gcov_report/ tests.out.dSYM/ MLP_app
	@rm -f test/test test/test_generated_*.weights
	@rm -f tests.out app/.qmake.stash app/3d_viewer_2_0.pro.user
	@rm -f .clang-format
	@rm -f *.info *.gzip MLP *.aux *.dvi *.log *.toc

tests: clean
	g++ app/model/*.cc app/controller/*.cc test/test.cpp -o test/test -lstdc++ -lgtest -lgtest_main
	cd test && ./test

style:
	cp ../materials/linters/.clang-format .
	cd app ; clang-format -n controller/*.h controller/*.cc model/*.h model/*.cc view/*.h view/*.cc main.cpp

cppcheck:
	cd app ; cppcheck --suppress=missingIncludeSystem --suppress=unknownMacro --std=c++17 --language=c++ controller/*.h controller/*.cc model/*.h model/*.cc view/*.h view/*.cc main.cpp

build:
	mkdir build
	cp -R app/ ./build/

compile: clean build
	cd build ; qmake mlp.pro; make
	cp ./build/mlp.app/Contents/MacOS/mlp ./Mlp

run:
	./Mlp
