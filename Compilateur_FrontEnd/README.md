# 🔍 Analyse Lexicale & Syntaxique — Commandes de Billets

**Projet L2 — Compilation (Front-End)**  
**Universite de Poitiers — 2024-2025**  
**Auteur : SAIFEDDINE Abdellah**

---

## 📌 Description

Implémentation d'un **analyseur lexical et syntaxique** en **Lex** et **Yacc** pour valider et
analyser des commandes de billets de concert.

Ce projet couvre les deux phases du front-end d'un compilateur :
- **Analyse lexicale** (Lex/Flex) : reconnaissance des tokens (dossier, nom, date, heure, nb places...)
- **Analyse syntaxique** (Yacc/Bison) : validation de la grammaire de la commande et calcul sémantique

---

## 📁 Structure du projet

```
Compilateur_FrontEnd/
├── README.md
├── Makefile
├── src/
│   ├── Exo.1.1.lex       # Affichage de chaque token reconnu
│   ├── Exo.1.2.lex       # Comptage du nombre de concerts par commande
│   ├── Exo.2.1.lex       # Lexer pour la validation syntaxique
│   ├── Exo.2.1.yacc      # Validation : "La commande est valide"
│   ├── Exo.2.2.lex       # Lexer pour le comptage des places
│   ├── Exo.2.2.yacc      # Affichage du nombre total de places
│   ├── Exo.2.3.lex       # Lexer avec support numeros de places
│   └── Exo.2.3.yacc      # Validation avec liste de numeros de places
└── examples/
    ├── exemple_commande.txt          # Exemple de commande standard
    ├── SAIFEDDINE.exempleCommande.txt # Exemple avec numeros de places
    └── SAIFEDDINE.ExplicationPlaces.txt # Explication de la modification grammaticale
```

---

## 📄 Format d'une commande

```
12345678
ANNE-CLAIRE/BERGEY
C001 RockFestival 25/03/24 20:30 5 places
C002 JazzNight 26/3/24 19:00 7 places
C003 ClassicConcert 27/03/24 21:00 5 places
```

| Champ | Format | Exemple |
|---|---|---|
| Dossier | 8 chiffres exactement | `12345678` |
| PrenomNom | `PRENOM/NOM` majuscules | `ANNE-CLAIRE/BERGEY` |
| Code concert | Lettres + chiffres | `C001` |
| Nom concert | Alphanumérique | `RockFestival` |
| Date | `DD/MM`, `DD/M`, `DD/MM/YY` | `25/03/24` |
| Heure | `HH:MM` | `20:30` |
| Nb places | Entier 1–99 | `5` |
| Mot clé | `places` (minuscules) | `places` |

---

## 🧩 Exercices

### Exercice 1 — Analyse lexicale seule

**1.1** — Reconnaît et affiche chaque token :
```
dossier RC prenomNom RC codeConcert nomConcert date heure nb places RC ... FinFichier
```

**1.2** — Compte le nombre de concerts et affiche :
```
ANNE-CLAIRE/BERGEY a achete des places de 3 concerts.
```

### Exercice 2 — Analyse lexicale + syntaxique (Lex + Yacc)

**2.1** — Valide la syntaxe de la commande :
```
La commande est valide
```

**2.2** — Valide et compte le total de places :
```
Le dossier 12345678 concerne 17 places
```

**2.3** — Extension : reconnait les numéros de places après `places` :
```
C001 RockFestival 25/03/24 20:30 5 places 101 102 103 104 105
```

---

## 🛠️ Compilation

### Prérequis
```bash
sudo apt install flex bison gcc
```

### Compiler tous les exercices
```bash
make
```

### Compiler un exercice spécifique
```bash
make bin/exo11   # Exercice 1.1
make bin/exo22   # Exercice 2.2
```

### Lancer les tests
```bash
make test11   # → affichage des tokens
make test12   # → ANNE-CLAIRE/BERGEY a achete des places de 3 concerts.
make test21   # → La commande est valide
make test22   # → Le dossier 12345678 concerne 17 places
make test23   # → La commande est valide (avec numeros de places)
```

---

## 📐 Points techniques

- Les expressions régulières Lex gèrent les variantes de dates (`DD/M`, `DD/MM`, `DD/MM/YY`)
- La grammaire Yacc utilise les **valeurs sémantiques** (`%union`, `%type`) pour propager les entiers
- Le tri des concerts dans la liste utilise une **récursivité gauche** (standard Yacc)
- L'extension 2.3 ajoute une règle `liste_numeros` récursive pour les numéros de places
