#include "pch.h"
#include "ResourcePackStream.h"

using namespace Jampack;

//
// ResourcePackStream implementation
//

ResourcePackStream::ResourcePackStream()
	: m_File(NULL)
{

}

ResourcePackStream::~ResourcePackStream()
{
	if (m_File != NULL)
	{
		m_File = NULL;
		m_File->close();
		delete m_File;
	}
}

bool ResourcePackStream::Initialise(const char* filename)
{
	std::fstream* fs = new std::fstream(filename);
	return Initialise(fs);
}

bool ResourcePackStream::Initialise(__in std::fstream* stream)
{
	if (NULL == stream)
		return false;

	if (stream->bad())
		return false;

	m_File = stream;
}

bool ResourcePackStream::ReadHeader(uint8_t& majorVersion, uint8_t& minorVersion, std::string& name)
{
	if (m_File == NULL)
		return false;


}

bool ResourcePackStream::ReadTableOfContent(/*Something will go here*/)
{

}

bool ResourcePackStream::ReadResource()
{

}

// Writes
void ResourcePackStream::WriteHeader(const uint8_t majorVersion, const uint8_t minorVersion, const std::string& name) { }
void ResourcePackStream::WriteTableOfContent(/*something will go here*/) { }
void ResourcePackStream::WriteResource() { }