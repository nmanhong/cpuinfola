#pragma once
#include <stdint.h>



#define CPUINFO_LOONGARCH_CPUCFG_IMPLEMENTER_MASK  UINT32_C(0xFF000000)
#define CPUINFO_LOONGARCH_CPUCFG_VARIANT_MASK      UINT32_C(0x00F00000)
#define CPUINFO_LOONGARCH_CPUCFG_PART_MASK UINT32_C(0x000F0000)
#define CPUINFO_LOONGARCH_CPUCFG_REVISION_MASK         UINT32_C(0x0000FFF0)
#define CPUINFO_LOONGARCH_CPUCFG_SUFFIX_MASK     UINT32_C(0x0000000F)

#define CPUINFO_LOONGARCH_CPUCFG_IMPLEMENTER_OFFSET  24
#define CPUINFO_LOONGARCH_CPUCFG_VARIANT_OFFSET      20
#define CPUINFO_LOONGARCH_CPUCFG_PART_OFFSET 16
#define CPUINFO_LOONGARCH_CPUCFG_REVISION_OFFSET          4
#define CPUINFO_LOONGARCH_CPUCFG_SUFFIX_OFFSET      0



inline static uint32_t cpucfg_set_implementer(uint32_t cpucfg, uint32_t implementer) {
	return (cpucfg & ~CPUINFO_LOONGARCH_CPUCFG_IMPLEMENTER_MASK) |
		((implementer << CPUINFO_LOONGARCH_CPUCFG_IMPLEMENTER_OFFSET) & CPUINFO_LOONGARCH_CPUCFG_IMPLEMENTER_MASK);
}

inline static uint32_t cpucfg_set_variant(uint32_t cpucfg, uint32_t variant) {
	return (cpucfg & ~CPUINFO_LOONGARCH_CPUCFG_VARIANT_MASK) |
		((variant << CPUINFO_LOONGARCH_CPUCFG_VARIANT_OFFSET) & CPUINFO_LOONGARCH_CPUCFG_VARIANT_MASK);
}

inline static uint32_t cpucfg_set_part(uint32_t cpucfg, uint32_t part) {
	return (cpucfg & ~CPUINFO_LOONGARCH_CPUCFG_PART_MASK) |
		((part << CPUINFO_LOONGARCH_CPUCFG_PART_OFFSET) & CPUINFO_LOONGARCH_CPUCFG_PART_MASK);
}

inline static uint32_t cpucfg_set_revision(uint32_t cpucfg, uint32_t revision) {
	return (cpucfg & ~CPUINFO_LOONGARCH_CPUCFG_REVISION_MASK) |
		((revision << CPUINFO_LOONGARCH_CPUCFG_REVISION_OFFSET) & CPUINFO_LOONGARCH_CPUCFG_REVISION_MASK);
}
inline static uint32_t cpucfg_set_suffix(uint32_t cpucfg, uint32_t suffix) {
	return (cpucfg & ~CPUINFO_LOONGARCH_CPUCFG_SUFFIX_MASK) |
		((suffix << CPUINFO_LOONGARCH_CPUCFG_SUFFIX_OFFSET) & CPUINFO_LOONGARCH_CPUCFG_SUFFIX_MASK);
}


inline static uint32_t cpucfg_get_variant(uint32_t cpucfg) {
	return (cpucfg & CPUINFO_LOONGARCH_CPUCFG_VARIANT_MASK) >> CPUINFO_LOONGARCH_CPUCFG_VARIANT_OFFSET;
}

inline static uint32_t cpucfg_get_implementer(uint32_t cpucfg) {
	return (cpucfg & CPUINFO_LOONGARCH_CPUCFG_IMPLEMENTER_MASK) >> CPUINFO_LOONGARCH_CPUCFG_IMPLEMENTER_OFFSET;
}

inline static uint32_t cpucfg_get_part(uint32_t cpucfg) {
	return (cpucfg & CPUINFO_LOONGARCH_CPUCFG_PART_MASK) >> CPUINFO_LOONGARCH_CPUCFG_PART_OFFSET;
}

inline static uint32_t cpucfg_get_revision(uint32_t cpucfg) {
	return (cpucfg & CPUINFO_LOONGARCH_CPUCFG_REVISION_MASK) >> CPUINFO_LOONGARCH_CPUCFG_REVISION_OFFSET;
}

inline static uint32_t cpucfg_get_suffix(uint32_t cpucfg) {
	return (cpucfg & CPUINFO_LOONGARCH_CPUCFG_SUFFIX_MASK) >> CPUINFO_LOONGARCH_CPUCFG_SUFFIX_OFFSET;
}

inline static uint32_t cpucfg_copy_implementer(uint32_t cpucfg, uint32_t other_cpucfg) {
	return (cpucfg & ~CPUINFO_LOONGARCH_CPUCFG_IMPLEMENTER_MASK) | (other_cpucfg & CPUINFO_LOONGARCH_CPUCFG_IMPLEMENTER_MASK);
}

inline static uint32_t cpucfg_copy_variant(uint32_t cpucfg, uint32_t other_cpucfg) {
	return (cpucfg & ~CPUINFO_LOONGARCH_CPUCFG_VARIANT_MASK) | (other_cpucfg & CPUINFO_LOONGARCH_CPUCFG_VARIANT_MASK);
}

inline static uint32_t cpucfg_copy_part(uint32_t cpucfg, uint32_t other_cpucfg) {
	return (cpucfg & ~CPUINFO_LOONGARCH_CPUCFG_PART_MASK) | (other_cpucfg & CPUINFO_LOONGARCH_CPUCFG_PART_MASK);
}

inline static uint32_t cpucfg_copy_revision(uint32_t cpucfg, uint32_t other_cpucfg) {
	return (cpucfg & ~CPUINFO_LOONGARCH_CPUCFG_REVISION_MASK) | (other_cpucfg & CPUINFO_LOONGARCH_CPUCFG_REVISION_MASK);
}

inline static uint32_t cpucfg_copy_suffix(uint32_t cpucfg, uint32_t other_cpucfg) {
	return (cpucfg & ~CPUINFO_LOONGARCH_CPUCFG_SUFFIX_MASK) | (other_cpucfg & CPUINFO_LOONGARCH_CPUCFG_SUFFIX_MASK);
}