function tournerG(Patte_L,Patte_R)
for m = 1:5
    angle_D = [ 0     0    -pi/4    -pi/4 ;
                0     0    -pi/4    -pi/4 ;
                0     0    -pi/4    -pi/4 ];
            
     angle_G = [ 0   0    -pi/4   -pi/4 ;
                 0   0    -pi/4   -pi/4 ;
                 0   0    -pi/4   -pi/4 ];

        
        %% Motion et dessin des pattes
        [ Patte_L, Patte_R ] = MGD( Patte_L, Patte_R, angle_D, angle_G );
        

end
    for i = 0:0.2:pi
        %% Initialisation des angles
        
        
        
        angle_D(1,1:4) = [ -i/4 0 -0.159*(i-pi/2)*(i-pi/2)-pi/8 -pi/4 ];%bouger patte 1
        angle_G(3,1:4) = [ +i/4 0 -0.159*(i-pi/2)*(i-pi/2)-pi/8 -pi/4 ];%bouger patte6
        [ Patte_L, Patte_R ] = MGD( Patte_L, Patte_R, angle_D, angle_G );
        
        
    end
    for i = 0:0.2:pi
        
        
        angle_D(2,1:4) = [ -i/4 0 -0.159*(i-pi/2)*(i-pi/2)-pi/8  -pi/4 ];%pouger patte 2
        angle_G(2,1:4) = [ i/4 0 -0.159*(i-pi/2)*(i-pi/2)-pi/8  -pi/4 ];%pouger patte 5
        
        
        
        
        %% Motion et dessin des pattes
        [ Patte_L, Patte_R ] = MGD( Patte_L, Patte_R, angle_D, angle_G );
              hold on
    end
     for i = 0:0.2:pi
         angle_D(3,1:4) = [ -i/4 0 -0.159*(i-pi/2)*(i-pi/2)-pi/8 -pi/4 ];%bouger patte3
         angle_G(1,1:4) = [ +i/4 0 -0.159*(i-pi/2)*(i-pi/2)-pi/8 -pi/4 ];%bouger patte 4
         [ Patte_L, Patte_R ] = MGD( Patte_L, Patte_R, angle_D, angle_G );
     end
     
        
 
    %faire avancer le robot
      for i = pi:-0.6:0
        %% Initialisation des angles
        
        angle_D = [ -i/4      0    -pi/4   -pi/4 ;
                    -i/4       0    -pi/4   -pi/4 ;
                    -i/4      0    -pi/4   -pi/4 ];
        
        angle_G = [ i/4 0    -pi/4    -pi/4 ;
                    i/4    0    -pi/4    -pi/4 ;
                    i/4   0    -pi/4    -pi/4 ];
        
        
 
        %% Motion et dessin des pattes
        [ Patte_L, Patte_R ] = MGD( Patte_L, Patte_R, angle_D, angle_G );
      end
end
    