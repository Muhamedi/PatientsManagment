/**
 * Copyright (C) 2020 Muhamed Krasniqi. All rights reserved
 * muhamed.krasniqi@student.uni-pr.edu
 *
 * @file  opt.c
 *
 * @brief Implements functions for the option processing
 * 
 * @author (MK) Muhamed Krasniqi
 * @date   $Date: Sun May 31, 21:48:27:59 WEST 2020 $
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>
#include <getopt.h>
#include <unistd.h>
#include <libgen.h>

#include "opt.h"

extern char *optarg;
extern int   optopt;

/***************************************************************************//** 
 * @brief Private member - checks if the options are OK 
 *
 * This functions checks the specified options
 *
 * @param[in,out] aoObj - pointer to the application's options object
 *
 * @retval 
 ******************************************************************************/
int opt_check__  (/*@out@*/appOption *aoObj)
{
  int res = (int) OPT_SUCCESS;

  if (aoObj == NULL)
    {
      return (int) OPT_PROC_ERROR;
    }
  
  if (aoObj->interactive == OPT_SPECIFIED &&
      (aoObj->append == OPT_SPECIFIED || aoObj->list == OPT_SPECIFIED)
     )
    {
      printf ("\nInvalid option combination: interactiv ");
      if (aoObj->append == OPT_SPECIFIED)
        {
          printf (" and append ");
        }
      else
        {
          printf (" and list ");
        }

      printf (" is not allowed\n");
      res = (int) OPT_PROC_ERROR;
    }

  if (aoObj->f_name == NULL)
    {
      printf ("\nThe file option (-f f_name) has to be defined\n");
      res = (int) OPT_PROC_ERROR;
    }

  return res;
}

/***************************************************************************//** 
 * @brief Initializes the data structure describing the application options 
 *
 * This functions initializes the data structure that describes the specified
 * application options
 *
 * @param[in,out] aoObj - pointer to the application's options object
 *
 * @retval void
 ******************************************************************************/
void opt_init  (/*@out@*/appOption *aoObj)
{
  if (aoObj == NULL)
    {
      return;
    }
  
  aoObj->append      = OPT_NOTSPECIFIED;
  aoObj->list        = OPT_NOTSPECIFIED;
  aoObj->interactive = OPT_NOTSPECIFIED;
  aoObj->f_name      = NULL;
  aoObj->fp          = NULL;
}

/***************************************************************************//** 
 * @brief Frees the data structure describing the application options 
 *
 * This functions frees the data structure that describes the specified
 * application options
 *
 * @param[in,out] aoObj - pointer to the application's options object
 *
 * @retval void
 ******************************************************************************/
void opt_free  (/*@out@*/appOption *aoObj)
{
  if (aoObj == NULL)
    {
      return;
    }

  if (aoObj->f_name == NULL || aoObj->fp == NULL)
    {
      return;
    }
  
  aoObj->append      = OPT_NOTSPECIFIED;
  aoObj->list        = OPT_NOTSPECIFIED;
  aoObj->interactive = OPT_NOTSPECIFIED;

  if (aoObj->f_name != NULL)
    {
      free ((void *) aoObj->f_name);
      aoObj->f_name = NULL;
    }

  if (aoObj->fp != NULL)
    {
      (void) fclose (aoObj->fp);
      aoObj->fp = NULL;
    }
}

/***************************************************************************//** 
 * @brief Handles the passed options
 *
 * This functions frees the data structure that describes the specified
 * application options
 *
 * @param[in,out] aoObj - pointer to the application's options object
 *
 * @retval OPT_SUCCESS
 * @retval OPT_PROC_ERROR
 ******************************************************************************/
int opt_proc (int argc, char *argv [], /*@out@*/appOption *aoObj)
{
  int n_opt = 0;

  if (aoObj == NULL)
    {
      return (int) OPT_PROC_ERROR;
    }
  
  /* while ((n_opt = getopt (argc, argv, OPT_PATTERN)) != -1) */
  while ((n_opt = getopt (argc, argv, "af:l")) != -1)
    {
      printf ("\nThe option -%c [%s]", n_opt, argv [1]);
      switch (n_opt)
        {
        case 'f':
          printf ("\nThe file option has been detected: %s", optarg);
          if (opt_strclone (&aoObj->f_name, optarg) == (int) OPT_NULLPOINTER)
            {
              return (int) OPT_PROC_ERROR;
            }
          printf ("\nThe filename is: %s", aoObj->f_name);
          break;
          
        case 'a':
          aoObj->append = OPT_SPECIFIED;
          break;
          
        case 'l':
          aoObj->list = OPT_SPECIFIED;
          break;
          
        case '?':
          printf ("\nUnsupported option '%c'", n_opt);
          opt_usage (argv [0]);
          break;
          
        default: /* '?' */
          opt_usage (argv [0]);          
        }
    }

  if (opt_check__ (aoObj) == (int) OPT_PROC_ERROR)
    {
      opt_usage (argv [0]);
      return (int) OPT_PROC_ERROR;
    }

  return (int) OPT_SUCCESS;
}

/***************************************************************************//** 
 * @brief Clones a string 
 *
 * This functions allocates memory and clones the given string
 *
 * @param[in,out] dest - pointer to the destination object holding the clone
 * @param[in] src - pointer to the source string
 *
 * @retval OPT_SUCCESS     on success
 * @retval OPT_MALLOCERROR on an memory allocation error 
 * @retval OPT_NULLPOINTER on a passing of a null pointer 
 ******************************************************************************/
int opt_strclone (/*@out@*/ char **dest, const char *src)
{
  size_t  s_len = 0;
  char   *ptr   = NULL;
  
  /* check preconditions - given parameters are not equal to NULL */
  if (dest == NULL || src == NULL)
    {
      return (int) OPT_NULLPOINTER;
    }

  s_len = strlen (src);
  ptr   = (char *) malloc (s_len + 1);

  if (ptr == NULL)
    {
      return (int) OPT_MALLOCERROR;
    }

  *dest = ptr;

  while (*src != '\0')
    {
      *ptr++ = *src++;
    }
  *ptr = '\0';

  return (int) OPT_SUCCESS;
}

/***************************************************************************//** 
 * @brief Writes the usage information  
 *
 * This functions writes the usage information in the stdout and exits with 
 * an error
 *
 * @param[in] src - the application string
 *
 * @retval void
 ******************************************************************************/
void opt_usage (const char *app_name)
{
  char *a_name = basename ((char *) app_name);

  printf ("\n\tSYNOPSIS\n");
  printf ("\t%s [OPTION] ... \n", a_name);
  printf ("\t -f arg, (mandatory) the patient list file name \n");
  printf ("\t -a,     (optional) append a patient to the file \n");
  printf ("\t -l,     (optional) list all patients stored in the file \n\n");

  exit (EXIT_FAILURE);
}
