function demarche(Patte_L,Patte_R)

angle_D = [ 0     0    -pi/4                            -pi/4 ;     %patte 1
            0    0    -0.159*(-pi/2)*(-pi/2)-pi/8    -pi/4 ;     %patte 2
             0     0    -pi/4                            -pi/4 ];    %patte 3
        
        angle_G = [ 0    0    -0.159*(pi/2)*(pi/2)-pi/8   -pi/4 ;    %patte 4
                     0      0    -pi/4                           -pi/4 ;    %patte 5
                    0    0    -0.159*(pi/2)*(pi/2)-pi/8   -pi/4 ];   %patte 6


for m = 1:3
    for i = 0:0.2:pi
        %%Motion des pates  2 ,4 et 6 pour les placer pour avancer 
        
%         angle_D = [ 0     0    -pi/4                            -pi/4 ;     %patte 1
%                   -i/4    0    -0.159*(i-pi/2)*(i-pi/2)-pi/8    -pi/4 ;     %patte 2
%                     0     0    -pi/4                            -pi/4 ];    %patte 3
%         
%         angle_G = [ -i/4    0    -0.159*(i-pi/2)*(i-pi/2)-pi/8   -pi/4 ;    %patte 4
%                      0      0    -pi/4                           -pi/4 ;    %patte 5
%                     -i/4    0    -0.159*(i-pi/2)*(i-pi/2)-pi/8   -pi/4 ];   %patte 6
                
        angle_D(2,1:4) = [ -i/4    0    -0.159*(i-pi/2)*(i-pi/2)-pi/8    -pi/4 ];
        
        angle_G(1,1:4) = [ -i/4    0    -0.159*(i-pi/2)*(i-pi/2)-pi/8   -pi/4 ];
        
        angle_G(3,1:4) = [  -i/4    0    -0.159*(i-pi/2)*(i-pi/2)-pi/8   -pi/4 ];
        
        
        hold on
        
        %% Motion et dessin des pattes
        [ Patte_L, Patte_R ] = MGD( Patte_L, Patte_R, angle_D, angle_G );
        
    end
    
    for i = 0:0.2:pi
        %% Motion des pattes 1, 3 et 5 pour les placer pour avancer 
        
        angle_G(2,1:4) = [ -i/4 0 -0.159*(i-pi/2)*(i-pi/2)-pi/8  -pi/4 ];
        
        angle_D(1,1:4) = [ -i/4 0 -0.159*(i-pi/2)*(i-pi/2)-pi/8 -pi/4 ];
        
        angle_D(3,1:4) = [ -i/4 0 -0.159*(i-pi/2)*(i-pi/2)-pi/8 -pi/4 ];
        
        
        hold on
        
        %% Motion et dessin des pattes
        [ Patte_L, Patte_R ] = MGD( Patte_L, Patte_R, angle_D, angle_G );
        
        
    end
    %pattes placées, le robot avance 
      for i = pi:-0.6:0
        %% Initialisation des angles
        
        angle_D = [ 0      0    -pi/4   -pi/4 ;
                   -i/4    0    -pi/4   -pi/4 ;
                    0      0    -pi/4   -pi/4 ];
        
        angle_G = [ -i/4 0    -pi/4    -pi/4 ;
                    0    0    -pi/4    -pi/4 ;
                  -i/4   0    -pi/4    -pi/4 ];
        
        
    
        %on revient dans l'état initial
        %% Motion et dessin des pattes
      
         angle_G(2,1:4) = [ -i/4 0 -pi/4  -pi/4 ];%patte5
        
        angle_D(1,1:4) = [ -i/4 0 -pi/4 -pi/4 ];%patte1
        
        angle_D(3,1:4) = [ -i/4 0 -pi/4 -pi/4 ];%patte3
        
        hold on
        
        %% Motion et dessin des pattes
        [ Patte_L, Patte_R ] = MGD( Patte_L, Patte_R, angle_D, angle_G );
      end
end