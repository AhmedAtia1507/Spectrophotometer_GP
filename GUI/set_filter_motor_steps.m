function reply = set_filter_motor_steps(no_of_steps)
% function to move the filter motor to specific number of steps (input to
% the function)
s = serialport("COM10",115200, "Timeout", 10000);
%configureTerminator(s,"\n");
str = strcat("movto-", string(no_of_steps));
writeline(s,str);
reply = readline(s);
clear s
end


