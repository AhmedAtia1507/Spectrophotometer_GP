function respond = set_ref_gain(gain_value)
%function to send to set reference gain 
s = serialport("COM10",250000,"Timeout",6000);
str1 = string(gain_value);
str2 = strcat("set-ref-newgain-to-",str1);
writeline(s,str2);
respond = readline(s);%reply with "applied" or "not applied"
clear s
end 