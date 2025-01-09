#include "revolution/sc/scapi.h"
#include <revolution/SC.h>

const char *countryIdToISOA2[] = {
    NULL, "JP", NULL, NULL, NULL, NULL, NULL, NULL, "AI", "AG", "AR", "AW", "BS", "BB",
    "BZ", "BO", "BR", "VG", "CA", "KY", "CL", "CO", "CR", "DM", "DO", "EC", "SV", "GF",
    "GD", "GP", "GT", "GY", "HT", "HN", "JM", "MQ", "MX", "MS", "AN", "NI", "PA", "PY",
    "PE", "KN", "LC", "VC", "SR", "TT", "TC", "US", "UY", "VI", "VE", NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, "AL", "AU", "AT", "BE", "BA", "BW",
    "BG", "HR", "CY", "CZ", "DK", "EE", "FI", "FR", "DE", "GR", "HU", "IS", "IE", "IT",
    "LV", "LS", "LI", "LT", "LU", "MK", "MT", "ME", "MZ", "NA", "NL", "NZ", "NO", "PL",
    "PT", "RO", "RU", "RS", "SK", "SI", "ZA", "ES", "SZ", "SE", "CH", "TR", "GB", "ZM",
    "ZW", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, "TW", NULL, NULL, NULL, NULL, NULL, NULL, NULL, "KR", NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, "HK", "MO", NULL, NULL, NULL, NULL, NULL, NULL, "ID", "SG",
    "TH", "PH", "MY", NULL, NULL, NULL, "CN", NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    "AE", "IN", "EG", "OM", "QA", "KW", "SA", "SY", "BH", "JO"
};

const char *SCUTILGetISOCountryCodeA2(int id) {
    u32 new_id = SCGetSimpleAddressID(id);
    if (new_id + 0x10000 == 0xFFFF)
        return NULL;
    if ((new_id >>= 24) >= 178)
        return NULL;
    return countryIdToISOA2[new_id];
}
