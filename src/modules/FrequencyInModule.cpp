#include "FrequencyInModule.h"
#include "Renderer.h"
#include "../ModularSynth.h"

#ifndef TUNING
#define TUNING 440.0
#endif

FrequencyInModule::FrequencyInModule(ModularSynth& synth)
	:SynthModule(synth, moduleId, 0, 1, 0), mLed(0.0f)
{
}

void FrequencyInModule::cycle()
{
	setOutput(0, mSynth.getFrequency() * static_cast<float>(TUNING / 2) / 1000);

	float rate = 1.0f / mSampleRate / 0.25f;

	if (mSynth.getNoteTrigger())
	{
		mActive = 1;
		mLed = 1.0f;
	}

	if (mActive)
	{
		mLed -= rate;

		if (mLed <= 0)
		{
			mActive = 0;
		}
	}
}



const char * FrequencyInModule::getInputName(int input) const
{
	return "FrequencyIn";
}


const char * FrequencyInModule::getOutputName(int output) const
{
	static const char *names[] = {"Output"};
	return names[output];
}


const char * FrequencyInModule::getName() const
{
	return "FrequencyIn";
}

SynthModule * FrequencyInModule::createModule(ModularSynth& synth)
{
	return new FrequencyInModule(synth);
}

void FrequencyInModule::render(Renderer& renderer, const SDL_Rect& moduleArea, bool isSelected) const
{
	renderer.renderRect(moduleArea, getModuleColor(isSelected));

	SDL_Rect led = {moduleArea.x + moduleArea.w - (moduleArea.w / 8) - 2, moduleArea.y + moduleArea.h - 6, 4, 4};

	if (mLed > 0)
	{
		renderer.renderRect(led, Color(64 + ((255 - 64) * mLed), 64 - (64 * mLed), 64 - (64 * mLed)));
	}

	SDL_Rect textArea = {moduleArea.x + 2, moduleArea.y + moduleArea.h / 2 - 4, 100, 100};
	renderer.renderText(textArea, Color(255,255,255), getName());
}
