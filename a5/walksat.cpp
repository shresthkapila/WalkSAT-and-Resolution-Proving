#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include <random>
#include "walksat.h"
using namespace std;

walksat::walksat(){}
walksat::~walksat(){}

map<int,bool> walksat::algorithm(){
	map<int,bool> dictionary;
	int flips;
	// cout<<"XXXXX----done-------XXXXXX"<<endl;
	srand(time(NULL));
	for (int i = 0; i < this->noOfVariables; ++i){
		if(rand()%2 == 0){
			dictionary[i+1] = true;
		}else{
			dictionary[i+1] = false;
		}
	}
	// all clauses to unsatisfied
	auto i = clauseMapping.begin();
	while(i != clauseMapping.end()){
		if (!clauseCheck(dictionary, i->second)){
			unsatisfiedClause.insert(i->first);
		}
		i++;
	}
	flips = 10000;
	while(flips != 0) {
		flips -= 1;
		bool flag = unsatisfiedClause.empty();
		if (flag == true) {
			return dictionary;
		}

		// TODO : clause = random.choice(unsatisfied)
		auto randomClause = unsatisfiedClause.begin(); 
		// HINT:  http://www.cplusplus.com/forum/beginner/35440/
		auto ithVal = rand()%(unsatisfiedClause.size());
		// HINT : https://stackoverflow.com/questions/5848041/access-to-nth-element-of-set (moving to nth value of set)
		advance(randomClause, ithVal);
		auto clause = clauseMapping[*randomClause];

		// HINT: https://stackoverflow.com/questions/686353/random-float-number-generation
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		int current;
		if (r < 0.5) {
			int clRand = rand()%clause.size();
			current = abs(clause[clRand]);
		}
		else {
			int currentMin = noOfClauses;
			int variable, ctrChanges, i=0;
			while (i < clause.size()) {
				variable = clause[i];
				variable = abs(variable);
				ctrChanges = getUnsatisfiesClauses(dictionary, variable);
				if (currentMin > ctrChanges) {
					currentMin = ctrChanges;
					current = variable; 
				}
				i+=1;
			}
		}
		bool flag2 = dictionary[current];
		dictionary[current] = !flag2;
	}
	map<int,bool> ret;
	ret[0] = false;
	return ret;
}

void walksat::display(const map<int,bool> &dictionary){
	map<int,bool> dictionaryCopy = dictionary;
	// hint of using const_iterator : http://www.cplusplus.com/forum/beginner/126145/
	map<int,bool>::const_iterator i = dictionaryCopy.begin();
	while(i != dictionaryCopy.end()){
		cout<<"first : " << i->first <<"   Second : " << i->second << endl;
		i++;
	}
}

bool walksat::check(const map<int,bool> &dictionary){
	auto i = clauseMapping.begin();
	while(i != clauseMapping.end()){
		if (!clauseCheck(dictionary, i->second)){
			return false;
		}
		i++;
	}
	return true;
}

bool walksat::clauseCheck(const map<int,bool> &dictionary, const vector<int> & row){
	// hint of using const_iterator : http://www.cplusplus.com/forum/beginner/126145/
	vector<int>::const_iterator i = row.begin();
	while(i != row.end()){
		//cout<<"3.XXXXX----done-------XXXXXX"<<endl;
		 if (((*i < 0) && (!dictionary.at(abs(*i)))) || ((*i > 0) && (dictionary.at(abs(*i)))) ) 
		 {
		 	return true;
		 }
		i++;
	}
	
	//cout<<"4. XXXXX----done-------XXXXXX"<<endl;
	return false;
}


int walksat::getUnsatisfiesClauses(map<int,bool> &dictionary, int variable){
	bool flag = dictionary[variable];
	dictionary[variable] = !flag;
	int temp = 0;
	auto i = clauseMapping.begin();
	while(i != clauseMapping.end()){
		if(checkSymbol(i->second, variable)){
			bool f = clauseCheck(dictionary, i->second);
			auto unsatVal = unsatisfiedClause.find(i->first);
			if (f && (unsatVal != unsatisfiedClause.end())){
				temp -= 1;
			}else if(!f && (unsatVal== unsatisfiedClause.end())) {
				temp += 1;
			}
		}
		i++;
	}
	flag = dictionary[variable];
	dictionary[variable] = !flag;
	return temp;
}


bool walksat::checkSymbol(vector<int> &row, int sy){
	int i = 0;
	while(i < row.size() ){
		int positiveVal = abs(row[i]);
		if(positiveVal == sy) {
			return true;
		}
		i++;
	}
	return false;
}
string walksat::toString(const vector<int> &row){
	string temp = "P";
    auto i = 0;
    while(i <= row.size()){
        temp = temp + " " + to_string(row[i]);
        i++;
    }
    return temp;
}