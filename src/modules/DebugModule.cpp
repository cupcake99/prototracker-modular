#include "DebugModule.h"
#include "../Renderer.h"
#include <cstdio>

DebugModule::DebugModule(ModularSynth& synth)
:SynthModule(synth, moduleId, 2, 1, 1)
{
}


void DebugModule::cycle()
{
	// Passthru
	setOutput(0, getInput(0));
}


const char * DebugModule::getInputName(int input) const
{
	static const char *names[] = {"Input", "On/Off"};
	return names[input];
}


const char * DebugModule::getOutputName(int output) const
{
	static const char *names[] = {"Passthru"};
	return names[output];
}


const char * DebugModule::getName() const
{
	return mLabel;
;
}


void DebugModule::onLoaded()
{
	setInput(0, 0.0f);
	onDial(0);
}

void DebugModule::onShow()
{
	// Trigger mLabel update
	onDial(0);
}

SynthModule * DebugModule::createModule(ModularSynth& synth)
{
	return new DebugModule(synth);
}


void DebugModule::render(Renderer& renderer, const SDL_Rect& moduleArea, bool isSelected) const
{
	renderer.renderRect(moduleArea, getModuleColor(isSelected));
	SDL_Rect textArea = {moduleArea.x + 2, moduleArea.y + moduleArea.h / 2 - 4, 100, 100};
	renderer.renderText(textArea, Color(255,255,255), getName());
	if (getInput(1) >= 1)
		printf("Debug Module %d: %+06.6f\n", static_cast<int>(getParam(0)), getInput(0));
}

void DebugModule::onDial(int delta)
{
	int track = (static_cast<int>(delta + mParams[0]) + 8) % 8;
	
	setParam(0, track);
	sprintf(mLabel, "Dbg%d", track);
}