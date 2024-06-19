function [Pos_12v,Neg_12v,Supply_5v,Supply_3v,Supply_12v] = get_voltages()
% function to get supplies voltages
s = serialport("COM10",250000, "Timeout", 6000);
writeline(s,"get-voltages");% send to get the supplies voltages
values = readline(s);% reply with the values of the voltages
values = split(values," ");
pos_12v =values(1,1);%+12v (+12 of dc to dc converter)
Pos_12v = str2double(pos_12v); % convert string to numeric value
neg_12v =values(2,1);%-12v (-12 of dc to dc converter)
Neg_12v = str2double(neg_12v);
supply_5v =values(3,1);%5v (supply 5v)
Supply_5v = str2double(supply_5v);
supply_3v =values(4,1);%3.3v (supply 3.3v)
Supply_3v = str2double(supply_3v);
supply_12v =values(5,1);%12v (supply 12v of the lamp)
Supply_12v= str2double(supply_12v);
clear s
end