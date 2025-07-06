#include "../include/MaterialBibliografico.h"
#include <sstream>

using std::string;
using std::stringstream;

MaterialBibliografico::MaterialBibliografico(const string &titulo, const string &autor,
                                             const string &isbn, int anio, int copias)
    : titulo(titulo), autor(autor), isbn(isbn), anio(anio),
      copiasTotales(copias), copiasDisponibles(copias) {}

string MaterialBibliografico::toFileString() const
{
  stringstream ss;
  ss << getTipo() << "|" << titulo << "|" << autor << "|" << isbn << "|"
     << anio << "|" << copiasTotales << "|" << copiasDisponibles;
  return ss.str();
}

bool MaterialBibliografico::prestarCopia()
{
  if (copiasDisponibles > 0)
  {
    copiasDisponibles--;
    return true;
  }
  return false;
}

bool MaterialBibliografico::devolverCopia()
{
  if (copiasDisponibles < copiasTotales)
  {
    copiasDisponibles++;
    return true;
  }
  return false;
}

bool MaterialBibliografico::operator==(const MaterialBibliografico &other) const
{
  return isbn == other.isbn;
}

std::ostream &operator<<(std::ostream &os, const MaterialBibliografico &material)
{
  material.mostrarInformacion();
  return os;
}
