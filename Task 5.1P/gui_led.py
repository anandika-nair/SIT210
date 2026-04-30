from tkinter import*  # Import everything from tkinter for GUI creation
import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library to control pins

# Set GPIO numbering mode to BCM (this uses the pin numbers from the chip, not board layout)
GPIO.setmode(GPIO.BCM)

# Set up GPIO pins 17, 27, and 22 as output pins
GPIO.setup(17, GPIO.OUT)
GPIO.setup(27, GPIO.OUT)
GPIO.setup(22, GPIO.OUT)

# This function runs whenever a radio button is selected
def select_room():
    # Check Living Room checkbox
    if living_var.get() == 1:   # If checked
        GPIO.output(17, True)   # Turn ON LED
    else:
        GPIO.output(17, False)  # Turn OFF LED

    # Check Bathroom checkbox
    if bathroom_var.get() == 1:
        GPIO.output(27, True)
    else:
        GPIO.output(27, False)

    # Check Closet checkbox
    if closet_var.get() == 1:
        GPIO.output(22, True)
    else:
        GPIO.output(22, False)

# Function to turn all LEDs ON
def all_on():
    living_var.set(1)           # Set all checkboxes to ON
    bathroom_var.set(1)
    closet_var.set(1)
    select_room()               # Update LEDs

# Function to turn all LEDs OFF
def all_off():
    living_var.set(0)           # Set all checkboxes to OFF
    bathroom_var.set(0)
    closet_var.set(0)
    select_room()               # Update LEDs

# Function to safely exit the program
def exit_program():
    all_off()                   # Turn OFF all LEDs
    GPIO.cleanup()              # Reset GPIO pins
    root.destroy()              # Close GUI window


root = Tk() #Creates main application window

Label(root, text="Select Room").pack() #Adds a label at the top of the window

# Variables to store checkbox values (0 = OFF, 1 = ON)
living_var = IntVar()
bathroom_var = IntVar()
closet_var = IntVar()

# Create checkboxes for each room
Checkbutton(root, text="Living Room", variable=living_var, command=select_room).pack()
Checkbutton(root, text="Bathroom", variable=bathroom_var, command=select_room).pack()
Checkbutton(root, text="Closet", variable=closet_var, command=select_room).pack()

# Buttons for controlling all LEDs
Button(root, text="Turn ALL ON", command=all_on).pack()
Button(root, text="Turn ALL OFF", command=all_off).pack(
    
Button(root, text="Exit", command=root.destroy).pack() #Adding an exit button to close the program

root.mainloop() # Start the GUI loop

