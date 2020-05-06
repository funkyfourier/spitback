import("stdfaust.lib");

frequency = hslider("Frequency", 1, 0, 10, 0.1);
depth = maxDelay * hslider("Depth", 0.5, 0, 1, 0.01) : si.smoo;

origSR = 44100;

maxDelay = 512 * ma.SR / origSR : int;

voices = 4;

voice(i) = de.fdelay(4096, depth + depth * os.oscrs(frequency/(i+1)));

process = _,_ <: par(i, voices, voice(i));