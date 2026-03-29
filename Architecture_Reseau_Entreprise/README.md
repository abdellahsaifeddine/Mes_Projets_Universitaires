# 🌐 Architecture Réseau d'Entreprise — SaifNet Corp

**Projet L2 — Réseaux & Systèmes**  
**Université de Poitiers — 2024-2025**  
**Auteur : SAIFEDDINE Abdellah**

---

## 📌 Description

Conception et configuration complète d'une **architecture réseau d'entreprise sécurisée**
pour une société fictive **SaifNet Corp** (~150 employés, 3 sites).

Le projet couvre :
- Conception topologique multi-sites (siège + 2 agences)
- Plan d'adressage IPv4 avec segmentation VLAN
- Configuration des routeurs, switches et firewall (Cisco IOS)
- Sécurisation du réseau (ACL, DMZ, NAT)
- Routage inter-VLAN et protocole OSPF

---

## 🏢 Contexte : SaifNet Corp

| Site | Rôle | Nombre d'hôtes |
|---|---|---|
| **Siège — Poitiers** | Direction, DSI, Serveurs | ~80 postes |
| **Agence A — Bordeaux** | Commercial, RH | ~40 postes |
| **Agence B — Paris** | R&D, Support | ~30 postes |

---

## 📁 Structure du projet

```
Architecture_Reseau_Entreprise/
├── README.md
├── docs/
│   ├── plan_adressage.md        # Plan d'adressage IPv4 complet
│   ├── conception_topologie.md  # Choix topologiques justifiés
│   └── politique_securite.md    # Politique de sécurité et ACL
├── schemas/
│   ├── topologie_globale.txt    # Schéma ASCII topologie complète
│   └── plan_vlan.txt            # Tableau récapitulatif des VLANs
├── configs/
│   ├── routeurs/
│   │   ├── R0_siege.cfg         # Routeur principal Siège
│   │   ├── R1_bordeaux.cfg      # Routeur Agence Bordeaux
│   │   └── R2_paris.cfg         # Routeur Agence Paris
│   ├── switches/
│   │   ├── SW_siege.cfg         # Switch multicouche Siège
│   │   ├── SW_bordeaux.cfg      # Switch Agence Bordeaux
│   │   └── SW_paris.cfg         # Switch Agence Paris
│   └── firewall/
│       └── FW_siege.cfg         # Firewall ASA Siège (DMZ)
└── scripts/
    └── test_connectivite.sh     # Script de test ping entre VLANs
```

---

## 🗺️ Plan d'adressage — Vue rapide

| VLAN | Nom | Réseau | Passerelle | Hôtes max |
|---|---|---|---|---|
| VLAN 10 | Direction | 192.168.10.0/26 | 192.168.10.1 | 62 |
| VLAN 20 | DSI | 192.168.20.0/26 | 192.168.20.1 | 62 |
| VLAN 30 | Serveurs | 192.168.30.0/27 | 192.168.30.1 | 30 |
| VLAN 40 | DMZ | 192.168.40.0/28 | 192.168.40.1 | 14 |
| VLAN 50 | Commercial | 192.168.50.0/26 | 192.168.50.1 | 62 |
| VLAN 60 | RH | 192.168.60.0/27 | 192.168.60.1 | 30 |
| VLAN 70 | R&D | 192.168.70.0/26 | 192.168.70.1 | 62 |
| VLAN 80 | Support | 192.168.80.0/27 | 192.168.80.1 | 30 |
| VLAN 99 | Management | 192.168.99.0/28 | 192.168.99.1 | 14 |

---

## 🔒 Sécurité

- **Firewall ASA** en coupure entre Internet et le réseau interne
- **DMZ** isolée (serveurs Web, Mail, DNS publics)
- **ACL étendues** sur chaque interface routeur
- **NAT/PAT** pour masquer les adresses internes
- **Port Security** sur les switches (MAC address sticky)
- **VLAN Management** dédié (VLAN 99) isolé du trafic utilisateur
- **Désactivation des ports inutilisés** sur tous les switches

---

## 🛠️ Technologies utilisées

`Cisco IOS` · `OSPF` · `VLANs 802.1Q` · `Inter-VLAN Routing` · `NAT/PAT` · `ACL` · `Cisco ASA` · `DHCP` · `DNS`

---

## ▶️ Simulation

Le projet est simulable avec **Cisco Packet Tracer** (version 8.x recommandée).  
Ouvrir le fichier `.pkt` (non inclus pour raisons de taille) et charger
les configurations depuis `configs/` via la console de chaque équipement.
