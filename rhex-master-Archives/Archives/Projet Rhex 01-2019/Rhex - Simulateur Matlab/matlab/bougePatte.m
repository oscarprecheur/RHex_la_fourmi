function nvRob = bougePatte( Patte, theta )
% Permet la construction des repères et leurs modifications

Patte.Seg(1).DH(3) = theta(1);
Patte.Seg(2).DH(3) = theta(2)-pi/2;
Patte.Seg(3).DH(3) = theta(3)-pi/2;
Patte.Seg(4).DH(3) = theta(4);

for i=1:4
    Patte.Seg(i).theta = theta(i);
end

Patte.Seg(1).rep = jTJ(Patte.base, Patte.Seg(1).DH); % On part de la base
for i=2:4
    Patte.Seg(i).rep = jTJ(Patte.Seg(i-1).rep, Patte.Seg(i).DH); % en remontant articulation par articulation
end

Patte.outil.rep = jTJ(Patte.Seg(4).rep, Patte.outil.DH); % jusqu'à l'outil terminal
nvRob=Patte;

end
