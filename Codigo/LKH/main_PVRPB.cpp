#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
//#include <map>
#include <vector>
#include <math.h>
#include <algorithm>
//#include <unordered_map>
//#include <deque>
#include <string.h>
#include <list>

using namespace std;

//Creamos las estructuras para almacenar los datos necesarios de la instancia a trabajar

struct Cliente {

	int numero = 0;
	int x = 0;
	int y = 0;
	vector <int> dia; /*si se quiere acceder al dia 1 de trabajo,
							se debe acceder a la posicion n-1, es decir a la posicion 0 */

	vector <int> demandaDia; /*si se quiere acceder a la demanda del dia 1 de trabajo,
									se debe acceder a la posicion n-1, es decir a la posicion 0 */

	//lo anterior aplica para generar las rutas por vehiculos en los respectivos dias.

};

struct Deposito {

	int numero = 0;
	int x = 0;
	int y = 0;
	int cantVh = 0; //cantidad de vehiculos que posee el deposito
	int capVh = 0; //capacidad de cada vehiculo del deposito

};



int main (int argc, char** argv) {


	if ( argc > 2 ) {

		cout << "Error, cantidad de parametros no valida" << endl;
		return -1;

	}


	if (argv[1] == NULL) {

		cout << "Error, cantidad de parametros no valida. Falta archivo" << endl;
		return -1;

	}


	ifstream datosPVRPB (argv[1]);

	string nombre_lkh;
	nombre_lkh = argv[1]; //se utiliza el nombre de la instancia para dar nombre al archivo para lkh
	string parametro2 = nombre_lkh+".par";
	ofstream salida1_lkh (nombre_lkh+".par"); //creamos el archivo para usar el lkh
	//Crear archivo ".par"
	salida1_lkh << "PROBLEM_FILE = " << nombre_lkh+".tsp" << endl;
	salida1_lkh << "OPTIMUM = 378032" << endl;
	salida1_lkh << "MOVE_TYPE = 5" << endl;
	salida1_lkh << "PATCHING_C = 3" << endl;
	salida1_lkh << "PATCHING_A = 2" << endl;
	salida1_lkh << "RUNS = 5" << endl;
	salida1_lkh << "OUTPUT_TOUR_FILE  = " << nombre_lkh+".txt" << endl;
	salida1_lkh.close();

	nombre_lkh = argv[1]; //se vuelve a actualizar la variable en caso de error al haberla registrado anteriormente

	//Creamos el archivo donde iran las coordenadas para usar el lkh
	ofstream salida2_lkh (nombre_lkh+".tsp");
	string linea;
	vector <Cliente> datosCliente; //se almacenaran los datos de los clientes del archivo
	Deposito dep; //se almacenaran los datos del deposito
	int diasAtencion = 0;

	int dim = 0;
	int cont = 0; //usado para saltar bloques de lectura
	string basura;
	int contDim = 1; //usado para almacenar los datos de cliente y deposito de manera ordenada
	int contCliente = 0;
	int contDatos = 0;
	int demcliente = 0;
	int diacliente = 0;

	while (!datosPVRPB.eof()) { //comenzar la lectura de archivos para almacenar los datos.

		if (cont==0) { //Se salta las 3 primeras lineas que no nos sirven

			getline(datosPVRPB,linea);
			//cout << linea << endl;
			getline(datosPVRPB,linea);
			//cout << linea << endl;
			getline(datosPVRPB,linea);
			//cout << linea << endl;
			cont++;
		}

		if (cont==1) {

			datosPVRPB >> basura;
			datosPVRPB >> basura;
			datosPVRPB >> dim;
			//cout << dim << endl;
			datosPVRPB >> basura;
			datosPVRPB >> basura;
			datosPVRPB >> dep.capVh;
			//cout << dep.capVh << endl;
			datosPVRPB >> basura;
			datosPVRPB >> basura;
			datosPVRPB >> dep.cantVh;
			//cout << dep.cantVh << endl;
			datosPVRPB >> basura;
			datosPVRPB >> basura;
			datosPVRPB >> diasAtencion;
			//cout << diasAtencion << endl;
			datosPVRPB >> linea; //leer la linea NODE_COORD_SECTION
			//cout << linea << endl;
			cont++;

		}

		if (cont==2) {
			while (contDim <= dim) {

				if (contDim == 1){

					datosPVRPB >> dep.numero;
					datosPVRPB >> dep.x;
					datosPVRPB >> dep.y;
					contDim++;
					//cout << dep.numero << " " << dep.x << " " << dep.y << endl;

				}

				else if (contDim > 1) {

					Cliente clPivote; //
					datosPVRPB >> clPivote.numero;
					datosPVRPB >> clPivote.x;
					datosPVRPB >> clPivote.y;

					datosCliente.push_back(clPivote);
					//cout << datosCliente[contCliente].numero << " " << datosCliente[contCliente].x << " " << datosCliente[contCliente].y << endl;
					contCliente++;
					contDim++;

				}


			}

			cont++;
		}

		if (cont==3){

			datosPVRPB >> basura; //leer la linea NODE_DEMANDA_TIPO_7DIAS
			//cout << basura << endl;//NODE_DEMANDA_TIPO_7DIAS
			cont++;
			contCliente = 0; //se igual el contador al numero del primer cliente.
			getline(datosPVRPB,linea); //linea en blanco, error de no se que
			getline(datosPVRPB,linea); //linea en blanco, error de no se que
			//cout << linea << endl;

		}

		if (cont == 4 and contCliente <= (dim-2)) {

			if (datosCliente[contCliente].numero == (contCliente+2)){

				//cout << datosCliente[contCliente].numero << " ";
				datosPVRPB >> demcliente; //solo usado para limpiar la linea del numero del cliente

				while (diasAtencion > contDatos) {

					datosPVRPB >> demcliente;
					datosCliente[contCliente].demandaDia.push_back(demcliente);
					datosPVRPB >> diacliente;
					datosCliente[contCliente].dia.push_back(diacliente);
					//cout << datosCliente[contCliente].demandaDia[contDatos] << " " << datosCliente[contCliente].dia[contDatos] << " ";
					contDatos++;

				}
				//cout << endl;
				contCliente++;
				contDatos = 0;
			}

		}


		else {

			break;

		}


	}

	datosPVRPB.close();

//-----------------------------------------------------------------------------------------------------------------------
	/*
	*
	*		 INICIO Creacion de Matriz de distancias.
	*
	*
	*/


	float Distancias[contCliente][contCliente];
	float dist_calculada=0;

	for(int i=0;i< contCliente ; i++){
		for (int j = 0; j < contCliente; j++) {
			if(j==i){
				Distancias[i][j] = 0;
				Distancias[j][i] = 0;
				break;
			}


			dist_calculada = sqrt( pow(datosCliente[i].x - datosCliente[j].x ,2)
			                     + pow(datosCliente[i].y - datosCliente[j].y ,2));

		   Distancias[i][j] = dist_calculada;
			Distancias[j][i] = dist_calculada;

		}
	}

			/*
			for (int i = 0; i < contCliente; i++) {
				for (int j = 0; j < contCliente; j++) {
					cout << "cliente " << i+1 << " con " << j+1 << " ---> " << Distancias[i][j] << endl;
				}
			}
			*/


	/*
	*
	*		 FIN Creacion de Matriz de distancias.
	*
	*
	*/

//------------------------------------------------------------------------------------------------------------------------

	/*
	*
	*
	*		INICIO rutas iniciales con LKH
	*
	*/




	/*
	*
	*
	*		FIN rutas iniciales con LKH
	*
	*/



}
