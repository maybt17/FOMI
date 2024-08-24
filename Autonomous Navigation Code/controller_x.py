#!/usr/bin/env python

import pygame
import RPi.GPIO as GPIO
import time
import subprocess 
from pygame.constants import JOYBUTTONDOWN
pygame.init()

# for 1st Motor on ENB
ENB = 33
IN4 = 35
IN3 = 37

# for 2nd Motor on ENA
ENA = 23
IN2 = 29
IN1 = 31

# GPIO meads, general purpose input slash output
# set pin numbers to the board's
GPIO.setmode(GPIO.BOARD)

# initialize EnA, In1 and In2
GPIO.setup(ENB, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(IN3, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(IN4, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(ENA, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(IN1, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(IN2, GPIO.OUT, initial=GPIO.LOW)

joysticks = []

for i in range(0, pygame.joystick.get_count()):
	joysticks.append(pygame.joystick.Joystick(i))
	joysticks[-1].init()

#Print out the name of the controller
print(pygame.joystick.Joystick(0).get_name())

#Xbox Joystick axis
#axis 0 up down, down -1, up 1 
#axis 1 left -1 right 1
#center = 0

#main loop
while True or KeyboardInterrupt:
	#check for joystick events
	for event in pygame.event.get():
		if event.type == JOYBUTTONDOWN:
			if event.button == 0:
				print("button 0 down")
				subprocess.call(['sh', './ros_startup.sh])
			if event.button == 1:
				print("button 1 down")
			if event.button == 2:
				print("button 2 down")
			if event.button == 3:
				print("button 3 down")
			if event.button == 4:
				print("button 4 down")
			if event.button == 5:
				print("button 5 down")
			if event.button == 6:
				print("button 6 down")
			if event.button == 7:
				print("button 7 down")
			if event.button == 8:
				print("button 8 down")
		if event.type == pygame.JOYAXISMOTION:
			if event.axis < 2: #left stick
				if event.axis == 0: #left/right
					if event.value < -0.5:
						GPIO.output(ENB, GPIO.HIGH)
						GPIO.output(IN3, GPIO.LOW)
						GPIO.output(IN4, GPIO.LOW)
						GPIO.output(ENA, GPIO.HIGH)
						GPIO.output(IN1, GPIO.LOW)
						GPIO.output(IN2, GPIO.HIGH)
						time.sleep(0.01)
						GPIO.output(ENB, GPIO.HIGH)
						GPIO.output(IN3, GPIO.LOW)
						GPIO.output(IN4, GPIO.LOW)
						GPIO.output(ENA, GPIO.HIGH)
						GPIO.output(IN1, GPIO.LOW)
						GPIO.output(IN2, GPIO.LOW)
					if event.value > 0.5:
						GPIO.output(ENB, GPIO.HIGH)
						GPIO.output(IN3, GPIO.HIGH)
						GPIO.output(IN4, GPIO.LOW)
						GPIO.output(ENA, GPIO.HIGH)
						GPIO.output(IN1, GPIO.LOW)
						GPIO.output(IN2, GPIO.LOW)
						time.sleep(0.01)
						GPIO.output(ENB, GPIO.HIGH)
						GPIO.output(IN3, GPIO.LOW)
						GPIO.output(IN4, GPIO.LOW)
						GPIO.output(ENA, GPIO.HIGH)
						GPIO.output(IN1, GPIO.LOW)
						GPIO.output(IN2, GPIO.LOW)
				if event.axis == 1: #up/down
					if event.value < -0.5: #forwards
						GPIO.output(ENB, GPIO.HIGH)
						GPIO.output(IN3, GPIO.HIGH)
						GPIO.output(IN4, GPIO.LOW)
						GPIO.output(ENA, GPIO.HIGH)
						GPIO.output(IN1, GPIO.LOW)
						GPIO.output(IN2, GPIO.HIGH)
						time.sleep(0.01)
						GPIO.output(ENB, GPIO.HIGH)
						GPIO.output(IN3, GPIO.LOW)
						GPIO.output(IN4, GPIO.LOW)
						GPIO.output(ENA, GPIO.HIGH)
						GPIO.output(IN1, GPIO.LOW)
						GPIO.output(IN2, GPIO.LOW)
					if event.value > 0.5: #backwards
						GPIO.output(ENB, GPIO.HIGH)
						GPIO.output(IN3, GPIO.LOW)
						GPIO.output(IN4, GPIO.HIGH)
						GPIO.output(ENA, GPIO.HIGH)
						GPIO.output(IN1, GPIO.HIGH)
						GPIO.output(IN2, GPIO.LOW)
						time.sleep(0.01)
						GPIO.output(ENB, GPIO.HIGH)
						GPIO.output(IN3, GPIO.LOW)
						GPIO.output(IN4, GPIO.LOW)
						GPIO.output(ENA, GPIO.HIGH)
						GPIO.output(IN1, GPIO.LOW)
						GPIO.output(IN2, GPIO.LOW)
						
						
GPIO.cleanup()					


	
