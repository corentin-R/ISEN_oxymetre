#build executable by linking objects
projet.exe: affichage.o calcul.o filtreIIR.o filtreFIR.o lecture.o menu.o divers.o main.o
	gcc affichage.o calcul.o filtreIIR.o filtreFIR.o lecture.o menu.o divers.o main.o -o projet7.exe


#compile affichage.c
affichage.o: affichage.c affichage.h
	gcc -c affichage.c -o affichage.o

#compile calcul.c
calcul.o: calcul.c calcul.h
	gcc -c calcul.c -o calcul.o

#compile filtreIIR.c
filtreIIR.o: filtreIIR.c filtreIIR.h
	gcc -c filtreIIR.c -o filtreIIR.o

#compile filtreFIR.c
filtreFIR.o: filtreFIR.c filtreFIR.h
	gcc -c filtreFIR.c -o filtreFIR.o

#compile lecture.c
lecture.o: lecture.c lecture.h
	gcc -c lecture.c -o lecture.o

#compile menu.c
menu.o: menu.c menu.h
	gcc -c menu.c -o menu.o

#compile divers.c
divers.o: divers.c divers.h
	gcc -c divers.c -o divers.o

#compile main.c
main.o: main.c
	gcc -c main.c -o main.o

#remove all object files and executable
clean:
	rm -f *.o projet.exe