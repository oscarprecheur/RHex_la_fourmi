function [Theta] = deplacement_pas (Patte, Pd, Pa, decalage_vertical)

% Distance du robot
l1 = Patte.long.coxa;
l2 = Patte.long.femur;
l3 = Patte.long.tibia;

H = Pd;

T=[cos(-pi/2), -sin(-pi/2), 0, 0;
    sin(-pi/2), cos(-pi/2), 0, 0;
    0,             0,       1, 0;
    0,             0,       0, 1];

j1 = size(H(3):0.05:H(3) + decalage_vertical);
j2 = size(0:0.005:pi);
j3 = size(H(3):-0.05:H(3) - decalage_vertical);

Total = j1(2) + j2(2) + j3(2);

Theta = zeros(3, Total);
k = 1;
for j= H(3):0.05:H(3) + decalage_vertical
    
    H(3) = j;
    
    X = T * [H 1]';
    
    
    % Calcul de l'angle
    Theta1 = atan2(X(2), X(1));
    Xvar = sqrt((X(1)-l1*cos(Theta1))^2 + (X(2)-l1*sin(Theta1))^2);
    Yvar = X(3);
    Theta3haut = acos((Xvar*Xvar+Yvar*Yvar-l2*l2-l3*l3)/(2*l2*l3));
    Theta3bas = -acos((Xvar*Xvar+Yvar*Yvar-l2*l2-l3*l3)/(2*l2*l3));
    Theta2haut = atan2((Yvar*(l2+l3*cos(Theta3haut))-Xvar*l3*sin(Theta3haut)),(Xvar*(l2+l3*cos(Theta3haut))+Yvar*l3*sin(Theta3haut)));
    Theta2bas = atan2((Yvar*(l2+l3*cos(Theta3bas))-Xvar*l3*sin(Theta3bas)),(Xvar*(l2+l3*cos(Theta3bas))+Yvar*l3*sin(Theta3bas)));
    
    angle_D(1) = Theta1;
    angle_D(2) = 0;
    angle_D(3) = Theta2bas;
    angle_D(4) = Theta3bas;
    
    Theta(1:4, k) = angle_D(1:4);
    k = k + 1;
    
    %% Tracé de la patte bougée
    Patte = bougePatte(Patte, angle_D);
    Patte_dessine(Patte); % Dessine la patte "dans son etat actuel", ici l'etat final
    %%trace_rep(Patte); % Trace les reperes
    plot3(H(1),H(2),H(3), 'o');
    
    
    drawnow

    
    
end

Pa(3) = H(3);
R = (sqrt((H(1)-Pa(1))^2+ (H(3)-Pa(3))^2))/2; 
b = (Pa(3) + H(3)) / 2;
a = (H(1) + Pa(1)) / 2 ;

for j= 0:0.005:pi
    
    H(1) = a + R*cos(j);
    H(3) = b + R/2*sin(j);
    
    X = T * [H 1]';
    
    
    % Calcul de l'angle
    Theta1 = atan2(X(2), X(1));
    Xvar = sqrt((X(1)-l1*cos(Theta1))^2 + (X(2)-l1*sin(Theta1))^2);
    Yvar = X(3);
    Theta3haut = acos((Xvar*Xvar+Yvar*Yvar-l2*l2-l3*l3)/(2*l2*l3));
    Theta3bas = -acos((Xvar*Xvar+Yvar*Yvar-l2*l2-l3*l3)/(2*l2*l3));
    Theta2haut = atan2((Yvar*(l2+l3*cos(Theta3haut))-Xvar*l3*sin(Theta3haut)),(Xvar*(l2+l3*cos(Theta3haut))+Yvar*l3*sin(Theta3haut)));
    Theta2bas = atan2((Yvar*(l2+l3*cos(Theta3bas))-Xvar*l3*sin(Theta3bas)),(Xvar*(l2+l3*cos(Theta3bas))+Yvar*l3*sin(Theta3bas)));
    
    angle_D(1) = Theta1;
    angle_D(2) = 0;
    angle_D(3) = Theta2bas;
    angle_D(4) = Theta3bas;
    
    Theta(1:4, k) = angle_D(1:4);
    k = k + 1;
    
    %% Tracé de la patte bougée
    Patte = bougePatte(Patte, angle_D);
    Patte_dessine(Patte); % Dessine la patte "dans son etat actuel", ici l'etat final
    %%trace_rep(Patte); % Trace les reperes
    plot3(H(1),H(2),H(3), 'o');
    
    
    drawnow

    
    
end

for j= H(3):-0.05:  H(3) - decalage_vertical
    
    H(3) = j;
    
    X = T * [H 1]';
    
    
    % Calcul de l'angle
    Theta1 = atan2(X(2), X(1));
    Xvar = sqrt((X(1)-l1*cos(Theta1))^2 + (X(2)-l1*sin(Theta1))^2);
    Yvar = X(3);
    Theta3haut = acos((Xvar*Xvar+Yvar*Yvar-l2*l2-l3*l3)/(2*l2*l3));
    Theta3bas = -acos((Xvar*Xvar+Yvar*Yvar-l2*l2-l3*l3)/(2*l2*l3));
    Theta2haut = atan2((Yvar*(l2+l3*cos(Theta3haut))-Xvar*l3*sin(Theta3haut)),(Xvar*(l2+l3*cos(Theta3haut))+Yvar*l3*sin(Theta3haut)));
    Theta2bas = atan2((Yvar*(l2+l3*cos(Theta3bas))-Xvar*l3*sin(Theta3bas)),(Xvar*(l2+l3*cos(Theta3bas))+Yvar*l3*sin(Theta3bas)));
    
    angle_D(1) = Theta1;
    angle_D(2) = 0;
    angle_D(3) = Theta2bas;
    angle_D(4) = Theta3bas;
    
    Theta(1:4, k) = angle_D(1:4);
    k = k + 1;
    
    %% Tracé de la patte bougée
    Patte = bougePatte(Patte, angle_D);
    Patte_dessine(Patte); % Dessine la patte "dans son etat actuel", ici l'etat final
    %%trace_rep(Patte); % Trace les reperes
    plot3(H(1),H(2),H(3), 'o');
    
    
    drawnow
end

figure(2) 
plot(Theta(1, :), 'r');

plot(Theta(2, :), 'b');

plot(Theta(3, :), 'g');

plot(Theta(4, :), 'm');
legend(['Theta 1', 'Theta 2', 'Theta 3', 'Theta 4']);
title('Theta');
