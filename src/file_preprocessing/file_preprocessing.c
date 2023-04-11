/**
 * @file   file_preprocessing.c
 * @brief  This file contains the functions that related to the path wrapper
 * that helps the program process files (includes data such as path, file, path
 * and file, extension).
 * @author Matthew C. Lindeman
 * @date   April 11, 2023
 * @bug    None known
 * @todo   Nothing
 */
#include "include/file_preprocessing.h"

/**
 * This function returns the string of the file extension for the given type.
 * @param type - The type of file extension.
 * @return  .\ - The string rep of the file extension.
 */
const char * file_type_to_string(file_type type) {
  switch(type) {
    case PNG:  return "png";
    case PPM:  return "ppm";
    case NONE: return "none";
  }
  return NULL;
}

/**
 * This function initializes a path wrapper with the given path and file.
 * @param         path_file - The path and file name of the path wrapper to be
 * made.
 * @return the_path_wrapper - The inited path wrapper.
 */
path_wrapper init_path_wrapper(const char * path_file) {
  path_wrapper the_path_wrapper = calloc(1, sizeof(struct PATH_WRAPPER_T));
  char * end_of_path = NULL;
  size_t path_len = 0;
  size_t file_name_len = 0;
  if((end_of_path = strrchr(path_file, DIR_DELIMITER))) {
    path_len = end_of_path - path_file;
    the_path_wrapper->path = calloc(path_len + 1, sizeof(char));
    file_name_len = strnlen(end_of_path, MAX_PATH_LEN);
    the_path_wrapper->file_name = calloc(path_len + 1, sizeof(char));
    the_path_wrapper->path_file = calloc(file_name_len + path_len + 1, sizeof(char));
    // + 1 bc end_of_path is at the DIR_DELIMITER
    strncpy(the_path_wrapper->file_name, end_of_path + 1, file_name_len);
    strncpy(the_path_wrapper->path, path_file, path_len);
    strncpy(the_path_wrapper->path_file, path_file, path_len + file_name_len);
    the_path_wrapper->type = find_extention(end_of_path + 1);
  } else {
    file_name_len = strnlen(path_file, MAX_PATH_LEN);
    the_path_wrapper->file_name = calloc(file_name_len + 1, sizeof(char));
    the_path_wrapper->path_file = calloc(file_name_len + 1, sizeof(char));
    strncpy(the_path_wrapper->file_name, path_file, file_name_len);
    strncpy(the_path_wrapper->path_file, path_file, file_name_len);
    the_path_wrapper->path = NULL;
    the_path_wrapper->type = find_extention(path_file);
  }
  return the_path_wrapper;
}

/**
 * This function determines if there is an extension in the given file name and
 * if so returns the file_type (enumeration) of the extension.
 * @param file_name - The name of the file.
 * @return       .\ - The file_type of the extension.
 */
int find_extention(const char * file_name) {
  char * beg_of_ext = NULL;
  if((beg_of_ext = strrchr(file_name, EXT_DELIMITER)))
    for(int i = 0; i < NONE; i++)
      if(!strncmp(file_name + (beg_of_ext - file_name + 1),
            file_type_to_string(i), MAX_PATH_LEN))
        return i;
  return NONE;
}

/**
 * This function debugs a given path wrapper.
 * @param the_path_wrapper - The path wrapper to be debugged.
 * @return             N/a
 */
void debug_path_wrapper(path_wrapper the_path_wrapper) {
  printf("[PATH_WRAPPER]\n");
  printf("path_file: `%s`\n", the_path_wrapper->path_file);
  printf("file_name: `%s`\n", the_path_wrapper->file_name);
  printf("path: `%s`\n", the_path_wrapper->path);
  printf("type: `%s`\n", file_type_to_string(the_path_wrapper->type));
}

/**
 * This function frees a given path wrapper.
 * @param the_path_wrapper - The path wrapper to be freed.
 * @return             N/a
 */
void free_path_wrapper(path_wrapper the_path_wrapper) {
  if(the_path_wrapper) {
    if(the_path_wrapper->path_file)
      free(the_path_wrapper->path_file);
    if(the_path_wrapper->file_name)
      free(the_path_wrapper->file_name);
    if(the_path_wrapper->path)
      free(the_path_wrapper->path);
    free(the_path_wrapper);
    the_path_wrapper = NULL;
  }
}
