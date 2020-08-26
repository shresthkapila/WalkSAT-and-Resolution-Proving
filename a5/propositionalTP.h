#include <iostream>
#include <map>
#include <set>
using namespace std;
#pragma once

#ifndef __propositionalTP_H___
#define __propositionalTP_H___

class propositionalTP {
    private:
        int noOfClauses;
        int noOfVariables;
        map<string, set<int> > clauseMapping;

    public:
        // Constructors
        propositionalTP();

        //Destructor
        ~propositionalTP();

        //getters and setters
        int getNoOfClauses() const;
        int getNoOfVariables() const;
        map<string, set<int> > getClauseMapping() const;
        void setNoOfClauses(int noOfClauses);
        void setNoOfVariables(int noOfVariables);
        void setClauseMapping(map<string, set<int> > clauseMapping);

        // additional functions
        bool algorithm();
        void display();
        map<string, set<int> > solver(const set<int> &, const set<int> &);
        string toString(const set<int> &row);

        
};

#endif