function [ Patte ] = Create_Patte( basePatte )

%% Paramètres DH
Patte.Seg(1).angle = 0; % liaison au corps
Patte.Seg(2).angle = 0;
Patte.Seg(3).angle = 0;
Patte.Seg(4).angle = 0; % liaison à l'outil

Patte.long.coxa = 13; % distance entre les différentes articulations
Patte.long.femur = 20; % ce modele ne prend pas en compte les deux partie du coxa
Patte.long.tibia = 30;

Patte.base = basePatte;
Patte.Seg(1).DH = [0 0 Patte.Seg(1).angle 0];
Patte.Seg(2).DH = [-pi/2 0 Patte.Seg(2).angle-pi/2 Patte.long.coxa];
Patte.Seg(3).DH = [-pi/2 0 Patte.Seg(3).angle-pi/2 0];
Patte.Seg(4).DH = [0 Patte.long.femur Patte.Seg(4).angle 0];
Patte.outil.DH = [0 Patte.long.tibia 0 0];

%% Création des repères
Patte.Seg(1).rep = jTJ(Patte.base, Patte.Seg(1).DH);
for i=2:4
    Patte.Seg(i).rep = jTJ(Patte.Seg(i-1).rep, Patte.Seg(i).DH);
end
Patte.outil.rep = jTJ(Patte.Seg(4).rep, Patte.outil.DH);

%% Points termineaux
p0 = Patte.base(1:3,4);
p1 = Patte.Seg(1).rep(1:3,4);
p2 = Patte.Seg(2).rep(1:3,4);
p3 = Patte.Seg(3).rep(1:3,4);
p4 = Patte.Seg(4).rep(1:3,4);
p5 = Patte.outil.rep(1:3,4);

% Affichage
Patte.prtPatte1 = line([p0(1) p1(1)], [p0(2) p1(2)], [p0(3) p1(3)], 'Color', 'b', 'LineWidth', 2, 'LineStyle', '-'); %% Ne doit pas être affiché puisque les deux premiers repères sont confondus
Patte.prtPatte2 = line([p1(1) p2(1)], [p1(2) p2(2)], [p1(3) p2(3)], 'Color', 'r', 'LineWidth', 2, 'LineStyle', '-');
Patte.prtPatte3 = line([p2(1) p3(1)], [p2(2) p3(2)], [p2(3) p3(3)], 'Color', 'b', 'LineWidth', 2, 'LineStyle', '-'); %% Ne doit pas être affiché puisque les repères sont confondus
Patte.prtPatte4 = line([p3(1) p4(1)], [p3(2) p4(2)], [p3(3) p4(3)], 'Color', 'c', 'LineWidth', 2, 'LineStyle', '-');
Patte.prtPatte5 = line([p4(1) p5(1)], [p4(2) p5(2)], [p4(3) p5(3)], 'Color', 'm', 'LineWidth', 2, 'LineStyle', '-');

end
