#include <iostream>
#include <cstdlib>
#include <windows.h>
#define NumFilosofos 5
#define NumPalillos NumFilosofos
#define MinDeComidas 6

using namespace std;

//Indicara el estado del Filosofo (Pensando o Comiendo
int Filosofos[NumFilosofos];
//General el total de Turnos
int TotalTurnos = NumFilosofos / 2;
//Guarda el ID de los Filosofos que pueden comer
int Turnos[NumFilosofos / 2];
//Guarda las Comidas hechas por cada Filosofo
int ContadorComidas[NumFilosofos];

int DuracionDelTurno = 2;

//Esta funcion recibe como parametro el IdFilosofoInicial que en main es idPrimerFilosofo
void AsignarTurnos(int IdFilosofoInicial)
{
    //En el arreglo se guarda el ID del Filoso Inicial
    Turnos[0] = IdFilosofoInicial;

    //Este for se encargara de llenar la segunda casilla de turno
    for(int i = 1; i < TotalTurnos; i++)
    {

        //Basicamente sera 2 numeros mayor al IdFilosofoInicial
        int idFilosofo = Turnos[i - 1] + 2;

        //Si el segundo turno es 5 o 6, entonces estos se volveran 0 u 1 respectivamente
        if(idFilosofo == NumFilosofos)
        {
            idFilosofo = 0;
        } else if(idFilosofo ==  NumFilosofos + 1)
        {
            idFilosofo = 1;
        }
        //Se agrega el segundo ID en turno
        Turnos[i] = idFilosofo;
    }
}

void TerminoDeComida(){
    //Incrementa el contador de comidas para aquellos que esten comiendo
    for(int f : Turnos)
    {
        ContadorComidas[f]++;
    }
}

int VerificarCantidadDeComidas()
{
    //Recorre el arreglo para ver si todos comieron 6 veces, si comieron las 6 veces restorna un 1 de lo contrario un 0
    int TodosComieron = 1;
    for(int c : ContadorComidas)
    {
        if(c < MinDeComidas)
        {
            TodosComieron = 0;
            break;
        }
    }
    return TodosComieron;
}

void ImprimirPalillos(int IdFilosofo)
{
    //Imprime los palillos usados por los Filosofos
    int PalilloDer = IdFilosofo;
    int PalilloIzq = IdFilosofo + 1;
    //Si el palillo izquierdo es igual a 5, entonces se volvera 0
    if(PalilloIzq == NumPalillos)
    {
        PalilloIzq = 0;
    }

    cout << "Con los palillos " << PalilloDer << " y " << PalilloIzq << endl;
}


void ImprimirEstadoFilosofos(){
    //Recorre a los Filosofos para imprimir su estado
    for(int i = 0; i < NumFilosofos; i++)
    {
        int EstaComiendo = 0;
        for(int f : Turnos)
        {
            //Aquellos que tengan su turno de comer imprimira que esta comiendo y las comidas que lleva
            if(i == f)
            {
                EstaComiendo = 1;
                cout << "El filosofo " << i << " esta comiendo";
                cout << " | Lleva "<< ContadorComidas[i] << " comidas"<< endl;
                ImprimirPalillos(i);
                break;
            }
        }
        //Si el Filosofo en el recorrido no esta comiendo entonces imprime lo siguiente
        if(EstaComiendo == 0)
        {
            cout << "El filosofo " << i << " esta pensando | Lleva "<< ContadorComidas[i] << " comidas"<< endl;
        }
    }

    cout << endl << endl;
}

int main()
{
    int idPrimerFilosofo = 0;

    //El ciclo se mantendra hasta que todos coman minimo 6 veces
    while(!VerificarCantidadDeComidas()){

        AsignarTurnos(idPrimerFilosofo);

        ImprimirEstadoFilosofos();

        Sleep(DuracionDelTurno);

        TerminoDeComida();

        idPrimerFilosofo++;
        //Si el primer filosofo en el turno llega a ser 5, este cambiara a 0
        if(idPrimerFilosofo == NumFilosofos) {
            idPrimerFilosofo = 0;
        }
    }

    cout << "Estado final: " << endl << endl;

    int i = 0;

    //Recorre el arreglo de Contador de comidas e imprime sus datos
    for(int c : ContadorComidas)
    {
        cout << "El filosofo " << i << " comio "<< c << " comidas"<< endl;
        i++;
    }
    cout << endl << endl;

    cout << "Todos los Filosofos han comido minimo " << MinDeComidas << " veces" << endl << endl;

    return 0;
}

