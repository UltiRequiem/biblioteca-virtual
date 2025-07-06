#ifndef LIBRO_H
#define LIBRO_H

#include "MaterialBibliografico.h"

using std::string;

class Libro : public MaterialBibliografico
{
private:
  string genero;
  int numeroPaginas;

public:
  Libro(const string &titulo, const string &autor, const string &isbn,
        int anio, int copias, const string &genero = "", int paginas = 0);

  void mostrarInformacion() const override;
  string getTipo() const override { return "LIBRO"; }
  string toFileString() const override;

  string getGenero() const { return genero; }
  int getNumeroPaginas() const { return numeroPaginas; }

  void setGenero(const string &genero) { this->genero = genero; }
  void setNumeroPaginas(int paginas) { this->numeroPaginas = paginas; }

  static Libro *fromFileString(const string &line);
};

#endif
