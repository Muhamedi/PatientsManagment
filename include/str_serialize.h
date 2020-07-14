/** 
 * Copyright (C) 2020 Muhamed Krasniqi. All rights reserved
 * muhamed.krasniqi@student.uni-pr.edu
 *
 * @file  str_serialize.c
 *
 * @brief Implements functions for the string file serialization 
 * 
 * @author (MK) Muhamed Krasniqi
 * @date   $Date: Sun May 31, 21:48:27:59 WEST 2020 $
 */

#ifndef _STR_SERIALIZE_H
#define _STR_SERIALIZE_H 1

#include <stdio.h>

#define SER_EOF         -2
#define SER_ALLOC_ERROR -1
#define SER_INT_LEN      4

typedef struct _CString
{
  int   length;
  char *p_str;
} CString_t;

int str_len   (          /*@null@*/ const char      *      str);
int str_init  (          /*@null@*/ const char      *      str, CString_t *const c_str);
int str_write (FILE *fp, /*@null@*/ const CString_t *const c_str);
int str_read  (FILE *fp, /*@null@*/       CString_t *const c_str);
bool isNumber(const char *input);

#endif /* _STR_SERIALIZE_H */

 
