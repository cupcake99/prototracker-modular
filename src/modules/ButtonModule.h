#pragma once

#include "../SynthModule.h"

class ButtonModule: public SynthModule
{
	int mValue;
	char mLabel[50];

	ButtonModule(ModularSynth& synth);

public:
	static const int moduleId = 46;
	static const int maxInstances = -1;
	static constexpr const char *moduleName = "Button";

	static SynthModule * createModule(ModularSynth& synth);

	virtual void cycle();

	virtual void onLoaded();
//	virtual void onShow();
//	virtual void onDial(int delta);
	virtual void onAction(SynthGrid& synthGrid);
	virtual void render(Renderer& renderer, const SDL_Rect& moduleArea, bool isSelected) const;

	virtual const char * getName() const;
	virtual const char * getInputName(int input) const;
	virtual const char * getOutputName(int output) const;

};
