#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "StudentTester.h"
#include "Student.h"

using namespace std;

StudentTester::StudentTester() : error_(false), funcname_("") {}

// error code 0 = pass all to get 2 marks
// error codes 1,2 = pass all with same error code get 1 mark

// 3 types of students. check cwa with no modules
void StudentTester::testa() {
	funcname_ = "StudentTester::testa";

	BScStudentOld a("alice");
	if (a.y2cwa() != 0 || a.y3cwa() != 0)
		errorOut_("empty BScStudentOld incorrect", 0);

	BScStudentNew b("bob");
	if (b.y2cwa() != 0 || b.y3cwa() != 0)
		errorOut_("empty BScStudentNew incorrect", 0);

	MScStudent c("carol");
	if (c.cwa() != 0)
		errorOut_("empty MScStudent incorrect", 0);

	passOut_();
}

// add: duplicate add; exceed credits
void StudentTester::testb() {
	funcname_ = "StudentTester::testb";

	BScStudentOld a("");
	bool b = a.addModule("CO3105",0);
	if (!b) errorOut_("return boolean not correct when added once",1);
	b = a.addModule("CO3105",0);
	if (b) errorOut_("return boolean not correct when added again",1);

	BScStudentNew c("");
	c.addModule("CO3FAK",0);
	b = c.addModule("CO3105",60);
	if (b || c.y3cwa() != 0)
		errorOut_("allowed addition exceeding BSc max credits",2);
	MScStudent d("");
	d.addModule("CO7FAK",0);
	d.addModule("CO7201",0);
	b = d.addModule("CO7105",60);
	if (b || d.cwa() != 0)
		errorOut_("allowed addition exceeding MSc max credits",2);

	passOut_();
}

// add: module does not exist; wrong yeargroup
void StudentTester::testc() {
	funcname_ = "StudentTester::testc";

	MScStudent a("");
	bool b = a.addModule("CO7XYZ",50);
	if (b || a.cwa() != 0)
		errorOut_("allowed addition of non-existing modules",1);

	b = a.addModule("CO3105",50);
	if (b || a.cwa() != 0)
		errorOut_("allowed addition of BSc modules to MSc",2);
	BScStudentOld c("");
	b = c.addModule("CO7105",50);
	if (b || c.cwa() != 0)
		errorOut_("allowed addition of MSc modules to BSc",2);

	passOut_();
}

// y2cwa
void StudentTester::testd() {
	funcname_ = "StudentTester::testd";

	BScStudentOld a("");
	a.addModule("CO2011",40);
	if (!approxEq(a.y2cwa(), 40))
		errorOut_("BScOld y2cwa 40 reported as "+std::to_string(a.y2cwa()),1);

	a.addModule("CO2015",70);
	if (!approxEq(a.y2cwa(), 55))
		errorOut_("BScOld y2cwa 55 reported as "+std::to_string(a.y2cwa()),2);
	a.addModule("CO2001",80);
	if (!approxEq(a.y2cwa(), 60))
		errorOut_("BScOld y2cwa 60 reported as "+std::to_string(a.y2cwa()),2);
	a.addModule("CO3101",90);
	if (!approxEq(a.y2cwa(), 60))
		errorOut_("BScOld y2cwa 60 reported as "+std::to_string(a.y2cwa()),2);

	BScStudentNew b("");
	b.addModule("CO2011",40);
	if (!approxEq(b.y2cwa(), 40))
		errorOut_("BScNew y2cwa 40 reported as "+std::to_string(b.y2cwa()),2);
	b.addModule("CO2015",70);
	if (!approxEq(b.y2cwa(), 55))
		errorOut_("BScNew y2cwa 50 reported as "+std::to_string(b.y2cwa()),2);
	b.addModule("CO2001",80);
	if (!approxEq(b.y2cwa(), 60))
		errorOut_("BScNew y2cwa 60 reported as "+std::to_string(b.y2cwa()),2);
	b.addModule("CO3101",90);
	if (!approxEq(b.y2cwa(), 60))
		errorOut_("BScNew y2cwa 60 reported as "+std::to_string(b.y2cwa()),2);

	passOut_();
}

// y3cwa
void StudentTester::teste() {
	funcname_ = "StudentTester::teste";

	BScStudentNew b("");
	b.addModule("CO3105",40);
	if (!approxEq(b.y3cwa(), 40))
		errorOut_("BScNew y3cwa 40 reported as "+std::to_string(b.y3cwa()),1);

	b.addModule("CO3102",50);
	if (!approxEq(b.y3cwa(), 45))
		errorOut_("BScNew y3cwa 45 reported as "+std::to_string(b.y3cwa()),2);
	b.addModule("CO3201",60);
	if (!approxEq(b.y3cwa(), 54))
		errorOut_("BScNew y3cwa 54 reported as "+std::to_string(b.y3cwa()),2);
	b.addModule("CO2201",70);
	if (!approxEq(b.y3cwa(), 54))
		errorOut_("BScNew y3cwa 54 reported as "+std::to_string(b.y3cwa()),2);

	BScStudentOld a("");
	a.addModule("CO3105",40);
	if (!approxEq(a.y3cwa(), 40))
		errorOut_("BScOld y3cwa 40 reported as "+std::to_string(a.y3cwa()),2);
	a.addModule("CO3102",50);
	if (!approxEq(a.y3cwa(), 45))
		errorOut_("BScOld y3cwa 45 reported as "+std::to_string(a.y3cwa()),2);
	a.addModule("CO3201",60);
	if (!approxEq(a.y3cwa(), 54))
		errorOut_("BScOld y3cwa 54 reported as "+std::to_string(a.y3cwa()),2);
	a.addModule("CO2201",70);
	if (!approxEq(a.y3cwa(), 54))
		errorOut_("BScOld y3cwa 54 reported as "+std::to_string(a.y3cwa()),2);

	passOut_();
}

// cwa msc
void StudentTester::testf() {
	funcname_ = "StudentTester::testf";

	MScStudent a("");
	a.addModule("CO7105",40);
	if (!approxEq(a.cwa(), 40))
		errorOut_("MSc cwa 40 reported as "+std::to_string(a.cwa()),1);

	a.addModule("CO7102",50);
	if (!approxEq(a.cwa(), 45))
		errorOut_("MSc cwa 45 reported as "+std::to_string(a.cwa()),2);
	a.addModule("CO7201",60);
	if (!approxEq(a.cwa(), 55))
		errorOut_("MSc cwa 55 reported as "+std::to_string(a.cwa()),2);

	passOut_();
}

// cwa bscold
void StudentTester::testg() {
	funcname_ = "StudentTester::testg";

	BScStudentOld a("");
	a.addModule("CO2FAK", 44.4);
	a.addModule("CO3FAK", 66.6);
	if (!approxEq(a.cwa(), 57.72))
		errorOut_("BScOld cwa reported as "+std::to_string(a.cwa()),0);

	passOut_();
}

// cwa bscnew
void StudentTester::testh() {
	funcname_ = "StudentTester::testh";

	BScStudentNew a("");
	a.addModule("CO2FAK", 44.4);
	a.addModule("CO3FAK", 66.6);
	if (!approxEq(a.cwa(), 59.274))
		errorOut_("BScNew cwa reported as "+std::to_string(a.cwa()),0);

	passOut_();
}

// updatemark
void StudentTester::testi() {
	funcname_ = "StudentTester::testi";

	BScStudentOld a("");
	a.addModule("CO3105",69.31);
	a.updateMark("CO3105",42.57);
	if (!approxEq(a.y3cwa(), 42.57))
		errorOut_("update mark incorrect",1);

	MScStudent b("");
	b.addModule("CO7105",69.31);
	b.updateMark("CO7105",42.57);
	if (!approxEq(b.cwa(), 42.57))
		errorOut_("update mark incorrect",2);

	passOut_();
}

// updatemark return value
void StudentTester::testj() {
	funcname_ = "StudentTester::testj";

	BScStudentOld a("");
	bool b = a.updateMark("CO2101", 90);
	if (b || a.y2cwa() != 0)
		errorOut_("BScOld updated mark of module not added",1);
	BScStudentNew c("");
	b = c.updateMark("CO3105", 90);
	if (b || c.y3cwa() != 0)
		errorOut_("BScNew updated mark of module not added",1);

	MScStudent d("");
	d.addModule("CO7105",50);
	b = d.updateMark("CO7XYZ",60);
	if (b || !approxEq(d.cwa(), 50))
		errorOut_("update mark added nonexistent module",2);

	passOut_();
}

// polymorphic add,update,cwa
void StudentTester::testk() {
	funcname_ = "StudentTester::testk";

	Student* sp = new BScStudentOld("");
	sp->addModule("CO3105", 100);
	if (!approxEq(sp->cwa(), 60))
		errorOut_("BScOld cwa reported as "+std::to_string(sp->cwa()),1);
	delete sp;

	sp = new BScStudentNew("");
	sp->addModule("CO3105", 90);
	sp->updateMark("CO3105",100);
	if (!approxEq(sp->cwa(), 67))
		errorOut_("BScNew cwa reported as "+std::to_string(sp->cwa()),2);
	delete sp;

	sp = new MScStudent("");
	sp->addModule("CO7105", 100);
	sp->updateMark("CO7105",90);
	if (!approxEq(sp->cwa(), 90))
		errorOut_("MSc cwa reported as "+std::to_string(sp->cwa()),1);
	delete sp;

	passOut_();
}

// simple >>
void StudentTester::testl() {
	funcname_ = "StudentTester::testl";

	ifstream fin("teststudent1.txt");
	BScStudentNew a("");
	fin >> a; // 2101 50 3201 70
	if (!approxEq(a.y2cwa(),50) || !approxEq(a.y3cwa(),70))
		errorOut_("read input stream incorrect",0);

	passOut_();
}

// >> mix with add/update, duplicate entries, nonexistent module
void StudentTester::testm() {
	funcname_ = "StudentTester::testm";

	ifstream fin("teststudent2.txt");
	BScStudentOld a("");
	a.addModule("CO3105",30);
	fin >> a; // 3102 40 3105 50 3xyz 99
	if (!approxEq(a.y3cwa(),35))
		errorOut_(">> incorrect",1);
	a.addModule("CO3102",60);
	if (!approxEq(a.y3cwa(),35))
		errorOut_("add after >> incorrect",2);
	a.updateMark("CO3102",60);
	if (!approxEq(a.y3cwa(),45))
		errorOut_("update after >> incorrect",2);

	passOut_();
}

// >> wrong year group, exceed credit, polymorphic
void StudentTester::testn() {
	funcname_ = "StudentTester::testn";

	ifstream fin("teststudent3.txt"); // 7105 40 3105 50 3FAK 60
	BScStudentOld a("");
	Student& sr = a;
	fin >> sr;
	if (!approxEq(sr.cwa(),30))
		errorOut_(">> not reading into BScOld correctly",1);

	ifstream fin2("teststudent3.txt");
	MScStudent b("");
	Student& sr2 = b;
	fin2 >> sr2;
	if (!approxEq(sr2.cwa(),40))
		errorOut_(">> not reading into MSc correctly",2);

	passOut_();
}

// deg class bscold1: 2 basic routes
void StudentTester::testo() {
	funcname_ = "StudentTester::testo";

	string s;
	BScStudentOld a("");
	a.addModule("CO2001",100);
	a.addModule("CO2006",100);
	a.addModule("CO2008",40);
	a.addModule("CO2011",40);
	a.addModule("CO2012",100);
	a.addModule("CO2015",100);
	a.addModule("CO2016",40);
	a.addModule("CO2017",40);
	a.addModule("CO3101",70);
	a.addModule("CO3102",70);
	a.addModule("CO3105",70);
	a.addModule("CO3002",69);
	a.addModule("CO3093",69);
	a.addModule("CO3201",69);
	s = a.calcDegClass();
	if (s != "FIRST CLASS")
		errorOut_("cwa>70 reported as "+s,1);
//cout << a.y2cwa() << " " << a.y3cwa() << " " << a.cwa() << endl;

	a.updateMark("CO2006",70);
	a.updateMark("CO2015",75);
	s = a.calcDegClass();
	if (s != "UPPER SECOND CLASS")
		errorOut_("cwa<67 reported as "+s,1);
	a.updateMark("CO2006",100);
	a.updateMark("CO2015",100);

	a.updateMark("CO3002",69.6);
	a.updateMark("CO3201",60);
	s = a.calcDegClass();
	if (s != "FIRST CLASS")
		errorOut_("cwa>67 and 120cr>70 reported as "+s,2);

	a.updateMark("CO3002",69.4);
	a.updateMark("CO3201",54);
	s = a.calcDegClass();
	if (s != "UPPER SECOND CLASS")
		errorOut_("cwa<67 and 105cr>70 reported as "+s,2);

	a.updateMark("CO2001",80);
	a.updateMark("CO2006",80);
	a.updateMark("CO2008",40);
	a.updateMark("CO2011",40);
	a.updateMark("CO2012",80);
	a.updateMark("CO2015",80);
	a.updateMark("CO2016",40);
	a.updateMark("CO2017",40);
	a.updateMark("CO3101",60);
	a.updateMark("CO3102",60);
	a.updateMark("CO3105",60);
	a.updateMark("CO3002",59);
	a.updateMark("CO3093",59);
	a.updateMark("CO3201",59);
	s = a.calcDegClass();
	if (s != "UPPER SECOND CLASS")
		errorOut_("cwa>60 reported as "+s,1);

	a.updateMark("CO2006",60);
	a.updateMark("CO2015",60);
	a.updateMark("CO3201",56.5);
	s = a.calcDegClass();
	if (s != "LOWER SECOND CLASS")
		errorOut_("cwa<57 reported as "+s,1);
	a.updateMark("CO2006",80);
	a.updateMark("CO2015",80);

	a.updateMark("CO3002",59.6);
	a.updateMark("CO3201",50);
	s = a.calcDegClass();
	if (s != "UPPER SECOND CLASS")
		errorOut_("cwa>57 and 120cr>60 reported as "+s,2);

	a.updateMark("CO3002",59.4);
	a.updateMark("CO3201",44);
	s = a.calcDegClass();
	if (s != "LOWER SECOND CLASS")
		errorOut_("cwa<57 and 105cr>60 reported as "+s,2);

	a.updateMark("CO2001",60);
	a.updateMark("CO2006",60);
	a.updateMark("CO2008",40);
	a.updateMark("CO2011",40);
	a.updateMark("CO2012",60);
	a.updateMark("CO2015",60);
	a.updateMark("CO2016",40);
	a.updateMark("CO2017",40);
	a.updateMark("CO3101",50);
	a.updateMark("CO3102",50);
	a.updateMark("CO3105",50);
	a.updateMark("CO3002",49);
	a.updateMark("CO3093",49);
	a.updateMark("CO3201",49);
	s = a.calcDegClass();
	if (s != "LOWER SECOND CLASS")
		errorOut_("cwa>50 reported as "+s,1);

	a.updateMark("CO3002",50);
	a.updateMark("CO3201",40);
	s = a.calcDegClass();
	if (s != "LOWER SECOND CLASS")
		errorOut_("cwa>47 and 120cr>50 reported as "+s,2);

	a.updateMark("CO3002",49.4);
	a.updateMark("CO3201",34.6);
	s = a.calcDegClass();
	if (s != "THIRD CLASS")
		errorOut_("cwa<47 and 105cr>50 reported as "+s,2);

	a.updateMark("CO2001",39.6);
	a.updateMark("CO2006",40);
	a.updateMark("CO2008",40);
	a.updateMark("CO2011",40);
	a.updateMark("CO2012",40);
	a.updateMark("CO2015",40);
	a.updateMark("CO2016",40);
	a.updateMark("CO2017",40);
	a.updateMark("CO3101",40);
	a.updateMark("CO3102",40);
	a.updateMark("CO3105",40);
	a.updateMark("CO3002",40);
	a.updateMark("CO3093",40);
	a.updateMark("CO3201",39.6);
	s = a.calcDegClass();
	if (s != "THIRD CLASS")
		errorOut_("cwa>40 reported as "+s,1);
	// no 2nd route at 3rd cls

	passOut_();
}

// deg class bscold2: borderline, dropped cls
void StudentTester::testp() {
	funcname_ = "StudentTester::testp";

	string s;
	BScStudentOld a("");
	a.addModule("CO2001",65);
	a.addModule("CO2006",65);
	a.addModule("CO2008",65);
	a.addModule("CO2011",65);
	a.addModule("CO2012",70);
	a.addModule("CO2015",70);
	a.addModule("CO2016",72);
	a.addModule("CO2017",72);
	a.addModule("CO3101",70);
	a.addModule("CO3102",70);
	a.addModule("CO3105",68);
	a.addModule("CO3002",68);
	a.addModule("CO3093",65);
	a.addModule("CO3201",65);
	s = a.calcDegClass();
	if (s != "BORDERLINE FIRST CLASS")
		errorOut_("borderline 1st reported as "+s,1);

	a.updateMark("CO2016",70);
	a.updateMark("CO2015",34);
	a.updateMark("CO2017",34);
	a.updateMark("CO3105",94);
	a.updateMark("CO3002",94);
	s = a.calcDegClass();
	if (s != "UPPER SECOND CLASS")
		errorOut_("dropping to 2:1 due to fail reported as "+s,2);

	a.updateMark("CO2001",55);
	a.updateMark("CO2006",55);
	a.updateMark("CO2008",55);
	a.updateMark("CO2011",55);
	a.updateMark("CO2012",60);
	a.updateMark("CO2015",60);
	a.updateMark("CO2016",62);
	a.updateMark("CO2017",62);
	a.updateMark("CO3101",60);
	a.updateMark("CO3102",60);
	a.updateMark("CO3105",58);
	a.updateMark("CO3002",58);
	a.updateMark("CO3093",55);
	a.updateMark("CO3201",55);
	s = a.calcDegClass();
	if (s != "BORDERLINE UPPER SECOND CLASS")
		errorOut_("borderline 2:1 reported as "+s,1);

	a.updateMark("CO2016",60);
	a.updateMark("CO2015",34);
	a.updateMark("CO2017",34);
	a.updateMark("CO3105",77.3);
	a.updateMark("CO3002",77.3);
	s = a.calcDegClass();
	if (s != "LOWER SECOND CLASS")
		errorOut_("dropping to 2:2 due to fail reported as "+s,2);

	a.updateMark("CO2001",45);
	a.updateMark("CO2006",45);
	a.updateMark("CO2008",45);
	a.updateMark("CO2011",45);
	a.updateMark("CO2012",50);
	a.updateMark("CO2015",50);
	a.updateMark("CO2016",52);
	a.updateMark("CO2017",52);
	a.updateMark("CO3101",50);
	a.updateMark("CO3102",50);
	a.updateMark("CO3105",48);
	a.updateMark("CO3002",48);
	a.updateMark("CO3093",45);
	a.updateMark("CO3201",45);
	s = a.calcDegClass();
	if (s != "BORDERLINE LOWER SECOND CLASS")
		errorOut_("borderline 2:2 reported as"+s,1);

	a.updateMark("CO2016",50);
	a.updateMark("CO2015",34);
	a.updateMark("CO2017",34);
	a.updateMark("CO3105",60);
	a.updateMark("CO3002",60);
	s = a.calcDegClass();
	if (s != "THIRD CLASS")
		errorOut_("dropping to 3rd due to fail reported as "+s,2);

	passOut_();
}

// deg class bscold3: pass, fail, compensation
void StudentTester::testq() {
	funcname_ = "StudentTester::testq";

	string s;
	BScStudentOld a("");
	a.addModule("CO2001",41);
	a.addModule("CO2006",40);
	a.addModule("CO2008",40);
	a.addModule("CO2011",40);
	a.addModule("CO2012",40);
	a.addModule("CO2015",40);
	a.addModule("CO2016",40);
	a.addModule("CO2017",40);
	a.addModule("CO3101",40);
	a.addModule("CO3102",40);
	a.addModule("CO3105",40);
	a.addModule("CO3002",40);
	a.addModule("CO3093",40);
	s = a.calcDegClass();
	if (s != "INSUFFICIENT CREDITS")
		errorOut_("insufficient credits reported as "+s,1);

	a.addModule("CO3201",15);
	s = a.calcDegClass();
	if (s != "FAIL")
		errorOut_("cwa<35 reported as "+s,1);

	// failing credits >= 50, compensatable but cwa not high enough
	a.updateMark("CO3093",39.3);
	a.updateMark("CO3201",35);
	s = a.calcDegClass();
	if (s != "FAIL")
		errorOut_("fail credits >= 50 reported as "+s,2);

	// failing credits >= 50, cwa high enough but uncompensatable range
	a.updateMark("CO2017",34.3);
	a.updateMark("CO3002",34.3);
	a.updateMark("CO3093",34.3);
	a.updateMark("CO3201",50);
	s = a.calcDegClass();
	if (s != "FAIL")
		errorOut_("bad fail credits >= 50 reported as "+s,2);

	a.updateMark("CO2015",40);
	a.updateMark("CO2017",40);
	a.updateMark("CO3101",40);
	a.updateMark("CO3102",40);
	a.updateMark("CO3105",40);
	a.updateMark("CO3002",40);
	a.updateMark("CO3093",40);
	a.updateMark("CO3201",19);
	s = a.calcDegClass();
	if (s != "PASS")
		errorOut_("cwa>35 reported as "+s,1);

	passOut_();
}

// deg class bscnew1: 2 basic routes
void StudentTester::testr() {
	funcname_ = "StudentTester::testr";

	string s;
	BScStudentNew a("");
	a.addModule("CO2101",100);
	a.addModule("CO2102",100);
	a.addModule("CO2104",40);
	a.addModule("CO2106",40);
	a.addModule("CO2103",100);
	a.addModule("CO2201",40);
	a.addModule("CO3101",70.3);
	a.addModule("CO3102",70.3);
	a.addModule("CO3105",70.3);
	a.addModule("CO3002",69.9);
	a.addModule("CO3093",69.9);
	a.addModule("CO3201",69.9);
	s = a.calcDegClass();
	if (s != "FIRST CLASS")
		errorOut_("cwa>70 reported as "+s,1);

	a.updateMark("CO3201",61);
	s = a.calcDegClass();
	if (s != "UPPER SECOND CLASS")
		errorOut_("cwa<68 reported as " + s,1);

	a.updateMark("CO3002",70.1);
	a.updateMark("CO3201",63);
	s = a.calcDegClass();
	if (s != "FIRST CLASS")
		errorOut_("cwa>68 and 120cr>70 reported as "+s,2);

	a.updateMark("CO3002",66);
	s = a.calcDegClass();
	if (s != "UPPER SECOND CLASS")
		errorOut_("cwa<68 and 105cr>70 reported as "+s,2);

	a.updateMark("CO2101",80);
	a.updateMark("CO2102",80);
	a.updateMark("CO2104",40);
	a.updateMark("CO2106",40);
	a.updateMark("CO2103",80);
	a.updateMark("CO2201",40);
	a.updateMark("CO3101",60.3);
	a.updateMark("CO3102",60.3);
	a.updateMark("CO3105",60.3);
	a.updateMark("CO3002",59.9);
	a.updateMark("CO3093",59.9);
	a.updateMark("CO3201",59.9);
	s = a.calcDegClass();
	if (s != "UPPER SECOND CLASS")
		errorOut_("cwa>60 reported as "+s,1);

	a.updateMark("CO3201",51);
	s = a.calcDegClass();
	if (s != "LOWER SECOND CLASS")
		errorOut_("cwa<60 reported as "+s,1);

	a.updateMark("CO3002",60.1);
	a.updateMark("CO3201",53);
	s = a.calcDegClass();
	if (s != "UPPER SECOND CLASS")
		errorOut_("cwa>58 and 120cr>60 reported as "+s,2);

	a.updateMark("CO3002",56);
	s = a.calcDegClass();
	if (s != "LOWER SECOND CLASS")
		errorOut_("cwa<58 and 105cr>60 reported as "+s,2);

	a.updateMark("CO2101",60);
	a.updateMark("CO2102",60);
	a.updateMark("CO2104",40);
	a.updateMark("CO2106",40);
	a.updateMark("CO2103",60);
	a.updateMark("CO2201",40);
	a.updateMark("CO3101",50.3);
	a.updateMark("CO3102",50.3);
	a.updateMark("CO3105",50.3);
	a.updateMark("CO3002",49.9);
	a.updateMark("CO3093",49.9);
	a.updateMark("CO3201",49.9);
	s = a.calcDegClass();
	if (s != "LOWER SECOND CLASS")
		errorOut_("cwa>50 reported as "+s,1);

	a.updateMark("CO3201",41);
	s = a.calcDegClass();
	if (s != "THIRD CLASS")
		errorOut_("cwa>50 reported as "+s,1);

	a.updateMark("CO3002",50.1);
	a.updateMark("CO3201",43);
	s = a.calcDegClass();
	if (s != "LOWER SECOND CLASS")
		errorOut_("cwa>48 and 120cr>50 reported as "+s,2);

	a.updateMark("CO3002",46);
	s = a.calcDegClass();
	if (s != "THIRD CLASS")
		errorOut_("cwa<48 and 105cr>50 reported as "+s,2);

	passOut_();
}

// deg class bscnew2: borderline, dropped cls, Y3 credits
void StudentTester::tests() {
	funcname_ = "StudentTester::tests";

	string s;
	BScStudentNew a("");
	a.addModule("CO2101",66);
	a.addModule("CO2102",70);
	a.addModule("CO2103",66);
	a.addModule("CO2104",66);
	a.addModule("CO2106",70);
	a.addModule("CO2201",70);
	a.addModule("CO3101",72);
	a.addModule("CO3102",72);
	a.addModule("CO3105",68);
	a.addModule("CO3002",68);
	a.addModule("CO3093",66);
	a.addModule("CO3201",66.1);
	s = a.calcDegClass();
	if (s != "BORDERLINE FIRST CLASS")
		errorOut_("borderline 1st reported as "+s,1);

	a.updateMark("CO3101",76);
	a.updateMark("CO3102",68);
	s = a.calcDegClass();
	if (s != "UPPER SECOND CLASS")
		errorOut_("dropping to 2:1 due to Y3cr reported as "+s,2);

	a.updateMark("CO2101",56);
	a.updateMark("CO2102",60);
	a.updateMark("CO2103",56);
	a.updateMark("CO2104",56);
	a.updateMark("CO2106",60);
	a.updateMark("CO2201",60);
	a.updateMark("CO3101",62);
	a.updateMark("CO3102",62);
	a.updateMark("CO3105",58);
	a.updateMark("CO3002",58);
	a.updateMark("CO3093",56);
	a.updateMark("CO3201",56.1);
	s = a.calcDegClass();
	if (s != "BORDERLINE UPPER SECOND CLASS")
		errorOut_("borderline 2:1 reported as "+s,1);

	a.updateMark("CO3101",66);
	a.updateMark("CO3102",58);
	s = a.calcDegClass();
	if (s != "LOWER SECOND CLASS")
		errorOut_("dropping to 2:2 due to Y3cr reported as "+s,2);

	a.updateMark("CO2101",46);
	a.updateMark("CO2102",50);
	a.updateMark("CO2103",46);
	a.updateMark("CO2104",46);
	a.updateMark("CO2106",50);
	a.updateMark("CO2201",50);
	a.updateMark("CO3101",52);
	a.updateMark("CO3102",52);
	a.updateMark("CO3105",48);
	a.updateMark("CO3002",48);
	a.updateMark("CO3093",46);
	a.updateMark("CO3201",46.1);
	s = a.calcDegClass();
	if (s != "BORDERLINE LOWER SECOND CLASS")
		errorOut_("borderline 2:2 reported as "+s,1);

	a.updateMark("CO3101",56);
	a.updateMark("CO3102",48);
	s = a.calcDegClass();
	if (s != "THIRD CLASS")
		errorOut_("dropping to 3rd due to Y3cr reported as "+s,2);

	passOut_();
}

// deg class bscnew3: 3rd/pass/fail
void StudentTester::testt() {
	funcname_ = "StudentTester::testt";

	string s;
	BScStudentNew a("");
	a.addModule("CO2101",40);
	a.addModule("CO2102",40);
	a.addModule("CO2103",40);
	a.addModule("CO2104",40);
	a.addModule("CO2106",40);
	a.addModule("CO2201",40);
	a.addModule("CO3101",40);
	a.addModule("CO3102",40);
	a.addModule("CO3105",40);
	a.addModule("CO3002",44);
	a.addModule("CO3093",39);
	s = a.calcDegClass();
	if (s != "INSUFFICIENT CREDITS")
		errorOut_("insufficients credit reported as "+s,1);
	a.addModule("CO3201",39.8);
	s = a.calcDegClass();
	if (s != "FAIL")
		errorOut_("failed >60crs reported as "+s,1);

	a.updateMark("CO3002",40);
	a.updateMark("CO3093",40);
	a.updateMark("CO3201",22);
	s = a.calcDegClass();
	if (s != "PASS")
		errorOut_("cwa>35 reported as " + s,2);

	a.updateMark("CO3201",30);
	s = a.calcDegClass();
	if (s != "PASS")
		errorOut_("cwa<38 reported as " + s,2);

	a.updateMark("CO3201",34);
	s = a.calcDegClass();
	if (s != "THIRD CLASS")
		errorOut_("cwa>38 and 120cr>40 reported as " + s,2);

	passOut_();
}

// deg class msc1
void StudentTester::testu() {
	funcname_ = "StudentTester::testu";

	string s;
	MScStudent a("");
	a.addModule("CO7214", 100);
	a.addModule("CO7215", 69);
	a.addModule("CO7216", 69);
	a.addModule("CO7217", 69);
	a.addModule("CO7218", 69);
	a.addModule("CO7105", 60);
	a.addModule("CO7210", 60);
	a.addModule("CO7099", 60);
	a.addModule("CO7201", 70);
	s = a.calcDegClass();
	if (s != "DISTINCTION")
		errorOut_("cwa>70 distinction reported as "+s,1);

	a.updateMark("CO7215", 62);
	s = a.calcDegClass();
	if (s != "MERIT")
		errorOut_("cwa<70 reported as "+s,1);

	a.updateMark("CO7215", 70);
	a.updateMark("CO7216", 70);
	a.updateMark("CO7217", 70);
	a.updateMark("CO7218", 50);
	a.updateMark("CO7105", 50);
	a.updateMark("CO7210", 50);
	a.updateMark("CO7099", 50);
	s = a.calcDegClass();
	if (s != "DISTINCTION")
		errorOut_("taught part 60cr distinction reported as "+s,1);

	a.updateMark("CO7215", 69);
	s = a.calcDegClass();
	if (s != "MERIT")
		errorOut_("taught part 45cr distinction reported as "+s,1);
	a.updateMark("CO7215", 70);

	a.updateMark("CO7201", 69);
	s = a.calcDegClass();
	if (s != "MERIT")
		errorOut_("project mark short of distinction reported as "+s,2);
	a.updateMark("CO7201", 70);

	a.updateMark("CO7099", 49);
	s = a.calcDegClass();
	if (s != "MERIT")
		errorOut_("dropped to merit due to narrow fail credits reported as "+s,2);

	a.updateMark("CO7210", 49);
	s = a.calcDegClass();
	if (s != "PASS")
		errorOut_("dropped to pass due to narrow fail credits reported as "+s,2);

	a.updateMark("CO7210", 39);
	s = a.calcDegClass();
	if (s != "FAIL")
		errorOut_("dropped to fail due to bad fail credits reported as "+s,2);

	passOut_();
}

// deg class msc2
void StudentTester::testv() {
	funcname_ = "StudentTester::testv";

	string s;
	MScStudent a("");
	a.addModule("CO7214", 90);
	a.addModule("CO7215", 59);
	a.addModule("CO7216", 59);
	a.addModule("CO7217", 59);
	a.addModule("CO7218", 59);
	a.addModule("CO7105", 50);
	a.addModule("CO7210", 50);
	a.addModule("CO7099", 50);
	a.addModule("CO7201", 60);
	s = a.calcDegClass();
	if (s != "MERIT")
		errorOut_("cwa>60 merit reported as "+s,1);

	a.updateMark("CO7215", 52);
	s = a.calcDegClass();
	if (s != "PASS")
		errorOut_("cwa<60 reported as "+s,1);

	a.updateMark("CO7214", 60);
	a.updateMark("CO7215", 60);
	a.updateMark("CO7216", 60);
	a.updateMark("CO7217", 60);
	a.updateMark("CO7218", 50);
	a.updateMark("CO7099", 49);
	s = a.calcDegClass();
	if (s != "MERIT")
		errorOut_("taught part 60 cr merit reported as "+s,1);

	a.updateMark("CO7214", 59);
	s = a.calcDegClass();
	if (s != "PASS")
		errorOut_("taught part 45 cr merit reported as "+s,1);
	a.updateMark("CO7214", 60);

	a.updateMark("CO7201", 59);
	s = a.calcDegClass();
	if (s != "PASS")
		errorOut_("project mark short of merit reported as "+s,2);
	a.updateMark("CO7201", 60);

	a.updateMark("CO7210", 49);
	s = a.calcDegClass();
	if (s != "PASS")
		errorOut_("dropped to pass due to narrow fail reported as "+s,2);

	a.updateMark("CO7210", 39);
	s = a.calcDegClass();
	if (s != "FAIL")
		errorOut_("dropped to fail due to bad fail reported as "+s,2);

	passOut_();
}

// deg class msc3
void StudentTester::testw() {
	funcname_ = "StudentTester::testw";

	string s;
	MScStudent a("");
	a.addModule("CO7214", 60);
	a.addModule("CO7215", 50);
	a.addModule("CO7216", 50);
	a.addModule("CO7217", 50);
	a.addModule("CO7218", 50);
	a.addModule("CO7105", 50);
	a.addModule("CO7210", 49);
	a.addModule("CO7201", 50);
	s = a.calcDegClass();
	if (s != "INSUFFICIENT CREDITS")
		errorOut_("insufficient credits reported as "+s,1);

	a.addModule("CO7099", 40);
	s = a.calcDegClass();
	if (s != "PASS")
		errorOut_("pass reported as "+s,1);

	// ocwa route is actually pointless, if NF<30cr then taught pass > 90cr!

	a.updateMark("CO7105", 49);
	s = a.calcDegClass();
	if (s != "FAIL")
		errorOut_("fail due to 45 narrow fail credits reported as "+s,2);

	a.updateMark("CO7105", 50);
	a.updateMark("CO7099", 39);
	s = a.calcDegClass();
	if (s != "FAIL")
		errorOut_("fail due to bad fail credits reported as "+s,2);

	a.updateMark("CO7099", 40);
	a.updateMark("CO7201", 49);
	s = a.calcDegClass();
	if (s != "FAIL")
		errorOut_("fail due to project reported as "+s,2);

	passOut_();
}

// <<
void StudentTester::testx() {
	funcname_ = "StudentTester::testx";

	MScStudent a("alice");
	a.addModule("CO7FAK",50.5);
	a.addModule("CO7201",50.5);
	stringstream ss;
	ss << a;
	string s = ss.str();
	if (s != "alice\tPASS")
		errorOut_("output stream \"alice\tPASS\" reported as "+s,0);

	passOut_();
}

// <<, deg class polymorphic
void StudentTester::testy() {
	funcname_ = "StudentTester::testy";

	Student* students[2];
	students[0] = new BScStudentOld("alice");
	students[1] = new BScStudentNew("bob");
	for(int i=0;i<2;i++) {
		students[i]->addModule("CO2001",70);
		students[i]->addModule("CO2002",65);
		students[i]->addModule("CO2006",70);
		students[i]->addModule("CO2011",65);
		students[i]->addModule("CO2012",70);
		students[i]->addModule("CO2015",70);
		students[i]->addModule("CO2016",65);
		students[i]->addModule("CO2017",65);
		students[i]->addModule("CO3101",70);
		students[i]->addModule("CO3102",70);
		students[i]->addModule("CO3103",70);
		students[i]->addModule("CO3105",70);
		students[i]->addModule("CO3099",65);
		students[i]->addModule("CO3202",65);
	}
	string s;
	s = students[0]->calcDegClass();
	if (s != "FIRST CLASS")
		errorOut_("alice 1st class reported as "+s,1);
	s = students[1]->calcDegClass();
	if (s != "UPPER SECOND CLASS")
		errorOut_("bob 2:1 reported as "+s,1);

	stringstream ssa, ssb;
	ssa << (*students[0]);
	ssb << (*students[1]);
	s = ssa.str();
	if (s != "alice\tFIRST CLASS")
		errorOut_("alice output stream reported as "+s,2);
	s = ssb.str();
	if (s != "bob\tUPPER SECOND CLASS")
		errorOut_("bob output stream reported as "+s,2);

	passOut_();
}

void StudentTester::errorOut_(const string& errMsg, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail";
	cerr << errBit;
	cerr << ": " << errMsg << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void StudentTester::passOut_() {

	if (!error_) {
		cerr << funcname_ << ":" << " pass" << endl;
	}
	cerr << std::flush;
}

bool StudentTester::approxEq(float f1, float f2) {

	if (fabs(f1-f2) < 0.01) return true;
	else return false;
}
