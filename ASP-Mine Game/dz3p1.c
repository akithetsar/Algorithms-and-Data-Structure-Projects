#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define BROJ_SIM_TACAKA 10000000



float RandomFloat(float min, float max)
{

    float random = ((float) rand()) / (float) RAND_MAX;

    float range = max - min;
    return (random*range) + min;
}
typedef struct cvor{
    int indeks;
    float r, x, y;
} Cvor;

typedef struct cvor_susednosti{
    int dest;
    struct cvor_susednosti *next;
} CvorSusednosti;


typedef struct lista_susednosti{
    CvorSusednosti *first;
} ListaSusednosti;

typedef struct graf{

    Cvor **cvorovi;
    ListaSusednosti *susednosti;

} Graf;

void delGrana(Graf* graf, int src, int dest, int n);

Cvor* queue[256];
int front = - 1;
int rear = -1;

Cvor* DELETE()
{
    if (front == - 1 || front > rear)
    {
        printf("Underflow \n");
        return NULL;
    }
    else
    {
        Cvor* temp = queue[front];
        front = front + 1;
        return temp;
    }
}

void INSERT(Cvor* cvor)
{

    if (rear == 256 - 1)
        printf("Overflow \n");
    else
    {
        if (front == - 1)

            front = 0;

        rear = rear + 1;
        queue[rear] = cvor;
    }
}

Graf* napraviGraf(int n){
    Graf* novi_graf = NULL;
    novi_graf = malloc(sizeof (Graf));
    novi_graf->cvorovi = malloc(sizeof (Cvor*) * n);
    novi_graf->susednosti = malloc(sizeof (ListaSusednosti)*n);

    for(int i = 0; i < n; i++){
        novi_graf->cvorovi[i] = NULL;
        novi_graf->susednosti[i].first = NULL;

    }



    return novi_graf;
}

void dodajCvor(Graf* graf, float x, float y, float r, int n){
    int i;
    for(i = 0; graf->cvorovi[i] && i < n; i++);
    if(i == n) printf("GRAF JE PUN");
    graf->cvorovi[i] = malloc(sizeof (Cvor));
    graf->cvorovi[i]->indeks = i;

    graf->cvorovi[i]->x = x;
    graf->cvorovi[i]->y = y;
    graf->cvorovi[i]->r = r;

}

void delCvor(Graf* graf, int n, int indeks){

    CvorSusednosti *tek, *p;
    tek = graf->susednosti[indeks].first;
    for(int i = 0; i < n; i++){
        delGrana(graf, i, indeks, n);
    }
    while(tek){
        p = tek;
        tek = tek->next;

        free(p);

    }
    graf->susednosti[indeks].first = NULL;
    free(graf->cvorovi[indeks]);
    graf->cvorovi[indeks] = NULL;
}

void dodajGranu(Graf* graf, int src, int dest, int n){
    if((!(graf->cvorovi[src] && graf->cvorovi[dest]) || src < 0 || src > (n-1) || dest < 0 || dest > (n-1)) || (src == dest)) printf("Jedan ili oba od ovih cvorova ne postoje\n");
    else {
        CvorSusednosti *tek, *novi = malloc (sizeof(CvorSusednosti));
        novi->dest = dest;
        novi->next = NULL;
        if (!graf->susednosti[src].first)
            graf->susednosti[src].first = novi;
        else {

            for(tek = graf->susednosti[src].first; tek; tek = tek->next){
                if(tek->dest == dest && tek){
                    printf("Vec postoji ova grana!");
                    return;
                }
            }

            for (tek=graf->susednosti[src].first; tek->next; tek=tek->next);
            tek->next = novi;
        }

    }
}


void delGrana(Graf* graf, int src, int dest, int n){
    //Jedan ili oba od ovih cvorova ne postoje
    if((!(graf->cvorovi[src] && graf->cvorovi[dest]) || src < 0 || src > (n-1) || dest < 0 || dest > (n-1)) || (src == dest)) printf("");
    else {
        CvorSusednosti *tek = graf->susednosti[src].first, *pret = NULL,
                *stari;
        while (tek)
            if (tek->dest != dest) {
                pret = tek;
                tek = tek->next; }
            else { /* ako se element izostavlja */
                stari = tek;
                tek = tek->next;
                if (!pret)
                    graf->susednosti[src].first = tek;
                else
                    pret->next = tek;
                free (stari);
            }


    }
}
void printGraf(Graf* graf, int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (graf->cvorovi[i]) {
            printf("[%d (x:%f, y:%f, r:%f) ; %d] -> ", i, graf->cvorovi[i]->x, graf->cvorovi[i]->y, graf->cvorovi[i]->r, graf->cvorovi[i]->indeks);
            CvorSusednosti *p = graf->susednosti[i].first;

            while (p) {
                printf("[%d] -> ", p->dest);
                p = p->next;
            }
            printf("none");
            putchar('\n');
        }
        else{
            printf("[%d NULL]\n", i);
        }
    }
}

void delGraf(Graf* graf, int n){
    int i, j;




    for(i=0; i < n; i++){
        CvorSusednosti *tek = graf->susednosti[i].first, *p;
        while(tek){
            p = tek;
            tek = tek->next;

            free(p);

        }

        free(graf->cvorovi[i]);

    }
    free(graf->susednosti);
    free(graf->cvorovi);
    free(graf);

}

int opcije(){
    int opcija;
    putchar('\n');
    printf("Izaberite jednu od opcija\n");
    printf("1. Dodaj cvor\n");
    printf("2. Izbrisi cvor\n");
    printf("3. Dodaj granu\n");
    printf("4. Obrisi granu\n");
    printf("5. Ispisi graf\n");
    printf("6. Zavrsi\n");
    printf("7. Mine\n");

    printf("Izbor: ");
    scanf("%d", &opcija);
    putchar('\n');

    return opcija;
}

int BFS(Graf* graf, int indeks, int n, int to_print){

    if(graf->cvorovi[indeks] == NULL) return 0;
    int i;
    int visit[n];
    int num = 1;
    for(i = 0; i < n; i++){
        visit[i] = 0;
    }
    visit[indeks] = 1;
    INSERT(graf->cvorovi[indeks]);
    if(to_print) {
        if(indeks != n) {

            printf("-%d-", graf->cvorovi[indeks]->indeks);
        }
        else{
            printf("-raketa-");
        }
    }

    while(!(front == - 1 || front > rear)){
        Cvor* v = DELETE();

        CvorSusednosti *tek, *p;
        tek = graf->susednosti[v->indeks].first;

        while(tek){
            if(!(visit[tek->dest])) {
                p = tek;
                if(to_print && !visit[tek->dest]) {
                    printf("%d-", p->dest);
                }
                visit[tek->dest] = 1;


                num++;

                INSERT(graf->cvorovi[p->dest]);
            }
            tek = tek->next;
        }
    }
    if(to_print) {
        putchar('\n');
    }
    return num;
}

float BFS_POVRSINA(Graf* graf, int indeks, int n){
    float ymin, ymax , xmin , xmax ;
    if(graf->cvorovi[indeks] == NULL) return 0;
    float povrsina;
    int i, j;
    int visit[n];
    int len = 0;

    for(i = 0; i < n; i++){
        visit[i] = 0;
    }
    visit[indeks] = 1;
    Cvor* cvorovi[n];

    INSERT(graf->cvorovi[indeks]);

    cvorovi[len++] = graf->cvorovi[indeks];
    while(!(front == - 1 || front > rear)){
        Cvor* v = DELETE();

        CvorSusednosti *tek, *p;
        tek = graf->susednosti[v->indeks].first;

        while(tek){
            if(!(visit[tek->dest])) {
                p = tek;
                cvorovi[len++] = graf->cvorovi[p->dest];
                visit[tek->dest] = 1;


                INSERT(graf->cvorovi[p->dest]);
            }
            tek = tek->next;
        }
    }


    float count = 0;
    ymin = -20;
    ymax = 20;
    xmax = 20;
    xmin = -20;
    for(i = 0; i < BROJ_SIM_TACAKA; i++){


        float rand_x = RandomFloat(xmin, xmax);
        float rand_y = RandomFloat(ymin, ymax);
        for(j = 0; j < len; j++){
            float d = sqrt(pow((cvorovi[j]->x - rand_x), 2) + pow((cvorovi[j]->y - rand_y), 2));
            if(d <= cvorovi[j]->r) {
                count++;
                break;
            }
        }
    }
    float rat;
    rat =  count / BROJ_SIM_TACAKA;
    povrsina = rat * ((xmax-xmin)*(ymax-ymin));
    printf("Povrsina: %f\n", povrsina);
    return povrsina;
}


int main() {
    time_t t;
    srand((unsigned) time(&t));
    int size;
    printf("Izaberite velicinu grafa: ");
    scanf("%d", &size);
    Graf* graf = napraviGraf(size);
    int is_mine = 0;
    while(1){
        int opcija;
        opcija = opcije();
        float x, y, r;
        int indeks, indeksod, indeksdo;
        int to_break = 0;
        char buffer;
        switch (opcija) {
            case 1:

                printf("(x, y, r):");
                scanf("%f %f %f", &x, &y, &r);
                dodajCvor(graf, x, y, r, size);
                break;
            case 2:
                printf("Indeks: ");
                scanf("%d", &indeks);
                delCvor(graf, size, indeks);
                break;
            case 3:
                printf("Indeks \"od\": ");
                scanf("%d", &indeksod);
                printf("Indeks \"do\": ");
                scanf("%d", &indeksdo);
                dodajGranu(graf, indeksod, indeksdo, size);
                break;
            case 4:
                printf("Indeks \"od\": ");
                scanf("%d", &indeksod);
                printf("Indeks \"do\": ");
                scanf("%d", &indeksdo);
                delGrana(graf, indeksod, indeksdo, size);
                break;
            case 5:
                printGraf(graf, size);
                printf("Enter...");
                getchar();
                scanf("%c", &buffer);
                break;
            case 6:
                delGraf(graf, size);
                to_break = 1;
                break;
            case 7:
                delGraf(graf, size);
                is_mine = 1;
                to_break = 1;

                break;

            default:
                printf("Molim vas jednu od datih opcija.");
                break;
        }


        if(to_break) break;
    }

    if(is_mine) {
        printf("Ime fajla: ");
        char fajl_name[256];
        scanf("%s", fajl_name);
        FILE *fajl = fopen(fajl_name, "r");

        int broj_mina;
        int i, j;
        fscanf(fajl, "%d", &broj_mina);

        fgetc(fajl);
        float x, y, r;

        Graf *graf_mine = napraviGraf(broj_mina+1);
        for (i = 0; i < broj_mina; i++) {
            fscanf(fajl, "%f %f %f", &x, &y, &r);
            dodajCvor(graf_mine, x, y, r, broj_mina);
        }

        for(i = 0; i < broj_mina; i++){
            for(j = 0; j < broj_mina; j++){
                if(i != j){
                    float d = sqrt(pow((graf_mine->cvorovi[i]->x - graf_mine->cvorovi[j]->x), 2) + pow((graf_mine->cvorovi[i]->y - graf_mine->cvorovi[j]->y), 2));
                    if(d <= graf_mine->cvorovi[i]->r){
                        dodajGranu(graf_mine, i, j, broj_mina);
                    }
                }
            }
        }

        char buffer;
        printGraf(graf_mine, broj_mina);
        putchar('\n');

        printf("Enter...");
        getchar();
        scanf("%c", &buffer);
        fclose(fajl);


        while(1){
            int to_break = 0;
            int opcija;
            int num;
            int t, curr, max, i_max;
            float ymin, ymax, xmin, xmax;
            float currx, curry;

            putchar('\n');
            printf("Izaberite jednu od opcija\n");
            printf("1. Nadji efikasnost mine\n");
            printf("2. Nadji najefikasniju minu\n");
            printf("3. Ispali raketu\n");
            printf("4. Povrsina najefikasnije\n");
            printf("5. Ispisi graf\n");
            printf("6. Zavrsi\n");

            printf("Izbor: ");
            scanf("%d", &opcija);
            putchar('\n');
            switch (opcija) {
                case 1:
                    printf("Indeks mine: ");
                    scanf("%d", &t);
                    num = BFS(graf_mine, t, broj_mina+1, 1);
                    printf("Efikasnost: %d\n", num);
                    printf("Enter...");
                    getchar();
                    scanf("%c", &buffer);
                    break;
                case 2:
                    max = 0;
                    i_max = 0;
                    for(i = 0; i < broj_mina-1; i++){
                        curr = BFS(graf_mine, i, broj_mina+1, 0);
                        if(curr > max){
                            max = curr;
                            i_max = i;
                        }
                    }
                    printf("Najefikasnija mina: %d\n", i_max);
                    printf("Efikasnost: %d\n", max);
                    printf("Enter...");
                    getchar();
                    scanf("%c", &buffer);
                    break;
                case 3:
                    printf("(x, y, r): ");
                    scanf("%f %f %f", &x, &y, &r);
                    dodajCvor(graf_mine, x, y, r, broj_mina+1);
                    for(i=0; i<broj_mina; i++){

                        float d = sqrt(pow((graf_mine->cvorovi[broj_mina]->x - graf_mine->cvorovi[i]->x), 2) + pow((graf_mine->cvorovi[broj_mina]->y - graf_mine->cvorovi[i]->y), 2));
                        if(d <= graf_mine->cvorovi[broj_mina]->r){
                            dodajGranu(graf_mine, broj_mina, i, broj_mina+1);
                        }
                    }
                    num = BFS(graf_mine, broj_mina, broj_mina, 1);
                    printf("Efikasnost: %d", num);
                    delCvor(graf_mine, broj_mina+1, broj_mina);
                    break;
                case 4:
                    max = 0;
                    i_max = 0;

                    for(i = 0; i < broj_mina; i++){
                        curr = BFS(graf_mine, i, broj_mina+1, 0);
                        if(curr > max){
                            curr = BFS(graf_mine, i, broj_mina+1, 0);
                            if(curr > max){
                                max = curr;
                                i_max = i;
                            }
                        }


                    }

                    BFS_POVRSINA(graf_mine, i_max, broj_mina+1);



                    printf("Enter...");
                    getchar();
                    scanf("%c", &buffer);
                    break;

                case 5:
                    printGraf(graf_mine, broj_mina);
                    printf("Enter...");
                    getchar();
                    scanf("%c", &buffer);
                    break;
                case 6:
                    delGraf(graf_mine, broj_mina+1);
                    to_break = 1;
                    break;


                default:
                    printf("Molim vas jednu od datih opcija.");
                    break;
            }
            if(to_break) break;
        }

    }
    return 0;
}
