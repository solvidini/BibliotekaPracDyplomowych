#include "pch.h"
#include "Biblioteka.h"
#include "Praca.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <map>
#include <conio.h>

using namespace std;


Biblioteka::~Biblioteka(){
    delete[] prace;
}

void Biblioteka::add(Praca * p){
    prace[ilePrac] = *p;
    ilePrac++;
}

void Biblioteka::loadFromFile(){
    ifstream in("bazaprac.txt");
    // ZAKLADAM, ZE KAZDA LINIA W PLIKU JEST PRZEZNACZONA DLA JEDNEJ ZMIENNEJ , A DANE W PLIKU SA POPRAWNE.
    // 10 WIERSZY W PLIKU PRZEZNACZONYCH JEST DLA JEDNEJ PRACY. JESLI PRACE BEDA 2, TO LINII POWINNO BYC 20 ITD.
    if (in.is_open()){
        size_t id;
        string typPracy;
        string tytul;
        string nazwiskoAutora;
        string imionaAutora;
        size_t rok;
        string nazwiskoPromotora;
        string imionaPromotora;
        string slowaKluczowe;
        string streszczenie;
        //pomocnicze zmienne:
        string s_id;
        string s_rok;

        while(!in.eof()){
            getline(in, s_id);
            if (s_id == "") break;
            stringstream ssid(s_id);
            ssid >> id;
            getline(in, typPracy);
            getline(in, tytul);
            getline(in, nazwiskoAutora);
            getline(in, imionaAutora);
            getline(in, s_rok);
            stringstream ssrok(s_rok);
            ssrok >> rok;
            getline(in, nazwiskoPromotora);
            getline(in, imionaPromotora);
            getline(in, slowaKluczowe);
            getline(in, streszczenie);
            Praca * p = new Praca(id,typPracy,tytul,nazwiskoAutora,imionaAutora,rok,nazwiskoPromotora,imionaPromotora,slowaKluczowe,streszczenie);
            add(p);
        }
        in.close();
    }
}

void Biblioteka::addByUser(){
        size_t id;
        string typPracy;
        char tytul[100];
        string nazwiskoAutora;
        char imionaAutora[100];
        size_t rok;
        string nazwiskoPromotora;
        char imionaPromotora[100];
        string slowaKluczowe;
        char streszczenie[1000];
        // zmienna pomocnicza:
        bool sprawdz_id = true;
        cout << "Podaj kolejne dane pracy:" << endl;
        cout << "ID: ";
        if (!(cin >> id)){
            cerr << "To nie jest liczba!";
            exit(0);
        }
        while (sprawdz_id){
            for (size_t i=0; i<ilePrac; i++){
                if (id == prace[i].getId()){
                    cout << "Id zajete! Podaj nowe!" << endl
                        << "ID: ";
                    if (!(cin >> id)){
                        cerr << "To nie jest liczba!";
                        exit(0);
                    }
                }
                else sprawdz_id = false;
            }
            sprawdz_id = false;
        }
        cout << "Typ pracy: "; cin >> typPracy;
        while (typPracy != "inz" && typPracy != "lic" && typPracy != "mgr"){
            cout << "Bledne dane! Dopuszczalne wartosci ( \"inz\", \"lic\", \"mgr\" )" << endl
                << "Typ pracy: "; cin >> typPracy;
        }
        cin.ignore();
        cout << "Tytul: "; cin.getline(tytul,100);
        cout << "Nazwisko autora: "; cin >> nazwiskoAutora;
        cin.ignore();
        cout << "Imiona autora: "; cin.getline(imionaAutora,100);
        cout << "Rok powstania pracy: ";
        if (!(cin >> rok)){
            cerr << "To nie jest liczba!";
            exit(0);
        }
        while (rok<2000){
            cout << "Bledne dane! Min. rok to 2000" << endl
                << "Rok powstania pracy: ";
            if (!(cin >> rok)){
                cerr << "To nie jest liczba!";
                exit(0);
            }
        }
        cout << "Nazwisko promotora: "; cin >> nazwiskoPromotora;
        cin.ignore();
        cout << "Imiona promotora: "; cin.getline(imionaPromotora,100);
        cout << "Slowa kluczowe: "; cin >> slowaKluczowe;
        cin.ignore();
        cout << "Streszczenie: "; cin.getline(streszczenie,1000);
        cout << endl;
        Praca * p = new Praca(id,typPracy,tytul,nazwiskoAutora,imionaAutora,rok,nazwiskoPromotora,imionaPromotora,slowaKluczowe,streszczenie);
        add(p);
        p -> addData();
}

void Biblioteka::wyswietlSkrocony(){
    cout << endl << "Lista prac w skroconej formie:" << endl;
    for (size_t i=0; i<ilePrac; i++)
        prace[i].wyswietlSkrocony();
    cout << endl << "Koniec listy." << endl << endl;
}

void Biblioteka::wyswietlPelny(){
    cout << endl << "Lista prac w pelnej formie:" << endl;
    for (size_t i=0; i<ilePrac; i++)
        prace[i].wyswietlPelny();
    cout << endl << "Koniec listy." << endl << endl;
}

void Biblioteka::editData(){
    size_t choice;
    cout << endl << "Podaj identyfikator pracy, ktora chcesz edytowac: ";
    if (!(cin >> choice)){
            cerr << "To nie jest liczba!";
            exit(0);
    }
    size_t i = 0;
    for (; i<ilePrac; ++i){
        if (choice == prace[i].getId()){
            cout << endl << "Dane pracy: " << endl;
            prace[i].wyswietlPelny();
            cout << endl;
            prace[i].edit(); //edycja w klasie praca
            ofstream out("bazaprac.txt", ofstream::out | ofstream::trunc);
            out.close();
            for (size_t j=0; j<ilePrac; j++){
                prace[j].addData();
            }
            break;
        }
    }
    if (i>=ilePrac) cout << "Brak pracy o podanym identyfikatorze!" << endl << endl;
}

void Biblioteka::wyswietlZPodzialem(){
    cout << endl << "Liczba wszystkich prac: " << ilePrac << endl;
    cout << endl << "Prace inzynierskie: ";
    for (size_t i=0; i<ilePrac; i++){
        if (prace[i].getTypPracy() == "inz"){
            prace[i].wyswietlSkrocony();
        }
    }
    cout << endl << "Prace licencjackie: ";
    for (size_t i=0; i<ilePrac; i++){
        if (prace[i].getTypPracy() == "lic"){
            prace[i].wyswietlSkrocony();
        }
    }
    cout << endl << "Prace magisterskie: ";
    for (size_t i=0; i<ilePrac; i++){
        if (prace[i].getTypPracy() == "mgr"){
            prace[i].wyswietlSkrocony();
        }
    }
    cout << endl;
}

void Biblioteka::wyswietlNajczestszeSlowo(){
    string * tab = new string[ilePrac*10](); //zakladam, ze jedna praca moze miec max 10 slow kluczowych
    string linia;
    size_t count1 = 0;
    for (size_t i = 0; i < ilePrac; ++i){
        linia = prace[i].getSlowaKluczowe();
        for (size_t j = 0; j < linia.length(); j++){
            if (linia[j]==';') count1++;
            else tab[count1]+=linia[j];
        }
    }
    //////////////////////////////////////////////
    map <string,size_t> index;
    for (size_t x = 0; x < count1-1; ++x){
        for (size_t i = x; i < count1-1; ++i){
            if (tab[x]==tab[i+1]) index[tab[x]]++;
        }
    }
    //////////////////////////////////////////////
    size_t i_max = 0;
    string slowo;
    for (size_t x = 0; x < count1; ++x){
        if (i_max < index[tab[x]]){
                i_max = index[tab[x]];
                slowo = tab[x];
        }
    }
    delete[] tab;
    cout << endl << "Najczesciej powtarzajace sie slowo kluczowe to: " << slowo << endl
        << "Slowo to wystepuje w " << index[slowo] << " pracach." << endl;

}

void Biblioteka::wyswietlWedlugPromotorow(){
    map <string, size_t> promotor;
    string * who = new string[ilePrac];
    cout << endl << "Lista prac dla poszczegolnych promotorow: " << endl;
    for (size_t x = 0; x < ilePrac; ++x){
        who[x] = prace[x].getNazwiskoPromotora() + " " + prace[x].getImionaPromotora();
        promotor[who[x]]++;
        if (promotor[who[x]]>1) who[x] = "/nOnE/"; //likwidacja powtorzen
    }
    stringstream ss;
    for (size_t x = 0; x < ilePrac; ++x){
        if (who[x] != "/nOnE/"){
                ss << promotor[who[x]];
                who[x] = who[x] + ": " + ss.str();
                ss.str(string());
        }
    }
    for (size_t x = 0; x < ilePrac; ++x){ //sortowanie alfabetycznie
        for (size_t i = x; i < ilePrac-1; ++i){
            if (((int)who[x][0])>((int)who[i+1][0])) swap(who[x], who[i+1]);
            else if (((int)who[x][0])==((int)who[i+1][0])){
                if (((int)who[x][1])>((int)who[i+1][1])) swap(who[x], who[i+1]);
            }
        }
    }
    for (size_t x = 0; x < ilePrac; ++x){
        if (who[x] != "/nOnE/") cout << who[x] << endl;
    }
    delete[] who;
}

void Biblioteka::wyszukajNaPodstawie(){
    char choice;
    string podaneNazwiskoA;
    string podaneNazwiskoP;
    string podanyTytul;
    string podaneSlowoKluczowe;
    string podaneStreszczenie;
    size_t podanyRok;
    Praca * wyniki = new Praca[ilePrac]();
    size_t counter = 0, CC = 0; // CC - compare counter - licznik porownujacy
    string pasujace;
    cout << endl << "Wybierz na podstawie ktorego kryterium chcesz wyszukac prace: " << endl
        << "1 - Nazwisko autora." << endl
        << "2 - Nazwisko promotora." << endl
        << "3 - Tytul." << endl
        << "4 - Slowo kluczowe." << endl
        << "5 - Streszczenie." << endl
        << "6 - Rok powstania." << endl
        << "Kliknij dowolny inny klawisz, aby przerwac wyszukiwanie." << endl;
        choice = _getch();
        switch(choice){
        case '1': cout << endl << "Podaj nazwisko autora: ";
            cin >> podaneNazwiskoA;
            for (size_t i = 0; i < ilePrac; i++){
                for (size_t j = 0; j < podaneNazwiskoA.length(); j++){
                    if (prace[i].getNazwiskoAutora().length() <= CC) break;
                    else {
                        if (prace[i].getNazwiskoAutora()[j] == podaneNazwiskoA[j]) CC++;
                        else {
                            CC = 0;
                            break;
                        }
                    }
                }
                if (CC > 0 || CC == prace[i].getNazwiskoAutora().length()){
                    wyniki[counter] = prace[i];
                    counter++;
                }
                CC = 0;
            }
            break;
        case '2': cout << endl << "Podaj nazwisko promotora: ";
            cin >> podaneNazwiskoP;
            for (size_t i = 0; i < ilePrac; i++){
                for (size_t j = 0; j < podaneNazwiskoP.length(); j++){
                    if (prace[i].getNazwiskoPromotora().length() <= CC) break;
                    else {
                        if (prace[i].getNazwiskoPromotora()[j] == podaneNazwiskoP[j]) CC++;
                        else {
                            CC = 0;
                            break;
                        }
                    }
                }
                if (CC > 0 || CC == prace[i].getNazwiskoPromotora().length()){
                    wyniki[counter] = prace[i];
                    counter++;
                }
                CC = 0;
            }
            break;
        case '3': cout << endl << "Podaj tytul: ";
            cin >> podanyTytul;
            for (size_t i = 0; i < ilePrac; i++){
                for (size_t j = 0; j < podanyTytul.length(); j++){
                    if (prace[i].getTytul().length() <= CC) break;
                    else {
                        if (prace[i].getTytul()[j] == podanyTytul[j]) CC++;
                        else {
                            CC = 0;
                            break;
                        }
                    }
                }
                if (CC > 0 || CC == prace[i].getTytul().length()){
                    wyniki[counter] = prace[i];
                    counter++;
                }
                CC = 0;
            }
            break;
        case '4': cout << endl << "Podaj slowo kluczowe: ";
            cin >> podaneSlowoKluczowe;
            for (size_t i = 0; i < ilePrac; i++){
                for (size_t j = 0; j < prace[i].getSlowaKluczowe().length(); j++){
                    if (prace[i].getSlowaKluczowe()[j] == podaneSlowoKluczowe[CC]){
                       pasujace+=prace[i].getSlowaKluczowe()[j];
                       CC++;
                    }
                    if (pasujace == podaneSlowoKluczowe){
                        if (counter == 0){
                            wyniki[counter] = prace[i];
                            counter++;
                            pasujace = "";
                            CC = 0;
                        } else {
                            if (wyniki[(counter-1)].getId() != prace[i].getId()){ //eliminacja powtorzen!
                                wyniki[counter] = prace[i];
                                counter++;
                                pasujace = "";
                                CC = 0;
                            }
                        }
                    }
                    if (prace[i].getSlowaKluczowe()[j] == ';'){
                      pasujace = "";
                      CC = 0;
                    }
                }
            }
            break;
        case '5': cout << endl << "Podaj streszczenie: ";
            cin >> podaneStreszczenie;
            for (size_t i = 0; i < ilePrac; i++){
                for (size_t j = 0; j < podaneStreszczenie.length(); j++){
                    if (prace[i].getStreszczenie().length() <= CC) break;
                    else {
                        if (prace[i].getStreszczenie()[j] == podaneStreszczenie[j]) CC++;
                        else {
                            CC = 0;
                            break;
                        }
                    }
                }
                if (CC > 0 || CC == prace[i].getStreszczenie().length()){
                    wyniki[counter] = prace[i];
                    counter++;
                }
                CC = 0;
            }
            break;
        case '6': cout << endl << "Podaj rok powstania: ";
            cin >> podanyRok;
            for (size_t i = 0; i < ilePrac; i++){
                if (prace[i].getRok() == podanyRok){
                    wyniki[counter] = prace[i];
                    counter++;
                }
            }
            break;
        default:
            break;
    }
    cout << endl;
    for (size_t x = 0; x < counter; ++x){ //sortowanie w kolejnosci od najnowszych do najstarszych
        for (size_t i = x; i < counter-1; ++i){
            if (prace[x].getRok() < prace[i+1].getRok()) swap(wyniki[x], wyniki[i+1]);
            }
    }
    if (counter >0) cout << "Znalezione prace: " << endl;
    else cout << "Nie znaleziono prac!" << endl;
    for (size_t x = 0; x < counter; x++){
        cout << x+1 << ") "; wyniki[x].wyswietlSkrocony();
    }
}
