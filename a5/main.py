import random
import time
import copy

allClauses = []
variables = set()

# Code from AIMAPYTHON logic.py

def fileOpener(path, RunType):
    ALL = open(path, 'r')
    stats = ALL.readline().split()
    noOfClauses = int(stats[3])
    for i in range(noOfClauses):
        rows = []
        for row in ALL.readline().split():
            rows.append(int(row))
        # print(rows)
        if rows.pop() is not 0:
            print("wrong input format. File should be use the minisat input format !")
        for i in rows:
            variables.add(abs(i))

        if RunType is "Walksat":
            allClauses.append(rows)
    
        elif RunType is "RP":
            cl = ""
            for var in rows:
                if var is rows[len(rows)-1]:
                    cl = cl + str(var)
                else:
                    cl = cl + str(var) + ' '

            allClauses.append(cl)
        

def pl_true(model, rows):
    for row in rows:
        if (row < 0 and model[abs(row)] is False) or (row > 0 and model[row] is True) :
            return True
    return False

def probability(p):
    """Return true with probability p."""
    return p > random.uniform(0.0, 1.0)

def WalkSAT(p=0.5, max_flips=10000):
    # model is a random assignment of true/false to the symbols in clauses
    model = {s: random.choice([True, False]) for s in variables}
    satisfied, unsatisfied = [], []

    for i in range(max_flips):
        for row in allClauses:
            if pl_true(model, row):
                satisfied.append(row)
            else:
                unsatisfied.append(row)

        if not unsatisfied:  # if model satisfies all the clauses
            return model
        
        clause = random.choice(unsatisfied)
        if probability(p):
            sym = random.choice(clause)
            sym = abs(sym)
        else:
            # Flip the symbol in clause that maximizes number of sat. clauses
            def sat_count(sym):
                # Return the the number of clauses satisfied after flipping the symbol.
                model[sym] = not model[sym]
                count = len([cl for cl in allClauses if pl_true(model, cl)])
                model[sym] = not model[sym]
                return count

            currentMax = 0
            for k in clause:
                count = sat_count(abs(k))
                if currentMax < count:
                    sym = abs(k)
                    currentMax = count

        model[sym] = not model[sym]

    # If no solution is found within the flip limit, we return failure
    return None


def pl_resolution():
    new = set()
    while True:
        n = len(allClauses)
        pairs = [(allClauses[i], allClauses[j])
                 for i in range(n) for j in range(i + 1, n)]
        for (ci, cj) in pairs:
            resolvents = pl_resolve(ci, cj)
            if False in resolvents:
                return True
            new = new.union(set(resolvents))
        if new.issubset(set(allClauses)):
            return False
        for c in new:
            if c not in allClauses:
                allClauses.append(c)


def pl_resolve(ci, cj):
    clauses = []
    # disjunction work
    First = set(ci.split())
    Second = set(cj.split())
    for di in First:
        for dj in Second:
            posj = int(dj)
            posi = -1 * int(di)
            if posi is posj:
                remF = First.copy()
                remS = Second.copy()
                remF.remove(di)
                remS.remove(dj)
                removedVar = remF.union(remS)
                removedVar = list(removedVar)
                cl = ""
                for var in removedVar:
                    if var is removedVar[len(removedVar)-1]:
                        cl = cl + var
                    else:
                        cl = cl + var + ' '
                clauses.append(cl)
    return clauses


def main():
    
    print("What would you like to test ?")
    print("\t\t1.Walksat.")
    print("\t\t2.Resolution proving.")
    choice = input("\tEnter your choice ( 1 or 2 ) : ")
    while choice not in ['1','2']:
        choice = input("\t Error : Please enter 1 or 2. \n Enter your choice ( 1 or 2 ) : ")
    if choice is '1':
        RunType = "Walksat"
        fileOpener("files/cnf2-4-50.txt", RunType)
        start = time.time()
        flg = WalkSAT()
        end = time.time()
        time_elapsed = (end-start)
        print(f'Time elapsed {time_elapsed} seconds.')
        #print("return type :", flg)
    else:
        RunType = "RP"
        fileOpener("files/cnf2-4-50.txt", RunType)
        start = time.time()
        flg  = pl_resolution()
        end = time.time()
        time_elapsed = (end-start)
        print(f'Time elapsed {time_elapsed} seconds.')
        #print("return type :", flg)

main()


    