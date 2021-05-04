/**
 * @file reporteAlumnos.c
 * @brief Este programa genera una estructura a partir de una lista de alumnos, clasificada por
 * 	  carrera, la lista la lee de un archivo .txt con estrucutra
 * 	  <#cuenta>	<Nombre>	<Carrera>	<promedio>\n
 * 	  Los alumnos de la misma carrera se asignan a una lista FIFO, se calcula la carrera, la
 * 	  canitdad de alumnoes en esa carrera, el promedio general, el mejor estudiante.
 * 	  Un navegador permite navegar la estructura de listas, se puede mostrar los alumnos,
 * 	  moverse a la izquierda, derecha y salir, al salir se puede generar un reporte, este es un
 * 	  archivo de nombre "lista.txt" que contiene la información recopilada.
 * @author Fernando Yedra, Nancy Melina
 * @date 26/03/2021
 */

#include "def.h"
extern nodo *crearListaDoble(nodo *pt, info dat;);
extern void imprimirFIFO(nodito *pt);
extern void fetchInfo(nodo *pt);
extern void generarReporte(nodo *pt);

int main(int argc, char *argv[]){
	info dat;
	nodo *inicio;
	FILE *fp;
	int i = 0, j;
	navegador nav;
	char opcion;

	inicio = NULL;
	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("Error: Archivo no dispoible\n");
		exit(1);
	}
	fclose(fp);
	for(j = 0;j <= 26; j++){
		fp = fopen(argv[1], "r");
		while(fscanf(fp, "%i %[^\t] %[^\t] %f\n", &dat.cta, dat.nom, dat.car, &dat.prom)==4){
			if(dat.nom[0] == 65+j){
				inicio = crearListaDoble(inicio, dat);
				i++;
			}
		}
		fclose(fp);
	}
	printf("Se leyeron %i alumnos\n", i);
	inicio = inicio->izq;
	fetchInfo(inicio);
	//Implementar Navegador
	nav.pos = inicio;
	while(opcion != 's'){
		nav.list = nav.pos->fifo;
		fetchInfo(nav.pos);
		printf("+++++++Menu++++++\n");
		printf("Estas en: %s\n", nav.pos->carrera);
		printf("Tiene: %i alumnos\n", nav.pos->alumnos);
		printf("Promedio general: %f\n", nav.pos->prom);
		printf("El mejor alumno es: %s\n", nav.pos->mejor);
		printf("+++++++++++++++++\n");
		printf("1)\t[i]zq\n");
		printf("2)\t[d]er\n");
		printf("3)\t[m]ostrar\n");
		printf("4)\t[s]alir\n");
		printf("Seleccionar opción: ");
		scanf(" %c", &opcion);
		switch(opcion){
			case 's':
				printf("Saliendo...\n");
				printf("Generar reporte [s/n]? ");
				scanf(" %c", &opcion);
				if(opcion == 's'){
					generarReporte(inicio);
				}
				else{
					printf("No se genereara reporte\n");
					opcion = 's';
					break;
				}
				break;
			case 'i':
				nav.pos = nav.pos->izq;
				break;
			case 'd':
				nav.pos = nav.pos->der;
				break;
			case 'm':
				imprimirFIFO(nav.list);
				break;
			default:
				printf("Opcion invalida\n");
				break;
		}
	}

	return 0;
}
