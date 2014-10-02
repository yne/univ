% 2. Avant de pouvoir manipuler une image sous Matlab, il faut la charger en mémoire.
% Pour cela, nous utilisons la fonction imread de Matlab.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% a. Utiliser la fonction imread pour charger l’image coins.png.
% Nommer I l’image chargée.
I = imread('coin.png');

% b. Quel type d’image est l’image coins.png ?
% Quelle est sa taille ?
imageinfo(I);

% c. Quel est le plus faible niveau de gris présent dans l’image ?
min(min(I));
% Et le plus grand ?
max(max(I));
% Quelle est la moyenne des niveaux de gris de l’image ?
mean(mean(I));

% d. Afficher l’image I en utilisant la fonction imshow.
imshow(I);
% Pour ouvrir une nouvelle figure, il faut taper figure avant d’afficher une image.
imshow(I)
% e. Utiliser la fonction impixelinfo pour avoir des informations sur les pixels de l’image.
imshow(I), impixelinfo;

% f. Charger l’image trees.tif sous Matlab, en exécutant la commande [X,map] = imread(‘trees.tif’).
[X,map] = imread('trees.tif');

% A quoi correspondent les deux variables X et map ?
%>>X est le des valeurs et map la palette de couleur (normalisé de 0 à 1)

% Afficher la variable X, en faisant imshow(x,map). Commenter le résultat.
imshow(X, map);
% g. La commande subplot de Matlab permet d’afficher plusieurs images dans la même figure.
% Afficher I et X dans la même figure (X sera affichée en utilisant map comme précédemment).
subplot(1,2,1), imshow(I);
subplot(1,2,2), imshow(X,map);

% Pourquoi l’image I apparaît-elle différente ?
%>> car la map (palette) est differente

% h. Même question que précédemment, mais en utilisant la fonction subimage
% au lieu de imshow. Commenter sur l’utilité de cette fonction.
subplot(1,2,1), subimage(I);
subplot(1,2,2), subimage(X,map);

% i. Fermez toutes les figures en faisant close all.
close all;

% 3. Quantification des niveaux de gris d’une image
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% a. Reprenez l’image coins.png et afficher la en utilisant la commande
% imshow(I, gray(256)).
I_gray = imshow(I, gray(256));
% A quoi correspond gray(256) ?
%>> a une palette de de 256 nuance de gris

% b. En utilisant la fonction grayslice quantifier l’image précédente
% sur moins de niveaux de gris (128, 64, 32, 16, 8, 4, 2)
% afficher à chaque fois l’image obtenue
subplot(1,8,1), imshow(grayslice(I, 256));
subplot(1,8,2), imshow(grayslice(I, 128));
subplot(1,8,3), imshow(grayslice(I, 64));
subplot(1,8,4), imshow(grayslice(I, 32));
subplot(1,8,5), imshow(grayslice(I, 16));
subplot(1,8,6), imshow(grayslice(I, 8));
subplot(1,8,7), imshow(grayslice(I, 4));
subplot(1,8,8), imshow(grayslice(I, 2));

% Commenter le résultat.
%%>>

% 4. Echantillonnage spatial.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% a. Reprenez l’image initiale et décimer la d’un facteur 2 (et ensuite 3) dans
% chacune des directions de l’espace. Affichez les images résultantes et conclure.
imshow(I(1:2:end, 1:2:end));
imshow(I(1:3:end, 1:3:end));

% b. Comment peut-on augmenter le nombre de pixels ?
% Mettez en pratique cette méthode en vous aidant de la fonction imresize de Matlab.
imshow(imresize(I, 2));

% Commenter les résultats obtenus.
%%>>

% c. Refaites les manipulations en a. et b. de manière séquentielle
modif=imresize(I(1:2:end, 1:2:end), 2)
imshow(modif);
% (décimation suivie de sur-échantillonnage du même ordre)
% et calculer une erreur entre le résultat et l’image initiale.
imabsdiff(I, modif);
% Conclure.
%%>>L'image a perdue en qualité

% 5. Opérations arithmétiques entre les images.
% a. Ajouter ou soustraire une constante :
% a.i. Charger l’image cameraman.tif.
I = imread('cameraman.tif');
% Afficher l’image.
imshow(I);
% Ajouter une constante à l’image (50)
light = imadd(I, 50); % eq : I+50
% afficher l’image résultante.
imshow(light);
% Commenter le résultat.
%>>L'image est plus clair

% a.ii. Dans la question précédente
% quelles sont les valeurs min et max de l’image résultat ?
min(min(light));
max(max(light));

% Quelle opération doit-on faire pour afficher proprement cette image ?
%>> appliquer un ratio plutot que de tout augmenter
% Réaliser la (attention au format des données !)
Imlt=immultiply(I, 1.5);
% et afficher la nouvelle image.
imshow(Imlt);
% Commenter le résultat.
%>>le noir reste noir et le gris est plus clair

% a.iii. Même questions que les deux précédentes, mais en soustrayant une
% constante à l’image initiale.
imshow((I-128)+128);
% a.iv. Calculer et afficher le négatif de l’image.
imshow(imcomplement(I));

% b. Multiplier ou diviser l’image initiale par un coefficient (0.7)
Imult=immultiply(I, 0.7);
% afficher le résultat.
% Commenter les deux images obtenues.
subplot(1,2,1), imshow(I);
subplot(1,2,2), imshow(Imult);
%>>l'image est plus foncée

% c. Charger les images gradient.tif et gradient_with_text.tif.
gradient=imread('gradient.tif');
gradient_text=imread('gradient_with_text.tif');
% La deuxième pourrait représenter un document scanné sous conditions de changement d’illumination.
% L’objectif est de retrouver une image binaire (fond en noir et texte en blanc).
imshow(gradient);
imshow(gradient_with_text);

% c.i. Une première méthode consisterait à seuiller l’image. Pour cela, on
% utilise d’abord la fonction Matlab graythresh qui permet de fournir
% automatiquement un seuil ‘optimal’ adapté à notre image. Ce niveau
% sera ensuite utiliser avec la fonction im2bw pour binariser l’image
% originale. Afficher et commenter le résultat obtenu.
gradient_text_nb_1 = im2bw(gradient, graythresh(gradient_with_text));
imshow(gradient_text_nb_1);

% c.ii. La deuxième méthode consiste à diviser (imdivide) les deux images
% chargées précédemment. Faites cette opération et afficher le résultat
% (faites attention aux valeurs obtenues !). Commenter le résultat.
% c.iii. Est-ce que cette deuxième méthode pourrait être utilisée si on ne
% connaissait pas l’image gradient ?
gradient_text_nb_2 = imdivide(gradient, 255);
imshow(gradient_text_nb_2);

% 6. Opérations géométriques.
% a. Charger l’image cameraman.tif.
% a.i. Tourner la de 90° et 180°.
imshow(imrotate(I, 90));
imshow(imrotate(I, 180));
% a.ii. Utiliser la fonction imrotate pour tourner l’image de 35°.
imshow(imrotate(I, 35));
% Quelle est la taille de la nouvelle image ?
size(imrotate(I, 35));
%%>>l'image est plus grande

% Quelles sont les paramètres de la fonction imrotate ?
%>>imrotate(A,angle,method,bbox)
% En quoi influencent-ils le résultat ?
%>>method = algo de calcule des point intermediaire (nearest,bilinear,bicubic)
%>>bbox = gestion des bordure (crop,loose)

imshow(imrotate(I, 35, 'nearest', 'crop'));
