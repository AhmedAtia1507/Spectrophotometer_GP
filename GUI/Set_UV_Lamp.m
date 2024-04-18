function  current_status = Set_UV_Lamp(selection)% Selection is ON or OFF
% function to set uv lamp on/off and reply with the current status after
% set it 

s = serialport("COM10",115200, "Timeout", 6000);
%configureTerminator(s,"\n");
if selection == "ON"
    writeline(s,"set-uv-on");% send to set uv lamp on
   
       
    
elseif selection == "OFF"
    writeline(s,"set-uv-off");% send to set uv lamp off
   
else
    % do nothing
end
current_status = readline(s);%  reply with the status of the uv lamp after set it 
clear s
end


    




