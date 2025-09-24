#include "util.h"
#include <fstream>
#include <iostream>
#include <limits>
using namespace std;

bool cargarPreset(Cola<Ticket>& eventos, const string& path){
    ifstream in(path);
    if(!in.is_open()){
        cout << "No se pudo abrir: " << path << "\n";
        return false;
    }
    string line;
    int count=0;
    while(getline(in, line)){
        if(line.empty()) continue;
        Ticket t;
        if(ticketFromLine(line, t)){
            eventos.enqueue(t);
            ++count;
        }
    }
    cout << "Cargados " << count << " tickets desde " << path << "\n";
    return count>0;
}

void encolarManual(Cola<Ticket>& eventos){
    Ticket t;
    cout << "ID: "; cin >> t.id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Cliente: "; getline(cin, t.cliente);
    cout << "Asunto: ";  getline(cin, t.asunto);
    cout << "Detalle: "; getline(cin, t.detalle);
    eventos.enqueue(t);
    cout << "Ticket encolado.\n";
}

void procesarSiguiente(Cola<Ticket>& eventos, Pila<Accion>& acciones){
    Ticket t;
    if(!eventos.dequeue(t)){
        cout << "No hay tickets para procesar.\n";
        return;
    }
    Accion a;
    a.tipo = TipoAccion::RESOLVER;
    a.ticket = t;

    // ⚡ limpiar buffer antes de getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Ingrese comentario para este ticket: ";
    getline(cin, a.comentario);

    acciones.push(a);

    cout << "Procesado ticket: ";

    mostrarTicket(t);

    cout << "Comentario guardado: " << a.comentario << "\n";
}

void deshacer(Pila<Accion>& acciones, Cola<Ticket>& eventos){
    Accion a;
    if(!acciones.pop(a)){
        cout << "No hay acciones para deshacer.\n";
        return;
    }
    if(a.tipo == TipoAccion::RESOLVER){
        eventos.enqueueFront(a.ticket);
        cout << "UNDO: Reabierto ticket "; mostrarTicket(a.ticket);
    } else {
        cout << "Tipo de accion no soportado para undo.\n";
    }
}

void buscarRec(const Cola<Ticket>& eventos, const Pila<Accion>& acciones){
    cout << "Buscar por ID: ";
    int id; cin >> id;

    bool enCola = eventos.searchRec([&](const Ticket& t){ return mismoId(t,id); });
    bool enPila = acciones.searchRec([&](const Accion& ac){ return mismoId(ac.ticket,id); });

    cout << "Resultado busqueda id #" << id << " -> "
         << "Cola: " << (enCola ? "SI" : "NO")
         << " | Pila: " << (enPila ? "SI" : "NO") << "\n";
}

void mostrarStats(const Cola<Ticket>& eventos, const Pila<Accion>& acciones){
    cout << "Pendientes (Cola): " << eventos.sizeRec()
         << " | Acciones (Pila): " << acciones.sizeRec() << "\n";
}

void printColaRec(const Cola<Ticket>& eventos){
    cout << "--- COLA (pendientes) ---\n";
    eventos.printRec([](const Ticket& t){ mostrarTicket(t); });
}
void printPilaRec(const Pila<Accion>& acciones){
    cout << "--- PILA (acciones, top->bottom) ---\n";
    acciones.printRec([](const Accion& a){
        cout << "[Accion: " << (a.tipo==TipoAccion::RESOLVER ? "RESOLVER" : "OTRA")
             << "] (Comentario: " << a.comentario << ")\n";
        mostrarTicket(a.ticket);
    });
}
