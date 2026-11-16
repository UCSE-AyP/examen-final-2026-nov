# Rúbrica Oficial de Evaluación — Examen Final Regular (Noviembre 2026)
**Cátedra:** Algoritmos y Programación  
**Módulo 4 (Integrador):** Arreglos de Estructuras (AoS), ABM, Ordenamiento, Filtrado y Estadística  
**Institución:** Universidad Católica de Santiago del Estero — Departamento Académico San Salvador  

---

## 1. Estructura y Modalidad de Evaluación

La evaluación corresponde a una instancia de **Examen Final Regular (Tema Único)** desarrollada **100% en computadora en C++** (sin instancia escrita en papel):

| Instancia | Soporte | Ponderación | Foco Pedagógico |
| :--- | :---: | :---: | :--- |
| **Laboratorio de Programación** | Computadora (C++) | **100%** | Declaración de `struct Medicamento` (tipos primitivos), integración en menú `switch` y desarrollo de los 7 módulos algorítmicos sobre AoS. |

---

## 2. Desglose Detallado: Laboratorio de Programación (100% C++)

El código base provisto entrega el esqueleto de `main()`, el arreglo `inventario[CAPACIDAD]` precargado con 4 registros y las rutinas de presentación (`mostrarMenu`, `mostrarFicha`, `mostrarTabla`). El estudiante debe declarar los campos de `struct Medicamento` (admitiéndose `double` o `float` en campos decimales sin penalización), definir sus prototipos, completar los `case 1` al `case 8` del `switch` (incluyendo validaciones de dominio y cálculo de `categoria` y `precioVenta`) y programar los **7 bloques algorítmicos**:

### Bloque 1: Búsqueda por Clave Primaria (10%)
- **Firma de Referencia:** `int buscarPorCodigo(const Medicamento arr[], int tam, int codigoBuscado);`
- **Criterios de Evaluación:**
  - **10% (Completo / Excelente):** Recorrido secuencial respetando `tam`. Al hallar coincidencia, retorna inmediatamente la posición `[0 .. tam-1]` (salida temprana $\mathcal{O}(1)$ en mejor caso). Retorna `-1` si no existe. Usa `const` para proteger el arreglo como parámetro de solo lectura.
  - **5% (Parcial / Básico):** Localiza el registro pero omite el retorno `-1`, no aplica `const` o recorre todo el arreglo sin salida temprana.
  - **0% (Insuficiente):** No compila, desborda límites o no localiza el registro.

### Bloque 2: Alta / Inserción con Unicidad de Clave (15%)
- **Firma de Referencia:** `bool insertarMedicamento(Medicamento arr[], int &tam, int capacidad, int pos, const Medicamento &nuevo);`
- **Criterios de Evaluación:**
  - **15% (Completo / Excelente):** Validación de límites físicos (`tam < capacidad` y `0 <= pos <= tam`). **Reutilización modular** de `buscarPorCodigo(...)` para rechazar códigos duplicados. Corrimiento contiguo a derecha (*Right-Shift*) desde `tam` hasta `pos + 1`, inserción en `arr[pos]`, incremento `tam++` (por referencia) y retorno booleano.
  - **12% (Aceptable / Funcional):** Inserta desplazando correctamente y evita duplicados mediante búsqueda lineal *in-line* sin reutilizar el módulo de búsqueda (80% del bloque).
  - **5% (Básico):** Inserta pero omite unicidad de clave o comete errores de límite (*off-by-one*) en el corrimiento.
  - **0% (Insuficiente):** Sobrescribe datos sin desplazar, no actualiza `&tam` o desborda `capacidad`.

### Bloque 3: Modificación *in-place* con Clave Primaria Inmutable (15%)
- **Firma de Referencia:** `bool modificarMedicamento(Medicamento arr[], int tam, const Medicamento &actualizado);`
- **Criterios de Evaluación:**
  - **15% (Completo / Excelente):** Reutiliza `buscarPorCodigo(...)` para localizar la celda. Actualiza *in-place* `anioVencimiento`, `categoria`, `precioLista` y `precioVenta`, preservando **estrictamente inmutable** `codigo` (PK). Se admite el recálculo de campos derivados tanto dentro del `switch` como dentro de la función. Retorna `true` o `false`.
  - **12% (Aceptable / Funcional):** Modifica correctamente sin alterar la PK usando búsqueda *in-line* (80% del bloque).
  - **0% (Insuficiente):** Modifica la clave primaria, no actualiza derivados o corrompe memoria.

### Bloque 4: Baja Física con Compactación del Arreglo (15%)
- **Firma de Referencia:** `bool darDeBajaMedicamento(Medicamento arr[], int &tam, int codigoABorrar);`
- **Criterios de Evaluación:**
  - **15% (Completo / Excelente):** Reutiliza `buscarPorCodigo(...)` para localizar el índice. Compacta el arreglo mediante corrimiento contiguo a izquierda (*Left-Shift*) desde `pos` hasta `tam - 2`, decrementa `tam--` (por referencia) y retorna `true` (o `false` si no existe).
  - **12% (Aceptable / Funcional):** Compacta correctamente usando búsqueda *in-line* (80% del bloque).
  - **5% (Básico):** Aplica baja lógica en lugar de física o comete error *off-by-one* al compactar.
  - **0% (Insuficiente):** Decrementa `tam` sin compactar o no reduce `tam`.

### Bloque 5: Ordenamiento Burbuja Mejorada Ascendente con Intercambio Completo (20%)
- **Firmas de Referencia:** `void intercambiar(Medicamento &a, Medicamento &b);` y `void ordenarPorPrecioListaBurbujaAsc(Medicamento arr[], int tam);`
- **Criterios de Evaluación:**
  - **20% (Completo / Excelente):** Implementa **Burbuja Mejorada** con bandera booleana `huboIntercambio` para corte anticipado. Comparación estricta en orden **ascendente** por `precioLista`. Intercambio completo del `struct Medicamento` mediante la función auxiliar `intercambiar(Medicamento &a, Medicamento &b)` pasando por referencia.
  - **12% (Aceptable / Funcional):** Implementa Burbuja clásica sin bandera de corte o realiza swap manual con variable `struct` auxiliar dentro de la función sin modularizar `intercambiar(...)`.
  - **0% (Insuficiente):** No ordena, ordena descendente, permuta campos sueltos desincronizando los registros o utiliza `std::sort`.

### Bloque 6: Filtrado de Registros por Categoría (10%)
- **Firma de Referencia:** `int filtrarPorCategoria(const Medicamento arr[], int tam, char catBuscada);`
- **Criterios de Evaluación:**
  - **10% (Completo / Excelente):** Recorre `[0 .. tam-1]` protegiendo el arreglo con `const`. Filtra los registros donde `arr[i].categoria == catBuscada`, reutiliza `mostrarFicha(arr[i])` para su visualización y contabiliza/retorna la cantidad de coincidencias (o informa claramente cuando es `0`).
  - **5% (Parcial / Básico):** Filtra y muestra datos pero omite `const`, no reutiliza `mostrarFicha` o no contempla el caso sin coincidencias.
  - **0% (Insuficiente):** No filtra, recorre basura más allá de `tam` o altera el arreglo.

### Bloque 7: Cálculo Estadístico Seguro por Categoría (15%)
- **Firma de Referencia:** `double calcularPromedioPorCategoria(const Medicamento arr[], int tam, char catBuscada);`
- **Criterios de Evaluación:**
  - **15% (Completo / Excelente):** Recorre `[0 .. tam-1]` protegiendo el arreglo con `const`, acumula `precioVenta` y cuenta solo los elementos de `catBuscada`. Implementa **doble guarda defensiva** (`if (tam <= 0) return 0.0;` y `if (cont == 0) return 0.0;`) evitando división por cero tanto con arreglo vacío como con categoría inexistente en los datos activos. Retorna promedio `double`.
  - **8% (Aceptable / Parcial):** Calcula el promedio correctamente cuando existen datos, pero omite la guarda cuando `cont == 0` o `tam <= 0`, o bien omite `const`.
  - **0% (Insuficiente):** Provoca división por cero, acumula `precioLista` en lugar de `precioVenta`, promedia sobre `tam` total en vez de `cont`, o no recorre el arreglo.

---

## 3. Penalizaciones y Criterios Disciplinares

| Falta Técnica | Penalización | Justificación Pedagógica |
| :--- | :---: | :--- |
| **Uso de Vectores Paralelos** | **-50% del examen** | Violación directa del paradigma Array of Structs (AoS). |
| **Uso de `std::string` en el `struct`** | **-10%** | Incumplimiento de la directiva de tipos primitivos puros. |
| **Uso de `std::sort` o librerías externas** | **-20% (Bloque 5 anulado)** | Se evalúa la codificación manual de Burbuja Mejorada. |
| **Errores de Compilación** | **Descuento en bloque (hasta -30%)** | El código debe compilar en C++. Si una corrección sintáctica mínima permite evaluar la lógica, se reconoce puntaje parcial en el bloque afectado. |
| **Permutación de campos sueltos en ordenamiento** | **-15%** | Destruye la integridad referencial de los registros. |

> [!IMPORTANT]
> **Regla de No Acumulación:** Las penalizaciones no se acumulan si sancionan el mismo defecto ya descontado en su bloque específico. La calificación final nunca será inferior a 0%.

---

## 4. Tabla de Conversión a Nota Final (Escala UCSE 1 a 10)

| Puntaje Total (%) | Nota UCSE | Condición Académica |
| :---: | :---: | :--- |
| **0 – 39%** | **1 – 2** | No Aprobado / Reprobado |
| **40 – 59%** | **3** | Insuficiente |
| **60 – 67%** | **4** | **Aprobado (Mínimo de acreditación)** |
| **68 – 75%** | **5** | Aprobado (Aceptable) |
| **76 – 83%** | **6** | Bueno |
| **84 – 87%** | **7** | Muy Bueno |
| **88 – 91%** | **8** | Distinguido |
| **92 – 95%** | **9** | Excelente |
| **96 – 100%** | **10** | Sobresaliente |
