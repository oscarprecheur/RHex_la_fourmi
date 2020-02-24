
function [ Patte_L, Patte_R ] = MGI( Patte_L, Patte_R, disposition_D )

Patte_L = Patte_L(1);

Patte.Seg(1).DH(3) = theta(1);
Patte.Seg(2).DH(3) = theta(2)-pi/2;
Patte.Seg(3).DH(3) = theta(3)-pi/2;
Patte.Seg(4).DH(3) = theta(4);

for i=1:4
    Patte.Seg(i).theta = theta(i);
end

Patte.Seg(1).rep = jTJ(Patte.base, Patte.Seg(1).DH); % On part de la base



end

