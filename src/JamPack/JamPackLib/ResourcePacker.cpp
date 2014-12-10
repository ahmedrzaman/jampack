#include "pch.h"
#include "ResourcePackStream.h"
#include "ResourcePack.h"
#include "ResourcePacker.h"
#include "zlib.h"

using namespace Jampack;

//
// ResourcePacker implementation
//


ResourcePacker::ResourcePacker()
{

}

ResourcePacker::~ResourcePacker()
{

}

void ResourcePacker::AddResource(const std::string& fileName)
{
	FileListCollection::iterator iter;
	if (Find(fileName, iter))
		return;

	m_FileList.push_back(fileName);
}

void ResourcePacker::RemoveResource(const std::string& fileName)
{
	FileListCollection::iterator iter;
	if (!Find(fileName, iter))
		return;

	m_FileList.erase(iter);
}

bool ResourcePacker::Find(const std::string& fileName, ResourcePacker::FileListCollection::const_iterator& iterOut) const
{
	FileListCollection::const_iterator iter = m_FileList.cbegin();
	for (; iter != m_FileList.end(); iter++)
	{
		if ((*iter).compare(fileName) == 0)
		{
			iterOut = iter;
			return true;
		}
	}

	return false;
}

bool ResourcePacker::OpenPack(const std::string& packFilePath)
{
	m_PackFileStream.open(packFilePath);
	if (m_PackFileStream.bad())
		throw std::exception("Failed to create file.");

	return true;
}

bool ResourcePacker::WriteIntoPack(const std::vector<char*>& bytes)
{
	if (!m_PackFileStream.write((char*)bytes.data(), bytes.size()))
		return false;

	return true;
}

void ResourcePacker::ClosePack()
{
	if (m_PackFileStream.is_open())
	{
		m_PackFileStream.clear();
		m_PackFileStream.close();
	}
}

void ResourcePacker::PackImmediately(const std::string& outputDirectory)
{
	ClosePack();

	if (!OpenPack(outputDirectory + "packfile.pack"))
		throw std::exception("Cannot create packfile.");

	FileListCollection::iterator index = m_FileList.begin();
	for (; index != m_FileList.end(); index++)
	{
		// Load the file stream.
		std::ifstream fs(index->data(), std::ios::in | std::ios::binary);
		if (fs.good() && fs.is_open())
		{
			// Take the stream.
			std::streamsize size = fs.gcount();
			std::vector<char*> bytes((int)size);
			if (fs.read(*(bytes.data()), size))
			{
				// Todo: zip it up.

				// Pack into file.
				WriteIntoPack(bytes);
			}
		}

		fs.close();
	}

	ClosePack();
}