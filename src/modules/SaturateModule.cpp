#include "SaturateModule.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "SDL.h"

SaturateModule::SaturateModule(ModularSynth& synth)
:SynthModule(synth, moduleId, 1, 1, 0)
{
}


SaturateModule::~SaturateModule()
{
}


void SaturateModule::cycle()
{
	setOutput(0, tanh(getInput(0)));
}


const char * SaturateModule::getInputName(int input) const
{
	static const char *names[] = {"Input"};
	return names[input];
}


const char * SaturateModule::getOutputName(int output) const
{
	return "Output";
}


const char * SaturateModule::getName() const
{
	return "Saturate";
}

SynthModule * SaturateModule::createModule(ModularSynth& synth)
{
	return new SaturateModule(synth);
}
