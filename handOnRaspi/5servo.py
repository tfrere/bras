from Tkinter import *
import time
from RIPO import PWM

for i = 0 ; i ++ ; i < 5:
	servo[i] = PWM.Servo()

servo[0] = GPIO.PWM(18, 100);
servo[1] = GPIO.PWM(18, 100);
servo[2] = GPIO.PWM(18, 100);
servo[3] = GPIO.PWM(18, 100);
servo[4] = GPIO.PWM(18, 100);

class App:

	def __init__(self, master):
		frame = Frame(master)
		frame.pack()
		scale = Scale(frame, from_=0, to=180, orient=HORIZONTAL, command=self.update)
		scale.grid(row=0)


	def update(self, angle):
		duty = float(angle) / 10.0 + 2.5
		pwm.ChangeDutyCycle(duty)

root = Tk()
root.wm_title('Servo Control')
app = App(root)

root.geometry("200x50+0+0")
root.mainloop()




