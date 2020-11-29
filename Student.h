#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
#include<map>
#include <string>
#include "Module.h"
using std::istream;
using std::ostream;
using std::string;

const int MAX_MODULES = 20; // should you need to use something like this
const int BSC_YEAR_CREDIT = 120;
const int MSC_YEAR_CREDIT = 180;

class Student {

public:
	// Default constructor, just to make this release version compilable.
	// If your implementation is correct this should be removed
	Student();

	// Constructor, with student's userid as argument
	Student(const string& uid);

	// If you need non-default versions of destructors, copy constructors
	// etc. please define yourself. Here I assume the default versions
	// are ok. You will not be tested on copy constructing/assigning.

	// Add this module to the student, with the given mark.
	// If moduleCode does not exist in the MCT table,
	// or if the module is of the wrong year group for this student,
	// or if the student already have this module,
	// or if adding this module exceeds the total credits of this year,
	// do nothing and return false. Otherwise return true.
	virtual bool addModule(string moduleCode, float mark);

	// Update the mark of this module.
	// If moduleCode does not appear in the MCT table,
	// or if the student have not already added this module,
	// do nothing and return false. Otherwise return true.
	virtual bool updateMark(string moduleCode, float mark);

	// Returns the CWA of the student taking all the modules added so
	// far into account.
	// For BSc students it is a weighted average of Y2 and Y3 CWAs.
	// For MSc students it is a weighted average of all modules.
	// It should still calculate even if not a whole year worth of
	// modules have been added.
	// If no modules have been added so far, return 0.
	virtual float cwa() const;

	// Returns a string which is one of the degree classification
	// results (see webpage for details).
	// If insufficient credits have been entered, return
	// "INSUFFICIENT CREDITS".
	virtual string calcDegClass() const;

	// TODO: add any protected/private member variables

	// The input stream operator, that reads module code and marks from the
	// input stream and add it to the student as done by addModule().
	// In situations where addModule() would have returned false, do not add
	// and quietly move on to the next module.
	friend istream& operator>>(istream& is, Student& student);

	// The output stream operator, printing uid and degree class info
	// of the student as specified in the webpage.
	friend ostream& operator<<(ostream& os, const Student& student);
};

class BScStudent : public Student {
public:
	// similar comment to Student default constructor applies
	BScStudent();

	BScStudent(const string& uid);

	// CWA for Y2 and Y3 respectively.
	// Same rules as Student::cwa() regarding not having a whole year's
	// worth of modules applies here.
	virtual float y2cwa() const;
	virtual float y3cwa() const;

	// TODO: you may need to override some functions in the base class
	bool addModule(string moduleCode, float mark);
    bool updateMark(string moduleCode, float mark);
    float cwa() const;
	string calcDegClass() const;


	// TODO: add any protected/private member variables
};

class BScStudentOld : public BScStudent {
private:
    map<string , float> mp1;
	string name;
public:
	BScStudentOld(const string& uid){
        name = uid;
	}

	// TODO: you may need to override some functions in the base class
    bool addModule(string moduleCode, float mark){
       if(MCT.find(moduleCode) == MCT.end()){
		   return false;
	   }
	   if(moduleCode[2] != 3 || moduleCode[2] != 2){
		   return false;
	   }
	   if(mp1.find(moduleCode) != mp1.end()){
		   return false;
	   }
	   int sum=0;
	   for(auto x : mp1){
          sum += MCT.at(x.first);
	   }
	   sum += MCT.at(moduleCode);
	   if(sum > 120){
		   return false;
	   }
	   mp1.insert({moduleCode , mark});
	   return true;
	}
    bool updateMark(string moduleCode, float mark){
		if(MCT.find(moduleCode) == MCT.end()){
			return false;
		}
		if(mp1.find(moduleCode) == mp1.end()){
			return false;
		}
		mp1[moduleCode] = mark;
		return true;
	}
	float y2cwa() const{
		float ans = 0.0;
		for(auto x : mp1){
			string code = x.first;
			if(code[2] == '2'){
			    ans += (MCT.at(x.first)*x.second);
			}
		}
		ans = ans/120;
		return ans;
	}
	float y3cwa() const{
		float ans = 0.0;
		for(auto x : mp1){
			string code = x.first;
			if(code[2] == '3'){
			    ans += (MCT.at(x.first)*x.second);
			}
		}
		ans = ans/120;
		return ans;
	}
	float cwa() const{
		return 0.4*y2cwa() + 0.6*y3cwa();
	}
	string calcDegClass() const{
		int fail_cred = 0;
		int cred = 0;
		for(auto x : mp1){
			string code = x.first;
            float m = x.second;
			char y = code[2];
			cred += MCT.at(code);
			if(y == '2'){
				if(m>=39.50 || (m>=34.50 && y2cwa() >= 39.50)){
					continue;
				}else{
					fail_cred += MCT.at(code);
				}
			}
			if(y == '3'){
				if(m>=39.50 || (m>=34.50 && y2cwa() >= 39.50)){
					continue;
				}else{
					fail_cred += MCT.at(code);
				}
			}
		}
	}
	// TODO: add any protected/private member variables
};

class BScStudentNew : public BScStudent {
private:
    string name;
    map<string , float> mp2;
public:
	BScStudentNew(const string& uid){
		name = uid;
	}

	// TODO: you may need to override some functions in the base class
	bool addModule(string moduleCode, float mark){
       if(MCT.find(moduleCode) == MCT.end()){
		   return false;
	   }
	   if(moduleCode[2] != 3 || moduleCode[2] != 2){
		   return false;
	   }
	   if(mp2.find(moduleCode) != mp2.end()){
		   return false;
	   }
	   int sum=0;
	   for(auto x : mp2){
          sum += MCT.at(x.first);
	   }
	   sum += MCT.at(moduleCode);
	   if(sum > 120){
		   return false;
	   }
	   mp2.insert({moduleCode , mark});
	   return true;
	}
    bool updateMark(string moduleCode, float mark){
		if(MCT.find(moduleCode) == MCT.end()){
			return false;
		}
		if(mp2.find(moduleCode) == mp2.end()){
			return false;
		}
		mp2[moduleCode] = mark;
		return true;
	}
	float y2cwa() const{
		float ans = 0.0;
		for(auto x : mp2){
			string code = x.first;
			if(code[2] == '2'){
			    ans += (MCT.at(x.first)*x.second);
			}
		}
		ans = ans/120;
		return ans;
	}
	float y3cwa() const{
		float ans = 0.0;
		for(auto x : mp2){
			string code = x.first;
			if(code[2] == '3'){
			    ans += (MCT.at(x.first)*x.second);
			}
		}
		ans = ans/120;
		return ans;
	}
	float cwa() const{
		return 0.33*y2cwa() + 0.67*y3cwa();
	}
	string calcDegClass() const{
		int fail_cred = 0;
		int cred = 0;
		for(auto x : mp2){
			string code = x.first;
            float m = x.second;
			char y = code[2];
			cred += MCT.at(code);
			if(y == '2'){
				if(m>=40){
					continue;
				}else{
					fail_cred += MCT.at(code);
				}
			}
			if(y == '3'){
				if(m>=40){
					continue;
				}else{
					fail_cred += MCT.at(code);
				}
			}
		}
	}

	// TODO: add any protected/private member variables
};

class MScStudent : public Student {
private:
    string name;
    map<string , float> mp;
public:
	MScStudent(const string& uid){
		name = uid;
	}

	// TODO: you may need to override some functions in the base class
    bool addModule(string moduleCode , float mark){
       if(MCT.find(moduleCode) == MCT.end()){
		   return false;
	   }
	   if(moduleCode[2] != 7){
		   return false;
	   }
	   if(mp.find(moduleCode) != mp.end()){
		   return false;
	   }
	   int sum=0;
	   for(auto x : mp){
          sum += MCT.at(x.first);
	   }
	   sum += MCT.at(moduleCode);
	   if(sum > 180){
		   return false;
	   }
	   mp.insert({moduleCode , mark});
	   return true;
	}
	bool updateModule(string moduleCode , float mark){
		if(MCT.find(moduleCode) == MCT.end()){
			return false;
		}
		if(mp.find(moduleCode) == mp.end()){
			return false;
		}
		mp[moduleCode] = mark;
		return true;
	}
	float cwa() const{
		if(mp.size() == 0){
			return 0;
		}
		float ans = 0.0;
		for(auto x : mp){
			ans += (MCT.at(x.first)*x.second);
		}
		ans = ans/180.0;
		return ans;
	}
	string calcDegClass() const{
            
	}

	// TODO: add any protected/private member variables
};

#endif