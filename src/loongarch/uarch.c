#include <stdint.h>

#include <loongarch/api.h>
#include <loongarch/cpucfg.h>
#include <cpuinfo/log.h>


void cpuinfo_loongarch_decode_vendor_uarch(
	uint32_t cpucfg,
	enum cpuinfo_vendor vendor[restrict static 1],
	enum cpuinfo_uarch uarch[restrict static 1])
{
	
	const char temp_vendor = 'A' + cpucfg_get_implementer(cpucfg);
	switch (temp_vendor) {
		case 'L':
			*vendor = cpuinfo_vendor_loongson;
			switch(cpucfg_get_variant(cpucfg)){
				case 0x3:
					if(cpucfg_get_revision(cpucfg)==5){
						*uarch = cpuinfo_uarch_LA464;
					}
					break;
			}
			break;
		default:
			//not match verify vendor and uarch
			*vendor = cpuinfo_vendor_unknown;
			*uarch = cpuinfo_uarch_unknown;
	}
}
