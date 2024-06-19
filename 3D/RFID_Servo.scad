/*
*******************************************
Objekt Info: RFID Servo Schloss

*******************************************
Version: 13.11.2022 khf
*******************************************
*/

//***************   Auswahl   *************

//Auswahl 0=alles, 1= Servohalter, 2=Schloss,  
        auswahl="0";

//***************   Libraries  ************

include </mylib/constants.scad>
use </mylib/shapes.scad>
use <sg90.scad>;

//*****************************************

//***************  Parameter   *************
$fn=60;
//*****************************************

//**************   Programm  **************


module elemente(){
$fs = 0.01;
rotate([90,0,0])
translate([5.5,29.4,-27])
sg90();

color("grey")
translate([11,-6.3,29.2])
rotate([90,0,180])
import("Gear.stl", convexity=3);
}


//Servo-Halter
module servohalter(){
difference(){
translate([0,18.5,27])
rotate([180,0,0])
cuboid([70,15,30], chamfer=1, $fn=24);
translate([-6,8,23])
cube([23,36,13]);
 
 //Servo Bohrlöcher   
translate([-8.5,27,29.5])
rotate([90,0,0])
cylinder(20,1,1,$fn=60);
    
 translate([-8.5,37,29.5])
rotate([90,30,0])
cylinder(20,2.5,2.5,$fn=6); 
    
translate([20,27,29.5])
rotate([90,0,0])
cylinder(20,1,1,$fn=60);
    
 translate([20,37,29.5])
rotate([90,30,0])
cylinder(20,2.5,2.5,$fn=6);   
translate([16,8,27.5])
cube([3,25,4]);    
}


//Grundplatte
difference(){
translate([-3,5,7])
rotate([90,0,0])
cuboid([110,13,50], chamfer=1, $fn=24);
translate([-50,-9.5,4.7])    
cube([150,16,15]); 
 //Bohrlöcher mit Senkungen
translate([47,25,-3])
cylinder(20,1.5,1.5,$fn=60);
 translate([47,25,11])
cylinder(5,1.5,4.5,$fn=60);    
    
translate([-53,25,-3])
cylinder(20,1.5,1.5,$fn=60); 
 translate([-53,25,11])
cylinder(5,1.5,4.5,$fn=60); 
    
translate([-53,-15,-3])
cylinder(20,1.5,1.5,$fn=60); 
 translate([-53,-15,11])
cylinder(5,1.5,4.5,$fn=60); 
    
translate([47,-15,-3])
cylinder(20,1.5,1.5,$fn=60); 
 translate([47,-15,11])
cylinder(5,1.5,4.5,$fn=60);   
}
}

//Schloss
module schloss(){
difference(){
translate([70,5,9.5])
rotate([90,0,0])
cuboid([30,18,50], chamfer=1, $fn=24);
translate([53,-10.5,3.7])    
cube([50,18,11]);
    
 translate([60,-15,-3])
cylinder(25,1.5,1.5,$fn=60); 
 translate([60,-15,16])
cylinder(5,1.5,4.5,$fn=60); 

translate([80,-15,-3])
cylinder(25,1.5,1.5,$fn=60); 
 translate([80,-15,16])
cylinder(5,1.5,4.5,$fn=60);     
 
  translate([60,25,-3])
cylinder(25,1.5,1.5,$fn=60); 
 translate([60,25,16])
cylinder(5,1.5,4.5,$fn=60); 

translate([80,25,-3])
cylinder(25,1.5,1.5,$fn=60); 
 translate([80,25,16])
cylinder(5,1.5,4.5,$fn=60); 
}   
}

module print(){
	if (auswahl == "0") {
		servohalter();
        schloss();
        elemente();
        color("red")
        translate([-137,-31,5])
        import("Rack.stl", convexity=3);
        
	} else if (auswahl == "1") {
		servohalter();
	} else if (auswahl == "2") {
		schloss();
	} 
}

print();
