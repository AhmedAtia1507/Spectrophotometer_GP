
function respond = set_sample_gain(gain_value)
%function to send to set sample gain 
s = serialport("COM10",250000,"Timeout",6000);
str1 = string(gain_value);
str2 = strcat("set-sample-newgain-to-",str1);
writeline(s,str2);
respond = readline(s);%reply with "applied" or "not applied"
clear s
end 