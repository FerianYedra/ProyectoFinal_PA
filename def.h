/**
 * @flie def.h
 * @brief Esta cabecera contiene las estructuras y bibliotecas usadas para reporteAlumnos.c
 * @author Fernando Yedra, Nancy Melina
 * @date 26/03/2021
 */

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct datos{
	int cta;
	char nom[40];
	char car[80];
	float prom;
};
typedef struct datos info;

struct lista{
	int cuenta;
	char nombre[40];
	char carrera[80];
	float promedio;
	struct lista *next;
};
typedef struct lista nodito;

struct elemento{
	char mejor[40];
	char carrera[80];
	int alumnos;
	float prom;
	struct elemento *izq, *der;
	nodito *fifo;
};
typedef struct elemento nodo;

struct estBuscador{
	nodo *pos;
	nodito *list;
};
typedef struct estBuscador navegador;

struct listArb{
	int cuenta;
	char nombre[40];
	char carrera[80];
	float prom;
	struct listArb *izq, *der;
};
typedef struct listArb arbol;
