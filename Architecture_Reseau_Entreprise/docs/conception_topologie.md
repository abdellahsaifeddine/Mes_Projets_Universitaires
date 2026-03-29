# Conception Topologique — SaifNet Corp
**Auteur : SAIFEDDINE Abdellah**

---

## 1. Topologie globale

J'ai opté pour une architecture **hub-and-spoke** entre les trois sites :
le siège de Poitiers joue le rôle de hub central, les deux agences
(Bordeaux et Paris) sont les spokes. Cette topologie est justifiée par :

- Le siège héberge les serveurs centraux (AD, fichiers, sauvegarde)
- Les agences ont besoin d'accéder au siège mais communiquent peu entre elles
- Simplifie le routage et la gestion des ACL
- Réduit le nombre de liens WAN nécessaires (2 liens vs 3 en full-mesh)

---

## 2. Topologie interne (par site)

Chaque site adopte une architecture **3 couches** (Core / Distribution / Access) :

```
                    [Internet]
                        |
                   [Firewall ASA]
                        |
              [R0 — Routeur Siège] -------- WAN -------- [R1 Bordeaux]
              /          \                                      |
    [SW_Siege L3]      [Serveurs DMZ]              [SW_Bordeaux L2]
    /    |    \                                    /           \
[VLAN10][VLAN20][VLAN30]                    [VLAN50]        [VLAN60]
Direction  DSI  Serveurs                   Commercial         RH
```

Pour les agences, une architecture **2 couches** suffit (Distribution + Access)
car le nombre d'hôtes est plus faible et la complexité moindre.

---

## 3. Équipements retenus

### Siège — Poitiers
| Équipement | Modèle | Rôle |
|---|---|---|
| Firewall | Cisco ASA 5506-X | Filtrage Internet / DMZ |
| Routeur | Cisco 2901 | Routage inter-sites, NAT |
| Switch L3 | Cisco 3560 | Inter-VLAN routing, trunk |
| Switch L2 | Cisco 2960 (x2) | Accès utilisateurs |

### Agences — Bordeaux / Paris
| Équipement | Modèle | Rôle |
|---|---|---|
| Routeur | Cisco 1941 | Routage WAN, DHCP relay |
| Switch L2 | Cisco 2960 | Accès utilisateurs, VLANs |

---

## 4. Protocole de routage : OSPF

J'ai choisi **OSPF (Open Shortest Path First)** pour les raisons suivantes :

- Protocole à état de lien : convergence rapide en cas de panne
- Standard ouvert (pas propriétaire contrairement à EIGRP)
- Supporte bien la segmentation en areas pour scaler si l'entreprise grandit
- Toute l'infrastructure est dans **Area 0** (backbone) car 3 sites = taille modeste

Configuration OSPF :
- Process ID : 1
- Router-ID : adresse loopback de chaque routeur
  - R0 : 1.1.1.1
  - R1 : 2.2.2.2
  - R2 : 3.3.3.3

---

## 5. Inter-VLAN Routing

Le routage inter-VLAN est assuré par le **Switch L3 (3560)** au siège via
des **Switched Virtual Interfaces (SVI)** — une interface virtuelle par VLAN.
Cette approche "Router-on-a-stick" évitée au profit du L3 switch offre de
meilleures performances car le trafic ne remonte pas au routeur.

Pour les agences, le routeur gère le routage inter-VLAN via des
**sous-interfaces (subinterfaces)** avec encapsulation 802.1Q sur le lien trunk
vers le switch (Router-on-a-stick justifié par le faible trafic inter-VLAN).

---

## 6. DHCP

- **Siège** : serveur DHCP centralisé sur le Switch L3 (une pool par VLAN)
- **Agences** : DHCP relay (`ip helper-address`) vers le serveur central du siège

Cela centralise la gestion des baux DHCP et évite de maintenir des serveurs
DHCP locaux sur chaque site.
