#!/usr/bin/python3
#azeazeazeaze
#https://docs.python.org/3/library/struct.html#format-characters
import struct
from math import *

# b(1) signed char
# B(1) unsigned char
# h(2) short
# H(2) usigned short
# f(4) float

r2d=180/pi
d2r=1/r2d
r2n=32767/pi
d2n=32767/180
n2r=1/r2n
n2d=1/d2n


ADDR_VERSION=0
ADDR_PATTE=2
ADDR_OPERATING_MODE=3
ADDR_STATUS=4

ADDR_VELOCITY_LIMIT=ADDR_STATUS+4

ADDR_VELOCITY_LIMIT1=ADDR_VELOCITY_LIMIT
ADDR_VELOCITY_LIMIT2=ADDR_VELOCITY_LIMIT+4
ADDR_VELOCITY_LIMIT3=ADDR_VELOCITY_LIMIT+8
ADDR_VELOCITY_LIMIT4=ADDR_VELOCITY_LIMIT+12


ADDR_MAX_POS=ADDR_VELOCITY_LIMIT4+4

ADDR_MAX_POS1=ADDR_MAX_POS
ADDR_MIN_POS1=ADDR_MAX_POS+2
ADDR_MAX_POS2=ADDR_MAX_POS+4
ADDR_MIN_POS2=ADDR_MAX_POS+6
ADDR_MAX_POS3=ADDR_MAX_POS+8
ADDR_MIN_POS3=ADDR_MAX_POS+10
ADDR_MAX_POS4=ADDR_MAX_POS+12
ADDR_MIN_POS4=ADDR_MAX_POS+14

ADDR_CURRENT_POS=ADDR_MIN_POS4+2

ADDR_CURRENT_POS1=ADDR_CURRENT_POS
ADDR_CURRENT_POS2=ADDR_CURRENT_POS+2
ADDR_CURRENT_POS3=ADDR_CURRENT_POS+4
ADDR_CURRENT_POS4=ADDR_CURRENT_POS+6

ADDR_CURRENT_COORD=ADDR_CURRENT_POS4+2
ADDR_CURRENT_X=ADDR_CURRENT_COORD
ADDR_CURRENT_Y=ADDR_CURRENT_COORD+4
ADDR_CURRENT_Z=ADDR_CURRENT_COORD+8


ADDR_GOAL_POS=ADDR_CURRENT_Z+4
ADDR_GOAL_POS1=ADDR_GOAL_POS
ADDR_GOAL_POS2=ADDR_GOAL_POS+2
ADDR_GOAL_POS3=ADDR_GOAL_POS+4
ADDR_GOAL_POS4=ADDR_GOAL_POS+6

ADDR_GOAL_COORD=ADDR_GOAL_POS4+2
ADDR_GOAL_X=ADDR_GOAL_COORD
ADDR_GOAL_Y=ADDR_GOAL_COORD+4
ADDR_GOAL_Z=ADDR_GOAL_COORD+8


ADDR_KP=ADDR_GOAL_Z+4
ADDR_KP1=ADDR_KP
ADDR_KP2=ADDR_KP+4
ADDR_KP3=ADDR_KP+8
ADDR_KP4=ADDR_KP+12

INST_PING=1
INST_READ=2
INST_WRITE=3
INST_FONCTION=6

FONC_RESET_CODEUR=1
FONC_VARIATEUR=2


#dimensions robot
d1=0.130
d2=0.200
d3=0.330  #d3 bout de sphere : enlever rayon sur Z

from socket import *
from time import *

sp=socket(AF_INET,SOCK_DGRAM)
PATTE=[(0,0),('192.168.0.1',6000),('192.168.0.2',6000),('192.168.0.3',6000),('192.168.0.4',6000),('192.168.0.5',6000),('192.168.0.6',6000),]

def MGI3(P): 
    #modele avec q2=0
    x=P[0]
    y=P[1]
    z=P[2]
   
    
    q1=atan2(y,x)-pi/2
    #modele 2axes
    YY=-z
    XX=sqrt(x*x+y*y)-d1
    #pos coude bas
    q4=acos((XX*XX+YY*YY-(d2*d2+d3*d3))/2/d2/d3);
    #pos coude haut
    #q(4)=acos((XX*XX+YY*YY-(d2*d2+d3*d3))/2/d2/d3);
    a1=d2+d3*cos(q4);
    a2=d3*sin(q4)
    q3=atan2(a1*YY-a2*XX,a1*XX+a2*YY)
    return (q1,0,q3,q4)

def MGD(q):
    q1=q[0]
    q2=q[1]
    q3=q[2]
    q4=q[3]
    x=cos(q1)*sin(q2)*(-d3*cos(q3)*sin(q4)-sin(q3)*(d3*cos(q4)+d2))-sin(q1)*(-d3*sin(q3)*sin(q4)+cos(q3)*(d3*cos(q4)+d2)+d1)
    y=cos(q1)*(-d3*sin(q3)*sin(q4)+cos(q3)*(d3*cos(q4)+d2)+d1)+sin(q1)*sin(q2)*(-d3*cos(q3)*sin(q4)-sin(q3)*(d3*cos(q4)+d2))
    z=cos(q2)*(-d3*cos(q3)*sin(q4)-sin(q3)*(d3*cos(q4)+d2))
    return(x,y,z)
    

def write1(id,addr,val):
    nb=4+1;
    frame=bytes([id])+bytes([nb])+bytes([INST_WRITE])+bytes([addr])+struct.pack("B",val)
    sp.sendto(bytes(frame,),PATTE[id])

def write2(id,addr,val):
    nb=4+2;
     
    frame=bytes([id])+bytes([nb])+bytes([INST_WRITE])+bytes([addr])+struct.pack("h",val)
    sp.sendto(bytes(frame,),PATTE[id])

def write4(id,addr,val):
    nb=4+4;
    frame=bytes([id])+bytes([nb])+bytes([INST_WRITE])+bytes([addr])+struct.pack("f",val)
    sp.sendto(bytes(frame,),PATTE[id])

conv=32767/pi
conv=32767/180

def SetVmax(id,vmax):
    frame=bytes([id])+bytes([nb])+bytes([INST_WRITE])+bytes([ADDR_VELOCITY_LIMIT])+struct.pack("f",vmax)+struct.pack("f",vmax)+struct.pack("f",vmax)+struct.pack("f",vmax)

def SetGoalPos(id,p1,p2,p3,p4):
    #envoie consigne pos en rad
    nb=(4+4*2)
#    frame=bytes([id])+bytes([nb])+bytes([INST_WRITE])+bytes([ADDR_GOAL_POS1])+struct.pack("h",int(p1*conv))+struct.pack("h",int(p2*conv))+struct.pack("h",int(p3*conv))+struct.pack("h",int(p4*conv))
    frame=bytes([id])+bytes([nb])+bytes([INST_WRITE])+bytes([ADDR_GOAL_POS1])+struct.pack("h",int(p1))+struct.pack("h",int(p2))+struct.pack("h",int(p3))+struct.pack("h",int(p4))
    
##    nb=(4+3*2)
##    frame=bytes([id])+bytes([nb])+bytes([INST_WRITE])+bytes([ADDR_GOAL_POS2])+struct.pack("h",p2)+struct.pack("h",p3)+struct.pack("h",p4)
##    
    sp.sendto(bytes(frame,),PATTE[id])

def ResetCodeur(id,cod):
    nb=(4+1)
    frame=bytes([id])+bytes([nb])+bytes([INST_FONCTION])+bytes([FONC_RESET_CODEUR])+bytes([cod])
    sp.sendto(bytes(frame,),PATTE[id])

def ActiveVariateur(id,cod):
    nb=(4+1)
    frame=bytes([id])+bytes([nb])+bytes([INST_FONCTION])+bytes([FONC_VARIATEUR])+bytes([cod])
    sp.sendto(bytes(frame,),PATTE[id])



#demande pos 
#frame=b"q"+bytes([3])
#sp.sendto(bytes(frame,),PATTE)
#data,aa=sp.recvfrom(500)
#print(data)
#print(data[1:2])
#art=struct.unpack('B',data[1:2])
#val=struct.unpack('h',data[2:4])
#print("q%d : %d" % (art[0],val[0]))


#SetGoalPos(4,5,6,7,8);
#write1(4,ADDR_STATUS,10);
#write2(4,ADDR_MAX_POS4,-400)
#write4(4,ADDR_VELOCITY_LIMIT4,-500.1);
#write4(4,ADDR_CURRENT_Z,-500.1);
#write2(4,ADDR_GOAL_POS1,-40)
#write4(4,ADDR_GOAL_X,-500.1);

#write2(4,ADDR_GOAL_POS2,0)
#write2(4,ADDR_GOAL_POS3,2000)
##sleep(0.1)
##write2(4,ADDR_GOAL_POS4,-6000)
##sleep(0.1)

#write2(3,ADDR_GOAL_POS4,-6000)
sleep(0.1)
#SetGoalPos(3,-0,0,0,0)
#SetGoalPos(3,0,0,0,0)

##sleep(0.1)
#print(MGI3((0,0.3,-0.23)))
#print(MGD((0,0,-30*d2r,120*d2r)))


#print(MGD(MGI3((0,0.3,-0.23))))
#sleep(1)

#ActiveVariateur(4,1)
#SetGoalPos(1,0,0,0,0)
#sleep(5)
#ActiveVariateur(1,0)


#ResetCodeur(5,3)

#for p in [1,2,3,4,5,6]:
#    ActiveVariateur(p,0)

pat=1
act=0

ActiveVariateur(pat,act)

#P6-2 : -150
#P5-2 : -150
#P4-2 : -150
#P3-2 : 250
#P2-2 : 900


SetGoalPos(pat,0,00,0,0)
sleep(1)
##ResetCodeur(pat,0)
#ResetCodeur(pat,2)
#ResetCodeur(pat,2)
##ResetCodeur(pat,3)

sleep(2)
#SetGoalPos(pat,0,0,0,0)


sleep(2)



#print("variateur 5")

#sleep(1)

sp.close()
exit()


q1=0
q2=0
q3=0
q4=0

for p in [1,2,3,4,5,6]:
    SetGoalPos(p,0,0,0,0)
    ActiveVariateur(p,1)


#ResetCodeur(1,3)

#ActiveVariateur(5,1)
#ResetCodeur(5,3)

sleep(5)


q1=0
q2=6000
q3=5000
q4=-15000

for p in [1,2,3]:
    SetGoalPos(p,q1,q2,q3,q4)
for p in [4,5,6]:
    SetGoalPos(p,-q1,-q2,q3,q4)

sleep(15)
q1=1000
q2=6000
q3=5000
q4=-8000

for p in [1,2,3]:
    SetGoalPos(p,q1,q2,q3,q4)
for p in [4,5,6]:
    SetGoalPos(p,-q1,-q2,q3,q4)


sleep(7)

q1=0
q2=0
q3=0
q4=0

for p in [1,2,3]:
    SetGoalPos(p,q1,q2,q3,q4)
for p in [4,5,6]:
    SetGoalPos(p,-q1,-q2,q3,q4)



#SetGoalPos(3,-0,0,000,-2000)

sleep(0.3)

sp.close()
