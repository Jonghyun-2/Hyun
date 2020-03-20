#!/usr/bin/env python
# coding: utf-8

# In[2]:


import glob
import numpy as np
import cv2 as cv
import tensorflow as tf
import matplotlib.pyplot as plt
import hyun_dataprocess as h_data
import tkinter as tk
from tkinter import filedialog


# In[3]:


from tensorflow.keras.applications.resnet_v2 import ResNet50V2


# In[4]:


path = r'C:\Users\micke\Downloads\DataSet\DentalScreening\*'
npyPath = glob.glob(path)[3]
labelPath = glob.glob(path)[0]


# In[5]:


def rotate_img(img, deg):
    n_rows, n_cols = img.shape[:2]
    
    if deg == 0:
        return img
    else:
        rotation_mat = cv.getRotationMatrix2D((n_cols // 2, n_rows // 2), deg, 1)
        rotated_img = cv.warpAffine(img, rotation_mat, (n_cols, n_rows))
        rotated_img = rotated_img[..., np.newaxis]
        
        return rotated_img

def read_data(imgs, labels, dtype=None, clip_range=None,
              udlr_idxs_to_crop=None, aug_flip_lr=False, aug_flip_ud=False, rotation_range=None):
    x = imgs
    y = labels
    
    if clip_range is not None:
        x = x[clip_range.start:clip_range.stop:clip_range.step, ...]
        y = y[clip_range.start:clip_range.stop:clip_range.step, ...]
    
    if udlr_idxs_to_crop is not None:
        x = x[:, udlr_idxs_to_crop[0]:udlr_idxs_to_crop[1], udlr_idxs_to_crop[2]:udlr_idxs_to_crop[3], :]
        
    if aug_flip_lr:
        x = np.concatenate((x, x[..., ::-1, :]))
        y = np.concatenate((y, y))
        
    if aug_flip_ud:
        x = np.concatenate((x, x[:, ::-1, ...]))
        y = np.concatenate((y, y))
        
    if rotation_range is not None:
        x = np.array([rotate_img(img, deg) for img in x for deg in rotation_range])
        y = np.repeat(y, len(rotation_range), axis=0)
    
    if dtype is not None:
        x = x.astype(dtype)
        y = y.astype(dtype)
    
#     print(x.dtype, x.shape)
#     jin_utils.print_mean_sd(x)
#     jin_utils.print_min_max(x)
#     print()
#     print(y.dtype, y.shape)
#     jin_utils.print_unique_cnt(y.astype(np.uint8))

    return x, y


# In[6]:


class hyperparameters():
    def __init__(self):
        self.input_shape = ()
        self.udlr_idxs_to_crop = ()
        self.batch_size = 32
        self.learning_rate = 1e-4
        self.epochs = 30
        
    def setparams(self,params):
        '''
        setparams[input_shape,udlr_idxs_to_crop,batch_size=32,epochs=1e-4,learning_rate=30]
        '''
        self.input_shape = params.get('input_shape')
        self.udlr_idxs_to_crop = params.get('udlr_idxs_to_crop')
        self.input_shape = (self.input_shape[0] - self.udlr_idxs_to_crop[0] + self.udlr_idxs_to_crop[1],
                            self.input_shape[1] - self.udlr_idxs_to_crop[2] + self.udlr_idxs_to_crop[3],
                            self.input_shape[2])
        self.batch_size = params.get('batch_size')
        self.epochs = params.get('epochs')
        self.learning_rate = params.get('learning_rate')        


# In[7]:


class dataProcessing():
    class imgProcess():
    #     def __init__(self):
    #         self.imgs
        def read_npy(self):
            root = tk.Tk()
            root.filename =  tk.filedialog.askopenfilename(initialdir = "C:",title = "choose your file",filetypes =(("npy file","*.npy"),("all files","*.*")))
            root.withdraw()
            return np.load(root.filename)

        def crop_img(self,imgs,croparea):
            '''
            Parameters
            ------------
            imgs : (n, width, height, channel)
                n : the number of imgs
            croparea : (x,y,width,height)
            '''
            imgs = imgs[:,croparea[0]:croparea[1],croparea[2]:croparea[3],:]
            return imgs
        def divide_imgs(self,imgs,testCount,trainCount = None):
            '''
             Parameters
            ------------
            imgs : full data set 
                (n, width, height, channel)
                n : the number of imgs
            testCount : the number of testset img
            trainCount : the number of trainset img
            '''
            testImgs = imgs[:testCount,...]
            if trainCount is not None:
                trainImgs = imgs[-trainCount :,...]
            else :
                trainImgs = imgs[testCount :,...]
            return testImgs, trainImgs
    class labelProcess():
        def divide_labels(self,labels,testCount,trainCount = None):
            testLabels = labels[:testCount]
            if trainCount is not None:
                trainLabels = labels[-trainCount :,...]
            else :
                trainLabels = labels[testCount :,...]
            return testLabels, trainLabels


# In[90]:


# class modelBuild():
# #     def __init__(self):
# #         self.model
        
#     def bulid_ResNet50V2(self, input_shape=None):
#         base_model = ResNet50V2(include_top=False, weights=None, input_shape=input_shape)

#         x = base_model.output
#         x = tf.keras.layers.GlobalAveragePooling2D(name='gap')(x)

#         x = tf.keras.layers.Dense(512, activation='relu', name='fc1')(x)
#         x = tf.keras.layers.Dense(256, activation='relu', name='fc2')(x)
#         main_output = tf.keras.layers.Dense(1, name='fc3')(x)

#         model = tf.keras.models.Model(inputs=base_model.input, outputs=main_output, name='resnet50_v2')

#         return model


# In[8]:


class modelMaker():
    def __init__(self,):
        self.history = None
        
    def set_hyperparams(self,hyperparameters):
        self.input_shape = hyperparameters.input_shape
        self.batch_size = hyperparameters.batch_size
        self.learning_rate = hyperparameters.learning_rate
        self.epochs = hyperparameters.epochs
        
    def bulid_model_ResNet50V2(self):
        base_model = ResNet50V2(include_top=False, weights=None, input_shape=self.input_shape)

        x = base_model.output
        x = tf.keras.layers.GlobalAveragePooling2D(name='gap')(x)

        x = tf.keras.layers.Dense(512, activation='relu', name='fc1')(x)
        x = tf.keras.layers.Dense(256, activation='relu', name='fc2')(x)
        main_output = tf.keras.layers.Dense(1, name='fc3')(x)

        model = tf.keras.models.Model(inputs=base_model.input, outputs=main_output, name='resnet50_v2')
        return model
        
    def compile_model(self, model,optimizer = tf.optimizers.Adam):
        
        model.compile(optimizer=optimizer(lr=self.learning_rate),
                  loss=tf.keras.losses.mean_squared_error, metrics=['mae'])
        return model
        
    def fit_model(self,model,trainImgs,trainLabels,testImgs=None,testLabels=None):
        if (testImgs is None and testLabels is None):
            history = model.fit(trainImgs, trainLabels,
                                 batch_size=self.batch_size,
                                 epochs=self.epochs)
            
        else:
            history = model.fit(trainImgs, trainLabels,
                                     batch_size=self.batch_size,
                                     epochs=self.epochs,
                                     validation_data=(testImgs, testLabels))
        return history
    
    def load_model(self):
        root = tk.Tk()
        root.filename =  tk.filedialog.askopenfilename(initialdir = "C:",title = "choose your file",filetypes =(("h5 files","*.h5"),("all files","*.*")))
        root.withdraw()
        model = tf.keras.models.load_model(root.filename)
        return model


# In[9]:


class visualize():
    def __init__(self):
        self.figsize = (14,4)
    def plotHistory(self,history):
        dict_hist = history.history
        list_hist = list(dict_hist.keys())
        plt.figure(figsize=self.figsize)
        plt.subplot(121)
        plt.title(list_hist[0])
        plt.plot(hist[list_hist[0]],'bo',label = list_hist[0])
        plt.plot(hist[list_hist[2]],'g',label = list_hist[2])
        plt.legend()

        plt.subplot(122)
        plt.title(list_hist[1])
        plt.plot(hist[list_hist[1]],'bo',label = list_hist[1])
        plt.plot(hist[list_hist[3]],'g',label = list_hist[3])
        plt.legend()
        plt.show()
    def drawHeatmap(self):
        # todo
        pass


# In[10]:


class logger():
    def save_weight(self,model,modelName):
        root = tk.Tk()
        root.filename = tk.filedialog.askdirectory(initialdir ="C:/")
        root.withdraw()
        path = root.filename+ "/"
        model.save(path+modelName)
        print("Model Save : Done")
        
    def save_heatmap(self,img,imgName):
        root = tk.Tk()
        root.filename = tk.filedialog.askdirectory(initialdir ="C:/")
        root.withdraw()
        path = root.filename+ "/"
        cv.imwrite(path+imgName,img)
        print("Img Save : Done")
