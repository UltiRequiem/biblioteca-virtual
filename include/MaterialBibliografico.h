#ifndef MATERIALBIBLIOGRAFICO_H
#define MATERIALBIBLIOGRAFICO_H

#include <string>
#include <iostream>

using std::string;

class MaterialBibliografico
{
protected:
  string titulo;
  string autor;
  string isbn;
  int anio;
  int copiasTotales;
  int copiasDisponibles;

public:
  MaterialBibliografico(const string &titulo, const string &autor,
                        const string &isbn, int anio, int copias);

  virtual ~MaterialBibliografico() = default;

  virtual void mostrarInformacion() const = 0;
  virtual string getTipo() const = 0;
  virtual string toFileString() const;

  string getTitulo() const { return titulo; }
  string getAutor() const { return autor; }
  string getIsbn() const { return isbn; }
  int getAnio() const { return anio; }
  int getCopiasTotales() const { return copiasTotales; }
  int getCopiasDisponibles() const { return copiasDisponibles; }

  void setTitulo(const string &titulo) { this->titulo = titulo; }
  void setAutor(const string &autor) { this->autor = autor; }
  void setIsbn(const string &isbn) { this->isbn = isbn; }
  void setAnio(int anio) { this->anio = anio; }
  void setCopiasTotales(int copias) { this->copiasTotales = copias; }
  void setCopiasDisponibles(int copias) { this->copiasDisponibles = copias; }

  bool prestarCopia();
  bool devolverCopia();
  bool hayDisponibles() const { return copiasDisponibles > 0; }

  bool operator==(const MaterialBibliografico &other) const;
  friend std::ostream &operator<<(std::ostream &os, const MaterialBibliografico &material);
};

#endif
