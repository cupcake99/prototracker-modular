#include "ConstModule.h"
#include <cstdio>

ConstModule::ConstModule(ModularSynth& synth)
	:SynthModule(synth, moduleId, 0, 2, 1)
{
}


void ConstModule::cycle()
{
	// 1.0 * const
	setOutput(0, getParam(0) / 100.0f);

	// 0.001 * const
	setOutput(1, getParam(0) / 100.0f / 1000.0f);
}



const char * ConstModule::getInputName(int input) const 
{
	return "";
}


const char * ConstModule::getOutputName(int output) const 
{
	static const char *names[] = {"Output", "Output/1000"};
	return names[output];
}


const char * ConstModule::getName() const
{
	return mLabel;
}


SynthModule * ConstModule::createModule(ModularSynth& synth)
{
	return new ConstModule(synth);
}


void ConstModule::onDial(int delta)
{
	setParam(0, static_cast<float>((delta + static_cast<int>(mParams[0]))));
	snprintf(mLabel, sizeof(mLabel), "%.2f", mParams[0] / 100.0f);
}


void ConstModule::onLoaded()
{
	// Trigger mLabel update
	setOutput(0, 0);
	onDial(0);
}

void ConstModule::onShow()
{
	// Trigger mLabel update
	onDial(0);
}
