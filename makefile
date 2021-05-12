#Aqui se encuentra las instrucciones de makefile para generar el ejecutable reporteAlumnos.exe

reporteAlumnos.exe:reporteGTK.o funcionesGTK.o
	gcc reporteGTK.o funcionesGTK.o -o reporteAlumnos.exe `pkg-config --libs gtk+-2.0`

reporteGTK.o: reporteGTK.c
	gcc -c reporteGTK.c `pkg-config --cflags gtk+-2.0`

funcionesGTK.o: funcionesGTK.c
	gcc -c funcionesGTK.c `pkg-config --cflags gtk+-2.0`
