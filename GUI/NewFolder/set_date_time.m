function respond = set_date_time(date,time)
%function to send to set date and time 
s = serialport("COM10",250000,"Timeout",6000);
%str1 = string(date);
str2 = strcat("set-time-",date," ",time);
writeline(s,str2);
respond = readline(s);%respond when done with "time update success" or "time update failed"
clear s
end 