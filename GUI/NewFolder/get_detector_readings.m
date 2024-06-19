function [Reference,Reference_Amplified,Sample,Sample_Amplified,Reference_gain_value,Sample_gain_value] = get_detector_readings()
% function to get the current detector readings ==>replay with refernce small signal - refernce amplified signal- sample small signal-sample amplified signal-current ref digital pot gain - current sample digital pot gain like 1-9-2-18-9-20
s = serialport("COM10",250000, "Timeout", 6000);
writeline(s,"get-det-readings");% send to get the current detector readings
values = readline(s);
values = split(values,"-");
refernce_small_signal =values(1,1);
Reference = str2double(refernce_small_signal); % convert string to numeric value
refernce_amplified_signal=values(2,1);
Reference_Amplified= str2double(refernce_amplified_signal);
sample_small_signal =values(3,1);
Sample = str2double(sample_small_signal);
sample_amplified_signal=values(4,1);
Sample_Amplified = str2double(sample_amplified_signal);
current_ref_digital_pot_gain =values(5,1);
Reference_gain_value= str2double(current_ref_digital_pot_gain);
current_sample_digital_pot_gain =values(6,1);
Sample_gain_value = str2double(current_sample_digital_pot_gain);
clear s
end