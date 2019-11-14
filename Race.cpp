//Michał J
//RaceSystem

#include <iostream>
#include <fstream>
using namespace std;

struct Zawodnik{
    string nazwisko;
    string imie;
    string numerPrawaJazdy;
    string numerRejestracyjny;
    Zawodnik *nastepny;
    Zawodnik();
};

Zawodnik::Zawodnik()
{
    nastepny = NULL;
}

struct ListaZawodnikow
{
    Zawodnik *pierwszaOsoba;
    Zawodnik *ostatniaOsoba;
    void utworzListeZPliku(bool &czyPustaLista, int ileInfoWczytac, int &ileJestElementowListy, string &nazwaPlikuDoOdczytu);
    void dodajDaneRecznie(string nazwisko, string imie, string numerPrawaJazdy, string numerRejestracyjny, int &ileJestElementowListy);
    void usunZawodnika(int nr, bool &czyPustaLista, int &ileJestElementowListy);
    void pokaz(int ileJestElementowListy);
    void szukaj(int opcjaWew);
    void dodajVIP(int &ileJestElementowListy);
    void usunPierwszego(int &ileJestElementowListy,bool &czyPustaLista);
    void sortuj();
    ListaZawodnikow();
};

ListaZawodnikow::ListaZawodnikow()                  //konstuktorem  tworząc listę odrazu tworzę rejest o polu "nastepny"=NULL
{
    pierwszaOsoba=NULL;
}

void ListaZawodnikow::utworzListeZPliku(bool &czyPustaLista, int ileInfoWczytac, int &ileJestElementowListy, string &nazwaPlikuDoOdczytu){
    string nazwaPliku;
    Zawodnik *aktualny, *ogon=ostatniaOsoba, *glowa=pierwszaOsoba;
    string kosz;
    int ileElementowPrzetworzono=0;
    if(czyPustaLista==1){
        glowa=NULL;
        aktualny=NULL;
        ogon=NULL;
    }
    else{
        aktualny=glowa;
        while(aktualny->nastepny!=NULL)
            aktualny=aktualny->nastepny;
        ogon=aktualny;
    }
    string im, naz, nrRA, nrPJ; //imie, nazwisko, nrRejestracynyAuta, nrPrawaJazdy
    ifstream dane;

    do{
        if(czyPustaLista==1){
            cout<<"Podaj poprawna nazwe pliku do odczytu danych:\n";
            cin>>nazwaPliku;
            nazwaPlikuDoOdczytu=nazwaPliku;
            cin.get(); // czyta ewentualny bufor
        }
        else
            nazwaPliku=nazwaPlikuDoOdczytu;

        dane.open(nazwaPliku.c_str());
        if(!dane.is_open()){        //jeśli błąd otwarcia
            dane.close();   //zamknij
            dane.clear();   // wyczyść
        }
    }
    while(!dane.is_open()); // dopóki nie otwarto pliku

    for(int i=0; i < ileJestElementowListy; i++)
        getline(dane, kosz);

    while(!(dane.eof()||ileElementowPrzetworzono==ileInfoWczytac)){
        aktualny = new Zawodnik;      //miejsce dla nowego elementu
        dane>>naz>>im>>nrRA>>nrPJ;
        aktualny->imie=im;
        aktualny->nazwisko=naz;
        aktualny->numerPrawaJazdy=nrPJ;
        aktualny->numerRejestracyjny=nrRA;
        aktualny->nastepny=NULL;
        if(glowa==NULL){
            glowa=aktualny;
            ogon=aktualny;
        }
        else
        {
            ogon->nastepny=aktualny;
            ogon=ogon->nastepny;
        }
        ileElementowPrzetworzono++;
        ileJestElementowListy++;
        czyPustaLista=0;
    }
    pierwszaOsoba=glowa;
    ostatniaOsoba=ogon;
}

void ListaZawodnikow::dodajDaneRecznie(string nazwisko, string imie, string numerPrawaJazdy, string numerRejestracyjny,int &ileJestElementowListy)
{
    Zawodnik *noweDane = new Zawodnik;
    noweDane->imie=imie;
    noweDane->nazwisko=nazwisko;
    noweDane->numerPrawaJazdy=numerPrawaJazdy;
    noweDane->numerRejestracyjny=numerRejestracyjny;

    if(pierwszaOsoba==NULL) //to dodajemy na początek
    {
        pierwszaOsoba=noweDane;
    }
    else //szukamy ogona
    {
        Zawodnik *tmp= pierwszaOsoba;
        while(tmp->nastepny!=NULL)
            tmp=tmp->nastepny;

        tmp->nastepny=noweDane; // dodajemy nowe el na koniec listy
        noweDane->nastepny=NULL;
    }
    ileJestElementowListy++;
}

void ListaZawodnikow::pokaz(int ileJestElementowListy)
{
    if(ileJestElementowListy!=0){
        Zawodnik *tmp = pierwszaOsoba;
        int numer=1;
        while(tmp!=NULL)
        {
            cout<<numer<<". imie: "<<tmp->imie<<", nazwisko: "<<tmp->nazwisko<<",nr prawa jazdy: "<<tmp->numerPrawaJazdy;
            cout<<",nr rej.: "<<tmp->numerRejestracyjny<<"\n";
            tmp=tmp->nastepny;
            numer++;
        }
    }
}

void ListaZawodnikow::usunZawodnika(int nr,bool &czyPustaLista,int &ileJestElementowListy) //nr to nr osoby indeksując od 1 za którą usuwamy kolejną
{
    if(nr==0) //usuwam głowe
    {
        Zawodnik *tmp=pierwszaOsoba;
        pierwszaOsoba = pierwszaOsoba->nastepny;
        delete tmp;
        czyPustaLista=0;
        ileJestElementowListy=0;
    }
    else
    {
        int i=0;
        Zawodnik *tmp = pierwszaOsoba;
        Zawodnik *tmpmniejjednen = NULL;
        while(i<nr) // znajdujemy element za którym usuwamy
        {
            if(tmp->nastepny==NULL)
            {
                //doszlismy do ogona listy niechcący
                cout<<"hola hola";
                return;
            }
            tmpmniejjednen=tmp;
            tmp = tmp->nastepny;

            i++;
        }
        if(tmp->nastepny==NULL) //mamy ogon bo chcieliśmy
        {
            tmpmniejjednen->nastepny=NULL;
        }
        else
        {
            Zawodnik *tenOut = tmpmniejjednen->nastepny;
            tmpmniejjednen->nastepny=tenOut->nastepny;
            delete tenOut;
            ileJestElementowListy--;
        }
    }
}

void ListaZawodnikow::szukaj(int opcjaWew){
    Zawodnik *aktualny=pierwszaOsoba;
    int numer=1;
    cout<<"Podaj szukane dane:\n";
    string danaSzukana;
    bool czyCosSiePokazalo=0;
    cin>>danaSzukana;
    cout<<"Wyniki wyszukiwania:\n";
    if(opcjaWew == 1){
        while(aktualny!=NULL){
            if(danaSzukana==aktualny->imie){
                cout<<numer<<". imie: "<<aktualny->imie<<", nazwisko: "<<aktualny->nazwisko<<",nr prawa jazdy: "<<aktualny->numerPrawaJazdy;
                cout<<",nr rej.: "<<aktualny->numerRejestracyjny<<"\n";
                czyCosSiePokazalo=1;
            }
            numer++;
            aktualny=aktualny->nastepny;
        }
    }
    if(opcjaWew == 2){
        while(aktualny!=NULL){
            if(aktualny->nazwisko==danaSzukana){
                cout<<numer<<". imie: "<<aktualny->imie<<", nazwisko: "<<aktualny->nazwisko<<",nr prawa jazdy: "<<aktualny->numerPrawaJazdy;
                cout<<",nr rej.: "<<aktualny->numerRejestracyjny<<"\n";
                czyCosSiePokazalo=1;
            }
            numer++;
            aktualny=aktualny->nastepny;
        }
    }
    if(opcjaWew == 3){
        while(aktualny!=NULL){
            if(aktualny->numerRejestracyjny==danaSzukana){
                cout<<numer<<". imie: "<<aktualny->imie<<", nazwisko: "<<aktualny->nazwisko<<",nr prawa jazdy: "<<aktualny->numerPrawaJazdy;
                cout<<",nr rej.: "<<aktualny->numerRejestracyjny<<"\n";
                czyCosSiePokazalo=1;
            }
            numer++;
            aktualny=aktualny->nastepny;
        }
    }
    if(opcjaWew == 4){
        while(aktualny!=NULL){
            if(aktualny->numerPrawaJazdy==danaSzukana){
                cout<<numer<<". imie: "<<aktualny->imie<<", nazwisko: "<<aktualny->nazwisko<<",nr prawa jazdy: "<<aktualny->numerPrawaJazdy;
                cout<<",nr rej.: "<<aktualny->numerRejestracyjny<<"\n";
                czyCosSiePokazalo=1;
            }
            numer++;
            aktualny=aktualny->nastepny;
        }
    }
    if(czyCosSiePokazalo==0)cout<<"Brak zawodnikow o takich danych";
    cout<<"\n\n";
}

void ListaZawodnikow::dodajVIP(int &ileJestElementowListy){

    string imie, nazwisko, numerPrawaJazdy, numerRejestracyjny;
    cout<<"\nNazwisko: ";
    cin>>nazwisko;
    cout<<"Imie: ";
    cin>>imie;
    cout<<"Numer prawa jazdy : ";
    cin>>numerPrawaJazdy;
    cout<<"Numer rejestracyjny : ";
    cin>>numerRejestracyjny;

    Zawodnik *noweDane = new Zawodnik, *tmp;
    noweDane->imie=imie;
    noweDane->nazwisko=nazwisko;
    noweDane->numerPrawaJazdy=numerPrawaJazdy;
    noweDane->numerRejestracyjny=numerRejestracyjny;

    tmp=pierwszaOsoba;
    pierwszaOsoba=noweDane;
    noweDane->nastepny=tmp;

    ileJestElementowListy++;
}

void ListaZawodnikow::usunPierwszego(int &ileJestElementowListy,bool &czyPustaLista){
    if(ileJestElementowListy==0){
        cout<<"Lista jest juz pusta";
    }
    else{
        Zawodnik *tmp=pierwszaOsoba;
        if(pierwszaOsoba->nastepny==NULL){
            pierwszaOsoba=pierwszaOsoba->nastepny;
            delete tmp;
            ileJestElementowListy--;
            czyPustaLista==true;
        }
        else{
            pierwszaOsoba = pierwszaOsoba->nastepny;
            delete tmp;
            czyPustaLista=0;
            ileJestElementowListy--;
        }
    }
}


void ListaZawodnikow::sortuj(){
    int opcjaWewnatrz;
    while(opcjaWewnatrz!=66){
        int opcjaWewnatrz;
        cout<<"Wybierz po jakiej informacji sortowac:\n";
        cout<<"1. Aby sortowac po imieniu\n";
        cout<<"2. Aby sortowac po nazwisku\n";
        cout<<"3. Aby sortowac po numerze rejestracyjny\n";
        cout<<"4. Aby sortowac po numerze prawa jazdy\n";
        cout<<"66. Aby wrocic do menu glownego\n";
        cout<<"Cyfry maja pierwszenstwo przed literami!\n";
        cin>>opcjaWewnatrz;
        cout<<"Posortowana lista:\n\n";

        cout<<"\nNwm jak mam to zrobic tylko w pamieci, bez pisania 2 rownoleglej listy\n";
        if(opcjaWewnatrz==1);
        if(opcjaWewnatrz==2);
        if(opcjaWewnatrz==3);
        if(opcjaWewnatrz==4);
        if(opcjaWewnatrz==66) break;
    }
}

int main()
{
    ListaZawodnikow *bazaDanych = new ListaZawodnikow;
    int ileInfoWczytac, opcja,ileJestElementowListy=0;
    string nazwisko;
    string imie;
    string numerPrawaJazdy;
    string numerRejestracyjny;
    string nazwaPlikuDoOdczytu;
    bool czyPustaLista=1; //1 to potwierdzenie że lista jest pusta, 0 to zaprzeczenie

    cout<<"Podaj ilu zawodnikow zarejestrowac:\n";
    cin>>ileInfoWczytac;

    bazaDanych->utworzListeZPliku(czyPustaLista,ileInfoWczytac, ileJestElementowListy, nazwaPlikuDoOdczytu);
    bazaDanych->pokaz(czyPustaLista);
    while(opcja!=666)
    {
        cout<<"\nWybierz opcje:\n";
        cout<<"0. Aby pokazac liste zawodnikow\n";
        cout<<"1. Aby dodac zawodnika\n";
        cout<<"2. Aby wystartowac pierwszego na liscie zawodnika\n";
        cout<<"3. Aby usunac dowolnego zawodnika\n";
        cout<<"4. Aby wyszukac zawodnika\n";
        cout<<"5. Aby dodac VIP\n";
        cout<<"6. Aby sortowac liste\n";
        cout<<"666. Aby zamknac program\n";
        cin>>opcja;

        if(opcja==0) bazaDanych->pokaz(ileJestElementowListy);

        if(opcja==1){
            cout<<"\nNazwisko: ";
            cin>>nazwisko;
            cout<<"Imie: ";
            cin>>imie;
            cout<<"Numer prawa jazdy : ";
            cin>>numerPrawaJazdy;
            cout<<"Numer rejestracyjny : ";
            cin>>numerRejestracyjny;
            bazaDanych->dodajDaneRecznie(nazwisko, imie, numerPrawaJazdy, numerRejestracyjny, ileJestElementowListy);
        }

        if(opcja==2){
            bazaDanych->usunPierwszego(ileJestElementowListy,czyPustaLista);
        }

        if(opcja==3){
            int j;
            cout<<"Ktorego zawodnika usunac: ";
            cin>>j;
            j-=1;
            bazaDanych->usunZawodnika(j, czyPustaLista, ileJestElementowListy);
        }

        if(opcja==4){
            int opcjaWewnatrz=0;
            while(opcjaWewnatrz!=66){
                cout<<"Wybierz po jakiej informacji szukac:\n";
                cout<<"1. Aby szukac po imieniu\n";
                cout<<"2. Aby szukac po nazwisku\n";
                cout<<"3. Aby szukac po numerze rejestracyjny\n";
                cout<<"4. Aby szukac po numerze prawa jazdy\n";
                cout<<"66. Aby wrocic do menu glownego\n";
                cin>>opcjaWewnatrz;

                if(opcjaWewnatrz==1) bazaDanych->szukaj(1);
                if(opcjaWewnatrz==2) bazaDanych->szukaj(2);
                if(opcjaWewnatrz==3) bazaDanych->szukaj(3);
                if(opcjaWewnatrz==4) bazaDanych->szukaj(4);
            }
        }

        if(opcja==5) bazaDanych->dodajVIP(ileJestElementowListy);
        if(opcja==6) bazaDanych->sortuj();
    }


    delete bazaDanych;
    return 0;
}