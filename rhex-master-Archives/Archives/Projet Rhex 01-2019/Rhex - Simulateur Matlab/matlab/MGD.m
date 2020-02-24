function [ Patte_L, Patte_R ] = MGD( Patte_L, Patte_R, angle_D, angle_G )
%% Motion et dessin des pattes

% Gauche
for i = 1:3
    Patte_L(i) = bougePatte(Patte_L(i), angle_G(i,:)); % fait bouger la patte dans la position voulue
    Patte_dessine(Patte_L(i));
    axis([-100,100,-100,100,-60,10])
   
    drawnow
end

% Droite
for i = 1:3
    Patte_R(i) = bougePatte(Patte_R(i), angle_D(i,:));
    Patte_dessine(Patte_R(i));
    drawnow
end

end

