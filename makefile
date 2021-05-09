#Aqui se encuentra las instrucciones de makefile para generar el ejecutable reporteAlumnos.exe

reporteAlumnos.exe:reporteAlumnos.o funciones.o
	gcc reporteGTK.o funcionesGTK.o -o reporteAlumnos.exe `pkg-config --libs gtk+-2.0`

reporteAlumnos.o:reporteAlumnos.c
	gcc -c reporteGTK.c `pkg-config --cflags gtk+-2.0`

funciones.o:funciones.c
	gcc -c funcionesGTK.c `pkg-config --cflags gtk+-2.0`
