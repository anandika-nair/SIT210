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
    # Check which room is selected using the StringVar "room"
  
     if room.get() == "living":
        GPIO.output(17,True) # Turn ON pin 17 
        GPIO.output(27,False)  # Turn OFF other pins
        GPIO.output(22,False)
     elif room.get() == "bathroom":
          GPIO.output(17,False) 
          GPIO.output(27,True) # Turn ON pin 27 
          GPIO.output(22,False) 
     elif room.get() == "closet":
          GPIO.output(17,False) 
          GPIO.output(27,False)
          GPIO.output(22,True)  # Turn ON pin 22
       # If none is selected
     else:
        GPIO.output(17,False) 
        GPIO.output(27,False)
        GPIO.output(22, False)

root = Tk() #Creates main application window

Label(root, text="Select Room").pack() #Adds a label at the top of the window

room = StringVar() # Create a variable to store the selected radio button value and will hold strings like "living", "bathroom", etc.

# Create radio buttons for each room
Radiobutton(root, text="Living Room", variable=room, value="living", command=select_room).pack()
Radiobutton(root, text="Bathroom", variable=room, value="bathroom", command=select_room).pack()
Radiobutton(root, text="Closet", variable=room, value="closet", command=select_room).pack()

Button(root, text="Exit", command=root.destroy).pack() #Adding an exit button to close the program

root.mainloop() # Start the GUI loop

