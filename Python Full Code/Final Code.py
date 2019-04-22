import serial
import pygame
import time
import os
import math



os.environ['SDL_VIDEODRIVER'] = 'dummy'  #  MUST BE HERE FOR PYGAME TO WORK!!!!

ser1 = serial.Serial('/dev/ttyACM0', 57600, timeout = 1) # $ ls /dev/tty* to find arduino port
ser2 = serial.Serial('/dev/ttyACM1', 57600, timeout = 1)
time.sleep(2)

def liftRaise():
    ser2.write(b'g')
    print('Lift is Raising!')

def liftLower():
    ser2.write(b'h')
    print('Lift is Lowering!')

def launchSpinUp():
    ser2.write(b'i')
    print('Preparing for Launch!')

def shoot():
    ser2.write(b'j')
    print('Firing!')

def launchExit():
    ser2.write(b'y')
    print('Exiting Launch Mode!')

def haltLift():
    ser2.write(b'x')
    print('Stopping Lift Actuation!')

def pistonExtend():
    ser2.write(b'w')
    print('Piston Extending')

def pistonRetract():
    ser2.write(b'v')
    print('Piston Retracting')

def haltPiston():
    ser2.write(b'u')
    print('Halting piston actuation')

def halt():
    ser1.write(b'z')
    print('Brakes!')

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

pygame.init()
pygame.display.set_mode((1, 1))  ##Sets up size of dummy display so pygame.video gets initialized
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()

mode = 'manual'
done = False

while done == False:

    if mode == 'manual':

        ser1.write(b'M')

        while ((mode == 'manual') and (done == False)):

            #  Allow inputs from controller to be processed
            pygame.event.get()

            if joystick.get_button(6) or joystick.get_button(7):

                halt()

                while joystick.get_button(6) and done == False and mode == 'manual':

                    liftRaise()
                    pygame.event.get()

                    if joystick.get_button(2):

                        done = True

                    if joystick.get_button(9):

                        mode == 'auto'

                while joystick.get_button(7) and done == False and mode == 'manual':

                    liftLower()
                    pygame.event.get()

                    if joystick.get_button(2):

                        done = True

                    if joystick.get_button(9):

                        mode == 'auto'

                haltLift()

            #  Set 'Share'-button to enter launch mode
            if joystick.get_button(8):

                halt()

                #  Initialize condition for launch mode while loop
                launchMode = True

                #  Allow launch motors to spin throughout launch mode
                launchSpinUp()

                #  Launch mode loop
                while done == False and launchMode == True and mode == 'manual':

                    pygame.event.get()

                    #  Allow program to end straight from launch mode
                    if joystick.get_button(2):

                        done = True

                    #  Allow launch mode to end without ending manual mode
                    elif joystick.get_button(3):

                        launchMode = False

                    elif joystick.get_button(9):

                        mode = 'auto'

                    else:

                        #shoot()  ###REMEMBER TO PUT PISTON CYCLE CONDITION HERE!!!###
                        if joystick.get_button(5) or joystick.get_button(4):

                            while joystick.get_button(5) and done == False and mode == 'manual':

                                pistonExtend()
                                pygame.event.get()

                                if joystick.get_button(2):

                                    done = True

                                if joystick.get_button(9):

                                    mode = 'auto'

                            while joystick.get_button(4) and done == False and mode == 'manual':

                                pistonRetract()
                                pygame.event.get()

                                if joystick.get_button(2):

                                    done = True

                                if joystick.get_button(9):

                                    mode = 'auto'

                            haltPiston()
        
                launchExit()
        
            if joystick.get_button(5) or joystick.get_button(4):

                halt()

                while joystick.get_button(5) and done == False and mode == 'manual':

                    pistonExtend()
                    pygame.event.get()

                    if joystick.get_button(2):

                        done = True

                    if joystick.get_button(9):

                        mode = 'auto'

                while joystick.get_button(4) and done == False and mode == 'manual':

                    pistonRetract()
                    pygame.event.get()

                    if joystick.get_button(2):

                        done = True

                    if joystick.get_button(9):

                        mode = 'auto'

                haltPiston()


            if joystick.get_button(2) or done == True:

                print('\t\t\t  O-button pressed!')
                print('\t\t\tExiting Manual Mode')

                done = True

            if joystick.get_button(9) or mode == 'auto':

                print('\t\t\tStart button Pressed!')
                print('\t\t\t Entering Auto Mode')

                mode = 'auto'

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

#           if abs(xPos) < 0.2:

#               xPos = 0 

#           if abs(yPos) < 0.2:

#               yPos = 0

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

            if wheels == ['1000','1000','1000','1000']:
                halt()

            else:

                for i in range(4):
        
                    for j in range(4):
                        ser1.write((wheels[i][j]).encode())

    if mode == 'auto':

        ser1.write(b'A')

        while done == False and mode == 'auto':

            if ser1.in_waiting > 0:

                data = ser1.read()

                if data == b'a':

                    liftRaise()

                    while ser2.in_waiting == 0:

                        if joystick.get_button(8):

                            done = True

                        if joystick.get_button(9):

                            mode = 'manual'

                    data = ser2.read()

                    haltLift()

                    time.sleep(2)

                    while data == b'b':

                        liftLower()

                        while ser2.in_waiting == 0:

                            if joystick.get_button(8):

                                done = True

                            if joystick.get_button(9):

                                mode = 'manual'

                        data = ser2.read()

                    if data == b'C':

                        ser1.write(b'C')

                    time.sleep(1)

            if ser1.in_waiting > 0:

                data = ser1.read()

                if data == b'E':

                    launchSpinUp()

                    for i in range(3):

                        pistonExtend()
                        time.sleep(2)
                        pistonRetract()
                        time.sleep(2)

                    haltPiston()

                    mode = 'manual'

            if joystick.get_button(8):

                done = True

            if joystick.get_button(9):

                mode = 'manual'

ser1.close()
ser2.close()
pygame.quit()

            
    
