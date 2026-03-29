# Politique de Sécurité — SaifNet Corp
**Auteur : SAIFEDDINE Abdellah**

---

## 1. Principes généraux

La politique de sécurité repose sur le principe du **moindre privilège** :
tout trafic est interdit par défaut, seul le trafic explicitement autorisé
est permis. Les ACL sont appliquées au plus près de la source.

---

## 2. Zones de sécurité

```
[Internet] → [DMZ] → [Réseau interne]
              ↑
         [Firewall ASA]
```

| Zone | Niveau de confiance | Contenu |
|---|---|---|
| Outside (Internet) | 0 | Non fiable |
| DMZ | 50 | Serveurs publics (Web, Mail, DNS) |
| Inside (LAN) | 100 | Réseau interne |

**Règles inter-zones :**
- Internet → DMZ : HTTP(80), HTTPS(443), SMTP(25), DNS(53) autorisés
- DMZ → Inside : INTERDIT (la DMZ ne peut pas initier vers le LAN)
- Inside → DMZ : autorisé (les employés peuvent accéder aux serveurs DMZ)
- Inside → Internet : HTTP, HTTPS, DNS autorisés via NAT/PAT

---

## 3. ACL sur les routeurs

### R0 — Siège (interface WAN entrante)

```
! Bloquer les adresses RFC 1918 venant d'Internet (anti-spoofing)
deny ip 10.0.0.0 0.255.255.255 any
deny ip 172.16.0.0 0.15.255.255 any
deny ip 192.168.0.0 0.0.255.255 any
! Autoriser le trafic établi (réponses)
permit tcp any any established
! Autoriser HTTP/HTTPS vers la DMZ
permit tcp any host 192.168.40.10 eq 80
permit tcp any host 192.168.40.10 eq 443
permit tcp any host 192.168.40.11 eq 25
permit tcp any host 192.168.40.12 eq 53
permit udp any host 192.168.40.12 eq 53
! Tout le reste est bloqué
deny ip any any log
```

### ACL inter-VLANs (appliquée sur SW_Siege L3)

```
! VLAN RH (60) ne peut PAS accéder à la R&D (70)
deny ip 192.168.60.0 0.0.0.31 192.168.70.0 0.0.0.63
! Direction (10) peut accéder à tout
permit ip 192.168.10.0 0.0.0.63 any
! DSI (20) peut accéder à tout (administration)
permit ip 192.168.20.0 0.0.0.63 any
! Serveurs (30) ne communiquent qu'avec DSI et Direction
permit ip 192.168.30.0 0.0.0.31 192.168.10.0 0.0.0.63
permit ip 192.168.30.0 0.0.0.31 192.168.20.0 0.0.0.63
deny ip 192.168.30.0 0.0.0.31 any
! Utilisateurs → Internet via NAT
permit ip 192.168.0.0 0.0.255.255 any
```

---

## 4. NAT/PAT

Le NAT est configuré sur R0 avec une seule IP publique (PAT) :

```
! Interface outside (vers Internet)
ip nat outside → interface GigabitEthernet0/0

! Interface inside (vers LAN)
ip nat inside → interface GigabitEthernet0/1

! ACL définissant les réseaux à natter
access-list 10 permit 192.168.0.0 0.0.255.255

! PAT avec l'IP de l'interface WAN
ip nat inside source list 10 interface GigabitEthernet0/0 overload
```

---

## 5. Sécurité sur les switches

### Port Security (switch accès)
```
! Activer port security sur chaque port accès
switchport port-security
switchport port-security maximum 1
switchport port-security mac-address sticky
switchport port-security violation shutdown
```

### Désactivation des ports inutilisés
```
interface range FastEthernet0/20 - 24
 shutdown
 description PORT_INUTILISE
```

### Protection contre le VLAN hopping
```
! Désactiver DTP sur les ports accès
switchport mode access
switchport nonegotiate
! VLAN natif différent du VLAN 1 sur les trunks
switchport trunk native vlan 999
```

---

## 6. Sécurisation des accès d'administration

```
! Mot de passe enable chiffré
enable secret SaifNet@2024!

! Accès console
line console 0
 password Console@2024
 login
 exec-timeout 5 0

! SSH uniquement (pas Telnet)
ip domain-name saifnet.local
crypto key generate rsa modulus 2048
ip ssh version 2
line vty 0 4
 transport input ssh
 login local
 exec-timeout 10 0

! Compte administrateur local
username admin privilege 15 secret Admin@2024!

! Bannière d'avertissement
banner motd # Acces reserve au personnel autorise SaifNet Corp #
```
