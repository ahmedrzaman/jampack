#pragma once

//
// ResourcePacker class:
//	This class compress the given files and directories, bundles them into a 
//	 file and outputs them into the given location.
//
/*

	##############################

	[PackFile_V2 format]

	PackTOC
	packCount
	pack0 = packoffset0
	pack1 = packoffset1
	pack2 = packoffset2

	<packoffset0>
	name "pack0"
	ResTOC
	res0 = resoff0
	res1 = offset1
	res2 = offset2
	<resoff0>
	<resoff1>

	<packoffset1>

	<packoffset2>

*/
namespace Jampack
{
	class ResourcePackStream;

	class ResourcePacker
	{
	private:
		typedef std::vector<const std::string> FileListCollection;

	public:

		ResourcePacker();
		~ResourcePacker();
		
		// Add the given filename to packer for packing.
		void AddResource(__in const std::string& fileName);

		// Remove the given resource file name from packing.
		void RemoveResource(__in const std::string& fileName);

		// Loads the list of files and packs them into a file.
		void PackImmediately(__in const std::string& outputDirectory);


	private:

		// Finds if the given fileName is in the resource list.
		bool Find(__in const std::string& fileName, __out FileListCollection::const_iterator& iterOut) const;

		bool OpenPack(__in const std::string& packFilePath);
		bool WriteIntoPack(__in const std::vector<char*>& bytes);
		void ClosePack();
		
	private:

		FileListCollection m_FileList;

		std::ofstream m_PackFileStream;

	private:
		// No copying!
		ResourcePacker(const ResourcePacker& copy);
		ResourcePacker& operator=(const ResourcePacker& copy);
	};
}