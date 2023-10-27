#include <iostream>
using namespace std;

// Cele 3 obiecte se numesc: Avion, Roata si Navigatie si fac parte din domeniul aeronavelor
// Fiecare obiect are cate o functie prorprie: Pentru avion este adaugata o revizie, pentru Roata este crescut numarul de ani iar pentru navigatie este instalata o noua voce.


class Roata;
class Navigatie;

class Avion {
private:
    const string serie;
    static string taraInmatriculare;
    string marca;
    int nrOreZbor;
    int nrRevizii;
    int* aniRevizii;
public:
    //GET SI SET
    string getSerie() const {
        return serie;
    }

    static string getTaraInmatriculare() {
        return taraInmatriculare;
    }

    static void setTaraInmatriculare(string taraInmatriculare) {
        Avion::taraInmatriculare = taraInmatriculare;
    }

    string getMarca() {
        return marca;
    }

    void setMarca( string marca) {
        this->marca = marca;
    }

    int getNrOreZbor() {
        return nrOreZbor;
    }

    void setNrOreZbor(int nrOreZbor) {
        this->nrOreZbor = nrOreZbor;
    }

    int getNrRevizii() {
        return nrRevizii;
    }


    int* getAniRevizii()  {
        return this->aniRevizii;
    }

    void setAniRevizii(int nrRevizii, int* aniRevizii) {

        if (nrRevizii > 0) {
            this->nrRevizii = nrRevizii;
            if (this->aniRevizii != nullptr) {
                delete[]this->aniRevizii;
            }
            this->aniRevizii = new int[this->nrRevizii];
            for (int i = 0; i < this->nrRevizii; i++) {
                this->aniRevizii[i] = aniRevizii[i];
            }
        }
    }

    //METODE

    void afisare() {
        cout << "Avionul cu seria de sasiu: " << this->serie << " de marca: " << this->marca << " inmatriculat in tara: " << this->taraInmatriculare << " are un numar de: " << this->nrOreZbor << " ore de zbor. ";
            
        if (this->nrRevizii) {
            cout << "Acesteia i - au fost facute : " << this->nrRevizii << " revizii \n" << "Reviziile au fost realizate in anii: ";
            for (int i = 0; i < this->nrRevizii; i++)
                cout << this->aniRevizii[i] << " ";
            cout << "\n \n";
        }
        else {
            cout << "Nu au fost efectuate revizii.\n \n";
        }
    }

    void adaugareRevizie(int an) {
        int* aux = new int[this->nrRevizii + 1];
        for (int i = 0; i < this->nrRevizii; i++) {
            aux[i] = this->aniRevizii[i];
        }
        aux[nrRevizii] = an;
        if(this->aniRevizii!=nullptr)
            delete[] this->aniRevizii;
        this->aniRevizii = aux;
        this->nrRevizii++;
    }

    //CONSTRUCTORI
    Avion() : serie("9JHWX735") {
        this->marca = "NoName";
        this->nrOreZbor = 0;
        this->nrRevizii = 0;
        this->aniRevizii = nullptr;
    }

    Avion(string serie, string marca, int nrOreZbor, int nrRevizii, int* aniRevizii) : serie(serie) {
        this->marca = marca;
        this->nrOreZbor = nrOreZbor;
        this->nrRevizii = nrRevizii;
        this->aniRevizii = new int[nrRevizii];
        for (int i = 0; i < nrRevizii; i++) {
            this->aniRevizii[i] = aniRevizii[i];
        }
    }

    Avion(const Avion& avion) : serie(avion.serie) {
        this->marca = avion.marca;
        this->nrOreZbor = avion.nrOreZbor;
        this->nrRevizii = avion.nrRevizii;
        this->aniRevizii = new int[this->nrRevizii];
        for (int i = 0; i < this->nrRevizii; i++) {
            this->aniRevizii[i] = avion.aniRevizii[i];
        }
    }

    Avion(string marca, int nrOreZbor) : serie("9JHWX735") {
        this->marca = marca;
        this->nrOreZbor = nrOreZbor;
        this->nrRevizii = 0;
        this->aniRevizii = nullptr;
    }

    ~Avion() {
        if (this->aniRevizii != nullptr) {
            delete[] this->aniRevizii;
        }
    }

    friend void mentenantaAeronava(Avion &, Roata &, Navigatie &);
    friend void calculIndiciStare(Avion&, Roata&, Navigatie&);

};

string Avion::taraInmatriculare = "Romania";


class Roata {
private:
    const string pozitie;
    static string materialPneu;
    int varsta;
    int nrPane;
    string* luniRealizarePana;

public:
    //GET SI SET
    string getPozitie() const {
        return pozitie;
    }

    static string getMaterialPneu() {
        return materialPneu;
    }

    static void setMaterialPneu( string materialPneu) {
        Roata::materialPneu = materialPneu;
    }

    int getVarsta(){
        return varsta;
    }

    void setVarsta(int varsta) {
        this->varsta = varsta;
    }

    int getNrPane() {
        return nrPane;
    }

    string* getLuniRealizarePana() {
        return luniRealizarePana;
    }

    void setLuniRealizarePana(int nrPane, string* luniRealizarePana) {
        if (nrPane > 0) {
                this->nrPane = nrPane;
                if (this->luniRealizarePana != nullptr) {
                    delete[]this->luniRealizarePana;
                }
                this->luniRealizarePana = new string[this->nrPane];
                for (int i = 0; i < this->nrPane; i++) {
                    this->luniRealizarePana[i] = luniRealizarePana[i];
                }
     
        }
    }

    //METODE

    void afisare() {
        cout << "Roata pozitionata: " << this->pozitie << " cu pneul fabricat din: " << this->materialPneu << " are o varsta de: " << this->varsta << " ani. ";

        if (this->nrPane) {
            cout << "Acesteia a avut pana de: " << this->nrPane << " ori \n" << "Panele au fost facute in lunile: ";
            for (int i = 0; i < this->nrPane; i++)
                cout << this->luniRealizarePana[i] << " ";
            cout << "\n \n";
        }
        else {
            cout << "Roata nu a avut pana pana acum.\n \n";
        }
    }

    void crestereVarstaUnAn() {
        this->varsta++;
    }

    //CONSTRUCTORI

    Roata() : pozitie("Dreapta Fata") {
        this->varsta = 0;
        this->nrPane = 0;
        this->luniRealizarePana = nullptr;
    }

    Roata(string pozitie, int varsta, int nrPane, string* luniRealizarePana) : pozitie(pozitie) {
        this->varsta = varsta;
        this->nrPane = nrPane;
        this->luniRealizarePana = new string[nrPane];
        for (int i = 0; i < nrPane; i++) {
            this->luniRealizarePana[i] = luniRealizarePana[i];
        }
    }

    Roata(const Roata& roata) :pozitie(roata.pozitie) {
        this->varsta = roata.varsta;
        this->nrPane = roata.nrPane;
        this->luniRealizarePana = new string[this->nrPane];
        for (int i = 0; i < this->nrPane; i++) {
            this->luniRealizarePana[i] = roata.luniRealizarePana[i];
        }
    }

    Roata(string pozitie, int varsta) : pozitie(pozitie) {
        this->varsta = varsta;
        this->nrPane = 0;
        this->luniRealizarePana = nullptr;
    }

    ~Roata() {
        if (this->luniRealizarePana != nullptr) {
            delete[] this->luniRealizarePana;
        }
    }

    friend void mentenantaAeronava(Avion&, Roata&, Navigatie&);
    friend void calculIndiciStare(Avion&, Roata&, Navigatie&);
};

string Roata::materialPneu = "Cauciuc";


class Navigatie {
private:
    const string limba;
    static string tipConectivitate;
    string marca;
    int numarVoci;
    string* numeleVocilor;
public:
    //GET  SI SET

    string getLimba() const {
        return limba;
    }

    static string getTipConectivitate() {
        return tipConectivitate;
    }

    static void setTipConectivitate( string tipConectivitate) {
        Navigatie::tipConectivitate = tipConectivitate;
    }

    string getMarca()  {
        return marca;
    }

    void setMarca(const string& marca) {
        this->marca = marca;
    }

    int getNumarVoci() {
        return numarVoci;
    }

    void setNumarVoci(int newNumarVoci) {
        this->numarVoci = newNumarVoci;
    }

    string* getNumeleVocilor() {
        return numeleVocilor;
    }

    void setNumeleVocilor(int numarVoci, string* numeleVocilor) {
        if (numarVoci > 0) {
            this->numarVoci = numarVoci;
            if (this->numeleVocilor != nullptr) {
                delete[]this->numeleVocilor;
            }
            this->numeleVocilor = new string[this->numarVoci];
            for (int i = 0; i < this->numarVoci; i++) {
                this->numeleVocilor[i] = numeleVocilor[i];
            }

        }
    }
    //METODE

    void afisare() {
        cout << "Sistemul de navigatie conectat prin: " << this->tipConectivitate << " de la marca: " << this->marca << " ofera indicatii in limba " << this->limba;

        if (this->numarVoci) {
            cout << " are un numar de: " << this->numarVoci << " voci. Vocile sunt denumite dupa cum urmeaza: ";
            for (int i = 0; i < this->numarVoci; i++)
                cout << this->numeleVocilor[i] << " ";
            cout << "\n \n";
        }
        else {
            cout << " Insa nu exista momentan voci instalate.\n \n";
        }
    }

    void instalareVoce(const string& numeNou) {

        if (this->numeleVocilor == nullptr) {
            this->numeleVocilor = new string[1];
            this->numarVoci = 1;
            this->numeleVocilor[0] = numeNou;
        }
        else {
   
            string* aux = new string[this->numarVoci + 1];

            for (int i = 0; i < this->numarVoci; i++) {
                aux[i] = numeleVocilor[i];
            }
            aux[this->numarVoci] = numeNou;


            this->numarVoci++;

            delete[] this->numeleVocilor;

            this->numeleVocilor = aux;
        }
    }

    //CONSTRUCTORI

    Navigatie() : limba("Romana") {
        this->marca = "Google";
        this->numarVoci = 0;
        this->numeleVocilor = nullptr;
    }

    Navigatie(string limba, string marca, int numarVoci, string* numeleVocilor) : limba(limba) {
        this->marca = marca;
        this->numarVoci = numarVoci;

        this->numeleVocilor = new string[numarVoci];
        for (int i = 0; i < numarVoci; i++) {
            this->numeleVocilor[i] = numeleVocilor[i];
        }

    }

    //Constructorul de copiere
    Navigatie(const Navigatie& navigatie):limba(navigatie.limba) {
        this->marca = navigatie.marca;
        this->numarVoci = navigatie.numarVoci;

        this->numeleVocilor = new string[this->numarVoci];
        for (int i = 0; i < this->numarVoci; i++) {
            this->numeleVocilor[i] = navigatie.numeleVocilor[i];
        }
    }

    Navigatie(string marca, int numarVoci, string* numeleVocilor) : limba("Romana") {
        this->marca = marca;
        this->numarVoci = numarVoci;

        this->numeleVocilor = new string[this->numarVoci];
        for (int i = 0; i < numarVoci; i++) {
            this->numeleVocilor[i] = numeleVocilor[i];
        }
    }

    ~Navigatie() {
        if (this->numeleVocilor != nullptr) {
            delete[] this->numeleVocilor;
        }
    }

    friend void mentenantaAeronava(Avion&, Roata& , Navigatie& );
    friend void calculIndiciStare(Avion&, Roata&, Navigatie&);

};

string Navigatie::tipConectivitate = "Satelit";

//FUNCTII GLOBALE

void mentenantaAeronava(Avion& avion, Roata& roata, Navigatie& navigatie) {
    cout << "Se va realiza mentenanta avionului cu seria: " << avion.serie << "ce are un numar de: " << avion.nrOreZbor<<"\n";


    //Roata este schimbata daca are un numar de pane mai mare de 3 sau o varsta mai mare de 12 luni
    if (roata.nrPane > 3 || roata.varsta > 12) {
        roata.nrPane = 0;
        roata.varsta = 0;
        string* empty = new string[0];
        roata.setLuniRealizarePana(0, empty);
    }

    cout << "Starea rotilor dupa mentenanta:\n";
    roata.afisare();
    //Navigatiile de la google nu mai sunt permise deci trebuie schimbate cu unele garmin care au memoria compatibila.
    if (navigatie.getMarca() == "Google") {
        navigatie.setMarca("Garmin");
    }

    if (navigatie.numarVoci == 0 || navigatie.numeleVocilor == nullptr){
        navigatie.instalareVoce("DefaulAndreea");
    }

    cout << "Starea navigatiei dupa mentenanta:\n";
    navigatie.afisare();

    avion.adaugareRevizie(2023);
}

void calculIndiciStare(Avion& avion, Roata& roata, Navigatie& navigatie) {
    float raportrev = 0.1;
    if (avion.nrRevizii && avion.nrOreZbor) raportrev = avion.nrRevizii / (float)avion.nrOreZbor;
    cout << "Raportul reviziilor in functie de numarul orelor de zbor: " << raportrev << "\n";
    cout << "Trebuie realizata o mentenanta anul acesta? : ";
    if (avion.aniRevizii[avion.nrRevizii] == 2023) cout << "NU\n";
    else cout << "Da\n";
    float raport;
    if (roata.varsta > 0 && roata.nrPane > 0)
         raport = (float)roata.varsta / (float)roata.nrPane;
    else  raport = 0;
    cout << "Raportul intre varsta rotii si numarul de pane: " << raport << "\n \n";
}

int main() {

    //FAZA 1
    cout << "\n \n FAZA 1 \n \n";
    cout << "Clasa Avion: \n";
    Avion avion;
    avion.afisare();
    int aniRevizii_1[] = { 2005, 2006, 2007 };
    Avion avion1("2BZQN580", "Cesna", 200000, 3, aniRevizii_1);
    avion1.afisare();
    Avion avion2("Boeing", 74000);
    avion2.afisare();
    avion2.adaugareRevizie(2023);
    avion2.afisare();

    cout << "\nClasa Roata: \n";
    Roata roata;
    roata.afisare();
    string luni_pane_1[] = { "ianuarie", "februarie" };
    Roata roata1("Spate", 1, 2, luni_pane_1);
    roata1.afisare();
    Roata roata2("Fata", 4);
    roata2.afisare();
    roata2.crestereVarstaUnAn();
    roata2.afisare();

    cout << "\nClasa Navigatie: \n";
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
    
    //FAZA 2
    cout << "\n \n FAZA 2 \n \n";
    //functionalitate operator de copiere
    cout << "\nFunctionalitate operator de copiere: \n";

    Avion avion3 = avion2;
    Roata roata3 = roata2;
    Navigatie navigatie3 = navigatie2;

    cout << "\n \n";
    if (avion3.getSerie() == avion2.getSerie()) cout << "TRUE \n";
    else cout << "FALSE\n";
    if (roata3.getPozitie() == roata2.getPozitie()) cout << "TRUE \n";
    else cout << "FALSE\n";
    if (navigatie3.getTipConectivitate() == navigatie2.getTipConectivitate()) cout << "TRUE \n";
    else cout << "FALSE\n";
    cout << "\n \n";


    //functionalitate functii prietene
    cout << "\nFunctionalitate functii prietene: \n";
    mentenantaAeronava(avion1, roata1, navigatie1);
    cout << "\n";
    calculIndiciStare(avion1, roata1, navigatie1);

    //functionalitae get-eri
    cout << "\nFunctionalitate get-eri: \n";

    //Clasa Avion
    cout << "Avionul cu seria de sasiu: " << avion2.getSerie() << " de marca: " << avion2.getMarca() << " inmatriculat in tara: " << avion2.getTaraInmatriculare() << " are un numar de: " << avion2.getNrOreZbor() << " ore de zbor. ";
    if (avion2.getNrRevizii()) {
        cout << "Acesteia i - au fost facute : " << avion2.getNrRevizii() << " revizii \n" << "Reviziile au fost realizate in anii: ";
        for (int i = 0; i < avion2.getNrRevizii(); i++)
            cout << avion2.getAniRevizii()[i] << " ";
        cout << "\n \n";
    }
    else {
        cout << "Nu au fost efectuate revizii.\n \n";
    }

    //Clasa Roata
    cout << "Roata pozitionata: " << roata2.getPozitie() << " cu pneul fabricat din: " << roata2.getMaterialPneu() << " are o varsta de: " << roata2.getVarsta() << " ani. ";
    if (roata2.getNrPane()) {
        cout << "Acesteia a avut pana de: " << roata2.getNrPane() << " ori \n" << "Panele au fost facute in lunile: ";
        for (int i = 0; i < roata2.getNrPane(); i++)
            cout << roata2.getLuniRealizarePana()[i] << " ";
        cout << "\n \n";
    }
    else {
        cout << "Roata nu a avut pana pana acum.\n \n";
    }

    //Clasa Navigatie
    cout << "Sistemul de navigatie conectat prin: " << navigatie2.getTipConectivitate() << " de la marca: " << navigatie2.getMarca() << " ofera indicatii in limba " << navigatie2.getLimba();
    if (navigatie2.getNumarVoci()) {
        cout << " are un numar de: " << navigatie2.getNumarVoci() << " voci. Vocile sunt denumite dupa cum urmeaza: ";
        for (int i = 0; i < navigatie2.getNumarVoci(); i++)
            cout << navigatie2.getNumeleVocilor()[i] << " ";
        cout << "\n \n";
    }
    else {
        cout << " Insa nu exista momentan voci instalate.\n \n";
    }

    // functionalitate set-eri
    cout << "\nFunctionalitate set-eri: \n";
    avion2.setMarca("Airbus");
    avion2.setNrOreZbor(55000);
    int* anirevizii_3 = new int[5] {1999, 1993, 1994, 2009, 2023};
    avion2.setAniRevizii(5, anirevizii_3);
    avion2.setTaraInmatriculare("Bulgaria");

    avion2.afisare();

    roata2.setMaterialPneu("Naylon");
    roata2.setVarsta(12);
    string* luni = new string[3]{ "ianuaria", "martie", "mai" };
    roata2.setLuniRealizarePana(3, luni);

    roata2.afisare();

    navigatie2.setMarca("sygic");
    navigatie2.setTipConectivitate("Radio");
    string* numevoci_3 = new string[2]{ "Loredana", "Mihai" };
    navigatie2.setNumeleVocilor(2, numevoci_3);

    navigatie2.afisare();

    return 0;
}