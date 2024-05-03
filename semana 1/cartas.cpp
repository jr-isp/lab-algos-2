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
int* cambios_cartas(int* lista, int longitud, int cartas_distintas);
int* conteo_cartas(int* lista, int longitud);
int* calcular_nuevas_cartas(int* lista_reducida, int& longitud, int k);
void procedimiento_intercambio(int* lista, int &longitud, int k);

int main(){
    const int k = 3; //te lo da el problema
    int longitud;


    int* lista = bienvenida(longitud);

    bool ordenada = esta_ordenada(lista, longitud);
    
    if (!ordenada){
        ordenar(lista, longitud);
        }

    mostrar_lista(lista, longitud);
    
    procedimiento_intercambio(lista, longitud, k);

    mostrar_lista(lista, longitud);

    return 0;
}

int* bienvenida(int &longitud){
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
        bool mazo_vacio = (k == longitud);
        
        if (!mazo_vacio){
            nueva_lista = new int[longitud - k];
            for (int n = 0; n < (longitud - k); n++){
                nueva_lista[n] = lista[k+n];
            }
            longitud = longitud - k;
        }
        else {
            nueva_lista = new int[1];
            nueva_lista[0] = -1;
            longitud = 1;
        }

    }

    return(nueva_lista);
}

int* tomar_cartas(int* lista, int* nuevas_cartas, int &longitud, int k){
    //Para recoger k-1 cartas de la lista nuevas_cartas

    int* nueva_lista;

    //caso borde, la lista botó todas
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
    int* cambios = cambios_cartas(lista, longitud, cartas_distintas); 

    int* conteo = new int[2*cartas_distintas];
    int* conjunto_cartas = new int[cartas_distintas + 1];

    conjunto_cartas[0] = lista[0];
    for (int n = 1; n < cartas_distintas; n++){
        conjunto_cartas[n] = lista[cambios[n-1]];
    }

    conteo[0] = conjunto_cartas[0];
    conteo[1] = cambios[0];
    for (int n = 2; n < 2*cartas_distintas - 2; n += 2){
        conteo[n] = conjunto_cartas[(n/2)];
        conteo[n+1] = (cambios[(n/2)]-cambios[(n/2)-1]);
    }

    if (cartas_distintas > 1){
        conteo[2*cartas_distintas - 2] = conjunto_cartas[cartas_distintas - 1];
        conteo[2*cartas_distintas - 1] = longitud - cambios[cartas_distintas - 2];
    }
    else
        conteo[1] = longitud;

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

int* cambios_cartas(int* lista, int longitud, int cartas_distintas){
    // lista con los indices donde hay cambios de cartas
        int* cambio_cartas;

        if (cartas_distintas == 1){
            cambio_cartas = new int[1];
            cambio_cartas[0] = -1;
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
        }
    return (cambio_cartas);
}

void procedimiento_intercambio(int* lista, int &longitud, int k){
    int* nuevas_cartas;

    int* conteo = conteo_cartas(lista, longitud);
    if (conteo[1] < k) {
        // nuevas_cartas = new int[1];
        // nuevas_cartas[0] = -1; //caso borde
        cout << "No hay suficientes cartas iguales para descartar..." << endl;
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
    }
}

int* calcular_nuevas_cartas(int* lista_reducida, int& longitud, int k){
    int cartas_distintas = cuenta_cartas_distintas(lista_reducida, longitud);
    int* conteo = conteo_cartas(lista_reducida, longitud);
    cout << "Conteo ";
    mostrar_lista(conteo, cartas_distintas);
    int* nuevas_cartas = new int[k-1];

    int cartas_a_anadir = 0; //cartas a añadir
    if (conteo[1] >= k){ //quedan mas de k cartas iguales 
        cout << "Quedan más de " << k << " cartas, añadimos " << k-1 << " iguales" <<endl;
        for (int n = 0; n < (k-1) ; n++){   
            cout << "índice " << n << " ";
            nuevas_cartas[n] = conteo[0];   
        }
        //añadimos k-1 cartas iguales a la primera
    }
    else{
        cout << "Completamos cartas"<<endl;
        while (cartas_a_anadir < (k-1)){
        //un bucle para añadir las cartas

            for (int n = 0; n < 2*cartas_distintas; n+=2){
                //recorremos la lista para saber cuales añadir
                int numero_carta = conteo[n];
                int cantidad_carta = conteo[n+1];

                int cartas_que_faltan = 0; //para llegar a k

                if (cantidad_carta < k){
                    cartas_que_faltan = k-cantidad_carta; //cuentas le faltan para llegar a k
                    
                    for (int m = 0; m < cartas_que_faltan; m++){
                        if (cartas_a_anadir < (k-1)){
                            nuevas_cartas[n] = numero_carta;
                            cartas_a_anadir++;
                        }
                    }
                }
            }
        }
    }
    cout << "Nuevas cartas: ";
    mostrar_lista(nuevas_cartas, cartas_a_anadir);
    return nuevas_cartas;
}