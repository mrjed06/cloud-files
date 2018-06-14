# cloud-files
Lighting effects for individually addressable RGB LED strips controlled with an Arduino. Utilizes the Adafruit Neopixel Library for Arduino single-wire based LED pixels and strips.

#Code Summary
Code consists of separate functions that are called to display unique lighting effects. The void loop() searches for strings sent via bluetooth and triggers an effect when one is detected.

#Color Customization Guide:
Cabin Lighting: Change the cabin lighting color by modifying the three inputs of the setGlobalRGB(Ro,Go,Bo) function called at the end of  void Setup(). The Ro, Go, and Bo inputs of the setGlobalRGB(Ro,Go,Bo) takes values 0-255 and correspond to the actual r, g, and b values that define the cabin light color.

Crossfade Light Effect Colors: Change the two colors blended in the Crossfade effect by  modifying the six inputs of the crossFade(ro,go,bo,rf,gf,bf) function/(s) called within void loop(). The ro, go, and bo inputs correspond to the r, g, and b values of the first color and the rf, gf, and bf inputs correspond to the r, g, and b values of the second color. All six inputs take values 0-255.

#List of Light Effects:
ON(); turns
-ambient lights ON
-ambient lights OFF
-ambient lights to level 1 intensity
-ambient lights to level 2 intensity
-(2X) two color crossFade
