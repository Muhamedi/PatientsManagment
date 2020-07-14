/**
 * Copyright (C) 2020 Muhamed Krasniqi. All rights reserved
 * Prishtina, Kosova. muhamed.krasniqi2@student.uni-pr.edu
 *
 * @file  patient.c
 *
 * @brief Implements functions for the Person_t type file serialization 
 * 
 * @author (IS) Muhamed Krasniqi (muhamed.krasniqi2@student.uni-pr.edu)
 * @date   $Date: Wed June 03, 20:27:59 2020 $
 */

#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "str_serialize.h"
#include "patient.h"

#define MAXPATIENTSTRLEN (512)

/***************************************************************************//** 
 * @brief Gets the input data from stdin and saves them to the prop 
 *
 * @param[in/out] c_str - the pointer to the c_str object 
 * @param[in] isNumProp - if true then the input string should be a number
 * @param[in] prop_name - property name to get the input data for
 *
 * @retval 0 in case an error was occured
 * @retval > 0 success
 ******************************************************************************/

static int get_prop (CString_t *c_str, bool isNumProp, const char *prop_name)
{
  char  buff [MAXPATIENTSTRLEN];
  char *r_str  = NULL; 
  retry: 
  printf ("\n\tplease insert the %s: ", prop_name);
  r_str  = fgets (&buff[0], MAXPATIENTSTRLEN, stdin);
  if(isNumProp) {
    if(!isNumber(r_str)) {
       printf ("\n\t%s should be a number.", prop_name);
       goto retry;
    }
  }

  return str_init (r_str, c_str);
}

/***************************************************************************//** 
 * @brief Asks the user for all patient's data from the stdin 
 *
 * @param[in/out] patient - the pointer to the patient object
 *
 * @retval 0 in case an error was occured
 * @retval 1 success
 ******************************************************************************/
int Patient_get (Patient_t *const patient)
{
  /* the patient's object  */
  patient->personal_nr.p_str = NULL;
  patient->name.p_str=NULL;
  patient->surname.p_str = NULL;
  patient->age.p_str=NULL;
  patient->address.p_str=NULL;  
  patient->testing_date.p_str=NULL;  

  printf ("\nPlease insert the patient's information: ");

  if (get_prop  (&patient->personal_nr, true, "personal_nr") == 0)
    {
      perror("Initianization of personal_nr property failed");
      Patient_free(patient);
      return 0;
    }
  
  if (get_prop  (&patient->name, false, "name") == 0)
    {
      perror("Initianization of name property failed");
      Patient_free(patient);
      return 0;
    }
  
  if (get_prop  (&patient->surname, false, "surname") == 0)
    {
      perror("Initianization of surname property failed");
      Patient_free(patient);
      return 0;
    }
  
  if (get_prop  (&patient->age, true, "age") == 0)
    {
      perror("Initianization of email property failed");
      Patient_free(patient);
      return 0;
    }

  if (get_prop  (&patient->address, false, "address") == 0)
    {
      perror("Initianization of address property failed");
      Patient_free(patient);
      return 0;
    }

  if (get_prop  (&patient->testing_date, false, "testing_date") == 0)
    {
      perror("Initianization of testing_date property failed");
      Patient_free(patient);
      return 0;
    }

  return 1;
}

/***************************************************************************//** 
 * @brief Initialize a Patient_t object
 *
 * @param[in] fp    - file pointer to Patient_t object
 *
 * @retval void
 ******************************************************************************/
void Patient_init  (Patient_t *const patient)
{
  if (patient == NULL)
    {
      return;
    }

  patient->personal_nr.p_str = NULL;
  patient->name.p_str = NULL;
  patient->surname.p_str=NULL;
  patient->age.p_str = NULL;
  patient->address.p_str=NULL;
  patient->testing_date.p_str=NULL;
}

/***************************************************************************//** 
 * @brief Release an object of type Patient_t
 *
 * @param[in,out]     Patient_t patient - the object to be released
 *
 *
 * @retval void
 ******************************************************************************/
void Patient_free(Patient_t *const patient)
{
    if(patient->personal_nr.p_str != NULL)
    {
        free(patient->personal_nr.p_str);
        patient->personal_nr.p_str = NULL;
    }
    if(patient->name.p_str != NULL)
    {
        free(patient->name.p_str);
        patient->name.p_str = NULL;
    }

    if(patient->surname.p_str != NULL)
    {
        free(patient->surname.p_str);
        patient->surname.p_str = NULL;
    }

    if(patient->age.p_str != NULL)
    {
        free(patient->age.p_str);
        patient->age.p_str = NULL;
    }

    if(patient->address.p_str != NULL)
    {
        free(patient->address.p_str);
        patient->address.p_str = NULL;
    }

    if(patient->testing_date.p_str != NULL)
    {
        free(patient->testing_date.p_str);
        patient->testing_date.p_str = NULL;
    }
}

/***************************************************************************//** 
 * @brief Writes a Patient_t patient object input into the file 
 *
 * First the four (4) bytes will be written indicating the length of the
 * string to be written, and then the string itself will be written for each of the 
 * patient's properties.
 *
 * @param[in,out] fp    - file pointer
 * @param[in]     patient - the input Patient_t
 *
 * @retval 0  in case an error was occured
 * @retval > 0 number of bytes written in the file
 ******************************************************************************/
int Patient_write (FILE *fp, /*@null@*/  const Patient_t *const patient)
{
  int status = 0;

  if (patient == NULL)
    {
      return status;
    }

  status = (int) str_write (fp, &patient->personal_nr);

  if (status == 0)
    {
       printf ("\nError writing patient personal_nr '%s' to the file", patient->personal_nr.p_str);
       return status;
    }

  status = (int) str_write (fp, &patient->name);

  if (status == 0)
    {
       printf ("\nError writing patient name '%s' to the file", patient->name.p_str);
       return status;
    }

  status = (int) str_write (fp, &patient->surname);

  if (status == 0)
    {
       printf ("\nError writing patient surname '%s' to the file", patient->surname.p_str);
       return status;
    }

  status = (int) str_write (fp, &patient->age);

  if (status == 0)
    {
       printf ("\nError writing patient age '%s' to the file", patient->age.p_str);
       return status;
    }

  status = (int) str_write (fp, &patient->address);

  if (status == 0)
    {
       printf ("\nError writing patient address '%s' to the file", patient->address.p_str);
       return status;
    }

  status = (int) str_write (fp, &patient->testing_date);

  if (status == 0)
    {
       printf ("\nError writing patient testing_date '%s' to the file", patient->testing_date.p_str);
       return status;
    }

  return status;
}

/***************************************************************************//** 
 * @brief Reads an Patient_t patient object from the file 
 *
 * First the four (4) bytes will be read, which indicate the length of the
 * string to be read, and then the string itself will be read for each of the 
 * patient's properties.
 *
 * @param[in,out] fp  - file pointer
 * @param[out]    patient - pointer to the patient object to be read Patient_t  
 *
 * @retval 0             in case an error was occured
 * @retval > 0            number of bytes read out from the file
 ******************************************************************************/
int Patient_read (FILE *fp, /*@null@*/ Patient_t *const patient)
{
  int   status = 0;

  if (fp == NULL || patient == NULL) 
    {
      return status;
    }
  
  status = (int) str_read (fp, &patient->personal_nr);
  if (status == 0)
    {
       printf ("\nError reading patient's personal_nr from the file");
       return status;
    }
  
  status = (int) str_read (fp, &patient->name);
  if (status == 0)
    {
       printf ("\nError reading patient's name from the file");
       return status;
    }
  
  status = (int) str_read (fp, &patient->surname);
  if (status == 0)
    {
       printf ("\nError reading patient's surname from the file");
       return status;
    }
  
  status = (int) str_read (fp, &patient->age);
  if (status == 0)
    {
       printf ("\nError reading patient's age from the file");
       return status;
    }

  status = (int) str_read (fp, &patient->address);
  if (status == 0)
    {
       printf ("\nError reading patient's address from the file");
       return status;
    }

  status = (int) str_read (fp, &patient->testing_date);
  if (status == 0)
    {
       printf ("\nError reading patient's testing_date from the file");
       return status;
    }

  return status;
}

/***************************************************************************//** 
 * @brief Prints the data of the patient properties
 *
 * Print the properties of the Patient_t object
 *
 * @param[in]    patient - pointer to the patient object to be read Patient_t  
 * 
 * @retval void
 ******************************************************************************/

void Patient_print(Patient_t *const patient) {
   printf("\n############################################");
   printf("\nPersonal number: %s", patient->personal_nr.p_str);
   printf("Name: %s", patient->name.p_str);
   printf("Surname: %s", patient->surname.p_str);
   printf("Age: %s", patient->age.p_str);
   printf("Address: %s", patient->address.p_str);
   printf("Testing date: %s", patient->testing_date.p_str);
}
