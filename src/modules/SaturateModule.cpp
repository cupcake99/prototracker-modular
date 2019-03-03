#include "SaturateModule.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "SDL.h"

SaturateModule::SaturateModule(ModularSynth& synth)
:SynthModule(synth, moduleId, 2, 1, 0)
{
}


SaturateModule::~SaturateModule()
{
}


void SaturateModule::cycle()
{
	setOutput(0, std::fdimf(std::fabsf(getInput(0)), std::fabsf(std::tanh(getInput(0) * getDrive()))) > 0.0f ? getInput(0) : std::tanh(getInput(0) * getDrive()));
}

const char * SaturateModule::getInputName(int input) const
{
	static const char *names[] = {"Input", "Drive"};
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

void SaturateModule::onLoaded()
{
	setInput(1, 1.0f);
}

float SaturateModule::getDrive()
{
	return std::fmaxf(0.0f, getInput(1));
}
