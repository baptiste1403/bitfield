#ifndef BITFIELD_H
#define BITFIELD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    size_t nb_bits;
    size_t nb_bytes;
    unsigned char* data;
} bitfield_t;

void print_bitfield(const bitfield_t* bf);
bool set_bit(bitfield_t* bf, size_t index, bool value);
bool add_bit(bitfield_t* bf, bool value);
bool get_bit(const bitfield_t* bf, size_t index);
void free_bitfield(bitfield_t* bf);

#ifdef BITFIELD_IMPLEMENTATION

void print_bitfield(const bitfield_t* bf) {
    for(size_t i = 0; i < bf->nb_bytes; i++) {
        size_t nb_bits_not_printed = bf->nb_bits - i*8;
        size_t nb_bit_not_printed_in_bytes = nb_bits_not_printed < 8 ? nb_bits_not_printed : 8;
        for(size_t j = 0; j < nb_bit_not_printed_in_bytes; j++) {
            char res = (bf->data[i] & (1 << j));
            printf("%c", (res == 0) ? '0' : '1');
        }
        printf(" ");
    }
    printf("\n");
}

bool set_bit(bitfield_t* bf, size_t index, bool value) {
    if(bf->nb_bits <= index) {
        if((bf->nb_bytes*8) <= index) {
            size_t new_byte_size = (index / 8UL) + 1;
            bf->data = realloc(bf->data, new_byte_size * sizeof(unsigned char));
            memset(bf->data + bf->nb_bytes, 0, new_byte_size - bf->nb_bytes);
            bf->nb_bytes = new_byte_size;
        }
        bf->nb_bits = index+1;
    }

    size_t array_index = index/8;
    size_t shift = index%8;
    if(value) {
        bf->data[array_index] |= (((unsigned char)1) << shift);
    } else {
        bf->data[array_index] &= ~(((unsigned char)1) << shift);
    }
}

bool add_bit(bitfield_t* bf, bool value) {
    size_t index = bf->nb_bits;
    set_bit(bf, index, value);
    return index;
}

bool get_bit(const bitfield_t* bf, size_t index) {
    if(bf->nb_bits <= index) return false;
    size_t array_index = index/8;
    size_t shift = index%8;

    return (bf->data[array_index] & (1UL << shift));
}

void free_bitfield(bitfield_t* bf) {
    free(bf->data);
    *bf = (bitfield_t){0};
}
#endif // BITFIELD_IMPLEMENTATION
#endif // BITFIELD_H