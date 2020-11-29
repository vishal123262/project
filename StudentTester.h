#ifndef STUDENTTESTER_H_
#define STUDENTTESTER_H_

#include <string>

class StudentTester {
public:
	StudentTester();

	// init
	void testa();

	// add
	void testb();
	void testc();

	// year cwa
	void testd();
	void teste();
	void testf();

	// mixed cwa
	void testg();
	void testh();

	// update
	void testi();
	void testj();

	// polymorphic add,cwa
	void testk();

	// >>
	void testl();
	void testm();
	void testn();

	// deg class
	void testo();
	void testp();
	void testq();
	void testr();
	void tests();
	void testt();
	void testu();
	void testv();
	void testw();

	// <<, polymorphic deg class
	void testx();
	void testy();

private:
	void errorOut_(const std::string& errMsg, unsigned int errBit);
	void passOut_();

	bool approxEq(float f1, float f2);

	char error_;
	std::string funcname_;

};

#endif /* STUDENTTESTER_H_ */