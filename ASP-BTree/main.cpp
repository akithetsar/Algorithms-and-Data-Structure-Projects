#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

// Zapis iz Customer tabele
struct Customer {
    int c_id; // Primarni kljuc
    string c_f_name; // Ime
    string c_l_name; // Prezime
    string c_email_1; // Mejl
    int c_ad_id; // Spoljašnji kljuc koji nije bitan
};


// Zapis iz CustomerAccount tabele
typedef struct CustomerAccount {

    unsigned long long ca_id; // Primarni kljuc
    unsigned long long ca_b_id; // Neki unutrasnji podatak
    unsigned long long ca_c_id; //spoljašnji ključ na Customer
    string name; //ime accounta
    int ca_tax_st; //neki podatak
    double ca_bal; //neki podatak

} Account;


// Data je id customer i njegovi accountovi
typedef struct Data {
    unsigned long long ca_c_id;
    vector<Account> accounts;
} Data;


// BStablo
class BStablo {
private:

    // Jedan cvor B-stabla, cuva decu u children, a id i accountove u data
    typedef struct BNode {

        vector<BNode *> children;
        vector<Data> data;
        bool isLeaf;
        struct BNode *parent;

    } BNode;

public:
    //Konstruktor praznog stabla reda m
    BStablo(int mm) : m(mm), root(nullptr), height(0) {}

    int CreateIndex(const string file);

    void Search(unsigned long long c_id, string file);

    bool insertAccount(const Account &acc);

    bool deleteAccount(const Account &acc);

    bool deleteCustomerInfo(unsigned long long c_id);

    void print();

public:
    BNode *root;
private:
    int m;
    int height;

};


bool BStablo::insertAccount(const Account &acc) {

    BNode *curr = root;
    stack<BNode *> prevStack;

    bool splitted = false;
    //Ako je prazno napravi root
    if (!curr) {
        root = new BNode;
        Data newData;
        newData.ca_c_id = acc.ca_c_id;
        newData.accounts.push_back(acc);
        root->data.push_back(newData);
        root->isLeaf = true;
        return true;
    }
    prevStack.push(nullptr);



    // Nadji list gde treba da ubacimo ACC
    while (!curr->isLeaf) {
        // Ako nije prazno
        for (int i = 0; i < curr->data.size(); i++) {
            //Ako vec postoji ID
            if (curr->data[i].ca_c_id == acc.ca_c_id) {
                curr->data[i].accounts.push_back(acc);
                return true;
            }

            // Ako je manji od trenutnog key idi levo
            if (curr->data[i].ca_c_id > acc.ca_c_id) {
                prevStack.push(curr);
                curr = curr->children[i];
                break;
            } else if (curr->data[i].ca_c_id < acc.ca_c_id && i == curr->data.size() - 1) {
                prevStack.push(curr);
                curr = curr->children[i + 1];
                break;
            }
        }

    }

    bool addEnd = true;
    for (int i = 0; i < curr->data.size(); i++) {

        //Ako vec postoji ID u listu insertuj acc
        if (curr->data[i].ca_c_id == acc.ca_c_id) {
            curr->data[i].accounts.push_back(acc);

            return true;
        }
        //Insertuj na mesto gde treba da bude
        if (curr->data[i].ca_c_id > acc.ca_c_id) {
            Data newData;
            newData.accounts.push_back(acc);
            newData.ca_c_id = acc.ca_c_id;
            curr->data.insert(curr->data.cbegin() + i, newData);
            addEnd = false;

            break;
        }
    }
    if (addEnd) {
        //Stavi na kraj ako je najveci u nizu
        Data newData;
        newData.accounts.push_back(acc);
        newData.ca_c_id = acc.ca_c_id;
        curr->data.push_back(newData);
    }
    //Ako je pun splituj

    while (curr->data.size() == m) {

        BNode *prev = prevStack.top();
        prevStack.pop();
        //AKO SE ROOT SPLITUJE
        if (!prev) {


            BNode *left = new BNode;
            BNode *right = new BNode;
            BNode *newRoot = new BNode;
            if (!splitted) {
                left->isLeaf = true;
                right->isLeaf = true;
            } else {
                left->isLeaf = false;
                right->isLeaf = false;

            }
            newRoot->isLeaf = false;
            int middle = (m + 1) / 2;

            //Ubaci sredinu u novi root
            newRoot->data.push_back(curr->data[middle]);

            //Ubaci levo od sredine u levi
            for (int i = 0; i < middle; i++) {
                left->data.push_back(curr->data[i]);
            }

            if (splitted) {
                for (int i = 0; i < middle + 1; i++) {
                    left->children.push_back(curr->children[i]);
                }
            }

            //Ubaci desno od sredine u desni
            for (int i = middle + 1; i < curr->data.size(); i++) {
                right->data.push_back(curr->data[i]);
            }
            if (splitted) {
                for (int i = middle + 1; i < curr->children.size(); i++) {
                    right->children.push_back(curr->children[i]);
                }
            }
            newRoot->children.push_back(left);
            newRoot->children.push_back(right);
            delete root;
            root = newRoot;

            return true;
        }
            //AKO SE NESTO DRUGO SPLITUJE
        else {
            BNode *left = new BNode;
            BNode *right = new BNode;

            if (!splitted) {
                left->isLeaf = true;
                right->isLeaf = true;
            } else {
                left->isLeaf = false;
                right->isLeaf = false;
            }

            int middle = (m + 1) / 2;

            int i;
            for (i = 0; i < prev->data.size(); i++) {

                //Insertuj na mesto gde treba da bude
                if (prev->data[i].ca_c_id > acc.ca_c_id) {
                    prev->data.insert(prev->data.cbegin() + i, curr->data[middle]);
                    addEnd = false;
                    break;
                }
            }
            if (addEnd) {
                //Stavi na kraj ako je najveci u nizu
                prev->data.push_back(curr->data[middle]);
            }




            //Ubaci levo od sredine u levi
            for (int i = 0; i < middle; i++) {
                left->data.push_back(curr->data[i]);
            }
            if (splitted) {
                for (int i = 0; i < middle + 1; i++) {
                    left->children.push_back(curr->children[i]);
                }
            }


            //Ubaci desno od sredine u desni
            for (int i = middle + 1; i < curr->data.size(); i++) {
                right->data.push_back(curr->data[i]);
            }
            if (splitted) {
                for (int i = middle + 1; i < curr->children.size(); i++) {
                    right->children.push_back(curr->children[i]);
                }
            }
            prev->children[i] = left;
            prev->children.insert(prev->children.cbegin() + i + 1, right);
            prev->isLeaf = false;
            delete curr;
            curr = prev;
            splitted = true;

        }

    }

    return true;
}

int BStablo::CreateIndex(const string file) {
    ifstream myfile(file);

    if (!myfile.is_open()) {
        std::cout << "Could not open file!\n";
        return -1;
    }


    string line;

    while (getline(myfile, line)) {
        vector<string> res;
        int pos = 0;
        for (int i = 0; i < 6; i++) {
            pos = line.find("|");
            res.push_back(line.substr(0, pos));
            line.erase(0, pos + 1); // 3 is the length of the delimiter, "%20"
        }

        Account new_acc;
        new_acc.ca_id = stoull(res[0]);
        new_acc.ca_b_id = stoull(res[1]);
        new_acc.ca_c_id = stoull(res[2]);
        new_acc.name = res[3];
        new_acc.ca_tax_st = stoi(res[4]);
        new_acc.ca_bal = stod(res[5]);
        this->insertAccount(new_acc);
    }
    myfile.close();
    return 1;
}

void BStablo::Search(unsigned long long c_id, string file) {
    int br_koraka = 0;
    BNode *curr = root;

    //Ako je prazno
    if (!curr) {
        cout << "Stablo je prazno";
    }

    //Nadji accounts
    vector<Account> accounts;
    while (curr) {
        br_koraka++;
        bool to_break = false;
        for (int i = 0; i < curr->data.size(); i++) {
            //Ako vec postoji ID
            if (curr->data[i].ca_c_id == c_id) {
                accounts = curr->data[i].accounts;
                to_break = true;
                break;
            }
            // Ako je manji od trenutnog key idi levo
            if (curr->data[i].ca_c_id > c_id) {
                if (curr->children.empty()) {
                    curr = nullptr;
                    break;
                }
                curr = curr->children[i];
                break;
            } else if (curr->data[i].ca_c_id < c_id && i == curr->data.size() - 1) {
                if (curr->children.empty()) {
                    curr = nullptr;
                    break;
                }
                curr = curr->children[i + 1];
                break;
            }
        }
        if (to_break) break;
    }

    if (!curr) {
        cout << "Korisnik nije otvorio racun nijednom";
        return;
    }
    ifstream myfile(file);
    ofstream towrite("C:\\Users\\akith\\CLionProjects\\aspDom2TAKE2\\Search.txt");
    if (!myfile.is_open()) {
        std::cout << "Could not open file!\n";
        return;
    }
    if (!towrite.is_open()) {
        std::cout << "Could not open file!\n";
        return;
    }

    string line;

    while (getline(myfile, line)) {
        vector<string> res;
        br_koraka++;
        int pos = 0;
        for (int i = 0; i < 6; i++) {
            pos = line.find("|");
            res.push_back(line.substr(0, pos));
            line.erase(0, pos + 1); // 3 is the length of the delimiter, "%20"
        }
        //Ako je taj customer
        if (stoull(res[0]) == c_id) {
            if (accounts.empty()) {
                towrite << res[0] << '|' << res[1] << '|' << res[2] << '|' << res[3] << '|' << "null" << '|' << "null"
                        << '|' << "null" << '|' << "null";
            } else {
                for (auto account: accounts) {
                    towrite << res[0] << '|' << res[1] << '|' << res[2] << '|' << res[3] << '|' << account.ca_id << '|'
                            << account.ca_c_id << '|' << account.ca_tax_st << '|' << account.ca_b_id << endl;
                }
            }
            cout << "BR KORAKA: " << br_koraka << endl;

            return;
        }

    }
}

bool BStablo::deleteCustomerInfo(unsigned long long c_id) {
    BNode *curr = root;
    int br_koraka = 0;
    //Ako je prazno
    if (!curr) {
        cout << "Stablo je prazno";
    }

    //Nadji accounts
    vector<Account> *accounts;
    while (curr) {
        br_koraka++;
        bool to_break = false;
        for (int i = 0; i < curr->data.size(); i++) {
            //Ako vec postoji ID
            if (curr->data[i].ca_c_id == c_id) {
                accounts = &(curr->data[i].accounts);
                to_break = true;
                break;
            }
            // Ako je manji od trenutnog key idi levo
            if (curr->data[i].ca_c_id > c_id) {
                if (curr->children.empty()) {
                    curr = nullptr;
                    break;
                }
                curr = curr->children[i];
                break;
            } else if (curr->data[i].ca_c_id < c_id && i == curr->data.size() - 1) {
                if (curr->children.empty()) {
                    curr = nullptr;
                    break;
                }
                curr = curr->children[i + 1];
                break;
            }
        }
        if (to_break) break;
    }

    if (!curr) {
        cout << "Korisnik nije otvorio racun nijednom";
        cout << "BR KORAKA: " << br_koraka << endl;

        return false;
    }

    accounts->clear();
    cout << "BR KORAKA: " << br_koraka << endl;


    return true;

}

void BStablo::print() {

    if (!root) {
        cout << "Prazno stablo" << endl;
        return;
    }

    queue<BNode *> bnode_q;
    bnode_q.push(root);

    while (!bnode_q.empty()) {

        int numOfNodes = bnode_q.size();

        for (int i = 0; i < numOfNodes; ++i) {
            BNode *current = bnode_q.front();
            bnode_q.pop();
            for (auto &data : current->data) {
                cout << data.ca_c_id << " ";
            }
            cout << " | ";
            for (auto &child : current->children) {
                if (child) {
                    bnode_q.push(child);
                }
            }
        }
        cout << endl;
        cout << string(m * 8 * numOfNodes , '-');  // Adjust spacing as needed
        cout << endl;
    }
}

void dodaj(BStablo stablo) {
    Account new_acc;
    cout << "Ukucaj atribute racuna: " << endl;
    cout << "CA_ID: ";
    cin >> new_acc.ca_id;
    cout << "CA_B_ID: ";
    cin >> new_acc.ca_b_id;
    cout << "CA_C_ID: ";
    cin >> new_acc.ca_c_id;
    cout << "CA_NAME: ";
    cin >> new_acc.name;
    cout << "CA_TAX_ST: ";
    cin >> new_acc.ca_tax_st;
    cout << "CA_BAL: ";
    cin >> new_acc.ca_bal;

    stablo.insertAccount(new_acc);

}


int main() {

    int m;
    cout << "Unesi m stabla: ";
    cin >> m;
    string fajl;
    cout << "Unesi customer account fajl: ";
    cin >> fajl;

    BStablo novo_stablo{m};

    novo_stablo.CreateIndex(fajl);
    bool program = true;
    while (program) {
        unsigned long long opcija;
        cout << "0. Zavrsi program" << endl;
        cout << "1. Ispisi stablo" << endl;
        cout << "2. Dodaj racun" << endl;
        cout << "3. Obrisi racun" << endl;
        cout << "4. Obrisi sve racune jednog korisnika" << endl;
        cout << "5. Pretrazi stablo" << endl;
        cout << "Izaberi opciju: ";
        cin >> opcija;


        switch (opcija) {
            case 0:
                program = false;
                break;
            case 1:
                novo_stablo.print();
                break;
            case 2:
                dodaj(novo_stablo);
                break;
            case 3:
                cout << "DELETE";
                break;
            case 4:
                cout << "ID? ";
                unsigned long long id_c;
                cin >> id_c;
                novo_stablo.deleteCustomerInfo(id_c);
                break;
            case 5:
                cout << "ID? ";
                unsigned long long id;
                cin >> id;
                novo_stablo.Search(id, "C:\\Users\\akith\\CLionProjects\\aspDom2TAKE2\\Customer.txt");
                break;
            default:
                cout << "Izaberite jednu od opcija" << endl;
        }

    }

    return 0;
}