#include <iostream>
#include <iomanip>

using namespace std;

const int CAPACIDAD = 15;

// Prototipos de funciones a implementar por el estudiante
void intercambiarInt(int &a, int &b);
void intercambiarChar(char &a, char &b);
void intercambiarDouble(double &a, double &b);
int buscarPorCodigo(const int codigos[], int tam, int codigoBuscado);
bool insertarMedicamento(int codigos[], int aniosVencimiento[], char categorias[], double preciosLista[], double preciosVenta[],
                         int &tam, int pos, int codigo, int anioVencimiento, char categoria, double precioLista, double precioVenta);
bool modificarMedicamento(const int codigos[], int aniosVencimiento[], char categorias[], double preciosLista[], double preciosVenta[],
                          int tam, int codigo, int nuevoAnio, char nuevaCat, double nuevoPrecioLista, double nuevoPrecioVenta);
bool darDeBajaMedicamento(int codigos[], int aniosVencimiento[], char categorias[], double preciosLista[], double preciosVenta[],
                          int &tam, int codigoABorrar);
void ordenarPorPrecioListaBurbujaAsc(int codigos[], int aniosVencimiento[], char categorias[], double preciosLista[], double preciosVenta[], int tam);
int filtrarPorCategoria(const int codigos[], const int aniosVencimiento[], const char categorias[], const double preciosLista[], const double preciosVenta[],
                        int tam, char catBuscada);
double calcularPromedioPorCategoria(const char categorias[], const double preciosVenta[], int tam, char catBuscada);

// Modulos meramente de escritura pre-implementados
void mostrarMenu();
void mostrarFicha(int codigo, int anioVencimiento, char categoria, double precioLista, double precioVenta);
void mostrarTabla(const int codigos[], const int aniosVencimiento[], const char categorias[], const double preciosLista[], const double preciosVenta[], int tam);

int main() {
    int codigos[CAPACIDAD]          = {105, 210, 308, 412};
    int aniosVencimiento[CAPACIDAD] = {2027, 2030, 2026, 2028};
    char categorias[CAPACIDAD]      = {'M', 'E', 'C', 'M'};
    double preciosLista[CAPACIDAD]  = {8000.0, 12000.0, 5000.0, 9500.0};
    double preciosVenta[CAPACIDAD]  = {7200.0, 12000.0, 4000.0, 8550.0};
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
                mostrarTabla(codigos, aniosVencimiento, categorias, preciosLista, preciosVenta, tam);
                break;
            case 2: {
                cout << ">>> CONSULTA DE MEDICAMENTO POR CODIGO <<<\n";
                int cod;
                cout << "  Ingrese Codigo a buscar: ";
                cin >> cod;
                int pos = buscarPorCodigo(codigos, tam, cod);
                if (pos != -1) {
                    cout << "  [OK] Medicamento localizado en celda [" << pos << "]:\n";
                    mostrarFicha(codigos[pos], aniosVencimiento[pos], categorias[pos], preciosLista[pos], preciosVenta[pos]);
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

                int codigo, anioVencimiento;
                char categoria;
                double precioLista, precioVenta;

                cout << "  Ingrese Codigo del medicamento (entero > 0): ";
                cin >> codigo;
                while (codigo <= 0) {
                    cout << "  [!] Codigo invalido. Ingrese entero positivo (> 0): ";
                    cin >> codigo;
                }

                cout << "  Ingrese Anio de vencimiento [2026..2035]: ";
                cin >> anioVencimiento;
                while (anioVencimiento < 2026 || anioVencimiento > 2035) {
                    cout << "  [!] Anio fuera de rango. Ingrese entre 2026 y 2035: ";
                    cin >> anioVencimiento;
                }

                cout << "  Ingrese Precio de Lista (> 0): $";
                cin >> precioLista;
                while (precioLista <= 0.0) {
                    cout << "  [!] Precio invalido. Ingrese valor > 0: $";
                    cin >> precioLista;
                }

                if (anioVencimiento == 2026) {
                    categoria = 'C';
                    precioVenta = precioLista * 0.80;
                } else if (anioVencimiento <= 2028) {
                    categoria = 'M';
                    precioVenta = precioLista * 0.90;
                } else {
                    categoria = 'E';
                    precioVenta = precioLista;
                }

                if (insertarMedicamento(codigos, aniosVencimiento, categorias, preciosLista, preciosVenta,
                                        tam, pos, codigo, anioVencimiento, categoria, precioLista, precioVenta)) {
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
                int pos = buscarPorCodigo(codigos, tam, cod);
                if (pos == -1) {
                    cout << "\n  [-] Medicamento no encontrado.\n";
                } else {
                    int nuevoAnio;
                    char nuevaCat;
                    double nuevoPrecioLista, nuevoPrecioVenta;

                    cout << "  Modificando medicamento con Codigo: " << cod << " (inalterable)\n";

                    cout << "  Nuevo Anio de vencimiento [2026..2035]: ";
                    cin >> nuevoAnio;
                    while (nuevoAnio < 2026 || nuevoAnio > 2035) {
                        cout << "  [!] Anio fuera de rango. Ingrese entre 2026 y 2035: ";
                        cin >> nuevoAnio;
                    }

                    cout << "  Nuevo Precio de Lista (> 0): $";
                    cin >> nuevoPrecioLista;
                    while (nuevoPrecioLista <= 0.0) {
                        cout << "  [!] Precio invalido. Ingrese valor > 0: $";
                        cin >> nuevoPrecioLista;
                    }

                    if (nuevoAnio == 2026) {
                        nuevaCat = 'C';
                        nuevoPrecioVenta = nuevoPrecioLista * 0.80;
                    } else if (nuevoAnio <= 2028) {
                        nuevaCat = 'M';
                        nuevoPrecioVenta = nuevoPrecioLista * 0.90;
                    } else {
                        nuevaCat = 'E';
                        nuevoPrecioVenta = nuevoPrecioLista;
                    }

                    if (modificarMedicamento(codigos, aniosVencimiento, categorias, preciosLista, preciosVenta,
                                             tam, cod, nuevoAnio, nuevaCat, nuevoPrecioLista, nuevoPrecioVenta)) {
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
                if (darDeBajaMedicamento(codigos, aniosVencimiento, categorias, preciosLista, preciosVenta, tam, cod)) {
                    cout << "\n  [OK] Registro eliminado y arreglos compactados correctamente. Total activos: " << tam << "\n";
                } else {
                    cout << "\n  [-] Codigo no encontrado. No se realizo ninguna baja.\n";
                }
                break;
            }
            case 6:
                cout << ">>> ORDENAMIENTO BURBUJA (ASCENDENTE POR PRECIO DE LISTA) <<<\n";
                ordenarPorPrecioListaBurbujaAsc(codigos, aniosVencimiento, categorias, preciosLista, preciosVenta, tam);
                cout << "  [OK] Inventario ordenado de menor a mayor segun precio de lista con exito.\n";
                mostrarTabla(codigos, aniosVencimiento, categorias, preciosLista, preciosVenta, tam);
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
                int cant = filtrarPorCategoria(codigos, aniosVencimiento, categorias, preciosLista, preciosVenta, tam, cat);
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
                double prom = calcularPromedioPorCategoria(categorias, preciosVenta, tam, cat);
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

void intercambiarInt(int &a, int &b) {
    int aux = a;
    a = b;
    b = aux;
}

void intercambiarChar(char &a, char &b) {
    char aux = a;
    a = b;
    b = aux;
}

void intercambiarDouble(double &a, double &b) {
    double aux = a;
    a = b;
    b = aux;
}

int buscarPorCodigo(const int codigos[], int tam, int codigoBuscado) {
    for (int i = 0; i < tam; ++i) {
        if (codigos[i] == codigoBuscado) {
            return i;
        }
    }
    return -1;
}

bool insertarMedicamento(int codigos[], int aniosVencimiento[], char categorias[], double preciosLista[], double preciosVenta[],
                         int &tam, int pos, int codigo, int anioVencimiento, char categoria, double precioLista, double precioVenta) {
    if (tam >= CAPACIDAD || pos < 0 || pos > tam) return false;
    if (buscarPorCodigo(codigos, tam, codigo) != -1) return false;
    for (int i = tam; i > pos; --i) {
        codigos[i] = codigos[i - 1];
        aniosVencimiento[i] = aniosVencimiento[i - 1];
        categorias[i] = categorias[i - 1];
        preciosLista[i] = preciosLista[i - 1];
        preciosVenta[i] = preciosVenta[i - 1];
    }
    codigos[pos] = codigo;
    aniosVencimiento[pos] = anioVencimiento;
    categorias[pos] = categoria;
    preciosLista[pos] = precioLista;
    preciosVenta[pos] = precioVenta;
    tam++;
    return true;
}

bool modificarMedicamento(const int codigos[], int aniosVencimiento[], char categorias[], double preciosLista[], double preciosVenta[],
                          int tam, int codigo, int nuevoAnio, char nuevaCat, double nuevoPrecioLista, double nuevoPrecioVenta) {
    int pos = buscarPorCodigo(codigos, tam, codigo);
    if (pos == -1) return false;
    aniosVencimiento[pos] = nuevoAnio;
    categorias[pos] = nuevaCat;
    preciosLista[pos] = nuevoPrecioLista;
    preciosVenta[pos] = nuevoPrecioVenta;
    return true;
}

bool darDeBajaMedicamento(int codigos[], int aniosVencimiento[], char categorias[], double preciosLista[], double preciosVenta[],
                          int &tam, int codigoABorrar) {
    int pos = buscarPorCodigo(codigos, tam, codigoABorrar);
    if (pos == -1) return false;
    for (int k = pos; k < tam - 1; ++k) {
        codigos[k] = codigos[k + 1];
        aniosVencimiento[k] = aniosVencimiento[k + 1];
        categorias[k] = categorias[k + 1];
        preciosLista[k] = preciosLista[k + 1];
        preciosVenta[k] = preciosVenta[k + 1];
    }
    tam--;
    return true;
}

void ordenarPorPrecioListaBurbujaAsc(int codigos[], int aniosVencimiento[], char categorias[], double preciosLista[], double preciosVenta[], int tam) {
    bool huboIntercambio = true;
    for (int i = 0; i < tam - 1 && huboIntercambio; ++i) {
        huboIntercambio = false;
        for (int j = 0; j < tam - 1 - i; ++j) {
            if (preciosLista[j] > preciosLista[j + 1]) {
                intercambiarInt(codigos[j], codigos[j + 1]);
                intercambiarInt(aniosVencimiento[j], aniosVencimiento[j + 1]);
                intercambiarChar(categorias[j], categorias[j + 1]);
                intercambiarDouble(preciosLista[j], preciosLista[j + 1]);
                intercambiarDouble(preciosVenta[j], preciosVenta[j + 1]);
                huboIntercambio = true;
            }
        }
    }
}

int filtrarPorCategoria(const int codigos[], const int aniosVencimiento[], const char categorias[], const double preciosLista[], const double preciosVenta[],
                        int tam, char catBuscada) {
    int cont = 0;
    for (int i = 0; i < tam; ++i) {
        if (categorias[i] == catBuscada) {
            mostrarFicha(codigos[i], aniosVencimiento[i], categorias[i], preciosLista[i], preciosVenta[i]);
            cont++;
        }
    }
    return cont;
}

double calcularPromedioPorCategoria(const char categorias[], const double preciosVenta[], int tam, char catBuscada) {
    if (tam <= 0) return 0.0;
    double suma = 0.0;
    int cont = 0;
    for (int i = 0; i < tam; ++i) {
        if (categorias[i] == catBuscada) {
            suma += preciosVenta[i];
            cont++;
        }
    }
    if (cont == 0) return 0.0;
    return suma / cont;
}

void mostrarMenu() {
    cout << "\n======================================================================\n";
    cout << "         SISTEMA DE GESTION DE FARMACIA (VECTORES PARALELOS)          \n";
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

void mostrarFicha(int codigo, int anioVencimiento, char categoria, double precioLista, double precioVenta) {
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  | FICHA DE MEDICAMENTO EN INVENTARIO                               |\n";
    cout << "  +------------------------------------------------------------------+\n";
    cout << "  | Codigo Lote:      " << left << setw(47) << codigo << "|\n";
    cout << "  | Anio Vencimiento: " << left << setw(47) << anioVencimiento << "|\n";
    cout << "  | Categoria:        " << left << setw(47) << (categoria == 'C' ? "C (Critico -20%)" : (categoria == 'M' ? "M (Medio -10%)" : "E (Estable 0%)")) << "|\n";
    cout << "  | Precio Lista:    $" << left << setw(47) << fixed << setprecision(2) << precioLista << "|\n";
    cout << "  | Precio Venta:    $" << left << setw(47) << fixed << setprecision(2) << precioVenta << "|\n";
    cout << "  +------------------------------------------------------------------+\n" << right;
}

void mostrarTabla(const int codigos[], const int aniosVencimiento[], const char categorias[], const double preciosLista[], const double preciosVenta[], int tam) {
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
             << setw(6) << codigos[i] << " |   "
             << setw(6) << aniosVencimiento[i] << " |  "
             << categorias[i] << "  | $"
             << setw(11) << fixed << setprecision(2) << preciosLista[i] << " | $"
             << setw(11) << fixed << setprecision(2) << preciosVenta[i] << " |\n";
    }
    cout << "+-----+--------+----------+-----+--------------+--------------+\n";
    cout << "Total medicamentos en inventario: " << tam << ".\n";
}
