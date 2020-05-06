import("stdfaust.lib");

freq   = hslider("Speed", 0.5, 0, 10, 0.01);
fb     = hslider("Feedback", 0, -0.999, 0.999, 0.001);
dflange = 0.001 * ma.SR * hslider("Width", 10, 0, 20, 0.001);

curdel1 = dflange+dflange*(1 + os.oscrs(freq))/2;
curdel2 =  dflange+dflange*(1 + os.oscrc(freq))/2;

process = pf.flanger_stereo(4096,curdel1,curdel2,1,fb,0);