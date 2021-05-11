/**
 * @file reporteGTK.c
 * @brief El programa principal para el proyecto final de Programacion Aplicada
 * @author Nancy Melina y Fernando Yedra
 * @date 11/05/2021
 */

#include "def.h"

nodo *listaCircular(nodo *pt, info dat);
nodo *listaFIFO(nodo *pt, info dat);
arbol *generarArbol(arbol *pt, info dat);
void actualizarNodos(nodo *pt);

void recorrerIzq(GtkButton *btnIzq, gpointer nav);
void recorrerDer(GtkButton *btnIzq, gpointer nav);
void mostrarAlum(GtkButton *btnMostrar, gpointer nav);
void darBaja(GtkButton *btnBaja, gpointer nav);
void closeApp(GtkButton *exit, gpointer data);
void buscarCta(GtkButton *btnBuscarCta, gpointer nav);
void buscarProm(GtkButton *btnBuscarProm, gpointer inicio);

int main(int argc, char *argv[]){
	info dat;
	nodo *inicio = NULL;
	arbol *root = NULL;
	FILE *fp;
	int i = 0, j;
	navegador nav;
	char opcion;

	printf("------Leyendo archivo------\n");
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
	printf("------Archivo leido------\n------Actualizando estructura------\n");
	actualizarNodos(inicio);
	printf("------Estructura atualizada------\n");
	nav.pos = inicio;
	nav.list = inicio->fifo;
	nav.root = root;
	printf("------Iniciando interfaz en GTK------\n");

	//La parte gráfica del programa comienza aqui
	//Declaración de variables para los objetos
	GtkWidget *window, *titulo, *separador, *table, *box, *box2, *box3;
	GtkWidget *lblBusc, *lblCar, *lblProm, *lblMej, *lblAlum;
	GtkWidget *btnIzq, *btnDer;
	GtkWidget *btnMostrar, *btnBaja;
	GtkWidget *btnExit;
	GtkWidget *lblBuscarCta, *btnBuscarCta;
	GtkWidget *lblBuscarProm, *btnBuscarProm;

	//1. Iniciar el ambiente
	gtk_init(&argc, &argv);

	printf("Ambiente iniciado\n");
	
	//2. Crear widgets y fijar atributos
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	box = gtk_hbox_new(FALSE, 1);
	box2 = gtk_vbox_new(FALSE, 5);
	box3 = gtk_vbox_new(FALSE, 1);
	gtk_window_set_title(GTK_WINDOW(window), "Menu principal");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	titulo = gtk_label_new("Menu de gestion de carreras\n");

	printf("Ventana principal\n");

	table = gtk_table_new(2, 8, FALSE);
	lblBusc = gtk_label_new("Buscador por lista de carreras");
	lblCar = gtk_label_new("Carrera:");
	nav.lblResCar = gtk_label_new(nav.pos->carrera);
	lblProm = gtk_label_new("Promedio General:");
	sprintf(nav.auxWord, "%f", nav.pos->prom);
	nav.lblResProm = gtk_label_new(nav.auxWord);
	lblMej = gtk_label_new("Mejor Alumno:");
	nav.lblResMej = gtk_label_new(nav.pos->mejor);
	lblAlum = gtk_label_new("Numero de Alumnos:");
	sprintf(nav.auxWord, "%i", nav.pos->alumnos);
	nav.lblResAlum = gtk_label_new(nav.auxWord);

	btnIzq = gtk_button_new_with_label("Anterior");
	btnDer = gtk_button_new_with_label("Siguiente");

	btnMostrar = gtk_button_new_with_label("Mostrar Alumnos");
	btnBaja = gtk_button_new_with_label("Dar de Baja");

	btnExit = gtk_button_new_with_label("Salir");

	separador = gtk_vseparator_new();

	lblBuscarCta = gtk_label_new("Busqueda por numero de cuenta:");
	nav.entryCta = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(nav.entryCta),"Introducir numero de cuenta...");
	btnBuscarCta = gtk_button_new_with_label("Buscar");

	lblBuscarProm = gtk_label_new("Busqueda por promedio:");
	nav.entryProm = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(nav.entryProm),"Introducir el promedio...");
	btnBuscarProm = gtk_button_new_with_label("Buscar");

	printf("Atributos asignados\n");
	
	//3. Registrar las llamadas a las funciones
	gtk_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(closeApp), inicio);
	printf("1\n");
	gtk_signal_connect(GTK_OBJECT(btnIzq), "clicked", GTK_SIGNAL_FUNC(recorrerIzq), &nav);
	printf("2\n");
	gtk_signal_connect(GTK_OBJECT(btnDer), "clicked", GTK_SIGNAL_FUNC(recorrerDer), &nav);
	printf("3\n");
	gtk_signal_connect(GTK_OBJECT(btnMostrar), "clicked", GTK_SIGNAL_FUNC(mostrarAlum), &nav);
	printf("4\n");
	gtk_signal_connect(GTK_OBJECT(btnBaja), "clicked", GTK_SIGNAL_FUNC(darBaja), &nav);
	printf("5\n");
	gtk_signal_connect(GTK_OBJECT(btnExit), "clicked", GTK_SIGNAL_FUNC(closeApp), inicio);
	printf("6\n");
	gtk_signal_connect(GTK_OBJECT(btnBuscarCta), "clicked", GTK_SIGNAL_FUNC(buscarCta), &nav);
	printf("7\n");
	gtk_signal_connect(GTK_OBJECT(btnBuscarProm), "clicked", GTK_SIGNAL_FUNC(buscarProm), &nav);
	printf("8\n");

	printf("Botones conectados\n");

	//4. Definir jerarquias
	gtk_table_attach(GTK_TABLE(table), lblBusc, 0, 2, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(table), lblCar, 0, 1, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(table), nav.lblResCar, 1, 2, 1, 2, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(table), lblProm, 0, 1, 2, 3, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(table), nav.lblResProm, 1, 2, 2, 3, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(table), lblMej, 0, 1, 3, 4, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(table), nav.lblResMej, 1, 2, 3, 4, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(table), lblAlum, 0, 1, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(table), nav.lblResAlum, 1, 2, 4, 5, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(table), btnIzq, 0, 1, 5, 6, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(table), btnDer, 1, 2, 5, 6, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(table), btnMostrar, 0, 1, 6, 7, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(table), btnBaja, 1, 2, 6, 7, GTK_FILL, GTK_FILL, 0, 0);
	gtk_table_attach(GTK_TABLE(table), btnExit, 0, 2, 7, 8, GTK_FILL, GTK_FILL, 0, 0);

	gtk_table_set_row_spacings(GTK_TABLE(table), 5);
	gtk_table_set_col_spacings(GTK_TABLE(table), 5);

	printf("------Empacando------\n");

	gtk_container_add(GTK_CONTAINER(window), box3);
	gtk_box_pack_start_defaults(GTK_BOX(box3), titulo);
	gtk_box_pack_start_defaults(GTK_BOX(box3), box);
	gtk_box_pack_start_defaults(GTK_BOX(box), table);
	//gtk_box_pack_start_defaults(GTK_BOX(box), separador);
	gtk_box_pack_start_defaults(GTK_BOX(box), box2);
	gtk_box_pack_start_defaults(GTK_BOX(box2), lblBuscarCta);
	gtk_box_pack_start_defaults(GTK_BOX(box2), nav.entryCta);
	gtk_box_pack_start_defaults(GTK_BOX(box2), btnBuscarCta);
	gtk_box_pack_start_defaults(GTK_BOX(box2), lblBuscarProm);
	gtk_box_pack_start_defaults(GTK_BOX(box2), nav.entryProm);
	gtk_box_pack_start_defaults(GTK_BOX(box2), btnBuscarProm);

	//5. Mostrar Los widgets
	printf("------Iniciando interfaz------\n");
	gtk_widget_show_all(window);

	//6. Iniciar el loop
	gtk_main();

	return 0;
}
