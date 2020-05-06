import("stdfaust.lib");
freq = hslider("freq",100,50,5000,1);
gain = hslider("gain",0,-48,48,0.1);

process = _ : fi.lowshelf(3, gain, freq) : _;