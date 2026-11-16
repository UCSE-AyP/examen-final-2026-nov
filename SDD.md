# Software Design Document (SDD) — Examen Final Regular (Noviembre 2026)
**Asignatura:** Algoritmos y Programación (Módulo 4: Arreglos de Estructuras - AoS, ABM, Ordenamiento, Filtrado y Estadística)  
**Instancia:** Examen Final Regular — Mesa Noviembre 2026  
**Universidad Católica de Santiago del Estero — Departamento Académico San Salvador**  
**Ciclo Lectivo:** 2026  
**Duración:** 120–150 minutos  
**Modalidad:** **100% Práctica en Computadora (C++)** — Único tema, sin instancia escrita en papel.

---

## 1. Visión General y Objetivos de Evaluación

El presente documento formaliza la arquitectura técnica, modelo de datos, contratos algorítmicos, invariantes de memoria y casos de prueba para el **Examen Final Regular (Noviembre 2026)**.

### Arquitectura y Reglas de la Cátedra
1. **100% Laboratorio de Programación (C++):**
   - Resolución integral en computadora sobre un arreglo estático de registros (`struct` + array AoS) de capacidad física `CAPACIDAD = 15` y tamaño lógico inicial `tam = 4`.
   - **Tipos de datos exclusivamente primitivos (`int`, `char`, `double`):** Se prohíbe `std::string` en los campos de la estructura para evitar conflictos de búfer con `cin.ignore()` / `getline()`. Toda entrada de consola se efectúa limpiamente mediante `cin >>`.
   - **Plantilla Base Completa tipo 4to Examen:** Se entrega `main()` con los 4 registros iniciales precargados, el bucle interactivo `do-while`, los `case 1` a `case 8` con `// TODO` y las 3 funciones de presentación pre-implementadas (`mostrarMenu()`, `mostrarFicha()`, `mostrarTabla()`).
   - **Responsabilidad del Estudiante:** Declarar los 6 campos del `struct Medicamento` en el orden exacto de la tabla, diseñar los prototipos de las funciones lógicas, completar los `case` del `switch` (incluyendo validaciones de dominio y cálculo de campos derivados) e implementar los **7 bloques algorítmicos** más la función auxiliar `intercambiar(...)`.
   - **Ampliación de Final (Filtro + Estadística por Categoría):** Incorpora filtrado por categoría (reutilizando `mostrarFicha`) y promedio estadístico filtrado por categoría con doble guarda defensiva (`tam <= 0` o `coincidencias == 0`).

---

## 2. Definición del Tema Único y Modelo de Datos

### Sistema de Gestión de Farmacia — Stock de Medicamentos
- **Entidad:** `Medicamento`
- **Contexto:** Administración en memoria RAM del inventario de medicamentos de una farmacia institucional, clasificación automática de categoría según proximidad del año de vencimiento, aplicación de descuentos por liquidación de lote y reportes estadísticos por categoría.
- **Estructura C++ (6 campos, 100% Primitivos, orden estricto):**
```cpp
struct Medicamento {
    int codigo;            // Clave Primaria univoca (estrictamente inmutable, > 0)
    int anioVencimiento;   // Anio de vencimiento del lote (2026 .. 2035)
    int stockCajas;        // Existencias fisicas en cajas (>= 0)
    char categoria;        // Calculado: 'C' (Critico 2026), 'M' (Medio 2027..2028), 'E' (Estable >= 2029)
    double precioLista;    // Precio base de lista por caja (> 0.0)
    double precioVenta;    // Calculado: precioLista con descuento por categoria
};
```
- **Reglas de Negocio y Campos Derivados:**
  - `categoria`:
    - Si `anioVencimiento == 2026` → `'C'` (**Crítico / Vence este año**).
    - Si `anioVencimiento <= 2028` → `'M'` (**Medio plazo**).
    - Caso contrario (`anioVencimiento >= 2029`) → `'E'` (**Estable / Largo plazo**).
  - `precioVenta`:
    - Si `categoria == 'C'` → `precioLista * 0.80` (`-20%` de descuento por liquidación).
    - Si `categoria == 'M'` → `precioLista * 0.90` (`-10%` de descuento promocional).
    - Si `categoria == 'E'` → `precioLista * 1.00` (precio pleno de lista).
- **Algoritmo de Ordenamiento en C++:** **Burbuja Mejorada Ascendente** por `precioLista` (menor a mayor) con bandera `huboIntercambio` e intercambio de registros completos mediante `intercambiar(Medicamento &a, Medicamento &b)`.

### Registros Precargados Iniciales (`CAPACIDAD = 15`, `tam = 4`)
| Posición | `codigo` | `anioVencimiento` | `stockCajas` | `categoria` | `precioLista` | `precioVenta` |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| `[0]` | `105` | `2027` | `40` | `'M'` | `8000.00` | `7200.00` |
| `[1]` | `210` | `2030` | `15` | `'E'` | `12000.00` | `12000.00` |
| `[2]` | `308` | `2026` | `25` | `'C'` | `5000.00` | `4000.00` |
| `[3]` | `412` | `2028` | `60` | `'M'` | `9500.00` | `8550.00` |

---

## 3. Contratos de Funciones Algorítmicas (Lógica Pura C++)

### 3.1. Búsqueda por Clave Primaria (10%)
- **Firma Oficial:** `int buscarPorCodigo(const Medicamento arr[], int tam, int codigoBuscado);`
- **Contrato:**
  - Recorrido secuencial desde `0` hasta `tam - 1`.
  - Salida temprana inmediata apenas `arr[i].codigo == codigoBuscado`.
  - Retorna índice `[0 .. tam-1]` o centinela `-1`. Respeta `const` en el arreglo.

### 3.2. Alta / Inserción en Posición con Unicidad de Clave (15%)
- **Firma Oficial:** `bool insertarMedicamento(Medicamento arr[], int &tam, int capacidad, int pos, const Medicamento &nuevo);`
- **Contrato:**
  - Control de capacidad y fronteras: retorna `false` si `tam >= capacidad || pos < 0 || pos > tam`.
  - **Reutilización obligatoria de búsqueda:** invoca `buscarPorCodigo(arr, tam, nuevo.codigo) != -1` para rechazar duplicados.
  - *Right-Shift:* desplaza `arr[i] = arr[i - 1]` desde `i = tam` hasta `pos + 1`.
  - Inserta `arr[pos] = nuevo`, incrementa `tam++` y retorna `true`.

### 3.3. Modificación *in-place* con Clave Primaria Inmutable (15%)
- **Firma Oficial:** `bool modificarMedicamento(Medicamento arr[], int tam, const Medicamento &actualizado);`
- **Contrato:**
  - Reutiliza `buscarPorCodigo(arr, tam, actualizado.codigo)` para hallar `pos`. Si `pos == -1`, retorna `false`.
  - Muta *in-place* `anioVencimiento`, `stockCajas`, `categoria`, `precioLista` y `precioVenta` en `arr[pos]`.
  - **Invariante:** `arr[pos].codigo` permanece estrictamente inmutable. Retorna `true`.

### 3.4. Baja Física con Compactación del Arreglo (15%)
- **Firma Oficial:** `bool darDeBajaMedicamento(Medicamento arr[], int &tam, int codigoABorrar);`
- **Contrato:**
  - Reutiliza `buscarPorCodigo(arr, tam, codigoABorrar)` para hallar `pos`. Si `pos == -1`, retorna `false`.
  - *Left-Shift:* desplaza `arr[k] = arr[k + 1]` desde `k = pos` hasta `tam - 2`.
  - Decrementa `tam--` y retorna `true`.

### 3.5. Ordenamiento Burbuja Mejorada con Intercambio de Estructuras (20%)
- **Firmas Oficiales:**
  - `void intercambiar(Medicamento &a, Medicamento &b);`
  - `void ordenarPorPrecioListaBurbujaAsc(Medicamento arr[], int tam);`
- **Contrato:**
  - Bandera booleana `huboIntercambio` para terminación anticipada cuando no hay permutaciones en una pasada.
  - Criterio estricto: intercambia si `arr[j].precioLista > arr[j + 1].precioLista`.
  - Permuta estructuras completas mediante `intercambiar(arr[j], arr[j + 1])`.

### 3.6. Filtrado de Registros por Categoría (10%)
- **Firma Oficial:** `int filtrarPorCategoria(const Medicamento arr[], int tam, char catBuscada);`
- **Contrato:**
  - Recorrido secuencial sobre `const Medicamento arr[]` en `[0 .. tam-1]`.
  - Por cada registro cuya `categoria == catBuscada`, invoca `mostrarFicha(arr[i])` e incrementa un contador.
  - Retorna la cantidad total de medicamentos mostrados (`0` si no hay coincidencias o `tam <= 0`).

### 3.7. Cálculo Estadístico Seguro por Categoría (15%)
- **Firma Oficial:** `double calcularPromedioPorCategoria(const Medicamento arr[], int tam, char catBuscada);`
- **Contrato:**
  - Recorrido secuencial sobre `const Medicamento arr[]` acumulando `precioVenta` y contando coincidencias donde `arr[i].categoria == catBuscada`.
  - **Doble guarda defensiva:** si `tam <= 0 || cont == 0`, retorna inmediatamente `0.0` para evitar división por cero.
  - Retorna `suma / cont` en punto flotante `double`.

### 3.8. Capa de Presentación Pre-implementada
```cpp
void mostrarMenu();
void mostrarFicha(const Medicamento &e);
void mostrarTabla(const Medicamento arr[], int tam);
```

---

## 4. Casos de Prueba Formales Verificados (4 Casos C++)

### Caso 1: Alta en Posición (Right-Shift)
- **Entrada (`stdin`):** `3`, `2`, `250`, `2026`, `18`, `6000.0`, `1`, `0`
- **Resultado esperado:** Inserta código `250` (`anio=2026`, `stock=18`, `cat='C'`, `precioLista=6000.00`, `precioVenta=4800.00`) en celda `[2]`. Desplaza `308` a `[3]` y `412` a `[4]`. `tam` pasa a `5`.

### Caso 2: Búsqueda y Modificación (PK Inmutable)
- **Entrada (`stdin`):** `4`, `105`, `2029`, `55`, `10000.0`, `2`, `105`, `0`
- **Resultado esperado:** Modifica el medicamento `105` manteniendo intacto su código, pasando a `anio=2029`, `stock=55`, `cat='E'`, `precioLista=10000.00`, `precioVenta=10000.00`. La consulta posterior exhibe la ficha actualizada.

### Caso 3: Baja Física con Compactación (Left-Shift)
- **Entrada (`stdin`):** `5`, `210`, `1`, `0`
- **Resultado esperado:** Elimina código `210` de `[1]`, desplaza `308` a `[1]` y `412` a `[2]`, y reduce `tam` a `3`.

### Caso 4: Ordenamiento Burbuja Ascendente, Filtro y Estadística por Categoría
- **Entrada (`stdin`):** `6`, `7`, `M`, `8`, `M`, `0`
- **Resultado esperado:**
  - Opción `6`: Orden ascendente por `precioLista`: `308 ($5000.00)`, `105 ($8000.00)`, `412 ($9500.00)`, `210 ($12000.00)`.
  - Opción `7` (`'M'`): Muestra las 2 fichas de categoría `'M'` (`105` y `412`) e informa `2` coincidencias.
  - Opción `8` (`'M'`): Promedio de `precioVenta` en categoría `'M'`: `(7200.00 + 8550.00) / 2 = $7875.00`.

---

## 5. Matriz de Ponderación Oficial (100% C++)

| Bloque | Módulo / Competencia Evaluada | Soporte | Pts |
| :---: | :--- | :---: | :---: |
| 1 | Búsqueda por Clave Primaria (Salida temprana, Centinela `-1`, `const`) | C++ | 10% |
| 2 | Alta / Inserción con Unicidad (Capacidad, Posición, Reutilización búsqueda, *Right-Shift*, `tam++`) | C++ | 15% |
| 3 | Modificación *in-place* con PK Inmutable (Reutilización búsqueda, Recálculo de derivados) | C++ | 15% |
| 4 | Baja Física con Compactación (Reutilización búsqueda, *Left-Shift*, `tam--`) | C++ | 15% |
| 5 | Ordenamiento Burbuja Mejorada Ascendente (`huboIntercambio`, `intercambiar` completo) | C++ | 20% |
| 6 | Filtrado por Categoría (`const`, invocación a `mostrarFicha`, conteo de coincidencias) | C++ | 10% |
| 7 | Estadística Segura por Categoría (`const`, acumulador + contador, doble guarda `tam <= 0 \|\| cont == 0`) | C++ | 15% |
| **Total** | **Acreditación Integral Examen Final Regular — Mesa Noviembre 2026** | **C++** | **100%** |
