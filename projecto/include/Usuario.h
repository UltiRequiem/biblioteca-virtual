#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>

using std::string;

class Usuario
{
private:
  string nombre;
  string dni;
  string correoElectronico;
  string *librosPresrados;
  int capacidadPrestamos;
  int totalPrestamos;
  int maxPrestamos;

public:
  Usuario(const string &nombre, const string &dni,
          const string &correo, int maxPrestamos = 5);

  ~Usuario();

  string getNombre() const { return nombre; }
  string getDni() const { return dni; }
  string getCorreo() const { return correoElectronico; }
  int getMaxPrestamos() const { return maxPrestamos; }
  int getPrestamosActuales() const { return totalPrestamos; }
  string *getLibrosPrestados() const { return librosPresrados; }

  void setNombre(const string &nombre) { this->nombre = nombre; }
  void setCorreo(const string &correo) { this->correoElectronico = correo; }
  void setMaxPrestamos(int max) { this->maxPrestamos = max; }

  bool puedePrestar() const;
  bool prestarLibro(const string &isbn);
  bool devolverLibro(const string &isbn);
  bool tieneLibro(const string &isbn) const;

  void mostrarInformacion() const;
  void mostrarPrestamos() const;

  string toFileString() const;
  static Usuario *fromFileString(const string &line);

  bool operator==(const Usuario &other) const;

  // igual que el el otro archivo, usaremos friend para
  // evitar getters repetitivos
  friend std::ostream &operator<<(std::ostream &os, const Usuario &usuario);

private:
  void redimensionarPrestamos();
};

#endif
