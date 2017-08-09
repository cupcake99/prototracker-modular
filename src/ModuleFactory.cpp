#include "ModuleFactory.h"
#include "OscillatorModule.h"
#include "PassthruModule.h"
#include "AudioOutModule.h"
#include "FrequencyInModule.h"
#include <cstdlib>

#define REGISTER(module) registerModule(module::moduleId, module::moduleName, &module::createModule, module::maxInstances)

ModuleFactory::ModuleFactory()
{
	REGISTER(OscillatorModule);
	REGISTER(PassthruModule);
	REGISTER(FrequencyInModule);
	REGISTER(AudioOutModule);
}


void ModuleFactory::registerModule(int id, const char *name, SynthModule::CreateModuleFunc createModule, int maxInstances)
{
	mModules.push_back(Module(id, name, createModule, maxInstances));
}


SynthModule* ModuleFactory::createModule(int id, ModularSynth& synth) const
{
	for (int i = 0 ; i < mModules.size() ; ++i)
		if (mModules[i].id == id)
			return mModules[i].createFunc(synth);
			
	return NULL;
}


int ModuleFactory::getNumModules() const
{
	return mModules.size();
}


const ModuleFactory::Module& ModuleFactory::getModuleInfo(int index) const
{
	return mModules[index];
}