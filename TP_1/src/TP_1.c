/*
 ============================================================================
 Name        : TP_1.c
 Author      : Costilla Augusto Matias
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 1 Enunciado
Una agencia de viaje necesita calcular costos para sus vuelos de Latam y Aerolíneas Argentinas para ofrecerlos a sus clientes.
Se deberá ingresar por cada vuelo los km totales y el precio total del mismo.
El objetivo de la aplicación es mostrar las diferentes opciones de pagos a sus clientes.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#define DESCUENTO 10
#define INTERES 25

int main(void) {
	setbuf(stdout, NULL);
	int x;//x=Kilometros
	float y, z;//y=Aerolineas, z=Latam
	float preciosAerolineas[4];//0=debito, 1=credito, 2=bitcoin, 3=precio unitario
	float preciosLatam[4];//0=debito, 1=credito, 2=bitcoin, 3=precio unitario
	int flag1, flag2, flag3;
	int opcion;
	int repetir=1;
	flag1=0;
	flag2=0;
	flag3=0;

	while(repetir){
		if(utn_getInt(&opcion, TEXT_MENU, TEXT_ERROR, 1, 6, 4)==0){
			switch(opcion){
			case 1:
				flag1=ObtenerKM(&x);
				break;
			case 2:
				flag2=MenuPrecios(&y, &z);
				break;
			case 3:
				if(flag1 && flag2){
					CalcularCostos(x, y, preciosAerolineas, DESCUENTO, INTERES);
					CalcularCostos(x, z, preciosLatam, DESCUENTO, INTERES);
					flag3=1;
					printf("\nCostos calculados con exito, vaya a la opcion 4 para ver los resultados\n\n");
				}else{
					if(flag1==1 && flag2==0){
						printf("\nFalta ingresar los precios de los vuelos...\n\n");
					}else{
						if(flag1==0 && flag2==1){
							printf("\nFalta ingresar los Kilometros a recorrer en el vuelo...\n\n");
						}else{
							printf("\nFalta ingresar los precios y los Kilometros a recorrer en el vuelo...\n\n");
						}
					}
				}
				break;
			case 4:
				if(flag3){
					InformarResultados(x, y, z, preciosAerolineas, preciosLatam);
				}else{
					printf("\nDebe seleccionar la opcion 3 para calcular los costos antes de mostrar los resultados\n\n");
				}
				break;
			case 5:
				CargaForzada();
				break;
			case 6:
				repetir=0;
			}
		}else{
			printf("Error! demasiados ingresos no validos");
			repetir=0;
		}
	}

	return EXIT_SUCCESS;
}































