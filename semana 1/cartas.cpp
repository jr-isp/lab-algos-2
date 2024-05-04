/* Problema de las N cartas Codeforces
Hecho por Jesús Isea 16-10553
*/

// Ahora usando pointers

#include <iostream>
using namespace std;

void ordenar(int* lista, int longitud);
bool esta_ordenada(int* lista, int longitud);
void mostrar_lista(int* lista, int longitud);
int cuenta_cartas_distintas(int* lista, int longitud);
int* cambios_cartas(int* lista, int longitud, int cartas_distintas, int& longitud_cambios);
int* leer_caso(int& numero_cartas, int& k);
int* conteo_cartas(int* lista, int longitud);
int numero_de_casos();

int respuesta(int* lista, int longitud, int k);

int main(){

    int casos = numero_de_casos();
    int* respuestas = new int[casos];
    for (int n = 0; n < casos; n++){
        int k, longitud;
        int* lista;

        lista = leer_caso(longitud, k);

        bool ordenada = esta_ordenada(lista, longitud);
        
        if (!ordenada){
            ordenar(lista, longitud);
            }

        respuestas[n] = respuesta(lista, longitud, k);

        delete[] lista;
    }

    for (int n = 0; n < casos; n++){
        cout << respuestas[n] << endl;
    }

    delete[] respuestas;

    return 0;
}

int respuesta(int* lista, int longitud, int k){
    int cartas_distintas = cuenta_cartas_distintas(lista, longitud);
    int* conteo = conteo_cartas(lista, longitud);

    bool posible = false;
    for (int n = 1; n < 2*cartas_distintas; n += 2){
        if (conteo[n] >= k){
            posible = true;
            break;
        }
    }

    if(posible)
        return (k-1);
    else
        return longitud;

    delete[] conteo;
}


void ordenar(int* lista, int longitud){ //ordena array de enteros con BUBBLESORT
    bool terminado = esta_ordenada(lista, longitud);
    int bubble;
    int contador = 0;
    
    while (!terminado){
        bubble = lista[0];
        for (int n = 1; n < longitud; n++){
            if (lista[n] > lista[n-1]){
                bubble = lista[n];
                lista[n] = lista[n-1];
                lista[n-1] = bubble;
            }
        }

        terminado = esta_ordenada(lista, longitud);

        contador++;
        if (contador >= longitud){
            terminado = true;
            cout << "Excedido límite de bucles, error" << endl;
        }
    }
}

bool esta_ordenada(int* lista, int longitud){ //true si ordenada decreciente, 
//false en caso contrario
    bool retorno = true;
    bool bucle = false;

    if (longitud >= 2){
        bucle = true;
    }

    if (bucle){
        for (int n = 1; n<longitud;n++){
            if (lista[n] > lista[n-1]){
                retorno = false;
                break;
                }
        }
    }

    return (retorno);
}

void mostrar_lista(int* lista, int longitud){
    cout << "Lista: ";
    for (int n = 0; n < longitud; n++){
        cout << lista[n] << " ";
    }
    cout << endl;
}


int* conteo_cartas(int* lista, int longitud){ //una lista con el
//numero de la carta y el # de cartas de ese número

    int cartas_distintas = cuenta_cartas_distintas(lista, longitud);
    int longitud_cambios = cartas_distintas;
    int* cambios = cambios_cartas(lista, longitud, cartas_distintas, longitud_cambios); 

    int* conteo = new int[2*cartas_distintas];
    int* conjunto_cartas = new int[cartas_distintas];

    conjunto_cartas[0] = lista[0];
    for (int n = 1; n < cartas_distintas; n++){
        conjunto_cartas[n] = lista[cambios[n-1]];
    }

    if (cambios[0] == -1){ //no hay cambio todas son iguales
        conteo[0] = conjunto_cartas[0];
        conteo[1] = longitud;
    }
    else{
        for (int n = 0; n < 2*cartas_distintas-2; n += 2){
            conteo[n] = conjunto_cartas[(n/2)];
            conteo[n+1] = (cambios[(n/2)]-cambios[(n/2)-1]);
        }
        conteo[2*cartas_distintas - 2] = conjunto_cartas[cartas_distintas - 1];
        conteo[2*cartas_distintas - 1] = longitud - cambios[cartas_distintas - 2];
    }

    delete[] conjunto_cartas;
    return conteo;
}

int cuenta_cartas_distintas(int* lista, int longitud){
    // devuelve cuántos números distintos hay en la lista
    int cartas_distintas = 1;
    for (int n = 1; n < longitud; n++){
        if (lista[n] != lista[n-1]){
            cartas_distintas++;
        }
    }
    return cartas_distintas;
}

int* cambios_cartas(int* lista, int longitud, int cartas_distintas, int& longitud_cambios){
    // lista con los indices donde hay cambios de cartas
        int* cambio_cartas;

        if (cartas_distintas == 1){ //no hay cambios porque todas son iguales
            cambio_cartas = new int[1];
            cambio_cartas[0] = -1;
            longitud_cambios = 1;
        }
        else{
            cambio_cartas = new int[cartas_distintas - 1]; //array con los indices
            //donde hay cambio de carta

            int elementos = 0;
            for (int n = 1; n < longitud; n++){
                if (lista[n] != lista[n-1]){
                    cambio_cartas[elementos] = n;
                    elementos++;
                }
            }
            longitud_cambios = cartas_distintas - 1;
        }
    return (cambio_cartas);
}

int* leer_caso(int& numero_cartas, int& k){
    cin >> numero_cartas >> k;
    int* lista = new int[numero_cartas];
    for (int n = 0; n < numero_cartas; n++){
        cin >> lista[n];
    }

    return lista;
}

int numero_de_casos(){
    int numero;
    cin >> numero;
    return numero;
}