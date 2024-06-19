function respond = set_filter_motor(filter_number) %filter_number is (F1,F2,F3,F4,F5,F6,F7,F8)
% function to send to set filter motor to be in  "filter_number" position 
s = serialport("COM10",250000,"Timeout",6000);
str = strcat("set-filtermoter-to-",filter_number);
writeline(s,str);
respond = readline(s);% respond with it is "moved" or "failed to move"
clear s
end
