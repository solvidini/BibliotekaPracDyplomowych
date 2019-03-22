#include "pch.h"
#include "Praca.h"
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <conio.h>
Praca::Praca(){}
Praca::~Praca(){}

void Praca::addData(){
    ofstream out("bazaprac.txt", ios::app);
        if (out.is_open()){
            out << id << endl;
            out << typPracy << endl;
            out << tytul << endl;
            out << nazwiskoAutora << endl;
            out << imionaAutora << endl;
            out << rok << endl;
            out << nazwiskoPromotora << endl;
            out << imionaPromotora << endl;
            out << slowaKluczowe << endl;
            out << streszczenie << endl;
            out.close();
        }
}

void Praca::wyswietlSkrocony(){
    cout << " " << id << " " << typPracy << " " << imionaAutora[0] << ". " << nazwiskoAutora << " ,," << tytul << "'' " << rok << endl;
}

void Praca::wyswietlPelny(){
    cout << endl << setw(65) << setfill('-') << "-" << endl << "Id: " << id << endl << "Typ: " << typPracy << endl << "Autor: " << imionaAutora << " " << nazwiskoAutora << endl << "Tytul: " << tytul
        << endl << "Slowa kluczowe: " << slowaKluczowe << endl << "Rok: " << rok << endl << "Promotor: " << imionaPromotora << " " << nazwiskoPromotora << endl << "Streszczenie: "
        << streszczenie << endl << setw(65) << setfill('-') << "-" << endl;
}

void Praca::edit(){
    char choice;
    char tytul2[100];
    char imiona2[100];
    char streszczenie2[1000];
    cout << "Ktore dane chcesz zmienic?" << endl
        << "1 - Imie i nazwisko." << endl
        << "2 - Typ pracy." << endl
        << "3 - Rok powstania." << endl
        << "4 - Tytul." << endl
        << "5 - Slowa kluczowe." << endl
        << "6 - Opis." << endl
        << "Kliknij dowolny inny klawisz, aby opuscic menu bez zmian." << endl;
        choice = _getch();
        switch(choice){
        case '2':
            cout << "Nowy typ pracy: "; cin >> typPracy;
            while (typPracy != "inz" && typPracy != "lic" && typPracy != "mgr"){
                cout << "Bledne dane! Dopuszczalne wartosci ( \"inz\", \"lic\", \"mgr\" )" << endl
                    << "Typ pracy: "; cin >> typPracy;
            }
                    cout << endl << "Dane zostaly zaktualizowane!" << endl;
            break;
        case '4':
            cin.ignore();
            cout << "Nowy tytul pracy: "; cin.getline(tytul2,100);
            tytul = (string)tytul2;
                    cout << endl << "Dane zostaly zaktualizowane!" << endl;
            break;
        case '1':
            cout << "Nowe nazwisko autora: "; cin >> nazwiskoAutora;
            cin.ignore();
            cout << "Nowe imiona autora: "; cin.getline(imiona2,100);
            imionaAutora = (string)imiona2;
                    cout << endl << "Dane zostaly zaktualizowane!" << endl;
            break;
        case '3':
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
                    cout << endl << "Dane zostaly zaktualizowane!" << endl;
            }
            break;
        case '5':
            cout << "Slowa kluczowe: "; cin >> slowaKluczowe;
                    cout << endl << "Dane zostaly zaktualizowane!" << endl;
            break;
        case '6':
        cin.ignore();
        cout << "Streszczenie: "; cin.getline(streszczenie2,1000);
        streszczenie = (string)streszczenie2;
                    cout << endl << "Dane zostaly zaktualizowane!" << endl;
            break;
        default:
            break;
    }
}
