#include "ButtonModule.h"
#include "Renderer.h"
#include <cstdio>

ButtonModule::ButtonModule(ModularSynth& synth)
:SynthModule(synth, moduleId, 0, 1, 1), mValue(0)
{
}


void ButtonModule::cycle()
{
	setOutput(0, mValue);
}



const char * ButtonModule::getInputName(int input) const
{
	return "";
}


const char * ButtonModule::getOutputName(int output) const
{
	static const char *names[] = {"Output"};
	return names[output];
}


const char * ButtonModule::getName() const
{
	return mLabel;
}


SynthModule * ButtonModule::createModule(ModularSynth& synth)
{
	return new ButtonModule(synth);
}


//void ButtonModule::onDial(int delta)
//{
//	;
//}

void ButtonModule::onAction(SynthGrid& synthGrid)
{
	if (mValue)
	{
		snprintf(mLabel, sizeof(mLabel), "Off");
		mValue = 0;
	}
	else
	{
		snprintf(mLabel, sizeof(mLabel), " On");
		mValue = 1;
	}
}

void ButtonModule::onLoaded()
{
	// Trigger mLabel update
	setOutput(0, 0);
	snprintf(mLabel, sizeof(mLabel), "Off");
	mValue = 0;
//	onDial(0);
}

//void ButtonModule::onShow()
//{
//	// Trigger mLabel update
////	onDial(0);
//}

void ButtonModule::render(Renderer& renderer, const SDL_Rect& moduleArea, bool isSelected) const
{
	renderer.renderRect(moduleArea, getModuleColor(isSelected));

	SDL_Rect led = {moduleArea.x + moduleArea.w - (moduleArea.w / 8) - 2, moduleArea.y + moduleArea.h - 6, 4, 4};

	if (mValue)
		renderer.clearRect(led, Color(255, 0, 0));
	else
		renderer.drawRect(led, Color(255, 0, 0));

	SDL_Rect textArea = {moduleArea.x + 2, moduleArea.y + moduleArea.h / 2 - 4, 100, 100};
	renderer.renderText(textArea, Color(255,255,255), getName());
}
