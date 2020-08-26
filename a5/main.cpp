#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <cstdlib>
#include <assert.h>
using namespace std;

#include "propositionalTP.h"
#include "walksat.h"

// splitting a string using delementer : https://www.techiedelight.com/split-string-cpp-using-delimiter/
vector<string> split(string &row) {
    vector<string> vari;
    size_t begin, end = 0;
    while((begin = row.find_first_not_of(' ', end)) != string::npos){
        end = row.find(' ', begin);
        vari.push_back(row.substr(begin,end-begin));
    }
   return vari;
}


set<int> toInteger(vector<string> &attribute){
    set<int> row;
    for(int i = 0; i < attribute.size(); ++i){
         row.insert(stoi(attribute[i]));
    }
    return row;
}

string tostring(const set<int> &row){
    string temp = "P";
    auto i = row.begin();
    while(i != row.end()){
        temp += " ";
        temp += to_string(*i);;
        i++;
    }
    return temp;
}

string tostring1(const vector<int> &row){
	string temp = "P";
    auto i = 0;
    while(i <= row.size()){
        temp += " ";
        temp += to_string(row[i]);
        i++;
    }
    return temp;
}
 
int main() {
    bool flag = false;
    char fileName[] = "files/cnf2-4-200.txt";
    string line;
    ifstream file(fileName);
    char c = ' ';
    int var,cl;
    
    cout << "******************************"<<endl;
    cout << "What would you like to test?"<<endl;
    cout << "\t\t1. Walksat"<<endl;
    cout << "\t\t2. Resolution Proving"<<endl;
    cout << "\tEnter your choice. 1 or 2 : ";
    int choice;
    cin >> choice;

    while (!flag) {
        if (choice == 1){
            flag = true;
            map<string, vector<int> > allClauses;
            if (file.is_open()) {
                // Generating first line
                getline(file, line);
                vector<string> attributes = split(line);
                var = stoi(attributes[2]);
                cl = stoi(attributes[3]);
                int i = 0;
                while (i < cl) {
                    //Generating each line
                    getline(file, line);
                    vector<string> attributes = split(line);

                    vector<int> row;
                    for(int j=0;j<=attributes.size()-1;j++){
                        row.push_back(stoi(attributes[j]));
                    }

                    pair<string, vector<int> > clausePair;
                    clausePair = make_pair(tostring1(row), row);
                    allClauses.insert(clausePair);
                    i++;
                }
                file.close();
            }
            //walksat
            walksat sat;
            sat.clauseMapping = allClauses;
            sat.noOfClauses = cl;
            sat.noOfVariables = var;

            // HINT: https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
            clock_t start, end;
            // cout<<"XXXXX----done-------XXXXXX"<<endl;
            start = clock(); 
            ios_base::sync_with_stdio(false);
            map<int,bool> ret = sat.algorithm();
            end= clock(); 
            // cout<<"XXXXX----done-------XXXXXX"<<endl;
            double timeTaken = double(end-start)/ double(CLOCKS_PER_SEC);
            cout << "Time elapsed (in seconds): " << fixed << timeTaken << setprecision(5)<< " seconds." <<endl;
            // sat.display(ret);
        }
        else if (choice == 2){
            flag = true;
            map<string, set<int> > allClauses;
            if (file.is_open()) {
                // Generating first line
                getline(file, line);
                vector<string> attributes = split(line);
                var = stoi(attributes[2]);
                cl = stoi(attributes[3]);
                
                int length, i = 0;
                while (i < cl) {
                    //Generating each line
                    getline(file, line);
                    vector<string> attributes = split(line);
                    length = attributes.size();

                    if (attributes[length-1] != "0") {
                        cout<< "file data error" ;
                        exit(0); 
                    }
                    attributes.pop_back();
                    set<int> clauseSet = toInteger(attributes);
                    pair<string, set<int> > clausePair;

                    for (int k=0 ; k < length-1 ; k++) {
                        clausePair = make_pair(tostring(clauseSet), clauseSet);
                        allClauses.insert(clausePair);
                    } 
                    i++;
                }
                file.close();
            }
            //resolution proving
            propositionalTP* ptp = new propositionalTP();
            ptp->setNoOfVariables(var);
            ptp->setNoOfClauses(cl);
            ptp->setClauseMapping(allClauses);

            // HINT: https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
            clock_t start, end;
            // cout<<"XXXXX----done-------XXXXXX"<<endl;
            start = clock(); 
            ios_base::sync_with_stdio(false);
            bool out = ptp->algorithm();
            end= clock(); 
            // cout<<"XXXXX----done-------XXXXXX"<<endl;
            double timeTaken = double(end-start)/ double(CLOCKS_PER_SEC);
            cout << "Time elapsed (in seconds): " << fixed << timeTaken << setprecision(5)<< " seconds." <<endl;
            // cout<<"result : "<<out<<endl;
            delete ptp;
        }
        else {
            cout << "ERROR : Enter a valid input (1 or 2) : ";
            cin >> choice;
            continue;
        }
    }
    
    return 0;
}