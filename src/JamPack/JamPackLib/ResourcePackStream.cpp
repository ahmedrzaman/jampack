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
	_ASSERT(stream != NULL);
	if (stream == NULL)
		return false;

	if (stream->bad())
		return false;

	m_File = stream;



	return true;
}

bool ResourcePackStream::ReadHeader(__out uint8_t& majorVersion, __out uint8_t& minorVersion, __out std::string& name)
{
	_ASSERT(m_File != NULL);
	if (m_File == NULL)
		return false;

	// PACK
	// 0 9
	// "pack0"
	// 15

	return false;
}

bool ResourcePackStream::ReadTableOfContent(/*Something will go here*/)
{
	_ASSERT(m_File != NULL);
	if (m_File == NULL)
		return false;

	return false;
}

bool ResourcePackStream::ReadResource()
{
	_ASSERT(m_File != NULL);
	if (m_File == NULL)
		return false;

	return false;
}

// Writes
void ResourcePackStream::WriteHeader(const uint8_t majorVersion, const uint8_t minorVersion, const std::string& name) { }
void ResourcePackStream::WriteTableOfContent(/*something will go here*/) { }
void ResourcePackStream::WriteResource() { }