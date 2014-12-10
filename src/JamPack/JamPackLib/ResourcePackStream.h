#pragma once

namespace Jampack
{
	class ResourcePackStream
	{
	public:
		ResourcePackStream();
		~ResourcePackStream();

		_Check_return_ 
			bool Initialise(__in const char* filename);

		_Check_return_ 
			bool Initialise(__in std::fstream* stream);

		bool ExtractResource(const char* filename); // ??
		void StoreResource(const char* filepath); // ??

	private:

		// Reads
		bool ReadHeader(__out uint8_t& majorVersion, __out uint8_t& minorVersion, __out std::string& name);
		bool ReadTableOfContent(/*Something will go here*/);
		bool ReadResource();

		// Writes
		void WriteHeader(__in const uint8_t majorVersion, __in const uint8_t minorVersion, __in const std::string& name);
		void WriteTableOfContent(/*something will go here*/);
		void WriteResource();

	private:

		std::fstream* m_File; // Todo: Make this thread-safe.

	private:
		// No copying
		ResourcePackStream(const ResourcePackStream& copy);
		ResourcePackStream& operator=(const ResourcePackStream& that);
	};
}