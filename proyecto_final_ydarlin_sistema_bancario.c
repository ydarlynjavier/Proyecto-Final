#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 100
#define FICHERO_TRANSACCIONES "transacciones.txt"
#define FICHERO_CLIENTES "clientes.txt"
#define FICHERO_CLAVE "clave.txt"

typedef struct {
    int id;
    char nombre[50];
    float saldo;
    char producto[50]; // Producto asociado al cliente
} Cliente;

Cliente clientes[MAX_CLIENTES];
int numClientes = 0;

// Prototipos
void login();
void menu();
void registrarCliente();
void depositar();
void retirar();
void consultarSaldo();
void cambiarClave();
void guardarTransaccion(int id, const char *transaccion, float monto);
void guardarClientesEnArchivo();

int main() {
    login();
    return 0;
}

void login() {
    char clave[10], claveIngresada[10];
    int intentos = 0;

    FILE *archivo = fopen(FICHERO_CLAVE, "r");
    if (!archivo) {
        archivo = fopen(FICHERO_CLAVE, "w");
        fprintf(archivo, "1234"); // Clave predeterminada
        fclose(archivo);
        archivo = fopen(FICHERO_CLAVE, "r");
    }
    fscanf(archivo, "%s", clave);
    fclose(archivo);

    while (intentos < 3) {
        printf("Ingrese su clave: ");
        scanf("%s", claveIngresada);
        if (strcmp(clave, claveIngresada) == 0) {
            printf("Login exitoso\n");
            menu();
            return;
        } else {
            printf("Clave incorrecta\n");
            intentos++;
        }
    }
    printf("Demasiados intentos fallidos. Programa finalizado.\n");
}

void menu() {
    int opcion;
    do {
        printf("\n=== Menu Principal ===\n");
        printf("1. Registrar cliente\n");
        printf("2. Depositar\n");
        printf("3. Retirar\n");
        printf("4. Consultar saldo\n");
        printf("5. Cambiar clave\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: registrarCliente(); break;
            case 2: depositar(); break;
            case 3: retirar(); break;
            case 4: consultarSaldo(); break;
            case 5: cambiarClave(); break;
            case 6: printf("Saliendo del programa...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 6);
}

void registrarCliente() {
    if (numClientes >= MAX_CLIENTES) {
        printf("No se pueden agregar mas clientes.\n");
        return;
    }
    Cliente nuevoCliente;
    nuevoCliente.id = numClientes + 1;
    printf("Ingrese el nombre del cliente: ");
    scanf(" %[^\n]s", nuevoCliente.nombre);
    printf("Ingrese el producto asociado al cliente: ");
    scanf(" %[^\n]s", nuevoCliente.producto);
    nuevoCliente.saldo = 0.0;
    clientes[numClientes++] = nuevoCliente;
    printf("Cliente registrado con ID %d.\n", nuevoCliente.id);
    guardarClientesEnArchivo();
}

void depositar() {
    int id;
    float monto;
    printf("Ingrese el ID del cliente: ");
    scanf("%d", &id);
    if (id < 1 || id > numClientes) {
        printf("Cliente no encontrado.\n");
        return;
    }
    printf("Ingrese el monto a depositar: ");
    scanf("%f", &monto);
    clientes[id - 1].saldo += monto;
    printf("Deposito exitoso. Nuevo saldo: %.2f\n", clientes[id - 1].saldo);
    guardarTransaccion(id, "Deposito", monto);
}

void retirar() {
    int id;
    float monto;
    printf("Ingrese el ID del cliente: ");
    scanf("%d", &id);
    if (id < 1 || id > numClientes) {
        printf("Cliente no encontrado.\n");
        return;
    }
    printf("Ingrese el monto a retirar: ");
    scanf("%f", &monto);
    if (clientes[id - 1].saldo < monto) {
        printf("Saldo insuficiente.\n");
    } else {
        clientes[id - 1].saldo -= monto;
        printf("Retiro exitoso. Nuevo saldo: %.2f\n", clientes[id - 1].saldo);
        guardarTransaccion(id, "Retiro", monto);
    }
}

void consultarSaldo() {
    int id;
    printf("Ingrese el ID del cliente: ");
    scanf("%d", &id);
    if (id < 1 || id > numClientes) {
        printf("Cliente no encontrado.\n");
        return;
    }
    printf("Saldo del cliente %s: %.2f\n", clientes[id - 1].nombre, clientes[id - 1].saldo);
}

void cambiarClave() {
    char nuevaClave[10];
    FILE *archivo = fopen(FICHERO_CLAVE, "w");
    if (!archivo) {
        printf("Error al cambiar la clave.\n");
        return;
    }
    printf("Ingrese la nueva clave: ");
    scanf("%s", nuevaClave);
    fprintf(archivo, "%s", nuevaClave);
    fclose(archivo);
    printf("Clave cambiada exitosamente.\n");
}

void guardarTransaccion(int id, const char *transaccion, float monto) {
    FILE *archivo = fopen(FICHERO_TRANSACCIONES, "a");
    if (!archivo) {
        printf("Error al guardar la transaccion.\n");
        return;
    }
    fprintf(archivo, "ID: %d | Cliente: %s | Transaccion: %s | Monto: %.2f\n", 
            clientes[id - 1].id, clientes[id - 1].nombre, transaccion, monto);
    fclose(archivo);
}

void guardarClientesEnArchivo() {
    FILE *archivo = fopen(FICHERO_CLIENTES, "w");
    if (!archivo) {
        printf("Error al guardar los datos de los clientes.\n");
        return;
    }
    for (int i = 0; i < numClientes; i++) {
        fprintf(archivo, "ID: %d | Nombre: %s | Producto: %s | Saldo: %.2f\n",
                clientes[i].id, clientes[i].nombre, clientes[i].producto, clientes[i].saldo);
    }
    fclose(archivo);
    printf("Datos de los clientes guardados exitosamente.\n");
}