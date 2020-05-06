import("stdfaust.lib");
freq = hslider("freq",100,50,5000,1);
gain = hslider("gain",0,-480,480,0.1);

process = _ : fi.highshelf(3, gain, freq) : _;