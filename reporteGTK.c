//Añadir documentación

#include "def.h"

//Añadir prototipos
nodo *listaCircular(nodo *pt, info dat);
nodo *listaFIFO(nodo *pt, info dat);
arbol *generarArbol(arbol *pt, info dat);

int main(int argc, char *argv[]){
	info dat;
	nodo *inicio = NULL;
	arbol *root = NULL;
	FILE *fp;
	int i = 0, j;
	navegador nav;
	char opcion;

	fp = fopen("alumnos.txt", "r");
	if(fp == NULL){
		printf("Archivo alumnos.txt no disponible\n");
		exit(1);
	}
	fclose(fp);
	for(j = 0; j <= 26; j++){
		fopen("alumnos.txt", "r");
		while(fscanf(fp, "%i %[^\t] %[^\t] %f\n", &dat.cta, dat.nom, dat.car, &dat.prom)==4){
			if(dat.car[0] == 65 + j){
				printf("Se mando a guardar %s\n", dat.car);
				inicio = listaCircular(inicio, dat);
			}
		}
		fclose(fp);
	}
	fopen("alumnos.txt", "r");	
	while(fscanf(fp, "%i %[^\t] %[^\t] %f\n", &dat.cta, dat.nom, dat.car, &dat.prom)==4){
			inicio = listaFIFO(inicio, dat);
			root = generarArbol(root, dat);
			i++;
	}
	printf("Se leyeron %i alumnos\n", i);

	return 0;
}
