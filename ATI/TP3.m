%Rappelez la d�finition de l�histogramme d�une image. En utilisant l�aide de Matlab, trouvez la
%fonction qui calcule l�histogramme d�une image et la fa�on dont elle doit �tre utilis�e (param�tres d�entr�e, de sortie).
im=imread('circuit.tif');
imhist(im);

vec=im(:);
%1. Dans la m�me figure, afficher l�image circuit.tif et son histogramme, en utilisant un nombre de bins diff�rent
subplot(2,2,1), imshow(im);
subplot(2,2,2), hist(double(vec));
subplot(2,2,3), hist(double(vec),length(vec));
subplot(2,2,4), imhist(im,64);

%Conclure sur l�utilit� de cette deuxi�me variable d�entr�e de la fonction
%>> Elle permet de specifier le nombre de barre de notre histo Matlab qui calcule l�histogramme.

%Expliquer pourquoi les valeurs sur l�axe des ordonn�es des histogrammes changent quand on change le nombre de bins.
%>> Car l'histo est cummul�

%2. Ajouter une constante � l�image
im_light=im+64;
% retracer l�histogramme.
subplot(2,2,1), imshow(im);
subplot(2,2,2), imshow(im_light);
subplot(2,2,3), hist(double(im(:)),0:1:255);
subplot(2,2,4), hist(double(im_light(:)),0:1:255);

% Commenter le r�sultat.
%>> l'histo est shift� sur la droite

%3. Appliquer un seuillage � l�image
im_seuil = zeros(size(im));
im_seuil( im > 64 ) = 1;
% retracer l�histogramme.
subplot(2,3,1), imshow(im);
subplot(2,3,2), imshow(im_light);
subplot(2,3,3), imshow(im_seuil);
subplot(2,3,4), hist(double(im      (:)),0:1:255);
subplot(2,3,5), hist(double(im_light(:)),0:1:255);
subplot(2,3,6), hist(double(im_seuil(:)),2);

%Commenter le r�sultat.
%>> il n'y a que 2 valeur et c'est trop cool

%4. R�cup�rer dans une variable les valeurs de bins.
[n,bin]=hist(double(im_seuil(:)));
%Normaliser les
binN=bin/sum(bin);
%v�rifier que la somme des valeurs normalis�es donne 1.
sum(binN)
%Afficher l�histogramme normalis� en utilisant la fonction bar de Matlab.
bar(binN);

%5. Charger l�image pout.tif
im=imread('pout.tif');
% Egaliser son histogramme en utilisant la m�thode du cours et en passant par une fonction Matlab.
histeq(im);%prend l'histo de l'image,la normaliser et la reaffiche
% Comparer les deux r�sultats.

% Afficher l�image originale, son histogramme,
% son histogramme normalis� et l�image finale.
newmap=histeq(im);
subplot(2,2,1), imshow(im);
subplot(2,2,2), hist(double(im));
subplot(2,2,3), histeq(im);
subplot(2,2,4), hist(newmap);

%Afficher les histogrammes cumul�s des images originales et finales
%commenter la diff�rence entre le deux.

%6. M�me question que 5. Pour l�image tire.tif. Expliquer le r�sultat.
subplot(1,2,1), subimage(circuit), subplot(1,2,2), histeq(circuit);
pout = imread('pout.tif');
subplot(1,2,1), subimage(pout);
subplot(1,2,2), histeq(pout);

tire = imread('tire.tif');
subplot(1,2,1), subimage(tire);
subplot(1,2,2), histeq(tire);

%7. Quelle op�ration effectue la fonction adapthisteq sur une image ? Appliquer la � l�image
%coins.png et comparer le r�sultat � une �galisation d�histogramme classique.

subplot(1,3,1), subimage(coin);
subplot(1,3,2), subimage(adapthisteq(coin));
subplot(1,3,3), subimage(histeq(coin));

%
% Convolution et filtrage dans le domaine spatial
%

%Cr�er deux vecteurs
a = [0 0 0 1 0 0 0];
f = [1 2 3 4 5];
%a. Calculer la convolution de a par f, en utilisant la fonction imfilter de Matlab.
af_conv=imfilter(a,f,'conv');

%Utiliser l�aide de Matlab pour comprendre les options de la fonction imfilter.
%b. M�me question pour le calcul de la corr�lation.
af_corr=imfilter(a,f,'corr');

%c. Dans les deux cas et en fonction de l�option choisie,
%quelle est le lien entre la longueur du vecteur de sortie (convolution ou corr�lation) et la longueur des deux vecteurs a et f ?

%2. M�mes questions qu�en 1 pour deux matrices x y
x = [140 108 94 ;89 99 125 ; 121 134 221];
y = [-1 0 1 ;-2 0 2 ;-1 0 1];
xy_conv=imfilter(x,y,'conv');
xy_corr=imfilter(x,y,'corr');

%3. Filtres moyenneurs.
%a. Appliquer un filtre moyenneur de taille 3�3 � l�image cameraman.tiff.
im=imread('cameraman.tif');
m1=[1 1 1 ; 1 1 1; 1 1 1]/9;
im_flou=imfilter(im,m1,'conv');
%Commenter le r�sultat.
%Comment doit-on proc�der pour filtrer davantage l�image ? Montrer le nouveau r�sultat.
%b. Afin de donner plus d�importance au pixel central, filtrer l�avec m2...
m2=[1 2 1 ;2 4 2 ;1 2 1] / 16;
im_filtre=imfilter(im,m2,'conv');

%Comparaison

[L,C]=size(im);

subplot(1,4,1), imshow(im);
subplot(1,4,2), imshow(im_flou);
subplot(1,4,3), imshow(im_filtre);
subplot(1,4,4), imshow(im+randn(L,C));


