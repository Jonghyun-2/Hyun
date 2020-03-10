import tkinter as tk
from tkinter import filedialog
from tkinter import ttk
from matplotlib.figure import Figure
import numpy as np
import glob

class corr:
    def __init__(self):
        self.rootPath = ""
        ############################
        ##### Canvas Parameter #####
        ############################
        self.bgColor = ["midnightBlue"]

        ############################
        ##### Button Parameter #####
        ############################
        self.buttonColor = ["white"]
        self.buttonRelief = ['flat', 'groove', 'raised', 'ridge', 'solid', 'sunken']

        self.window = tk.Tk()
        self.setCanvas()
        self.setButton()
        self.window.mainloop()

    def setCanvas(self):
        # geometry("너비x높이+초기x좌표+초기y좌표")
        self.window.geometry("640x480")
        self.window.title("Smart Monitoring tool")
        self.window.configure(background=self.bgColor[0])
        self.window.resizable(False,False)

    def setButton(self):
        self.loadButton = tk.Button(self.window, text='load', command=self.setPath,
                                    width =10,height = 1,bg=self.bgColor[0],fg= self.buttonColor[0],relief=self.buttonRelief[4])
        self.loadButton.pack()
        self.loadButton.place(x= 10,y=10)

        self.quitButton = tk.Button(self.window, text='Quit', command=self.window.quit,
                                    width = 10,height = 1,bg=self.bgColor[0],fg= self.buttonColor[0],relief=self.buttonRelief[4])
        self.quitButton.pack()
        self.quitButton.place(x=10, y=430)

#        self.action = ttk.Checkbutton(win, text=“ClickMe”, command = clickMe)

    def setPath(self):
        self.rootPath = tk.filedialog.askdirectory()
        if self.rootPath != "":
            # initial area
            self.erase = tk.Label(self.window,width=470, height=1,bg=self.bgColor[0])
            self.erase.place(x=10, y=40)
            self.status = tk.Label(self.window, text=self.rootPath,height=1)
            self.status.pack()
            self.status.place(x=10, y=40)


test = corr()




























