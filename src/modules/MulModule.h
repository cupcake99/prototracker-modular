#pragma once

#include "../SynthModule.h"

class MulModule: public SynthModule
{
	MulModule(ModularSynth& synth);

public:
	static const ModuleClass moduleClass = ModuleClass::Arithmetic;
	static const int moduleId = 6;
	static const int maxInstances = -1;
	static constexpr const char *moduleName = "Mul";

	static SynthModule * createModule(ModularSynth& synth);

	virtual void cycle();

	virtual const char * getName() const;
	virtual const char * getInputName(int input) const;
	virtual const char * getOutputName(int output) const;

};
