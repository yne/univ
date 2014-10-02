% L’objectif de ce TP est de passer en revue les méthodes classiques de restoration d’images 
% (debruitage et réduction du flou dans une image). 
% Dans ce TP, nous considérons que le modèle de formation de l’image est le suivante
%(ce modèle est utilisé dans beaucoup d’applications) : 
% i(x,y) = h(x,y) * i(x,y) + b(x,y);
% Avec * le produit de convolution et b(x,y) le bruit.

% Généralement h(x,y) est un noyau qui introduit 
% un flou dans l’image. Dans ce qui suit, nous le considérerons connu.
% L’objectif est donc de retrouver  #$% , à partir de, . 

% 1. Formuler l’équation 1 dans le domaine de Fourier, et conclure sur l’effet que
% , a sur la transformée de Fourier de l’image idéale. 
% 2. Charger l’image coat_of_arms.png et visualiser la.
i=imread('coat_of_arms.jpg');
%imshow(i);

d=20;
h=ones(d)/(d*d);

[n,m]=size(i);
H=fft2(h,n,m);

I=fft2(double(i));

R=H.*I;
r=real(ifft2(R));

%imshow(uint8(r));

% Cette image constituera par la suite 
% a. Générer l’image, , en considérant  , un filtre moyenneur de taille 20x20.
% On considérera ici le cas sans bruit ( , = 0). Utiliser pour cela la fonction 
% imfilter de Matlab : imfilter(i_ideal, h, ’conv’, ’circular’). 

r_if=imfilter(i, h, 'conv', 'circular');
%subplot(1,2,1),imshow(uint8(r));
%subplot(1,2,2),imshow(uint8(r_if));


% b. Visualiser la transformée de Fourier de i_ideal(x,y) de i(x,y), et de, h(x,y)

subplot(1,3,1),imagesc(log(abs(I))),colormap(gray);
subplot(1,3,2),imagesc(log(abs(R))),colormap(gray);
subplot(1,3,3),imagesc(log(abs(H))),colormap(gray);


% Commenter les trois résultats. 

% c. Une méthode naïve de retrouver i_ideal(x,y) serait d’obtenir sa TF par : I(x,y)/H(x,y)
% Mettez cette méthode en œuvre
O = I./H;
o=real(ifft2(O));
imshow(uint8(o));

% commenter le résultat. 
%>> ca ne marche pas

% Expliquer pourquoi cette méthode n’est pas bonne. 


% d. Une méthode pour palier le problème rencontré en 2.c est de faire une division contrainte
% comme suit : 
% avec S un seuil. Mettez cette méthode en œuvre et commentez le résultat. 


% e. Une méthode plus robuste qui permet de récupérer une estimation de l’image 
%"#$% , est le filtre de Wiener. Avec le filtre de Wiener, la transformée de Fourier 
% de"#$% , est obtenue par : 

%, ,            (Eq.2)   
%  avec K une constante qui approxime le rapport bruit sur signal. 
% i. A quoi correspond le filtre de Wiener pour K égal à 0 ? 
% ii. Implémenter votre filtre de Wiener en utilisant l’expression dans (Eq.2). 

% |x| = abs(x)

% iii. Sous Matlab, le filtre de Wiener est implémenté par la fonction deconvwnr. 
wnr2 = deconvwnr(r_if,h, 10e-10);
imshow(wnr2);

% Appliquer le filtre de Wiener à l’image générée en 2.a. Pour le cas sans bruit, 
% des petites valeurs de K (10 e -­‐5) donnent les meilleurs résultats. 
wnr2 = deconvwnr(r_if,h, 10e-5);
imshow(wnr2);

% iv. Comparer votre résulat avec celui de Matlab.

% 3. Mêmes questions qu’en 2, mais en considérant le cas avec bruit.
% Dans ce cas, l’image  obtenue en 2.a sera bruitée avec un bruit additif Gaussien,
% de puissance telle que le RSB soit de 40 dB. Dans ce cas avec bruit, la constante K sera choisie plus grande (10 e -­‐3). 
SNR = 30;
ps_in = sum(sum(in.^2)); % puissance de l’image 
pb_norm = ps_in/(10^(SNR/10)); % puissance du bruit 
noise=randn(size(in)); % bruit Gaussien 
noise_norm = noise/sqrt(sum(sum(noise.^2)))*sqrt(pb_norm); % régler la puissance du bruit 
out = in + noise_norm; % bruiter l’image in
subplot(1,3,1),imshow(in);
subplot(1,3,2),imshow(noise_norm);
subplot(1,3,3),imshow(out);

% 4. Trouver un moyen de trouver le meilleur K. 
