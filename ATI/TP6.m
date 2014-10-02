 %%1
cam=imread('Cameraman.bmp');
L=linspace(1,256,256);
%%a
for x=  1: 49,T(x)=256-x* 2;end;
for x= 50:150,T(x)=181-x*.5;end;
for x=151:256,T(x)=380-x*(155/104);end;
%afficher la transformé T
plot([T' L']);%comparé a la courbe lineaire normale

%b appliquer a l'image
out=cam;%duplique l'image dans out
for i=1:numel(cam),cam(i)=T(cam(i));end;%modifie out

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

%valeur du module pour la fréquence nulle (0,0)
centre(1,1)/(size(cam,1)*size(cam,2))
m=mean2(cam);
%m=118.7245

%5.b Construisez ce filtre avec Matlab
filtre=zeros(25,25);

imCAM=fftshift(CAM);
w=25;
imCAM(128-w/2:128+w/2,128-w/2:128+w/2)=0;
%imshow(log(abs(imCAM)),[]);
%affichage de l'image filtrée
imshow(ifft2(fftshift(imCAM)), []);
% il ne reste que les contours
% encore plus de filtre
imCAM=fftshift(CAM);
imCAM(127:129,1:256)=0;
imCAM(1:256,127:129)=0;
imshow(log(abs(imCAM)),[]);
imshow(ifft2(fftshift(imCAM)), []);
%d ?

%6
w=32;
imCAM=fftshift(CAM);
imCAM(1:w,1:256)=0;
imCAM(1:256,1:w)=0;
imCAM(255-w:255,1:256)=0;
imCAM(1:256,255-w:255)=0;
imshow(log(abs(imCAM)),[]);
imshow(ifft2(fftshift(imCAM)), []);

%7
f_conv=[0 0 0;0 1 0;0 0 0]-(fspecial('laplacian')).*(ones(3,3)/(3*3));
imshow(uint8(conv2(double(cam),f_conv)));
