#pragma once

namespace Jampack
{
	/*
	[PackFile format]

	<header>
	major.minor
	name "pack0"
	ResourceCount
	<ResTOC>
	res0 = resoff0
	res1 = resoff1
	res2 = resoff2
	<resoff0>
	..
	..
	<resoff1>
	..
	..
	<resoff2>
	<end_of_file>
	*/

	class ResourcePackStream
	{
	public:
		ResourcePackStream();
		~ResourcePackStream();

		bool IsValid() const;
		bool IsOpen() const;
		bool Open(__in const char* filename);
		void Close();
		
		bool ExtractResource(__in const char* filename);
		void StoreResource(__in const char* filepath);

		const std::string& GetName() const;
		uint8_t GetMajorVersion() const;
		uint8_t GetMinorVersion() const;

	private:

		void ReadHeader();
		void ReadTOC();
		
		void Read(_Out_writes_bytes_all_(length) uint8_t* outBuf, uint32_t length);

		uint8_t ReadUint8();
		uint16_t ReadUint16();
		uint32_t ReadUint32();
		uint64_t ReadUint64();

		int8_t ReadInt8();
		int16_t ReadInt16();
		int32_t ReadInt32();
		int64_t ReadInt64();

	private:

		std::fstream m_file;
		bool m_open;
		bool m_valid;
		bool m_fail;

		std::string m_name;

		uint8_t m_major;
		uint8_t m_minor;

		uint32_t m_resCount;
		std::map<std::string, uint64_t> m_resTable;

		// Offsets
		uint64_t m_tocOffset;
		uint64_t m_resStartOffset;

	private:
		// No copying
		ResourcePackStream(const ResourcePackStream& copy);
		ResourcePackStream& operator=(const ResourcePackStream& that);
	};
}