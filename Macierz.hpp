#include<iostream>
#include<vector>
#include<limits>
#include <iomanip>
using namespace std;

class Macierz
{
    public:
    
    Macierz() {}
    Macierz(int x, int y) : rows(x), cols(y) // tworzy macierz wypełnioną zerami
    {
        vector<vector<double>> m(rows, vector<double>(cols, 0));
        matrix = m;
    } 
    Macierz(string nazwa, int x, int y) : nazwa(nazwa), rows(x), cols(y) // tworzy macierz o danej nazwie wypełnioną podanymi liczbami
    {   
        
        vector<vector<double>> m(rows, vector<double>(cols, 0));
        for(int i = 0; i < x; i++)
        {
            cout << "Wiersz " << i << endl;
            for(int j = 0; j < y; j++ )
            {
                try
                {
                    double aa = wczytajLiczbeDouble();
                    m[i][j] = aa;
                }
                catch(const invalid_argument& e)
                {
                    cerr << e.what() << endl;
                    throw;
                }

                
            }  
        }
        matrix = m;
        cout << endl;
        wyswietlMacierz();
    }

    virtual ~Macierz() {}

    void wyswietlMacierz()
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                cout << setw(6) << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    Macierz operator*(const Macierz& other) const
    {
        Macierz res(rows, other.cols);
        double s;
        if(cols == other.rows)
        {
            for(int i = 0; i < rows; i++) 
            {
                for(int j = 0; j < other.cols; j++)
                {
                    s = 0;
                    for(int k = 0; k < cols; k++)
                    {
                        s += matrix[i][k] * other.matrix[k][j];
                    }
                    res.matrix[i][j] = s;
                }
            }
            return res;
        }
        else
        {
            throw invalid_argument("Nie mozna mnozyc");
        }
        
    }

    string getNazwa() const
    {
        return nazwa;
    }
    int getRow() const
    {
        return rows;
    }
    int getCol() const
    {
        return cols;
    }
  

    double wczytajLiczbeDouble() 
    {
        double liczba;
        if (!(cin >> liczba) || cin.fail()) 
        {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            throw invalid_argument("Blad!. Nie podales liczby\n");
        }
        return liczba;
    }
    virtual double wyznacznik() const
    {
        throw invalid_argument("Nie mozna obliczyc wyznacznika");
    }
   

    Macierz operator+(const Macierz& other) const
    {
        Macierz res(*this);
        if(rows == other.rows && cols == other.cols)
        {
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    res.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
                }
            }
            return res;
        }
        else
        {
           throw invalid_argument("Nie mozna dodawac");
        }
    }

    Macierz operator-(const Macierz& other) const
    {
        Macierz res(*this);
        if(rows == other.rows && cols == other.cols)
        {
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    res.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
                }
            }
            return res;
        }
        else
        {
            throw invalid_argument("Nie mozna odejmowac");
        }
        
    }

    protected:
    int rows,cols;
    string nazwa;
    vector<vector<double>> matrix;
};

class Macierz_kwad : public Macierz
{
    public:
    Macierz_kwad(string name, int rozmiar) : Macierz(name, rozmiar, rozmiar) {}
    
    double wyznacznik() const override
    {
        double res = 0;
        if(rows == cols)
        {
            vector<double> WK(rows);
            for(int i = 0; i < rows; i++)
            {
                WK[i] = i;
            }
            res = det(rows, 0, WK, matrix);
            return res;
        }
        else
        {
            throw invalid_argument("Nie mozna obliczyc wyznacznika");
        }
        
    }


    private:
    double det(int n, int w, vector<double> WK, vector<vector<double>> A) const
    {
        int s,m,k;
        if(n == 1)
        {
            return A[w][WK[0]];
        }
        else
        {
            vector<double> KK(n-1);
            s = 0; m = 1;
            for(int i = 0; i < n; i++)
            {
                k = 0;
                for(int j = 0; j < n - 1; j++)
                {
                    if(k == i)
                    {
                        k++;
                    } 
                    KK[j] = WK[k++];
                }
                s += m*A[w][WK[i]]*det(n-1, w+1, KK, A);
                m = -m;

            }
            return s;
        }
    }
};
