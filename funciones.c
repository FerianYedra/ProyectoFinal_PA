#include "def.h"
/**
 * @file funciones.c
 * @brief Esta funcion agrega los alumnos leídos a una lista FIFO en la lista circular doble.
 * @author Fernando Yedra
 * @date 26/03/2021
 * @param pt	Es la información de la lista FIFO
 * @param dat	Contiene la información del alumno
 * @return pt	Es el inicio de la lista FIFO
 */
extern nodito *anexarFIFO(nodito *pt, info dat){
	nodito *aux, *mover;
	mover = pt;
	aux = (nodito *)malloc(sizeof(nodito));
	if(aux == NULL){
		printf("Error: no hay memoria disponible\n");
		exit(1);
	}
	aux->cuenta = dat.cta;
	strcpy(aux->nombre, dat.nom);
	strcpy(aux->carrera, dat.car);
	aux->promedio = dat.prom;
	aux->next = NULL;
	if(pt == NULL){
		pt = aux;
	}else{
		while(mover->next != NULL){
			mover = mover->next;
		}
		mover->next = aux;
	}

	return pt;
}

/**
 * @brief Esta función revisa que la carrera del alumno ya exista, manda añadir al FIFO si encuentra.
 * @author Fernando Yedra
 * @date 26/03/2021
 * @param pt	Es la referencia a la lista circular
 * @param dat	Contiene la información del alumno
 * @reuturn 0	Si no encuentra la carrera en la lista, 1 Si encuentra la carrera
 */

extern int revisarMaterias(nodo *pt, info dat){
	nodo *aux = pt;
	int i = 0;
	
	do{
		if(strcmp(dat.car, pt->carrera) == 0){
			pt->fifo = anexarFIFO(pt->fifo, dat);
			i = 1;
		}
		pt = pt->der;
	}while(pt->der != aux);
	pt = aux;

	return i;
}

/**
 * @brief Esta función manda a anaexar a la lista circular, revisa que si la carrera esta repetida
 * 	  no se agregue el nodo.
 * @author Fernando Yedra, Nancy Melina
 * @date 26/03/2021
 * @param pt	Es la referencia al incio de la lista
 * @param dat	Contiene la información del alumno
 * @return pt	Regresa el inico de la lista
 */

extern nodo *crearListaDoble(nodo *pt, info dat)
{
  nodo *nuevo, *aux = pt;

  nuevo=(nodo *)malloc(sizeof(nodo));
  nuevo->fifo = NULL;
  if(nuevo == NULL)
   {
	   printf("\nNo hay memoria disponible");
	   exit(1);
   }
  strcpy(nuevo->carrera, dat.car);
  if(pt == NULL)
  {
	  pt=nuevo;
	  nuevo->der=pt;
	  nuevo->izq=pt;
	  nuevo->fifo = anexarFIFO(nuevo->fifo, dat);
  }else{
	  if(revisarMaterias(pt, dat) == 1){
		free(nuevo);
	  }else{
	  	aux=pt->izq;
          	nuevo->izq=aux;
          	nuevo->der=pt;
          	pt->izq=nuevo;
          	aux->der=nuevo;
		nuevo->fifo = anexarFIFO(nuevo->fifo, dat);
	  }
    }

  return pt;
}

/**
 * @brief Esta función manda a imprimir la lista fifo que se encuentre en un nodo.
 * @author Fernando Yedra, Nancy Melina
 * @date 26/03/2021
 * @param pt	Es la referencia al inicio de la lista FIFO en un nodo
 * @return void
 */

extern void imprimirFIFO(nodito *pt){
	nodito *aux = pt;
	printf("Imprimiendo carrera\n");
	while(aux != NULL){
		printf("\n----------------\n %i\n %s\n %s\n %f\n",aux->cuenta,aux->nombre,aux->carrera,aux->promedio);
		aux = aux->next;
	}
	printf("Fin de la lista\n");

	return;
}

/**
 * @brief Esta función manda a evaluar los datos en la lista FIFO para agregarlos al nodo.
 * @author Fernando Yedra
 * @date 26/03/2021
 * @param pt	Es la referencia al nodo acutal
 * @return void
 */

extern void fetchInfo(nodo *pt){
	nodito *inicioFIFO = pt->fifo;
	float sum = 0.0;
	float promPasado = pt->fifo->promedio;
	
	pt->alumnos = 0;
	nodo *aux = pt;
	while(aux->fifo != NULL){
		pt->alumnos++;
		sum += pt->fifo->promedio;
		if(pt->fifo->promedio >= promPasado){
			strcpy(pt->mejor, pt->fifo->nombre);
		}
		promPasado = pt->fifo->promedio;
		aux->fifo = aux->fifo->next;
	}
	pt->fifo = inicioFIFO;
	pt->prom = sum/(float)pt->alumnos;
	
	return;
}

/**
 * @brief Esta función manda a crear un archivo de nombre "listas.txt" con los datos de la estrucutra
 * @author Fernando Yedra, Nancy Melina
 * @date 26/03/2021
 * @param pt	Es la referencia al inicio de la lista circular.
 * @return void
 */

extern void generarReporte(nodo *pt){
	nodo *aux = pt;
	FILE *fp;

	fp = fopen("listas.txt", "w");
	if (fp == NULL) {
		printf("Error: Archivo no disponible\n");
		exit(1);
	}
	do{
		fetchInfo(aux);
		fprintf(fp, "%s\t%i\t%f\t%s\n", aux->carrera, aux->alumnos, aux->prom, aux->mejor);
		while(aux->fifo != NULL){
			fprintf(fp, "%i\t%s\t%f\n", aux->fifo->cuenta, aux->fifo->nombre, aux->fifo->promedio);
			aux->fifo = aux->fifo->next;
		}
		aux = aux->izq;
	}while (aux->izq != pt);
	fclose(fp);

	return;
}
