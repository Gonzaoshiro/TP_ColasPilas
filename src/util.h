#ifndef UTIL_H
#define UTIL_H

#include <string>
#include "dominio.h"
#include "cola.h"
#include "pila.h"
using namespace std;

bool cargarPreset(Cola<Ticket>& eventos, const string& path);
void encolarManual(Cola<Ticket>& eventos);
void procesarSiguiente(Cola<Ticket>& eventos, Pila<Accion>& acciones);
void deshacer(Pila<Accion>& acciones, Cola<Ticket>& eventos);
void buscarRec(const Cola<Ticket>& eventos, const Pila<Accion>& acciones);
void mostrarStats(const Cola<Ticket>& eventos, const Pila<Accion>& acciones);
void printColaRec(const Cola<Ticket>& eventos);
void printPilaRec(const Pila<Accion>& acciones);

#endif // UTIL_H
