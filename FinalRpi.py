import serial
import time
from time import sleep
import pytesseract
import cv2
import threading
import os
import numpy as np
from threading import Thread, Lock


Flag = 0
Flag1 = 0
Steps = "280\n"
StepstoNextBelt = "550\n"
matchFound = "540\n"
nomatchFound = "500\n"
myconfig = r"--psm 7 --oem 1"

path = r'/home/pi/PD/images/2.png'




if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.reset_input_buffer()
label_cascade = cv2.CascadeClassifier('/home/pi/PD/Project/cascade.xml')




def readSerial():
    while True:
        if ser.in_waiting > 0:
            global Flag
           
            Flag = 0
            line = ser.readline().decode('utf-8').rstrip()
            num = int(line)
            print(num)
            Flag = num
            if(Flag == 3):
                    if((Pcode[0] == 'M') or (Pcode[1] == 'M') or (Pcode[2] == 'M') ):
                        print('match found')
                        ser.reset_input_buffer()
                        ser.write(matchFound.encode('utf-8'))
                        Flag =0
                   
                    else:
                        print('no match')
                        ser.reset_input_buffer()
                        ser.write(nomatchFound.encode('utf-8'))
                        Flag =0
                       
           
           
                               
readSerialTh = threading.Thread(target=readSerial,)
readSerialTh.daemon=True
readSerialTh.start()



while True:
   
    if(Flag == 1):
       
        ser.write(Steps.encode('utf-8'))
        #ser.write(StepstoNextBelt.encode('utf-8'))
        Flag = 0
    elif(Flag == 2):
       
        vid = cv2.VideoCapture(0)
       
        ret, frame = vid.read()
        sleep(1)
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
       
       
       
        #detection part
        labels = label_cascade.detectMultiScale(gray, 1.05,8, minSize=(180,180))
        #for (x, y, w, h) in labels:
         #   cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0), 2)
        for (x, y, w, h) in labels:
            cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0), 2)
           
       
       
           
       
        #image = cv2.rotate(thresh, cv2.cv2.ROTATE_90_CLOCKWISE)
        frame = cv2.rotate(gray, cv2.cv2.ROTATE_90_CLOCKWISE)
        image_crop = frame[420:630,0:480]
        ret,thresh = cv2.threshold(image_crop,100,255,0)
        thresh = cv2.adaptiveThreshold(image_crop,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,\
            cv2.THRESH_BINARY,29,28)
        #thresh = cv2.threshold(thresh,110,255,0)
       # kernel = np.array([[-1,-1,-1], [-1,9,-1], [-1,-1,-1]])
        #thresh = cv2.filter2D(thresh, -1, kernel)
        cv2.imwrite('/home/pi/PD/images/2.png',thresh)
        sleep(0.1)
        text = pytesseract.image_to_string(cv2.imread(path),lang="eng",config=myconfig)
        print(text)
        Pcode = list(text)
        print(Pcode[0])
       
       
            #ser.write(matchFound.encode('utf-8'))
        cv2.imshow('frame', gray)
       
        cv2.imwrite('/home/pi/PD/images/1.png',gray)
         
        vid.release()
        cv2.destroyAllWindows()
        ser.write(StepstoNextBelt.encode('utf-8'))

         
    sleep(1)

   
   
   


