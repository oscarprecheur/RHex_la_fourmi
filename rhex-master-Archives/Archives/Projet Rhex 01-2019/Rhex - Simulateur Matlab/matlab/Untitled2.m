% % Distance du robot
% l1 = Patte.long.coxa;
% l2 = Patte.long.femur;
% l3 = Patte.long.tibia;
% 
% X = [30 10 10];
% 
% % Calcul de l'angle
% Theta1 = atan2(X(2), X(1));
% Xvar = sqrt((X(1)-l1*cos(Theta1))^2 + (X(2)-l1*sin(Theta1))^2);
% Yvar = X(3); 
% Theta3haut = acos((Xvar*Xvar+Yvar*Yvar-l2*l2-l3*l3)/(2*l2*l3));
% Theta3bas = -acos((Xvar*Xvar+Yvar*Yvar-l2*l2-l3*l3)/(2*l2*l3));
% Theta2haut = atan2((Yvar*(l2+l3*cos(Theta3haut))-Xvar*l3*sin(Theta3haut)),(Xvar*(l2+l3*cos(Theta3haut))+Yvar*l3*sin(Theta3haut)));
% Theta2bas = atan2((Yvar*(l2+l3*cos(Theta3bas))-Xvar*l3*sin(Theta3bas)),(Xvar*(l2+l3*cos(Theta3bas))+Yvar*l3*sin(Theta3bas)));
% 
% angle_D(1) = Theta1;
% angle_D(2) = 0;
% angle_D(3) = Theta2haut;
% angle_D(4) = Theta3haut;
% 
% x = l3*cos(angle_D(1))*cos(angle_D(3)+angle_D(4)) + cos(angle_D(1)) * (l2*cos(angle_D(3) + l1)) ;
% y = l3*sin(angle_D(1))*cos(angle_D(3)+angle_D(4)) + sin(angle_D(1)) * (l2*cos(angle_D(3) + l1)) ;
% z = +l3 * sin(angle_D(3)+angle_D(4)) + l2*sin(angle_D(3));