#ifndef GAMEBOY_EMULATOR_CARTRIDGE_H
#define GAMEBOY_EMULATOR_CARTRIDGE_H

#include <string>
#include <unordered_map>

static const std::unordered_map<uint8_t, std::string> CARTRIDGE_TYPES = {
        {0x00, "ROM ONLY"},
        {0x01, "MBC1"},
        {0x02, "MBC1+RAM"},
        {0x03, "MBC1+RAM+BATTERY"},
        {0x05, "MBC2"},
        {0x06, "MBC2+BATTERY"},
        {0x08, "ROM+RAM"},
        {0x09, "ROM+RAM+BATTERY"},
        {0x0B, "MMM01"},
        {0x0C, "MMM01+RAM"},
        {0x0D, "MMM01+RAM+BATTERY"},
        {0x0F, "MBC3+TIMER+BATTERY"},
        {0x10, "MBC3+TIMER+RAM+BATTERY"},
        {0x11, "MBC3"},
        {0x12, "MBC3+RAM"},
        {0x13, "MBC3+RAM+BATTERY"},
        {0x19, "MBC5"},
        {0x1A, "MBC5+RAM"},
        {0x1B, "MBC5+RAM+BATTERY"},
        {0x1C, "MBC5+RUMBLE"},
        {0x1D, "MBC5+RUMBLE+RAM"},
        {0x1E, "MBC5+RUMBLE+RAM+BATTERY"},
        {0x20, "MBC6"},
        {0x22, "MBC7+SENSOR+RUMBLE+RAM+BATTERY"},
        {0xFC, "POCKET CAMERA"},
        {0xFD, "BANDAI TAMA5"},
        {0xFE, "HuC3"},
        {0xFF, "HuC1+RAM+BATTERY"}
};

static const std::unordered_map<uint16_t , std::string> NEW_LICENSE_CODES = {
        {0x00, "None"},
        {0x01, "Nintendo R&D1"},
        {0x08, "Capcom"},
        {0x13, "Electronic Arts"},
        {0x18, "Hudson Soft"},
        {0x19, "b-ai"},
        {0x20, "kss"},
        {0x22, "pow"},
        {0x24, "PCM Complete"},
        {0x25, "san-x"},
        {0x28, "Kemco Japan"},
        {0x29, "seta"},
        {0x30, "Viacom"},
        {0x31, "Nintendo"},
        {0x32, "Bandai"},
        {0x33, "Ocean/Acclaim"},
        {0x34, "Konami"},
        {0x35, "Hector"},
        {0x37, "Taito"},
        {0x38, "Hudson"},
        {0x39, "Banpresto"},
        {0x41, "Ubi Soft"},
        {0x42, "Atlus"},
        {0x44, "Malibu"},
        {0x46, "angel"},
        {0x47, "Bullet-Proof"},
        {0x49, "irem"},
        {0x50, "Absolute"},
        {0x51, "Acclaim"},
        {0x52, "Activision"},
        {0x53, "American sammy"},
        {0x54, "Konami"},
        {0x55, "Hi tech entertainment"},
        {0x56, "LJN"},
        {0x57, "Matchbox"},
        {0x58, "Mattel"},
        {0x59, "Milton Bradley"},
        {0x60, "Titus"},
        {0x61, "Virgin"},
        {0x64, "LucasArts"},
        {0x67, "Ocean"},
        {0x69, "Electronic Arts"},
        {0x70, "Infogrames"},
        {0x71, "Interplay"},
        {0x72, "Broderbund"},
        {0x73, "sculptured"},
        {0x75, "sci"},
        {0x78, "THQ"},
        {0x79, "Accolade"},
        {0x80, "misawa"},
        {0x83, "lozc"},
        {0x86, "Tokuma Shoten Intermedia"},
        {0x87, "Tsukuda Original"},
        {0x91, "Chunsoft"},
        {0x92, "Video system"},
        {0x93, "Ocean/Acclaim"},
        {0x95, "Varie"},
        {0x96, "Yonezawa/s’pal"},
        {0x97, "Kaneko"},
        {0x99, "Pack in soft"},
        {0xA4, "Konami (Yu-Gi-Oh!)"}
};

static const std::unordered_map<uint8_t, std::string> ROM_SIZES = {
        {0x00, "32 KB"},
        {0x01, "64 KB"},
        {0x02, "128 KB"},
        {0x03, "256 KB"},
        {0x04, "512 KB"},
        {0x05, "1 MB"},
        {0x06, "2 MB"},
        {0x07, "4 MB"},
        {0x08, "8 MB"},
        {0x52, "1.1 MB"},
        {0x53, "1.2 MB"},
        {0x54, "1.5 MB"}
};

static const std::unordered_map<uint8_t, std::string> RAM_SIZES = {
        {0x00, "0 KB"},
        {0x01, "Unused"},
        {0x02, "8 KB"},
        {0x03, "32 KB"},
        {0x04, "128 KB"},
        {0x05, "64 KB"}
};

static const std::unordered_map<uint8_t, std::string> DEST_CODES = {
        {0x00, "Japan"},
        {0x01, "Overseas"}
};

// address range 0x0100 - 0x014F
struct rom_header {
    uint8_t entry_point[0x4]; // 0x0100 - 0x0103
    uint8_t nintendo_logo[0x30]; // 0x0104 - 0x0133

    char title[16]; // 0x0134 - 0x0143
    uint16_t new_license_code; // 0x0144 - 0x0145
    uint8_t sgb_flag; // 0x0146
    uint8_t cartridge_type; // 0x0147
    uint8_t rom_size; // 0x0148
    uint8_t ram_size; // 0x0149
    uint8_t destination_code; // 0x014A
    uint8_t old_license_code; // 0x014B
    uint8_t rom_version; // 0x014C
    uint8_t header_checksum; // 0x014D
    uint16_t global_checksum; // 0x014E - 0x014F
};

struct Cartridge {
    std::string filename;
    uint32_t rom_size;
    uint8_t* rom_data;
    rom_header* header;
};

bool load_cartridge(const std::string& cart);


#endif //GAMEBOY_EMULATOR_CARTRIDGE_H
