EXEC = test_tableau_dynamique
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -pedantic -Wextra

all: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(EXEC)
	@echo "Compilation terminée"
	@echo "\n**** Exécution du programme : ****\n"
	@./$(EXEC)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJ) $(EXEC)
