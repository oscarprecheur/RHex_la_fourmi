%% TEST AFFICHAGE DU ROBOT
clear all
clc
clf
%% Création de l'espace
figure(1)
xlabel('x')
ylabel('y')
zlabel('z')

axis([-50 50 -50 50 -50 10]);

hold on
grid on

view(-210,30)

%% Initialisation du repère
basePatte = eye(4);

%% Initialisation Du Robot
[ Patte ] = Create_Patte( basePatte );
% trace_rep(Patte);

% decalage vertical de la patte avant et apres l'ellipse
decalage_vertical = 5;

% Point depart et arriver
Pa = [-20 20 -40];
Pd = [20 20 -40];

[Theta] = deplacement_pas (Patte, Pd, Pa, decalage_vertical);
