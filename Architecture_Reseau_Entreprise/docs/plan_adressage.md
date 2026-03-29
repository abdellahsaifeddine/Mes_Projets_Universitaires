# Plan d'Adressage IPv4 — SaifNet Corp
**Auteur : SAIFEDDINE Abdellah**

---

## 1. Réseau global

Le réseau privé de SaifNet Corp utilise la plage **192.168.0.0/16**.
Chaque site dispose de sa propre plage, segmentée en VLANs.

| Site | Plage attribuée | Masque |
|---|---|---|
| Siège Poitiers | 192.168.10.0 — 192.168.49.255 | Variable |
| Agence Bordeaux | 192.168.50.0 — 192.168.69.255 | Variable |
| Agence Paris | 192.168.70.0 — 192.168.89.255 | Variable |
| Management | 192.168.99.0/28 | 255.255.255.240 |

---

## 2. Liens WAN inter-sites (point à point)

Les liens WAN entre les sites utilisent des /30 (2 hôtes utiles par lien).

| Lien | Réseau | R0 (Siège) | R1/R2 (Agence) |
|---|---|---|---|
| Siège ↔ Bordeaux | 10.0.0.0/30 | 10.0.0.1 | 10.0.0.2 |
| Siège ↔ Paris | 10.0.1.0/30 | 10.0.1.1 | 10.0.1.2 |

---

## 3. Siège — Poitiers

### VLAN 10 — Direction
```
Réseau   : 192.168.10.0/26
Masque   : 255.255.255.192
Passerelle : 192.168.10.1
DHCP pool  : 192.168.10.10 — 192.168.10.60
Broadcast  : 192.168.10.63
Hôtes max  : 62
```

### VLAN 20 — DSI (Informatique interne)
```
Réseau   : 192.168.20.0/26
Masque   : 255.255.255.192
Passerelle : 192.168.20.1
DHCP pool  : 192.168.20.10 — 192.168.20.60
Broadcast  : 192.168.20.63
Hôtes max  : 62
```

### VLAN 30 — Serveurs internes
```
Réseau   : 192.168.30.0/27
Masque   : 255.255.255.224
Passerelle : 192.168.30.1
Adresses statiques uniquement :
  - 192.168.30.10 : Serveur de fichiers
  - 192.168.30.11 : Active Directory / DNS interne
  - 192.168.30.12 : Serveur d'impression
  - 192.168.30.13 : Serveur de sauvegarde
Broadcast  : 192.168.30.31
Hôtes max  : 30
```

### VLAN 40 — DMZ
```
Réseau   : 192.168.40.0/28
Masque   : 255.255.255.240
Passerelle : 192.168.40.1
Adresses statiques uniquement :
  - 192.168.40.10 : Serveur Web (Apache)
  - 192.168.40.11 : Serveur Mail (Postfix)
  - 192.168.40.12 : Serveur DNS public (BIND)
Broadcast  : 192.168.40.15
Hôtes max  : 14
```

---

## 4. Agence Bordeaux

### VLAN 50 — Commercial
```
Réseau   : 192.168.50.0/26
Masque   : 255.255.255.192
Passerelle : 192.168.50.1
DHCP pool  : 192.168.50.10 — 192.168.50.50
Broadcast  : 192.168.50.63
Hôtes max  : 62
```

### VLAN 60 — Ressources Humaines
```
Réseau   : 192.168.60.0/27
Masque   : 255.255.255.224
Passerelle : 192.168.60.1
DHCP pool  : 192.168.60.10 — 192.168.60.28
Broadcast  : 192.168.60.31
Hôtes max  : 30
```

---

## 5. Agence Paris

### VLAN 70 — R&D
```
Réseau   : 192.168.70.0/26
Masque   : 255.255.255.192
Passerelle : 192.168.70.1
DHCP pool  : 192.168.70.10 — 192.168.70.40
Broadcast  : 192.168.70.63
Hôtes max  : 62
```

### VLAN 80 — Support
```
Réseau   : 192.168.80.0/27
Masque   : 255.255.255.224
Passerelle : 192.168.80.1
DHCP pool  : 192.168.80.10 — 192.168.80.28
Broadcast  : 192.168.80.31
Hôtes max  : 30
```

---

## 6. VLAN Management (tous sites)

```
Réseau   : 192.168.99.0/28
Masque   : 255.255.255.240
Passerelle : 192.168.99.1
Adresses statiques :
  - 192.168.99.2  : R0 (Siège)
  - 192.168.99.3  : R1 (Bordeaux)
  - 192.168.99.4  : R2 (Paris)
  - 192.168.99.5  : SW_Siege (interface VLAN 99)
  - 192.168.99.6  : SW_Bordeaux
  - 192.168.99.7  : SW_Paris
  - 192.168.99.8  : Firewall ASA
Broadcast  : 192.168.99.15
Hôtes max  : 14
```

---

## 7. Justification du découpage CIDR

J'ai choisi de sur-dimensionner légèrement chaque sous-réseau (+20% par rapport
aux besoins actuels) pour anticiper la croissance de l'entreprise sans avoir à
re-adresser le réseau. Le /26 (62 hôtes) pour les grands VLANs et le /27 (30 hôtes)
pour les petits départements permet une utilisation efficace de l'espace d'adressage
tout en laissant de la marge.

Le VLAN Management en /28 est volontairement petit (14 hôtes) car seuls
les équipements actifs (routeurs, switches, firewall) y sont connectés.
Cela limite la surface d'attaque sur ce réseau critique.
