function respond = set_grating_motor(value_of_wavelength)
%function to send to move grating motor to specific wavelength
%(value_of_wavelength)
s = serialport("COM10",250000,"Timeout",6000);
str1 = string(value_of_wavelength);
str2 = strcat("set-gratingmoter-to-WL-",str1);
writeline(s,str2);%send the grating moter to the "value_of_wavelength"in nm position 
respond = readline(s);% respond with "moved" or "failed to move"
clear s
end 