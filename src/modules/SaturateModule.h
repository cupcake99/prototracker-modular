#pragma once

#include "../SynthModule.h"

class SaturateModule: public SynthModule
{
	SaturateModule(ModularSynth& synth);
	
public:
	virtual ~SaturateModule();
	
	static const int moduleId = 50;
	static const int maxInstances = -1;
	static constexpr const char *moduleName = "Saturate";
	
	static SynthModule * createModule(ModularSynth& synth);
	
	virtual void cycle();
	virtual void onLoaded();
	
	virtual const char * getName() const;
	virtual const char * getInputName(int input) const;
	virtual const char * getOutputName(int output) const;
};
