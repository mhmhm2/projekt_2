#include"Matematyka.hpp"

using namespace std;

int main()
{
    Matematyka M;
    cout << "\nDostepne akcje:\nsMat - stworz macierz\nzMat - zniszcz macierz\nlMat - wyswietl macierze\ninfoMat - wyswietl informacje o macierzy\nexit - wyjscie z gry" << endl;
    M.gra();   
}