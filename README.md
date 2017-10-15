# FRC 4461 LED Panel Project

This project uses an Arduino board to control a 16x16 RGB LED panel. Each LED on the panel is individually addressable by setting the corresponding value in the `leds` array in the code.

## Getting started

1. Go to arduino.cc and download the Arduino IDE
2. Clone this repository and open it in the Arduino IDE
3. Plug the Arduino board in via USB
4. From the Arduino IDE, choose "Tools" -> "Board" -> "Arduino / Genuino Mega or Mega 2560". This is the board I'll be supplying you with, but if you're using a different board choose that.
5. Go to "Sketch" -> "Upload" to load the code on to the Arduino
6. Connect the provided 5v power adapter to the positive and negative rails of the breadboard (these are the long horizontal lines).
7. Connect the capacitor between the positive and negative rails. Make sure you plug this in with negative and positive on the correct side. Search the internet for which side is positive if needed. Doing this incorrectly will blow up the capicitor and potentially damage the power supply or board.
8. Connect the 220 ohm resister between two columns in the breadboard.
9. Connect the "DIN" from the LED panel to one of those columns.
10. Connect pin 5 from the Arduino to the other column.
11. Connect the positive and negative for the LED panel to the rail.
12. Connect a ground pin from the Arduino to the negative rail on the breadboard.
13. Plug the arduino in via USB.
14. Plug the 5v power supply in for the panel.
15. **If anything seems off, immediately unplug the power**

## Modifying the code

The code is intended to be a proof of concept and not a complete solution. There are definitely improvements that can be made. To start with, the code is only working with a 2 color image (black and orange). You can do better than this by hand crafting an image or writing routines to pick other colors. You should come up with an idea for what you want it to do and then try to tackle making the display do it.

### Key code features

The `index` function might be the most critical function to understand. The `index` function takes an X and Y coordinate and returns the index in to the `leds` array that corresponds to that position. This is important because the panel is setup in a zig zagging pattern so the lights aren't all in order from left to right. Note that the `index` function considers the top-left of the panel to be 0, 0. This is pretty normal for displays, but is different that you'll typically think of coordinates in math.

`renderBitmapFromProgmem` is another important function. This function will render a 2 color bitmap where each bit tells whether to turn a pixel on or off. The Arduino doesn't have a huge amount of memory and this allows us to store a full 256 pixels in only 32 bytes. The downside to bitmaps is that you only have one color. An alternative that you could do is to define a palette that an image can refer to. Look up the FastLED documentation and sample code for examples on using a palette. The other important thing this function does is read from progmem. The Arduino has both ram and program memory which can be used to read or store bits. Unfortunately, ram is more expensive so it tends to be much more limited than progmem. As a result, we store the image in progmem (if you look at the definition of `Smile` you'll see it has `PROGMEM` at the end). The downside is that you can't just read or write to a value in progmem, instead you have to call methods like `pgm_read_byte_near` to get the value. This means if you're going to be using ram instead you'll need to modify the function or create another version.

## Project goals

The RoboRIO and the Arduino both support a serial bus called SPI. Your goal is to write some SPI code to communicate from the RoboRIO to the Arduino and have the Arduino display some stat. An example of this would be to fill the grid from the bottom up as a bar graph of how fast you're going. Once you have that, think of some fun things you can do. For example, you could use the accelerometer to detect when you hit another robot or wall and display a frowny face.