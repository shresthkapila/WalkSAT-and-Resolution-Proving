#include <iostream>
#include <stdlib.h>
using namespace std;
#include <string>
#include <vector>
#include <cstdlib>
#include <utility>
#include <map>
#include "propositionalTP.h"
//#pragma once


//Constructor
propositionalTP::propositionalTP() {
}

//Destructor
propositionalTP::~propositionalTP() {
}

//getters and setters
int propositionalTP::getNoOfClauses() const {
    return this->noOfClauses;
}

int propositionalTP::getNoOfVariables() const {
    return this->noOfVariables;
}
map<string, set<int> > propositionalTP::getClauseMapping() const {
    return this->clauseMapping;
}
void propositionalTP::setNoOfClauses(int noOfClauses) {
    this->noOfClauses = noOfClauses;
}
void propositionalTP::setNoOfVariables(int noOfVariables) {
    this->noOfVariables = noOfVariables;
}
void propositionalTP::setClauseMapping(std::map<std::string, std::set<int> >clauseMapping) {
    this->clauseMapping = clauseMapping;
}
//Additional functions

bool propositionalTP::algorithm(){
    int size;
    map<string, set<int> > next, current;
    bool flag = true;
    while(flag){
        size = next.size();
        auto i = this->clauseMapping.begin();
        while(i != this->clauseMapping.end()){
            auto j = i;
            while(j!= this->clauseMapping.end()){
                current = solver(i->second, j->second);
                //cout<<"before if"<<endl;
                if(current.count("P") > 0){
                    //cout<<"before if"<<endl;
                    return false;
                }//cout<<"after if"<<endl;
                next.insert(current.begin(), current.end());
                j++;
            }
            i++;
        }
        if(next.size() == size){
            return true;
        }else{
            this->clauseMapping.insert(next.begin(), next.end());
        }
    }

}

map<string, set<int> > propositionalTP::solver(const set<int> & current, const set<int> & next ){
     map<std::string, set<int> > curerentCopy;
     set<int> nextCopy, tempCl;
     auto i = current.begin();
     while(i != current.end()){
            auto j = next.begin();
            while(j!= next.end()){
                if((*j) == ((*i)*-1)){
                    nextCopy = current;
                    tempCl = next;
                    nextCopy.erase(*i);
                    tempCl.erase(*j);
                    tempCl.insert(nextCopy.begin(), nextCopy.end());
                    curerentCopy.insert(make_pair(toString(tempCl),tempCl));
                }
                j++;
            }
            i++;
        }
    return curerentCopy;
}

string propositionalTP::toString(const set<int> &row){
    string temp = "P";
    auto i = row.begin();
    while(i != row.end()){
        temp = temp + " " + to_string(*i);
        i++;
    }
    return temp;
}

void propositionalTP::display(){
    auto i = this->clauseMapping.begin();
    i++;
    while(i!= this->clauseMapping.end()){
        cout << i->first << endl;
        i++; 
    }
}
