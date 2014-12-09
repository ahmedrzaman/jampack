#pragma once


namespace Jampack
{
	//
	// ResourcePack class:
	//	This is a pack file for resources.
	//

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

	class ResourcePack
	{
	public:
		ResourcePack();
		~ResourcePack();

		bool Load(__in ResourcePackStream& stream);
		void Save(__in ResourcePackStream& stream);
		
		const std::string& GetName() const;

		uint8_t GetMajorVersion() const;
		uint8_t GetMinorVersion() const;

		bool IsValid() const;

	private:

		std::string m_Name;

		bool m_IsValid;

		uint8_t m_MajorVersion;
		uint8_t m_MinorVersion;

		// Offsets
		int m_TOCOffset;
	};
}