/**
* Copyright (C) 2020 Muhamed Krasniqi. All rights reserved
 * muhamed.krasniqi@student.uni-pr.edu
 *
 * @file  main.c
 *
 * @brief Implements the main function
 * 
 * @author (IS) Muhamed Krasniqi (muhamed.krasniqi2@student.uni-pr.edu)
 * @date   $Date: Wed June 03, 20:27:59 2020 $
 */

#define _POSIX_SOURCE

#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "opt.h"
#include "patient.c"

#define BUFF_LEN (1024)

int main (int argc, char *argv [])
{
   appOption   opt;
   Patient_t   patient;
  
  /* initialize the patient object */
  Patient_init(&patient);
  
  /* initialize the application option object */
  opt_init (&opt);
  
  if ((char) opt_proc (argc, argv, &opt) == OPT_PROC_ERROR)
    {
      opt_free (&opt);
      return EXIT_FAILURE;
    }

  /* open a file */
  printf ("\nThe file '%s' is opening ... ", opt.f_name);
  
  if ((opt.fp = fopen (opt.f_name, "a+")) == NULL)
    {
      printf ("\nError opening the file: '%s' [Error string: '%s']",
              opt.f_name, strerror (errno));
      opt_free (&opt);
      return -1;
    }
  
  printf (" done");

  if (opt.append == (char) OPT_SPECIFIED)
    {
      /* Get the patient data from std input */
      if (Patient_get (&patient) == 0)
        {
          printf ("\nError getting the patient ");
          (void) opt_free (&opt);
          return -1;
        }
      /* Append the patient to the file */
      if (Patient_write (opt.fp, &patient) == 0)
        {
          printf ("\nError writing the patient with personal number: %s", patient.personal_nr.p_str);
          (void) opt_free    (&opt);
          (void) Patient_free (&patient);
          return -1;
        }
    }
  if (opt.list == (char) OPT_SPECIFIED)
    {
      /* list all patients */
      printf("\n\nList of patients:");
      while(Patient_read (opt.fp, &patient) != SER_EOF) {
        Patient_print(&patient);
      }
      (void) Patient_free (&patient);
    }  

  /* release all resources */ 
  (void) opt_free (&opt);
  
  printf ("\nBye\n");
   
  return 0;
}
