#include"Macierz.hpp"
#include<memory>
#include<algorithm>

class Matematyka
{
    public:
    Matematyka() {}
    ~Matematyka() {}

    void gra()
    {
        string polecenie;
        while(true)
        {   
            cout << "\nDostepne akcje:\tsMat, zMat, lMat, infoMat, exit oraz dzialania (A+B, A-B, A*B)" << endl;
            cin >> polecenie;
            size_t plusPos = polecenie.find('+');
            size_t minusPos = polecenie.find('-');
            size_t multiplyPos = polecenie.find('*');
            if(polecenie == "exit")
            {
                break;
            }
            else if (polecenie == "sMat") 
            {
                zbudujMacierz();           
            } 
            else if(polecenie == "lMat")
            {
                wylistujMacierze();
            }
            else if(polecenie == "infoMat")
            {
                informacje();
            }
            else if(polecenie == "zMat")
            {
                usunMacierz();
            }
            else if(plusPos != string::npos) // dodawanie
            {
                string operandA = polecenie.substr(0, plusPos);
                string operandB = polecenie.substr(plusPos + 1);

                dodajMacierze(operandA, operandB);
            }
            else if (minusPos != string::npos) // odejmowanie
            {
                string operandA = polecenie.substr(0, minusPos);
                string operandB = polecenie.substr(minusPos + 1);

                odejmijMacierze(operandA, operandB);
            }
            else if (multiplyPos != string::npos) // mnożenie
            {
                string operandA = polecenie.substr(0, multiplyPos);
                string operandB = polecenie.substr(multiplyPos + 1);

                pomnozMacierze(operandA, operandB);
            }
            else
            {
                cout << "Niepoprawne polecenie. Sprobuj ponownie." << endl;
            }
        }
    }

    void zbudujMacierz()
    {
        string name;
        cout << "Podaj nazwe macierzy" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // usuwanie znaków w buforze aż do nowej linii
        getline(cin, name); // wczytanie całej linii do zmiennej name
            if(!name.empty() && !isdigit(name[0])) // warunek: zmienna name nie jest pusta i pierwszy znak nie jest cyfrą
            {
                bool czyPowtorzenie = false;
                for(const auto& nazwa : nazwy) // sprawdzenie czy wprowadzona nazwa już istnieje
                {
                    if(name == nazwa)
                    {
                        cout << "Nie mozna powtarzac nazw macierzy" << endl;
                        czyPowtorzenie = true;
                        break;
                    }
                }
                if(czyPowtorzenie == false) // jeśli nazwa się nie powtórzyła to wprowadzamy wymiary macierzy
                {
                    cout << "Podaj wymiar macierzy (wiersz i kolumna)" << endl;
                    try 
                    {
                        int a = wczytajLiczbeCalkowita();
                        int b = wczytajLiczbeCalkowita();
                        if(a==b)
                        {
                            macierze.push_back(make_unique<Macierz_kwad>(name,a));
                        }
                        else
                        {
                            macierze.push_back(make_unique<Macierz>(name,a,b));
                        }
                        
                        nazwy.push_back(name);

                    } 
                    catch(const invalid_argument &e) // jeśli wprowadzone liczby nie są typu int to łapany jest wyjątek
                    {
                        cerr << e.what() << endl;
                    }
                }
                
            } 
            else 
            {
                cout << "Nazwa macierzy nie moze sie zaczynac od cyfry" << endl;
            } 
        
    }

    int wczytajLiczbeCalkowita() 
    {
        int liczba;
        if (!(cin >> liczba) || cin.fail()) 
        {
            cin.clear(); // resetowanie strumienia wejściowego
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // czyszczenie bufora, usuwanie znaków w buforze aż do nowej linii
            throw invalid_argument("Blad!. Podaj poprawna liczbe calkowita."); // rzucenie wyjątku
        }
        return liczba;
    }
   
    void usunMacierz()
    {
        string name;
        cout << "Podaj nazwe macierzy" << endl;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        getline(cin, name);
        bool czyJestMacierz = false;
        for(const auto& macierz : macierze)
        {
            if(macierz->getNazwa() == name)
            {
                czyJestMacierz = true;
                macierze.erase(remove(macierze.begin(),macierze.end(), macierz), macierze.end()); // usuwanie danej macierzy z wektora macierzy
                nazwy.erase(remove(nazwy.begin(), nazwy.end(), name), nazwy.end()); // usuwanie nazwy z wektora nazw
                cout << "Usunieto macierz " << name << endl;
                break;
            }
        }
        if(czyJestMacierz == false)
        {
            cout << "Nie ma takiej macierzy" << endl;
        }
    }

    void wylistujMacierze() const
    {
        for (const auto& macierz : macierze)
        {
            cout << "Macierz " << macierz->getNazwa() << endl;
            macierz->wyswietlMacierz();
        }
    }

    void informacje()
    {
        string name;
        cout << "Podaj nazwe macierzy" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        bool czyJestMacierz = false;
        for (const auto& macierz : macierze)
        {
            if(macierz->getNazwa() == name)
            {
                try
                {
                    czyJestMacierz = true;
                    cout << "Macierz " << name << " (" << macierz->getRow() << "x" << macierz->getCol() << ")" <<  endl;
                    macierz->wyswietlMacierz();
                    cout << "Wyznacznik: " << macierz->wyznacznik() << endl;
                    break;
                }
                catch(const invalid_argument& e)
                {
                    cerr << e.what() << endl;
                }
                
            }
        }
        if(czyJestMacierz == false)
        {
            cout << "Nie ma takiej macierzy" << endl;
        }
        
    }

    

    void dodajMacierze(const string& nazwaA, const string& nazwaB)
    {
        auto macierzAIt = find_if(macierze.begin(), macierze.end(), [&nazwaA](const auto& m) { return m->getNazwa() == nazwaA; });
        auto macierzBIt = find_if(macierze.begin(), macierze.end(), [&nazwaB](const auto& m) { return m->getNazwa() == nazwaB; });

        if(macierzAIt != macierze.end() && macierzBIt != macierze.end())
        {
            try
            {
                auto wynik = *macierzAIt->get() + *macierzBIt->get();
                cout << "Wynik dodawania:\n";
                wynik.wyswietlMacierz();
            }
            catch(const invalid_argument& e)
            {
                cerr << e.what() << endl;
            }
            
        }
        else
        {
            cout << "Nie znaleziono macierzy o podanych nazwach." << endl;
        }
    }

    void odejmijMacierze(const string& nazwaA, const string& nazwaB)
    {
        auto macierzAIt = find_if(macierze.begin(), macierze.end(), [&nazwaA](const auto& m) { return m->getNazwa() == nazwaA; });
        auto macierzBIt = find_if(macierze.begin(), macierze.end(), [&nazwaB](const auto& m) { return m->getNazwa() == nazwaB; });

        if(macierzAIt != macierze.end() && macierzBIt != macierze.end())
        {
            try
            {
                Macierz wynik = *macierzAIt->get() - *macierzBIt->get();
                cout << "Wynik odejmowania:\n";
                wynik.wyswietlMacierz();
            }
            catch(const invalid_argument& e)
            {
                cerr << e.what() << endl;
            }
            
        }
        else
        {
            cout << "Nie znaleziono macierzy o podanych nazwach." << endl;
        }
    }

    void pomnozMacierze(const string& nazwaA, const string& nazwaB)
    {
        auto macierzAIt = find_if(macierze.begin(), macierze.end(), [&nazwaA](const auto& m) { return m->getNazwa() == nazwaA; });
        auto macierzBIt = find_if(macierze.begin(), macierze.end(), [&nazwaB](const auto& m) { return m->getNazwa() == nazwaB; });

        if(macierzAIt != macierze.end() && macierzBIt != macierze.end())
        {
            try
            {
                Macierz wynik = *macierzAIt->get() * *macierzBIt->get();
                cout << "Wynik mnozenia:\n";
                wynik.wyswietlMacierz();
            }
            catch(const invalid_argument& e)
            {
                cerr << e.what() << endl;
            }
            
        }
        else
        {
            cout << "Nie znaleziono macierzy o podanych nazwach." << endl;
        }
    }

    private:
    vector<unique_ptr<Macierz>> macierze; // wektor przechowujacy macierze
    vector<string> nazwy;                 // wektor przechowujacy nazwy macierzy
};