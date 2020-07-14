/** 
 * Copyright (C) 2020 Muhamed Krasniqi. All rights reserved
 * muhamed.krasniqi@student.uni-pr.edu
 *
 * @file  patient.c
 *
 * @brief Implements functions for the Person_t type file serialization 
 * 
 * @author (MK) Muhamed Krasniqi
 * @date   $Date: Sun May 31, 21:48:27:59 WEST 2020 $
 */

#ifndef _Patient_H
#define _Patient_H 1

#include <stdio.h>
#include "str_serialize.h"

typedef struct _Patient
{
  CString_t personal_nr;
  CString_t name;
  CString_t surname;
  CString_t age;
  CString_t address;
  CString_t testing_date;
} Patient_t;

int Patient_get   (Patient_t *const patient);
void Patient_init  (Patient_t *const patient);
void Patient_free (Patient_t *const patient);
int Patient_write (FILE *fp, /*@null@*/  const Patient_t *const patient);
int Patient_read  (FILE *fp, /*@null@*/       Patient_t *const patient);
void Patient_print(Patient_t *const patient);

#endif /* _Patient_H */