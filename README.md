![image missing](other/clang.png)  
A simple line follower project of mine.
Consists of:
 * ATmega 328P  
 * L298 dual H-bridge  
 * 6x QRE1113GR optotransistors  
 * 2x pololu clone 12V 1200RPM motors  
 * step down 5V converter  
 * 7,4V Li-Ion battery  
 * couple resistors, LEDs and other passive components  

Programmed in Arduino.  
Uses PID loop and a simple algorithm to find center of line (using weighed average).  
Follows black line on white background.  

Video of device test  
[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/-RvJ9BSbzys/0.jpg)](https://www.youtube.com/watch?v=-RvJ9BSbzys) 

Before mounting DC motors:  
![image missing](making%20of/before-mounting-motors.jpg)  
![image missing](making%20of/before-mounting-motors-debug.jpg)  

Finding voltage/speed characteristic using optical speed measurement:  
![image missing](making%20of/testing.jpg)  
![image missing](making%20of/testing2.jpg)  
![image missing](making%20of/spreadsheet2.jpg)  
![image missing](making%20of/spreadsheet.jpg)  


