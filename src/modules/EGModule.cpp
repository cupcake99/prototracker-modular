#include "EGModule.h"
#include "Renderer.h"
#include <algorithm>

EGModule::EGModule(ModularSynth& synth)
	:SynthModule(synth, moduleId, 4, 3, 0), mState(Idle), mAmp(0.0f), mPrevKeyOn(0.0f)
{
}


void EGModule::cycle()
{
	if (mPrevKeyOn <= 0.5f && getInput(2) > 0.5f)
	{
		mState = Attack;
	}

	if (mPrevHardReset <= 0.5f && getInput(3) > 0.5f)
	{
		mState = Attack;
		mAmp = 0.0;
	}

	mPrevKeyOn = getInput(2);
	mPrevHardReset = getInput(3);

	setOutput(1, 0);

	float attackSpeed, decaySpeed;

	switch (mState)
	{
		case Idle:
			break;

		case Attack:
			setOutput(2, 0.0f);
			if (getInput(0) > 0)
				attackSpeed = 1.0f / mSampleRate / getInput(0);
			else
				attackSpeed = 1.0f;

			mAmp += attackSpeed;

			if (mAmp >= 1.0f)
			{
				mAmp = 1.0f;
				mState = Full;
			}
			break;

		case Full:
			setOutput(2, 1.0f);
			if (getInput(2) < 0.5f)
				mState = Decay;
			break;

		case Decay:
			setOutput(2, 1.0f);
			if (getInput(1) > 0)
				decaySpeed = 1.0f / mSampleRate / getInput(1);
			else
				decaySpeed = 1.0f;

			mAmp -= decaySpeed;

			if (mAmp <= 0.0f)
			{
				setOutput(1, 1.0f);

				mAmp = 0.0f;
				mState = Idle;
			}
			break;
	}

	setOutput(0, mAmp);
}


const char * EGModule::getInputName(int input) const
{
	static const char *names[] = {"Attack", "Decay", "KeyOn", "HardReset"};
	return names[input];
}


const char * EGModule::getOutputName(int output) const
{
	static const char *names[] = {"Output", "Finished", "State"};
	return names[output];
}


const char * EGModule::getName() const
{
	return "EG";
}

SynthModule * EGModule::createModule(ModularSynth& synth)
{
	return new EGModule(synth);
}

void EGModule::render(Renderer& renderer, const SDL_Rect& moduleArea, bool isSelected) const
{
	renderer.renderRect(moduleArea, getModuleColor(isSelected));

	SDL_Rect led = {moduleArea.x + moduleArea.w - (moduleArea.w / 8) - 2, moduleArea.y + (moduleArea.h / 2) - 2, 4, 4};

	if (mAmp > 0)
	{
		renderer.renderRect(led, Color(64 + ((255 - 64) * mAmp), 64 - (64 * mAmp), 64 - (64 * mAmp)));
	}

	SDL_Rect textArea = {moduleArea.x + 2, moduleArea.y + moduleArea.h / 2 - 4, 100, 100};
	renderer.renderText(textArea, Color(255,255,255), getName());
}
