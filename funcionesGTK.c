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

//Aqui inician las funciones para GTK

void closeApp(GtkButton *btnExit, gpointer data){
        gtk_main_quit();
        printf("------Cerrando ventana------\n");
        return;
}

void recorrerIzq(GtkButton *btnIzq, gpointer nav){
	navegador *pt = (navegador *)nav;
	char nAlum[3];
	char cProm[10];
	if(pt->pos == NULL){
                return;
        }
	pt->pos = pt->pos->izq;
	pt->list = pt->pos->fifo;
	sprintf(nAlum, "%i", pt->pos->alumnos);
	sprintf(cProm, "%f", pt->pos->prom);
	gtk_label_set_text(GTK_LABEL(pt->lblResCar), pt->pos->carrera);
	gtk_label_set_text(GTK_LABEL(pt->lblResProm), cProm);
	gtk_label_set_text(GTK_LABEL(pt->lblResMej), pt->pos->mejor);
	gtk_label_set_text(GTK_LABEL(pt->lblResAlum), nAlum);
	return;
}

void recorrerDer(GtkButton *btnIzq, gpointer nav){
	navegador *pt = (navegador *)nav;
        char nAlum[3];
	char cProm[10];
	if(pt->pos == NULL){
                return;
        }
        pt->pos = pt->pos->der;
	pt->list = pt->pos->fifo;
        sprintf(nAlum, "%i", pt->pos->alumnos);
	sprintf(cProm, "%f", pt->pos->prom);
        gtk_label_set_text(GTK_LABEL(pt->lblResCar), pt->pos->carrera);
        gtk_label_set_text(GTK_LABEL(pt->lblResProm), cProm);
        gtk_label_set_text(GTK_LABEL(pt->lblResMej), pt->pos->mejor);
        gtk_label_set_text(GTK_LABEL(pt->lblResAlum), nAlum);
	return;
}

void mostrarAlum(GtkButton *btnMostrar, gpointer nav){
	navegador *pt = (navegador *)nav;
	GtkWidget *tituloMostrar, *boxMostrar, *lblAlumnos;
	nodito *aux = pt->list;
	char tituloM[100], alumnosM[200];
	int i = 0;

	pt->wdwMostrar = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	boxMostrar = gtk_vbox_new(FALSE, 5);
	gtk_window_set_title(GTK_WINDOW(pt->wdwMostrar), "Mostrar Alumnos");
	gtk_container_set_border_width(GTK_CONTAINER(pt->wdwMostrar), 10);
	sprintf(tituloM, "Alumnos en %s\n", pt->pos->carrera);
	tituloMostrar = gtk_label_new(tituloM);
	while(aux != NULL){
		if(i == 0){
			sprintf(alumnosM, "%s\n", aux->nombre);
			i = 1;
		}else{
			sprintf(alumnosM, "%s\n%s\n", alumnosM, aux->nombre);
		}
		aux = aux->next;
	}
	lblAlumnos = gtk_label_new(alumnosM);
	
	gtk_container_add(GTK_CONTAINER(pt->wdwMostrar), boxMostrar);
	gtk_box_pack_start_defaults(GTK_BOX(boxMostrar), tituloMostrar);
	gtk_box_pack_start_defaults(GTK_BOX(boxMostrar), lblAlumnos);

	gtk_widget_show_all(pt->wdwMostrar);
	return;
}

void darBaja(GtkButton *btnBaja, gpointer nav){
	navegador *pt = (navegador *)nav;
	char nAlum[3];
        char cProm[10];
	nodo *aux = pt->pos, *sig = pt->pos->der;
	if(pt->pos == NULL){
                printf("Error Lista vacia\n");
		return;
        }else if(pt->pos->der == pt->pos){
                pt->pos = NULL;
		free(aux);
                gtk_label_set_text(GTK_LABEL(pt->lblResCar), "Lista vacia");
                gtk_label_set_text(GTK_LABEL(pt->lblResProm), "Lista vacia");
                gtk_label_set_text(GTK_LABEL(pt->lblResMej), "Lista vacia");
                gtk_label_set_text(GTK_LABEL(pt->lblResAlum), "Lista vacia");
                return;
        }
	pt->pos->izq->der = pt->pos->der;
	pt->pos->der->izq = pt->pos->izq;
	free(aux);
	printf("------Nodo eliminado------\n");
	pt->pos = sig;
	sprintf(nAlum, "%i", pt->pos->alumnos);
        sprintf(cProm, "%f", pt->pos->prom);
        gtk_label_set_text(GTK_LABEL(pt->lblResCar), pt->pos->carrera);
        gtk_label_set_text(GTK_LABEL(pt->lblResProm), cProm);
        gtk_label_set_text(GTK_LABEL(pt->lblResMej), pt->pos->mejor);
        gtk_label_set_text(GTK_LABEL(pt->lblResAlum), nAlum);
	return;
}

void buscarCta(GtkButton *btnBuscarCta, gpointer root){
	/*arbol *pt = (arbol *)root;
	GtkWidget *tituloCta, *lblInfo, *boxCta;
	int i = 1;
	char nombre[40], nCta[20], prom[10], info[200];

	pt->wdwCta = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	boxCta = gtk_vbox_new(FALSE, 5);
	gtk_window_set_title(GTK_WINDOW(pt->wdwCta), "Busqueda Cta");
	gtk_container_set_border_width(GTK_CONTAINER(pt->wdwCta), 10);
	
	if(i == 1){
		tituloCta = gtk_label_new("Alumno no encontrado\n");
		lblInfo = gtk_label_new(":(");
	}

	gtk_container_add(GTK_CONTAINER(pt->wdwCta), boxCta);
	gtk_box_pack_start_defaults(GTK_BOX(boxCta), tituloCta);
	gtk_box_pack_start_defaults(GTK_BOX(boxCta), lblInfo);

	gtk_widget_show_all(pt->wdwCta);
	*/
	return;
}

void buscarProm(GtkButton *btnBuscarProm, gpointer inicio){
	return;
}
