function Corps_dessine( Corps,x )
% Dessin de la patte

p0 = Corps.base(1:3,4);
p1 = Corps.Left(1).rep(1:3,4);
p2 = Corps.Left(2).rep(1:3,4);
p3 = Corps.Left(3).rep(1:3,4);
p4 = Corps.Right(1).rep(1:3,4);
p5 = Corps.Right(2).rep(1:3,4);
p6 = Corps.Right(3).rep(1:3,4);

set(Corps.prtCorps1, 'xdata', [p0(1)+x, p1(1)+x], 'ydata', [p0(2) p1(2)], 'zdata', [p0(3) p1(3)]);
set(Corps.prtCorps2, 'xdata', [p1(1)+x, p2(1)+x], 'ydata', [p1(2) p2(2)], 'zdata', [p1(3) p2(3)]);
set(Corps.prtCorps3, 'xdata', [p2(1)+x, p3(1)+x], 'ydata', [p2(2) p3(2)], 'zdata', [p2(3) p3(3)]);
set(Corps.prtCorps4, 'xdata', [p3(1)+x, p4(1)+x], 'ydata', [p3(2) p4(2)], 'zdata', [p3(3) p4(3)]);
set(Corps.prtCorps5, 'xdata', [p4(1)+x, p5(1)+x], 'ydata', [p4(2) p5(2)], 'zdata', [p4(3) p5(3)]);
set(Corps.prtCorps6, 'xdata', [p5(1)+x, p6(1)+x], 'ydata', [p5(2) p6(2)], 'zdata', [p5(3) p6(3)]);

end
