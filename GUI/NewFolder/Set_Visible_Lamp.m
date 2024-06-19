function  current_status = Set_Visible_Lamp(selection)% Selection is ON or OFF
% function to set visible lamp on/off and reply with the current status after
% set it 
s = serialport("COM10",250000, "Timeout", 6000);
if selection == "ON"
    writeline(s,"set-vi-on");% send to set vi lamp on
elseif selection == "OFF"
    writeline(s,"set-vi-off");% send to set vi lamp off
else
    %do nothing
end
current_status = readline(s);% reply with the status of the vi lamp after set it 
clear s
end