function  T  = Rot( mat, ang, axe )
% Opérateur rotation 
switch axe
    case 'x'
        T=[1, 0, 0, 0;
           0, cos(ang), -sin(ang), 0;
           0, sin(ang), cos(ang), 0;
           0, 0, 0, 1];
       T=mat*T;
       
    case 'y'
        T=[cos(ang), 0, sin(ang), 0;
           0, 1, 0, 0;
           -sin(ang), 0, cos(ang), 0;
           0, 0, 0, 1];
        T=mat*T;
    case 'z'
        T=[cos(ang), -sin(ang), 0, 0;
           sin(ang), cos(ang), 0, 0;
           0, 0, 1, 0;
           0, 0, 0, 1];
        T=mat*T;
    otherwise
        disp('mauvais axe de rotation')
    
end