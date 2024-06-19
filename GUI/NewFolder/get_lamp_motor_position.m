function Current_Position = get_lamp_motor_position()
%function to send to get the lamp motor position
s = serialport("COM10",250000,"Timeout",6000);
writeline(s,"get-lamp-moter-position");%send to get lamp motor position
Current_Position  = readline(s);% respond with it is on "UV Lamp" or "VI Lamp"
clear s
end 