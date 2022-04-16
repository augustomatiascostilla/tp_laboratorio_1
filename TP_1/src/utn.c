/*
 * utn_inpus.c
 *
 *  Created on: 5 abr. 2022
 *      Author: Augusto Matias Costilla
 */
#include <stdio.h>
#include <stdlib.h>

#define TEXT_MENU_PRECIOS "1. Ingresar Precio de Vuelo en Aerolineas:\n2. Ingresar Precio de Vuelo el Latam:\n3. Volver al Menu Anterior\n"
#define TEXT_MENU_ERRPREC "Error! opcion no valida\nVuelva a intentarlo...\n"


/******************************************************************************************/
/************************************{INPUTS}**********************************************/
/******************************************************************************************/


/// \brief pide un numero, lo valida en un determinado rango y lo escribe en un puntero
/// \param pResultado: pundero donde se escribe el numero obtenido
/// \param mensaje: mensaje para pedir numero
/// \param error: mensaje en caso de haber ingresado opcion no valida
/// \param min: menor numero admitido
/// \param max: mayor numero admitido
/// \param intentos: cantidad de intentos permitidos
/// \return -1 en caso de agotar intentos, 0 en caso de poder obtener el numero
int utn_getInt(int* pResultado, char* mensaje, char* error, int min, int max, int intentos){
	int ret=-1;
	int bufferInt;
	if(pResultado!=NULL && mensaje!=NULL && error!=NULL && min<=max && intentos>0){
		while(intentos>0){
			printf("%s",mensaje);
			scanf("%d",&bufferInt);
			if(bufferInt<=max && bufferInt>=min){
				*pResultado=bufferInt;
				ret=0;
				break;
			}
			printf("%s",error);
			intentos--;
			fflush(stdin);
		}
	}
	return ret;
}

int utn_getFloat(float* pResultado, char* mensaje, char* error, float min, float max, int intentos){
	int ret=-1;
	float bufferFloat;
	if(pResultado!=NULL && mensaje!=NULL && error!=NULL && min<=max && intentos>0){
		while(intentos>0){
			printf("%s",mensaje);
			scanf("%f",&bufferFloat);
			if(bufferFloat<=max && bufferFloat>=min){
				*pResultado=bufferFloat;
				ret=0;
				break;
			}
			printf("%s",error);
			intentos--;
			fflush(stdin);
		}
	}
	return ret;
}

/*****************************************************************************************/


int ObtenerKM(int* pResultado){
	int ret=0, buffer;
	if(utn_getInt(&buffer, "Ingrese los kilometros recorridos en el vuelo...\n",
			"Error! fuera de rango [2-15000], vuelva a intentarlo\n", 2, 15000, 4)==0)
	{
		ret=1;
		*pResultado=buffer;
		printf("\nlos kilometros fueron ingresados con exito\n\n");
	}

	return ret;
}

int ObtenerPrecios(float* pResultado, char* msje){
	int ret=0;
	float buffer;
	if(utn_getFloat(&buffer, msje,
			"Error! fuera del rango de precios [1000-30000], vuelva a intentarlo\n", 1000.0, 30000.0, 4)==0)
	{
		ret=1;
		*pResultado=buffer;
	}

	return ret;
}

int MenuPrecios(float* pResultado1, float* pResultado2){
	int ret=0, opcion, f1=0, f2=0, repeat=1;
	float buffer1, buffer2;

	while(repeat){
		if(utn_getInt(&opcion,TEXT_MENU_PRECIOS, TEXT_MENU_ERRPREC, 1, 3, 4)==0){
			switch(opcion){
			case 1:
				f1=ObtenerPrecios(&buffer1,"Ingrese el Precio del Vuelo en Aerolineas\n");
				break;
			case 2:
				f2=ObtenerPrecios(&buffer2,"Ingrese el Precio del Vuelo en Latam\n");
				break;
			case 3:
				repeat=0;
				break;
			}
		}else{
			repeat=0;
		}

		if(f1 && f2){
			printf("\nLos precios de ambas empresas fueron tomados con exito.\n\n");
			*pResultado1=buffer1;
			*pResultado2=buffer2;
			repeat=0;
			ret=1;
		}
	}
	return ret;
}

/***************************************************************************************/

float CalcularDescuento(float prec, int desc){
	float descuento=prec/100*desc;
	prec=prec-descuento;

	return prec;
}

float CalcularInteres(float prec, int inter){
	float interes=prec/100*inter;
	prec=prec+interes;

	return prec;
}

float CalcularPrecioBitcoin(float prec){
	const float bitcoin=4606954.55;
	float precioAPesos=prec/bitcoin;

	return precioAPesos;
}

float CalcularPrecioUnitario(float prec, int km){
	float precioUnitario=prec/km;

	return precioUnitario;
}

void CalcularCostos(int km, float precio, float aResultados[], int descuento, int interes){
	//0=debito, 1=credito, 2=bitcoin, 3=precio unitario
	int i;
	for(i=0; i<4; i++){
		switch(i){
		case 0:
			aResultados[i]=CalcularDescuento(precio, descuento);
			break;
		case 1:
			aResultados[i]=CalcularInteres(precio, interes);
			break;
		case 2:
			aResultados[i]=CalcularPrecioBitcoin(precio);
			break;
		case 3:
			aResultados[i]=CalcularPrecioUnitario(precio, km);
			break;

		}
	}
}

/**********************************************************************************************/

void InformarResultados(int kilometros, float precioA, float precioL, float* preciosA, float* preciosL){

	printf("\nKMs Ingresados: %d km\n\n", kilometros);

	printf("Precio Aerolineas $%.2f\n", precioA);
	printf("a) Precio con tarjeta de debito: $ %.2f\n", preciosA[0]);
	printf("b) Precio con tarjeta de credito: $ %.2f\n", preciosA[1]);
	printf("c) Precio pagando con bitcoin: %f BTC\n", preciosA[2]);
	printf("d) Mostrar Precio unitario $ %f\n\n", preciosA[3]);
	printf("Precio Latam: %.2f\n", precioL);
	printf("a) Precio con tarjeta de debito: $ %.2f\n", preciosL[0]);
	printf("b) Precio con tarjeta de credito: $ %.2f\n", preciosL[1]);
	printf("c) Precio pagando con bitcoin: %f BTC\n", preciosL[2]);
	printf("d) Mostrar Precio unitario: $ %f\n\n", preciosL[3]);

	if(precioA > precioL){
		printf("la diferencia de precio es: $ %.2f\n\n", precioA-precioL);
	}else{
		if(precioA < precioL){
			printf("la diferencia de precio es: $ %.2f\n\n", precioL-precioA);
		}else{
			printf("No hay diferencia de precio\n\n");
		}
	}
}

/*******************************************************************************/


void CargaForzada(void){
	int km=7090;
	float aerolineas=162965;
	float latam=159339;
	float costosA[4];
	float costosL[4];

	CalcularCostos(km, aerolineas, costosA, 10, 25);
	CalcularCostos(km, latam, costosL, 10, 25);

	InformarResultados(km, aerolineas, latam, costosA, costosL);
}





















