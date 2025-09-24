#include "menu.h"
#include "cola.h"
#include "pila.h"
#include "dominio.h"
#include "util.h"
#include <iostream>
using namespace std;

void mostrarMenu(){
    cout << "\n=== TP Pilas y Colas (Soporte Tecnico) ===\n"
         << "1) Cargar datos preset\n"
         << "2) Encolar ticket manual\n"
         << "3) Procesar siguiente (dequeue + push accion)\n"
         << "4) Deshacer ultima accion (pop + reabrir)\n"
         << "5) Mostrar Cola (recursivo)\n"
         << "6) Mostrar Pila (recursivo)\n"
         << "7) Buscar por ID (recursivo)\n"
         << "8) Vaciar estructuras (recursivo)\n"
         << "9) Estadisticas (size recursivo)\n"
         << "0) Salir\n"
         << "Opcion: ";
}

void loopMenu(){
    Cola<Ticket> eventos;
    Pila<Accion> acciones;

    int op;
    do{
        mostrarMenu();
        if(!(cin >> op)) break;

        switch(op){
            case 1: cargarPreset(eventos, "data/preset_tickets.txt"); break;
            case 2: encolarManual(eventos); break;
            case 3: procesarSiguiente(eventos, acciones); break;
            case 4: deshacer(acciones, eventos); break;
            case 5: printColaRec(eventos); break;
            case 6: printPilaRec(acciones); break;
            case 7: buscarRec(eventos, acciones); break;
            case 8: eventos.clearRec(); acciones.clearRec(); cout<<"Vaciadas.\n"; break;
            case 9: mostrarStats(eventos, acciones); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida\n";
        }
    } while(op != 0);
}
