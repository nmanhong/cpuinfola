#pragma once
#include <stdint.h>


#define CPUINFO_LOONGARCH_CPUCFG_REVISION_MASK     UINT32_C(0xFF000000)

#define CPUINFO_LOONGARCH_CPUCFG_REVISION_OFFSET      24



inline static uint32_t cpucfg_set_revision(uint32_t cpucfg, uint32_t revision) {
	return (cpucfg & ~CPUINFO_LOONGARCH_CPUCFG_REVISION_MASK) |
		((revision << CPUINFO_LOONGARCH_CPUCFG_REVISION_OFFSET) & CPUINFO_LOONGARCH_CPUCFG_REVISION_MASK);
}


inline static uint32_t cpucfg_get_revision(uint32_t cpucfg) {
	return (cpucfg & CPUINFO_LOONGARCH_CPUCFG_REVISION_MASK) >> CPUINFO_LOONGARCH_CPUCFG_REVISION_OFFSET;
}


inline static uint32_t cpucfg_copy_revision(uint32_t cpucfg, uint32_t other_cpucfg) {
	return (cpucfg & ~CPUINFO_LOONGARCH_CPUCFG_REVISION_MASK) | (other_cpucfg & CPUINFO_LOONGARCH_CPUCFG_REVISION_MASK);
}

