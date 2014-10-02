l = 4;
c = 2;
% Transformations appliquées aux niveaux de gris, de la forme s = f(r), ou où s représente le
% niveau de gris de sortie et r le niveau de gris de l’image originale.
% 1. Transformations linéaires appliquées aux niveaux de gris :
im_ori=imread('moon.tif');
% a. Créer et afficher (avec plot) la transformation identité
t_idt=uint8(0:1:255);
plot(t_idt);
% appliquer la à l’image moon.tif.
im_idt=(t_idt(im_ori+1));
% Afficher les deux images et conclure.
subplot(l,c,1), imshow(im_ori);
subplot(l,c,2), plot  (im_ori);
subplot(l,c,3), imshow(im_idt);
subplot(l,c,4), plot  (im_idt);

% b. Créer et afficher (avec plot) la transformation qui permet de calculer le
% négatif d’une image codées sur 8 bits. Appliquer la à l’image moon.tif et
t_inv=uint8(255:-1:0);
im_inv=(t_inv(im_ori+1));
% afficher les deux images dans la même figure.
subplot(l,c,1), imshow(im_ori);
subplot(l,c,2), plot  (im_ori);
subplot(l,c,3), imshow(im_idt);
subplot(l,c,4), plot  (im_idt);
subplot(l,c,5), imshow(im_inv);
subplot(l,c,6), plot  (im_inv);

% Proposer une autre méthode pour trouver le négatif d’une image codée sur 8 bits.
%255-ori

% Utiliser la et montrer que les deux résultats sont identiques.
max(max(imabsdiff(im_ori,im_idt))) % => 0 donc aucune differences

% 2. Transformations logarithmiques appliquées aux niveaux de gris :
% a. Créer afficher (avec plot) une transformation logarithmique donnée par
% s = c log(1+r), où s représente le niveau de gris de sortie, r le niveau de gris de
% l’image originale et c une constante. Pour une image codée sur 8 bits,
% trouver la constante c qui permet d’obtenir un résultat entre 0 et 255.
%l=log([1:256]);
%im_l = c*(l(im_ori+1));
c=255/log(256);
im_log= uint8(c*log(double(1+im_ori)));

% b. Appliquer la transformation en 2.a) à l’image radio.tif
im_ori=imread('radio.tif');

% afficher dans la même figure l’image originale et l’image résultante et commenter le résultat.
im_log = uint8(c*log(double(1+im_ori)));
subplot(l,c,1), imshow(im_ori);
subplot(l,c,2), plot  (im_ori);
subplot(l,c,3), imshow(im_log);
subplot(l,c,4), plot  (im_log);

% Est-ce que vous pensez que l’effet obtenu provient seulement du fait que l’image obtenue est plus claire que l’image originale ?
% Vérifier votre réponse.
% c. Donner l’expression de la transformation exponentielle représentant l’inverse de la transformation logarithmique en 2.a).
% Appliquer la à l’image obtenue en 2.b) et commenter le résultat.
im_exp = uint8(exp(double(1+im_log)/c));
subplot(l,c,1), imshow(im_ori);
subplot(l,c,2), plot  (im_ori);
subplot(l,c,3), imshow(im_log);
subplot(l,c,4), plot  (im_log);
subplot(l,c,5), imshow(im_exp);
subplot(l,c,6), plot  (im_exp);

max(max(imabsdiff(im_ori,im_exp))) % si => 0 donc aucune differences

% 3. Transformations puissance et racine carrée :
% a. Créer et afficher une transformation de la forme s = sqrt(r/c), avec les
% mêmes notations qu’auparavant. Pour une image codée sur 8 bits, trouver
% la constante c qui permet d’obtenir un résultat entre 0 et 255.
% b. Appliquer la transformation en 3.a) à l’image drill.tif, afficher dans la même
% figure l’image originale et l’image résultante et commenter le résultat.
% c. Donner l’expression de la transformation puissance permettant d’annuler
% l’effet obtenu en 3.b).

% 4. Transformations linéaires par morceaux :

% a. Créer et afficher la transformation suivante :
tlm(1:175) = 0:174;
tlm(176:200) = 255;
tlm(201:256) = 200:255;

im_tlm=(tlm(im_ori+1));
subplot(l,c,1), imshow(im_ori);
subplot(l,c,2), plot  (im_ori);
subplot(l,c,3), imshow(im_tlm);
subplot(l,c,4), plot  (im_tlm);

% Quel sera l’effet de cette transformation sur l’image ?
% Appliquer la à l’image micro.tif et afficher l’image originale et l’image résultante.