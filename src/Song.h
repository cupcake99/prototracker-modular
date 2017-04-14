#pragma once

struct Pattern;
struct Sequence;
struct Macro;
struct FileSection;

class Song
{
public:
	static const int songNameLength = 16;
	static const int songVersion = 16;
	
private:
	Sequence *sequence;
	Pattern *patterns;
	Macro *macros;
	
	int patternLength;
	int sequenceLength;
	
	char name[songNameLength + 1];
	
public:
	Song();
	~Song();
	
	int getPatternLength() const;
	int getSequenceLength() const;
	void setPatternLength(int length);
	void setSequenceLength(int length);
	
	Sequence& getSequence();
	Pattern& getPattern(int pattern);
	Macro& getMacro(int macro);
	
	int getLastPatternUsed() const;
	int getLastMacroUsed() const;
	char *getSongName();
	
	void clear();
	FileSection* pack();
	bool unpack(const FileSection& section);
	
	int getSize() const;

	static const int maxPatterns = 256;
	static const int maxSequenceRows = 256;
	static const int maxMacros = 256;
};
