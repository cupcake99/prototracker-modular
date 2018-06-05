#pragma once

#include "../SynthModule.h"

class DebugModule: public SynthModule
{
	DebugModule(ModularSynth& synth);
	char mLabel[50];
	
public:
	static const int moduleId = 45;
	static const int maxInstances = -1;
	static constexpr const char *moduleName = "Debug";
	
	static SynthModule * createModule(ModularSynth& synth);
	
	virtual void cycle();
	virtual void render(Renderer& renderer, const SDL_Rect& moduleArea, bool isSelected) const;
	virtual void onLoaded();
	virtual void onDial(int delta);
	virtual void onShow();
	
	virtual const char * getName() const;
	virtual const char * getInputName(int input) const;
	virtual const char * getOutputName(int output) const;
};
