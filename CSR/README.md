Introduction
============

L'architecture RMI permet de cr�er des r�seau complexe depuis Java. Dans ce TP cet
architecture sera utilis�e pour mettre en place un r�seau Chord. Devant les libert�s offertes par
le sujet nous avons pris certain d�cisions comme par exemple l�utilisation d�un syst�me de
bootstrap plut�t que de donner une adresse de peering � chaque nouveau noeud, nous nous
sommes pour cela inspir� de la philosophie du protocole bittorent :
http://engineering.bittorrent.com/2013/12/19/dht�bootstrap�update/.
Note : Suite � un malentendu sur l�organisation des s�ances de TP, une grande partie du projet
� �t� r�alis�e en bin�me avec Thomas BRUNELLA, comme nous vous en avons inform� en
TD.�Il�se�peut�donc�que�les�codes�source�des�projets�soient�fortement�similaires.

Travail R�alis�
============

Note : L�algorithme a �t� modifier suite a la remarque faite lors de la recette sur le fait que
l'algorithme�n�est�pas�repartie�sur�plusieurs�serveur.�L�archive�source�contient�donc�2�projets�:

Chord_Local�(version��valu�lors�de�la�recette)
- Le�programme�principale�se�connecte�au�serveur�RMI�lanc�localement.
- Les�nodes�s�enregistre�sur�le�registry�de�ce�serveur.
- Il�y�a�donc�1�server�avec�N�entr�e�dans�la�registry�RMI�pour�N�noeud

Chord_Multi
- Le�programme�principale�lance�une�s�rie�de�serveur�RMI.
- Les�noeud�sont�a�la�fois�client�et�serveur�et�s�enregsitre�sur�le�registry.
- Il�y�a�donc�N�server�avec�1�entr�e�dans�chaque�RMI�registry�pour�N�noeud
Ce changement de paradigme n�a pas �t� tr�s simple � mettre en place car l�algorithme de
chord est ind�pendant de la sous�couche (Notre premi�re impl�mentation �tait bas� sur un
HashMap�puis�port�en�RMI�donc�un�probl�me�similaire�c'�tait�d�j�pos�par�le�pass�)
Dans�ces�2�cas,�et�conform�ment�au�sujet,�tout�les��changes�sont�effectu�via�RMI.
En�plus�de�cet�exigence,�le�projet�r�pond�a�toute�les�autres�exigences�a�savoir�:
- Ajout�d�un�n�ud�dans�le�cercle
- D�part�d�un�n�ud�du�cercle
- Gestion�du���forwarding���des�requ�tes�(avec�et�sans�finger�table)
- Gestion�de�la�r�plication�des�donn�es
- G�n�ration�de�statistiques

Ex�cution
============

Pour�lancer�le�programme�il�suffit�:
1. d�importer�l�archive�des�sources�dans�eclise(via�File>Import)
2. puis�de�lancer�le�main()�de�la�class�Chord�du�projet�Chord_local�ou�Chord_Multi

Techniques utilis�es
====================

Le�code�est�repartie�sur�plusieurs�classes�:
- Chord : Classe permettant d'ex�cuter diff�rents sc�narios (test case) tel que la cr�ation
d�un�r�seau�identique�a�celui�vue�en�TD.
- Node : Classe principale du projet, c�est elle qui contient l'algorithme de chord. Elle met a
disposition�(via�son�interface�Node_I)�ses�m�thode�pour�une�utilisation�via�RMI
- Node_Stat : Classe proxy de Node, propose les m�mes fonctionnalit� que Node, mais
enregistre�chaque�appelle�de�m�thode�en�vue�de�g�n�rer�des�statistiques.
- Key : classe static qui ne fait que proposer une m�thodes de hashage pour la g�n�ration
de clef ainsi que la verification pour savoir si une clef est comprise entre deux autre clef.
Nous avons d�cid�s de la rendre ind�pendante de la classe Node car ses fonctionnalit�s
sont�ind�pendantes�de�l�algorithme�de�chord.

R�sultats Obtenus
=================

- La�mise�en�place�du�cercle�initial�fonctionne�via�la�technique�du�bootstrap.
- Marche�en�mode�1�registry�RMI�pour�N�Node�et�pour�1�Registry�par�Node
Affichage�des�port�utilis�par�java�lors�de�l�execution�du�test�Case��TD�
Les�Noeud�1,6,8,13,15�ouvrent�les�port�1106,1108,1113,1115
(le�port�1099�etant�le�node�1�mis�en�boostrap)
- L�ajout d�un noeud peu s�effectuer soit de fa�on simple par une s�rie d'appel a
la m�thode findSucc, ou bien en utilisant le findSuccFT qui passera par la
FingerTable�pour�placer�le�point�plus�vite.
- Gestion�du�veritable�voisinage�lors�de�l�ajout�se�fait�gr�ce�au�attribut�succ�et�pred
- Lors de l�ajout les noeud le succ update son attribut prec pour pointer vers le
nouveau noeud et inversement pour le pred. Pour v�rifier, nous avons recr�er les
m�me noeud qu�en TD (1,6,8,13,15) et les finger tables correspondes au
resultats�trouv�s�en�TD�:

Node : 1 data : 0 pred : 15 succ : 6 Fingers:6 6 6 13
Node : 6 data : 1 pred : 1 succ : 8 Fingers:8 8 13 15
Node : 8 data : 2 pred : 6 succ : 13 Fingers:13 13 13 1
Node : 13 data : 1 pred : 8 succ : 15 Fingers:15 15 1 6
Node : 15 data : 0 pred : 13 succ : 1 Fingers:1 1 6 8

- Le d�part d�un noeud est g�r� en mettant a jours ses succ/pred et en updatant les
fingertable�de�tout�les�noeud.�Voici�la�liste�des�noeud�avec�leur�Finger(Table)

Node : 1 data : 0 pred : 15 succ : 6 Fingers:6 6 6 15
Node : 6 data : 1 pred : 1 succ : 8 Fingers:8 8 15 15
Node : 8 data : 2 pred : 6 succ : 15 Fingers:15 15 15 1
Node : 15 data : 1 pred : 8 succ : 1 Fingers:1 1 6 8

On remarque qu'apr�s le d�part du noeud 13, (cf tableau au dessus) les fingers table
sont�bien�mises�a�jours .
- La�r�plication�(avec�k=2)�fonctionne�et�g�re�le�d�part�d�un�noeud
- On remarque qu'apr�s le d�part du noeud 13, les donn�es sont bien transf�r�es
au�successeur.
- La g�n�ration de statistiques a permit de visualiser l'�volution des performances selon
plusieurs�crit�re�(nombre�de�noeud�pr�sent,�taille�de�la�FT,�etc.)
- Ici nous constatons que la taille de la FT permet de diminuer grandement (l'�chelle est
logarithmique)�le�nombre�de�forward�n�cessaire�pour�atteindre�un�noeud.
Mise en perspective
Pour des raisons de simplicit� le syst�me actuelle repose sur le syst�me de bootstrap, ce qui
peu s�av�rer �tre probl�matique sur ce dernier d�cide de quitter le cercle.Il faudrais donc
impl�menter une solutions qui en cas de d�part du bootstrap permettant a son successeur de
prendre�les�responsabilit�s�de�ce�dernier.