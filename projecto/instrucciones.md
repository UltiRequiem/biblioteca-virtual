# Sistema de Gestión de Biblioteca Digital

## Objetivo

Desarrollar un **Sistema de Gestión de Biblioteca Digital** que permita registrar libros, realizar préstamos, devolver libros, y mostrar el estado actual de la biblioteca. Este sistema se debe implementar en **C++**, usando buenas prácticas de **programación orientada a objetos**, **archivos** para almacenamiento persistente, **asignación dinámica** de memoria, y una **estructura modular** con múltiples archivos ".cpp" y ".h" . Se debe automatizar la compilación usando un Makefile.

## Funcionalidades mínimas requeridas

Tu programa debe permitir:

- Registrar libros nuevos (título, autor, ISBN, año, número de copias).
- Registrar usuarios (nombre, ID (DNI del usuario), correo electrónico).
- Prestar libros a usuarios (debe verificar disponibilidad).
- Devolver libros.
- Consultar listado de libros disponibles y prestados.
  Guardar y cargar datos desde archivos (`libros.txt`, `usuarios.txt', etc.).

## Requisitos

- Uso de **clases** para representar `Libro`, `Usuario`, `Prestamo`, y `Biblioteca`.
- Al menos una clase debe utilizar **asignación dinámica de memoria** (por ejemplo, almacenar usuarios o libros en un arreglo dinámico).
- Dividir el código en **múltiples archivos** (`main.cpp`, `Libro.h/cpp`, `Usuario.h/cpp`, etc.).
- Automatizar el proceso de compilación con un **Makefile**.
- Leer y escribir datos en **archivos de texto** para simular persistencia de información.

## Adicionales

- Generar un pequeño informe de préstamos por usuario.
- Búsqueda de libros por título o autor.
- Limitar la cantidad de préstamos por usuario.
- Implementar herencia y polimorfismo, por ejemplo: Crear una clase base MaterialBibliografico con atributos y métodos comunes.
  Derivar clases como Libro, Revista, o Tesis que hereden de MaterialBibliografico.
  Usar punteros o referencias a la clase base para manipular diferentes tipos de materiales de forma polimórfica (con métodos virtuales como mostrarInformacion()).
- Interfaz en consola con menús ordenados.
- Validar entradas del usuario (evitar errores al ingresar datos).

## Entregables a través de GitHub

1. Código fuente dividido en múltiples archivos C++.
2. Archivos.txt de ejemplo (`libros.txt`, `usuarios.txt').
3. Archivo Makefile` funcional que compile todo el proyecto.
4. Documento PDF o README.md que explique:

- Estructura del proyecto.
- Cómo compilar y ejecutar.
  Qué funcionalidades fueron implementadas.

## Fechas importantes

- Fecha de entrega: **domingo 06 de julio, 12h**
- Presentación oral (opcional / como parte del examen final):

## Recomendaciones

- ¡Organiza bien tu código y agrega comentarios relevantes!
- Empieza por lo más simple: leer libros desde archivo, mostrar, y luego construir las clases.
- Divide el trabajo y el avance en commits relevantes y periódicos

## Nota

- Considerar tipos de variables de manera realista y lo más genérica posible. Para el formato del ISBN, puede consultarse
  la siguiente fuente:
  https://es.wikipedia.org/wiki/ISBN
- Los nombres de las funciones y variables deben ser claros y descriptivos.
- Seguir las buenas prácticas de programación orientada a objetos vistas en clase.
