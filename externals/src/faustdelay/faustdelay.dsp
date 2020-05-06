import("stdfaust.lib");

maxDelay = 2.0 * ma.SR : int;

delaySamples = hslider("Delay", 100, 0, 1000, 1) : si.smoo * 0.001 * ma.SR : int;
feedbackRatio = hslider("Feedback", 0.7, 0, 0.9, 0.01);
wet = hslider("Wet", 1, 0, 1, 0.01);

feedback = *(feedbackRatio);

delay(samples) = (+ : feedback) ~ de.delay(maxDelay, samples);

delayProcess(samples) = delay(samples)*wet;

delayLineLeft = _<:_,(de.delay(maxDelay, delaySamples) : delayProcess(delaySamples*2));
delayLineRight = _<:(de.delay(maxDelay, delaySamples*2) : delayProcess(delaySamples*2)),_;

process = _,_ : delayLineLeft, delayLineRight : _,_,_,_;