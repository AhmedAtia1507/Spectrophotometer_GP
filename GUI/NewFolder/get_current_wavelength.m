function Current_Wavelength = get_current_wavelength()
%function to send to get the current wavelength 
s = serialport("COM10",250000,"Timeout",6000);
writeline(s,"get-current-wav");%send to get the current wavelength
current_wavelength = readline(s);%respond with the current wavelength just a number like "1100\n"
Current_Wavelength = str2double(current_wavelength);
clear s
end 