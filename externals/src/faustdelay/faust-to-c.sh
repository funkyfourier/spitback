#!/bin/bash
# Transpiles the faust .dsp code to .c, so we can make a Pure Data external from there

faust -lang c faustdelay.dsp -o faustdelay.c