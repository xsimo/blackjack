OBJ = main.o affiche.o
CIBLE = executable
CFLAGS = -W -Wall -std=c99

all: $(CIBLE)

$(CIBLE): $(OBJ)
	gcc $(CFLAGS) -o $(CIBLE) $(OBJ)

%.o: %.c
	gcc $(CFLAGS) -c $<

$(OBJ) : affiche.h

.PHONY: clean

clean:
	rm -f $(OBJ)
	rm executable
