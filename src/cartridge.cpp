#include <iostream>
#include <fstream>

#include "cartridge.h"

static Cartridge cartridge;

std::string print_string(char char_array[]) {
    std::string str;

    int i = 0;
    while (char_array[i] != '\0') {
        str += char_array[i];
        i++;
    }

    return str;
}

std::string get_license() {
    if (cartridge.header->new_license_code <= 0xA4) {
        return NEW_LICENSE_CODES.at(cartridge.header->new_license_code);
    }

    return "UNKNOWN";
}

std::string get_type() {
    if (cartridge.header->cartridge_type <= 0xFF) {
        return CARTRIDGE_TYPES.at(cartridge.header->cartridge_type);
    }

    return "UNKNOWN";
}

std:: string get_rom_size() {
    return ROM_SIZES.at(cartridge.header->rom_size);
}

std::string get_ram_size() {
    return RAM_SIZES.at(cartridge.header->ram_size);
}

std::string get_dest_code() {
    return DEST_CODES.at(cartridge.header->destination_code);
}

bool load_cartridge(const std::string& cart) {
    std::cout << "hi from load cart" << std::endl;

    std::ifstream cart_file;
    cart_file.open(cart, std::ios::in | std::ios::binary);

    // check if rom opened correctly
    if (!cart_file.is_open()) {
        std::cerr << "Error! Failed to open: " << cart << std::endl;
        return false;
    }

    // get rom filename
    std::string delim = "/";
    cartridge.filename = cart.substr(cart.find(delim) + 1, cart.size());

    std::cout << "Opened: " << cartridge.filename << std::endl;

    // get rom size
    cart_file.seekg(0, std::ios::end);
    cartridge.rom_size = cart_file.tellg();

    std::cout << "Size of file: " << cartridge.rom_size << " bytes" << std::endl;

    // get rom data
    cart_file.seekg(0);
    cartridge.rom_data = static_cast<uint8_t *>(malloc(cartridge.rom_size));
    cart_file.read((char*)cartridge.rom_data, cartridge.rom_size);

    cart_file.close();

    // get rom header
    cartridge.header = (rom_header*)(cartridge.rom_data + 0x0100);
    cartridge.header->new_license_code = cartridge.header->new_license_code >> 8;

    // print cartridge information
    std::cout << "Cartridge Loaded: " << std::endl;
    std::cout << "\t Title      : " << print_string(cartridge.header->title) << std::endl;
    std::cout << "\t Type       : " << std::hex << (int)cartridge.header->cartridge_type << " (" << get_type() << ")" << std::endl;
    std::cout << "\t ROM Size   : " << get_rom_size() << std::endl;
    std::cout << "\t RAM Size   : " << get_ram_size() << std::endl;
    std::cout << "\t LIC Code   : " << std::hex << (int)cartridge.header->new_license_code << " (" << get_license() << ")" << std::endl;
    std::cout << "\t ROM Vers   : " << std::hex << (int)cartridge.header->rom_version << std::endl;
    std::cout << "\t DEST Code  : " << std::hex << (int)cartridge.header->destination_code << " (" << get_dest_code() << ")" << std::endl;

    // checksum incorrect, maybe because bad rom?
//    uint8_t checksum = 0;
//    for (uint16_t address = 0x0134; address <= 0x014C; address++) {
//        checksum = checksum - cartridge.rom_data[address] - 1;
//    }
//
//    if (checksum == cartridge.header->header_checksum) {
//        std::cout << "\t Checksum:  PASSED" << std::endl;
//    }


    std::cout << "Cartridge loaded successfully!" << std::endl;

    return true;
}

