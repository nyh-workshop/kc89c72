#include "kc89c72.h"

const int KC89C72_MIDItoFreq[] = {//MIDI note number
  15289, 14431, 13621, 12856, 12135, 11454, 10811, 10204,//0-o7
  9631, 9091, 8581, 8099, 7645, 7215, 6810, 6428,//8-15
  6067, 5727, 5405, 5102, 4816, 4545, 4290, 4050,//16-23
  3822, 3608, 3405, 3214, 3034, 2863, 2703, 2551,//24-31
  2408, 2273, 2145, 2025, 1911, 1804, 1703, 1607,//32-39
  1517, 1432, 1351, 1276, 1204, 1136, 1073, 1012,//40-47
  956, 902, 851, 804, 758, 716, 676, 638,//48-55
  602, 568, 536, 506, 478, 451, 426, 402,//56-63
  379, 358, 338, 319, 301, 284, 268, 253,//64-71
  239, 225, 213, 201, 190, 179, 169, 159,//72-79
  150, 142, 134, 127, 119, 113, 106, 100,//80-87
  95, 89, 84, 80, 75, 71, 67, 63,//88-95
  60, 56, 53, 50, 47, 45, 42, 40,//96-103
  38, 36, 34, 32, 30, 28, 27, 25,//104-111
  24, 22, 21, 20, 19, 18, 17, 16,//112-119
  15, 14, 13, 13, 12, 11, 11, 10,//120-127
  0//off
};

void KC89C72::note_chA(int i)
{
	chA.fineTune = KC89C72_MIDItoFreq[i]&0xff;
	chA.coarseTune = (KC89C72_MIDItoFreq[i] >> 8)&0x0f;
  	write_data(0x00, chA.fineTune);
 	write_data(0x01, chA.coarseTune);
}

void KC89C72::note_chB(int i)
{
	chB.fineTune = KC89C72_MIDItoFreq[i]&0xff;
	chB.coarseTune = (KC89C72_MIDItoFreq[i] >> 8)&0x0f;
  	write_data(0x02, chB.fineTune);
  	write_data(0x03, chB.coarseTune);
}

void KC89C72::note_chC(int i)
{
	chC.fineTune = KC89C72_MIDItoFreq[i]&0xff;
	chC.coarseTune = (KC89C72_MIDItoFreq[i] >> 8)&0x0f;
  	write_data(0x04, chC.fineTune);
  	write_data(0x05, chC.coarseTune);
}

void KC89C72::set_mix(bool chA_tone,bool chB_tone,bool chC_tone,bool chA_noise,bool chB_noise,bool chC_noise )
{
	r7reg = 0b11000000 |
			(chC_noise == true ? 0 : 0b00100000) |
			(chB_noise == true ? 0 : 0b00010000) |
			(chA_noise == true ? 0 : 0b00001000) |
			(chC_tone == true ? 0 : 0b00000100) |
			(chB_tone == true ? 0 : 0b00000010) |
			(chA_tone == true ? 0 : 0b00000001);
	write_data(7, r7reg);
}

void KC89C72::chA_setVol(unsigned char amplitude, bool useEnvelope ) {
	chA.amplitude = (amplitude & 0xf) | (useEnvelope << 4);
	write_data(8, chA.amplitude );
}

void KC89C72::chB_setVol(unsigned char amplitude, bool useEnvelope ) {
	chB.amplitude = (amplitude & 0xf) | (useEnvelope << 4);
	write_data(9, chB.amplitude );
}

void KC89C72::chC_setVol(unsigned char amplitude, bool useEnvelope ) {
	chC.amplitude = (amplitude & 0xf) | (useEnvelope << 4);
	write_data(10, chC.amplitude );
}

void KC89C72::setEnvelope(bool cont, bool attack, bool alternate, bool hold, unsigned long frequency)
{
	env.fineTune = frequency & 0xff;
	env.coarseTune = (frequency >> 8) & 0xff;
	env.envShapeCycle = (hold == true ? 0 : 1) |
					   (alternate == true ? 0 : 2) |
					   (attack == true ? 0 : 4) |
					   (cont == true ? 0 : 8);

	write_data(13, env.envShapeCycle);
	write_data(11, env.fineTune);
	write_data(12, env.coarseTune);
}

void KC89C72::setNoisePeriod(unsigned char np) {
	noisePeriod = np;
	write_data(6, noisePeriod & 0x0f);
}
