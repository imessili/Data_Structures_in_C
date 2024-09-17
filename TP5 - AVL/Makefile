EXEC = test_avl
SRC = $(wildcard *.c)
DOTS = $(wildcard *.dot)
IMG = $(DOTS:.dot=.svg)
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -pedantic -Wextra -g

.PHONY: clean compil dessin

all: compil dessin

compil: $(OBJ) 
	$(CC) $(CFLAGS) $^ -o $(EXEC)
	@echo "Compilation terminée"
	@echo "\n**** Exécution du programme : ****\n"
	@./$(EXEC)
	@make -s dessin

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(EXEC) $(DOTS) $(IMG)
	
dessin: $(IMG)
	
%.svg: %.dot
	dot -Tsvg $< -o $@	


