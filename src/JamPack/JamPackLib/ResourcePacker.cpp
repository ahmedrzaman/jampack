#include "pch.h"
#include "ResourcePack.h"
#include "ResourcePacker.h"

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

void ResourcePacker::AddResource(const std::wstring& fileName)
{
	FileListCollection::iterator iter;
	if (Find(fileName, iter))
		return;

	m_FileList.push_back(fileName);
}

void ResourcePacker::RemoveResource(const std::wstring& fileName)
{
	FileListCollection::iterator iter;
	if (!Find(fileName, iter))
		return;

	m_FileList.erase(iter);
}

bool ResourcePacker::Find(const std::wstring& fileName, ResourcePacker::FileListCollection::iterator& iterOut)
{
	FileListCollection::iterator iter = m_FileList.begin();
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

void ResourcePacker::PackImmediately(const std::wstring& outputDirectory)
{
	// Todo:
}