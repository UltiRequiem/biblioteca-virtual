#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <string>
#include <ctime>
#include <iostream>

using std::ostream;
using std::string;
using std::time_t;
// time_t nos permite representar fechas y tiempo
// de manera sencilla, es la cantidad de segundos
// desde el unix epoch (1/1/1970 00:00:00 UTC).

class Prestamo
{
private:
  string dniUsuario;
  string isbnLibro;
  time_t fechaPrestamo;
  time_t fechaDevolucion;
  bool activo;

public:
  Prestamo(const string &dniUsuario, const string &isbnLibro);

  Prestamo(const string &dniUsuario, const string &isbnLibro,
           time_t fechaPrestamo, time_t fechaDevolucion, bool activo);

  ~Prestamo() = default;

  string getDniUsuario() const { return dniUsuario; }
  string getIsbnLibro() const { return isbnLibro; }
  time_t getFechaPrestamo() const { return fechaPrestamo; }
  time_t getFechaDevolucion() const { return fechaDevolucion; }
  bool isActivo() const { return activo; }

  void marcarDevuelto();
  int diasPrestado() const;
  bool estaVencido(int diasLimite = 30) const;

  void mostrarInformacion() const;
  string fechaToString(std::time_t fecha) const;

  string toFileString() const;
  static Prestamo *fromFileString(const std::string &line);

  bool operator==(const Prestamo &other) const;

  // Usando friend para evitar getters repetitivos
  friend ostream &operator<<(ostream &os, const Prestamo &prestamo);
};

#endif