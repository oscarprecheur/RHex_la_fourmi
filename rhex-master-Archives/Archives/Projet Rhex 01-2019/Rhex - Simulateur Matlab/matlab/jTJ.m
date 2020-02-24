function  T  = jTJ( repj, DH )
% Matrice de passage
% DH: alpha, d, theta, r
% applique  rot trans rot trans sur la matrice initiale

T =   Rot(repj, DH(1), 'x');
T = trans(T, DH(2), 'x');
T =   Rot(T, DH(3), 'z');
T = trans(T, DH(4), 'z');


end

