function Patte_dessine( Patte )
% Dessin de la patte


p0 = Patte.base(1:3,4);
p1 = Patte.Seg(1).rep(1:3,4);
p2 = Patte.Seg(2).rep(1:3,4);
p3 = Patte.Seg(3).rep(1:3,4);
p4 = Patte.Seg(4).rep(1:3,4);
p5 = Patte.outil.rep(1:3,4);

set(Patte.prtPatte1, 'xdata', [p0(1), p1(1)], 'ydata', [p0(2) p1(2)], 'zdata', [p0(3) p1(3)]);
set(Patte.prtPatte2, 'xdata', [p1(1), p2(1)], 'ydata', [p1(2) p2(2)], 'zdata', [p1(3) p2(3)]);
set(Patte.prtPatte3, 'xdata', [p2(1), p3(1)], 'ydata', [p2(2) p3(2)], 'zdata', [p2(3) p3(3)]);
set(Patte.prtPatte4, 'xdata', [p3(1), p4(1)], 'ydata', [p3(2) p4(2)], 'zdata', [p3(3) p4(3)]);
set(Patte.prtPatte5, 'xdata', [p4(1), p5(1)], 'ydata', [p4(2) p5(2)], 'zdata', [p4(3) p5(3)]);

end
