/**
 * @file   file_preprocessing.h
 * @brief  This file contains the function definitions for file_preprocessing.c.
 * @author Matthew C. Lindeman
 * @date   April 11, 2023
 * @bug    None known
 * @todo   Nothing
 */
#ifndef FIL_H
#define FIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIR_DELIMITER '/'
#define EXT_DELIMITER '.'
#define MAX_PATH_LEN 1024

typedef enum {
  PNG,
  PPM,
  NONE,
} file_type;

const char * file_type_to_string(file_type type);

typedef struct PATH_WRAPPER_T {
  char * path_file;
  char * path;
  char * file_name;
  file_type type;
} * path_wrapper;

path_wrapper init_path_wrapper(const char * path_file);
int find_extention(const char * file_name);
void debug_path_wrapper(path_wrapper the_path_wrapper);
void free_path_wrapper(path_wrapper the_path_wrapper);

#endif
