import time
import os
import pygame
import math
import serial

rad2deg = 180/math.pi
deg2rad = math.pi/180

os.environ['SDL_VIDEODRIVER'] = 'dummy'

def getMotor(speed):
    
    if speed < 0:

        speed = abs(speed)

        direction = '0'
        hundreds = math.trunc(speed/100)
        tens = math.trunc((speed-100*hundreds)/10)
        ones = math.trunc(speed-100*hundreds-10*tens)
        wheel = direction + str(hundreds) + str(tens) + str(ones)

    else:

        speed = abs(speed)

        direction = '1'
        hundreds = math.trunc(speed/100)
        tens = math.trunc((speed-100*hundreds)/10)
        ones = math.trunc(speed-100*hundreds-10*tens)
        wheel = direction + str(hundreds) + str(tens) + str(ones)

    return wheel

ser1 = serial.Serial('/dev/ttyACM0', 57600, timeout = 1)
time.sleep(2)

pygame.init()
pygame.display.set_mode((1, 1))  ##Sets up size of dummy display so pygame.video gets initialized
pygame.joystick.init()

joystick = pygame.joystick.Joystick(0)
joystick.init()

done = False

while done == False:
    #startTime = time.clock()
    translateSpeed = 0
    rotationSpeed = 0

    pygame.event.get()


    xPos = joystick.get_axis(0)
    yPos = -(joystick.get_axis(1))
    rotation = joystick.get_axis(2)

    #print(xPos)
    #print(yPos)
    #print(rotation)

    if abs(xPos) < 0.2 and abs(yPos) < 0.2:

        xPos = 0
        yPos = 0

#    if abs(xPos) < 0.2:

#        xPos = 0 

#    if abs(yPos) < 0.2:

#        yPos = 0

    if abs(rotation) < 0.2:

        rotation = 0

    else:

        rotationSpeed = round(127*rotation)

    if xPos == 0 and yPos == 0:

        theta = 0

    else:

        theta = math.atan2(yPos, xPos)

    translateSpeed = round(127*math.sqrt(xPos**2 + yPos**2))

    #print(rotationSpeed)
    #print(translateSpeed)

    if translateSpeed > 127:

        translateSpeed = 127

    motorSpeed1 = round(translateSpeed*math.sin(theta+(math.pi/4)))+rotationSpeed
    motorSpeed2 = round(translateSpeed*math.sin(theta-(math.pi/4)))-rotationSpeed
    motorSpeed3 = round(translateSpeed*math.sin(theta-(math.pi/4)))+rotationSpeed
    motorSpeed4 = round(translateSpeed*math.sin(theta+(math.pi/4)))-rotationSpeed

    wheel1 = getMotor(motorSpeed1)
    wheel2 = getMotor(motorSpeed2)
    wheel3 = getMotor(motorSpeed3)
    wheel4 = getMotor(motorSpeed4)

    wheels = [wheel1, wheel2, wheel3, wheel4]
    
    if joystick.get_button(2):

        print('\t\t\t  O-button pressed!')
        print('\t\t\tExiting Mecanum Mode')
        done = True
        wheels = ['1000','1000','1000','1000']

    print(wheels)
    ser1.write('.'.encode("ascii"))

    for i in range(4):
        
        for j in range(4):
            ser1.write((wheels[i][j]).encode())
    #ser1.read(2)

    #time.sleep(0.1)
    #endTime = time.clock()
    #print("Time to process: ", endTime - startTime)

ser1.close()    
pygame.quit()
