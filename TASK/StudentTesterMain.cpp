#include <iostream>
#include "StudentTester.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

	for(int i=1; i<argc; i++) {
		switch (argv[i][0]) {
		case 'a': { StudentTester t; t.testa(); } break;
		case 'b': { StudentTester t; t.testb(); } break;
		case 'c': { StudentTester t; t.testc(); } break;
		case 'd': { StudentTester t; t.testd(); } break;
		case 'e': { StudentTester t; t.teste(); } break;
		case 'f': { StudentTester t; t.testf(); } break;
		case 'g': { StudentTester t; t.testg(); } break;
		case 'h': { StudentTester t; t.testh(); } break;
		case 'i': { StudentTester t; t.testi(); } break;
		case 'j': { StudentTester t; t.testj(); } break;
		case 'k': { StudentTester t; t.testk(); } break;
		case 'l': { StudentTester t; t.testl(); } break;
		case 'm': { StudentTester t; t.testm(); } break;
		case 'n': { StudentTester t; t.testn(); } break;
		case 'o': { StudentTester t; t.testo(); } break;
		case 'p': { StudentTester t; t.testp(); } break;
		case 'q': { StudentTester t; t.testq(); } break;
		case 'r': { StudentTester t; t.testr(); } break;
		case 's': { StudentTester t; t.tests(); } break;
		case 't': { StudentTester t; t.testt(); } break;
		case 'u': { StudentTester t; t.testu(); } break;
		case 'v': { StudentTester t; t.testv(); } break;
		case 'w': { StudentTester t; t.testw(); } break;
		case 'x': { StudentTester t; t.testx(); } break;
		case 'y': { StudentTester t; t.testy(); } break;
		default: { cout<<"Options are a -- y."<<endl; } break;
	       	}
	}
	return 0;
}
