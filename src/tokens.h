#include "morpho_plugin.h"

const uint8_t CUSDT_ADDRESS[ADDRESS_LENGTH] = {0xf6, 0x50, 0xC3, 0xd8, 0x8D, 0x12, 0xdB, 0x85, 0x5b, 0x8b, 0xf7, 0xD1, 0x1B, 0xe6, 0xC5, 0x5A, 0x4e, 0x07, 0xdC, 0xC9};

// Aave collateral token addresses.
const uint8_t AWETH_ADDRESS[ADDRESS_LENGTH] = {0xC0, 0x2a, 0xaA, 0x39, 0xb2, 0x23, 0xFE, 0x8D, 0x0A, 0x0e, 0x5C, 0x4F, 0x27, 0xeA, 0xD9, 0x08, 0x3C, 0x75, 0x6C, 0xc2};
const uint8_t AAAVE_ADDRESS[ADDRESS_LENGTH] = {0xc0, 0x0e, 0x94, 0xCb, 0x66, 0x2C, 0x35, 0x20, 0x28, 0x2E, 0x6f, 0x57, 0x17, 0x21, 0x40, 0x04, 0xA7, 0xf2, 0x68, 0x88};
const uint8_t AUNI_ADDRESS[ADDRESS_LENGTH] = {0x1f, 0x98, 0x40, 0xa8, 0x5d, 0x5a, 0xF5, 0xbf, 0x1D, 0x17, 0x62, 0xF9, 0x25, 0xBD, 0xAD, 0xdC, 0x42, 0x01, 0xF9, 0x84};
const uint8_t AUSDC_ADDRESS[ADDRESS_LENGTH] = {0xA0, 0xb8, 0x69, 0x91, 0xc6, 0x21, 0x8b, 0x36, 0xc1, 0xd1, 0x9D, 0x4a, 0x2e, 0x9E, 0xb0, 0xcE, 0x36, 0x06, 0xeB, 0x48};
const uint8_t ADAI_ADDRESS[ADDRESS_LENGTH] = {0x6B, 0x17, 0x54, 0x74, 0xE8, 0x90, 0x94, 0xC4, 0x4D, 0xa9, 0x8b, 0x95, 0x4E, 0xed, 0xeA, 0xC4, 0x95, 0x27, 0x1d, 0x0F};
const uint8_t AFEI_ADDRESS[ADDRESS_LENGTH] = {0x95, 0x6F, 0x47, 0xF5, 0x0A, 0x91, 0x01, 0x63, 0xD8, 0xBF, 0x95, 0x7C, 0xf5, 0x84, 0x6D, 0x57, 0x3E, 0x7f, 0x87, 0xCA};
const uint8_t AWBTC_ADDRESS[ADDRESS_LENGTH] = {0x22, 0x60, 0xFA, 0xC5, 0xE5, 0x54, 0x2a, 0x77, 0x3A, 0xa4, 0x4f, 0xBC, 0xfe, 0xDf, 0x7C, 0x19, 0x3b, 0xc2, 0xC5, 0x99};
const uint8_t AUSDT_ADDRESS[ADDRESS_LENGTH] = {0xdA, 0xC1, 0x7F, 0x95, 0x8D, 0x2e, 0xe5, 0x23, 0xa2, 0x20, 0x62, 0x06, 0x99, 0x45, 0x97, 0xC1, 0x3D, 0x83, 0x1e, 0xc7};

const token_info_t tokens_list[] = {
    // Compound collateral address and corresponding token info.
    {{0x4D, 0xdc, 0x2D, 0x19, 0x39, 0x48, 0x92, 0x6D, 0x02, 0xf9, 0xB1, 0xfE, 0x9e, 0x1d, 0xaa, 0x07, 0x18, 0x27, 0x0E, 0xD5}, "WETH ", 18},
    {{0x70, 0xe3, 0x6f, 0x6B, 0xF8, 0x0a, 0x52, 0xb3, 0xB4, 0x6b, 0x3a, 0xF8, 0xe1, 0x06, 0xCC, 0x0e, 0xd7, 0x43, 0xE8, 0xe4}, "COMP ", 18},
    {{0x35, 0xA1, 0x80, 0x00, 0x23, 0x0D, 0xA7, 0x75, 0xCA, 0xc2, 0x48, 0x73, 0xd0, 0x0F, 0xf8, 0x5B, 0xcc, 0xde, 0xD5, 0x50}, "UNI ", 18},
    {{0x39, 0xAA, 0x39, 0xc0, 0x21, 0xdf, 0xba, 0xE8, 0xfa, 0xC5, 0x45, 0x93, 0x66, 0x93, 0xaC, 0x91, 0x7d, 0x5E, 0x75, 0x63}, "USDC ", 6},
    {{0x5d, 0x3a, 0x53, 0x6E, 0x4D, 0x6D, 0xbD, 0x61, 0x14, 0xcc, 0x1E, 0xad, 0x35, 0x77, 0x7b, 0xAB, 0x94, 0x8E, 0x36, 0x43}, "DAI ", 18},
    {{0x77, 0x13, 0xDD, 0x9C, 0xa9, 0x33, 0x84, 0x8F, 0x68, 0x19, 0xF3, 0x8B, 0x83, 0x52, 0xD9, 0xA1, 0x5E, 0xA7, 0x3F, 0x67}, "FEI ", 18},
    {{0xcc, 0xF4, 0x42, 0x9D, 0xB6, 0x32, 0x2D, 0x5C, 0x61, 0x1e, 0xe9, 0x64, 0x52, 0x7D, 0x42, 0xE5, 0xd6, 0x85, 0xDD, 0x6a}, "WBTC ", 8},
    {{0xf6, 0x50, 0xC3, 0xd8, 0x8D, 0x12, 0xdB, 0x85, 0x5b, 0x8b, 0xf7, 0xD1, 0x1B, 0xe6, 0xC5, 0x5A, 0x4e, 0x07, 0xdC, 0xC9}, "USDT ", 6},
    // Aave token info.
    {{0xc0, 0x0e, 0x94, 0xCb, 0x66, 0x2C, 0x35, 0x20, 0x28, 0x2E, 0x6f, 0x57, 0x17, 0x21, 0x40, 0x04, 0xA7, 0xf2, 0x68, 0x88}, "AAVE ", 18}};