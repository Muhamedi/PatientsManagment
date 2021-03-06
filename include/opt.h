/** 
 * Copyright (C) 2020 Muhamed Krasniqi. All rights reserved
 * muhamed.krasniqi@student.uni-pr.edu
 *
 * @file  opt.h
 *
 * @brief Implements functions for the option processing
 * 
 * @author (MK) Muhamed Krasniqi
 * @date   $Date: Sun May 31, 21:48:27:59 WEST 2020 $
 */

#ifndef _OPT_H
#define _OPT_H 1_

#include <stdio.h>

/* defines different option macros */
#define OPT_FILE         (char) 0x01
#define OPT_APPEND       (char) 0x02
#define OPT_LIST         (char) 0x04
#define OPT_INTERACTIV   (char) 0x08
#define OPT_MAX_NUM      (char) 0x04

/* defines option's pattern */
#define OPT_PATTERN      "f:ahil"

/* define interactive commands */
#define INTA_APPEND      "append"
#define INTA_LIST        "list"
#define INTA_HELP        "help"
#define INTA_QUIT        "quit"
#define INTA_CMD_MAXLEN  100

/* define OPTION STATUS */
#define OPT_SPECIFIED    (char) 0x01
#define OPT_NOTSPECIFIED (char) 0x02

/* define the processing status of the passed options and arguments */
#define OPT_SUCCESS      (char) 0x01
#define OPT_PROC_ERROR   (char) 0x02
#define OPT_MALLOCERROR  (char) 0x04
#define OPT_NULLPOINTER  (char) 0x08

/* define application structure */
typedef struct _applOption
{
  char  append;
  char  list;
  char  interactive;
  char *f_name;
  FILE *fp;
  
} appOption;

/* public interface functions */
void opt_init     (/*@out@*/appOption *aoObj);
void opt_free     (/*@out@*/appOption *aoObj);
int  opt_proc     (         int         argc, char *argv[], /*@out@*/appOption *aoObj);
int  opt_strclone (/*@out@*/char      **dest, const char *src);
void opt_usage    (   const char       *name);
#endif /* _OPT_H */

 
