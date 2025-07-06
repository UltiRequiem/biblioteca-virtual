#include "../include/Usuario.h"
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;
using std::stringstream;

Usuario::Usuario(const string &nombre, const string &dni,
                 const string &correo, int maxPrestamos)
    : nombre(nombre), dni(dni), correoElectronico(correo), maxPrestamos(maxPrestamos)
{
  capacidadPrestamos = 5;
  totalPrestamos = 0;
  librosPresrados = new string[capacidadPrestamos];
}

Usuario::~Usuario()
{
  delete[] librosPresrados;
}

void Usuario::redimensionarPrestamos()
{
  int nuevaCapacidad = capacidadPrestamos * 2;
  string *nuevoArray = new string[nuevaCapacidad];

  for (int i = 0; i < totalPrestamos; i++)
  {
    nuevoArray[i] = librosPresrados[i];
  }

  delete[] librosPresrados;
  librosPresrados = nuevoArray;
  capacidadPrestamos = nuevaCapacidad;
}

bool Usuario::puedePrestar() const
{
  return totalPrestamos < maxPrestamos;
}

bool Usuario::prestarLibro(const string &isbn)
{
  if (!puedePrestar() || tieneLibro(isbn))
  {
    return false;
  }

  if (totalPrestamos >= capacidadPrestamos)
  {
    redimensionarPrestamos();
  }

  librosPresrados[totalPrestamos++] = isbn;
  return true;
}

bool Usuario::devolverLibro(const string &isbn)
{
  for (int i = 0; i < totalPrestamos; i++)
  {
    if (librosPresrados[i] == isbn)
    {
      for (int j = i; j < totalPrestamos - 1; j++)
      {
        librosPresrados[j] = librosPresrados[j + 1];
      }
      totalPrestamos--;
      return true;
    }
  }
  return false;
}

bool Usuario::tieneLibro(const string &isbn) const
{
  for (int i = 0; i < totalPrestamos; i++)
  {
    if (librosPresrados[i] == isbn)
    {
      return true;
    }
  }
  return false;
}

void Usuario::mostrarInformacion() const
{
  cout << "=== USUARIO ===" << endl;
  cout << "Nombre: " << nombre << endl;
  cout << "DNI: " << dni << endl;
  cout << "Correo: " << correoElectronico << endl;
  cout << "Préstamos actuales: " << totalPrestamos << "/" << maxPrestamos << endl;
  cout << "===============" << endl;
}

void Usuario::mostrarPrestamos() const
{
  cout << "Libros prestados a " << nombre << ":" << endl;
  if (totalPrestamos == 0)
  {
    cout << "  No tiene libros prestados." << endl;
  }
  else
  {
    for (int i = 0; i < totalPrestamos; i++)
    {
      cout << "  - ISBN: " << librosPresrados[i] << endl;
    }
  }
}

string Usuario::toFileString() const
{
  stringstream ss;
  ss << nombre << "|" << dni << "|" << correoElectronico << "|" << maxPrestamos << "|";

  for (int i = 0; i < totalPrestamos; i++)
  {
    if (i > 0)
      ss << ",";
    ss << librosPresrados[i];
  }

  return ss.str();
}

Usuario *Usuario::fromFileString(const string &line)
{
  stringstream ss(line);
  string item;
  string tokens[5];
  int tokenCount = 0;

  while (std::getline(ss, item, '|') && tokenCount < 5)
  {
    tokens[tokenCount++] = item;
  }

  if (tokenCount >= 4)
  {
    Usuario *usuario = new Usuario(tokens[0], tokens[1], tokens[2], std::stoi(tokens[3]));

    if (tokenCount > 4 && !tokens[4].empty())
    {
      stringstream prestamos(tokens[4]);
      string isbn;
      while (std::getline(prestamos, isbn, ','))
      {
        usuario->prestarLibro(isbn);
      }
    }

    return usuario;
  }
  return nullptr;
}

bool Usuario::operator==(const Usuario &other) const
{
  return dni == other.dni;
}

std::ostream &operator<<(std::ostream &os, const Usuario &usuario)
{
  usuario.mostrarInformacion();
  return os;
}
