/* Problema de las N cartas Codeforces
Hecho por Jesús Isea 16-10553
*/

// Ahora usando pointers

#include <iostream>
using namespace std;

int* bienvenida(int &longitud);
void ordenar(int* lista, int longitud);
bool esta_ordenada(int* lista, int longitud);
void mostrar_lista(int* lista, int longitud);
int* botar_cartas(int* lista, int &longitud, int k);
int* tomar_cartas(int* lista, int* nuevas_cartas, int &longitud, int k);
int cuenta_cartas_distintas(int* lista, int longitud);
int* cambios_cartas(int* lista, int longitud, int cartas_distintas, int& longitud_cambios);
int* conteo_cartas(int* lista, int longitud);
int* calcular_nuevas_cartas(int* lista_reducida, int longitud, int k);
bool procedimiento_intercambio(int* lista, int &longitud, int k);

int main(){
    int k = 5; //te lo da el problema
    int longitud;

    int* lista = bienvenida(longitud);
    bool ordenada = esta_ordenada(lista, longitud);
    
    if (!ordenada){
        ordenar(lista, longitud);
        }

    mostrar_lista(lista, longitud);
    
    bool terminado = procedimiento_intercambio(lista, longitud, k);

    mostrar_lista(lista, longitud);

    return 0;
}

int* bienvenida(int &longitud){ // Genera el mazo de cartas
    cout << "Escriba la cantidad de elementos: ";
    cin >> longitud;
    int numero;

    int* lista = new int [longitud];

    for (int n = 0; n < longitud; n++){
        cout << "Escriba el elemento: ";
        cin >> numero;
        
        lista[n] = numero;
    }

    return (lista);
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

int* botar_cartas(int* lista, int &longitud, int k){//bota las k primeras cartas
    bool permitido;
    int * nueva_lista;
    if (longitud < k){
        permitido = false;
        cout << "Quedan menos de " << k << " cartas, no se puede hacer." << endl;
        nueva_lista = lista;
    }

    if (permitido){
        bool mazo_vacio = (k == longitud); //si se botan todas las cartas
        
        if (!mazo_vacio){ //mazo no vacio
            nueva_lista = new int[longitud - k];
            for (int n = 0; n < (longitud - k); n++){
                nueva_lista[n] = lista[k+n];
            }
            longitud = longitud - k;
        }
        else { //mazo vacio
            nueva_lista = new int[1];
            nueva_lista[0] = -1; //solo es un place holder
            longitud = 1;
        }

    }

    return(nueva_lista);
}

int* tomar_cartas(int* lista, int* nuevas_cartas, int &longitud, int k){
    //Para recoger k-1 cartas de la lista nuevas_cartas

    int* nueva_lista;

    //caso borde, la lista botó todas en el paso anterior
    if (longitud == 1 && lista[0] == -1){
        nueva_lista = new int[k - 1];
        for (int n = 0; n < (k - 1); n++){
            nueva_lista[n] = nuevas_cartas[n];
        }
        longitud = k-1;
    }

    else {
        nueva_lista = new int[longitud + k - 1];
        for (int n = 0; n < longitud; n++){
            nueva_lista[n] = lista[n];
        }
        for (int n = longitud; n < (longitud + k - 1); n++){
            nueva_lista[n] = nuevas_cartas[n-longitud];
        }
        longitud = longitud + k - 1;
    }
    return (nueva_lista);
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

bool procedimiento_intercambio(int* lista, int &longitud, int k){
    //el procedimiento como tal de cada ronda, de botar y tomar cartas nuevas
    int* nuevas_cartas;
    bool terminado = false; //para saber si terminamos con esta ronda

    int* conteo = conteo_cartas(lista, longitud);
    if (conteo[1] < k) {
        // nuevas_cartas = new int[1];
        // nuevas_cartas[0] = -1; //caso borde
        cout << "No hay suficientes cartas iguales para descartar..." << endl;
        terminado = true;
    }
    else{
        cout << "Botaremos " << k << " cartas." << endl;
        lista = botar_cartas(lista, longitud, k);
        cout << "Cartas después de botar: ";
        mostrar_lista(lista, longitud);

        cout << "Procedemos a calcular cuales cartas tomar"<<endl;
        nuevas_cartas = calcular_nuevas_cartas(lista, longitud, k);

        cout << "Las tomamos"<<endl;
        lista = tomar_cartas(lista, nuevas_cartas, longitud, k);

        if (longitud == k-1)
            terminado = true;
    }

    return terminado;
}

int* calcular_nuevas_cartas(int* lista_reducida, int longitud, int k){
    //para calcular cuales serán las cartas nuevas que debemos tomar
    int cartas_distintas = cuenta_cartas_distintas(lista_reducida, longitud);
    int* conteo = conteo_cartas(lista_reducida, longitud);
    cout << "Conteo ";
    mostrar_lista(conteo, 2*cartas_distintas);
    int* nuevas_cartas = new int[k-1];

    int cartas_a_anadir = 0; // nro de cartas a añadir calculadas
    if (conteo[1] >= k){ //quedan mas de k cartas iguales en la mano reducida
        cout << "Quedan más de " << k << " cartas, añadimos " << k-1 << " iguales" <<endl;
        for (int n = 0; n < (k-1) ; n++){   
            cout << "índice " << n << " ";
            nuevas_cartas[n] = conteo[0];   
        }
        //añadimos k-1 cartas iguales a la primera
    }
    else{
        cout << "Completamos cartas"<<endl;
        int posicion = 0;
    
        for (int n = 0; n < 2*cartas_distintas; n+=2){
            //recorremos conteo para saber cuales añadir
            int numero_carta = conteo[n];
            cout << "Nro de carta " << numero_carta << endl;
            int cantidad_carta = conteo[n+1];
            cout << "Cantidad de cartas " << cantidad_carta << endl;

            int cartas_que_faltan = 0; //para llegar a k}
            int cartas_de_este_numero = 0;

            if (cantidad_carta < k){
                cartas_que_faltan = k-cantidad_carta; //cuentas le faltan para llegar a k
                cout << "Faltan " << cartas_que_faltan << " para llegar a " << k;
                cout << " cartas iguales de ese número" << endl;

                while (cartas_a_anadir < (k-1) && cartas_de_este_numero < cartas_que_faltan){
                    nuevas_cartas[posicion] = numero_carta;
                    cartas_a_anadir++;
                    posicion++;
                    cartas_de_este_numero++;
                    cout << "Se añade un " << numero_carta << endl;
                    cout << "Van " << cartas_a_anadir << " cartas calculadas" << endl;

                    if (cartas_a_anadir == (k-1)){
                        cout << "Calculadas todas las cartas" << endl;
                    }
                }
            }
        }
        cout << "Se calcularon " << cartas_a_anadir << " cartas a añadir" << endl;
    }
    cout << "Nuevas cartas: ";
    mostrar_lista(nuevas_cartas, cartas_a_anadir);
    return nuevas_cartas;
}