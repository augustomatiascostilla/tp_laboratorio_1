/*
 * utn_inpus.h
 *
 *  Created on: 5 abr. 2022
 *      Author: Augusto Matias Costilla
 */

#ifndef UTN_H_
#define UTN_H_
#define TEXT_MENU "1. Ingresar Kilómetros:\n2. Ingresar Precio de Vuelos:\n3. Calcular todos los costos:\n4. Informar Resultados\n5. Carga forzada de datos\n6. Salir\n"
#define TEXT_ERROR "Error, opcion no valida, vuelva a intentarlo... \n\n"

int utn_getInt(int*, char*, char*, int, int, int);
int utn_getFloat(float*, char*, char*, float, float, int);

int ObtenerKM(int*);
int MenuPrecios(float*, float*);
void CalcularCostos(int, float, float*, int, int);
void InformarResultados(int, float, float, float*, float*);
void CargaForzada(void);
#endif /* UTN_H_ */
