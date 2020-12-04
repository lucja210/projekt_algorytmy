#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
//#include <time.h>
using namespace std;
int n; //rozmiar danej tablicy
char save; //status opcji zapisu do pliku
int* check(int* tab, int size){ //funkcja zawrierajaca glowna czesc programu (algorytm wykonujacy zadania dla tablicy wejsciowej np. tabA)
    int* new_tab = new int[size]; //tablica wyjsciowa np. tabB
    for (int i = 0; i < n; i++){
        int ilosc_wiekszych = 0;
        for (int j = i; j < n; j++){
            if(tab[j]>tab[i]){
                ilosc_wiekszych++;
            }
        }
        new_tab[i]=ilosc_wiekszych;
    }
    return new_tab;
}
void opt_1(){ //pierwsza opcja, ktora pobiera tablice od uzytkownika
    system("cls"); //czyszczenie naszego terminala
    cout<<"Podaj szerokosc tablicy: ";
    cin>>n;
    int* tab = new int[n];
    cout<<"Wpisz liczby do tablicy na odpowiednik indeksie."<<endl;
    for (int i = 0; i < n; i++){ //wczytywanie danych do tabA
        int number = 0;
        cout<<i<<". ";
        cin>>number;
        tab[i]=number;
    }
    int* tab_b = check(tab, n); //wywolanie funkcji, ktora zwroci tabB
    //wyswietelenie tabA i tabB
    cout<<endl<<"Tablica wejsciowa: ";
    for (int i = 0; i < n; i++){
        cout<<tab[i]<<" ";
    }
    cout<<endl<<"Tablica wyjsciowa: ";
    for (int i = 0; i < n; i++){
        cout<<tab_b[i]<<" ";
    }
    cout<<endl;
    //zapis danych do pliku
    if (save == 't'){
        ofstream out_file;
        out_file.open("dane_wyjsciowe.txt");//otwarcie pliku
        if (out_file.is_open()){
            out_file<<"Tablica wejsciowa: ";
            for (int i = 0; i < n; i++){
                out_file<<tab[i]<<" ";
            }
            out_file<<endl<<"Tablica wyjsciowa: ";
            for (int i = 0; i < n; i++){
                out_file<<tab_b[i]<<" ";
            }
        }else{
            cout<<"Nie udalo sie otworzyc pliku!";
        }
        out_file.close();//zamkniecie pliku
        cout<<"\nTwoje dane i wyniki zostaly zapisane w pliku\n\n";
    }
}
void opt_2(){ //druga opcja, ktora pobiera dane z pliku dane.txt - plik powinien zawierac liczby oddzielone spacjami, moze zawierac kilka wierszy!
    system("cls");
    ifstream inp_file;
    inp_file.open("dane.txt"); //otwarcie pliku do odczytu
    if (inp_file.is_open()){
        char wiersz[100000]; //inicjalizacja zmiennej przechowujacej wiersz na, ktorym obecnie wykonujemy czynnosci
        //problemem jest, ze nie znamy dlugosci wiersza w pliku wiec dajemy mozliwie duzy rozmiar tablicy
        ofstream out_file;
        if (save == 't'){
            out_file.open("dane_wyjsciowe.txt"); //otwarcie pliku do zapisu
        }
        while(inp_file.getline(wiersz,100000)){ //petla dla kazdego wiersza z danymi wejsciowymi
            n=0;
            char number = '*', cur_number[100000];
            int ended_row[100000], i = 0, j=0;
            //ta petla ma za zadanie podzielic tablice ktora jest wierszem i przechowuje kazdy znak(cyfre) oraz spacje w osobnym indexie
            //na nowa tablice ktora zawiera pelne wartosci w indexie i nie zawiera spacji
            //ma to na celu konwersje tablicy na tablice ktora bedzie czytelna dla funkcji "check"
            while (1){
                number=wiersz[i];
                if (number == 0){
                    j=0;
                    ended_row[n] = atoi(cur_number); //konwersja typu tekstowego(char) na liczbowy(int)
                    n++;
                    fill_n(cur_number, 100000, 0); //czyszczenie tablicy
                    break;
                }
                if (number != ' '){
                    cur_number[j] = number;
                    j++;
                }else{
                    j=0;
                    ended_row[n] = atoi(cur_number);
                    n++;
                    fill_n(cur_number, 100000, 0);
                }
                i++;
            }
            int* new_tab = new int[n];
            //wypisanie danych oraz przepisanie danych z tablicy o ogromnym rozmiarze do tablicy o takim rozmiarze ile jest liczb
            cout<<"Tablica wejsciowa: ";
            for (int i = 0; i < n; i++){
                new_tab[i]=ended_row[i];
                cout<<new_tab[i]<<" ";
            }
            cout<<endl;
            cout<<"Tablica wyjsciowa: ";
            //wywolanie funkcji check z odpowiednia tablica w celu uzyskania tablicy "B" ktora jest wynikiem wykonania algorytmu
            int* checked_tab = check(new_tab, n);
            //wypisanie tabB
            for (int i = 0; i < n; i++){
                cout<<checked_tab[i]<<" ";
            }
            cout<<"\n\n";
            //wypisanie danych do pliku wyjsciowego
            if (out_file.is_open() && save=='t'){
                out_file<<"Tablica wejsciowa: ";
                for (int i = 0; i < n; i++){
                out_file<<new_tab[i]<<" ";
                }
                out_file<<"\nTablica wyjsciowa: ";
                for (int i = 0; i < n; i++){
                    out_file<<checked_tab[i]<<" ";
                }
                out_file<<"\n\n";
            } else if(save == 't'){
                cout<<"Nie udalo sie otworzyc pliku niezbednego do zapisu wynikow!";
            }
        }
        if(save=='t')
        cout<<"\nDane zaostaly wypisane rowniez do pliku!\n\n";
        out_file.close(); //zamkniecie pliku wyjsciowego
    }else {
        cout<<"Nie odalo sie otworzyc pliku z danymi wejsciowymi!\n\n";
    }
    inp_file.close(); //zamkniecie pliku wejsciowego
}
bool test (){ //testy automatyczne algorytmu
    //test 1 - dla liczb wymyslonych przez "autora"
    n=10;
    int* tab = new int[n];
    tab[0]=8; //przypisanie reczne wartosci do indexu
    tab[1]=7;
    tab[2]=2;
    tab[3]=7;
    tab[4]=65;
    tab[5]=4;
    tab[6]=6;
    tab[7]=8;
    tab[8]=989;
    tab[9]=0;
    int* checked_tab = check(tab, n); //wywolanie testowanej funkcji
    //sprawdzeine wynikow funkcji
    if (checked_tab[0]!=2 || checked_tab[1]!=3 || checked_tab[2]!=6 || checked_tab[3]!=3 || checked_tab[4]!=1 || checked_tab[5]!=3 || checked_tab[6]!=2 || checked_tab[7]!=1 || checked_tab[8]!=0 || checked_tab[9]!=0){
        return false; //jesli wyniki sa zle testy zwracaja falsz
    }
    //test 2 - tabA zawiera liczby od 0, 1, 2 -> n
    n=100;
    tab = new int[n];
    for(int i = 0; i<n;i++){
        tab[i]=i;
    }
    checked_tab = check(tab, n); //wywolanie funkcji sprawdzajacej, powinna zwrocic dane n-1, n-2, n-3 -> 0
    int j = 0;
    for(int i = n-1; i>=n;i--){ //sprawdzenie wynikow
        if (checked_tab[j] != n){
            return false; //jesli dane sa niezgodne testy zwracaja falsz
        }
        j++;
    }
    //test 3 - kazda kolejna liczba w tabA jest mniejsza od poprzedniej, wiec tabB powinna byc wypelniona 0
    n=100;
    tab = new int[n];
    j=0;
    for(int i = n; i>=0; i--){
        tab[j]=i;
        j++;
    }
    checked_tab = check(tab, n);
    for(int i = 0; i<n; i++){ //sprawdzenie wynikow
        if (checked_tab[i] != 0){
            return false; //jesli dane sa niezgodne testy zwracaja falsz
        }
    }
    return true; //jesli powyzsze testy nie zwrocily falszu to testy wykonaly sie pozytywnie i funkcja zwraca prawde
}
int main() { //main w ktorym dokonujemy wyboru, ktora opcje wybieramy oraz sa tu wywolywane testy
    char action, force = 0;
    while (1){ //petla wykonuje sie do momentu az uzytkownik poda odpowiedni znak
        system("cls");
        cout<<"Wybierz opcje programu:\n1) Wpisz recznie tablice\n2) Odczytaj tablice z pliku dane.txt (Plik powinien zawierac liczby odzielone spacja - plik moze zawierac kilka wierszy)\nWybieram: ";
        cin>>action;
        if (action == '1'){
            if(test() == false){ //jesli testy sa negatywne - co robic
                system("cls");
                cout<<"\n\nTesty zostaly zakonczone NIEPOWODZENIEM!!!\n\nPamietaj, ze w tym przypadku dane moge bys zle wyliczone!\n\nCzy chcesz kontynuowac prace z programem? (t/n): ";
                cin>>force;
                if (force != 't'){
                    return 0; //zakonczenie programu
                }
            }
            if(test() || force == 't'){
                while (1){ //pytanie o wypis do pliku
                    system("cls");
                    cout<<"\n\nCzy dane wyjsciowe maja byc zapisane w pliku?\nWybieram (t/n): ";
                    cin>>save;
                    if (save!='t' && save != 'n') {
                        continue;
                    }
                    break;
                }
                opt_1(); //wywalanie opcji nr 1, ktora pobiera dane od uzytkownika
            }
            system("PAUSE");
            return 0;
        } else if (action == '2'){
            if(test() == false){ //jesli testy sa negatywne - co robic//jesli testy sa negatywne - co robic
                system("cls");
                cout<<"\n\nTesty zostaly zakonczone NIEPOWODZENIEM!!!\n\nPamietaj, ze w tym przypadku dane moge bys zle wyliczone!\n\nCzy chcesz kontynuowac prace z programem? (t/n): ";
                cin>>force;
                if (force != 't'){
                    return 0; //zakonczenie programu
                }
            }
            if(test() || force == 't'){
                while (1){ //pytanie o wypis do pliku
                    system("cls");
                    cout<<"\n\nCzy dane wyjsciowe maja byc zapisane w pliku?\nWybieram (t/n): ";
                    cin>>save;
                    if (save!='t' && save != 'n') {
                        continue;
                    }
                    break;
                }
                opt_2(); //wywalanie opcji nr 2, ktora pobiera dane z pliku
            }
            system("PAUSE");
            return 0; //zakonczenie programu
        }
        continue;
    }
    return 1; //zakonczenie programu
}
