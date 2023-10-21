#include <iostream>
using namespace std;

// Cele 3 obiecte se numesc: Avion, Roata si Navigatie si fac parte din domeniul aeronavelor
// Fiecare obiect are cate o functie prorprie: Pentru avion este adaugata o revizie, pentru Roata este crescut numarul de ani iar pentru navigatie este instalata o noua voce.


class Avion {
public:
    const string serie;
    static string tara_inmatriculare;
    string marca;
    int nr_ore_zbor;
    int nr_revizii;
    int* ani_revizii;

    void afisare() {
        cout << "Avionul cu seria de sasiu: " << this->serie << " de marca: " << this->marca << " inmatriculat in tara: " << this->tara_inmatriculare << " are un numar de: " << this->nr_ore_zbor << " ore de zbor. ";
            
        if (this->nr_revizii) {
            cout << "Acesteia i - au fost facute : " << this->nr_revizii << " revizii \n" << "Reviziile au fost realizate in anii: ";
            for (int i = 0; i < this->nr_revizii; i++)
                cout << this->ani_revizii[i] << " ";
            cout << "\n \n";
        }
        else {
            cout << "Nu au fost efectuate revizii.\n \n";
        }
    }

    void adaugareRevizie(int an) {
        int* aux = new int[this->nr_revizii + 1];
        for (int i = 0; i < this->nr_revizii; i++) {
            aux[i] = this->ani_revizii[i];
        }
        aux[nr_revizii] = an;
        delete[] this->ani_revizii;
        this->ani_revizii = aux;
        this->nr_revizii++;
    }

    Avion() : serie("9JHWX735") {
        this->marca = "NoName";
        this->nr_ore_zbor = 0;
        this->nr_revizii = 0;
        this->ani_revizii = nullptr;
    }

    Avion(string serie, string marca, int nr_ore_zbor, int nr_revizii, int* ani_revizii) : serie(serie) {
        this->marca = marca;
        this->nr_ore_zbor = nr_ore_zbor;
        this->nr_revizii = nr_revizii;
        this->ani_revizii = new int[nr_revizii];
        for (int i = 0; i < nr_revizii; i++) {
            this->ani_revizii[i] = ani_revizii[i];
        }
    }

    Avion(string marca, int nr_ore_zbor) : serie("9JHWX735") {
        this->marca = marca;
        this->nr_ore_zbor = nr_ore_zbor;
        this->nr_revizii = 0;
        this->ani_revizii = nullptr;
    }

    ~Avion() {
        if (this->ani_revizii != nullptr) {
            delete[] this->ani_revizii;
        }
    }
};

string Avion::tara_inmatriculare = "Romania";


class Roata {
public:
    const string pozitie;
    static string material_pneu;
    int varsta;
    int nr_pane;
    string* luni_realizare_pana;

    void afisare() {
        cout << "Roapta pozitionata: " << this->pozitie << " cu pneul fabricat din: " << this->material_pneu << " are o varsta de: " << this->varsta << " ani. ";

        if (this->nr_pane) {
            cout << "Acesteia a avut pana de: " << this->nr_pane << " ori \n" << "Panele au fost facute in lunile: ";
            for (int i = 0; i < this->nr_pane; i++)
                cout << this->luni_realizare_pana[i] << " ";
            cout << "\n \n";
        }
        else {
            cout << "Roata nu a avut pana pana acum.\n \n";
        }
    }

    void crestereVarstaUnAn() {
        this->varsta++;
    }

    Roata() : pozitie("Dreapta Fata") {
        this->varsta = 0;
        this->nr_pane = 0;
        this->luni_realizare_pana = nullptr;
    }

    Roata(string pozitie, int varsta, int nr_pane, string* luni_realizare_pana) : pozitie(pozitie) {
        this->varsta = varsta;
        this->nr_pane = nr_pane;
        this->luni_realizare_pana = new string[nr_pane];
        for (int i = 0; i < nr_pane; i++) {
            this->luni_realizare_pana[i] = luni_realizare_pana[i];
        }
    }

    Roata(string pozitie, int varsta) : pozitie(pozitie) {
        this->varsta = varsta;
        this->nr_pane = 0;
        this->luni_realizare_pana = nullptr;
    }

    ~Roata() {
        if (this->luni_realizare_pana != nullptr) {
            delete[] this->luni_realizare_pana;
        }
    }
};

string Roata::material_pneu = "Cauciuc";


class Navigatie {
public:
    const string limba;
    static string tip_conectivitate;
    string marca;
    int numar_voci;
    string* numele_vocilor;

    void afisare() {
        cout << "Sistemul de navigatie conectat prin: " << this->tip_conectivitate << " de la marca: " << this->marca << " ofera indicatii in limba " << this->limba;

        if (this->numar_voci) {
            cout << " are un numar de: " << this->numar_voci << " voci. Vocile sunt denumite dupa cum urmeaza: ";
            for (int i = 0; i < this->numar_voci; i++)
                cout << this->numele_vocilor[i] << " ";
            cout << "\n \n";
        }
        else {
            cout << " Insa nu exista momentan voci instalate.\n \n";
        }
    }
    void instalareVoce( string numeVoce) {
        string* aux = new string[this->numar_voci + 1];

        for (int i = 0; i < this->numar_voci; i++) {
            aux[i] = this->numele_vocilor[i];
        }

        aux[this->numar_voci] = numeVoce;

        delete[] this->numele_vocilor; 

        this->numele_vocilor = aux; 

        this->numar_voci++;
    }


    Navigatie() : limba("Romana") {
        this->marca = "Google";
        this->numar_voci = 0;
        this->numele_vocilor = nullptr;
    }

    Navigatie(string limba, string marca, int numar_voci, string* numele_vocilor) : limba(limba) {
        this->marca = marca;
        this->numar_voci = numar_voci;
        this->numele_vocilor = new string[numar_voci];

        for (int i = 0; i < numar_voci; i++) {
            this->numele_vocilor[i] = numele_vocilor[i];
        }

    }


    Navigatie(string marca, int numar_voci, string* numele_vocilor) : limba("Romana") {
        this->marca = marca;
        this->numar_voci = numar_voci;

        this->numele_vocilor = new string[numar_voci];
        for (int i = 0; i < numar_voci; i++) {
            this->numele_vocilor[i] = numele_vocilor[i];
        }
    }

    ~Navigatie() {
        if (this->numele_vocilor != nullptr) {
            delete[] this->numele_vocilor;
        }
    }
};

string Navigatie::tip_conectivitate = "Satelit";

int main() {
    Avion avion;
    avion.afisare();
    int ani_revizii_1[] = { 2005, 2006, 2007 };
    Avion avion1("2BZQN580", "Cesna", 200000, 3, ani_revizii_1);
    avion1.afisare();
    Avion avion2("Boeing", 74000);
    avion2.afisare();
    avion2.adaugareRevizie(2023);
    avion2.afisare();

    Roata roata;
    roata.afisare();
    string luni_pane_1[] = { "ianuarie", "februarie" };
    Roata roata1("Spate", 4, 2, luni_pane_1);
    roata1.afisare();
    Roata roata2("Fata", 4);
    roata2.afisare();
    roata2.crestereVarstaUnAn();
    roata2.afisare();

    Navigatie navigatie;
    navigatie.afisare();
    string nume_voci_1[] = { "Carmen", "Marius" };
    Navigatie navigatie1("Italiana", "Garmin", 2, nume_voci_1);
    navigatie1.afisare();
    string nume_voci_2[] = { "Andrei", "Maria", "Doina"};
    Navigatie navigatie2("Nokia", 3, nume_voci_2);
    navigatie2.afisare();
    navigatie2.instalareVoce("Elena");
    navigatie2.afisare();
    return 0;
}