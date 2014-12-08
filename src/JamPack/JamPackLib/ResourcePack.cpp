#include "pch.h"

#include "ResourcePack.h"

using namespace Jampack;
/*
	[PackFile format]

	<header>
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

//
// ResourcePack implementation
//

