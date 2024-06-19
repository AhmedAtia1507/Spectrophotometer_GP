function [Date,Time] = get_date_time()
% function to send to get date and time 
s = serialport("COM10",250000,"Timeout",6000);
writeline(s,get-time);
values = readline(s);
values = split(values," ");
Date=values(1,1);
Time=values(2,1);
clear s
end