function respond = set_gratingmotor_to_right(No_of_steps)
% function to send to move grating motor to right specific number of steps
s = serialport("COM10",250000,"Timeout",6000);
str1 = string(No_of_steps);
str2 = strcat("set-gratingmoter-to-R-",str1);
writeline(s,str2);%send the grating motor "No_of_steps" to the right
respond = readline(s);%respond with  "moved" or "failed to move"
clear s
end