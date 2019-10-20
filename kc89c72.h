#ifndef KC89C72_H
#define KC89C72_H

extern const int KC89C72_MIDItoFreq[];

struct KC89C72_envelope
{
	unsigned char fineTune;
	unsigned char coarseTune;
	unsigned char envShapeCycle;
};

struct KC89C72_channel
{
	unsigned char fineTune;
	unsigned char coarseTune;
	unsigned char amplitude;
};

class KC89C72 {
	
private:
	unsigned char r7reg = 0x00;
	unsigned char noisePeriod = 0x00;
	struct KC89C72_channel chA;
	struct KC89C72_channel chB;
	struct KC89C72_channel chC;
	struct KC89C72_envelope env;
public:
	virtual void write_data(unsigned char addr, unsigned char inputData) = 0;
	void chA_setVol(unsigned char amplitude, bool useEnvelope );
	void chB_setVol(unsigned char amplitude, bool useEnvelope );
	void chC_setVol(unsigned char amplitude, bool useEnvelope );
	void setEnvelope(bool cont, bool attack, bool alternate, bool hold, unsigned long frequency);
	void setNoisePeriod(unsigned char np);
	void set_mix(bool chA_tone,bool chB_tone,bool chC_tone,bool chA_noise,bool chB_noise,bool chC_noise );
	void note_chA(int i);
	void note_chB(int i);
	void note_chC(int i);		
};

#endif