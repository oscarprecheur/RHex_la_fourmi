function [ Corps ] = Create_Corps( Base_corps,x)

%% Parametres du corps
Corps.base = Base_corps;
Corps.Long = 75;
Corps.Larg = 35;

%% Variables
Long_2 = Corps.Long/2;
Larg_2 = Corps.Larg/2;

%% Création des repères
% GAUCHE
Corps.Left(1).rep = trans( Corps.base, Long_2, 'x' );
Corps.Left(1).rep = trans( Corps.Left(1).rep, Larg_2, 'y' );

Corps.Left(2).rep = trans( Corps.base, 0, 'x' );
Corps.Left(2).rep = trans( Corps.Left(2).rep, Larg_2, 'y' );

Corps.Left(3).rep = trans( Corps.base, -Long_2, 'x' );
Corps.Left(3).rep = trans( Corps.Left(3).rep, Larg_2, 'y' );

% DROITE
Corps.Right(1).rep = trans( Corps.base, Long_2, 'x' );
Corps.Right(1).rep = trans( Corps.Right(1).rep, -Larg_2, 'y' );
Corps.Right(1).rep = Reflect( Corps.Right(1).rep, 'x' );

Corps.Right(2).rep = trans( Corps.base, 0, 'x');
Corps.Right(2).rep = trans( Corps.Right(2).rep, -Larg_2, 'y' );
Corps.Right(2).rep = Reflect( Corps.Right(2).rep, 'x' );

Corps.Right(3).rep = trans( Corps.base, -Long_2, 'x' );
Corps.Right(3).rep = trans( Corps.Right(3).rep, -Larg_2, 'y' );
Corps.Right(3).rep = Reflect( Corps.Right(3).rep, 'x' );


%% Points termineaux
p0 = Corps.base(1:3,4);
p1 = Corps.Left(1).rep(1:3,4);
p2 = Corps.Left(2).rep(1:3,4);
p3 = Corps.Left(3).rep(1:3,4);
p4 = Corps.Right(1).rep(1:3,4);
p5 = Corps.Right(2).rep(1:3,4);
p6 = Corps.Right(3).rep(1:3,4);

% Affichage
Corps.prtCorps1 = line([p0(1) p1(1)], [p0(2) p1(2)], [p0(3) p1(3)], 'Color', 'k', 'LineWidth', 2, 'LineStyle', '-');%patte1
Corps.prtCorps2 = line([p0(1) p2(1)], [p0(2) p2(2)], [p0(3) p2(3)], 'Color', 'k', 'LineWidth', 2, 'LineStyle', '-');%patte2
Corps.prtCorps3 = line([p0(1) p3(1)], [p0(2) p3(2)], [p0(3) p3(3)], 'Color', 'k', 'LineWidth', 2, 'LineStyle', '-');%patte3
Corps.prtCorps4 = line([p0(1) p4(1)], [p0(2) p4(2)], [p0(3) p4(3)], 'Color', 'k', 'LineWidth', 2, 'LineStyle', '-');%patte4
Corps.prtCorps5 = line([p0(1) p5(1)], [p0(2) p5(2)], [p0(3) p5(3)], 'Color', 'k', 'LineWidth', 2, 'LineStyle', '-');%patte4
Corps.prtCorps6 = line([p0(1) p6(1)], [p0(2) p6(2)], [p0(3) p6(3)], 'Color', 'k', 'LineWidth', 2, 'LineStyle', '-');%patte5

end

