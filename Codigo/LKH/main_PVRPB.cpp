#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <map>
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


void Usar_lkh(string parametro2);
extern "C" int lkh_main(int argc,char *argv[]);
map <int, map <int, vector <int> > > crear_archivo_lkh(string palabra1, string palabra2, int dAtencion, vector <Cliente> datosCliente, Deposito dep, vector <int> contadorEntrega, vector <int> contadorRecogida, map <int, map <int, vector <int> > > rutasSeparadas);



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
	/*ofstream salida1_lkh (nombre_lkh+".par"); //creamos el archivo para usar el lkh
	//Crear archivo ".par"
	salida1_lkh << "PROBLEM_FILE = " << nombre_lkh+".tsp" << endl;
	salida1_lkh << "OPTIMUM = 378032" << endl;
	salida1_lkh << "MOVE_TYPE = 5" << endl;
	salida1_lkh << "PATCHING_C = 3" << endl;
	salida1_lkh << "PATCHING_A = 2" << endl;
	salida1_lkh << "RUNS = 5" << endl;
	salida1_lkh << "OUTPUT_TOUR_FILE  = " << nombre_lkh+".txt" << endl;
	salida1_lkh.close(); */

	nombre_lkh = argv[1]; //se vuelve a actualizar la variable en caso de error al haberla registrado anteriormente

	//Creamos el archivo donde iran las coordenadas para usar el lkh
	//ofstream salida2_lkh (nombre_lkh+".tsp");
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
	vector <int> contadorEntrega;
	vector <int> contadorRecogida;

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
			for (int i = 0; i < diasAtencion; i++) {

				contadorEntrega.push_back(0);
				contadorRecogida.push_back(0);

			}

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
					if (diacliente == 0) {

						contadorEntrega[contDatos] = contadorEntrega[contDatos]+1;

					}

					else if (diacliente == 1) {

						contadorRecogida[contDatos] = contadorRecogida[contDatos]+1;

					}

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
	string baseNombreArchivoEntrega = "archivo_entrega_dia_";
	string baseNombreArchivoRecogida = "archivo_recogida_dia_";
	string nombreArchivoCompletoEntrega;
	string nombreArchivoCompletoRecogida;
	int sumaDia = 1;
	string nombreDia;
	map <int, map <int, vector <int> > > rutasSeparadas; //almacena los datos segun fueron utilizados en los archivos LKH

	for (int i = 0; i < diasAtencion; i++) {

		nombreDia = to_string(sumaDia);
		nombreArchivoCompletoEntrega = baseNombreArchivoEntrega+nombreDia;
		nombreArchivoCompletoRecogida = baseNombreArchivoRecogida+nombreDia;	
		rutasSeparadas = crear_archivo_lkh(nombreArchivoCompletoEntrega,nombreArchivoCompletoRecogida, i, datosCliente, dep, contadorEntrega, contadorRecogida, rutasSeparadas);
		sumaDia++;

	}



	/*
	*
	*
	*		FIN rutas iniciales con LKH
	*
	*/



}


void Usar_lkh(string parametro2){

	char lkh_exe[] = "lkh_main";
	char lkh_param[1024];
	strcpy(lkh_param, (parametro2).c_str());

	char *lkh_argv[] = { lkh_exe , lkh_param };
	lkh_main(2,lkh_argv);
}

map <int, map <int, vector <int> > > crear_archivo_lkh(string palabra1, string palabra2, int dAtencion, vector <Cliente> datosCliente, Deposito dep, vector <int> contadorEntrega, vector <int> contadorRecogida, map <int, map <int, vector <int> > > rutasSeparadas) {


    //Creo el archivo .par pero para ser usada con la ruta y el deposito
	ofstream ArchivoParEntrega (palabra1+".par");

	ArchivoParEntrega << "PROBLEM_FILE = " << palabra1+".tsp" << endl;
	//ArchivoParEntrega << "OPTIMUM = 378032" << endl;
	//ArchivoParEntrega << "MOVE_TYPE = 5" << endl;
	//ArchivoParEntrega << "PATCHING_C = 3" << endl;
	//ArchivoParEntrega << "PATCHING_A = 2" << endl;
	ArchivoParEntrega << "TRACE_LEVEL = 0" << endl;
	ArchivoParEntrega << "GAIN23 = NO" << endl;
	ArchivoParEntrega << "RUNS = 5" << endl;
	ArchivoParEntrega << "OUTPUT_TOUR_FILE  = " << palabra1+".txt" << endl;

	ArchivoParEntrega.close();

	ofstream ArchivoParRecogida (palabra2+".par");

	ArchivoParRecogida << "PROBLEM_FILE = " << palabra2+".tsp" << endl;
	//ArchivoParRecogida << "OPTIMUM = 378032" << endl;
	//ArchivoParRecogida << "MOVE_TYPE = 5" << endl;
	//ArchivoParRecogida << "PATCHING_C = 3" << endl;
	//ArchivoParRecogida << "PATCHING_A = 2" << endl;
	ArchivoParRecogida << "TRACE_LEVEL = 0" << endl;
	ArchivoParRecogida << "GAIN23 = NO" << endl;
	ArchivoParRecogida << "RUNS = 5" << endl;
	ArchivoParRecogida << "OUTPUT_TOUR_FILE  = " << palabra2+".txt" << endl;

	ArchivoParRecogida.close();


	/*double Mejor_Distancia = 1000000;
	int Deposito_temporal;
	vector<int> Casi_Definitiva;*/

	//for(map<int,Deposito>::iterator iter = D.begin() ; iter != D.end(); iter++){


        //Creo el archivo .tsp para cada ruta con el deposito
		ofstream ArchivoTspEntrega (palabra1+".tsp");

		ArchivoTspEntrega << "NAME : " << palabra1 << endl;
		ArchivoTspEntrega << "COMMENT : 2392-city problem (Padberg/Rinaldi)" << endl;
		ArchivoTspEntrega << "TYPE : TSP" << endl;
		ArchivoTspEntrega << "DIMENSION : " << (contadorEntrega[dAtencion]+1) << endl;
		ArchivoTspEntrega << "EDGE_WEIGHT_TYPE : EUC_2D" << endl;
		ArchivoTspEntrega << "NODE_COORD_SECTION" << endl;

		ArchivoTspEntrega << "1" << " " << dep.x << " " << dep.y << endl;

		int contEntrega = 2;
		rutasSeparadas[dAtencion];
		vector <int> rutaL;

		for(int i = 0 ; i < datosCliente.size() ; i++) {

			if (datosCliente[i].dia[dAtencion] == 0) {

				ArchivoTspEntrega <<  contEntrega << " " << datosCliente[i].x << " " << datosCliente[i].y << endl;
				contEntrega++;
				rutaL.push_back(datosCliente[i].numero);
			}

		}

		rutasSeparadas[dAtencion][0] = rutaL;
		
		ArchivoTspEntrega.close();

        //Uso el lkh de la ruta con el deposito
		Usar_lkh(palabra1+".par");

		ofstream ArchivoTspRecogida (palabra2+".tsp");

		ArchivoTspRecogida << "NAME : " << palabra2 << endl;
		ArchivoTspRecogida << "COMMENT : 2392-city problem (Padberg/Rinaldi)" << endl;
		ArchivoTspRecogida << "TYPE : TSP" << endl;
		ArchivoTspRecogida << "DIMENSION : " << (contadorRecogida[dAtencion]+1) << endl;
		ArchivoTspRecogida << "EDGE_WEIGHT_TYPE : EUC_2D" << endl;
		ArchivoTspRecogida << "NODE_COORD_SECTION" << endl;

		ArchivoTspRecogida << "1" << " " << dep.x << " " << dep.y << endl;

		int contRecogida = 2;
		vector <int> rutaB;

		for(int i = 0 ; i < datosCliente.size() ; i++){

			if (datosCliente[i].dia[dAtencion] == 1) {

				ArchivoTspRecogida <<  contRecogida << " " << datosCliente[i].x << " " << datosCliente[i].y << endl;
				contRecogida++;
				rutaB.push_back(datosCliente[i].numero);
			}

		}

		rutasSeparadas[dAtencion][1] = rutaB;
		
		ArchivoTspRecogida.close();

        //Uso el lkh de la ruta con el deposito
		Usar_lkh(palabra2+".par");

		//Leo el archivo de la ruta hecha por el lkh
		/* 
		ifstream datosRuta (palabra+".txt");
		vector<int> Mini_Ruta;
		string linea;
		getline(datosRuta,linea);
		getline(datosRuta,linea);
		getline(datosRuta,linea);
		getline(datosRuta,linea);
		getline(datosRuta,linea);
		getline(datosRuta,linea);
		getline(datosRuta,linea); // NO GUARDO EL DEPOSITO

		while(!datosRuta.eof()){

			getline(datosRuta,linea);
			if (linea == "-1") break;

			Mini_Ruta.push_back(atoi(linea.c_str()));

		}
		datosRuta.close();


		double distancia;
		distancia = Distancia_Clientes(L,Mini_Ruta,C);

		double distancia_Deposito_clientes;

		//Hago la suma de la distancia del deposito al primer y ultimo cliente
		distancia_Deposito_clientes =(double) distancia + sqrt(pow(C[L[Mini_Ruta[0]-2]-1].x - iter->second.x,2.0)+
		pow(C[L[Mini_Ruta[0]-2]-1].y - iter->second.y,2.0))+sqrt(pow(C[L[Mini_Ruta[Mini_Ruta.size()-1]-2]-1].x - iter->second.x,2.0)
		+pow(C[L[Mini_Ruta[Mini_Ruta.size()-1]-2]-1].y - iter->second.y,2.0));


        //voy guardando en que deposito deberia ir esa ruta dependiendo de la distancia minima
		if(distancia_Deposito_clientes < Mejor_Distancia && asignacion[iter->first].size() < vehiculos){
			Mejor_Distancia = distancia_Deposito_clientes;
			Deposito_temporal = iter->first;
			Casi_Definitiva = Mini_Ruta;

		}

	}
	vector<int> Definitivo;
	int demanda = 0;
	Definitivo.push_back(Deposito_temporal);
	for(int i = 0 ; i < Casi_Definitiva.size() ; i++){
		Definitivo.push_back(L[Casi_Definitiva[i]-2]);
        demanda = demanda+C[L[Casi_Definitiva[i]-2]-1].demanda;
	}
    Definitivo.push_back(Deposito_temporal);
	cout << endl;


    //cuando se a que deposito pertenece la guardo de manera definitiva.
	asignacion[Deposito_temporal][numero_ruta] = Definitivo;
	distancia_rutas[numero_ruta] = (double)Mejor_Distancia;
	Ruta_demanda[numero_ruta] = demanda; */

	return rutasSeparadas;

}