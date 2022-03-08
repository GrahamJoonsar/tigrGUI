# tigrGUI
A offshoot of tigr, an amazing and compact graphics library, but with added classes for objects you would typically find in a program with a gui.

Original repository:
https://github.com/erkkah/tigr

## The Components:

Each component has a draw and update method that must be called in the main loop of your program for the component to work properly.

### Button
The button class is, shocker, a button. The button has a text label on it and it changes color when the mouse is over it. The action of the button is executed whenever the mouse is on top of the button and the left mouse button is held. When this happens, the function specified by the user is called. To set a function for the button, call `setFunction` on the button and pass in a lambda that returns void and takes in a vector of void pointers. This way, there can be variable arguments of different types. Inside of the function use static cast to safely interact with your void pointers.

### Text Area
The text area class is a text box that the user can type into. Right now it is a fixed size, but I will add a scrollbar later on. The user can only have one text area selected at a time, and if a text area is selected, all keyboard input from the user will be added to the text area. the TextArea class has a method called `getText` that returns a std::string of whatever is in the text field at the time.

### Check Box
The check box is a toggleable button that has two states, on or off. The state of the check box can be detected with the `getVal` method, which returns true if the check box is toggled on.

### Slider
The slider is a horizontal component that allows the user to select from a range of values at a specified increment. The user drags a knob on the slider to select a value, and that value is read with the `getVal` method.
