Introduction
============

L'architecture RMI permet de créer des réseau complexe depuis Java. Dans ce TP cet
architecture sera utilisée pour mettre en place un réseau Chord. Devant les libertés offertes par
le sujet nous avons pris certain décisions comme par exemple l’utilisation d’un système de
bootstrap plutôt que de donner une adresse de peering à chaque nouveau noeud, nous nous
sommes pour cela inspiré de la philosophie du protocole bittorent :
http://engineering.bittorrent.com/2013/12/19/dht­bootstrap­update/.
Note : Suite à un malentendu sur l’organisation des séances de TP, une grande partie du projet
à été réalisée en binôme avec Thomas B, comme nous vous en avons informé en
TD. Il se peut donc que les codes source des projets soient fortement similaires.

Travail Réalisé
============

Note : L’algorithme a été modifier suite a la remarque faite lors de la recette sur le fait que
l'algorithme n’est pas repartie sur plusieurs serveur. L’archive source contient donc 2 projets :

Chord_Local (version évalué lors de la recette)
- Le programme principale se connecte au serveur RMI lancé localement.
- Les nodes s’enregistre sur le registry de ce serveur.
- Il y a donc 1 server avec N entrée dans la registry RMI pour N noeud

Chord_Multi
- Le programme principale lance une série de serveur RMI.
- Les noeud sont a la fois client et serveur et s’enregsitre sur le registry.
- Il y a donc N server avec 1 entrée dans chaque RMI registry pour N noeud
Ce changement de paradigme n’a pas été très simple à mettre en place car l’algorithme de
chord est indépendant de la sous­couche (Notre première implémentation était basé sur un
HashMap puis porté en RMI donc un problème similaire c'était déjà posé par le passé)
Dans ces 2 cas, et conformément au sujet, tout les échanges sont effectué via RMI.
En plus de cet exigence, le projet répond a toute les autres exigences a savoir :
- Ajout d’un nœud dans le cercle
- Départ d’un nœud du cercle
- Gestion du « forwarding » des requêtes (avec et sans finger table)
- Gestion de la réplication des données
- Génération de statistiques

Exécution
============

Pour lancer le programme il suffit :
1. d’importer l’archive des sources dans eclise(via File>Import)
2. puis de lancer le main() de la class Chord du projet Chord_local ou Chord_Multi

Techniques utilisées
====================

Le code est repartie sur plusieurs classes :
- Chord : Classe permettant d'exécuter différents scénarios (test case) tel que la création
d’un réseau identique a celui vue en TD.
- Node : Classe principale du projet, c’est elle qui contient l'algorithme de chord. Elle met a
disposition (via son interface Node_I) ses méthode pour une utilisation via RMI
- Node_Stat : Classe proxy de Node, propose les mêmes fonctionnalité que Node, mais
enregistre chaque appelle de méthode en vue de générer des statistiques.
- Key : classe static qui ne fait que proposer une méthodes de hashage pour la génération
de clef ainsi que la verification pour savoir si une clef est comprise entre deux autre clef.
Nous avons décidés de la rendre indépendante de la classe Node car ses fonctionnalités
sont indépendantes de l’algorithme de chord.

Résultats Obtenus
=================

- La mise en place du cercle initial fonctionne via la technique du bootstrap.
- Marche en mode 1 registry RMI pour N Node et pour 1 Registry par Node
Affichage des port utilisé par java lors de l’execution du test Case “TD”
Les Noeud 1,6,8,13,15 ouvrent les port 1106,1108,1113,1115
(le port 1099 etant le node 1 mis en boostrap)
- L’ajout d’un noeud peu s’effectuer soit de façon simple par une série d'appel a
la méthode findSucc, ou bien en utilisant le findSuccFT qui passera par la
FingerTable pour placer le point plus vite.
- Gestion du veritable voisinage lors de l’ajout se fait grâce au attribut succ et pred
- Lors de l’ajout les noeud le succ update son attribut prec pour pointer vers le
nouveau noeud et inversement pour le pred. Pour vérifier, nous avons recréer les
même noeud qu’en TD (1,6,8,13,15) et les finger tables correspondes au
resultats trouvés en TD :

Node : 1 data : 0 pred : 15 succ : 6 Fingers:6 6 6 13
Node : 6 data : 1 pred : 1 succ : 8 Fingers:8 8 13 15
Node : 8 data : 2 pred : 6 succ : 13 Fingers:13 13 13 1
Node : 13 data : 1 pred : 8 succ : 15 Fingers:15 15 1 6
Node : 15 data : 0 pred : 13 succ : 1 Fingers:1 1 6 8

- Le départ d’un noeud est géré en mettant a jours ses succ/pred et en updatant les
fingertable de tout les noeud. Voici la liste des noeud avec leur Finger(Table)

Node : 1 data : 0 pred : 15 succ : 6 Fingers:6 6 6 15
Node : 6 data : 1 pred : 1 succ : 8 Fingers:8 8 15 15
Node : 8 data : 2 pred : 6 succ : 15 Fingers:15 15 15 1
Node : 15 data : 1 pred : 8 succ : 1 Fingers:1 1 6 8

On remarque qu'après le départ du noeud 13, (cf tableau au dessus) les fingers table
sont bien mises a jours .
- La réplication (avec k=2) fonctionne et gère le départ d’un noeud
- On remarque qu'après le départ du noeud 13, les données sont bien transférées
au successeur.
- La génération de statistiques a permit de visualiser l'évolution des performances selon
plusieurs critère (nombre de noeud présent, taille de la FT, etc.)
- Ici nous constatons que la taille de la FT permet de diminuer grandement (l'échelle est
logarithmique) le nombre de forward nécessaire pour atteindre un noeud.
Mise en perspective
Pour des raisons de simplicité le système actuelle repose sur le système de bootstrap, ce qui
peu s’avérer être problématique sur ce dernier décide de quitter le cercle.Il faudrais donc
implémenter une solutions qui en cas de départ du bootstrap permettant a son successeur de
prendre les responsabilités de ce dernier.
