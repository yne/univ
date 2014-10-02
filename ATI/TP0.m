 %%1
cam=imread('Cameraman.bmp');
[W H]=imsize(cam);
L=linspace(1,256,256);
%%a
for x=  1: 49,T(x)=256-x* 2;end;
for x= 50:150,T(x)=181-x*.5;end;
for x=151:256,T(x)=380-x*(155/104);end;
%afficher la transformé T
plot([T' L']);%comparé a la courbe lineaire normale

%b appliquer a l'image
out=cam;%copie les attributs (W:H) et les valeurs (remplacées apres)
for i=1:numel(cam),out(i)=T(cam(i));end;%modifie out

subplot(1,2,1),imshow(cam);
subplot(1,2,2),imshow(out);

%c la T n'est pas reversible car pour un y donné plusieurs x sont possible
% exemple : dans l'interval 155 - 106

%%% CORRECTION de T => S %%%

for x=  1: 49,S(x)=256-x* 2;end;
for x= 50:150,S(x)=181-x*.5;end;
for x=151:256,S(x)=260-x*(107/104);end;

%afficher la transformé S
plot([L' T' S']);

%2
%non linéaire , ex: noise
img_noise = imnoise(cam,'gaussian');
imshow(img_noise);

%3
coin=imread('coins.png');
imhist(coin);
% on remarque que les valeurs sont groupé dans 2 intervales [50;75] & [150;200]
% pour binariser je vais choisir une valeurs entre ces 2 intervales (donc : 100)
bin = coin(:,:,1);
bin(bin> 100)=255;
bin(bin<=100)=0;

subplot(1,2,1),imshow(coin);
subplot(1,2,2),imshow(bin);

%les pieces sont maintenant clairement distinguées du fond
% car leurs valeurs etait comprises entre [150;200]
% alors que le fond etait dans l'intervale [50;75]


coin_eq = histeq(coin);

subplot(1,2,1),imshow(coin_eq);
subplot(1,2,2),imhist(coin_eq);
%il est desormais impossible de distinguer les zone "piece" des zones "fond"

%4
CAM=fft2(cam); 
% module de sa transformée de Fourier 2D en log
imshow(log(abs(fftshift(CAM))), []);
% Commentez le contenu fréquentiel de l’image.
% les valeurs se concentre sur les axe y=0 et x=0 ?
%>> les frequences continues

%valeur du module pour la fréquence nulle (0,0)
CAM(1,1)==sum(sum(cam))%7780728
%sous forme de moyenne
CAM(1,1)/(size(cam,1)*size(cam,2))%mean2(cam)

%5.b Construisez ce filtre avec Matlab
filtre=zeros(W,H);
s=128;%taille du filtre
filtre((W-s)/2:(W+s)/2,(H-s)/2:(H+s)/2)=1;

CAM_filtre=fftshift(CAM).*(0+filtre);

subplot(1,2,1),imshow(log(abs(CAM_filtre)),[]);
%affichage de l'image filtrée
subplot(1,2,2),imshow(ifft2(fftshift(CAM_filtre)), []);

%d ?

%6
CAM_filtre=fftshift(CAM).*(1-filtre);
subplot(1,2,1),imshow(log(abs(CAM_filtre)),[]);
%affichage de l'image filtrée
subplot(1,2,2),imshow(ifft2(fftshift(CAM_filtre)), []);


%7
f_conv=[0 0 0;0 1 0;0 0 0]-(fspecial('laplacian')).*(ones(3,3)/(3*3));
imshow(uint8(conv2(double(cam),f_conv)));
