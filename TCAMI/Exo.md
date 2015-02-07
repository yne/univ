Conception Multicycle
=====================

Nous souhaitons ajouter au chemin de contrôle multi-cycle (décrit en cours) les éléments du chemin de données et du contrôle nécessaire pour mettre en œuvre les instruction JAL/JR/JALR
1. Quels sont les éléments a ajouter au chemin de données et au lignes de contrôles (on choisira la solution qui minimise le nombre de cycle d'horloge pour les instruction ajouté en justifiant)
2. Donner les étapes d’exécution de chacune de ces instructions de le chemin de données multi cycle en utilisant la décomposition en étages (cf cours)
3. Donner les extension a apporter a la machine a état fini pour mettre en œuvre ces instructions

J    = 000010 <         IMM26              > = PC = IMM
JAL  = 000011 <         IMM26              > = R31=PC+4;PC=V;
JR   = 000000 <Rs5> 00000 00000 00000 001000 = PC = Rs
JALR = 000000 <Rs5> 00000 <Rd5> 00000 001001 = Rd = PC+4;PC=Ra

Cache-Proba
===========

On se propose d’étudier l’influence de 2 stratégies d'un cache sur sa performance :
WriteBack = MAJ différée de la MC
Write Throught with Write Allocate = MAJ en ligne de la MC avec chargement de bloc en cas de défaut a la fois sur L et E
h : proba de présence de l'info dans le cache
Wi: proba que la référence mémoire soir une écriture dans le cache
Wm: proba pour que le bloc a remplacer dans le cache ait été modifié
b : nb de mot dans le bloc
tm: temps d’accès a la MC
tc: temps d’accès au cache
Temps de transfert d'un bloc en lecture/MAJ = tm+b*tc

1. Donner l'algo d"taillé du fonctionnement des deux stratégies proposé en partant d'une demande de L ou E du proc
2. Établir, pour chaque stratégie de gestion, le temps d’accès moyen a la hiérarchie
 de mémoire (cache,MC). Comparer les 2 stratégie lorsque h tend vers 0 et h tend vers 1
3. En prenant tc comme unité de temps, Wi=0.1, Wm=0.4, tm=4*tc et b=4 , trouver la valeur de h pour laquelle les deux stratégies ont la même perf. En déduire la stratégie optimal en fonction de la taille du cache

Cache-Remplacement
==================

On considère un calculateur équipé d'un cache a 2 emplacement B0,B1 géré de façon associative (Asso d'ens d'ordre 2) et la succession des ref de bloc suivant :

TRACE BLOC   : a b a c a b d b a c d
DEFAULT BLOC : v v                  
CACHE B0     : a a a                
CACHE B1     : - b b                

Compléter le tableau en utilisant les algo FIFO et LRU.
1. Donner un synoptique général du cache a 2 emplacement et expliquer comment les bit LRU sont MAJ
2. Donner dans chaque cas et pour les référence de bloc considérés, la probabilité d’absence de l'information dans ce cache
3. Reprendre le même problème avec 3 emplacement de bloc, Comparer les résultat et en tirer des conclusions

ALEA
====


1. Donner les différents type de déroulement pouvant survenir au niveau de chaque étage du pipeline du R3000
2. Donner la définition d'une "exception précise"
3. Expliquer comment fonction la solution fondée sur le vecteur de présence d’exception associé a chaque instruction pour rendre les exception précise ?

Interruption
=============
Concevoir le circuit de "daisy chain" qui existe au niveau d'un unité d'E/S de la chaine en lui ajoutant la logique nécessaire pour permettre a l'unité, si elle est prioritaire, de fournir un numéro de vecteur au moment de la reconnaissance d'interruption
Ce circuit reçois en entré : un signal d'interruption provenant des circuit d'interfaces de l'unité elle même (noté IRQi) et le signal PI (entré de priorité/entré du daisi chaine)
et fournit en sortie le signal PO (sortie de priorité/sortie du daisy chain), le domaine d'interruption, et le num de vecteur d'interruption