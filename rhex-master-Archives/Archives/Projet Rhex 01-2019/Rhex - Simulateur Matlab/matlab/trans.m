function [ T ] = trans( mat, r, a )
%mat correspond à la matrice sur laquelle on applique la translation
%a=axe

switch a
    case 'x'

    T= [1, 0, 0, r;
        0, 1, 0, 0;
        0, 0, 1, 0;
        0, 0, 0, 1];
   T=mat*T;
   
    case'y'
    T=[1, 0, 0, 0;
        0, 1, 0, r;
        0, 0, 1, 0;
        0, 0, 0, 1];
   T=mat*T;
   
   case 'z'

    T=[1, 0, 0, 0;
        0, 1, 0, 0;
        0, 0, 1, r;
        0, 0, 0, 1];
   T=mat*T;
   
    otherwise
        disp('mauvais axe de translation')
   
end

