# Makefile - Compilateur FrontEnd (Lex/Yacc)
# Auteur : SAIFEDDINE Abdellah
# Universite de Poitiers - L2 Informatique - 2024-2025

CC      = gcc
LEX     = flex
YACC    = bison -y
CFLAGS  = -Wall -Wextra
LDFLAGS = -lfl

SRC = src
BIN = bin

all: $(BIN)/exo11 $(BIN)/exo12 $(BIN)/exo21 $(BIN)/exo22 $(BIN)/exo23

$(BIN):
	mkdir -p $(BIN)

# --- Exercice 1.1 : affichage des tokens ---
$(BIN)/exo11: $(SRC)/Exo.1.1.lex | $(BIN)
	$(LEX) -o $(BIN)/exo11.c $(SRC)/Exo.1.1.lex
	$(CC) $(CFLAGS) -o $@ $(BIN)/exo11.c $(LDFLAGS)

# --- Exercice 1.2 : comptage des concerts ---
$(BIN)/exo12: $(SRC)/Exo.1.2.lex | $(BIN)
	$(LEX) -o $(BIN)/exo12.c $(SRC)/Exo.1.2.lex
	$(CC) $(CFLAGS) -o $@ $(BIN)/exo12.c $(LDFLAGS)

# --- Exercice 2.1 : validation syntaxique ---
$(BIN)/exo21: $(SRC)/Exo.2.1.lex $(SRC)/Exo.2.1.yacc | $(BIN)
	$(YACC) -d -o $(BIN)/exo21.tab.c $(SRC)/Exo.2.1.yacc
	$(LEX)  -o $(BIN)/exo21.lex.c $(SRC)/Exo.2.1.lex
	$(CC) $(CFLAGS) -o $@ $(BIN)/exo21.lex.c $(BIN)/exo21.tab.c $(LDFLAGS)

# --- Exercice 2.2 : comptage des places ---
$(BIN)/exo22: $(SRC)/Exo.2.2.lex $(SRC)/Exo.2.2.yacc | $(BIN)
	$(YACC) -d -o $(BIN)/exo22.tab.c $(SRC)/Exo.2.2.yacc
	$(LEX)  -o $(BIN)/exo22.lex.c $(SRC)/Exo.2.2.lex
	$(CC) $(CFLAGS) -o $@ $(BIN)/exo22.lex.c $(BIN)/exo22.tab.c $(LDFLAGS)

# --- Exercice 2.3 : validation avec numeros de places ---
$(BIN)/exo23: $(SRC)/Exo.2.3.lex $(SRC)/Exo.2.3.yacc | $(BIN)
	$(YACC) -d -o $(BIN)/exo23.tab.c $(SRC)/Exo.2.3.yacc
	$(LEX)  -o $(BIN)/exo23.lex.c $(SRC)/Exo.2.3.lex
	$(CC) $(CFLAGS) -o $@ $(BIN)/exo23.lex.c $(BIN)/exo23.tab.c $(LDFLAGS)

clean:
	rm -rf $(BIN)

# --- Cibles de test rapide ---
test11: $(BIN)/exo11
	./$(BIN)/exo11 examples/exemple_commande.txt

test12: $(BIN)/exo12
	./$(BIN)/exo12 examples/exemple_commande.txt

test21: $(BIN)/exo21
	./$(BIN)/exo21 examples/exemple_commande.txt

test22: $(BIN)/exo22
	./$(BIN)/exo22 examples/exemple_commande.txt

test23: $(BIN)/exo23
	./$(BIN)/exo23 examples/SAIFEDDINE.exempleCommande.txt
