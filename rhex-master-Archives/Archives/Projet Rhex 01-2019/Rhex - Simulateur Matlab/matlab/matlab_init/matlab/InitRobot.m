function [ Patte_L, Patte_R, Corps ] = InitRobot( Repere_Robot )

%% Initialisation et dessin du corps
Corps = Create_Corps(Repere_Robot);

%% Initialisation et dessin des pattes

% Gauche
for i = 1:3
    Patte_L(i) = Create_Patte(Corps.Left(i).rep);
end

% Droite
for i = 1:3
    Patte_R(i) = Create_Patte(Corps.Right(i).rep);
end

end

