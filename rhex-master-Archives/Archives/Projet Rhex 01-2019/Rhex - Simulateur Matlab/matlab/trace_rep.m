function trace_rep( Patte )
% Trace les vecteurs des repères

%% Rédiction de la norme des vecteurs
norme = 3;

% De la base
for k=1:3
    Patte.base(:,k)= norme*Patte.base(:,k);
end

% De la patte
for i=1:4
    for j=1:3
         Patte.Seg(i).rep(:,j) = norme*Patte.Seg(i).rep(:,j);
    end
end

% De l'outil
for l=1:3
    Patte.outil.rep(:,l)= norme*Patte.outil.rep(:,l);
end

%% Tracé de la base
quiver3(Patte.base(1,4),Patte.base(2,4),Patte.base(3,4), Patte.base(1,1),Patte.base(2,1),Patte.base(3,1), 'color', [1 0 0])
quiver3(Patte.base(1,4),Patte.base(2,4),Patte.base(3,4), Patte.base(1,2),Patte.base(2,2),Patte.base(3,2), 'color', [0 1 0])
quiver3(Patte.base(1,4),Patte.base(2,4),Patte.base(3,4), Patte.base(1,3),Patte.base(2,3),Patte.base(3,3), 'color', [0 0 1])

%% Tracé de la base de la patte
for i=1:4
    
    quiver3(Patte.Seg(i).rep(1,4),Patte.Seg(i).rep(2,4),Patte.Seg(i).rep(3,4), Patte.Seg(i).rep(1,1),Patte.Seg(i).rep(2,1),Patte.Seg(i).rep(3,1), 'color', [1 0 0])
    quiver3(Patte.Seg(i).rep(1,4),Patte.Seg(i).rep(2,4),Patte.Seg(i).rep(3,4), Patte.Seg(i).rep(1,2),Patte.Seg(i).rep(2,2),Patte.Seg(i).rep(3,2), 'color', [0 1 0])
    quiver3(Patte.Seg(i).rep(1,4),Patte.Seg(i).rep(2,4),Patte.Seg(i).rep(3,4), Patte.Seg(i).rep(1,3),Patte.Seg(i).rep(2,3),Patte.Seg(i).rep(3,3), 'color', [0 0 1])
    
end

%% Tracé du repère de l'outil
 quiver3(Patte.outil.rep(1,4),Patte.outil.rep(2,4),Patte.outil.rep(3,4), Patte.outil.rep(1,1),Patte.outil.rep(2,1),Patte.outil.rep(3,1), 'color', [1 0 0])
 quiver3(Patte.outil.rep(1,4),Patte.outil.rep(2,4),Patte.outil.rep(3,4), Patte.outil.rep(1,2),Patte.outil.rep(2,2),Patte.outil.rep(3,2), 'color', [0 1 0])
 quiver3(Patte.outil.rep(1,4),Patte.outil.rep(2,4),Patte.outil.rep(3,4), Patte.outil.rep(1,3),Patte.outil.rep(2,3),Patte.outil.rep(3,3), 'color', [0 0 1])

end
