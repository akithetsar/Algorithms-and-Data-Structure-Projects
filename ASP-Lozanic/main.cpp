#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <chrono>
#include <queue>


int binomiKoef(int, int);


bool interpolPretrazivanje(int* const lista, int key, int n, bool ispisi){
    auto pocetak = std::chrono::high_resolution_clock::now();
    int low = 0, high = n - 1;
    int iteracije = 0;

    if(ispisi) {
        std::cout << "<------------ Interpol ------------>" << std::endl;
    }
    while(high >= low && lista[low] <= key && lista[high] >= key) {
        iteracije++;


        int mid = low + (high - low)*(key - lista[low])/(lista[high] - lista[low]);

        if(ispisi) {
            std::cout << "Iteracija " << iteracije << ": " << std::endl;

            std::cout << '\t' << "Donja granica: " << low << std::endl;
            std::cout << '\t' << "Sredina: " << mid << std::endl;
            std::cout << '\t' << "Gornja granica: " << high << std::endl;

        }
        if (lista[mid] == key) {
            if(ispisi) {
                std::cout << std::endl << "BROJ ITERACIJA: " << iteracije << std::endl;

                auto kraj = std::chrono::high_resolution_clock::now();
                auto trajanje = std::chrono::duration_cast<std::chrono::microseconds>(kraj - pocetak);

                std::cout << "Vreme potrebno: " << trajanje.count() << "ms" << std::endl;
                std::cout << "<------------ End ------------>" << std::endl;

            }

            return true;
        }


        else if(key < lista[mid]){
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    if(ispisi) std::cout << std::endl;
    }

    if(ispisi) {
        std::cout << "BROJ ITERACIJA: " << iteracije << std::endl;
        auto kraj = std::chrono::high_resolution_clock::now();
        auto trajanje = std::chrono::duration_cast<std::chrono::microseconds>(kraj - pocetak);

        std::cout << "Vreme potrebno: " << trajanje.count() << "ms" << std::endl;
        std::cout << "<------------ End ------------>" << std::endl;
    }


    return false;


}
bool ternarnoPretrazivanje(int const *lista, int key, int n, bool ispisi){
    auto pocetak = std::chrono::high_resolution_clock::now();
    int low = 0;
    int high = n -1 ;
    int iteracije = 0;
    if(ispisi) {
        std::cout << "<------------ Ternarno ------------>" << std::endl;
    }
    while(high >= low) {
        iteracije++;
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        if(ispisi) {
            std::cout << "Iteracija " << iteracije << ": " << std::endl;

            std::cout << '\t' << "Donja granica: " << low << std::endl;
            std::cout << '\t' << "Sredina 1: " << mid1 << std::endl;
            std::cout << '\t' << "Sredina 2: " << mid2 << std::endl;
            std::cout << '\t' << "Gornja granica: " << high << std::endl;
        }
        if (lista[mid1] == key) {
            if(ispisi) {
                std::cout << std::endl << "BROJ ITERACIJA: " << iteracije << std::endl;

                auto kraj = std::chrono::high_resolution_clock::now();
                auto trajanje = std::chrono::duration_cast<std::chrono::microseconds>(kraj - pocetak);

                std::cout << "Vreme potrebno: " << trajanje.count() << "ms" << std::endl;
                std::cout << "<------------ End ------------>" << std::endl;
            }
            return true;
        }
        if(lista[mid2] == key)
        {
            if(ispisi) {
                std::cout << std::endl << "BROJ ITERACIJA: " << iteracije << std::endl;
                auto kraj = std::chrono::high_resolution_clock::now();
                auto trajanje = std::chrono::duration_cast<std::chrono::microseconds>(kraj - pocetak);

                std::cout << "Vreme potrebno: " << trajanje.count() << "ms" << std::endl;
                std::cout << "<------------ End ------------>" << std::endl;
            }
            return true;
        }

        if(key < lista[mid1]){
            high = mid1 - 1;
        }
        else if(key > lista[mid2]){
            low = mid2 + 1;
        }
        else{
            low = mid1 + 1;
            high = mid2 - 1;
        }

        if(ispisi) std::cout << std::endl;
    }

    if(ispisi) {
        std::cout << "BROJ ITERACIJA: " << iteracije << std::endl;
        auto kraj = std::chrono::high_resolution_clock::now();
        auto trajanje = std::chrono::duration_cast<std::chrono::microseconds>(kraj - pocetak);

        std::cout << "Vreme potrebno: " << trajanje.count() << "ms" << std::endl;
        std::cout << "<------------ End ------------>" << std::endl;
    }
    return false;
}

class LozanicevTrougao {

private:
    int red;

public:
    int *trougao;
    LozanicevTrougao(int red){
        this->red = red;
        int l = red+1;
        int n = l*(l+1)/2;
        this->trougao = new int[n];

        // T(0, 0) = 0
        trougao[0] = 1;
        for(int i = 0; i < red; i++){
            for(int j = 0; j < i+1; j++){
                trougao[i*(i+1)/2 + j] =
                        0.5 * (binomiKoef(i, j) + binomiKoef(i % 2, j % 2)*binomiKoef(std::floor(i/2),std::floor(j/2)));
            }
        }
    }
    void print() {
        for (int i = 0; i < red; i++) {
            for (int r = 0; r < red - i; r++) {
                std::cout << "  ";
            }

            for (int j = 0; j < i + 1; j++) {
                std::cout << this->trougao[i * (i + 1) / 2 + j] << "   ";
            }
            std::cout << std::endl;
        }
    }


};





int main() {

    while(true){
        int br_red;
        char buffer;
        std::cout << "Unesite broj redova Lozanicevog trougla (-1 da se izadje): ";
        std::cin >> br_red;
        if(br_red == -1) break;

        LozanicevTrougao *noviTrougao = new LozanicevTrougao(br_red);

        noviTrougao->print();
        int pretrazujem;
        std::cout << std::endl << "Izaberite broj reda za pretrazivanje: ";
        std::cin >> pretrazujem;

        system("CLS");
        noviTrougao->print();

        int n = pretrazujem + 1;
        n = n / 2 ;

        if((pretrazujem + 1) % 2 != 0) n += 1;


        int *lista = new int[n];
        for(int i = 0; i < n; i++){
            lista[i] = noviTrougao->trougao[pretrazujem*(pretrazujem+1)/2 + i];
        }


        int key;
        std::cout << "Koji je kljuc za pretrazivanje: ";
        std::cin >> key;


        system("CLS");

        std::cout << "Lista za pretrazivanje: ";
        std::cout << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << lista[i] << " ";
        }
        std::cout << std::endl;


        bool rezTern = ternarnoPretrazivanje(lista, key, n, true);
        std::cout << std::endl;
        bool rezInterpol = interpolPretrazivanje(lista, key, n, true);


        std::string rez_str = rezInterpol && rezTern ? "Kljuc pronadjen" : "Kljuc nije pronadjen";
        std::cout << std::endl << rez_str << std::endl;

        std::cout << "-----------------------------------" << std::endl;




        std::cout << "Kliknite nesto + enter...";
        std::cin >> buffer;
        system("CLS");



    }




    return 0;
}






int binomiKoef(int n, int k) {
    if(n == 0 && k == 1){
        return 0;
    }
    if (k == 0 || k == n)
        return 1;

    return binomiKoef(n - 1, k - 1) + binomiKoef(n - 1, k);
}
