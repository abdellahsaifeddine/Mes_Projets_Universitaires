# 🎮 Moteur de Jeu — Clash Loyal

**Projet L2 — Algorithmique & Programmation**  
**Universite de Poitiers — 2024-2025**  
**Auteur : SAIFEDDINE Abdellah**

---

## 📌 Description

Implémentation en **C** d'un moteur de jeu inspiré de Clash Royale, avec affichage graphique via **SDL2**.  
Deux joueurs s'affrontent sur un plateau 11×19 cases. Chaque round, les unités attaquent, se déplacent,
et les joueurs achètent de nouvelles unités grâce à leur élixir.  
La partie se termine lorsque la **Tour Roi** d'un joueur est détruite.

Le projet m'a permis de mettre en pratique les structures de données dynamiques (listes doublement
chaînées), les algorithmes de tri (QuickSort, tri par sélection), ainsi que la gestion de fichiers
binaires et séquentiels pour la sauvegarde des parties.

---

## 📁 Structure du projet

```
Moteur_Jeu_ClashLoyal/
├── README.md
├── .gitignore
├── src/
│   ├── main.c            # Point d'entree, boucle de jeu, gestion SDL2
│   ├── clashloyal.c/.h   # Logique principale : unites, plateau, combats, deplacements
│   ├── listeDouble.c/.h  # Liste doublement chainee generique de Tunite*
│   ├── type.c/.h         # Types de base (Tunite, TuniteDuJeu, couple...)
│   ├── maSDL.c/.h        # Fonctions d'affichage SDL2 (sprites, fenetre)
│   ├── save.c/.h         # Sauvegarde/chargement binaire et sequentiel
│   ├── quicksort.c/.h    # QuickSort sur liste chainee (tri par attribut)
│   ├── Trisd.c/.h        # Tri par selection sur liste chainee
│   ├── TriViaTab.c/.h    # Tri via tableau intermediaire
│   ├── tester.c/.h       # Fonctions d'affichage debug
│   └── trash.c           # Fonctions experimentales / code de test
├── data/
│   ├── Archer.bmp        # Sprite archer
│   ├── Chevalier.bmp     # Sprite chevalier
│   ├── Dragon.bmp        # Sprite dragon
│   ├── Gargouille.bmp    # Sprite gargouille
│   ├── Tour.bmp          # Sprite tour defensive
│   ├── TourRoi.bmp       # Sprite tour du roi (objectif a detruire)
│   ├── Eau.bmp           # Terrain : eau
│   ├── Herbe.bmp         # Terrain : herbe
│   ├── Pont.bmp          # Terrain : pont
│   └── Terre.bmp         # Terrain : terre
└── build/
    ├── partiebin.clb     # Exemple de sauvegarde binaire
    └── partieseq.cls     # Exemple de sauvegarde sequentielle
```

---

## 🧩 Modules

| Fichier | Rôle |
|---|---|
| `clashloyal.c` | Création des unités, logique de combat, déplacement, achat |
| `listeDouble.c` | Structure de liste doublement chaînée (ajout, suppression, parcours) |
| `type.c` | Définition des types `Tunite`, `TuniteDuJeu`, `couple` |
| `maSDL.c` | Rendu graphique : chargement sprites, affichage plateau, maj fenêtre |
| `save.c` | Sérialisation binaire (`.clb`) et séquentielle (`.cls`) |
| `quicksort.c` | Tri rapide générique sur liste chaînée selon un attribut |
| `Trisd.c` | Tri par sélection sur liste chaînée |

---

## 🕹️ Unités disponibles

| Unité | PV | Dégâts | Portée | Position | Cibles |
|---|---|---|---|---|---|
| Tour | 500 | — | 3 | Sol | Sol + Air |
| Tour Roi | 800 | — | 4 | Sol | Sol + Air |
| Archer | 80 | 120 | 3 | Sol | Sol + Air |
| Chevalier | 300 | 140 | 1 | Sol | Sol |
| Dragon | 200 | 160 | 2 | Air | Sol + Air |
| Gargouille | 150 | 110 | 2 | Air | Sol + Air |

---

## 💾 Sauvegardes

| Touche | Action |
|---|---|
| `S` | Sauvegarde binaire (`partiebin.clb`) |
| `C` | Chargement binaire |
| `D` | Sauvegarde séquentielle (`partieseq.cls`) |
| `V` | Chargement séquentiel |
| `ECHAP` | Quitter |

---

## 🛠️ Compilation

### Prérequis
- **GCC** (MinGW sur Windows)
- **SDL2** (inclus dans le projet original via CodeBlocks)

### Avec CodeBlocks
Ouvrir `projetClashLoyal.cbp` et lancer la compilation (F9).

### En ligne de commande (Linux/Mac)
```bash
gcc src/*.c -o clashloyal -lSDL2 -lm
./clashloyal
```

---

## 📐 Architecture technique

Le plateau est un tableau 2D alloué dynamiquement (`Tunite***`) de dimensions 11×19.  
Les unités de chaque joueur sont stockées dans une **liste doublement chaînée** (`T_liste`),
ce qui permet des insertions/suppressions efficaces lors des combats.  
Le tri des unités avant chaque phase (attaque/déplacement) est réalisé par **QuickSort**
sur la liste chaînée, en passant un pointeur de fonction comme comparateur.
