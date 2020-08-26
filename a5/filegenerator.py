#!/usr/bin/env python
# coding: utf-8

# In[2]:


import random as rand
from random import choice


# file handling tutorial link : https://www.guru99.com/reading-and-writing-files-in-python.html


# In[3]:


def listgenrator(n):
    '''
    Genrates a list (-n:n) 
    '''
    randomlist = []
    for i in range(n):
        randomlist.append(-1 * int(i + 1))
    for i in range(n):
        randomlist.append(int(i + 1))
    return randomlist


# In[23]:


# p cnf <num_vbles> <num_clauses>
# p cnf var clauses
def fileGenerator(N, var, clauses, filename):
    filename = "files/"+filename
    file = open(filename, 'w')
    file.write("p cnf " + str(var) + " " + str(clauses) + "\n")
    for col in range(int(clauses)):
        List = listgenrator(int(var))
        for row in range(int(N)):
            ##SDF
            val = choice(List)
            List.remove(val)
            file.write(str(val) + " ")
        file.write('0\n')

    file.close()


# In[24]:


def main():
    filename = input("Enter filename: ")
    N = input("Enter no. of literals: ")
    Variables = input("Enter no. of Variables, symbols have to be greater than N: ")
    clauses = input("Enter no. of clauses: ")
    fileGenerator(N, Variables, clauses, filename)


if __name__ == '__main__':
    main()
