import serial
import tkinter as tk
from serial_cmd import Serial_cmd
s_cmd = Serial_cmd()
window = tk.Tk()
greeting = tk.Label(text="LINE FOLLOWING ROBOT")
greeting.pack()
def runClicked():
    s_cmd.write("R")
def stopClicked():
    s_cmd.write("S")
runButton = tk.Button(
    text="Run Robot",
    width=25,
    height=5,
    bg="blue",
    fg="yellow",
    command = runClicked
)

stopButton = tk.Button(
    text="Stop Robot",
    width=25,
    height=5,
    bg="red",
    fg="yellow",
    command = stopClicked
)
runButton.pack()
stopButton.pack()
window.mainloop()


