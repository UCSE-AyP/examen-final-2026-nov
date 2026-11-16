# Guía de Evaluación para Estudiantes — Examen Final Regular (Noviembre 2026)
**Cátedra:** Algoritmos y Programación  
**Modalidad:** 100% Práctica en Computadora (C++) — Tema Único  
**Institución:** Universidad Católica de Santiago del Estero — Departamento Académico San Salvador  

---

## 1. ¿Qué se evalúa en este Examen Final?

El examen consiste en desarrollar en C++ un sistema de gestión de stock de farmacia basado en un **Arreglo de Estructuras (Array of Structs — AoS)**.  
La totalidad del puntaje (**100%**) corresponde a la solución en computadora.

Se entrega una **plantilla base** con `main()`, 4 registros precargados y las funciones de impresión (`mostrarMenu()`, `mostrarFicha()`, `mostrarTabla()`).  
Tu trabajo consiste en:
1. Declarar los 6 campos del `struct Medicamento` con tipos primitivos (`int`, `char`, `double`, sin `std::string`) en el **orden exacto** indicado en el enunciado.
2. Definir los prototipos y programar los **7 módulos algorítmicos** (más la función auxiliar `intercambiar`).
3. Completar las opciones `1` a `8` del `switch` en `main()` con la lectura, validación de rangos y cálculo de campos derivados (`categoria` y `precioVenta`).

---

## 2. Distribución del Puntaje (100%)

| Bloque | Operación / Competencia | Puntos | Aspectos Clave para Lograr el 100% del Bloque |
| :---: | :--- | :---: | :--- |
| **1** | **Búsqueda por Código (`Read`)** | **10%** | Recorrido secuencial hasta `tam - 1`, retorno inmediato del índice al encontrarlo, `-1` si no existe y parámetro `const`. |
| **2** | **Alta / Inserción en Posición (`Create`)** | **15%** | Validar `tam < capacidad` y `0 <= pos <= tam`, **reutilizar la búsqueda** para rechazar códigos duplicados, desplazar a derecha (*Right-Shift*) e incrementar `tam++`. |
| **3** | **Modificación *in-place* (`Update`)** | **15%** | **Reutilizar la búsqueda**, actualizar campos mutables y recalcular `categoria` y `precioVenta`, manteniendo `codigo` **estrictamente inmutable**. |
| **4** | **Baja Física con Compactación (`Delete`)** | **15%** | **Reutilizar la búsqueda**, compactar desplazando a la izquierda (*Left-Shift*) sin dejar huecos y decrementar `tam--`. |
| **5** | **Burbuja Mejorada Ascendente (`Sort`)** | **20%** | Bandera `huboIntercambio` para corte anticipado, orden **ascendente** por `precioLista` e intercambio completo vía `intercambiar(Medicamento &a, Medicamento &b)`. |
| **6** | **Filtrado por Categoría (`Filter`)** | **10%** | Parámetro `const`, filtrar por `'C'`, `'M'` o `'E'` reutilizando `mostrarFicha(...)` y contabilizar/informar coincidencias. |
| **7** | **Estadística Segura por Categoría (`Stats`)** | **15%** | Parámetro `const`, acumular `precioVenta` y contar coincidencias de la categoría elegida, aplicando **doble guarda defensiva** (`tam <= 0` o `cont == 0` retorna `0.0`). |

> **Importante sobre Modularidad:** En Alta, Modificación y Baja se espera que reutilices la función de búsqueda del Bloque 1. Si repetís un bucle de búsqueda manual dentro de esas funciones en lugar de invocarla, se alcanza hasta el 80% funcional del bloque.

---

## 3. Reglas Fundamentales y Escala de Aprobación

- **Compilación limpia:** Tu programa debe compilar bajo el estándar **C++** sin errores.
- **Prohibido:** Uso de vectores paralelos, uso de `std::string` en el `struct`, uso de `std::sort` o intercambio de campos sueltos durante el ordenamiento.
- **Condición de aprobación:** Se requiere alcanzar al menos **60%** del puntaje total (**Nota 4**).

| Porcentaje | 0–39% | 40–59% | **60–67%** | 68–75% | 76–83% | 84–87% | 88–91% | 92–95% | 96–100% |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Nota UCSE** | 1 – 2 | 3 | **4 (Aprobado)** | 5 | 6 | 7 | 8 | 9 | 10 |
