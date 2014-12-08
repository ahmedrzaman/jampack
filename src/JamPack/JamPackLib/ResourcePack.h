#pragma once


namespace Jampack
{
	//
	// ResourcePack class:
	//	This is a pack file for resources.
	//

	class ResourcePack
	{
	public:
		ResourcePack(const char* name, long initialSize = 2000);
		~ResourcePack();

		bool Load(std::wstring fileName);
		bool Load(std::ifstream& stream);
		
	private:
		const char* m_szName;

		int m_MajorVersion;
		int m_MinorVersion;

	};


	//
	// ResourcePackReader class
	//
	class ResourcePackReader
	{
	public:
		ResourcePackReader();
		~ResourcePackReader();

		bool Open(std::wstring fileName);
		void Close();

		ULONG32 GetSize();
		
		bool GetStream();

	private:

	};

	//
	// ResourcePackWriter class
	//
	class ResourcePackWriter
	{
	public:
		ResourcePackWriter();
		~ResourcePackWriter();

		bool Initialise(const ResourcePack& packFile);

	private:
		ResourcePack* m_Pack;
	};
}