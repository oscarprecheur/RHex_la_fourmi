%% TEST AFFICHAGE DE LA PATTE
clear all
%close all
clc
clf
%% Création de l'espace
figure(1)
title('Test Affichage')
xlabel('x')
ylabel('y')
zlabel('z')

axis equal

hold on
grid on

view(-210,30); % angle de vue

% Legende, a modifier independament 
plot(0.1, 'r')
plot(0.1, 'g')
plot(0.1, 'b')
legend('x', 'y', 'z');

%% Initialisation du repère
repere_0 = eye(4);
theta = zeros(1,6);

%% Initialisation et dessin de la patte
Patte = Create_Patte(repere_0); % et dessine la patte dans son etat initial

%% Modification de la patte
angle_D = [ 0 0 -pi/4 -pi/4 ]; % angles desires 

Patte = bougePatte(Patte, angle_D); % Change les valeurs angulaires
Patte_dessine(Patte); % Dessine la patte "dans son etat actuel", ici l'etat final
trace_rep(Patte); % Trace les reperes

 
 
 
 
 
 