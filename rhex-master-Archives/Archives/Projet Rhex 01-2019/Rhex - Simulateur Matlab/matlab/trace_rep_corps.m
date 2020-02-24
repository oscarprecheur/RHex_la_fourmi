function trace_rep_corps( Corps,x )
%trace les vecteurs des repères

%% Réduction de la norme des vecteurs
norme = 3;

% De la base
for k=1:3
    Corps.base(:,k)= norme*Corps.base(:,k)+x;
end

% De la base des pattes gauches
for i=1:3
    for j=1:3
        Corps.Left(i).rep(:,j) = norme*Corps.Left(i).rep(:,j)+x;
    end
end

% De la base des pattes droites
for i=1:3
    for j=1:3
       Corps.Right(i).rep(:,j) = norme*Corps.Right(i).rep(:,j)+x;
    end
end


%% Tracé de la base
quiver3(Corps.base(1,4),Corps.base(2,4),Corps.base(3,4), Corps.base(1,1),Corps.base(2,1),Corps.base(3,1), 'color', [1 0 0])
quiver3(Corps.base(1,4),Corps.base(2,4),Corps.base(3,4), Corps.base(1,2),Corps.base(2,2),Corps.base(3,2), 'color', [0 1 0])
quiver3(Corps.base(1,4),Corps.base(2,4),Corps.base(3,4), Corps.base(1,3),Corps.base(2,3),Corps.base(3,3), 'color', [0 0 1])

%% Tracé de la base sur les pattes
% Gauche
for i=1:3 
    quiver3(Corps.Left(i).rep(1,4),Corps.Left(i).rep(2,4),Corps.Left(i).rep(3,4), Corps.Left(i).rep(1,1),Corps.Left(i).rep(2,1),Corps.Left(i).rep(3,1), 'color', [1 0 0])
    quiver3(Corps.Left(i).rep(1,4),Corps.Left(i).rep(2,4),Corps.Left(i).rep(3,4), Corps.Left(i).rep(1,2),Corps.Left(i).rep(2,2),Corps.Left(i).rep(3,2), 'color', [0 1 0])
    quiver3(Corps.Left(i).rep(1,4),Corps.Left(i).rep(2,4),Corps.Left(i).rep(3,4), Corps.Left(i).rep(1,3),Corps.Left(i).rep(2,3),Corps.Left(i).rep(3,3), 'color', [0 0 1])    
end

% Droite
for i=1:3 
    quiver3(Corps.Right(i).rep(1,4),Corps.Right(i).rep(2,4),Corps.Right(i).rep(3,4), Corps.Right(i).rep(1,1),Corps.Right(i).rep(2,1),Corps.Right(i).rep(3,1), 'color', [1 0 0])
    quiver3(Corps.Right(i).rep(1,4),Corps.Right(i).rep(2,4),Corps.Right(i).rep(3,4), Corps.Right(i).rep(1,2),Corps.Right(i).rep(2,2),Corps.Right(i).rep(3,2), 'color', [0 1 0])
    quiver3(Corps.Right(i).rep(1,4),Corps.Right(i).rep(2,4),Corps.Right(i).rep(3,4), Corps.Right(i).rep(1,3),Corps.Right(i).rep(2,3),Corps.Right(i).rep(3,3), 'color', [0 0 1])    
end

end




















