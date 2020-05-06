## Spitback

**Spitback** is a PD patch with some externals intended for use with [libpd](https://github.com/libpd/libpd). It consists of a simple wavetable synth/sampler, a simple drum player, and eight stereo effects. The aim is to make something proportionally powerful to current smartphones, and ideal for making audio and music apps for mobile platforms.

Spitback is the audio backend for Android sequencer app [Sputter](https://play.google.com/store/apps/details?id=info.casualcomputing.sputter), currently in beta phase.

### Getting started

Download the patch and open `src/main.pd`. Open [samplercontrolsui testsampleplayer] or [drumcontrolsui testdrumplayer]. In [samplercontrolsui testsampleplayer] click the bang labeled "open wave file". A rudimentary note triggering tool is provided, but you might want to connect a MIDI keyboard or sequencer. In [drumcontrolsui testdrumplayer] you can load a wave into each of the 16 drum slots. There is also a trigger for each drum slot.

Binaries of the externals are provided for Linux 64-bit, Mac and Windows 64-bit. Pure Data should find them when you open the patch if you are on one of these platforms. If not, please consult the documentation of [pd-lib-builder](https://github.com/pure-data/pd-lib-builder). 

### Using on mobile or other platforms

It should work on any platform including Android and iOS, but the externals will of course have to be compiled for the target platform. For more information regarding this, please see [pd-for-android's documentation](https://github.com/libpd/pd-for-android/wiki/Building-and-packaging-externals-for-Android) and [pd-for-ios's documentation](https://github.com/libpd/pd-for-ios/wiki/ios). I cannot provide any further information on that at this time, but might expand on this in the future.

### Future outlook

Spitback is currently being used in Android sequencer app [Sputter](https://play.google.com/store/apps/details?id=infocasualcomputing.sputter). By open sourcing the audio backend, I am hoping to:

* Give something back to the community in which I have found most valuable tools and knowledge to build my app. Without these, the would be no Sputter.
* Make it easier for others to build sequencer and music apps for mobile platforms.
* Build connections with other developers.
* Make it possible for others to build tools related to Sputter for either mobile or desktop, for example song players, instrument preset editors or effects and other features.

Things which could be improved: 

* Performance can probably be better. Is it cheaper to send floats to and from libpd instead of strings? 
* There should be a "swing" feature. Can we still use [metro]?
* Could waves be read with [soundfiler] instead of writing to an array from the libpd host?

## Usage with LibPD

#### Your libpd host may send these messages to Spitback

>addsamplertrack [slot]

This is for adding a sampler/synth track. The [slot] must be a unique integer. The sampler/synth can later be adressed using track id `sound[slot]`.

>adddrumtrack [slot]

This is for adding a drum track. The [slot] must be a unique integer. The drum machine can later be adressed using track id `drums[slot]`.

>[track-id]-noteon

To turn a note on, send a list to Spitback with this message as the first parameter. The second parameter should be the MIDI note value, and the third should be the velocity between 0 and 127. The `track-id` is `sound[slot]` for sampler/synth tracks and `drums[slot]` for drum tracks.

When this is done it will send a `libpdhost-sustainednoteon` message to the libpd host.

>[track-id]-noteoff

To turn a note off, send a list to Spitback with this message as the first parameter. The second parameter should be the MIDI note value.

When this is done it will send a `libpdhost-sustainednoteoff` message to the libpd host.

>bpm

Send a float to receiver `bpm` to set beats per minute.

#### In your libpd host, you may subscribe to these messages from Spitback

>libpdhost-tick

This is just a float which is sent to the host on each 16th of a beat. You'll want to update your sequencer logic when this happens.

>libpdhost-sustainednoteon

Every time a note is turned on, Spitback sends this message. The argument is a list, of which the first value says which note has been turned on. This is useful for keeping track of which notes are currently playing.

>libpdhost-sustainednoteoff

Opposite of `libpdhost-sustainednoteon`.

>libpdhost-onpause

This is a message saying that Spitback is done with cutting master volume and turning off all notes. This happens when it receives an `onpause` message. 

#### Loading waveforms

##### Sampler/synth tracks

1. Send a float with the sample rate of the waveform to `[track-id]-samplerate`
2. Send a float with the length of the waveform to `[track-id]-resize`
3. Write the float array to `[track-id]-tmp`
4. Send a float with the length of the waveform to `[track-id]-makeguardpoints`

##### Drum tracks

1. Send a float with the sample rate of the waveform to `[track-id]-samplerate`
2. Send a float with the length of the waveform to `[track-id]-resize`
3. Write the float array to `[track-id]-drum-[drum slot (between 0 and 15)]`

#### Removing tracks

Send a `clear` message to receiver `pd-subpatchsampler[slot]` for sampler/synth tracks or to `pd-subpatchdrum[slot]` for drum tracks.

#### Parameter ids

To get and set parameters, you will use these unique id's:

##### Track parameters

* volume
* pan
* mute

##### Sampler/synth parameters

* samplerate
* rootnote
* finetune
* samplestart
* sampleend
* samplelength
* loopstart
* loopend
* loopon
* attack
* decay
* sustain
* release
* lforate
* lfodepth
* lfoconnection
* filtercutoff
* filterselect
* filterattack
* filterdecay
* filtersustain
* filterrelease

##### Drum parameters

* samplestart
* sampleend
* samplelength
* volume
* finetune
* samplerate

##### Effect parameters

* rev-enable
* rev-damp
* rev-roomsize
* rev-spread
* rev-wet
* del-enable
* del-delay
* del-feedback
* del-wet
* del-spread
* flg-enable
* flg-freq
* flg-width
* flg-feedback
* flg-wet
* chorus-enable
* chorus-depth
* chorus-speed
* chorus-spread
* chorus-wet
* fxfilter-enable
* fxfilter-mode
* fxfilter-freq
* fxfilter-q
* 3eq-enable
* 3eq-lowgain
* 3eq-midgain
* 3eq-midfreq
* 3eq-midbw
* 3eq-highgain
* tremolo-enable
* tremolo-rate
* tremolo-smooth
* tremolo-depth
* gainer-enable
* gainer-gain
* gainer-pan

#### Setting parameters

Send a list to receiver `trackid-[parameter id]` with the second parameter being value, and the third argument being duration.

#### Reading parameters

##### For sampler/synth parameters

Read array `[track-id]-samplerparams`. The index for the parameter you want can be found in [pd paramwriters]->[pd samplerparamwriters] in the `sampleplayer.pd` patch.

##### For drum parameters

Read array `[track-id]-params-[drum slot (between 0 and 15)]`. The index for the parameter you want can be found in [pd paramwriters]->[pd slotparams] in the `drumplayer.pd` patch.

##### For effect parameters

Read array `[track-id]-fxparams`. The index for the parameter you want can be found in [pd paramwriters]->[pd fxparamwriters] in the `drumplayer.pd` patch (for drums) or [pd paramwriters]->[pd fxparamwriters] in the `sampleplayer.pd` patch (for sampler/synth).

##### For track/mixer parameters

Read array `[track-id]-mixerparams`. The index for the parameter you want can be found in [pd paramwriters]->[pd mixerparamwriters] in the `drumplayer.pd` patch (for drums) or [pd paramwriters]->[pd mixerparamwriters] in the `sampleplayer.pd` patch (for sampler/synth).

#### Moving effects up or down in the chain

Send a bang to `[track-id]-[effect-id]-moveup` to move it up and `[track-id]-[effect-id]-movedown` to move it down.