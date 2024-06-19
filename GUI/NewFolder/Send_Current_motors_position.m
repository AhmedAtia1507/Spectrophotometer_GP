function [Lamp_motor_steps,Grating_motor_steps,Filter_motor_steps,Current_wavelength]= Send_Current_motors_position()
%function to get the current motors position and the current
%wavelength
s = serialport("COM10",250000, "Timeout", 6000);
writeline(s,"get-motors-steps");% send to get the current motors position and the current wavelength 
positions = readline(s);% reply with "lampmotersteps-gratingmotorsteps-filtermotorsteps-currentwavelength"
positions = split(positions,"-");
lamp_motor_steps = positions(1,1);
Lamp_motor_steps = str2double(lamp_motor_steps);
grating_motor_steps = positions(2,1);
Grating_motor_steps = str2double(grating_motor_steps);
filter_motor_steps =  positions(3,1);
Filter_motor_steps = str2double(filter_motor_steps);
current_wavelength =  positions(4,1);
Current_wavelength = str2double(current_wavelength);
clear s
end