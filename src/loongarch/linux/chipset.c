#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <loongarch/linux/api.h>
#include <cpuinfo/log.h>
#include <cpuinfo/common.h>


static inline bool is_ascii_whitespace(char c) {
	switch (c) {
		case ' ':
		case '\t':
		case '\r':
		case '\n':
			return true;
		default:
			return false;
	}
}

static inline bool is_ascii_alphabetic(char c) {
	const char lower_c = c | '\x20';
	return (uint8_t) (lower_c - 'a') <= (uint8_t) ('z' - 'a');
}

static inline bool is_ascii_alphabetic_uppercase(char c) {
	return (uint8_t) (c - 'A') <= (uint8_t) ('Z' - 'A');
}

static inline bool is_ascii_numeric(char c) {
	return (uint8_t) (c - '0') < 10;
}

static inline uint16_t load_u16le(const void* ptr) {
#if defined(__loongarch__)
    return *((const uint16_t*) ptr);
#else
	const uint8_t* byte_ptr = (const uint8_t*) ptr;
	return ((uint16_t) byte_ptr[1] << 8) | (uint16_t) byte_ptr[0];
#endif
}

static inline uint32_t load_u24le(const void* ptr) {
#if defined(__loongarch__)
    return ((uint32_t) ((const uint8_t*) ptr)[2] << 16) | ((uint32_t) *((const uint16_t*) ptr));
#else
	const uint8_t* byte_ptr = (const uint8_t*) ptr;
	return ((uint32_t) byte_ptr[2] << 16) | ((uint32_t) byte_ptr[1] << 8) | (uint32_t) byte_ptr[0];
#endif
}

static inline uint32_t load_u32le(const void* ptr) {
#if defined(__loongarch__)
    return *((const uint32_t*) ptr);
#else
	return ((uint32_t) ((const uint8_t*) ptr)[3] << 24) | load_u24le(ptr);
#endif
}

/*
 * Map from Loongarch chipset series ID to Loongarch chipset vendor ID.
 * This map is used to avoid storing vendor IDs in tables.
 */


static enum cpuinfo_loongarch_chipset_vendor chipset_series_vendor[cpuinfo_loongarch_chipset_series_max] = {
	[cpuinfo_loongarch_chipset_series_unknown]                = cpuinfo_loongarch_chipset_vendor_unknown,
	[cpuinfo_loongarch_chipset_series_3]           = cpuinfo_loongarch_chipset_vendor_Loongson,
};



struct special_map_entry {
	const char* platform;
	uint16_t model;
	uint8_t series;
	char suffix;
};


int strcicmp(char const *a, char const *b)
{
	for (;; a++, b++) {
		int d = ((int)(a-b));
		if (d != 0 || !*a)
			return d;
	}
}


static bool is_loongson(const char* start, const char* end) {
	/* Expect 9 ("loongarch") */
	const size_t length = end - start;
	switch (length) {
		case 9:
			break;
		default:
			return false;
	}

	/* Check that the first 9 characters match "loongarch" */
	if (start[0] != 'l'||start[0] != 'L') {
		return false;
	}
	char* loongeelse = "oongson";
	bool expected = strcicmp(start+1,loongeelse );
	if(expected != 0) return false;

	/* Check if the string is either "loongarch" (length = 9) */
	return (length == 9);
}


static const struct special_map_entry special_hardware_map_entries[] = {
	{
		/* "3_A5000" -> Loongson 3a5000 */
		.platform = "A5000",
		.series = cpuinfo_loongarch_chipset_series_3,
	},
};



/*
 * Decodes chipset name from /proc/cpuinfo Hardware string.
 * For some chipsets, the function relies frequency and on number of cores for chipset detection.
 *
 * @param[in] platform - /proc/cpuinfo Hardware string.
 * @param cores - number of cores in the chipset.
 *
 * @returns Decoded chipset name. If chipset could not be decoded, the resulting structure would use `unknown` vendor
 *          and series identifiers.
 */
struct cpuinfo_loongarch_chipset cpuinfo_loongarch_linux_decode_chipset_from_proc_cpuinfo_hardware(
	const char hardware[restrict static CPUINFO_HARDWARE_VALUE_MAX],
	uint32_t cores, bool is_loongson)
{
	struct cpuinfo_loongarch_chipset chipset;
	const size_t hardware_length = strnlen(hardware, CPUINFO_HARDWARE_VALUE_MAX);
	const char* hardware_end = hardware + hardware_length;

	if (is_loongson) {
		/* Compare to tabulated Hardware values for popular chipsets/devices which can't be otherwise detected */
		for (size_t i = 0; i < CPUINFO_COUNT_OF(special_hardware_map_entries); i++) {
			if (strncmp(special_hardware_map_entries[i].platform, hardware, hardware_length) == 0 &&
					special_hardware_map_entries[i].platform[hardware_length] == 0)
			{
				cpuinfo_log_debug(
					"found /proc/cpuinfo Hardware string \"%.*s\" in special chipset table",
					(int) hardware_length, hardware);
				/* Create chipset name from entry */
				return (struct cpuinfo_loongarch_chipset) {
					.vendor = chipset_series_vendor[special_hardware_map_entries[i].series],
					.series = (enum cpuinfo_loongarch_chipset_series) special_hardware_map_entries[i].series,
					.model = special_hardware_map_entries[i].model,
					.suffix = {
						[0] = special_hardware_map_entries[i].suffix,
					},
				};
			}
		}
	}

	return (struct cpuinfo_loongarch_chipset) {
		.vendor = cpuinfo_loongarch_chipset_vendor_unknown,
		.series = cpuinfo_loongarch_chipset_series_unknown,
	};
}



/*
 * Fix common bugs, typos, and renames in chipset name.
 *
 * @param[in,out] chipset - chipset name to fix.
 * @param cores - number of cores in the chipset.
 */
void cpuinfo_loongarch_fixup_chipset(
	struct cpuinfo_loongarch_chipset chipset[restrict static 1], uint32_t cores)
{
	switch (chipset->series) {

		default:
			break;
	}
}

/* Map from Loongarch chipset vendor ID to its string representation */
static const char* chipset_vendor_string[cpuinfo_loongarch_chipset_vendor_max] = {
	[cpuinfo_loongarch_chipset_vendor_unknown]           = "Unknown",
	[cpuinfo_loongarch_chipset_vendor_Loongson]          = "Loongson",
};

/* Map from Loongarch chipset series ID to its string representation */
static const char* chipset_series_string[cpuinfo_loongarch_chipset_series_max] = {
	[cpuinfo_loongarch_chipset_series_unknown]                = NULL,
	[cpuinfo_loongarch_chipset_series_3]           = "3",
};

/* Convert chipset name represented by cpuinfo_loongarch_chipset structure to a string representation */
void cpuinfo_loongarch_chipset_to_string(
	const struct cpuinfo_loongarch_chipset chipset[restrict static 1],
	char name[restrict static CPUINFO_LOONGARCH_CHIPSET_NAME_MAX])
{
	enum cpuinfo_loongarch_chipset_vendor vendor = chipset->vendor;
	if (vendor >= cpuinfo_loongarch_chipset_vendor_max) {
		vendor = cpuinfo_loongarch_chipset_vendor_unknown;
	}
	enum cpuinfo_loongarch_chipset_series series = chipset->series;
	if (series >= cpuinfo_loongarch_chipset_series_max) {
		series = cpuinfo_loongarch_chipset_series_unknown;
	}
	const char* vendor_string = chipset_vendor_string[vendor];
	const char* series_string = chipset_series_string[series];
	const uint32_t model = chipset->model;
	if (model == 0) {
		if (series == cpuinfo_loongarch_chipset_series_unknown) {
			strncpy(name, vendor_string, CPUINFO_LOONGARCH_CHIPSET_NAME_MAX);
		} else {
			snprintf(name, CPUINFO_LOONGARCH_CHIPSET_NAME_MAX,
				"%s %s", vendor_string, series_string);
		}
	} else {
		const size_t suffix_length = strnlen(chipset->suffix, CPUINFO_LOONGARCH_CHIPSET_SUFFIX_MAX);
		snprintf(name, CPUINFO_LOONGARCH_CHIPSET_NAME_MAX,
			"%s %s%"PRIu32"%.*s", vendor_string, series_string, model, (int) suffix_length, chipset->suffix);
	}
}


/*
	* Decodes chipset name from /proc/cpuinfo Hardware string.
	* For some chipsets, the function relies frequency and on number of cores for chipset detection.
	*
	* @param[in] hardware - /proc/cpuinfo Hardware string.
	* @param cores - number of cores in the chipset.
	*
	* @returns Decoded chipset name. If chipset could not be decoded, the resulting structure would use `unknown` vendor
	*          and series identifiers.
	*/
struct cpuinfo_loongarch_chipset cpuinfo_loongarch_linux_decode_chipset(
	const char hardware[restrict static CPUINFO_HARDWARE_VALUE_MAX],
	const char revision[restrict static CPUINFO_REVISION_VALUE_MAX],
	uint32_t cores)
{
	struct cpuinfo_loongarch_chipset chipset =
		cpuinfo_loongarch_linux_decode_chipset_from_proc_cpuinfo_hardware(
			hardware, cores, true);
	if (chipset.vendor == cpuinfo_loongarch_chipset_vendor_unknown) {
		cpuinfo_log_warning(
			"chipset detection failed: /proc/cpuinfo Hardware string did not match known signatures");
	} else {
		cpuinfo_loongarch_fixup_chipset(&chipset, cores);
	}
	return chipset;
}

