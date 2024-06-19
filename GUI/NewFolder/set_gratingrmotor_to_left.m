function respond = set_gratingrmotor_to_left(No_of_steps)
% function to send to move grating motor to left specific number of steps
s = serialport("COM10",250000,"Timeout",6000);
str1 = string(No_of_steps);
str2 = strcat("set-gratingmoter-to-L-",str1);
writeline(s,str2);%send the grating moter "No_of_steps" to the left
respond = readline(s);%respond with "moved" or "failed to move"
clear s
end