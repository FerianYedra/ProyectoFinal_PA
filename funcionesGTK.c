#include "def.h"

nodo *listaCircular(nodo *pt, info dat){
	nodo *nuevo, *aux;
	int i = 0;

	aux = pt;
	nuevo = (nodo *)malloc(sizeof(nodo));
	if(nuevo == NULL){
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
		if(i == 0){
			aux = pt->izq;
			nuevo->izq = aux;
			nuevo->der = pt;
			pt->izq = nuevo;
			aux->der = nuevo;
			printf("Se guardo %s\n", dat.car);
		}
		else{
			free(nuevo);
			printf("No se guardo %s (repetido)\n", nuevo->carrera);
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
		printf("Se guardo %s\n", aux->nombre);
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
			printf("Se mando a guardar %s en %s\n", dat.nom, aux->carrera);
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
		printf("Se guardo %i\n", nuevo->cuenta);
	}
	while(aux != NULL && salir != 0){
		if(aux->cuenta > nuevo->cuenta){
			if(aux->der != NULL){
				aux = aux->der;
			}else{
				aux->der = nuevo;
				printf("Se guardo %i\n", nuevo->cuenta);
				salir = 0;
			}
		}
		if(aux->cuenta < nuevo->cuenta){
			if(aux->izq != NULL){
				aux = aux->izq;
			}else{
				aux->izq = nuevo;
				printf("Se guardo %i\n", nuevo->cuenta);
				salir = 0;
			}
		}
		if(aux->cuenta == nuevo->cuenta){
			printf("El alumno con la cuenta %i esta repetido, omitiendo\n", dat.cta);
			free(nuevo);
			salir = 0;
		}
	}
	return pt;
}

void actualizarNodos(nodo *pt){
	nodo *aux = pt;
	nodito *lista;
	float prom = 0, sum = 0, mejor;

	do{
		printf("Se esta revisando %s\n", aux->carrera);
		lista = aux->fifo;
		strcpy(aux->mejor, lista->nombre);
		sum = lista->promedio;
		aux->alumnos = 1;
		mejor = lista->promedio;
		lista = lista->next;
		while(lista != NULL){
			sum += lista->promedio;
			prom = lista->promedio;
			if(prom > mejor){
				strcpy(aux->mejor, lista->nombre);
				mejor = prom;
			}
			aux->alumnos++;
			lista = lista->next;
		}
		aux->prom = sum / aux->alumnos;
		aux = aux->der;
	}while(aux != pt);
	return;
}

void recorrerIzq(GtkButton *btnIzq, gpointer nav){
	return;
}
void recorrerDer(GtkButton *btnIzq, gpointer nav){
	return;
}
void mostrarAlum(GtkButton *btnMostrar, gpointer nav){
	return;
}
void darBaja(GtkButton *btnBaja, gpointer nav){
	return;
}
void close(GtkButton *exit, NULL){
	return;
}
void buscarCta(GtkButton *btnBuscarCta, gpointer root){
	return;
}
void buscarProm(GtkButton *btnBuscarProm, gpointer inicio){
	return;
}
