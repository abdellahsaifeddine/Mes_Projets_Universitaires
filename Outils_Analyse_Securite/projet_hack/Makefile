# ============================================================
# Makefile — Projet "Passe ton hack d'abord !"
# Auteurs : SAIFEDDINE Abdellah & EL BASBASSI Aladin
# ============================================================

OCAMLFIND = ocamlfind
OCAMLOPT  = ocamlopt
PACKAGES  = cryptokit,base64

# Fichiers sources dans l'ordre de dépendance
SRC = src/env.ml src/tri.ml src/p_fct.ml src/main.ml src/crack.ml

TARGET = crack

.PHONY: all clean

all: $(TARGET)

$(TARGET):
	$(OCAMLFIND) $(OCAMLOPT) -package $(PACKAGES) -linkpkg \
		-I src $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) src/*.cmi src/*.cmx src/*.o
