%% Simulateur Hexapode
clear all
close all
clc

%% TEST AFFICHAGE DU ROBOT
clear all
clc
%close all
clf
%% Création de l'espace
figure(2)
title('MODELISATION RHEX')
xlabel('x')
ylabel('y')
zlabel('z')

%axis equal

hold on
grid on
grid off
axis equal

view(-210,30)
legend('x', 'y', 'z');

%% Initialisation du repère
Repere_Robot = eye(4);

%légende
plot(0.1, 'r')
plot(0.1, 'g')
plot(0.1, 'b')



%% Initialisation Du Robot
[ Patte_L, Patte_R, Corps ] = InitRobot( Repere_Robot);


% %% Test
% hold on
% WorkSpace( Patte_L(1) ); % trace l'espace articulaire de la patte
 
figure (2)
trace_rep_corps( Corps,3); 
demarche(Patte_L,Patte_R);
%test_recule(Patte_L,Patte_R);
%tournerD(Patte_L,Patte_R);
%tournerG(Patte_L,Patte_R);
%% Tracé des repères
%Reperes( Corps, Patte_L, Patte_R );













