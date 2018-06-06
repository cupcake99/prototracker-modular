#include "TriggerNoteModule.h"
#include "Renderer.h"
#include "../ModularSynth.h"

TriggerNoteModule::TriggerNoteModule(ModularSynth& synth)
	:SynthModule(synth, moduleId, 0, 1, 0), mLed(0.0f)
{
}

void TriggerNoteModule::cycle()
{
	setOutput(0, mSynth.getNoteTrigger() ? 1.0f : 0.0f);

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



const char * TriggerNoteModule::getInputName(int input) const
{
	return "TriggerNote";
}


const char * TriggerNoteModule::getOutputName(int output) const
{
	return "Output";
}


const char * TriggerNoteModule::getName() const
{
	return "TriggerNote";
}

SynthModule * TriggerNoteModule::createModule(ModularSynth& synth)
{
	return new TriggerNoteModule(synth);
}

void TriggerNoteModule::render(Renderer& renderer, const SDL_Rect& moduleArea, bool isSelected) const
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
