import serial
import pygame
import time
import os

os.environ['SDL_VIDEODRIVER'] = 'dummy'  #  MUST BE HERE FOR PYGAME TO WORK!!!!

ser1 = serial.Serial('/dev/ttyACM0', 57600, timeout = 5) # $ ls /dev/tty* to find arduino port
ser2 = serial.Serial('/dev/ttyACM1', 57600, timeout = 5)
time.sleep(2)

def forward():
    ser1.write(b'a')
    print('Moving Forward!')

def reverse():
    ser1.write(b'b')
    print('Moving Backward!')

def transLeft():
    ser1.write(b'c')
    print('Moving Left!')

def transRight():
    ser1.write(b'd')
    print('Moving Right!')

def zeroCCW():
    ser1.write(b'e')
    print('Turning Left!')

def zeroCW():
    ser1.write(b'f')
    print('Turning Right!')

def liftRaise():
    ser2.write(b'g')
    print('Lift is Raising!')

def liftLower():
    ser2.write(b'h')
    print('Lift is Lowering!')

def launchSpinUp():
    ser2.write(b'i')
    print('Preparing for Launch!')

#  Sends signal for piston to cycle one time
def shoot():
    ser2.write(b'j')
    print('Firing!')

def diagFL():
    ser1.write(b'k')
    print("Moving Forward Left")

def diagFR():
    ser1.write(b'l')
    print('Moving Forward Right')

def diagBL():
    ser1.write(b'm')
    print('Moving Backward Left')

def diagBR():
    ser1.write(b'n')
    print('Moving Backward Right')

def halt():
    ser1.write(b'z')
    print('Brakes!')

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

pygame.init()
pygame.display.set_mode((1, 1))  ##Sets up size of dummy display so pygame.video gets initialized
pygame.joystick.init()

done = False

#  Main Loop
while done == False:

    neutralSticks = 0

    #  Allow inputs from controller to be processed
    pygame.event.get()

    #  Initialize joystick object
    joystick = pygame.joystick.Joystick(0)
    joystick.init()

    #  Set joystick threshold for left stick for side to side motion
    if abs(joystick.get_axis(0)) > 0.5 and abs(joystick.get_axis(1)) < 0.5:

        if joystick.get_axis(0) < 0:

            transLeft()

        else:

            transRight()

    elif abs(joystick.get_axis(0)) > 0.5 and abs(joystick.get_axis(1)) > 0.5:

        if joystick.get_axis(0) < 0:

            if joystick.get_axis(1) < 0:

                diagFL()

            else:

                diagBL()

        if joystick.get_axis(0) > 0:

            if joystick.get_axis(1) < 0:

                diagFR()

            else:

                diagBR()

    else:

        neutralSticks += 1

    #  Set joystick threshold for left stick for back and forth motion
    if abs(joystick.get_axis(1)) > 0.5 and abs(joystick.get_axis(0)) < 0.5:

        if joystick.get_axis(1) < 0:

            forward()

        else:

            reverse()

    elif abs(joystick.get_axis(1)) > 0.5 and abs(joystick.get_axis(0)) > 0.5:

        if joystick.get_axis(1) < 0:

            if joystick.get_axis(0) < 0:

                diagFL()

            else:

                diagFR()

        else:

            if joystick.get_axis(0) < 0:

                diagBL()

            else:

                diagBR()

    else:

        neutralSticks += 1

    #  Set joystick threshold for right stick for turning motion
    if abs(joystick.get_axis(2)) > 0.5:

        if joystick.get_axis(2) < 0:

            zeroCCW()

        else:

            zeroCW()

    else:

        neutralSticks += 1

    if joystick.get_button(0) or neutralSticks == 3:

        halt()

    #  Set L2-button to raise lift
    if joystick.get_button(6) or joystick.get_button(7):

        halt()

        while joystick.get_button(6) and done == False:

            liftRaise()
            pygame.event.get()

            if joystick.get_button(2):

                done = True

        while joystick.get_button(7) and done == False:

            liftLower()
            pygame.event.get()

            if joystick.get_button(2):

                done = True

        haltLift()

    #  Set 'Share'-button to enter launch mode
    if joystick.get_button(8):

        halt()

        #  Initialize condition for launch mode while loop
        launchMode = True

        #  Allow launch motors to spin throughout launch mode
        launchSpinUp()

        #  Launch mode loop
        while done == False and launchMode == True:

            pygame.event.get()

            #  Allow program to end straight from launch mode
            if joystick.get_button(2):

                done = True

            #  Allow launch mode to end without ending manual mode
            elif joystick.get_button(3):

                launchMode = False

            else:

                #shoot()  ###REMEMBER TO PUT PISTON CYCLE CONDITION HERE!!!###
                if joystick.get_button(5) or joystick.get_button(4):

                    while joystick.get_button(5) and done == False:

                        pistonExtend()
                        pygame.event.get()

                        if joystick.get_button(2):

                            done = True

                    while joystick.get_button(4) and done == False:

                        pistonRetract()
                        pygame.event.get()

                        if joystick.get_button(2):

                            done = True

                    haltPiston()
    
        launchExit()
    
    if joystick.get_button(5) or joystick.get_button(4):

        halt()

        while joystick.get_button(5) and done == False:

            pistonExtend()
            pygame.event.get()

            if joystick.get_button(2):

                done = True

        while joystick.get_button(4) and done == False:

            pistonRetract()
            pygame.event.get()

            if joystick.get_button(2):

                done = True

        haltPiston()


    if joystick.get_button(2) or done == True:

        print('\t\t\t  O-button pressed!')
        print('\t\t\tExiting Manual Mode')

        done = True


ser1.close()
ser2.close()
pygame.quit()
