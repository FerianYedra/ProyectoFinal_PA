//Añadir documentación

#include "def.h"

//Añadir prototipos

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
	while(fscanf(fp, "%i %[^\t] %[^\t] %f\n", &dat.cta, dat.nom, dat.car, &dat.prom)==4){
		if(dat.nom[0] == 65 + j){
			root = generarArbol(root, dat);
			i++;
		}
	}
	fclose(fp);
	printf("Se leyeron %i alumnos\n", i);
	for(j = 0; j <= 26; j++){
		inicio = hacerEstructura(root, 65+j);
	}

	return 0;
}
