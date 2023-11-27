#include <iostream>
#include <fstream>
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

    void writeB(const char* filename) {
        ofstream out(filename, ios::binary | ios::out);
        int marcaLength = marca.length();
        out.write((char*)(&marcaLength), sizeof(int));
        out.write(marca.c_str(), marcaLength);
        
        out.write((char*)(&nrOreZbor), sizeof(int));
        out.write((char*)(&nrRevizii), sizeof(int));
        out.write((char*)(aniRevizii), sizeof(int) * nrRevizii);

        out.close();
      

    }

    void readB(const char* filename) {
        ifstream in(filename, ios::binary | ios::in);

        int marcaLength;
        in.read((char*)(&marcaLength), sizeof(int));
        char* marcaBuffer = new char[marcaLength + 1];
        in.read(marcaBuffer, marcaLength);
        marcaBuffer[marcaLength] = '\0';
        marca = marcaBuffer;
        delete[] marcaBuffer;

        in.read((char*)(&nrOreZbor), sizeof(int));
        in.read((char*)(&nrRevizii), sizeof(int));
        aniRevizii = new int[nrRevizii];
        in.read((char*)(aniRevizii), sizeof(int) * nrRevizii);

        in.close();

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

    //SUPRAINCARCARE OPERATORI

    Avion operator=(const Avion& avion) {
        if (this != &avion) {
            this->marca = avion.marca;
            this->nrOreZbor = avion.nrOreZbor;
            this->nrRevizii = avion.nrRevizii;

            if (this->aniRevizii != nullptr)
                delete[]this->aniRevizii;

            this->aniRevizii = new int[this->nrRevizii];

            for (int i = 0; i < nrRevizii; i++) {
                this->aniRevizii[i] = avion.aniRevizii[i];
            }
        }
        return *this;
    }

    Avion operator+(const Avion& avion) {
        Avion aux = *this;
        aux.nrOreZbor += avion.nrOreZbor;
        aux.nrRevizii += avion.nrRevizii;
        if (aux.aniRevizii != nullptr)
            delete[]aux.aniRevizii;
        aux.aniRevizii = new int[aux.nrRevizii];
        for (int i = 0; i <= this->nrRevizii; i++)
            aux.aniRevizii[i] = this->aniRevizii[i];
        for (int i = 0; i <= avion.nrRevizii; i++)
            aux.aniRevizii[i + this->nrRevizii] = avion.aniRevizii[i];
        return aux;

    }

    Avion operator-(const Avion& avion) {
        Avion aux = *this;
        aux.nrOreZbor -= avion.nrOreZbor;

        return aux;
    }

     bool operator==(const Avion& avion) const{
         return (this->serie == avion.serie && this->nrOreZbor == avion.nrOreZbor);
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
    friend istream& operator>>(istream&, Avion&);

    friend ofstream& operator<<(ofstream& out, const Avion& avion)
    {
        out << avion.marca << "\n" << avion.nrOreZbor << "\n" << avion.nrRevizii << "\n";
        for (int i = 0; i < avion.nrRevizii; i++)
            out << avion.aniRevizii[i] << " ";
        out << "\n";
        return out;
    }

    friend ifstream& operator>>(ifstream& in, Avion& avion)
    {

        in >> avion.marca;
        in >> avion.nrOreZbor;
        in >> avion.nrRevizii;
        if (avion.aniRevizii != nullptr)
        {
            delete[]avion.aniRevizii;
        }
        avion.aniRevizii = new int[avion.nrRevizii];
        for (int i = 0; i < avion.nrRevizii; i++)
        {
            in >> avion.aniRevizii[i];
        }
        return in;
    }

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
    //SUPRAINCARCARE OPERATORI

    Roata operator=(const Roata& roata) {
        if (this != &roata) {
            this->varsta = roata.varsta;
            this->nrPane = roata.nrPane;

            if (this->luniRealizarePana != nullptr)
                delete[]this->luniRealizarePana;

            this->luniRealizarePana = new string[this->nrPane];

            for (int i = 0; i < this->nrPane; i++) {
                this->luniRealizarePana[i] = roata.luniRealizarePana[i];
            }
        }
        return *this;
    }

    bool operator!=(const Roata& roata) const {
        return !(this->pozitie == roata.pozitie && this->varsta == roata.varsta && this->nrPane == roata.nrPane);
    }

    bool operator<(const Roata& roata) const {
        return this->varsta < roata.varsta;
    }
    
    Roata operator+=(const Roata& roata) {
        this->varsta += roata.varsta;
        int nrPaneNou = this->nrPane + roata.nrPane;

        string* luniRealizarePanaNou = new string[nrPaneNou];

        for (int i = 0; i < this->nrPane; i++) {
            luniRealizarePanaNou[i] = this->luniRealizarePana[i];
        }

        for (int i = 0; i < roata.nrPane; i++) {
            luniRealizarePanaNou[i + this->nrPane] = roata.luniRealizarePana[i];
        }

        delete[] this->luniRealizarePana;
        this->luniRealizarePana = luniRealizarePanaNou;
        this->nrPane = nrPaneNou;
        return *this;
    }



    //CONSTRUCTORI

    Roata() : pozitie("Fata") {
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
    friend istream& operator>>(istream&, Roata&);

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

    void writeB(const char* filename) {
        ofstream out(filename, ios::binary | ios::out);
        int marcaLength = marca.length();
        out.write((char*)(&marcaLength), sizeof(int));
        out.write(marca.c_str(), marcaLength);

        out.write((char*)(&numarVoci), sizeof(int));
        for (int i = 0; i < numarVoci; ++i) {
            int length = numeleVocilor[i].length();
            out.write((char*)(&length), sizeof(int));
            out.write(numeleVocilor[i].c_str(), length);
        }

        out.close();
    }

    void readB(const char* filename) {
        ifstream in(filename, ios::binary | ios::in);
        int marcaLength;
        in.read((char*)(&marcaLength), sizeof(int));
        char* marcaBuffer = new char[marcaLength + 1];
        in.read(marcaBuffer, marcaLength);
        marcaBuffer[marcaLength] = '\0';
        marca = marcaBuffer;
        delete[] marcaBuffer;

        in.read((char*)(&numarVoci), sizeof(int));
        numeleVocilor = new string[numarVoci];
        for (int i = 0; i < numarVoci; ++i) {
            int length;
            in.read((char*)(&length), sizeof(int));
            char* buffer = new char[length + 1];
            in.read(buffer, length);
            buffer[length] = '\0';
            numeleVocilor[i] = buffer;
            delete[] buffer;
        }

        in.close();
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

    //SUPRAINCARCARE OPERATORI

    Navigatie operator=(const Navigatie& navigatie) {
        if (this != &navigatie) {
            this->marca = navigatie.marca;
            this->numarVoci = navigatie.numarVoci;

            if (this->numeleVocilor != nullptr)
                delete[]this->numeleVocilor;

            this->numeleVocilor = new string[this->numarVoci];

            for (int i = 0; i < this->numarVoci; i++) {
                this->numeleVocilor[i] = navigatie.numeleVocilor[i];
            }
        }
        return *this;
    }

    bool operator<=(const Navigatie& navigatie) const {
        return this->numarVoci <= navigatie.numarVoci;
    }


    //CONSTRUCTORI

    Navigatie() : limba("Engleza") {
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

    Navigatie(string marca, int numarVoci, string* numeleVocilor) : limba("Engleza") {
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
    friend ostream& operator<<(ostream&, Navigatie);
    friend istream& operator>>(istream&, Navigatie&);
    friend ofstream& operator<<(ofstream& out, const Navigatie& navigatie)
    {
        out << navigatie.marca << "\n" << navigatie.numarVoci << "\n";
        for (int i = 0; i < navigatie.numarVoci; i++)
            out << navigatie.numeleVocilor[i] << " ";
        out << "\n";
        return out;
    }

    friend ifstream& operator>>(ifstream& in, Navigatie& navigatie)
    {

        in >> navigatie.marca;
        in >> navigatie.numarVoci;
        if (navigatie.numeleVocilor != nullptr)
        {
            delete[]navigatie.numeleVocilor;
        }
        navigatie.numeleVocilor = new string[navigatie.numarVoci];
        for (int i = 0; i < navigatie.numarVoci; i++)
        {
            in >> navigatie.numeleVocilor[i];
        }
        return in;
    }
};

string Navigatie::tipConectivitate = "Satelit";


class Hangar {
private:
    bool esteOperational;
    int suprafata;
    int numarAvioane;
    Avion* avioane;
public:
    //get si set

    bool getEsteOperational() const {
        return this->esteOperational;
    }
    void setEsteOperational(bool este) {
        this->esteOperational = este;
    }

    int getSuprafata() const {
        return this->suprafata;
    }

    void setSuprafata(int numar) {
        this->suprafata = numar;
    }

    int getNumarAvioane() const {
        return this->numarAvioane;
    }

    Avion* getAvioane() {
        return this->avioane;
    }

    void setNumarAvioane(int numar, Avion* avioane) {
        numarAvioane = numar;
        if (this->avioane != nullptr) {
            delete[]avioane;
        }
        this->avioane = new Avion[numarAvioane];

        for (int i = 0; i < this->numarAvioane; i++)
            this->avioane[i] = avioane[i];
    }

    //constructori
    Hangar(): esteOperational(1), suprafata(100), numarAvioane(0), avioane(nullptr) {
    }
    Hangar(bool esteOperational, int suprafata, int numarAvioane, Avion* avioane) {
        this->esteOperational = esteOperational;
        this->suprafata = suprafata;
        this->numarAvioane = numarAvioane;
        this->avioane = new Avion[numarAvioane];
        for (int i = 0; i < this->numarAvioane; i++) {
            this->avioane[i] = avioane[i];
        }
    }

    Hangar(const Hangar& hangar) {
        this->esteOperational = hangar.esteOperational;
        this->suprafata = hangar.suprafata;
        this->numarAvioane = 0;
        this->avioane = new Avion[numarAvioane];
        for (int i = 0; i < this->numarAvioane; i++) {
            this->avioane[i] = hangar.avioane[i];
        }
    }


    ~Hangar() {
        delete[] avioane;
    }

    //Supraincarcare operatori

    Hangar& operator=(const Hangar& hangar) {
        if (this != &hangar) {
            this->esteOperational = hangar.esteOperational;
            this->suprafata = hangar.suprafata;
            this->numarAvioane = hangar.numarAvioane;
            if (avioane != nullptr) {
                delete[]this->avioane;
            }
            avioane = new Avion[this->numarAvioane];
            for (int i = 0; i < hangar.numarAvioane; ++i) {
                avioane[i] = hangar.avioane[i];
            }
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Hangar& hangar) {
        cout << "\nEste operational? (1 da, 0 nu)";
        in >> hangar.esteOperational;
        cout << "\nSuprafata: ";
        in >> hangar.suprafata;
        cout << "\nNumar avioane: ";
        in>> hangar.numarAvioane;
        hangar.avioane = new Avion[hangar.numarAvioane];
        cout << "\nCitire Avioane: ";
        for (int i = 0; i < hangar.numarAvioane; ++i) {
            in >> hangar.avioane[i];
        }
        cout << "\n";

        return in;
    }

    friend ostream& operator<<(ostream& out, const Hangar& hangar) {
        out << "Hangar este " << (hangar.esteOperational ? "operational." : "neoperational.") << endl;
        out << "Suprafata hangarului: " << hangar.suprafata << " metri patrati." << endl;
        out << "Numarul actual de avioane: " << hangar.numarAvioane << endl;
        out << "Avioanele din hangar:" << endl;
        for (int i = 0; i < hangar.numarAvioane; i++) {
            hangar.avioane[i].afisare();
        }
        return out;
    }



};


//SUPRAINCARCARE OPERATORI
ostream& operator<<(ostream& out, Navigatie nav) {

    out << "Sistemul de navigatie conectat prin: " << nav.tipConectivitate << " de la marca: " << nav.marca << " ofera indicatii in limba " << nav.limba;

    if (nav.numarVoci) {
        out << " are un numar de: " << nav.numarVoci << " voci. Vocile sunt denumite dupa cum urmeaza: ";
        for (int i = 0; i < nav.numarVoci; i++)
            out << nav.numeleVocilor[i] << " ";
        out << "\n \n";
    }
    else {
        out << " Insa nu exista momentan voci instalate.\n \n";
    }

    return out;

}

istream& operator>>(istream& in, Navigatie& navigatie) {
    cout << "Introduceti marca:";
    in >> navigatie.marca;
    cout << "Introduceti numarul de voci:";
    in >> navigatie.numarVoci;
    if (navigatie.numeleVocilor != nullptr) {
        delete[]navigatie.numeleVocilor;
    }
    navigatie.numeleVocilor = new string[navigatie.numarVoci];

    for (int i = 0; i < navigatie.numarVoci; i++) {
        cout << "Numele vocii " << i +1 << " : ";
        in >> navigatie.numeleVocilor[i];
    }

    return in;
}

istream& operator>>(istream& in, Roata& roata) {
    cout << "Introduceti varsta rotii:";
    in >> roata.varsta;
    cout << "Introduceti numarul de pane:";
    in >> roata.nrPane;
    if (roata.luniRealizarePana != nullptr) {
        delete[]roata.luniRealizarePana;
    }
    roata.luniRealizarePana = new string[roata.nrPane];

    for (int i = 0; i < roata.nrPane; i++) {
        cout << "Luna in care s-a realizat pana " << i + 1 << ": ";
        in >> roata.luniRealizarePana[i];
    }

    return in;
}

istream& operator>>(istream& in, Avion& avion) {
    cout << "Introduceti marca avionului:";
    in >> avion.marca;
    cout << "Introduceti numarul orelor de zbor:";
    in >> avion.nrOreZbor;
    cout << "Introduceti numarul de revizii:";
    in >> avion.nrRevizii;

    if (avion.aniRevizii != nullptr) {
        delete[]avion.aniRevizii;
    }
    avion.aniRevizii = new int[avion.nrRevizii];

    for (int i = 0; i < avion.nrRevizii; i++) {
        cout << "Anul in care a fost realizata revizia " << i + 1 << ": ";
        in >> avion.aniRevizii[i];
    }

    return in;
}

//FUNCTII GLOBALE PRIETENE

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
    float raportrev = 0.1f;
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

    ////FAZA 1
    //cout << "\n \n FAZA 1 \n \n";
    //cout << "Clasa Avion: \n";
    //Avion avion;
    //avion.afisare();
    //int aniRevizii_1[] = { 2005, 2006, 2007 };
    //Avion avion1("2BZQN580", "Cesna", 200000, 3, aniRevizii_1);
    //avion1.afisare();
    //Avion avion2("Boeing", 74000);
    //avion2.afisare();
    //avion2.adaugareRevizie(2023);
    //avion2.afisare();

    //cout << "\nClasa Roata: \n";
    //Roata roata;
    //roata.afisare();
    //string luni_pane_1[] = { "ianuarie", "februarie" };
    //Roata roata1("Spate", 1, 2, luni_pane_1);
    //roata1.afisare();
    //Roata roata2("Fata", 4);
    //roata2.afisare();
    //roata2.crestereVarstaUnAn();
    //roata2.afisare();

    //cout << "\nClasa Navigatie: \n";
    //Navigatie navigatie;
    //navigatie.afisare();
    //string nume_voci_1[] = { "Carmen", "Marius" };
    //Navigatie navigatie1("Italiana", "Garmin", 2, nume_voci_1);
    //navigatie1.afisare();
    //string nume_voci_2[] = { "Andrei", "Maria", "Doina"};
    //Navigatie navigatie2("Nokia", 3, nume_voci_2);
    //navigatie2.afisare();
    //navigatie2.instalareVoce("Elena");
    //navigatie2.afisare();
    //
    ////FAZA 2
    //cout << "\n \n FAZA 2 \n \n";
    ////functionalitate operator de copiere
    //cout << "\nFunctionalitate operator de copiere: \n";

    //Avion avion3 = avion2;
    //Roata roata3 = roata2;
    //Navigatie navigatie3 = navigatie2;

    //cout << "\n \n";
    //if (avion3.getSerie() == avion2.getSerie()) cout << "TRUE \n";
    //else cout << "FALSE\n";
    //if (roata3.getPozitie() == roata2.getPozitie()) cout << "TRUE \n";
    //else cout << "FALSE\n";
    //if (navigatie3.getTipConectivitate() == navigatie2.getTipConectivitate()) cout << "TRUE \n";
    //else cout << "FALSE\n";
    //cout << "\n \n";


    ////functionalitate functii prietene
    //cout << "\nFunctionalitate functii prietene: \n";
    //mentenantaAeronava(avion1, roata1, navigatie1);
    //cout << "\n";
    //calculIndiciStare(avion1, roata1, navigatie1);

    ////functionalitae get-eri
    //cout << "\nFunctionalitate get-eri: \n";

    ////Clasa Avion
    //cout << "Avionul cu seria de sasiu: " << avion2.getSerie() << " de marca: " << avion2.getMarca() << " inmatriculat in tara: " << avion2.getTaraInmatriculare() << " are un numar de: " << avion2.getNrOreZbor() << " ore de zbor. ";
    //if (avion2.getNrRevizii()) {
    //    cout << "Acesteia i - au fost facute : " << avion2.getNrRevizii() << " revizii \n" << "Reviziile au fost realizate in anii: ";
    //    for (int i = 0; i < avion2.getNrRevizii(); i++)
    //        cout << avion2.getAniRevizii()[i] << " ";
    //    cout << "\n \n";
    //}
    //else {
    //    cout << "Nu au fost efectuate revizii.\n \n";
    //}

    ////Clasa Roata
    //cout << "Roata pozitionata: " << roata2.getPozitie() << " cu pneul fabricat din: " << roata2.getMaterialPneu() << " are o varsta de: " << roata2.getVarsta() << " ani. ";
    //if (roata2.getNrPane()) {
    //    cout << "Acesteia a avut pana de: " << roata2.getNrPane() << " ori \n" << "Panele au fost facute in lunile: ";
    //    for (int i = 0; i < roata2.getNrPane(); i++)
    //        cout << roata2.getLuniRealizarePana()[i] << " ";
    //    cout << "\n \n";
    //}
    //else {
    //    cout << "Roata nu a avut pana pana acum.\n \n";
    //}

    ////Clasa Navigatie
    //cout << "Sistemul de navigatie conectat prin: " << navigatie2.getTipConectivitate() << " de la marca: " << navigatie2.getMarca() << " ofera indicatii in limba " << navigatie2.getLimba();
    //if (navigatie2.getNumarVoci()) {
    //    cout << " are un numar de: " << navigatie2.getNumarVoci() << " voci. Vocile sunt denumite dupa cum urmeaza: ";
    //    for (int i = 0; i < navigatie2.getNumarVoci(); i++)
    //        cout << navigatie2.getNumeleVocilor()[i] << " ";
    //    cout << "\n \n";
    //}
    //else {
    //    cout << " Insa nu exista momentan voci instalate.\n \n";
    //}

    //// functionalitate set-eri
    //cout << "\nFunctionalitate set-eri: \n";
    //avion2.setMarca("Airbus");
    //avion2.setNrOreZbor(55000);
    //int* anirevizii_3 = new int[5] {1999, 1993, 1994, 2009, 2023};
    //avion2.setAniRevizii(5, anirevizii_3);
    //avion2.setTaraInmatriculare("Bulgaria");

    //avion2.afisare();

    //roata2.setMaterialPneu("Naylon");
    //roata2.setVarsta(12);
    //string* luni = new string[3]{ "ianuaria", "martie", "mai" };
    //roata2.setLuniRealizarePana(3, luni);

    //roata2.afisare();

    //navigatie2.setMarca("sygic");
    //navigatie2.setTipConectivitate("Radio");
    //string* numevoci_3 = new string[2]{ "Loredana", "Mihai" };
    //navigatie2.setNumeleVocilor(2, numevoci_3);

    //navigatie2.afisare();

    ////FAZA 3

    //Avion avion4;
    //avion4.afisare();
    ////Operator =
    //avion4 = avion1;
    //avion4.afisare();
    ////operator +
    //avion4 = avion4 + avion4;
    //avion4.afisare();
    ////operator -
    //cout << "operator -" << '\n';
    //cout <<"inainte: "<< avion4.getNrOreZbor() << '\n';
    //avion4 = avion4 - avion1;
    //cout << "dupa: " << avion4.getNrOreZbor() << '\n';
    ////operator==
    //cout << "operator ==" << '\n';
    //cout << "Sunt identice avioanele? ";
    //if (avion4 == avion4) cout << "DA sunt!\n";
    //else cout << "NU sunt!\n";

    //cout << "\n \n";

    //Roata roata4;
    //roata4.afisare();
    ////Operator =
    //roata4 = roata2;
    //roata4.afisare();
    ////Operator !=
    //cout << "Sunt diferite rotile? ";
    //if (roata4 != roata1) cout << "DA sunt!\n";
    //else cout << "NU sunt!\n";
    ////Operator <
    //cout << "Este prima roata mai noua decat a 2 a? ";
    //if (roata4 < roata1) cout << "DA este!\n";
    //else cout << "NU este!\n";
    ////Operator +=
    //cout << "\n";
    //roata4 += roata3;
    //roata4.afisare();

    //cout << "\n \n";


    //Navigatie navigatie4;
    //navigatie4.afisare();
    ////Operator =
    //navigatie4 = navigatie3;
    //navigatie4.afisare();
    ////Operator <<
    //cout << "Functionalitate operator << \n";
    //cout << navigatie4;
    ////Operator <=
    //cout << "Are prima navigatie un numar de voci mai mic sau egal fata de a doua? ";
    //if (navigatie4 <= navigatie1) cout << "DA are!\n";
    //else cout << "NU are!\n";
    ////Operator >>
    //cout << "Functionalitate operator >> \n";
    //cin >> navigatie4;
    //cout << navigatie4;


    ////FAZA 4

    ////Vector avion
    //int numarElemente = 0;
    //cout << "Introduceti numarul de avioane pe care doriti sa le aveti in vector:";
    //cin >> numarElemente;
    //Avion* vAvion = new Avion[numarElemente];
    //for (int i = 0; i < numarElemente; i++) {
    //    cout << "Citire avion " << i + 1 << " :\n";
    //    cin >> vAvion[i];
    //}

    //for (int i = 0; i < numarElemente; i++) {
    //    cout << "Avionul cu numarul " << i + 1 << "\n";
    //    vAvion[i].afisare();
    //    cout << "\n";
    //}

    ////Vector roata
    //numarElemente = 0;
    //cout << "Introduceti numarul de roti pe care doriti sa le aveti in vector:";
    //cin >> numarElemente;
    //Roata* vRoata = new Roata[numarElemente];
    //for (int i = 0; i < numarElemente; i++) {
    //    cout << "Citire roata " << i + 1 << " :\n";
    //    cin >> vRoata[i];
    //}

    //for (int i = 0; i < numarElemente; i++) {
    //    cout << "Roata cu numarul " << i + 1 << "\n";
    //    vRoata[i].afisare();
    //    cout << "\n";
    //}

    ////Vector navigatie
    //numarElemente = 0;
    //cout << "Introduceti numarul de navigatii pe care doriti sa le aveti in vector:";
    //cin >> numarElemente;
    //Navigatie* vNavigatie = new Navigatie[numarElemente];
    //for (int i = 0; i < numarElemente; i++) {
    //    cout << "Citire navigatia " << i + 1 << " :\n";
    //    cin >> vNavigatie[i];
    //}

    //for (int i = 0; i < numarElemente; i++) {
    //    cout << "Navigatia cu numarul " << i + 1 << "\n";
    //    vNavigatie[i].afisare();
    //    cout << "\n";
    //}

    ////Matricea la alegere (Avioane)

    //int linii = 0, coloane = 0;
    //cout << "Introduceti numatul de linii ale matricei: ";
    //cin >> linii;
    //cout << "Introduceti numatul de coloane ale matricei: ";
    //cin >> coloane;

    //Avion** mAvion = new Avion * [linii];
    //for (int i = 0; i < linii; i++) {
    //    mAvion[i] = new Avion[coloane];
    //}

    //for (int i = 0; i < linii; i++) {
    //    for (int j = 0; j < coloane; j++) {
    //        cout << "Citire avion de pe linia " << i + 1 << " si coloana " << j + 1 << "\n";
    //        cin >> mAvion[i][j];
    //    }
    //}

    //for (int i = 0; i < linii; i++) {
    //    for (int j = 0; j < coloane; j++) {
    //        cout << "Afisare avion de pe linia " << i + 1 << " si coloana " << j + 1 << "\n";
    //        mAvion[i][j].afisare();
    //    }
    //}


    ////Eliberare memorie

    //if (linii != 0) {
    //    for (int i = 0; i < linii; ++i)
    //        delete[] mAvion[i];
    //}

    //if (mAvion != nullptr) {
    //    delete[] mAvion;
    //}

    //if (vAvion != nullptr) {
    //    delete[]vAvion;
    //}
    //if (vRoata != nullptr) {
    //    delete[]vRoata;
    //}
    //if (vNavigatie != nullptr) {
    //    delete[]vNavigatie;
    //}

    ////FAZA 5

    //Hangar hangar;

    //cin >> hangar;

    //cout << hangar.getEsteOperational();
    //Hangar hangar2 = hangar;
    //Hangar hangar3;
    //hangar3 = hangar2;
    //cout << hangar;
    //cout << hangar3;

    //FAZA 6
    //prima clas txt
    ofstream aviOut("avioane.txt", ios::out);
    Avion avion10;
    cin >> avion10;
    aviOut << avion10;
    aviOut.close();
    ifstream aviIn("avioane.txt", ios::in);
    Avion avion11;
    aviIn >> avion11;
    avion11.afisare();
    aviIn.close();
    //a doua clasa txt
    ofstream navOut("roti.txt", ios::out);
    Navigatie navigatie10;
    cin >> navigatie10;
    navOut << navigatie10;
    navOut.close();
    ifstream navIn("roti.txt", ios::in);
    Navigatie navigatie11;
    navIn >> navigatie11;
    navigatie11.afisare();
    navIn.close();

    //prima clasa fisier binar
    
    Avion avion12, avion13;
    cin >> avion12;
    avion12.writeB("avioane.bin");
    avion13.readB("avioane.bin");
    avion13.afisare();

    //a doua clasa fisier binar

    Navigatie navigatie12, navigatie13;
    cin >> navigatie12;
    navigatie12.writeB("navigatii.bin");
    navigatie13.readB("navigatii.bin");
    navigatie13.afisare();
    return 0;
}