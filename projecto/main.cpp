#include <iostream>
#include <string>
#include "include/Biblioteca.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void mostrarMenu()
{
  cout << "=== SISTEMA DE BIBLIOTECA ===" << endl;
  cout << "1. Agregar material" << endl;
  cout << "2. Buscar material" << endl;
  cout << "3. Prestar material" << endl;
  cout << "4. Devolver material" << endl;
  cout << "5. Mostrar todos los materiales" << endl;
  cout << "6. Agregar usuario" << endl;
  cout << "7. Mostrar prestamos de usuario" << endl;
  cout << "8. Mostrar todos los usuarios" << endl;
  cout << "9. Salir" << endl;
  cout << "Seleccione una opcion: ";
}

int main()
{
  Biblioteca biblioteca;
  int opcion;

  do
  {
    mostrarMenu();
    cin >> opcion;
    cin.ignore();

    switch (opcion)
    {
    case 1:
    {
      string titulo, autor, isbn, genero;
      int anio, copias, paginas;
      cout << "Ingrese titulo: ";
      getline(cin, titulo);
      cout << "Ingrese autor: ";
      getline(cin, autor);
      cout << "Ingrese ISBN: ";
      getline(cin, isbn);
      cout << "Ingrese año: ";
      cin >> anio;
      cout << "Ingrese numero de copias: ";
      cin >> copias;
      cin.ignore();
      cout << "Ingrese género: ";
      getline(cin, genero);
      cout << "Ingrese número de páginas: ";
      cin >> paginas;
      cin.ignore();

      Libro *nuevoLibro = new Libro(titulo, autor, isbn, anio, copias, genero, paginas);
      biblioteca.agregarMaterial(nuevoLibro);
      cout << "Libro agregado exitosamente." << endl;
      break;
    }
    case 2:
    {
      string titulo;
      cout << "Ingrese titulo a buscar: ";
      getline(cin, titulo);

      int cantidad = 0;
      MaterialBibliografico **resultados = biblioteca.buscarPorTitulo(titulo, cantidad);
      if (cantidad > 0)
      {
        cout << "Materiales encontrados:" << endl;
        for (int i = 0; i < cantidad; i++)
        {
          resultados[i]->mostrarInformacion();
          cout << "---" << endl;
        }
      }
      else
      {
        cout << "Material no encontrado." << endl;
      }
      break;
    }
    case 3:
    {
      string isbn, dni;
      cout << "Ingrese ISBN del material: ";
      getline(cin, isbn);
      cout << "Ingrese DNI del usuario: ";
      getline(cin, dni);

      if (biblioteca.prestarLibro(dni, isbn))
      {
        cout << "Material prestado exitosamente." << endl;
      }
      else
      {
        cout << "No se pudo prestar el material." << endl;
      }
      break;
    }
    case 4:
    {
      string isbn, dni;
      cout << "Ingrese ISBN del material: ";
      getline(cin, isbn);
      cout << "Ingrese DNI del usuario: ";
      getline(cin, dni);

      if (biblioteca.devolverLibro(dni, isbn))
      {
        cout << "Material devuelto exitosamente." << endl;
      }
      else
      {
        cout << "No se pudo devolver el material." << endl;
      }
      break;
    }
    case 5:
    {
      biblioteca.mostrarTodosMateriales();
      break;
    }
    case 6:
    {
      string nombre, dni, correo;
      cout << "Ingrese nombre del usuario: ";
      getline(cin, nombre);
      cout << "Ingrese DNI del usuario: ";
      getline(cin, dni);
      cout << "Ingrese correo del usuario: ";
      getline(cin, correo);

      Usuario *nuevoUsuario = new Usuario(nombre, dni, correo);
      biblioteca.agregarUsuario(nuevoUsuario);
      cout << "Usuario agregado exitosamente." << endl;
      break;
    }
    case 7:
    {
      string dni;
      cout << "Ingrese DNI del usuario: ";
      getline(cin, dni);

      biblioteca.mostrarPrestamosUsuario(dni);
      break;
    }
    case 8:
    {
      biblioteca.mostrarTodosUsuarios();
      break;
    }
    case 9:
    {
      cout << "Saliendo del sistema..." << endl;
      break;
    }
    default:
    {
      cout << "Opcion invalida. Intente de nuevo." << endl;
      break;
    }
    }

    if (opcion != 9)
    {
      cout << "Presione Enter para continuar...";
      cin.get();
    }

  } while (opcion != 9);

  return 0;
}
