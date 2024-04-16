function readings = snddet()

    %refernce small signal - refernce amplified signal- sample small signal-sample amplified signal-current digital pot gain like 1-9-2-18-9
    stm = serialport("COM4", 9600);
    readings = readline(stm);
    readings = readline(stm);
    %split the readings into separate 5x1 strings
    readings = split(readings, "-");
     ref = readings(1,1);
     ref_amp = readings(2,1);
     sample = readings(3,1);
     sample_amp = readings(4,1);
     gain = readings(5,1);
    delete(stm);
end