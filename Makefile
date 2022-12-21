.PHONY: all install uninstall clean dvi dist tests gcov_report lint leaks

FOLDER=../build/

all: clean build

build: clean
	mkdir $(FOLDER)
	cp calcul_qt.pro $(FOLDER)
	cp *.h *.cpp *.ui *.ts $(FOLDER)
	cd $(FOLDER); qmake calcul_qt.pro
	make -C $(FOLDER)
	cd $(FOLDER); rm -rf *.h *.cpp *.ui *.o *.ts *.pro *.qrc Makefile

install: build
	mkdir $(HOME)/Desktop/SmartCalc_v1.0/
	cp -rf $(FOLDER)calcul_qt.app $(HOME)/Desktop/SmartCalc_v1.0/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/SmartCalc_v1.0/

dvi:
	open calculator.html

dist:
	rm -rf archive_v1
	mkdir archive_v1
	cp Makefile *.c *.h *.pro *.html *.cpp *.ui *.user archive_v1/
	tar -cvzf $(HOME)/Desktop/archive_v1.tgz archive_v1/
	rm -rf archive_v1/

tests: clean_t
	g++ --coverage test.cpp model.cpp -o test -lgtest
	./test

gcov_report: tests
	lcov --no-external -t  "test" -o test.info -c -d ./
	genhtml -o report test.info
	open ./report/index.html

clean_t:
	rm -rf test

clean:
	rm -rf *.o *.a *.gc* *.info coverage report Test *.dSYM test.c
	rm -rf ./report
	rm -rf ./build
	rm -rf ../build
	rm -rf $(HOME)/Desktop/archive_v1.tar.gz

style:
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4}" -i *.cpp *.h
