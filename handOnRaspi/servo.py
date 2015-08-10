from Tkinter import *
import RPi.GPIO as GPIO
import time


GPIO.setmode(GPIO.BCM)
#GPIO.setup(18, GPIO.OUT)
#pwm = GPIO.PWM(18, 100)

#GPIO.setup(17, GPIO.OUT)
#pwm2 = GPIO.PWM(17, 100)

GPIO.setup(16, GPIO.OUT)
pwm3 = GPIO.PWM(16, 100)

GPIO.setup(19, GPIO.OUT)
pwm4 = GPIO.PWM(19, 100)

GPIO.setup(20, GPIO.OUT)
pwm5 = GPIO.PWM(20, 100)

#pwm.start(10)
#pwm2.start(10)
pwm3.start(10)
pwm4.start(10)
pwm5.start(10)


class App:

	def __init__(self, master, pwm):
		frame = Frame(master)
		frame.pack()
		self.pwm = pwm
		scale = Scale(frame, from_=1, to=180,
					orient=HORIZONTAL, command=self.update)
		scale.grid(row=0)

	def update(self, angle):
		duty = float(angle) / 10.0 + 2.5
		self.pwm.ChangeDutyCycle(duty)

root = Tk()
root.wm_title('Servo Control')
#app = App(root, pwm)
#app2 = App(root, pwm2)
app3 = App(root, pwm3)
app4 = App(root, pwm4)
app5 = App(root, pwm5)
root.geometry("200x250+0+0")

root.mainloop()

GPIO.cleanup()
