import serial
import time
import tkinter as tk

# Creating a gui widnow
window = tk.Tk()
window.configure(background = "white smoke")
window.geometry("320x100")
window.title("MOTOR CTRL - PYTHON GUI")

# connecting to the right COM port
megaBoard = serial.Serial('COM7', 9600)

def motor_control():
    """Defining all the commands and buttons that are on the GUI"""
    mod_val = 0

    print("MOTOR CONTROL PROGRAM")
    def starting():
        # Sending an R to start the motor
        print("Start driving")
        megaBoard.write(b'R')

    def stopping():
        # Sending an S to stop the motor
        print("Stop driving")
        megaBoard.write(b'S')

    def quit():
        # Sending a Q to quit the program
        print("\n** END OF PROGRAM**")
        megaBoard.write(b'Q')
        megaBoard.close()
        window.destroy()

    def set_mod_val():
        # Sending a mod value to the Arduino
        print("Set mod value")
        megaBoard.write(b'M')
        megaBoard.write(mod_val)

    # Defining all the widgets
    start_b = tk.Button(window, text = "START", command = starting, bg= "pale green", fg="dark slate gray", font=("Lucida Console", 20))
    stop_b = tk.Button(window, text = "STOP", command = stopping, bg= "tomato", fg="dark slate gray", font=("Lucida Console", 20))
    quit_b = tk.Button(window, text = "QUIT", command = quit, bg= "orchid", fg="dark slate gray", font=("Lucida Console", 20))
    mod_label = tk.Label(window, text='Mod value:', font=("Lucida Console", 13))
    mod_value = tk.Text(window, height = 1, width = 10)
    send_b = tk.Button(window, text="Send", command = set_mod_val, bg= "gray", fg="dark slate gray", font=("Lucida Console", 13))

    # Positioning all the buttons
    start_b.grid(row=1, column=0, padx=5, pady=10)
    stop_b.grid(row=1, column=1, padx=5, pady=10)
    quit_b.grid(row=1, column=2, padx=5, pady=10)
    mod_label.grid(row=2, column=0, padx=5)
    mod_value.grid(row=2, column=1)
    send_b.grid(row=2, column=2)

    window.mainloop()

time.sleep(2)
motor_control()
