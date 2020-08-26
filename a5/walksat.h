#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
using namespace std;

#ifndef _WALKSAT_H_
#define _WALKSAT_H_

#pragma once

class walksat {
public:
	set<string> unsatisfiedClause;
	int noOfClauses;
    int noOfVariables;
    map<string, vector<int> > clauseMapping;

	walksat();
	~walksat();
	map<int,bool> algorithm(); 
	void display(const map<int,bool> &);
	bool check(const map<int,bool> &dictionary);
	bool clauseCheck(const map<int,bool> &dictionary, const vector<int> &);
	int getUnsatisfiesClauses(map<int,bool> &dictionary, int var); 
	bool checkSymbol(vector<int> &, int sy);
	string toString(const vector<int> &row);
};

#endif