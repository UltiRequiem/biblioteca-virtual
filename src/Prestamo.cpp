#include "../include/Prestamo.h"
#include <sstream>
#include <iomanip>
#include <ctime>

using std::cout;
using std::endl;
using std::getline;
using std::localtime;
using std::ostream;
using std::put_time;
using std::stoll;
using std::string;
using std::stringstream;
using std::time;
using std::time_t;
using std::tm;

Prestamo::Prestamo(const string &dniUsuario, const string &isbnLibro)
    : dniUsuario(dniUsuario), isbnLibro(isbnLibro), activo(true)
{
  fechaPrestamo = time(nullptr);
  fechaDevolucion = 0;
}

Prestamo::Prestamo(const string &dniUsuario, const string &isbnLibro,
                   time_t fechaPrestamo, time_t fechaDevolucion, bool activo)
    : dniUsuario(dniUsuario), isbnLibro(isbnLibro), fechaPrestamo(fechaPrestamo),
      fechaDevolucion(fechaDevolucion), activo(activo) {}

void Prestamo::marcarDevuelto()
{
  if (activo)
  {
    fechaDevolucion = time(nullptr);
    activo = false;
  }
}

int Prestamo::diasPrestado() const
{
  time_t fechaFin = activo ? time(nullptr) : fechaDevolucion;
  return static_cast<int>((fechaFin - fechaPrestamo) / (24 * 60 * 60));
}

bool Prestamo::estaVencido(int diasLimite) const
{
  return activo && diasPrestado() > diasLimite;
}

void Prestamo::mostrarInformacion() const
{
  cout << "=== PRÉSTAMO ===" << endl;
  cout << "Usuario (DNI): " << dniUsuario << endl;
  cout << "Libro (ISBN): " << isbnLibro << endl;
  cout << "Fecha préstamo: " << fechaToString(fechaPrestamo) << endl;

  if (activo)
  {
    cout << "Estado: ACTIVO" << endl;
    cout << "Días prestado: " << diasPrestado() << endl;
    if (estaVencido())
    {
      cout << "PRÉSTAMO VENCIDO!!" << endl;
    }
  }
  else
  {
    cout << "Estado: DEVUELTO" << endl;
    cout << "Fecha devolución: " << fechaToString(fechaDevolucion) << endl;
    cout << "Duración préstamo: " << diasPrestado() << " días" << endl;
  }
  cout << "================" << endl;
}

string Prestamo::fechaToString(time_t fecha) const
{
  if (fecha == 0)
    return "N/A";

  tm *tm_info = localtime(&fecha);
  stringstream ss;
  ss << put_time(tm_info, "%d/%m/%Y %H:%M");
  return ss.str();
}

string Prestamo::toFileString() const
{
  stringstream ss;
  ss << dniUsuario << "|" << isbnLibro << "|" << fechaPrestamo << "|"
     << fechaDevolucion << "|" << (activo ? "1" : "0");
  return ss.str();
}

Prestamo *Prestamo::fromFileString(const string &line)
{
  stringstream ss(line);
  string item;
  string tokens[10];
  int tokenCount = 0;

  while (getline(ss, item, '|') && tokenCount < 10)
  {
    tokens[tokenCount++] = item;
  }

  if (tokenCount >= 5)
  {
    return new Prestamo(tokens[0], tokens[1],
                        stoll(tokens[2]), stoll(tokens[3]),
                        tokens[4] == "1");
  }
  return nullptr;
}

bool Prestamo::operator==(const Prestamo &other) const
{
  return dniUsuario == other.dniUsuario && isbnLibro == other.isbnLibro &&
         fechaPrestamo == other.fechaPrestamo;
}

ostream &operator<<(ostream &os, const Prestamo &prestamo)
{
  prestamo.mostrarInformacion();
  return os;
}
