#define BITFIELD_IMPLEMENTATION
#include "bitfield.h"

int main(void) {
    bitfield_t bf = {0};
    add_bit(&bf, false);
    print_bitfield(&bf);
    free_bitfield(&bf);
    return 0;
}