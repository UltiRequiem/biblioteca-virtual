#include "../include/Libro.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

Libro::Libro(const string &titulo, const string &autor, const string &isbn,
             int anio, int copias, const string &genero, int paginas)
    : MaterialBibliografico(titulo, autor, isbn, anio, copias),
      genero(genero), numeroPaginas(paginas) {}

void Libro::mostrarInformacion() const
{
  cout << "=== LIBRO ===" << endl;
  cout << "Título: " << titulo << endl;
  cout << "Autor: " << autor << endl;
  cout << "ISBN: " << isbn << endl;
  cout << "Año: " << anio << endl;
  cout << "Género: " << genero << endl;
  cout << "Páginas: " << numeroPaginas << endl;
  cout << "Copias totales: " << copiasTotales << endl;
  cout << "Copias disponibles: " << copiasDisponibles << endl;
  cout << "=============" << endl;
}

string Libro::toFileString() const
{
  stringstream ss;
  ss << getTipo() << "|" << titulo << "|" << autor << "|" << isbn << "|"
     << anio << "|" << copiasTotales << "|" << copiasDisponibles << "|"
     << genero << "|" << numeroPaginas;
  return ss.str();
}

Libro *Libro::fromFileString(const string &line)
{
  stringstream ss(line);
  string item;
  string tokens[10];
  int tokenCount = 0;

  while (getline(ss, item, '|') && tokenCount < 10)
  {
    tokens[tokenCount++] = item;
  }

  if (tokenCount >= 7)
  {
    string genero = tokenCount > 7 ? tokens[7] : "";
    int paginas = tokenCount > 8 ? stoi(tokens[8]) : 0;

    return new Libro(tokens[1], tokens[2], tokens[3],
                     stoi(tokens[4]), stoi(tokens[5]),
                     genero, paginas);
  }
  return nullptr;
}
