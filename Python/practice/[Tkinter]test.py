import tkinter as tk
from tkinter import filedialog
from tkinter import ttk
from matplotlib.figure import Figure
import numpy as np
import glob

class palette:
    def __init__(self):
        ################################################################################################################
        ###################### Function Parameters #####################################################################
        ################################################################################################################

        ############################
        ##### I/O ##################
        ############################
        self.rootPath = ""

        ################################################################################################################
        ###################### Design Parameters #######################################################################
        ################################################################################################################

        ############################
        ##### Canvas Parameter #####
        ############################
        self.bgColor = ["midnightBlue","red"]
        self.fgColor = ["white"]

        ############################
        ##### Frame Parameter #####
        ############################
        self.fHeight = 480

        ############################
        ##### Button Parameter #####
        ############################
        self.bWidth = 10
        self.bHeight = 1
        self.buttonRelief = ['flat', 'groove', 'raised', 'ridge', 'solid', 'sunken']

        ############################
        ### CheckBox Parameter #####
        ############################
        self.cFrameWidth = 150
        self.cFrameHeight = 350
        self.cBoxWidth = 13
        # 버튼이 체크된경우 1, 체크되지 않았을경우 1
        self.cVar1 = 0
        self.cVar2 = 0
        # 추가 self.cVar3 = 0

        ################################################################################################################
        ######################  Window Setting #########################################################################
        ################################################################################################################

        self.window = tk.Tk()
        self.setCanvas()
        self.setButton()
        self.window.mainloop()

    def setCanvas(self):
        # geometry("너비x높이+초기x좌표+초기y좌표")
        self.window.geometry("640x480+10+10")
        self.window.title("Smart Monitoring tool")
        self.window.configure(background=self.bgColor[1])
        self.window.resizable(False,False)

    # 버튼의 위치 스타일 지정
    def setButton(self):
        # bg=self.bgColor[0], fg= self.fgColor[0]
        self.cVar1 = tk.IntVar()
        self.cVar2 = tk.IntVar()

        # Frame
        self.initFrame = tk.Frame(self.window,width = 200,height =self.fHeight,bg=self.bgColor[0])
        self.initFrame.pack()
        #self.initFrame.pack(side="left",fill="both")
        self.plotFrame = tk.Frame(self.window,width = 320,height =self.fHeight)
        self.plotFrame.pack()
        #self.plotFrame.pack(side="center",fill="both")
        self.tabelFrame = tk.Frame(self.window, width=120, height=self.fHeight)
        self.tabelFrame.pack()
        #self.tabelFrame.pack(side="right")
        # initFrame
        self.loadButton = tk.Button(self.initFrame, text='load', command=self.setPath, width =self.bWidth,height =self.bHeight,bg=self.bgColor[0], fg= self.fgColor[0], relief=self.buttonRelief[4])
        self.loadButton.pack()
        # self.check1 = tk.Checkbutton(self.window, text= "Remaining Teeth",bg=self.bgColor[0], fg= self.fgColor[0],variable = self.cVar1, command=self.toggle)
        self.checkmenu = tk.LabelFrame(self.initFrame, text="Check box",width=self.cFrameWidth, height=self.cFrameHeight, bg=self.bgColor[0],fg=self.fgColor[0])
        self.checkmenu.pack()
        self.check1 = ttk.Checkbutton(self.checkmenu, text="Remaining Teeth", variable=self.cVar1,width=self.cBoxWidth)
        self.check1.pack()
        self.check2 = ttk.Checkbutton(self.checkmenu, text="Implant Teeth", variable=self.cVar2,width=self.cBoxWidth)
        self.check2.pack()
        self.startButton = ttk.Button(self.checkmenu,text="start !",width = self.cBoxWidth)
        self.startButton.pack()
        self.quitButton = tk.Button(self.initFrame, text='Quit', command=self.window.quit, width=self.bWidth, height=self.bHeight, bg=self.bgColor[0], fg=self.fgColor[0], relief=self.buttonRelief[4])
        self.quitButton.pack()


        ###########################
        ###### Location Info ######
        ###########################
        self.loadButton.place(x=10, y=10)
        self.checkmenu.place(x=10, y=60)
        self.check1.place(x=10, y=80)
        self.check2.place(x=10, y=100)
        self.startButton.place(x=10, y=300)
        self.quitButton.place(x=10, y=430)

    # Root dir을 얻기 위한 함수
    def setPath(self):
        self.rootPath = tk.filedialog.askdirectory()
        if self.rootPath != "":
            # initial area
            self.erase = tk.Label(self.window,width=470, height=1,bg=self.bgColor[0])
            self.erase.place(x=10, y=40)
            self.status = tk.Label(self.window, text=self.rootPath,height=1,bg=self.bgColor[0], fg= self.fgColor[0])
            #self.status.pack()
            self.status.place(x=10, y=40)



test = palette()
print(test.cVar1.get())
print(test.cVar2.get())




























