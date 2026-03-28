# Passe ton hack d'abord ! — Projet L2 Algorithmique & Programmation 2

**Auteurs :** SAIFEDDINE Abdellah & EL BASBASSI Aladin  
**Université de Poitiers — Année 2024-2025**

---

## Structure du projet

```
projet_hack/
├── src/
│   ├── env.ml        # Types, fonctions de base, utilitaires, hachage
│   ├── tri.ml        # Tri fusion générique (merge sort)
│   ├── p_fct.ml      # Fonctions d'analyse (doublons, hachages, passwords)
│   ├── main.ml       # Fonctions principales (fusion, craquage, export)
│   └── crack.ml      # Interface utilisateur interactive (point d'entrée)
├── data/
│   ├── depensetout01.txt             # Fuite 1 — mots de passe en clair
│   ├── depensetout02.txt             # Fuite 2 — mots de passe en clair
│   ├── slogram01.txt                 # Fuite 1 — mots de passe hachés
│   ├── slogram02.txt                 # Fuite 2 — mots de passe hachés
│   ├── tetedamis02.txt               # Fuite 2 — mots de passe hachés
│   └── french_passwords_top20000.txt # Top 20 000 mots de passe français
├── rapport/
│   ├── Rapport_projet.pdf            # Rapport / mode d'emploi complet
│   └── sujet-projet.pdf              # Sujet original
├── Makefile
└── README.md
```

---

## Dépendances

- OCaml (>= 4.10)
- `cryptokit` — pour le hachage SHA-256
- `base64` — pour l'encodage Base64 du haché

Installation via opam :
```bash
opam install cryptokit base64
```

---

## Compilation

```bash
make
```

Cela produit l'exécutable `crack` à la racine du projet.

---

## Utilisation

```bash
./crack
```

Une interface interactive se lance. Choisir un numéro de tâche pour exécuter les requêtes souhaitées (détails dans `rapport/Rapport_projet.pdf`).

---

## Description des modules

| Fichier     | Rôle |
|-------------|------|
| `env.ml`    | Types (`fich`, `count`), accesseurs (`user`, `pw`), validation de mot de passe, hachage, affichage |
| `tri.ml`    | Tri fusion générique (`sort`), comparateurs (`compare_by_user`, `compare_by_pw`, `compare_by_couple`) |
| `p_fct.ml`  | Détection de doublons, suppression de doublons, hachage de listes de mots de passe |
| `main.ml`   | Fusion de fuites, recherche par user/mdp, craquage via mots de passe courants |
| `crack.ml`  | Interface interactive, exécution sur les fichiers de données fournis |

---

## Complexités clés

| Fonction                    | Temps       | Espace |
|-----------------------------|-------------|--------|
| `sort`                      | O(n log n)  | O(n)   |
| `get_double`                | O(n log n)  | O(n)   |
| `get_list_out_double`       | O(n)        | O(n)   |
| `merge_out_double`          | O(n log n)  | O(n)   |
| `get_users_for_clair_mdp`   | O(n log n)  | O(n)   |
