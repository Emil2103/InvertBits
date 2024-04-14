#include <iostream>
#include <thread>
#include <chrono>

uint8_t CreateMask(std::size_t numberOfOnes, std::size_t firstN){
    uint8_t mask = 0b00000000;
    for (uint8_t i = firstN; i < firstN + numberOfOnes; ++i) {
        mask |= (1 << (8 - i));
    }
    return mask;
}


void invertSelectedBits(void* mem, std::size_t length, uint8_t mask) {
    unsigned char* bytes = static_cast<unsigned char*>(mem);
    for (std::size_t i = 0; i < length; ++i) {
        bytes[i] ^= mask;
  }
}

int main() {
    unsigned char memory[] = {0b10101010, 0b11001100, 0b11010000};
    std::size_t length = sizeof(memory);
    
    std::cout << "Введите с какого бита вы хотите инвертировать последовательность: ";
    std::size_t firstnumber;
    std::cin >> firstnumber;
    
    std::cout << "Введите количество бит, которое хотите инвертировать: ";
    std::size_t bit_length;
    std::cin >> bit_length;
    
    auto start = std::chrono::high_resolution_clock::now();
    uint8_t bitmask = CreateMask(bit_length, firstnumber);
    invertSelectedBits(memory, length, bitmask);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Время выполнения программы: " << duration.count() << " миллисекунд" << std::endl;
    
    for (std::size_t i = 0; i < length; ++i) {
        std::cout << "Byte " << i << ": " << std::bitset<8>(memory[i]) << std::endl;
    }

    return 0;
}
