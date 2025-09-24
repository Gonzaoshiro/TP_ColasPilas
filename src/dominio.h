#ifndef DOMINIO_H
#define DOMINIO_H

#include <string>
#include <iostream>
using namespace std;

// Representa un ticket de soporte: lo que entra en la COLA (FIFO)
struct Ticket {
    int id{};
    string cliente;
    string asunto;
    string detalle;
};

// Tipo de acción para el historial (PILA LIFO)
enum class TipoAccion { RESOLVER };

// Cada acción guarda el ticket y metadatos (quién/qué hizo)
struct Accion {
    TipoAccion tipo{TipoAccion::RESOLVER};
    Ticket ticket;
    string comentario; // ej. "Resuelto por operador X"
};

// ==== Helpers del dominio ====
void mostrarTicket(const Ticket& t);
bool mismoId(const Ticket& t, int id);
bool ticketFromLine(const string& line, Ticket& out);

#endif // DOMINIO_H
