import("filters.lib");
import("delays.lib");
import("basics.lib");
import("maths.lib");

origSR = 44100;

lpcf(delayTime,feedback,damp) = (+:delay(2048,delayTime))~ (*(1-damp) : (+ ~ *(damp)) : *(feedback));

cTuning = (1116,1188,1277,1356,1422,1491,1557,1617);
combtuningL(i, spread) = take(i+1,cTuning)*SR/origSR : int : +(spread);
aTuning = (556,441,341,225);
allpasstuningL(i) = take(i+1,aTuning)*SR/origSR : int;

scaleroom = 0.28;
offsetroom = 0.7;
allpassfeed = 0.5;
scaledamp = 0.85;
fixedgain = 0.1;

monoFreeverb(fb1, damp, spread) = _ <: par(i,8,lpcf(combtuningL(i, spread),fb1,damp)) :> 
seq(i,4,allpass_comb(1024,allpasstuningL(i),-allpassfeed));

combfeed = hslider("RoomSize",0.5,0,1,0.01)*scaleroom*SR/origSR + offsetroom;
damping = hslider("Damping",0.5,0,1,0.01)*scaledamp*SR/origSR;
spatSpread = hslider("Spatial Spread",0.5,0,1,0.01)*46*SR/origSR : int;

process = *(fixedgain),*(fixedgain) : + <: monoFreeverb(combfeed, damping, 0), monoFreeverb(combfeed, damping, spatSpread);