# Mi biblioteca

Projecto Final para el curso de Fundamentos de Programación con C++.

## Diagramas

Diagramas utiles para explicar

### Clases

![](./image2.png)

### Flujo en archivos

![](./image.png)

### Persistencia de datos

![](./image3.png)

### Operaciones

![](image-1.png)

## Como ejecutar

1. hacemos make ( compila todo)

```sh
make
```

Otra alternativa:

```sh
make run
```

Este comando se asegura que tangmos los materiales para persistencia:

```sh
make setup-data
```

Es como un seeder en una base de datos con datos de ejemplo.

Esto compila y ejecuta el programa.

El delegado dijo que espere a que actualize el repositorio y que me saldria las
instruciones del repositorio, pero ya pasaron algunos dis y todavia no sale.
cppcheck lo podemos instalar en mac usando brew:

Voy a copiar las instruciones que enviaron al grupo y desarrollarlo aqui para ir
avanzando.

## Estructura del Proyecto

### 📁 Directorios

```
projecto/
├── include/          # Headers (.h) - Declaraciones de clases
├── src/             # Implementaciones (.cpp) - Lógica del programa
├── data/            # Archivos de datos - Persistencia
├── obj/             # Archivos objeto (.o) - Compilación incremental
└── main.cpp         # Programa principal
```

### Headers (include/)

| Header                      | Clase               | Función                                |
| --------------------------- | ------------------- | -------------------------------------- |
| **MaterialBibliografico.h** | Base abstracta      | Define interfaz común para materiales  |
| **Libro.h**                 | Herencia            | Implementa libros con género y páginas |
| **Usuario.h**               | Gestión usuarios    | Maneja datos personales y límites      |
| **Prestamo.h**              | Control préstamos   | Fechas, estados y validaciones         |
| **Biblioteca.h**            | Controlador central | Coordina todas las operaciones         |

### Implementaciones (src/)

| Archivo CPP                   | Contiene                                           |
| ----------------------------- | -------------------------------------------------- |
| **MaterialBibliografico.cpp** | Métodos base, operadores, serialización            |
| **Libro.cpp**                 | Lógica específica de libros, validaciones ISBN     |
| **Usuario.cpp**               | Gestión de préstamos por usuario, validaciones DNI |
| **Prestamo.cpp**              | Cálculo de fechas, préstamos vencidos              |
| **Biblioteca.cpp**            | CRUD completo, carga/guardado de archivos          |

### Datos (data/)

| Archivo            | Formato                                                                 | Contenido                    |
| ------------------ | ----------------------------------------------------------------------- | ---------------------------- |
| **materiales.txt** | `LIBRO\|titulo\|autor\|isbn\|año\|copias\|disponibles\|genero\|paginas` | Inventario de libros         |
| **usuarios.txt**   | `nombre\|dni\|email\|limite\|`                                          | Base de usuarios registrados |
| **prestamos.txt**  | `dni\|isbn\|fechaPrestamo\|fechaDevolucion\|activo`                     | Historial de préstamos       |

| Archivo        | Uso                                                    |
| -------------- | ------------------------------------------------------ |
| **obj/\*.o**   | Archivos objeto compilados (generados automáticamente) |
| **.gitignore** | Excluye obj/ y ejecutables del control de versiones    |

## Notas

### uso de headers guards

En nuestros archivos .h usamos header guars para evitar que se reincluyan varias veces.
Lo caul causa errores de compilacion

### Calidad de codigo

Usamos cppcheck para analisis estatico de nuestro codigo.

cppcheck lo podemos instalar en mac usando brew:

```sh
brew install cppcheck
```
