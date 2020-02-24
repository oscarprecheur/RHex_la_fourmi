function WorkSpace( Patte )

figure(1)
title('surface de travail MGD');
xlabel('x')
ylabel('y')
zlabel('z')

axis equal
grid on 

angle = [0;0;pi;0];

Patte = bougePatte(Patte, angle);
    
                hold on
                plot3( Patte.outil.rep(1, 4),Patte.outil.rep(2, 4), Patte.outil.rep(3, 4), '.b' );
 
                angle = [0;0;0;0];

Patte = bougePatte(Patte, angle);
    
                hold on
                plot3( Patte.outil.rep(1, 4),Patte.outil.rep(2, 4), Patte.outil.rep(3, 4), '.b' );
                


pas = -20;

% for angle_1 = -pi/8:pi/pas:pi/8
%     for angle_2 = -pi/4:pi/pas:pi/4
%         for angle_3 = 0:pi/pas:pi/4
%             for angle_4 = 0:pi/pas:(5*pi/12)
%             
%                 angle(1) = angle_1;
%                 angle(2) = angle_2;
%                 angle(3) = angle_3;
%                 angle(4) = angle_4;
%         
%                 Patte = bougePatte(Patte, angle);
%     
%                 hold on
%                 plot3( Patte.outil.rep(1, 4),Patte.outil.rep(2, 4), Patte.outil.rep(3, 4), '.b' );
%                 
%             end     
%         end
%     end
% end


for angle_4 = 0:pi/pas:-(5*pi/12)
    for angle_3 = 0:pi/pas:-pi/2
        for angle_2 = pi/4:pi/pas:-pi/4
            for angle_1 = pi/8:pi/pas:-pi/8
            
                angle(1) = angle_1;
                % angle(2) = angle_2;
                angle(3) = angle_3;
                angle(4) = angle_4;
        
                Patte = bougePatte(Patte, angle);
    
                hold on
                plot3( Patte.outil.rep(1, 4),Patte.outil.rep(2, 4), Patte.outil.rep(3, 4), '.b' );
                
            end     
        end
    end
end




end

