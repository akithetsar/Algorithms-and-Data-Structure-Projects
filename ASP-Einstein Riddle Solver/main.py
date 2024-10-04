from collections import deque
import os
from time import sleep

top = -1
stack = []
queue = deque()
u_igri = True
fajlResenje = open("resenja.txt", "w", encoding="utf-16")
fajlStablo = open("stablo.txt", "w", encoding="utf-16")


#-------STABLO----------------
class Cvor:

    def __init__(self, data=None, level=0, indeks = 0):
        self.data = data
        self.next = None
        self.child = None
        self.parents = []
        self.level = level
        self.tacnost = True
        self.indeks = indeks

def zavrsiIgru():
    global u_igri
    u_igri = False

def dodajBrata(cvor, data):
    if(cvor == None):
        return None
    novi_cvor = Cvor(data)

    while(cvor.next != None):
        cvor = cvor.next
    cvor.next = novi_cvor
    return novi_cvor

def dodajDete(cvor, data):
    if (cvor == None):
        return None
    novi_cvor = Cvor(data)
    if(cvor.child != None):
        n = dodajBrata(cvor.child, data)
        return n
    else:
        cvor.child = novi_cvor
        return novi_cvor
count = 0
def preorder(root, M, N, indeks_to_find, print_tree = True, should_find = False, find_sol = False):
    push(root)
    prev_sib = None
    global count

    while(not isEmptyStack()):
        curr = pop()

        while(curr != None):
            if print_tree:
                level = curr.level
                prefixes_chars = [" ├─ ", " │  ", " └─ ", "    "]
                prefix = []
                for i in range(level):
                    if(i == level - 2 and curr.next == None and prev_sib == None):
                        prefix.append(prefixes_chars[3])
                    elif (i == level - 1):
                        prefix.append(prefixes_chars[0])
                    else:
                        prefix.append(prefixes_chars[1])

                to_print = "".join(prefix)
                fajlStablo.write(to_print)

                fajlStablo.write(str(curr.indeks))
                fajlStablo.write('\n')


                prev_sib = curr.next
            elif should_find:
                if(curr.indeks == indeks_to_find):
                    ispisiMatricu(curr.data, M, N)

            elif find_sol:
                if(curr.tacnost == True and curr.level == (M-1)*N):
                    to_write = str(curr.indeks)
                    fajlResenje.write(to_write)
                    fajlResenje.write('\n')
                    count += 1


            if(curr.next != None):
                push(curr.next)
            curr = curr.child


def preorder_helper(root, M, N):
    push(root)
    leaves = []
    prev_sib = None
    while(not isEmptyStack()):
        curr = pop()
        while(curr != None):
            if(curr.level < (M-1)*N):
                curr.tacnost = False
            else:
                leaves.append(curr)
            if(curr.next != None):
                push(curr.next)
            curr = curr.child
    return leaves

def preorder_get_leaves(root, M, N):
    push(root)
    leaves = []
    prev_sib = None
    while(not isEmptyStack()):
        curr = pop()
        while(curr != None):
            if(curr.level == (M-1)*N):
                leaves.append(curr)
            if(curr.next != None):
                push(curr.next)
            curr = curr.child
    return leaves

#-------------------------STACK-------------------------------


def isEmptyStack():
    global stack
    global top
    return top == -1

def pop():
    global stack
    global top
    if(not isEmptyStack()):
        v = stack[top]
        del(stack[top])
        top -= 1

        return v
def push(value):
    global stack
    global top
    top += 1
    stack.append(value)


#--------------------------UNOS FUNKCIJE------------------------------------

def unesiPojmove(M, N):

    while(True):

        try:
            fail = False
            pojmovi = []
            for i in range(M):
                pojmovi.append(input().split(','))
                if(len(pojmovi[i]) != N):
                    print(f"Unesite samo po {N} pojmova")
                    fail = True
                    break
            if(fail):
                continue


        except ValueError:
            print("Unesite pojmove odvojene zarezom")

        return pojmovi

def unesiMN():
    while (True):
        try:
            M = int(input(""))
            if (M < 1):
                print("Molim vas unesite broj veci od 0")
                continue
            N = int(input(""))
            if (N < 1):
                print("Molim vas unesite broj veci od 0")
                continue
            return (M, N)

        except ValueError:
            print("Unesite BROJ")
            continue

def unesiUslove(pojmovi):

    uslovi = []
    try:
        uslov = input()
        while (uslov != ""):
            uslovi.append(uslov)
            uslov = input()

    except ValueError:
        print("Unesite normalno uslov")
    for uslov in uslovi:
        uslovi_minus = []
        if ('+' in uslov):
            uslov1, uslov2 = uslov.split('+')
            for pojam_grupa in pojmovi:
                if (uslov1 in pojam_grupa):
                    for pojam in pojam_grupa:
                        if (pojam != uslov1):
                            uslovi.append(uslov2 + '-' + pojam)
                if (uslov2 in pojam_grupa):
                    for pojam in pojam_grupa:
                        if (pojam != uslov2):
                            uslovi.append(uslov1 + '-' + pojam)
    return uslovi


#--------------------------POMOCNE FUNKCIJE------------------------------------
def clear():
    os.system('cls')

def proveriIspravnost(curr):
    ispravnost = curr.tacnost
    clear()
    if(ispravnost == True):
        print("Trenutno ste na dobrom putu")
    else:
        print("Niste na dobrom putu")
    sleep(2)
def opcionoBiranje(lista_opcija, lista_funkcija, params):
    if(len(lista_opcija) != len(lista_funkcija)):
        print("DEBUG : RAZLICITE DUZINE LOGIKE I OPCIJA")
        print("DEBUG : RAZLICITE DUZINE LOGIKE I OPCIJA")
        print("DEBUG : RAZLICITE DUZINE LOGIKE I OPCIJA")

    print("Izaberite jednu od opcija: ")


    for i in range(len(lista_opcija)):
        print(f"{i}. {lista_opcija[i]}")

    dobar_izbor = False
    pitanje = "Upisite redni broj opcije: "
    while(not dobar_izbor):
        try:
            izbor = int(input(pitanje))
        except ValueError:
            print("Molim vas upisite ceo broj")
            continue
        dobar_izbor = True
        if izbor < 0 or izbor > (len(lista_opcija) - 1):
            dobar_izbor = False
            pitanje = "Molim vas upisite jednu od PONUDJENIH opcija: "


    if params[izbor] == None:
        clear()

        lista_funkcija[izbor]()
    else:
        clear()

        lista_funkcija[izbor](*(params[izbor]))

    return izbor

def ispisiMatricu(matrica, M, N):
    for i in range(M):
        ispisred = []
        for j in range(N):
            if(matrica[i][j] != None):
                ispisred.append(matrica[i][j])
            else:
                ispisred.append('')
        ispis = "\t\t".join(ispisred)
        print(ispis)
def fullMatrica(matrica):
    punaMatrica = True
    to_break = False
    for el in matrica:
        for e in el:
            if e == None:
                punaMatrica = False
                to_break = True
                break
        if to_break:
            break
    return punaMatrica

def fillerFunc():
    print("\n OVO JE FILLER FUNC \n")
    sleep(1)
    clear()
def kreiraj_stablo(tabela, M, N):
    root = Cvor(tabela, indeks=0)

    queue.append(root)
    indeks = 1
    while (len(queue) > 0):
        currParent = queue.popleft()
        parentLevel = currParent.level
        for i in range(1, M):
            for j in range(N):
                if currParent.data[i][j] != None:
                    continue

                for pojam in pojmovi[i]:
                    if pojam in currParent.data[i]:
                        continue
                    currNodeMatrix = []
                    currNodeMatrix.append(pojmovi[0])
                    for _ in range(1, M):
                        currNodeMatrix.append([None] * N)
                    for p in range(1, M):
                        for q in range(N):
                            currNodeMatrix[p][q] = currParent.data[p][q]
                    currNodeMatrix[i][j] = pojam
                    dete = dodajDete(currParent, currNodeMatrix)
                    dete.indeks = indeks
                    indeks += 1
                    dete.level = parentLevel + 1
                    dete.parents.append(currParent)
                    if (check_matrix(dete.data, M, N, uslovi)):
                        queue.append(dete)
                    else:
                        dete.tacnost = False

    to_process = preorder_helper(root, M, N)
    for i in range((M - 1) * N):

        leaves = []
        for el in to_process:
            leaves.append(el)
        to_process = []
        for leaf in leaves:
            for parent in leaf.parents:
                if (leaf.tacnost == True):
                    parent.tacnost = leaf.tacnost
                if (parent not in to_process):
                    to_process.append(parent)
    return root

def check_matrix(matrix_row, M, N, rules):
    matrix = [*zip(*matrix_row)]
    for rule in rules:

        if '-' in rule:
            item1, item2 = rule.split('-')
            # If the rule is of the form "item1-item2", the items should not be in the same column
            item1_col = None
            item2_col = None
            for i, column in enumerate(matrix):
                if item1 in column:
                    item1_col = i
                if item2 in column:
                    item2_col = i
            # If one or both of the items haven't been placed yet, skip this rule
            if item1_col is not None and item2_col is not None and item1_col == item2_col:
                return False
        else:
            item1, item2 = rule.split('+')

            # If the rule is of the form "item1+item2", the items should be in the same column
            item1_col = None
            item2_col = None
            for i, column in enumerate(matrix):
                if item1 in column:
                    item1_col = i
                if item2 in column:
                    item2_col = i
            # If one or both of the items haven't been placed yet, skip this rule
            if item1_col is not None and item2_col is not None and item1_col != item2_col:
                return False
    # If all rules pass, the matrix is valid
    return True
#--------------------------PROGRAM------------------------------------

M, N = unesiMN()
pojmovi = unesiPojmove(M, N)
uslovi = unesiUslove(pojmovi)
tabela = []
tabela.append(pojmovi[0])
for _ in range(1, M):
    tabela.append([None] * N)

print(pojmovi)
print(tabela)
print(uslovi)
root = kreiraj_stablo(tabela, M, N)

preorder(root, M, N, find_sol=False, should_find=False, indeks_to_find=False,print_tree=True)


igrac_tabela = []
igrac_tabela.append(pojmovi[0])
for _ in range(1, M):
    igrac_tabela.append([None] * N)

preorder(root, M, N, find_sol=False, should_find=False, indeks_to_find=False,print_tree=True)
preorder(root, M, N, find_sol=True, should_find=False, indeks_to_find=False, print_tree=False)
fajlResenje.write("")
currStanje = root



def igrajPotez(matrica, curr, pojmovi):
    ispisiMatricu(matrica, M, N)
    global currStanje
    while(True):
        print("Unesite polje u koje hocete da unesete vrednost kao: 1 1: ")
        polje = input("").split(" ")
        i = int(polje[0])
        j = int(polje[1])

        if(matrica[i][j] != None):
            print("Unesite ne popunjeno polje")
            continue
        break
    while(True):
        print("Unesite pojam u koje hocete da unesete u polje: ")
        vrednost = input("")
        if vrednost not in pojmovi[i]:
            print("Unesite vrednost koja moze biti u ovom redu")
            continue
        break
    matrica[i][j] = vrednost
    next = curr.child
    while(next):
        jednaki = True
        for p in range(len(matrica)):
            for q in range(len(matrica[0])):
                if next.data[p][q] != matrica[p][q]:
                    jednaki = False
        if jednaki:
            currStanje = next
            break
        next = next.next
    del(pojmovi[i][pojmovi[i].index(vrednost)])

def ispisiCvor(root, M, N):
    print("Indeks cvora: ")
    indeks = input("")
    preorder(root, M, N, int(indeks), should_find=True, print_tree=False, find_sol=False)
    input("")

def pomoc(currStanje):
    clear()
    child = currStanje.child
    print("Ovo su dobri potezi: ")
    while(child):
        if(child.tacnost == True):
            ispisiMatricu(child.data, M, N)
            print('----------------------------------------------')
        child = child.next
    input("")
fajlResenje.close()
fajlStablo.close()
while(u_igri):
    clear()
    print("Trenutno stanje matrice")
    ispisiMatricu(igrac_tabela, M, N)

    opcionoBiranje(["Igrajte potez", "Dobre opcije", "Ispravnost", "Kraj igre", "Ispisi cvor matrice"], [igrajPotez, pomoc, proveriIspravnost, zavrsiIgru, ispisiCvor],
                   [(igrac_tabela, currStanje, pojmovi), (currStanje,),(currStanje,),None, (root, M, N)])

    if (fullMatrica(igrac_tabela)):
        if (proveriIspravnost(currStanje)):
            print("Uspeli ste tacno da popunite matricu!")
            sleep(5)
            zavrsiIgru()
        else:
            print("Niste uspeli tacno da popunite matricu :(")
            sleep(5)
            zavrsiIgru()




