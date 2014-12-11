#include "pch.h"
#include "ResourcePackStream.h"

using namespace Jampack;

//
// ResourcePackStream implementation
//

ResourcePackStream::ResourcePackStream()
	: m_open(false)
	, m_valid(false)
	, m_fail(true)
	, m_major(0)
	, m_minor(0)
	, m_resCount(0)
	, m_resStartOffset(0)
	, m_tocOffset(0)
{
}

ResourcePackStream::~ResourcePackStream()
{
	// Todo: Close the file handle.
}

bool ResourcePackStream::IsOpen() const
{
	return m_open;
}

bool ResourcePackStream::Open(__in const char* filename)
{
	if (m_open)
		return true; // Not opening again.

	m_file.open(filename);
	if (m_file.bad())
	{
		std::stringstream ss;
		ss << "File not found (" << std::string(filename) << ")";
		throw std::exception(ss.str().c_str());
	}

	m_open = m_file.is_open();

	// Assuming that the file stream is good from now on.

	// Read the file's metadata

	char fileStr[4];
	m_file.read((char*)fileStr, sizeof(char) * 4);
	if (strcmp(fileStr, "PACK") != 0)
	{
		Close();
		return false;
	}

	ReadTOC();

	m_valid = m_file.good();

	return m_valid;
}

void ResourcePackStream::Close()
{
	if (m_file.is_open())
		m_file.close();
}

bool ResourcePackStream::ExtractResource(__in const char* filename, __out uint8_t* outBuff)
{
	// Todo

	return false;
}

const std::string& ResourcePackStream::GetName() const
{
	return m_name;
}

uint8_t ResourcePackStream::GetMajorVersion() const
{
	return m_major;
}

uint8_t ResourcePackStream::GetMinorVersion() const
{
	return m_minor;
}

bool ResourcePackStream::IsValid() const
{
	return m_valid;
}

void ResourcePackStream::ReadHeader()
{
	m_major = ReadUint8();
	m_minor = ReadUint8();

	uint8_t len = ReadUint8();
	char* nameStr = new char[len];

	Read((uint8_t*)nameStr, len);
	
	m_name = nameStr;

	delete[] nameStr;
}

void ResourcePackStream::ReadTOC()
{
	m_resCount = ReadUint32();

	m_tocOffset = m_file.tellg();

	for (uint32_t i = 0; i < m_resCount; i++)
	{
		uint8_t resNameLen = ReadUint8();

		char* resName = new char[resNameLen];
		m_file.read(resName, resNameLen);

		std::string resNameStr(resName); // name of resource
		uint64_t pos = ReadUint64();

		std::pair<std::string, uint64_t> pair(resNameStr, pos);
		m_resTable.insert(pair);

		delete[] resName;
	}

	m_resStartOffset = m_file.tellg();
}

void ResourcePackStream::Read(uint8_t* outBuf, uint32_t length)
{
	if (outBuf && length > 0)
	{
		if (m_file.is_open())
		{
			m_file.read((char*)outBuf, length);
			m_fail = !m_file.good();
		}
		else
		{
			m_fail = true;
		}

		if (m_fail)
		{
			// Just clear that memory.
			memset(outBuf, 0, length);
		}
	}

	_ASSERT(!m_fail);
}

uint8_t	ResourcePackStream::ReadUint8()
{
	uint8_t retValue = 0;
	Read((uint8_t*)& retValue, 1);

	return retValue;
}

uint16_t ResourcePackStream::ReadUint16()
{
	uint16_t retValue = 0;
	Read((uint8_t*)&retValue, 2);

	// Todo: care about endianness.

	return retValue;
}

uint32_t ResourcePackStream::ReadUint32()
{
	uint32_t retValue = 0;
	Read((uint8_t*)&retValue, 4);

	// Todo: care about endianness.

	return retValue;
}

uint64_t ResourcePackStream::ReadUint64()
{
	uint64_t retValue = 0;
	Read((uint8_t*)&retValue, 8);

	// Todo: care about endianness.

	return retValue;
}

int8_t ResourcePackStream::ReadInt8()
{
	int8_t retValue = 0;
	Read((uint8_t*)&retValue, 1);
	return retValue;
}

int16_t	ResourcePackStream::ReadInt16()
{
	int16_t retValue = 0;
	Read((uint8_t*)&retValue, 2);

	// Todo: care about endianness.

	return retValue;
}

int32_t	ResourcePackStream::ReadInt32()
{
	int32_t retValue = 0;
	Read((uint8_t*)&retValue, 4);

	// Todo: care about endianness.

	return retValue;
}

int64_t	ResourcePackStream::ReadInt64()
{
	int64_t retValue = 0;
	Read((uint8_t*)&retValue, 8);

	// Todo: care about endianness.

	return retValue;
}

