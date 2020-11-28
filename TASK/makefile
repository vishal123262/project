# Makefile

# the C++ compiler
CXX     = g++
#CXXVERSION = $(shell g++ --version | grep ^g++ | sed 's/^.* //g')

# options to pass to the compiler
CXXFLAGS = -O0 -g3 -std=c++14

All: all
all: main StudentTesterMain

main: main.cpp Student.o BScStudent.o BScStudentOld.o BScStudentNew.o MScStudent.o
	$(CXX) $(CXXFLAGS) main.cpp Student.o BScStudent.o BScStudentOld.o BScStudentNew.o MScStudent.o -o main

Student.o: Student.cpp Student.h Module.h
	$(CXX) $(CXXFLAGS) -c Student.cpp -o Student.o

BScStudent.o: BScStudent.cpp Student.h
	$(CXX) $(CXXFLAGS) -c BScStudent.cpp -o BScStudent.o

BScStudentOld.o: BScStudentOld.cpp Student.h
	$(CXX) $(CXXFLAGS) -c BScStudentOld.cpp -o BScStudentOld.o

BScStudentNew.o: BScStudentNew.cpp Student.h
	$(CXX) $(CXXFLAGS) -c BScStudentNew.cpp -o BScStudentNew.o

MScStudent.o: MScStudent.cpp Student.h
	$(CXX) $(CXXFLAGS) -c MScStudent.cpp -o MScStudent.o

StudentTester.o: StudentTester.cpp StudentTester.h
	$(CXX) $(CXXFLAGS) -c StudentTester.cpp -o StudentTester.o

StudentTesterMain: StudentTesterMain.cpp StudentTester.o Student.o BScStudent.o BScStudentOld.o BScStudentNew.o MScStudent.o
	$(CXX) $(CXXFLAGS) StudentTesterMain.cpp StudentTester.o Student.o BScStudent.o BScStudentOld.o BScStudentNew.o MScStudent.o -o StudentTesterMain

deepclean:
	rm -f *~ *.o main *.exe *.stackdump

clean:
	rm -f *~ *.o *.stackdump

