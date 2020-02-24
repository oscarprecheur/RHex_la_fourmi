# -*- coding: utf-8 -*-

from tkinter import * 
from tkinter.messagebox import *
import tkinter as tk


string = str()
string="toto"

class Application:
    
    def __init__(self):
        """Constructeur de la fenêtre principale"""
        self.root =Tk()
        self.root.title('RHEX')
        self.root.geometry("850x220")
        Label(self.root,
              text ="Rhex le chat").grid(row =0, column=0)


        #groupe boutons deplacements
        Button(self.root, text ='Front move',
               command =self.gofront).grid(row =3, column=8)
        Button(self.root, text ='Rear move',
               command =self.gorear).grid(row =5, column=8)
        Button(self.root, text ='Right move',
               command =self.goright).grid(row =4, column=9)
        Button(self.root, text ='Left move',
               command =self.goleft).grid(row =4, column=7)

        #groupe boutons on/off
        Button(self.root, text ='Robot on',
               command =self.poweron).grid(row =1, column=0, columnspan=2)
        Button(self.root, text ='Robot off',
               command =self.poweroff).grid(row =2, column=0, columnspan=2)
        
        #groupe boutons up/down
        Button(self.root, text ='Move Up',
               command =self.goup).grid(row =1, column=10, columnspan=3)
        Button(self.root, text ='Move Down',
               command =self.godown).grid(row =2, column=10, columnspan=3)
        
        #Bouton quitter 
        Button(self.root, text ='Quitter',
               command =self.root.destroy).grid(row =6, sticky = SW)
        
        #Zone de texte
        self.listbox = Text(self.root, width = 55, height = 10, wrap = WORD, background ='White')
        self.listbox.grid(row = 1,rowspan=15, column = 13)

        #scrollbar
        self.defilY = Scrollbar(self.root, orient='vertical',
        command=self.listbox.yview)
        self.defilY.grid(row=1, rowspan=15, column=15, sticky='ns')
        self.listbox['yscrollcommand'] = self.defilY.set

        #Bouton clear ecran
        #Button(self.root, text ='Clrscrn',
        #       command =self.listbox.delete(1.0,END)).grid(row = 6, column = 5)

       
        self.root.mainloop()

    #Controle des pattes 



    #fonctions de gestion des mouvements
 
    def gofront(self):
        #self.listbox['state']=NORMAL
        string="Front : [Frame]"
        self.listbox.insert(1.0,string + '\n' )
        #self.listbox['state']=DISABLED
    def gorear(self):
        string="Rear : [Frame]"
        self.listbox.insert(1.0,string + '\n' )
    def goright(self):
        string="Right : [Frame]"
        self.listbox.insert(1.0,string + '\n' )        
    def goleft(self):
        string="Left : [Frame]"
        self.listbox.insert(1.0,string + '\n' )
    def goup(self):
        string="Up : [Frame]"
        self.listbox.insert(1.0,string + '\n' )
    def godown(self):
        string="Down : [Frame]"
        self.listbox.insert(1.0,string + '\n' )

    #fonctions allumage/arret
    def poweron(self):
        string="On : [Frame]"
        self.listbox.insert(1.0,string + '\n' )
    def poweroff(self):
        string="Off : [Frame]"
        self.listbox.insert(1.0,string + '\n' )


    
   
f = Application()
