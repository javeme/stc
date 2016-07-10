#ifndef CharPosition_h
#define CharPosition_h

struct CharPosition
{
	unsigned int edgeIndex;
	unsigned int charIndex;
	unsigned int matchedPos;
	bool bImplicit;
};

#endif