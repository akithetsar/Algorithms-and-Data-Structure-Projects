import math
import numpy


# --------------------- IMPLEMENTACIJA KOCKE ----------------------------
seed = 42354

def iurng():
    global seed

    seed = (429493445 * seed + 907633385) % 4294967296
    return seed

def randomD():

    return iurng() / 4294967296.


def random6():
    return int(randomD() * 6 + 1)

# --------------------------------------------------------------------------







def pocketDice(hand, pocket):

    print("Izaberite brojeve kockica(po redu) koje cete da zadrzite")
    uzeto_bool = False
    while (not uzeto_bool):
        uzeto = input("Unesite: ").split(" ")
        to_continue = False

        for i in uzeto:
            if (i not in "123456"):
                print("Molim vas unesite validnde brojeve")
                pocket = []
                to_continue = True
                break
            pocket.append(hand[int(i) - 1])

        if to_continue:
            continue
        uzeto_bool = True

    print(pocket)
    return pocket


def throwDice(dice_num):
    hand_throw = []
    for i in range(dice_num):
        hand_throw.append(random6())

    return hand_throw

def playTurn(withFriend):
    dice_num = 6
    hand = throwDice(dice_num)
    redno_bacanje = 1
    pocket = []


    print("\nBacili ste sledece brojeve: ")
    print(hand)
    print("Da li hocete da upisete u rucnu ili da nastavite potez?")
    print("1. Rucna 2. Nastavi")
    opcija = input("Unesite opciju: ")
    
#CEKIRAJ DA LI JE VALIDNA OPCIJA LOOP
    while(True):
        if opcija == "1":
            print("Upisujem Rucnu")

        elif opcija == "2":
            nastavak_bacanja = True
            print(f"U {redno_bacanje}. bacanju dobili ste sledece brojeve: ")
            print(hand)
            redno_bacanje += 1
            pocket = pocketDice(hand, pocket)

            while(nastavak_bacanja):
                print(f"U {redno_bacanje}. bacanju dobili ste sledece brojeve: ")
                print(hand)
                redno_bacanje += 1
                pocket = pocketDice(hand, pocket)

                print("Da li želite da upišete u talon ili bacite ponovo?")
                print("1. Nastavi 2. Upisi talon")
                opcija = input("Unesite opciju: ")
        else:
            print("Unesite validnu opciju")





    # while(True):
    #
    #     if(opcija == "1"):
    #         print("Upisujem rucnu")
    #         break
    #
    #     elif(opcija == "2"):
    #
    #         pocket = pocketDice(hand, pocket)
    #
    #
    #         dice_num -= len(pocket)
    #         hand = throwDice(dice_num)
    #
    #         pocket = pocketDice(hand, pocket)
    #
    #
    #         print(pocket)
    #         hand = throwDice(6 - len(pocket))
    #         for el in hand:
    #             pocket.append(el)
    #         print(pocket)
    #         break
    #     else:
    #         print("Unesite validnu opciju")









def gameLoop():
    print("Dobrodosli u igru Jamb.");
    print("Igra se igra putem interaktivnog menija. Dobicete opcije i kada vam program trazi da upisete broj, vi upisete redni broj ispred opcije koju zelite da izaberete.");
    print("Srecno! Da pokrenete igru kliknite enter!");

    input("")

    #POTEZ LOOP
    while(True):


        print("Izaberite jednu od opcija: ");
        print("0. Izadji iz igre 1. Igraj Potez 2. Prepusti Prijatelju");
        opcija_prijatelj = input("Unesite opciju: ")
        withFriend = True
        bool_u_igri = True

        if(opcija_prijatelj == "0"):
            print("\n Izlazim iz igre.")
            bool_u_igri = False;
        elif(opcija_prijatelj == "1"):
            playTurn(not withFriend)




        elif(opcija_prijatelj == "2"):
            print("\n playTurn(1) \n")
        else: print("\n Niste uneli nijednu validnu opciju! \n ")

        if(not bool_u_igri):
            break

    print("Izasao iz loopa")

gameLoop()










