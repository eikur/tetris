#
# Jorge Soriano Pinedo. 14-8-2013
#
# Ubicar en la carpeta src

MAIN = main.cpp
COMP = g++
OUTD = ../bin/
OUTF = tetris

WOUTD = ../win-bin/
WOUTF = tetris-x64.exe
.PHONY: clean
.PHONY: remove

# Construción de los ejecutables.
tetris: 
	$(COMP) -c *.cpp
	$(COMP) *.o -o $(OUTD)$(OUTF) -lSDL2 -lSDL2_image -lSDL2_ttf
	rm *.o

# Borrado de objetos
remove: 
	rm *.o
# Borrado de ejecutables.
clean:
	rm ../bin/*
