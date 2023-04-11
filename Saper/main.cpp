#include <iostream>
#include <cstdlib>
#include <ctime>
//--------------------------------------------
void print(int m, int n, char **tab){
    for (int i=0; i<=30; i++) std::cout<<std::endl;

    std::cout<<'/';
    for (int j=0; j<n; j++) std::cout<<'-';
    std::cout<<'\\'<<std::endl;

    for (int i=0; i<m; i++){
        std::cout<<'|';
        for (int j=0; j<n; j++){
            std::cout<<tab[i][j];
        }
        std::cout<<'|'<<std::endl;
    }

    std::cout<<'\\';
    for (int j=0; j<n; j++) std::cout<<'-';
    std::cout<<'/'<<std::endl;
}
//-----------------------------------------------
void check(int x, int y, int m, int n, char**tab, int**bab, int &t){
    if(tab[x][y]!='=') return;
    if(bab[x][y]){
        tab[x][y]='*';
        print(m, n, tab);
        std::cout<<"Upssss"<<std::endl;
    }else{
        int d=0;
        for(int i=x-1; i<=x+1; i++){
            for (int j=y-1; j<=y+1; j++){
                if(i>=0 && j>=0 && i<m && j<n) if(bab[i][j]) d++;
            }
        }

        tab[x][y]=d+48;
        t++;
        if(d==0){
            tab[x][y]=' ';
            for(int i=x-1; i<=x+1; i++){
                for (int j=y-1; j<=y+1; j++){
                    if(i>=0 && j>=0 && i<m && j<n && (i!=x || j!=y)) check(i, j, m, n, tab, bab, t);
                }
            }
        }

    }
}
//-----------------------------------------------
char** set(int m, int n){
    char ** tab=new char* [m];
    for (int i=0; i<m; i++){
        tab[i]=new char[n];
        for (int j=0; j<n; j++){
            tab[i][j]='=';
        }
    }
    return tab;
}


int** setb(int m, int n, int bombs, char**a, int &t){
    int **tab=new int*[m];
    for (int i=0; i<m; i++){
        tab[i]=new int[n];
        for (int j=0; j<n; j++){
            tab[i][j]=0;
        }
    }

    int b[bombs][2];

    int x;
    int y;
    std::cin>>x;
    x--;
    std::cin>>y;
    y--;

    for (int i=0; i<bombs; i++){
        b[i][0]=rand() % m;
        b[i][1]=rand() % n;
        if(b[i][0]==x && b[i][1]==y){
            i--;
            continue;
        }
        for(int j=0; j<i; j++){
            if (   b[i][0]==b[j][0] && b[i][1]==b[j][1] ){
                i--;
                break;
            }
        }
    }

    for (int i=0; i<bombs; i++){
        tab[b[i][0]][b[i][1]]=1;
    }
    check(x, y, m, n, a, tab, t);
    return tab;
}

//-----------------------------------------------
void dealokacja(int m, char*(*tab)){
    for (int i=0; i<m; i++){
        delete [] tab[i];
    }
    delete [] tab;
}

void dealokacja2(int m, int**tab){
    for (int i=0; i<m; i++){
        delete[] tab[i];
    }
    delete[] tab;
}
//-----------------------------------------------


//--------------------------------------------------
void flaga(int x, int y, char**tab){
    if(tab[x][y]='=') tab[x][y]='f';
}


//------------------------------------------------
void game(int m, int n, char** tab, int **bab, int &t, int bombs){
    int x=0;
    int y=0;
    for (; 1;) {
        if (t>=m*n-bombs) {
            print(m,n,tab);
            std::cout << "Win";
            break;
        }
        print(m,n,tab);
        std::cin >> x;
        x--;
        if(x==-1){
            std::cin>>x;
            x--;
            std::cin>>y;
            y--;
            flaga(x,y,tab);
            continue;
        }
        std::cin >> y;
        y--;
        check(x, y, m, n, tab, bab, t);


    }
}

//------------------------------------------------
int main() {
    std::cout<<"Zasady:\n"
               "mapa zawiera 10 bomb i ma wymiary 10x10 (parametry można zmienic w kodzie)\n"
               "pole które chcemy kliknąć wybieramy przez wpierw podanie współrzędnej x, a po wcisnieciu enter, współrzędnej y\n"
               "pola indeksujemy od 1 do 10"
               "jesli chcemy postawić flagę to zamiast podania zmniennej x podajemy wartosc 0\n"
               "Jeśli jesteś gotów napisz 't':\n";
    //wymiary mapy
    for (;1;){
        char x;
        std::cin>>x;
        if (x=='t') break;
    }
    int m=10;
    int n=10;
    //ilość bomb
    int bombs=2;
    int t=0;
    //-------------------------------------------------
    char **tab=set (m, n);
    srand( time( NULL ) );
    print(m,n,tab);
    int **bab=setb(m, n, bombs, tab, t);
    //-------------------------------------------------
    game(m,n,tab, bab, t, bombs);

    //-------------------------------------------------
    dealokacja(m, tab);
    dealokacja2(m, bab);
    return 0;
}
