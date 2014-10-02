% 1. Rehaussement.
%%%%%%%%%%%%%%%%%%%%%

% a. Charger l’image moon.tif et afficher la.
moon=imread('moon.tif');
imshow(moon);
% b. Créer le masque correspondant au Laplacien
lp_mask=fspecial('laplacian');
% filtrer l’image.
moon_filtre=imfilter(moon, lp_mask);
% Afficher le résultat.
imshow(moon_filtre);

% c. A partir de l’image originale et l’image obtenue en b),
% comment peut-on obtenir une image rehaussée ?
	% en faisant la somme des 2 images
% Appliquer cette méthode
moon_reh = moon+moon_filtre;
% afficher le résultat.
imshow(moon_reh);
% d. Est-ce qu’on aurait pu obtenir le résultat en 1.c) en une seule opération ?
	% oui
% Si oui,mettez la en œuvre et vérifier qu’on obtient le même résultat.
imshow(moon+imfilter(moon, fspecial('laplacian')));

% e. On se propose de rehausser l’image moon.tif en utilisant les étapes suivantes :
% i. Rendez l’image moon.tif plus floue en utilisant un filtre moyenneur de taille 5×5.
blur_mask = fspecial('average',5);
moon_floue=imfilter(moon, blur_mask);
imshow(moon_floue);
% ii. Calculez l’image différence entre l’image originale et l’image floue.
moon_diff = moon - moon_floue;
imshow(moon_diff);
% iii. L’image finale est obtenue en additionnant l’image précédente et l’image originale.
imshow(moon_diff+moon);
% Commenter le résultat.
	% on retrouve moon (moon - moon_floue + moon = moon)

% iv. Est-ce que les trois opérations précédentes peuvent être faites en une seule ?
% Quelle est la différence par rapport à 1.c) ?


% Filtrage linéaire dans le domaine fréquentiel
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Rappelez les définitions des transformées de Fourier discrètes 1D et 2D.
% 1. Retrouver les résultats de TD pour un vecteur x=[1 1 1] :
% a. Sa transformée de Fourier 1D calculée sur 3 échantillons. Tracer son module (plot) en
% utilisant la fonction fftshift et en réglant correctement l’axe des abscisses
% (fréquences normalisées allant de -1/2 à 1/2). Pour créer l’axe des abscisses, vous
% pouvez utiliser la fonction linspace de Matlab.
% b. Même question que 1.a) mais en calculant la transformée de Fourier sur 6
% échantillons. Vérifier que le résultat est le même si vous complétez vous-même par
% des 0 ou vous laissez Matlab le faire.
% 2. Mêmes questions que 1 mais pour une image x = [1 1 1 ;1 1 1 ;1 1 1].
% 3. Chargez l’image cameraman.tif, calculez sa transformée de Fourier 2D et affichez son
% module, en réglant les deux axes des fréquences pour qu’elles correspondent à des
% fréquences normalisées (de -0,5 à 0,5). Pour améliorer le contraste, affichez le module en
% utilisant une transformation logarithmique. Comme l’image du module de la transformée de
% Fourier n’est pas forcément constituée de valeurs entières, utilisez la fonction Matlab
% imagesc à la place de imshow. Commenter le résultat.
% 4. On se propose de filtrer l’image précédente avec un filtre moyenneur de taille 3×3.
% a. Calculer et afficher le résultat du filtrage en effectuant la convolution dans le
% domaine spatial (fonction conv2 de Matlab).
% b. Retrouver le même résultat en effectuant la convolution dans le domaine
% fréquentiel. Dans les deux cas (4.a) et 4.b)), effectuez une convolution complète.
% 5. On se propose de réaliser un filtrage passe-bas, avec un filtre défini par un masque
% rectangulaire dans le domaine fréquentiel (1 pour les basses fréquences et 0 pour les hautes
% fréquences).
% a. Créez le masque et affichez-le.
% b. Filtrez l’image précédente avec ce masque et affichez le résultat. Commentez le
% résultat. D’où viennent les oscillations dans l’image ? Quelle est le masque spatial
% correspondant à votre filtre ?
% c. Comment doit-on changer le masque fréquentiel (le filtre) pour atténuer l’effet de
% ces oscillations ? Appliquez le nouveau masque et commentez le résultat.
% d. Modifiez les masques crées précédemment pour filtrer davantage l’image.
% 6. Même questions qu’en 5 mais pour un filtre passe-haut.