#Aqui se encuentra las instrucciones de makefile para generar el ejecutable reporteAlumnos.exe

reporteAlumnos.exe:reporteAlumnos.o funciones.o
	gcc reporteAlumnos.o funciones.o -o reporteAlumnos.exe

reporteAlumnos.o:reporteAlumnos.c
	gcc -c reporteAlumnos.c

funciones.o:funciones.c
	gcc -c funciones.c
