#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Preke {
    int id;
    string pavadinimas;
    double kaina;
    int kiekis;
};

vector<Preke> prekes;

void loadFromFile() {
    ifstream file("prekes.txt");
    prekes.clear();

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Preke p;
        string temp;

        getline(ss, temp, ';');
        p.id = stoi(temp);

        getline(ss, p.pavadinimas, ';');

        getline(ss, temp, ';');
        p.kaina = stod(temp);

        getline(ss, temp, ';');
        p.kiekis = stoi(temp);

        prekes.push_back(p);
    }
    file.close();
}


void saveToFile() {
    ofstream file("prekes.txt");

    for (auto p : prekes) {
        file << p.id << ";"
             << p.pavadinimas << ";"
             << p.kaina << ";"
             << p.kiekis << endl;
    }

    file.close();
}


void showAll() {
    for (auto p : prekes) {
        cout << p.id << " | " << p.pavadinimas
             << " | " << p.kaina << "€"
             << " | kiekis: " << p.kiekis << endl;
    }
}


void addItem() {
    Preke p;

    cout << "ID: ";
    cin >> p.id;
    cin.ignore();

    cout << "Pavadinimas: ";
    getline(cin, p.pavadinimas);

    cout << "Kaina: ";
    cin >> p.kaina;

    cout << "Kiekis: ";
    cin >> p.kiekis;

    prekes.push_back(p);
}


void updateItem() {
    int id;
    cout << "Įveskite ID: ";
    cin >> id;

    for (auto &p : prekes) {
        if (p.id == id) {
            cout << "Nauja kaina: ";
            cin >> p.kaina;

            cout << "Naujas kiekis: ";
            cin >> p.kiekis;
            return;
        }
    }
    cout << "Prekė nerasta\n";
}

void deleteItem() {
    int id;
    cout << "Įveskite ID: ";
    cin >> id;

    prekes.erase(
        remove_if(prekes.begin(), prekes.end(),
            [id](Preke p) { return p.id == id; }),
        prekes.end()
    );
}


void searchItem() {
    string name;
    cin.ignore();
    cout << "Įveskite pavadinimą: ";
    getline(cin, name);

    for (auto p : prekes) {
        if (p.pavadinimas.find(name) != string::npos) {
            cout << p.id << " | " << p.pavadinimas
                 << " | " << p.kaina << endl;
        }
    }
}


void sortByPrice() {
    sort(prekes.begin(), prekes.end(),
        [](Preke a, Preke b) {
            return a.kaina < b.kaina;
        });
}


void showStats() {
    double suma = 0;

    for (auto p : prekes) {
        suma += p.kaina * p.kiekis;
    }

    cout << "Bendra sandėlio vertė: " << suma << " €\n";
}


void menu() {
    int pasirinkimas;

    do {
        cout << "\n--- MENIU ---\n";
        cout << "1. Rodyti visas prekes\n";
        cout << "2. Pridėti prekę\n";
        cout << "3. Redaguoti prekę\n";
        cout << "4. Ištrinti prekę\n";
        cout << "5. Paieška\n";
        cout << "6. Rikiuoti pagal kainą\n";
        cout << "7. Statistika\n";
        cout << "0. Išeiti\n";

        cin >> pasirinkimas;

        switch (pasirinkimas) {
            case 1: showAll(); break;
            case 2: addItem(); break;
            case 3: updateItem(); break;
            case 4: deleteItem(); break;
            case 5: searchItem(); break;
            case 6: sortByPrice(); break;
            case 7: showStats(); break;
            case 0: saveToFile(); break;
        }

    } while (pasirinkimas != 0);
}


int main() {
    loadFromFile();
    menu();
    return 0;
}