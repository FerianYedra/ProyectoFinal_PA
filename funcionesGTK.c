#include "def.h"

nodo *listaCircular(nodo *pt, info dat){
	nodo *nuevo, *aux;
	int i = 0;

	aux = pt;
	nuevo = (nodo *)malloc(sizeof(nodo));
	if(nuevo = NULL){
		printf("No hay memoria dispoible\n");
		exit(1);
	}
	strcpy(nuevo->carrera, dat.car);
	nuevo->fifo = NULL;
	if(pt == NULL){
		pt = nuevo;
		nuevo->der = pt;
		nuevo->izq = pt;
		printf("Se guardo %s\n", dat.car);
	}else{
		do{
			if(strcmp(nuevo->carrera, aux->carrera) == 0){
				i = 1;
			}
			aux = aux->der;
		}while(aux != pt);
		if(i = 0){
			aux = pt->izq;
			nuevo->izq = aux;
			nuevo->der = pt;
			pt->izq = nuevo;
			aux->der = nuevo;
			printf("Se guardo %s\n", dat.car);
		}
		else{
			free(nuevo);
		}
	}
	return pt;
}

nodito *pushFIFO(info dat, nodito *pt){
	nodito *aux, *mover = pt;

	aux = (nodito *)malloc(sizeof(nodito));
	if(aux == NULL){
		printf("No hay memoria disponible\n");
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
		printf("Se guardo %s\n", aux->nombre);
	}
	return pt;
}

nodo *listaFIFO(nodo *pt, info dat){
	nodo *aux = pt;
	do{
		if(strcmp(dat.car, aux->carrera) == 0){
			aux->fifo = pushFIFO(dat, aux->fifo);
		}
		aux = aux->der;
	}while(aux != pt);
	return pt;
}

arbol *generarArbol(arbol *pt, info dat){
	arbol *nuevo, *aux = pt;
	int salir = 1;

	nuevo = (arbol *)malloc(sizeof(arbol));
	if(nuevo == NULL){
		printf("No hay meoria disponible\n");
		exit(1);
	}
	nuevo->cuenta = dat.cta;
	strcpy(nuevo->nombre, dat.nom);
	strcpy(nuevo->carrera, dat.car);
	nuevo->prom = dat.prom;
	nuevo->izq = NULL;
	nuevo->der = NULL;
	if(aux == NULL){
		pt = nuevo;
	}
	while(aux != NULL && salir != 0){
		if(dat.cta > nuevo->cuenta){
			if(aux->der != NULL){
				aux = aux->der;
			}else{
				aux->der = nuevo;
				salir = 0;
			}
		}
		if(dat.cta < aux->cuenta){
			if(aux->izq != NULL){
				aux = aux->izq;
			}else{
				aux->izq = nuevo;
				salir = 0;
			}
		}
		if(dat.cta == nuevo->cuenta){
			printf("El alumno con la cuenta %i esta repetido, omitiendo\n", dat.cta);
			free(nuevo);
			salir = 0;
		}
	}
	return pt;
}

