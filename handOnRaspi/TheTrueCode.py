from Tkinter import *
import RPi.GPIO as GPIO
import time


GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)
pwm = GPIO.PWM(18, 100)

GPIO.setup(17, GPIO.OUT)
pwm2 = GPIO.PWM(17, 100)

GPIO.setup(16, GPIO.OUT)
pwm3 = GPIO.PWM(16, 100)

GPIO.setup(19, GPIO.OUT)
pwm4 = GPIO.PWM(19, 100)

GPIO.setup(20, GPIO.OUT)
pwm5 = GPIO.PWM(20, 100)

pwm.start(10)
pwm2.start(10)
pwm3.start(10)
pwm4.start(10)
pwm5.start(10)

sleep(1)
pwm.start(100)
pwm2.start(100)
pwm3.start(100)
pwm4.start(100)
pwm5.start(100)

GPIO.cleanup()


