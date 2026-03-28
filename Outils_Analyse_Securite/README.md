# 🔐 Passe ton hack d'abord !

**Projet L2 — Algorithmique & Programmation 2**  
**Université de Poitiers — 2024-2025**  
**Auteurs :** SAIFEDDINE Abdellah & EL BASBASSI Aladin

---

## 📌 Description

Outil en **OCaml** simulant le travail d'un analyste en cybersécurité face à des fuites de bases de données.  
Le programme fusionne plusieurs fuites de mots de passe (en clair ou hachés), détecte les doublons, et tente de **cracker des mots de passe hachés** en SHA-256 + Base64 à partir d'un dictionnaire de mots de passe courants.

---

## 📁 Structure du projet
```
projet_hack/
├── src/
│   ├── env.ml        # Types, accesseurs, validation, hachage, affichage
│   ├── tri.ml        # Tri fusion générique (O(n log n))
│   ├── p_fct.ml      # Détection/suppression de doublons, hachage de listes
│   ├── main.ml       # Fusion de fuites, recherche, craquage
│   └── crack.ml      # Interface utilisateur interactive (point d'entrée)
├── data/
│   ├── depensetout01.txt              # Fuite 1 — mots de passe en clair
│   ├── depensetout02.txt              # Fuite 2 — mots de passe en clair
│   ├── slogram01.txt                  # Fuite 1 — mots de passe hachés
│   ├── slogram02.txt                  # Fuite 2 — mots de passe hachés
│   ├── tetedamis02.txt                # Fuite 2 — mots de passe hachés
│   └── french_passwords_top20000.txt  # Dictionnaire top 20 000 mots de passe français
├── rapport/
│   ├── Rapport_projet.pdf             # Rapport complet + mode d'emploi
│   └── sujet-projet.pdf               # Sujet original
├── Makefile
└── README.md
```

---

## ⚙️ Dépendances

- **OCaml** >= 4.10
- **cryptokit** — hachage SHA-256
- **base64** — encodage Base64

Installation via opam :
```bash
opam install cryptokit base64
```

---

## 🔨 Compilation
```bash
make
```

Produit l'exécutable `crack` à la racine du projet.

---

## 🚀 Utilisation
```bash
./crack
```

Une interface interactive se lance. Saisir un numéro de tâche pour exécuter les requêtes souhaitées.  
Le détail de chaque tâche est disponible dans `rapport/Rapport_projet.pdf`.

---

## 🧩 Modules

| Fichier | Rôle |
|---|---|
| `env.ml` | Types (`fich`, `count`), accesseurs (`user`, `pw`), validation de mot de passe, hachage SHA-256, affichage |
| `tri.ml` | Tri fusion générique (`sort`), comparateurs (`compare_by_user`, `compare_by_pw`, `compare_by_couple`) |
| `p_fct.ml` | Détection de doublons, suppression de doublons, hachage de listes |
| `main.ml` | Fusion de fuites, recherche par user/mdp, craquage via dictionnaire |
| `crack.ml` | Interface interactive, exécution sur les fichiers de données |

---

## 📊 Complexités

| Fonction | Temps | Espace |
|---|---|---|
| `sort` | O(n log n) | O(n) |
| `get_double` | O(n log n) | O(n) |
| `get_list_out_double` | O(n) | O(n) |
| `merge_out_double` | O(n log n) | O(n) |
| `get_users_for_clair_mdp` | O(n log n) | O(n) |

---

## 🛡️ Contexte pédagogique

Ce projet est réalisé dans un cadre **strictement académique**.  
Les techniques présentées (craquage par dictionnaire, analyse de fuites) sont étudiées à des fins de **sensibilisation à la sécurité informatique**.