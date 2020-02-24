function [ T ] = Reflect( mat, a )
% Reflect about 'a' axis
%% A Vérifier  pour y et z !!!!!
%%
switch a
    case 'x'

    T= [1, 0, 0, 0;
        0, -1, 0, 0;
        0, 0, 1, 0;
        0, 0, 0, 1];
   T=mat*T;
   
    case'y'
    T=[-1, 0, 0, 0;
       0, 1, 0, 0;
       0, 0, 1, 0;
       0, 0, 0, 1];
   T=mat*T;
   
   case 'z'

    T=[-1, 0, 0, 0;
       0, -1, 0, 0;
       0, 0, 1, 0;
       0, 0, 0, 1];
   T=mat*T;
   
    case 'o' % origin
        
    T=[-1, 0, 0, 0;
       0, -1, 0, 0;
       0, 0, -1, 0;
       0, 0, 0, 1];
   T=mat*T;        
        

    otherwise
        disp('mauvais axe de translation')








end

