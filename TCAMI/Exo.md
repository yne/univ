Conception Multicycle
=====================

Nous souhaitons ajouter au chemin de contrôle multi-cycle (décrit en cours) les éléments du chemin de données et du contrôle nécessaire pour mettre en œuvre les instruction JAL/JR/JALR

1. Quels sont les éléments a ajouter au chemin de données et au lignes de contrôles (on choisira la solution qui minimise le nombre de cycle d'horloge pour les instruction ajouté en justifiant)

2. Donner les étapes d’exécution de chacune de ces instructions de le chemin de données multi cycle en utilisant la décomposition en étages (cf cours)

3. Donner les extension a apporter a la machine a état fini pour mettre en œuvre ces instructions

| NAME | OPCODE | ARGUMENTS                   | CODE           |
|------|--------|-----------------------------|----------------|
| J    | 000010 |         IMM26               | PC=IMM;        |
| JAL  | 000011 |         IMM26               | R31=PC+4;PC=V; |
| JR   | 000000 |Rs5 00000 00000 00000 001000 | PC=Rs          |
| JALR | 000000 |Rs5 00000  Rd5  00000 001001 | Rd=PC+4;PC=Ra; |

Cache-Proba
===========

On se propose d’étudier l’influence de 2 stratégies d'un cache sur sa performance :
Write Back (WB) = MAJ différée de la MC
Write Throught with Write Allocate (WTWA) = MAJ en ligne de la MC avec chargement de bloc en cas de défaut a la fois sur L et E

* h : proba de présence de l'info dans le cache
* Wt: proba que la référence mémoire soit une écriture
* Wm: proba pour que le bloc a remplacer dans le cache ait été modifié
* b : nb de mot dans le bloc
* tm: temps d’accès a la MC
* tc: temps d’accès au cache

Temps de transfert d'un bloc en lecture/MAJ = Tm+b*Tc

1. Donner l'algo détaillé du fonctionnement des deux stratégies proposé en partant d'une demande de L ou E du proc

Write Back
----------
![sgv](https://upload.wikimedia.org/wikipedia/commons/c/c2/Write-back_with_write-allocation.svg)

Write Through
----------
![sgv](https://upload.wikimedia.org/wikipedia/commons/0/04/Write-through_with_no-write-allocation.svg)


2. Établir, pour chaque stratégie de gestion,
le temps d’accès moyen a la hiérarchie de mémoire (cache,MC).
Comparer les 2 stratégie lorsque h tend vers 0 et h tend vers 1

Pour caulculer le temps total il faut faire la somme de toute les (Proba * Temps)

Write through :

| Branche        | Proba            | Temps branche  |
|----------------|------------------|----------------|
|  Read  & hit   |  (1–Wt) *    h   |             Tc |
|  Read  & miss  |  (1–Wt) * (1–h)  | (Tm+b*Tc) + Tc |
|  Write & hit   |     Wt  *    h   |        Tm      |
|  Write & miss  |     Wt  * (1–h)  |        Tm + Tc |

Write Back :

| Branche                 | Proba                          |Temps de la branche      |
|-------------------------|--------------------------------|-------------------------|
| Read  & hit             | (1–Wt) *    h                  |                      Tc |
| Read  & miss & dirt     | (1–Wt) * (1–h) *    Wm         |  2 * (Tm + b * Tc) + Tc |
| Read  & miss & no dirt  | (1–Wt) * (1–h) * (1–Wm)        |      (Tm + b * Tc) + Tc |
| Write & hit             |    Wt  *    h                  |                      Tc |
| Write & miss & dirt     |    Wt  * (1–h) *    Wm         |  2 + (Tm + b * Tc) + Tc |
| Write & miss & no dirt  |    Wt  * (1–h) * (1-Wm)        |      (Tm + b * Tc) + Tc |

3. En prenant tc comme unité de temps, Wt=0.1, Wm=0.4, tm=4*tc et b=4

4. Trouver la valeur de h pour laquelle les deux stratégies ont la même perf.

5. En déduire la stratégie optimal en fonction de la taille du cache

Cache-Remplacement
==================

On considère un calculateur équipé d'un cache a 2 emplacement B0,B1 géré de façon associative (Asso d'ens d'ordre 2) et la succession des ref de bloc suivant :

|     NAME     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 
|--------------|---|---|---|---|---|---|---|---|---|---|---| 
| TRACE BLOC   | a | b | a | c | a | b | d | b | a | c | d | 
| DEFAULT BLOC | v | v |   |   |   |   |   |   |   |   |   | 
| CACHE B0     | a | a | a |   |   |   |   |   |   |   |   | 
| CACHE B1     |   | b | b |   |   |   |   |   |   |   |   | 

Compléter le tableau en utilisant les algo FIFO et LRU.

FIFO
----

|     NAME     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 
|--------------|---|---|---|---|---|---|---|---|---|---|---| 
| TRACE BLOC   | a | b | a | c | a | b | d | b | a | c | d | 
| DEFAULT BLOC | v | v | x | v | v | v | v | x | v | v | v | 
| CACHE B0     | a | a | a | c | c | b | b | b | a | a | d | 
| CACHE B1     |   | b | b | b | a | a | d | d | d | c | c | 

LRU
---

|     NAME     | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 
|--------------|---|---|---|---|---|---|---|---|---|---|---| 
| TRACE BLOC   | a | b | a | c | a | b | d | b | a | c | d | 
| DEFAULT BLOC | v | v | x | v | x | v | v | x | v | v | v | 
| CACHE B0     | a | a | a | a | a | a | d | d | a | a | d | 
| CACHE B1     |   | b | b | c | c | b | b | b | b | c | c | 

1. Donner un synoptique général du cache a 2 emplacement et expliquer comment les bit LRU sont MAJ

```
                 SRAM         DRAM
 ------         -------     --------- 
|      |--+----| CACHE |---|         |
|  UC  |  |     -------    | MEMOIRE |
|      |  |      buffer    | CENTRAL |
 ------   +-----[B0|B1]----|         |
                            ---------
```
 
2. Donner dans chaque cas et pour les référence de bloc considérés,
la probabilité d’absence de l'information dans ce cache

3. Reprendre le même problème avec 3 emplacement de bloc,
Comparer les résultat et en tirer des conclusions

ALEA
====

1. Donner les différents type de déroulement pouvant survenir au niveau de chaque étage du pipeline du R3000

- interruption
- modification de TLB. Cette exception est levée lorsque que l’adresse virtuelle d’une écriture correspond à une entrée de la TLB marqué non-inscriptible
- rechargement de la TLB. Indique que le système d’exploitation doit recharger la TLB pour effectuer une lecture/écriture
- erreur d’adressage lors de la lecture d’une Donnée/Instruction ou de l'ecriture d’une donnée
- erreur lors d’un accès mémoire pour la lecture d’une instruction ou de la L/E d’une donnée
- appel système
- point d’arrêt
- instruction inconnue (ou réservée)
- tentative avortée d’accès à un coprocesseur
- dépassement de capacité lors d’un calcul arithmétique

2. Donner la définition d'une "exception précise"


Exception précise :
--------------------

An interrupt or exception is called precise if the saved processor state corresponds with the sequential model of program execution where one instruction execution ends before the next begins.
Precise exception means that all instructions before the faulting instruction are committed and those after it can be restarted from scratch.
If an interrupt occurred, all instructions that are in program order before the interrupt signaling instruction are committed, and all later instructions are removed.
Depending on the architecture and the type of exception, the faulting instruction should be committed or removed without any lasting effect.

Interruptions précises :
-----------------------

An interrupt that leaves the machine in a well-defined state is called a precise interrupt. Such an interrupt has four properties:
- The Program Counter (PC) is saved in a known place.
- All instructions before the one pointed to by the PC have fully executed.
- No instruction beyond the one pointed to by the PC has been executed (that is no prohibition on instruction beyond that in PC, it is just that any changes they make to registers or memory must be undone before the interrupt happens).
- The execution state of the instruction pointed to by the PC is known.

Type de déroutement :
--------------------

- interruption
- (ME) modification de TLB. Cette exception est levée lorsque que l’adresse virtuelle d’une écriture correspond à une entrée de la TLB marqué non-inscriptible
- (ME) rechargement de la TLB. Indique que le système d’exploitation doit recharger la TLB pour effectuer une lecture/écriture
- (EI/ME) erreur d’adressage lors de la lecture d’une Donnée/Instruction ou de l'ecriture d’une donnée
- (EI) erreur lors d’un accès mémoire pour la lecture d’une instruction ou de la L/E d’une donnée
- (DI) instruction inconnue (ou réservée)
- (EX) appel système
- (EX) point d’arrêt
- (EX) tentative avortée d’accès à un coprocesseur
- (EX) dépassement de capacité lors d’un calcul arithmétique

3. Expliquer comment fonction la solution fondée sur le vecteur de présence d’exception associé a chaque instruction pour rendre les exception précise ?

Interruption
=============
Concevoir le circuit de "daisy chain" qui existe au niveau d'un unité d'E/S de la chaine en lui ajoutant la logique nécessaire pour permettre a l'unité, si elle est prioritaire, de fournir un numéro de vecteur au moment de la reconnaissance d'interruption
Ce circuit reçois en entré : un signal d'interruption provenant des circuit d'interfaces de l'unité elle même (noté IRQi) et le signal PI (entré de priorité/entré du daisi chaine)
et fournit en sortie le signal PO (sortie de priorité/sortie du daisy chain), le domaine d'interruption, et le num de vecteur d'interruption

![](http://www.cs.nyu.edu/courses/fall99/V22.0436-001/daisy-chain.png)
