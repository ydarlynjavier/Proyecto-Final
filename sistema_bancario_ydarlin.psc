Proceso SistemaBancario
    // Declaración de constantes y variables globales
    Definir MAX_CLIENTES, numClientes Como Entero;
    MAX_CLIENTES <- 100;
    numClientes <- 0;
	
    // Declaración de matrices para almacenar datos de los clientes
    Dimension clientesID(MAX_CLIENTES);
    Dimension clientesNombre(MAX_CLIENTES);
    Dimension clientesSaldo(MAX_CLIENTES);
	
    // Iniciar el proceso con el login
    login(numClientes, clientesID, clientesNombre, clientesSaldo);
	
FinProceso

Subproceso login(numClientes, clientesID, clientesNombre, clientesSaldo)
    Definir clave, claveIngresada Como Caracter;
    Definir intentos Como Entero;
    intentos <- 0;
    clave <- "1234"; // Clave predeterminada
	
    Mientras intentos < 3 Hacer
        Escribir "Ingrese su clave: ";
        Leer claveIngresada;
        Si clave = claveIngresada Entonces
            Escribir "Login exitoso";
            menu(numClientes, clientesID, clientesNombre, clientesSaldo);
        SiNo
            Escribir "Clave incorrecta";
            intentos <- intentos + 1;
        FinSi
    FinMientras
FinSubproceso

Subproceso registrarCliente(numClientes, clientesID, clientesNombre, clientesSaldo)
    Definir nombre Como Caracter;
    Si numClientes >= MAX_CLIENTES Entonces
        Escribir "No se pueden agregar más clientes.";
	FinSi

	numClientes <- numClientes + 1;
	clientesID(numClientes) <- numClientes;

	Escribir "Ingrese el nombre del cliente: ";
	Leer nombre;
	clientesNombre(numClientes) <- nombre;

	clientesSaldo(numClientes) <- 0.0;

	Escribir "Cliente registrado con éxito. ID del cliente: ", clientesID(numClientes);
FinSubproceso

Subproceso depositar(numClientes, clientesID, clientesNombre, clientesSaldo)
    Definir id Como Entero;
    Definir monto Como Real;
	
    Escribir "Ingrese el ID del cliente: ";
    Leer id;
	
    Si id < 1 O id > numClientes Entonces
        Escribir "Cliente no encontrado.";
	FinSi

	Escribir "Ingrese el monto a depositar: ";
	Leer monto;

	clientesSaldo(id) <- clientesSaldo(id) + monto;

	Escribir "Depósito realizado con éxito. Nuevo saldo: ", clientesSaldo(id);
FinSubproceso

Subproceso retirar(numClientes, clientesID, clientesNombre, clientesSaldo)
    Definir id Como Entero;
    Definir monto Como Real;
	
    Escribir "Ingrese el ID del cliente: ";
    Leer id;
	
    Si id < 1 O id > numClientes Entonces
        Escribir "Cliente no encontrado.";
	FinSi

	Escribir "Ingrese el monto a retirar: ";
	Leer monto;

	Si clientesSaldo(id) >= monto Entonces
		clientesSaldo(id) <- clientesSaldo(id) - monto;
		Escribir "Retiro realizado con éxito. Nuevo saldo: ", clientesSaldo(id);
	SiNo
		Escribir "Saldo insuficiente.";
	FinSi
FinSubProceso


Subproceso consultarSaldo(numClientes, clientesID, clientesNombre, clientesSaldo)
    Definir id Como Entero;
	
    Escribir "Ingrese el ID del cliente: ";
    Leer id;
	
    Si id < 1 O id > numClientes Entonces
        Escribir "Cliente no encontrado.";
FinSi

Escribir "Cliente: ", clientesNombre(id), " - Saldo actual: ", clientesSaldo(id);
FinSubproceso

Subproceso menu(numClientes, clientesID, clientesNombre, clientesSaldo)
    Definir opcion Como Entero;
    Repetir
        Escribir "=== Menú Principal ===";
        Escribir "1. Registrar cliente";
        Escribir "2. Depositar";
        Escribir "3. Retirar";
        Escribir "4. Consultar saldo";
        Escribir "5. Salir";
        Escribir "Seleccione una opción: ";
        Leer opcion;
		
        Segun opcion Hacer
            Caso 1:
                registrarCliente(numClientes, clientesID, clientesNombre, clientesSaldo);
            Caso 2:
                depositar(numClientes, clientesID, clientesNombre, clientesSaldo);
            Caso 3:
                retirar(numClientes, clientesID, clientesNombre, clientesSaldo);
            Caso 4:
                consultarSaldo(numClientes, clientesID, clientesNombre, clientesSaldo);
            Caso 5:
                Escribir "Saliendo del programa...";
            De Otro Modo:
                Escribir "Opción inválida.";
        FinSegun
    Hasta Que opcion = 5
FinSubproceso
