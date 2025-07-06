#include "../include/Biblioteca.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::stringstream;

Biblioteca::Biblioteca(const string &archivoMateriales,
                       const string &archivoUsuarios,
                       const string &archivoPrestamos)
    : archivoMateriales(archivoMateriales), archivoUsuarios(archivoUsuarios),
      archivoPrestamos(archivoPrestamos)
{

  capacidadMateriales = 10;
  totalMateriales = 0;
  materiales = new MaterialBibliografico *[capacidadMateriales];

  capacidadUsuarios = 10;
  totalUsuarios = 0;
  usuarios = new Usuario *[capacidadUsuarios];

  capacidadPrestamos = 10;
  totalPrestamos = 0;
  prestamos = new Prestamo *[capacidadPrestamos];

  cargarDatos();
}

Biblioteca::~Biblioteca()
{
  for (int i = 0; i < totalMateriales; i++)
  {
    delete materiales[i];
  }
  delete[] materiales;

  for (int i = 0; i < totalUsuarios; i++)
  {
    delete usuarios[i];
  }
  delete[] usuarios;

  for (int i = 0; i < totalPrestamos; i++)
  {
    delete prestamos[i];
  }
  delete[] prestamos;
}

void Biblioteca::redimensionarMateriales()
{
  int nuevaCapacidad = capacidadMateriales * 2;
  MaterialBibliografico **nuevoArray = new MaterialBibliografico *[nuevaCapacidad];

  for (int i = 0; i < totalMateriales; i++)
  {
    nuevoArray[i] = materiales[i];
  }

  delete[] materiales;
  materiales = nuevoArray;
  capacidadMateriales = nuevaCapacidad;
}

void Biblioteca::redimensionarUsuarios()
{
  int nuevaCapacidad = capacidadUsuarios * 2;
  Usuario **nuevoArray = new Usuario *[nuevaCapacidad];

  for (int i = 0; i < totalUsuarios; i++)
  {
    nuevoArray[i] = usuarios[i];
  }

  delete[] usuarios;
  usuarios = nuevoArray;
  capacidadUsuarios = nuevaCapacidad;
}

void Biblioteca::redimensionarPrestamos()
{
  int nuevaCapacidad = capacidadPrestamos * 2;
  Prestamo **nuevoArray = new Prestamo *[nuevaCapacidad];

  for (int i = 0; i < totalPrestamos; i++)
  {
    nuevoArray[i] = prestamos[i];
  }

  delete[] prestamos;
  prestamos = nuevoArray;
  capacidadPrestamos = nuevaCapacidad;
}

MaterialBibliografico *Biblioteca::buscarMaterialPorISBN(const string &isbn)
{
  for (int i = 0; i < totalMateriales; i++)
  {
    if (materiales[i]->getIsbn() == isbn)
    {
      return materiales[i];
    }
  }
  return nullptr;
}

Usuario *Biblioteca::buscarUsuarioPorDNI(const string &dni)
{
  for (int i = 0; i < totalUsuarios; i++)
  {
    if (usuarios[i]->getDni() == dni)
    {
      return usuarios[i];
    }
  }
  return nullptr;
}

Prestamo **Biblioteca::buscarPrestamosUsuario(const string &dni, int &cantidad)
{
  cantidad = 0;
  Prestamo **resultado = new Prestamo *[totalPrestamos];

  for (int i = 0; i < totalPrestamos; i++)
  {
    if (prestamos[i]->getDniUsuario() == dni)
    {
      resultado[cantidad++] = prestamos[i];
    }
  }

  return resultado;
}

Prestamo **Biblioteca::buscarPrestamosActivos(int &cantidad) const
{
  cantidad = 0;
  Prestamo **resultado = new Prestamo *[totalPrestamos];

  for (int i = 0; i < totalPrestamos; i++)
  {
    if (prestamos[i]->isActivo())
    {
      resultado[cantidad++] = prestamos[i];
    }
  }

  return resultado;
}

bool Biblioteca::agregarMaterial(MaterialBibliografico *material)
{
  if (!material || buscarMaterialPorISBN(material->getIsbn()) != nullptr)
  {
    return false;
  }

  if (totalMateriales >= capacidadMateriales)
  {
    redimensionarMateriales();
  }

  materiales[totalMateriales++] = material;
  return true;
}

bool Biblioteca::eliminarMaterial(const string &isbn)
{
  for (int i = 0; i < totalMateriales; i++)
  {
    if (materiales[i]->getIsbn() == isbn)
    {
      delete materiales[i];

      for (int j = i; j < totalMateriales - 1; j++)
      {
        materiales[j] = materiales[j + 1];
      }
      totalMateriales--;
      return true;
    }
  }
  return false;
}

void Biblioteca::mostrarTodosMateriales() const
{
  cout << "\n=== TODOS LOS MATERIALES ===" << endl;
  if (totalMateriales == 0)
  {
    cout << "No hay materiales registrados." << endl;
    return;
  }

  for (int i = 0; i < totalMateriales; i++)
  {
    materiales[i]->mostrarInformacion();
    cout << endl;
  }
}

void Biblioteca::mostrarMaterialesDisponibles() const
{
  cout << "\n=== MATERIALES DISPONIBLES ===" << endl;
  bool hayDisponibles = false;

  for (int i = 0; i < totalMateriales; i++)
  {
    if (materiales[i]->hayDisponibles())
    {
      materiales[i]->mostrarInformacion();
      cout << endl;
      hayDisponibles = true;
    }
  }

  if (!hayDisponibles)
  {
    cout << "No hay materiales disponibles actualmente." << endl;
  }
}

MaterialBibliografico **Biblioteca::buscarPorTitulo(const string &titulo, int &cantidad) const
{
  cantidad = 0;
  MaterialBibliografico **resultado = new MaterialBibliografico *[totalMateriales];

  for (int i = 0; i < totalMateriales; i++)
  {
    string materialTitulo = materiales[i]->getTitulo();

    if (materialTitulo.find(titulo) != string::npos)
    {
      resultado[cantidad++] = materiales[i];
    }
  }

  return resultado;
}

MaterialBibliografico **Biblioteca::buscarPorAutor(const string &autor, int &cantidad) const
{
  cantidad = 0;
  MaterialBibliografico **resultado = new MaterialBibliografico *[totalMateriales];

  for (int i = 0; i < totalMateriales; i++)
  {
    string materialAutor = materiales[i]->getAutor();

    if (materialAutor.find(autor) != string::npos)
    {
      resultado[cantidad++] = materiales[i];
    }
  }

  return resultado;
}

bool Biblioteca::agregarUsuario(Usuario *usuario)
{
  if (!usuario || buscarUsuarioPorDNI(usuario->getDni()) != nullptr)
  {
    return false;
  }

  if (totalUsuarios >= capacidadUsuarios)
  {
    redimensionarUsuarios();
  }

  usuarios[totalUsuarios++] = usuario;
  return true;
}

bool Biblioteca::eliminarUsuario(const string &dni)
{
  int cantidad;
  Prestamo **prestamosUsuario = buscarPrestamosUsuario(dni, cantidad);

  for (int i = 0; i < cantidad; i++)
  {
    if (prestamosUsuario[i]->isActivo())
    {
      cout << "No se puede eliminar el usuario. Tiene préstamos activos." << endl;
      delete[] prestamosUsuario;
      return false;
    }
  }
  delete[] prestamosUsuario;

  for (int i = 0; i < totalUsuarios; i++)
  {
    if (usuarios[i]->getDni() == dni)
    {
      delete usuarios[i];

      for (int j = i; j < totalUsuarios - 1; j++)
      {
        usuarios[j] = usuarios[j + 1];
      }
      totalUsuarios--;
      return true;
    }
  }
  return false;
}

void Biblioteca::mostrarTodosUsuarios() const
{
  cout << "\n=== TODOS LOS USUARIOS ===" << endl;
  if (totalUsuarios == 0)
  {
    cout << "No hay usuarios registrados." << endl;
    return;
  }

  for (int i = 0; i < totalUsuarios; i++)
  {
    usuarios[i]->mostrarInformacion();
    cout << endl;
  }
}

bool Biblioteca::prestarLibro(const string &dni, const string &isbn)
{
  Usuario *usuario = buscarUsuarioPorDNI(dni);
  MaterialBibliografico *material = buscarMaterialPorISBN(isbn);

  if (!usuario)
  {
    cout << "Usuario no encontrado." << endl;
    return false;
  }

  if (!material)
  {
    cout << "Material no encontrado." << endl;
    return false;
  }

  if (!usuario->puedePrestar())
  {
    cout << "El usuario ha alcanzado el límite de préstamos." << endl;
    return false;
  }

  if (!material->hayDisponibles())
  {
    cout << "No hay copias disponibles del material." << endl;
    return false;
  }

  if (usuario->tieneLibro(isbn))
  {
    cout << "El usuario ya tiene prestado este material." << endl;
    return false;
  }

  if (material->prestarCopia() && usuario->prestarLibro(isbn))
  {
    if (totalPrestamos >= capacidadPrestamos)
    {
      redimensionarPrestamos();
    }

    prestamos[totalPrestamos++] = new Prestamo(dni, isbn);
    cout << "Préstamo realizado exitosamente." << endl;
    return true;
  }

  return false;
}

bool Biblioteca::devolverLibro(const string &dni, const string &isbn)
{
  Usuario *usuario = buscarUsuarioPorDNI(dni);
  MaterialBibliografico *material = buscarMaterialPorISBN(isbn);

  if (!usuario || !material)
  {
    cout << "Usuario o material no encontrado." << endl;
    return false;
  }

  if (!usuario->tieneLibro(isbn))
  {
    cout << "El usuario no tiene prestado este material." << endl;
    return false;
  }

  for (int i = 0; i < totalPrestamos; i++)
  {
    if (prestamos[i]->getDniUsuario() == dni &&
        prestamos[i]->getIsbnLibro() == isbn &&
        prestamos[i]->isActivo())
    {

      prestamos[i]->marcarDevuelto();
      usuario->devolverLibro(isbn);
      material->devolverCopia();

      cout << "Devolución realizada exitosamente." << endl;
      return true;
    }
  }

  return false;
}

void Biblioteca::mostrarPrestamosActivos() const
{
  cout << "\n=== PRÉSTAMOS ACTIVOS ===" << endl;
  int cantidad;
  Prestamo **prestamosActivos = buscarPrestamosActivos(cantidad);

  if (cantidad == 0)
  {
    cout << "No hay préstamos activos." << endl;
  }
  else
  {
    for (int i = 0; i < cantidad; i++)
    {
      prestamosActivos[i]->mostrarInformacion();
      cout << endl;
    }
  }

  delete[] prestamosActivos;
}

void Biblioteca::mostrarPrestamosUsuario(const string &dni) const
{
  Usuario *usuario = const_cast<Biblioteca *>(this)->buscarUsuarioPorDNI(dni);
  if (!usuario)
  {
    cout << "Usuario no encontrado." << endl;
    return;
  }

  cout << "\n=== PRÉSTAMOS DE " << usuario->getNombre() << " ===" << endl;

  int cantidad;
  Prestamo **prestamosUsuario = const_cast<Biblioteca *>(this)->buscarPrestamosUsuario(dni, cantidad);

  if (cantidad == 0)
  {
    cout << "Este usuario no tiene préstamos registrados." << endl;
  }
  else
  {
    for (int i = 0; i < cantidad; i++)
    {
      prestamosUsuario[i]->mostrarInformacion();
      cout << endl;
    }
  }

  delete[] prestamosUsuario;
}

bool Biblioteca::validarISBN(const string &isbn) const
{
  if (isbn.length() != 10 && isbn.length() != 13)
  {
    return false;
  }

  for (char c : isbn)
  {
    if (!std::isdigit(c) && c != 'X' && c != 'x')
    {
      return false;
    }
  }

  return true;
}

bool Biblioteca::validarDNI(const string &dni) const
{
  if (dni.length() != 8)
  {
    return false;
  }

  for (char c : dni)
  {
    if (!std::isdigit(c))
    {
      return false;
    }
  }

  return true;
}

bool Biblioteca::cargarDatos()
{
  bool success = true;
  success &= cargarMateriales();
  success &= cargarUsuarios();
  success &= cargarPrestamos();
  return success;
}

bool Biblioteca::guardarDatos() const
{
  bool success = true;
  success &= guardarMateriales();
  success &= guardarUsuarios();
  success &= guardarPrestamos();
  return success;
}

int Biblioteca::getTotalPrestamosActivos() const
{
  int cantidad;
  Prestamo **prestamosActivos = buscarPrestamosActivos(cantidad);
  delete[] prestamosActivos;
  return cantidad;
}

bool Biblioteca::cargarMateriales()
{
  ifstream archivo(archivoMateriales);
  if (!archivo.is_open())
  {
    cout << "No se pudo abrir el archivo de materiales: " << archivoMateriales << endl;
    return false;
  }

  string linea;
  while (std::getline(archivo, linea))
  {
    if (linea.empty())
      continue;

    if (linea.find("LIBRO") == 0)
    {
      Libro *libro = Libro::fromFileString(linea);
      if (libro)
      {
        agregarMaterial(libro);
      }
    }
  }

  archivo.close();
  return true;
}

bool Biblioteca::guardarMateriales() const
{
  ofstream archivo(archivoMateriales);
  if (!archivo.is_open())
  {
    return false;
  }

  for (int i = 0; i < totalMateriales; i++)
  {
    archivo << materiales[i]->toFileString() << endl;
  }

  archivo.close();
  return true;
}

bool Biblioteca::cargarUsuarios()
{
  ifstream archivo(archivoUsuarios);
  if (!archivo.is_open())
  {
    cout << "No se pudo abrir el archivo de usuarios: " << archivoUsuarios << endl;
    return false;
  }

  string linea;
  while (std::getline(archivo, linea))
  {
    if (linea.empty())
      continue;

    Usuario *usuario = Usuario::fromFileString(linea);
    if (usuario)
    {
      agregarUsuario(usuario);
    }
  }

  archivo.close();
  return true;
}

bool Biblioteca::guardarUsuarios() const
{
  ofstream archivo(archivoUsuarios);
  if (!archivo.is_open())
  {
    return false;
  }

  for (int i = 0; i < totalUsuarios; i++)
  {
    archivo << usuarios[i]->toFileString() << endl;
  }

  archivo.close();
  return true;
}

bool Biblioteca::cargarPrestamos()
{
  ifstream archivo(archivoPrestamos);
  if (!archivo.is_open())
  {
    cout << "No se pudo abrir el archivo de préstamos: " << archivoPrestamos << endl;
    return false;
  }

  string linea;
  while (std::getline(archivo, linea))
  {
    if (linea.empty())
      continue;

    Prestamo *prestamo = Prestamo::fromFileString(linea);
    if (prestamo)
    {
      if (totalPrestamos >= capacidadPrestamos)
      {
        redimensionarPrestamos();
      }
      prestamos[totalPrestamos++] = prestamo;
    }
  }

  archivo.close();
  return true;
}

bool Biblioteca::guardarPrestamos() const
{
  ofstream archivo(archivoPrestamos);
  if (!archivo.is_open())
  {
    return false;
  }

  for (int i = 0; i < totalPrestamos; i++)
  {
    archivo << prestamos[i]->toFileString() << endl;
  }

  archivo.close();
  return true;
}

void Biblioteca::mostrarHistorialPrestamos() const
{
  cout << "\n=== HISTORIAL DE PRÉSTAMOS ===" << endl;
  if (totalPrestamos == 0)
  {
    cout << "No hay préstamos registrados." << endl;
    return;
  }

  for (int i = 0; i < totalPrestamos; i++)
  {
    prestamos[i]->mostrarInformacion();
    cout << endl;
  }
}

void Biblioteca::generarInformePrestamos() const
{
  cout << "\n=== INFORME DE PRÉSTAMOS ===" << endl;
  cout << "Total de materiales: " << totalMateriales << endl;
  cout << "Total de usuarios: " << totalUsuarios << endl;
  cout << "Total de préstamos: " << totalPrestamos << endl;
  cout << "Préstamos activos: " << getTotalPrestamosActivos() << endl;
}

void Biblioteca::mostrarMaterialesPopulares() const
{
  cout << "\n=== MATERIALES POPULARES ===" << endl;
}

void Biblioteca::mostrarPrestamosVencidos() const
{
  cout << "\n=== PRÉSTAMOS VENCIDOS ===" << endl;
}

void Biblioteca::limpiarPrestamosVencidos()
{
}
