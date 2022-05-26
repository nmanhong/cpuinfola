#include <stdint.h>

#include <loongarch/api.h>
#include <loongarch/cpucfg.h>
#include <cpuinfo/log.h>


void cpuinfo_loongarch_decode_vendor_uarch(
	//uint32_t cpucfg,
	enum cpuinfo_vendor vendor[restrict static 1],
	enum cpuinfo_uarch uarch[restrict static 1])
{
	*vendor = cpuinfo_vendor_loongson;
	*uarch = cpuinfo_uarch_loongarch_3a5000;
	/*
	function(cpucfg): choose vendor
	// switch (function(cpucfg)) {
	// 	case 'L':
	// 		*vendor = cpuinfo_vendor_loongson;
	// 		*uarch = cpuinfo_uarch_loongarch_3a5000;
	// 	default:
	// 		//not match verify vendor and uarch
	//		*vendor = cpuinfo_vendor_unknown;
	// 		*uarch = cpuinfo_uarch_unknown;
	// }
	*/
}
