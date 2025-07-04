#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include "MaterialBibliografico.h"
#include "Libro.h"
#include "Usuario.h"
#include "Prestamo.h"
#include <string>

using std::string;

class Biblioteca
{
private:
  MaterialBibliografico **materiales;
  Usuario **usuarios;
  Prestamo **prestamos;

  int capacidadMateriales;
  int totalMateriales;
  int capacidadUsuarios;
  int totalUsuarios;
  int capacidadPrestamos;
  int totalPrestamos;

  string archivoMateriales;
  string archivoUsuarios;
  string archivoPrestamos;

  MaterialBibliografico *buscarMaterialPorISBN(const string &isbn);
  Usuario *buscarUsuarioPorDNI(const string &dni);
  Prestamo **buscarPrestamosUsuario(const string &dni, int &cantidad);
  Prestamo **buscarPrestamosActivos(int &cantidad) const;

  void redimensionarMateriales();
  void redimensionarUsuarios();
  void redimensionarPrestamos();

public:
  Biblioteca(const string &archivoMateriales = "data/materiales.txt",
             const string &archivoUsuarios = "data/usuarios.txt",
             const string &archivoPrestamos = "data/prestamos.txt");

  ~Biblioteca();

  bool agregarMaterial(MaterialBibliografico *material);
  bool eliminarMaterial(const string &isbn);
  void mostrarTodosMateriales() const;
  void mostrarMaterialesDisponibles() const;
  MaterialBibliografico **buscarPorTitulo(const string &titulo, int &cantidad) const;
  MaterialBibliografico **buscarPorAutor(const string &autor, int &cantidad) const;

  bool agregarUsuario(Usuario *usuario);
  bool eliminarUsuario(const string &dni);
  void mostrarTodosUsuarios() const;

  bool prestarLibro(const string &dni, const string &isbn);
  bool devolverLibro(const string &dni, const string &isbn);
  void mostrarPrestamosActivos() const;
  void mostrarHistorialPrestamos() const;
  void mostrarPrestamosUsuario(const string &dni) const;

  void generarInformePrestamos() const;
  void mostrarMaterialesPopulares() const;
  void mostrarPrestamosVencidos() const;

  bool cargarDatos();
  bool guardarDatos() const;
  bool cargarMateriales();
  bool cargarUsuarios();
  bool cargarPrestamos();
  bool guardarMateriales() const;
  bool guardarUsuarios() const;
  bool guardarPrestamos() const;

  int getTotalMateriales() const { return totalMateriales; }
  int getTotalUsuarios() const { return totalUsuarios; }
  int getTotalPrestamosActivos() const;

  bool validarISBN(const string &isbn) const;
  bool validarDNI(const string &dni) const;
  void limpiarPrestamosVencidos();
};

#endif
