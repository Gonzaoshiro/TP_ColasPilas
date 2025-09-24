#include "dominio.h"
#include <sstream>
using namespace std;

void mostrarTicket(const Ticket& t){
    cout << "[#" << t.id << "] " << t.cliente << " | "
         << t.asunto << " | " << t.detalle << "\n";
}

bool mismoId(const Ticket& t, int id){ return t.id == id; } //Sirve para la busqueda por ID

bool ticketFromLine(const string& line, Ticket& out){
    stringstream ss(line); //Convierte el string en un flujo para poder leerlo campo por campo
    string id, cliente, asunto, detalle;
    if(!getline(ss, id, ';')) return false; //getline hace que lea hasta que encuentre un ";"
    if(!getline(ss, cliente, ';')) return false;
    if(!getline(ss, asunto, ';')) return false;
    if(!getline(ss, detalle)) return false; //En caso de que algun campo este vacio devuelve false

    try { out.id = stoi(id); } //stoi pasa de string a int el id
    catch(...) { return false; } //si no se puede devuelve false

    out.cliente = cliente;
    out.asunto  = asunto;
    out.detalle = detalle;
    return true;
}
