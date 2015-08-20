from Tkinter import *
import RPi.GPIO as GPIO
import time


GPIO.setmode(GPIO.BCM)

GPIO.setup(18, GPIO.OUT)
pwm3 = GPIO.PWM(18, 100)

pwm.start(10)


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
app = App(root, pwm)
root.geometry("200x250+0+0")

root.mainloop()

GPIO.cleanup()
