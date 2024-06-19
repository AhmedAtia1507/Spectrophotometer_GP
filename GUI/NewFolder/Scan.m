function values3 = Scan(Start_Wavelength,Step_Wavelength,Stop_Wavelength)
No_Of_Steps = (Stop_Wavelength - Start_Wavelenght)/ Step_Wavelength;
Start_WL = string(Start_Wavelength);
Step_WL = string(Step_Wavelength);
Stop_WL = string(Stop_Wavelength);
s = serialport("COM10",250000,"Timeout",6000);
str = strcat("Scan"," ",Start_WL," ",Stop_WL," ",Step_WL);
writeline(s,str);
%values = read(s,No_Of_Steps,"string");
values1 = zeros(1,No_Of_Steps);
for i=1:No_Of_Steps
    values1(1,i)=readline(s);
end
values2 = zeros(No_Of_Steps,2);
for loop_index = 1:No_Of_Steps
    Values = split(values1(1,loop_index)," ");
    %values1(1,loop_index) = values1(1,loop_index).';
    %values2(loop_index,1)= values1(1,loop_index);
    values2(loop_index,1) = Values(1,1);
    values2(loop_index,2) = Values(2,1);
end

for loop_index_2 = 1:No_Of_Steps
    values2(loop_index_2,1)= str2double(values2(loop_index_2,1));
    values2(loop_index_2,2)= str2double(values2(loop_index_2,2));
    
end
values3 = zeros(No_Of_Steps,4);
for j = 1:No_Of_Steps
    values3(j,1) = values2(j,1);% intensity of reference
    values3(j,2) = values2(j,2);% intensity of sample
    values3(j,3) = log10(values3(j,1)/values3(j,2));%calculation of absorption
    values3(j,4) = log10(values3(j,2)/values3(j,1));%calculation of transmission 
    
end
end

    