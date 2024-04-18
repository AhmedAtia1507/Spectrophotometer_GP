function status = get_lamp_status(lamp_type) % lamp type is uv or vi
% function to get the status of the lamp
s = serialport("COM10",115200, "Timeout", 6000);
%configureTerminator(s,"\n");
if lamp_type == "UV"
    writeline(s,"get-uv");% send to get the status of the uv lamp
    status = readline(s);% reply with the status of the uv lamp it is on/off
elseif lamp_type == "Visible"
    writeline(s,"get-vi");% send to get the status of the vi lamp
    status = readline(s);% reply with the status of the vi lamp it is on/off
else
    % do nothing
end
clear s
end
