function Respond = set_lamp_motor(lamp_type) %lamp type is UV or Visible 
% function to move the lamp motor to be in the UV or to be in the Visible 
s = serialport("COM10",250000,"Timeout",6000);
    if lamp_type == "UV"
    writeline(s,"set-lamp-moter-UV");%send to move the lamp motor to be in UV
    Respond = readline(s);% respond with "moved" or "failed to move"
    elseif lamp_type == "Visible"
    writeline(s,"set-lamp-moter-VI");%send to move the lamp motor to be in Visible
    Respond = readline(s);% respond with "moved" or "failed to move"
    else 
    %do nothing
    end
clear s
end 
