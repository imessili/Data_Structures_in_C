EXEC = test_iterateurs
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -pedantic -Wextra -Wno-unused-parameter

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
