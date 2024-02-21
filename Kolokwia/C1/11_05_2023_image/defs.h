//
// Created by Bartosz on 12.05.2023.
//

#ifndef KOL_11_05_DEFS_H
#define KOL_11_05_DEFS_H

#include <stdint.h>

enum error_code_t {
    ERROR_CODE_OK = 0,
    ERROR_CODE_INCORRECT_PARAMETERS,
    ERROR_CODE_FILE_NOT_EXISTS,
    ERROR_CODE_FILE_CORRUPTED,
    ERROR_CODE_COULDNT_CREATE_FILE,
    ERROR_CODE_FAILED_TO_ALLOCATE_MEMORY
};

struct rle_t {
    uint8_t val;
    uint32_t len;
};

enum error_code_t read_image(uint8_t **pimg, int *pwidth, int *pheight, const char *fname);
void show_array(const uint8_t *img, int width, int height);
enum error_code_t encode_array(struct rle_t **out, int *n, const uint8_t *img, int width, int height);


#endif //KOL_11_05_DEFS_H
