#include <iostream>
#include <iomanip>

using namespace std;

struct Medicamento {
    // Estructura declarada respetando estrictamente el orden del enunciado para inicializacion por llaves
    int codigo;            // Clave Primaria univoca (inmutable)
    int anioVencimiento;   // Anio de vencimiento (2026..2035)
    char categoria;        // 'C' Critico (2026), 'M' Medio (2027-2028), 'E' Estable (>= 2029)
    double precioLista;    // Precio base de lista (> 0.0)
    double precioVenta;    // Calculado: precioLista con descuento por categoria
};

// Prototipos de funciones a implementar por el estudiante
void intercambiar(Medicamento &a, Medicamento &b);
int buscarPorCodigo(const Medicamento arr[], int tam, int codigoBuscado);
bool insertarMedicamento(Medicamento arr[], int &tam, int capacidad, int pos, const Medicamento &nuevo);
bool modificarMedicamento(Medicamento arr[], int tam, const Medicamento &actualizado);
bool darDeBajaMedicamento(Medicamento arr[], int &tam, int codigoABorrar);
void ordenarPorPrecioListaBurbujaAsc(Medicamento arr[], int tam);
int filtrarPorCategoria(const Medicamento arr[], int tam, char catBuscada);
double calcularPromedioPorCategoria(const Medicamento arr[], int tam, char catBuscada);

// Modulos meramente de escritura pre-implementados
void mostrarMenu();
void mostrarFicha(const Medicamento &e);
void mostrarTabla(const Medicamento arr[], int tam);

int main() {
    const int CAPACIDAD = 15;
    Medicamento inventario[CAPACIDAD] = {
        {105, 2027, 'M', 8000.0,  7200.0},
        {210, 2030, 'E', 12000.0, 12000.0},
        {308, 2026, 'C', 5000.0,  4000.0},
        {412, 2028, 'M', 9500.0,  8550.0}
    };
    int tam = 4;

    int opcion = 0;
    do {
        mostrarMenu();
        cout << "  Seleccione una opcion [1-8, 0 para salir]: ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cout << "\n----------------------------------------------------------------------\n";
        switch (opcion) {
            case 1:
                mostrarTabla(inventario, tam);
                break;
            case 2: {
                cout << ">>> CONSULTA DE MEDICAMENTO POR CODIGO <<<\n";
                int cod;
                cout << "  Ingrese Codigo a buscar: ";
                cin >> cod;
                int pos = buscarPorCodigo(inventario, tam, cod);
                if (pos != -1) {
                    cout << "  [OK] Medicamento localizado en celda [" << pos << "]:\n";
                    mostrarFicha(inventario[pos]);
                } else {
                    cout << "  [-] Medicamento con codigo " << cod << " no existe en el inventario.\n";
                }
                break;
            }
            case 3: {
                cout << ">>> REGISTRO / INSERCION DE MEDICAMENTO EN POSICION <<<\n";
                int pos;
                cout << "  Ingrese posicion donde desea insertar [0 .. " << tam << "]: ";
                cin >> pos;

                Medicamento nuevo;
                cout << "  Ingrese Codigo del medicamento (entero > 0): ";
                cin >> nuevo.codigo;
                while (nuevo.codigo <= 0) {
                    cout << "  [!] Codigo invalido. Ingrese entero positivo (> 0): ";
                    cin >> nuevo.codigo;
                }

                cout << "  Ingrese Anio de vencimiento [2026..2035]: ";
                cin >> nuevo.anioVencimiento;
                while (nuevo.anioVencimiento < 2026 || nuevo.anioVencimiento > 2035) {
                    cout << "  [!] Anio fuera de rango. Ingrese entre 2026 y 2035: ";
                    cin >> nuevo.anioVencimiento;
                }

                cout << "  Ingrese Precio de Lista (> 0): $";
                cin >> nuevo.precioLista;
                while (nuevo.precioLista <= 0.0) {
                    cout << "  [!] Precio invalido. Ingrese valor > 0: $";
                    cin >> nuevo.precioLista;
                }

                if (nuevo.anioVencimiento == 2026) {
                    nuevo.categoria = 'C';
                    nuevo.precioVenta = nuevo.precioLista * 0.80;
                } else if (nuevo.anioVencimiento <= 2028) {
                    nuevo.categoria = 'M';
                    nuevo.precioVenta = nuevo.precioLista * 0.90;
                } else {
                    nuevo.categoria = 'E';
                    nuevo.precioVenta = nuevo.precioLista;
                }

                if (insertarMedicamento(inventario, tam, CAPACIDAD, pos, nuevo)) {
                    cout << "\n  [OK] Medicamento registrado exitosamente en la celda [" << pos << "]. Total: " << tam << "/" << CAPACIDAD << "\n";
                } else {
                    cout << "\n  [!] ERROR: No se pudo registrar. Verifique codigo duplicado, cupo agotado o posicion invalida.\n";
                }
                break;
            }
            case 4: {
                cout << ">>> MODIFICACION DE MEDICAMENTO (UPDATE / PK INMUTABLE) <<<\n";
                int cod;
                cout << "  Ingrese Codigo del medicamento a modificar: ";
                cin >> cod;
                int pos = buscarPorCodigo(inventario, tam, cod);
                if (pos == -1) {
                    cout << "\n  [-] Medicamento no encontrado.\n";
                } else {
                    Medicamento modificado;
                    modificado.codigo = cod; // Clave primaria inmutable
                    cout << "  Modificando medicamento con Codigo: " << cod << " (inalterable)\n";

                    cout << "  Nuevo Anio de vencimiento [2026..2035]: ";
                    cin >> modificado.anioVencimiento;
                    while (modificado.anioVencimiento < 2026 || modificado.anioVencimiento > 2035) {
                        cout << "  [!] Anio fuera de rango. Ingrese entre 2026 y 2035: ";
                        cin >> modificado.anioVencimiento;
                    }

                    cout << "  Nuevo Precio de Lista (> 0): $";
                    cin >> modificado.precioLista;
                    while (modificado.precioLista <= 0.0) {
                        cout << "  [!] Precio invalido. Ingrese valor > 0: $";
                        cin >> modificado.precioLista;
                    }

                    if (modificado.anioVencimiento == 2026) {
                        modificado.categoria = 'C';
                        modificado.precioVenta = modificado.precioLista * 0.80;
                    } else if (modificado.anioVencimiento <= 2028) {
                        modificado.categoria = 'M';
                        modificado.precioVenta = modificado.precioLista * 0.90;
                    } else {
                        modificado.categoria = 'E';
                        modificado.precioVenta = modificado.precioLista;
                    }

                    if (modificarMedicamento(inventario, tam, modificado)) {
                        cout << "\n  [OK] Datos del medicamento modificados exitosamente.\n";
                    } else {
                        cout << "\n  [!] Error al modificar.\n";
                    }
                }
                break;
            }
            case 5: {
                cout << ">>> BAJA FISICA DE MEDICAMENTO (DELETE / COMPACTACION) <<<\n";
                int cod;
                cout << "  Ingrese Codigo del medicamento a dar de baja: ";
                cin >> cod;
                if (darDeBajaMedicamento(inventario, tam, cod)) {
                    cout << "\n  [OK] Registro eliminado y arreglo compactado correctamente. Total activos: " << tam << "\n";
                } else {
                    cout << "\n  [-] Codigo no encontrado. No se realizo ninguna baja.\n";
                }
                break;
            }
            case 6:
                cout << ">>> ORDENAMIENTO BURBUJA (ASCENDENTE POR PRECIO DE LISTA) <<<\n";
                ordenarPorPrecioListaBurbujaAsc(inventario, tam);
                cout << "  [OK] Inventario ordenado de menor a mayor segun precio de lista con exito.\n";
                mostrarTabla(inventario, tam);
                break;
            case 7: {
                cout << ">>> FILTRADO DE MEDICAMENTOS POR CATEGORIA <<<\n";
                char cat;
                cout << "  Ingrese Categoria a filtrar (C: Critico, M: Medio, E: Estable): ";
                cin >> cat;
                if (cat >= 'a' && cat <= 'z') cat = cat - ('a' - 'A');
                while (cat != 'C' && cat != 'M' && cat != 'E') {
                    cout << "  [!] Categoria invalida. Ingrese C, M o E: ";
                    cin >> cat;
                    if (cat >= 'a' && cat <= 'z') cat = cat - ('a' - 'A');
                }
                int cant = filtrarPorCategoria(inventario, tam, cat);
                if (cant > 0) {
                    cout << "  [OK] Se encontraron " << cant << " medicamento(s) en la categoria '" << cat << "'.\n";
                } else {
                    cout << "  [-] No hay medicamentos registrados en la categoria '" << cat << "'.\n";
                }
                break;
            }
            case 8: {
                cout << ">>> REPORTE ESTADISTICO: PROMEDIO DE PRECIO DE VENTA POR CATEGORIA <<<\n";
                char cat;
                cout << "  Ingrese Categoria a promediar (C: Critico, M: Medio, E: Estable): ";
                cin >> cat;
                if (cat >= 'a' && cat <= 'z') cat = cat - ('a' - 'A');
                while (cat != 'C' && cat != 'M' && cat != 'E') {
                    cout << "  [!] Categoria invalida. Ingrese C, M o E: ";
                    cin >> cat;
                    if (cat >= 'a' && cat <= 'z') cat = cat - ('a' - 'A');
                }
                double prom = calcularPromedioPorCategoria(inventario, tam, cat);
                cout << "  [RESULTADO] Promedio de precio de venta (Categoria '" << cat << "'): $"
                     << fixed << setprecision(2) << prom << "\n";
                break;
            }
            case 0:
                cout << "  [SISTEMA]: Sesion finalizada. Fin del programa.\n";
                break;
            default:
                cout << "  [!] Opcion no valida. Seleccione una opcion valida del menu [0 a 8].\n";
                break;
        }
    } while (opcion != 0);

    return 0;
}

void intercambiar(Medicamento &a, Medicamento &b) {
    Medicamento aux = a;
    a = b;
    b = aux;
}

int buscarPorCodigo(const Medicamento arr[], int tam, int codigoBuscado) {
    for (int i = 0; i < tam; ++i) {
        if (arr[i].codigo == codigoBuscado) {
            return i;
        }
    }
    return -1;
}

bool insertarMedicamento(Medicamento arr[], int &tam, int capacidad, int pos, const Medicamento &nuevo) {
    if (tam >= capacidad || pos < 0 || pos > tam) return false;
    if (buscarPorCodigo(arr, tam, nuevo.codigo) != -1) return false;
    for (int i = tam; i > pos; --i) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = nuevo;
    tam++;
    return true;
}

bool modificarMedicamento(Medicamento arr[], int tam, const Medicamento &actualizado) {
    int pos = buscarPorCodigo(arr, tam, actualizado.codigo);
    if (pos == -1) return false;
    arr[pos].anioVencimiento = actualizado.anioVencimiento;
    arr[pos].categoria = actualizado.categoria;
    arr[pos].precioLista = actualizado.precioLista;
    arr[pos].precioVenta = actualizado.precioVenta;
    return true;
}

bool darDeBajaMedicamento(Medicamento arr[], int &tam, int codigoABorrar) {
    int pos = buscarPorCodigo(arr, tam, codigoABorrar);
    if (pos == -1) return false;
    for (int k = pos; k < tam - 1; ++k) {
        arr[k] = arr[k + 1];
    }
    tam--;
    return true;
}

void ordenarPorPrecioListaBurbujaAsc(Medicamento arr[], int tam) {
    bool huboIntercambio = true;
    for (int i = 0; i < tam - 1 && huboIntercambio; ++i) {
        huboIntercambio = false;
        for (int j = 0; j < tam - 1 - i; ++j) {
            if (arr[j].precioLista > arr[j + 1].precioLista) {
                intercambiar(arr[j], arr[j + 1]);
                huboIntercambio = true;
            }
        }
    }
}

int filtrarPorCategoria(const Medicamento arr[], int tam, char catBuscada) {
    int cont = 0;
    for (int i = 0; i < tam; ++i) {
        if (arr[i].categoria == catBuscada) {
            mostrarFicha(arr[i]);
            cont++;
        }
    }
    return cont;
}

double calcularPromedioPorCategoria(const Medicamento arr[], int tam, char catBuscada) {
    if (tam <= 0) return 0.0;
    double suma = 0.0;
    int cont = 0;
    for (int i = 0; i < tam; ++i) {
        if (arr[i].categoria == catBuscada) {
            suma += arr[i].precioVenta;
            cont++;
        }
    }
    if (cont == 0) return 0.0;
    return suma / cont;
}

void mostrarMenu() {
    cout << "\n======================================================================\n";
    cout << "         SISTEMA DE GESTION DE FARMACIA (ARRAY OF STRUCTS)            \n";
    cout << "======================================================================\n";
    cout << "  1. Listar Inventario Completo (Formato Tabular)\n";
    cout << "  2. Consultar Medicamento por Codigo (Read)\n";
    cout << "  3. Registrar Medicamento en Posicion (Create / Right-Shift)\n";
    cout << "  4. Modificar Medicamento Existente (Update / PK Inmutable)\n";
    cout << "  5. Dar de Baja Fisica (Delete / Left-Shift)\n";
    cout << "  6. Ordenar por Precio Lista (Burbuja Ascendente)\n";
    cout << "  7. Filtrar Medicamentos por Categoria (C / M / E)\n";
    cout << "  8. Calcular Promedio de Precio Venta por Categoria (Estadistica)\n";
    cout << "  0. Salir\n";
    cout << "======================================================================\n";
}

void mostrarFicha(const Medicamento &e) {
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  | FICHA DE MEDICAMENTO EN INVENTARIO                               |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  | Codigo Lote:      " << left << setw(47) << e.codigo << "|\n";
    cout << "  | Anio Vencimiento: " << left << setw(47) << e.anioVencimiento << "|\n";
    cout << "  | Categoria:        " << left << setw(47) << (e.categoria == 'C' ? "C (Critico -20%)" : (e.categoria == 'M' ? "M (Medio -10%)" : "E (Estable 0%)")) << "|\n";
    cout << "  | Precio Lista:    $" << left << setw(47) << fixed << setprecision(2) << e.precioLista << "|\n";
    cout << "  | Precio Venta:    $" << left << setw(47) << fixed << setprecision(2) << e.precioVenta << "|\n";
    cout << "  +------------------------------------------------------------------+\n" << right;
}

void mostrarTabla(const Medicamento arr[], int tam) {
    if (tam == 0) {
        cout << "  [!] El inventario de farmacia esta vacio (tam = 0).\n";
        return;
    }

    cout << "\n+-----+--------+----------+-----+--------------+--------------+\n";
    cout << "| POS | CODIGO | VENCIM.  | CAT | PRECIO LISTA | PRECIO VENTA |\n";
    cout << "+-----+--------+----------+-----+--------------+--------------+\n";

    cout << right;
    for (int i = 0; i < tam; ++i) {
        cout << "| [" << setw(1) << i << "] | "
             << setw(6) << arr[i].codigo << " |   "
             << setw(6) << arr[i].anioVencimiento << " |  "
             << arr[i].categoria << "  | $"
             << setw(11) << fixed << setprecision(2) << arr[i].precioLista << " | $"
             << setw(11) << fixed << setprecision(2) << arr[i].precioVenta << " |\n";
    }
    cout << "+-----+--------+----------+-----+--------------+--------------+\n";
    cout << "Total medicamentos en inventario: " << tam << ".\n";
}
