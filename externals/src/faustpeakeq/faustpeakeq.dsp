import("stdfaust.lib");
freqMid = hslider("freqMid",2200,400,3500,0.1);
gainMid = hslider("gainMid",0,-48,48,0.1);
qMid = hslider("qMid",50,0,3000,0.1);

process = _ : fi.peak_eq(gainMid, freqMid, qMid) : _;