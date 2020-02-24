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
title('Test Affichage')
xlabel('x')
ylabel('y')
zlabel('z')

%axis equal

hold on
grid on

view(-210,30)

%légende
plot(0.1, 'r')
plot(0.1, 'g')
plot(0.1, 'b')
legend('x', 'y', 'z');

%% Initialisation du repère
Repere_Robot = eye(4);



%% Initialisation Du Robot
[ Patte_L, Patte_R, Corps ] = InitRobot( Repere_Robot );


% %% Test
% hold on
% WorkSpace( Patte_L(1) ); % trace l'espace articulaire de la patte

figure (2)
for m = 1:5
    for i = 0:0.2:pi
        %% Initialisation des angles
        
        angle_D = [ 0 0 -pi/4 -pi/4 ;
            -i/4 0 -pi/4 -pi/4 ;
            0 0 -pi/4 -pi/4 ];
        
        angle_G = [ -i/4 0 -pi/4 -pi/4 ;
            0 0 -pi/4 -pi/4 ;
            -i/4 0 -pi/4 -pi/4 ];
  
        
        hold on
        
        %% Motion et dessin des pattes
        [ Patte_L, Patte_R ] = MGD( Patte_L, Patte_R, angle_D, angle_G );
        
    end
    
    for i = 0:0.2:pi
        %% Initialisation des angles
        
        angle_G(2,1:4) = [ -i/4 0 -pi/4 -pi/4 ];
        
        angle_D(1,1:4) = [ -i/4 0 -pi/4 -pi/4 ];
        
        angle_D(3,1:4) = [ -i/4 0 -pi/4 -pi/4 ];
        
        
        hold on
        
        %% Motion et dessin des pattes
        [ Patte_L, Patte_R ] = MGD( Patte_L, Patte_R, angle_D, angle_G );
        trans( Corps.Left(1).rep, -100, 'x' )
        trans( Corps.Right(1).rep, -100, 'x' )
        %% Corps.Left(1).rep = trans( 75, 500, 'x' );
        
    end
end

%% Tracé des repères
Reperes( Corps, Patte_L, Patte_R );













