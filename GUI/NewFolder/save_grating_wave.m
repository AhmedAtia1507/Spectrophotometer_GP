function  respond = save_grating_wave(no_of_steps)
%function to send to save the grating motor wave(no_of_steps) in the eeprom
s = serialport("COM10",250000,"Timeout",6000);
str1 = string(no_of_steps);
str2 = strcat("save-grating-wave-",str1);
writeline(s,str2);
respond = readline(s);%respond with "saved" of "failed to save"
clear s
end