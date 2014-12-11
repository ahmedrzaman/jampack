#include "pch.h"
#include "ResourcePacker.h"


class Thing
{
};

Thing* pThing = NULL;

void setThing(Thing& n)
{
	pThing = &n;
}

void createThing()
{
	Thing n;
	setThing(n);
}

void main()
{
	createThing();
	int i = 0;
	i++;

	Jampack::ResourcePacker rp;

	// Pack all the resources into 1 file.
}