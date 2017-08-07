#pragma once

#include "SynthConnection.h"
#include "IOscillator.h"

struct SynthModule;
struct FileSection;

class ModularSynth: public IOscillator
{
public:
	static const int maxModules = 16;
	static const int maxConnections = 64;

private:
	SynthModule *mModules[maxModules];
	SynthModule *mInputModule, *mOutputModule, *mOscillatorModule;
	SynthConnection mConnections[maxConnections];
	int mNumConnections;
	
	void cycle();
	
public:
	ModularSynth();
	virtual ~ModularSynth();
	
	const SynthModule* getModule(int index) const;
	const SynthConnection& getConnection(int index) const;
	int getNumConnections() const;
	
	bool addModule(int index, int moduleId);
	void removeModule(int index);
	bool connectModules(int fromModule, int toModule, int fromOutput, int toInput);
	void detachConnection(int moduleIndex, int type, int connectionIndex);
	void removeConnection(int index);
	void swapModules(int fromModule, int toModule);
	
	void clear();
	
	void writeSynth(FileSection& section);
	bool readSynth(const FileSection& section, int& offset);

	// IOscillator virtual methods
	virtual void triggerNote();
	virtual void setFrequency(float frequency);
	virtual void setVolume(int volume);
	virtual void update(int numSamples);
	virtual void render(Sample16 *buffer, int numSamples, int offset = 0);
};
