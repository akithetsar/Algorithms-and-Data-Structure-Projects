import os
from time import sleep
import time as tm

#-------------------------- KLASE --------------------------------------
class Talon:
    sumaGore = [0, 0, 0]
    sumaDole = [0, 0, 0]
    UKUPNO = 0
    num_of_cols = 3
    num_of_rows = 10
    cur_na_dole = 0
    cur_na_gore = 9

    def __init__(self, row_ptrs , column_indices, values, matrica, is_compressed):
        self.row_ptrs = row_ptrs
        self.column_indices = column_indices
        self.values = values
        self.matrica = matrica
        self.is_compressed = is_compressed


    def lenRucna(self):
        #COMPRESSED
        count = 0
        if(self.is_compressed):
            for col_i in self.column_indices:
                if col_i == 2:
                    count += 1
            return count

    def updateSuma(self):
        self.sumaGore = [0, 0, 0]
        self.sumaDole = [0, 0, 0]

        if self.is_compressed:
            for i in range(len(self.row_ptrs) - 1):
                row_extract_cols = self.column_indices[self.row_ptrs[i]:self.row_ptrs[i + 1]]
                row_extract_vals = self.values[self.row_ptrs[i]:self.row_ptrs[i + 1]]

                if i < 6:
                    for j in row_extract_cols:
                        if(row_extract_vals[row_extract_cols.index(j)] != "/"):
                            self.sumaGore[j] += row_extract_vals[row_extract_cols.index(j)]
                else:

                    for j in row_extract_cols:
                        if(row_extract_vals[row_extract_cols.index(j)] != "/"):
                            self.sumaDole[j] += row_extract_vals[row_extract_cols.index(j)]
        self.UKUPNO = sum(self.sumaDole) + sum(self.sumaGore)

    def ispisiTalon(self):
        self.updateSuma()
        elementi = ["(1)", "(2)", "(3)", "(4)", "(5)", "(6)", "Kenta", "Full", "Poker", "Jamb"]
        print("Talon: ")
        print("\tNa dole\t\tNa gore\t\tRučna")
        print("------------------------------------------")

        #-------------- AKO JE KOMPRESOVANA ------------------------------
        if self.is_compressed:
            if len(self.column_indices) == 0:
                row_print_list = ["0"]* self.num_of_cols
                row_print = "\t\t".join(row_print_list)

                for r in range(self.num_of_rows):
                    if r == 6:
                        suma_str = [str(x) for x in self.sumaGore]
                        print("------------------------------------------")
                        print("SUMA: \t" + "\t\t".join(suma_str))
                        print("------------------------------------------")

                    print(elementi[r] + '\t' + row_print)

                suma_str = [str(x) for x in self.sumaDole]
                print("------------------------------------------")
                print("SUMA: \t" + "\t\t".join(suma_str))
                print("------------------------------------------")

            else:

                for i in range(len(self.row_ptrs) - 1):
                    row_extract_cols = self.column_indices[self.row_ptrs[i]:self.row_ptrs[i+1]]
                    row_extract_vals = self.values[self.row_ptrs[i]:self.row_ptrs[i+1]]
                    row_print_list = []

                    if(i == 6):
                        suma_str = [str(x) for x in self.sumaGore]
                        print("------------------------------------------")
                        print("SUMA: \t" + "\t\t".join(suma_str))
                        print("------------------------------------------")
                    if len(row_extract_cols) == 0:
                        row_print_list = ["0"] * self.num_of_cols
                        row_print = "\t\t".join(row_print_list)
                    else:
                        for j in range(self.num_of_cols):
                            if j in row_extract_cols:
                                row_print_list.append(f"{row_extract_vals[row_extract_cols.index(j)]}")
                            else:
                                row_print_list.append("0")

                        row_print = "\t\t".join(row_print_list)

                    row_print = elementi[i] + '\t' + row_print
                    print(row_print)

                    if(i == 9):
                        suma_str = [str(x) for x in self.sumaDole]
                        print("------------------------------------------")
                        print("SUMA: \t" + "\t\t".join(suma_str))
                        print("------------------------------------------")

#---------------------- OBICNA MATRICA ---------------------------------------
        else:
            for i in range(10):
                row_print_list = []
                for j in range(3):
                    row_print_list.append(self.matrica[i][j])

                if (i == 6):
                    suma_str = [str(x) for x in self.sumaGore]
                    print("------------------------------------------")
                    print("SUMA: \t" + "\t\t".join(suma_str))
                    print("------------------------------------------")
                row_print_list = [str(x) for x in row_print_list]
                row_print = elementi[i] + '\t' + "\t\t".join(row_print_list)
                print(row_print)
                if (i == 9):
                    suma_str = [str(x) for x in self.sumaDole]
                    print("------------------------------------------")
                    print("SUMA: \t" + "\t\t".join(suma_str))
                    print("------------------------------------------")


    def popunjeno(self, row, col):
        if self.is_compressed:
            row_col_extract = self.column_indices[self.row_ptrs[row]:self.row_ptrs[row+1]]

            return col in row_col_extract
        else:
            return self.matrica[row][col] != 0



    def ubaciElement(self, row, col, val):
        if self.is_compressed == True:
            before = 0
            for i in range(row + 1):
                before += self.row_ptrs[i + 1] - self.row_ptrs[i]

            self.column_indices.insert(before, col)
            self.values.insert(before, val)


            for i in range(row + 1, len(self.row_ptrs)):
                self.row_ptrs[i] += 1
        else:
            self.matrica[row][col] = val

    def convertTalon(self):
        clear()

        print("KONVERTUJEM MATRICU")
        sleep(3)
        self.matrica = [[0,0,0], [0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0]]
        for i in range(len(self.row_ptrs)-1):

            cols = self.column_indices[self.row_ptrs[i]:self.row_ptrs[i+1]]
            vals = self.values[self.row_ptrs[i]:self.row_ptrs[i+1]]

            for j in range(len(cols)):
                self.matrica[i][cols[j]] = vals[j]

        self.is_compressed = False
        clear()

    def proveriPopunjenost(self):
        t = False
        if(not self.is_compressed):
            t = True

            for i in range(10):
                for j in range(3):
                    if(self.matrica[i][j] == 0):
                        t = False
                if t == False:
                    break
        return t
    def proveriMemoriju(self):
        return len(self.values)
    def resetujTalon(self):

        self.row_ptrs = [0] * 10
        self.column_indices = []
        self.values = []

        self.matrica = [[0,0,0]*10]
        self.is_compressed = True
        self.cur_na_gore = 9
        self.cur_na_dole = 0

#-------------------------- GLOBALNE PROMENLJIVE ---------------------

seed = tm.time()
talon = Talon([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [], [], [], True)

bool_u_igri = True
sumaFull = 0




# --------------------- IMPLEMENTACIJA KOCKE ----------------------------


def randInt():
    global seed

    seed = (429493445 * seed + 907633385) % 4294967296
    return seed

def randomDouble():

    return randInt() / 4294967296.


def random6():
    return int(randomDouble() * 6 + 1)

# --------------------------SUPPORT FUNC--------------------------


def clear():
    os.system('cls')

def fillerFunc():
    print("\n OVO JE FILLER FUNC \n")
    sleep(1)
    clear()

# --------------------------------------------------------------

def baciKockice(broj_kockice):
    bacanje = []
    for i in range(broj_kockice):
        bacanje.append(random6())

    return bacanje


def pokupiDzep(ruka, dzep):
    ruka_s = [str(x) for x in ruka]
    ruka_string = " ".join(ruka_s)
    talon.updateSuma()
    talon.ispisiTalon()
    print(f"Ovo je vaša ruka: {ruka_string}")
    print(f"Ovo je vaš džep: {dzep}" )
    dob_izbor = False

    while(not dob_izbor):

        try:

            print("Izaberite redne brojeve kockica koje hocete da pokupite 1-6(Npr: 1 2 6): ")
            za_dzep = input("Upiši redne brojeve: ")

            dob_izbor = True

            if len(za_dzep.split(" ")) > len(ruka_s):
                print("Uneli ste preveliki broj elemenata, pokušajte ponovo")
                dob_izbor = False
            dzep_split = za_dzep.split()
            dzep_split = [int(x) for x in dzep_split]
            for el in dzep_split:
                if int(el) < 0:
                    print("Unesite pozitivan broj ili nulu")
                    dob_izbor = False

        except ValueError:
            print("Molim vas upisite ceo broj")
            dob_izbor = False



    if(za_dzep == "0"):
        clear()
        sleep(0.5)
        return dzep
    else:
        za_dzep_split = za_dzep.split()
        za_dzep_split = [int(x) for x in za_dzep_split]
        for i in za_dzep_split:
            dzep.append(ruka[i-1])


    clear()
    sleep(0.5)
    return dzep



def upisiDole(ruka, pocket, redno_bacanje):
    global talon
    clear()
    sleep(1)
    talon.ispisiTalon()
    mogucnosti = proveri_mogucnosti(ruka, pocket, redno_bacanje)
    mogucnosti_str = mogucnosti[0]
    opcije = mogucnosti[1]
    print(f"Ovo su vaše trenutne kombinacije: {mogucnosti_str} \n")

    while(True):
        izbor = input("Upišite kombinaciju(TAČNO KAKO PIŠE IZNAD) ili -1 ako hocete da upisete prazno: : ")
        if izbor == "-1":
            upisiPrazno()
            break
        elif(izbor in mogucnosti_str):
            index = mogucnosti_str.index(izbor)
            opcija = opcije[index]
            if(talon.cur_na_dole == opcija[0]):
                talon.ubaciElement(talon.cur_na_dole, 0, opcija[1])
                talon.cur_na_dole += 1
                break
            else:
                print("Ova opcija vam nije na redu na dole, probajte drugu")
    clear()
    sleep(0.5)

def upisiGore(ruka, pocket, redno_bacanje):
    global talon
    clear()
    sleep(1)
    talon.ispisiTalon()
    mogucnosti = proveri_mogucnosti(ruka, pocket, redno_bacanje)
    mogucnosti_str = mogucnosti[0]
    opcije = mogucnosti[1]
    print(f"Ovo su vaše trenutne kombinacije: {mogucnosti_str} \n")



    while(True):
        izbor = input("Upišite kombinaciju(TAČNO KAKO PIŠE IZNAD) ili -1 ako hocete da upisete prazno: ")
        if izbor == "-1":
            upisiPrazno()
            break
        elif(izbor in mogucnosti_str):
            index = mogucnosti_str.index(izbor)
            opcija = opcije[index]
            if(talon.cur_na_gore == opcija[0]):
                talon.ubaciElement(talon.cur_na_gore, 1, opcija[1])
                talon.cur_na_gore -= 1
                break
            else:
                print("Ova opcija vam nije na redu na dole, probajte drugu")
    clear()
    sleep(0.5)

def upisiPrazno():
    talon.ispisiTalon()
    while(True):
        polje = input("Napišite koordinatu polja koje želite da precrtate(Npr: 5 0): ").split(" ")

        try:
            row = int(polje[0])
            col = int(polje[1])
            if(talon.popunjeno(row, col)):
                print("Ovo polje je popunjeno, pokusajte ponovo")
            elif(col > 2 or col < 0 or row > 9 or row < 0):
                print("Unesite pravi red/kolonu")
                continue
            else:
                talon.ubaciElement(row, col, "/")
                break

        except ValueError:
            print("Unesite pravilnu vrednost")
        except IndexError:
            print("Unesite pravi red/kolonu")
    clear()
    sleep(0.5)
def upisiRucna(ruka, pocket, redno_bacanje):

    global talon

    talon.ispisiTalon()
    clear()
    sleep(1)
    talon.ispisiTalon()
    mogucnosti = proveri_mogucnosti(ruka, pocket, redno_bacanje)
    mogucnosti_str = mogucnosti[0]
    opcije = mogucnosti[1]
    print(f"Ovo su vaše trenutne kombinacije: {mogucnosti_str} \n")



    while(True):
        izbor = input("Upišite kombinaciju(TAČNO KAKO PIŠE IZNAD) ili -1 ako hocete da upisete prazno: ")
        if izbor == "-1":
            upisiPrazno()
            break
        elif(izbor in mogucnosti_str):
            index = mogucnosti_str.index(izbor)
            opcija = opcije[index]
            if(not talon.popunjeno(opcija[0],2)):
                talon.ubaciElement(opcija[0], 2, opcija[1])
                break
            else:
                print("Ovo polje je već popunjeno")
    clear()
    sleep(0.5)

def upisujem(redno_bacanje, ruka, pocket):
    talon.ispisiTalon()
    mogucnosti = proveri_mogucnosti(ruka, pocket, redno_bacanje)
    print("UPISIVANJE NA TALON")
    print(f"Ovo su vaše trenutne kombinacije: {mogucnosti[0]} \n")
    if(redno_bacanje == 1):
        opcionoBiranje(["Upiši na dole", "Upiši na gore", "Upiši prazno", "Upiši ručnu"], [upisiDole, upisiGore, upisiPrazno, upisiRucna], [(ruka, pocket, redno_bacanje), (ruka, pocket, redno_bacanje), None, (ruka, pocket, redno_bacanje)])
    else:
        opcionoBiranje(["Upiši na dole", "Upiši na gore", "Upiši prazno"], [upisiDole, upisiDole, upisiPrazno], [(ruka, pocket, redno_bacanje), (ruka, pocket, redno_bacanje), None])


def proveri_mogucnosti(ruka, pocket, redno_bacanje):
    global talon

    ruka_pocket = pocket.copy()
    ruka_pocket.extend(ruka)
    broj_cifara = [0, 0, 0, 0, 0, 0]
    opcije_str = []
    #RED KOLICINA
    opcije = []

    for val in ruka_pocket:
        if (int(val) == 1):
            broj_cifara[0] += 1

        elif (int(val) == 2):
            broj_cifara[1] += 1
        elif (int(val) == 3):
            broj_cifara[2] += 1
        elif (int(val) == 4):
            broj_cifara[3] += 1
        elif (int(val) == 5):
            broj_cifara[4] += 1
        elif (int(val) == 6):
            broj_cifara[5] += 1

    sort_ruka_pocket = sorted(ruka_pocket)


    for i, val in enumerate(broj_cifara):

        if(val != 0):
            opcije_str.append(f"Broj: {i+1} x {val} put/a")
            opcije.append((i, (i+1) * val))

        if(val == 5):
            opcije_str.append(f"Jamb: {i+1}")
            opcije.append((9, 50 + (i + 1) * 5))
        if(val >= 4):
            opcije_str.append(f"Poker: {i+1}")
            opcije.append((8, 40 + (i + 1) * 4))



    for i in range(5):
        for j in range(1, 6):
            if ((broj_cifara[i] == 2 and broj_cifara[j] == 3) or (broj_cifara[i] == 3 and broj_cifara[j] == 2)):
                opcije_str.append(f"Full: {broj_cifara[i]} * {i + 1} i {broj_cifara[j]} * {j + 1}")
                opcije.append((7, broj_cifara[i] * (i+1) + broj_cifara[j] * (j + 1) + 30))


    if (sort_ruka_pocket == [1, 2, 3, 4, 5]):
        opcije_str.append(f"Kenta: 1 2 3 4 5")
        opcije.append((6, 66 - (redno_bacanje-1) * 10))
    elif(sort_ruka_pocket == [2, 3, 4, 5, 6]):
        opcije_str.append("Kenta: 2 3 4 5 6")
        opcije.append((6, 66 - (redno_bacanje-1) * 10))



    return (opcije_str, opcije)

def potezSam():

    ruka = baciKockice(5)
    ruka_s = [str(x) for x in ruka]
    ruka_string = " ".join(ruka_s)

    dzep = []
    redno_bacanje = 1
    zavrsen_potez = False
    while(redno_bacanje < 3):
        talon.updateSuma()
        talon.ispisiTalon()
        print(f"Ovo je vaša ruka: {ruka_string}")
        print(f"Ovo je vas dzep: {dzep}")
        print(f"Ovo su vaše trenutne kombinacije: {proveri_mogucnosti(ruka, dzep, redno_bacanje)[0]} \n")
        izbor = opcionoBiranje(["Upiši u talon", "Nastavi bacanja"], [upisujem, pokupiDzep], [(redno_bacanje, ruka, dzep), (ruka, dzep)])
        if(izbor == 0):
            zavrsen_potez = True
            break

        ruka = baciKockice(5 - len(dzep))
        if len(ruka) == 0:
            break
        ruka_s = [str(x) for x in ruka]
        ruka_string = " ".join(ruka_s)
        redno_bacanje += 1

    if(len(dzep) < 5):
        dzep.extend(ruka)

    if(not zavrsen_potez):
        upisujem(redno_bacanje, ruka, dzep)




    sleep(0.5)

def zavrsiIgru():
    global bool_u_igri
    bool_u_igri = False
    print("\nOvo su vasi rezultati ove igre")
    print(f"Ukupno: {talon.UKUPNO} poena")
    talon.resetujTalon()


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





def potezPrijatelj():
    ruka = baciKockice(5)
    ruka_s = [str(x) for x in ruka]
    ruka_string = " ".join(ruka_s)

    dzep = []
    redno_bacanje = 1
    zavrsen_potez = False
    mogucnosti = proveri_mogucnosti(ruka, dzep, redno_bacanje)
    mogucnosti_str = mogucnosti[0]
    opcije = mogucnosti[1]
    print(ruka)
    print(mogucnosti_str)
    sort_opcije = sorted(opcije,key = lambda x: x[1], reverse=True)
    print(sort_opcije)

    sleep(5)
#UPISI RUCNU AKO IMAS
    for i in range(len(sort_opcije)):
        opcija = sort_opcije[i]
        if (not talon.popunjeno(opcija[0], 2)):
            talon.ubaciElement(opcija[0], 2, opcija[1])
            zavrsen_potez = True
            break

    if(zavrsen_potez):
        return

    print("Upisujem gore/dole")

    if(talon.cur_na_dole < 6 and talon.cur_na_gore >= 6):
        #Na dole je iznad / Na gore je ispod
        pass

    elif(talon.cur_na_dole < 6 and talon.cur_na_gore < 6):
        #Na dole je iznad / Na gore je iznad
        na_dole_red = "/"
        na_gore_red = "/"
        for i in range(len(sort_opcije)):
            if(sort_opcije[i][0] == talon.cur_na_dole):
                na_dole_red = sort_opcije[i]
            if(sort_opcije[i][0] == talon.cur_na_gore):
                na_gore_red = sort_opcije[i]

        print(na_dole_red)
        print(na_gore_red)
        sleep(6)
        if(na_dole_red == "/" and na_gore_red == "/"):
            talon.ubaciElement(talon.cur_na_dole, 0, "/")
            talon.cur_na_dole += 1
        elif(na_dole_red == "/"):
            talon.ubaciElement(talon.cur_na_gore, 1, na_gore_red[1])
            talon.cur_na_gore -= 1
        elif(na_gore_red == "/"):
            talon.ubaciElement(talon.cur_na_dole, 0, na_dole_red[1])
            talon.cur_na_dole += 1
        elif(na_dole_red[1] / (na_dole_red[0] + 1) >= na_gore_red[1] / (na_gore_red[0] + 1)):
            talon.ubaciElement(talon.cur_na_dole, 0, na_dole_red[1])
            talon.cur_na_dole += 1
        elif(na_dole_red[1] / (na_dole_red[0] + 1) < na_gore_red[1] / (na_gore_red[0] + 1)):
            talon.ubaciElement(talon.cur_na_gore, 1, na_gore_red[1])
            talon.cur_na_gore -= 1


    elif(talon.cur_na_dole >= 6 and talon.cur_na_dole >= 6):
        #Na dole je ispod / Na gore je ispod
        pass
    elif(talon.cur_na_dole >= 6 and talon.cur_na_gore < 6):
        #Na dole je ispod / Na gore je iznad
        pass


def igra():
    global bool_u_igri
    u_igri = True
    while (u_igri):
        bool_u_igri = True
        clear()
        print("Dobrodosli u igru Jamb.")
        print("Igra se igra putem interaktivnog menija. Dobicete opcije i kada vam program trazi da upisete broj, vi upisete redni broj ispred opcije koju zelite da izaberete.")
        print("Srecno! Da pokrenete igru kliknite ENTER! \n\n\n")

        input("")

        sleep(1)
        clear()

       #GAME LOOP

        while(bool_u_igri):
            if(talon.proveriPopunjenost() == True):
                zavrsiIgru()
                break
            if(talon.proveriMemoriju() >= 10 and talon.is_compressed):
                talon.convertTalon()

            talon.updateSuma()
            talon.ispisiTalon()

            opcionoBiranje(["Izadji", "Igraj Sam Potez", "Prepusi Prijatelju Potez", "Novi Talon"], [zavrsiIgru, potezSam, potezPrijatelj, talon.resetujTalon], [None, None, None, None])

        while(True):
            print("Da li želite ponovo da igrate")
            print("0. Da")
            print("1. Ne")
            izbor = input("Unesite opciju: ")
            if(izbor == "1"):
                u_igri = False
                break
            elif(izbor == "0"):
                u_igri = True
                break
            else:
                print("Unesite jednu od opcija!")
        print("Dovidjenja!")



#Game Start
igra()










