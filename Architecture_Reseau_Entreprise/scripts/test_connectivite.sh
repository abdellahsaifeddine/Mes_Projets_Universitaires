#!/bin/bash
# ============================================================
# Script de test de connectivité inter-VLANs
# Auteur : SAIFEDDINE Abdellah
# Universite de Poitiers - L2 Réseaux - 2024-2025
#
# Usage : ./test_connectivite.sh
# Nécessite : ping disponible sur le système
# ============================================================

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PASS=0
FAIL=0

ping_test() {
    local description=$1
    local target=$2
    local expected=$3  # "ok" ou "fail"

    ping -c 2 -W 1 "$target" > /dev/null 2>&1
    result=$?

    if [ $result -eq 0 ]; then
        if [ "$expected" = "ok" ]; then
            echo -e "  ${GREEN}[OK]${NC}   $description ($target)"
            ((PASS++))
        else
            echo -e "  ${RED}[KO]${NC}   $description ($target) — devrait être BLOQUÉ"
            ((FAIL++))
        fi
    else
        if [ "$expected" = "fail" ]; then
            echo -e "  ${GREEN}[OK]${NC}   $description ($target) — correctement BLOQUÉ"
            ((PASS++))
        else
            echo -e "  ${RED}[KO]${NC}   $description ($target) — devrait être ACCESSIBLE"
            ((FAIL++))
        fi
    fi
}

echo "============================================================"
echo "  Test de connectivité — SaifNet Corp"
echo "  Auteur : SAIFEDDINE Abdellah"
echo "============================================================"
echo ""

echo -e "${YELLOW}[1] Passerelles VLANs — Siège${NC}"
ping_test "Passerelle VLAN10 Direction"    "192.168.10.1"  "ok"
ping_test "Passerelle VLAN20 DSI"          "192.168.20.1"  "ok"
ping_test "Passerelle VLAN30 Serveurs"     "192.168.30.1"  "ok"
ping_test "Passerelle VLAN40 DMZ"          "192.168.40.1"  "ok"
echo ""

echo -e "${YELLOW}[2] Serveurs internes — Siège${NC}"
ping_test "Serveur de fichiers"            "192.168.30.10" "ok"
ping_test "Active Directory / DNS interne" "192.168.30.11" "ok"
ping_test "Serveur d'impression"           "192.168.30.12" "ok"
echo ""

echo -e "${YELLOW}[3] DMZ — Serveurs publics${NC}"
ping_test "Serveur Web (Apache)"           "192.168.40.10" "ok"
ping_test "Serveur Mail (Postfix)"         "192.168.40.11" "ok"
ping_test "Serveur DNS public (BIND)"      "192.168.40.12" "ok"
echo ""

echo -e "${YELLOW}[4] Agences — Passerelles${NC}"
ping_test "Passerelle VLAN50 Commercial"   "192.168.50.1"  "ok"
ping_test "Passerelle VLAN60 RH"           "192.168.60.1"  "ok"
ping_test "Passerelle VLAN70 R&D"          "192.168.70.1"  "ok"
ping_test "Passerelle VLAN80 Support"      "192.168.80.1"  "ok"
echo ""

echo -e "${YELLOW}[5] Liens WAN inter-sites${NC}"
ping_test "R0 Siege  → R1 Bordeaux"        "10.0.0.2"      "ok"
ping_test "R0 Siege  → R2 Paris"           "10.0.1.2"      "ok"
echo ""

echo -e "${YELLOW}[6] Management${NC}"
ping_test "R0 Siege (management)"          "192.168.99.2"  "ok"
ping_test "R1 Bordeaux (management)"       "192.168.99.3"  "ok"
ping_test "R2 Paris (management)"          "192.168.99.4"  "ok"
ping_test "SW Siege (management)"          "192.168.99.5"  "ok"
echo ""

echo -e "${YELLOW}[7] Tests de sécurité — trafic BLOQUÉ attendu${NC}"
ping_test "RH → R&D (doit être bloqué)"    "192.168.70.10" "fail"
echo ""

echo "============================================================"
echo -e "  Résultats : ${GREEN}$PASS OK${NC} / ${RED}$FAIL ÉCHEC${NC}"
echo "============================================================"

if [ $FAIL -eq 0 ]; then
    echo -e "  ${GREEN}Tous les tests sont passés. Architecture conforme.${NC}"
    exit 0
else
    echo -e "  ${RED}$FAIL test(s) en échec. Vérifier les configurations.${NC}"
    exit 1
fi
