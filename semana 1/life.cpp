/* programa que resuelve el problema de
la vida, el universo y todo lo demás de SPOJ.

Hecho por Jesús Isea 16-10553*/

/*
compara las entradas de cin con 42, si no coincide entonces la imprime de vuelta. Si coincide,
entonces se detiene el programa.
*/

#include <iostream>
using namespace std;

int main(){
    int input;

    cin >> input; 
    while (input != 42){
        cout << input << endl;
        cin >> input;
    }
}
