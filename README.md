# 📋 Examen Final Regular (Noviembre 2026) — Sistema de Gestión de Farmacia (AoS)

**Universidad Católica de Santiago del Estero — Departamento Académico San Salvador**  
**Departamento Académico San Salvador (Jujuy)**  
**Cátedra:** Algoritmos y Programación  
**Ciclo Lectivo:** 2026  

---

## 🏛️ Modalidad de Evaluación (100% C++ — Tema Único)

El presente Examen Final evalúa competencias integrales en C++ sobre Arreglos Estáticos de Estructuras (*Array of Structs*), ciclo ABM completo, Ordenamiento Burbuja Mejorada Ascendente, Filtrado por Categoría y Estadística Segura (sin instancia escrita en papel):

### 1. Entorno Web Interactivo
- **`index.html`:** Portal institucional de acceso para alumnos.
- **`enunciado.html`:** Enunciado interactivo único — **Sistema de Gestión de Farmacia (`struct Medicamento`)**, con tabla de especificación de dominio, casos de prueba ejecutables y plantilla de código base.
- **`admin.html`:** Panel docente centralizado con accesos a especificaciones, solución y rúbricas.

---

### 2. Resolución de Referencia en C++
- **`resolucion.cpp`:** Implementación completa de referencia (`struct Medicamento`, búsqueda secuencial, inserción *Right-Shift* con unicidad, modificación *in-place* con PK inmutable, baja física *Left-Shift*, Burbuja Mejorada Ascendente por `precioLista` e `intercambiar`, filtrado por categoría reutilizando `mostrarFicha`, promedio de `precioVenta` por categoría con doble guarda defensiva y vistas `<iomanip>`).

#### Compilación y Ejecución (C++)
```bash
g++ -Wall -Wextra resolucion.cpp -o examen_final_nov.exe
./examen_final_nov.exe
```

---

### 3. Documentación Pedagógica y de Diseño
- **`SDD.md` (Software Design Document):** Especificación formal de arquitectura, modelo `Medicamento` (100% tipos primitivos), contratos algorítmicos y casos de prueba.
- **`rubrica.md`:** Rúbrica analítica oficial de corrección para el equipo docente (ponderación 100% C++).
- **`rubrica_estudiantes.md`:** Criterios de evaluación y escala UCSE en lenguaje transparente para estudiantes.
