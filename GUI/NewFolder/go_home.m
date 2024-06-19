function Current_step = go_home(motor_type)% motor_type (lamp,grating,filter)
% function to send to go to home position 
s = serialport("COM10",250000, "Timeout", 6000);
if motor_type == "lamp"
   writeline(s,"set-lamp-motor-home ");% send lamp motor to home
   current_step = readline(s);%reply with the current step after executing the go to home function like "0\n"
elseif motor_type == "grating"
   writeline(s,"set-grating-motor-home");% send grating motor to home
   current_step = readline(s);
elseif motor_type == "filter"
   writeline(s,"set-filter-motor-home ");% send filter motor to home
   current_step = readline(s); 
else
    % do nothing
end
Current_step = str2double(current_step);
clear s
end