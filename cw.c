#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>
#include "cw.h"

#define PROG_NAME "cw"
#define PROG_VERSION "0.1"

int print_version()
{
  printf("%s version %s\n", PROG_NAME, PROG_VERSION);
  return 0;
}

int print_help()
{
  printf("Usage: %s [options] [arguments]\n", PROG_NAME);
  printf("Options:\n");
  printf("  -h, --help     : print help\n");
  printf("  -c, --create   : create\n");
  printf("  -d, --delete   : delete\n");
  printf("  --setflag      : set flag\n");
  printf("  --clrflag      : clear flag\n");
  printf("  --strflag      : string flag\n");
  printf("  -a             : option a\n");
  printf("  -b arg         : option b\n");
//  printf("Arguments:\n");
//  printf("  arguments\n");
  return 0;
}

static void print_arg(int argc, char* argv[])
{
#if 0
  int i;
  for (i=0; i<argc; i++) {
    printf("argv[%d]=%s ", i, argv[i]);
  }
#endif
}

int main(int argc, char* argv[])
{
  int c, flag = 2;
  const char* optstring = "ab:hv" ; // optstringを定義します
  const struct option longopts[] = {
    //{    *name,           has_arg, *flag, val },
    {  "help",         no_argument,     0, 'h' },
    {  "create",       no_argument,     0, 'c' },
    {  "delete", required_argument,     0, 'd' },
    { "setflag",       no_argument, &flag,  1  },
    { "clrflag",       no_argument, &flag,  0  },
    {  "version",      no_argument,     0, 'v' },
    {         0,                 0,     0,  0  }, // termination
  };
  int longindex = 0;

  opterr = 0; // disable error log
  // non-option or end of argument list or error('?')までloop
  while ((c=getopt_long(argc, argv, optstring, longopts, &longindex)) != -1) {
  // print_arg(argc, argv);
    switch (c) {
      case 'a': // no option argument
        printf("opt=%c ", c);
        break;
      case 'd': // no option argument
        printf("delete opt=%c ", c);
        break;
      case 'v': 
        print_version();
        break;
      case 'h': 
      case '?': // unknown option character
        print_help();
        // case ':': // no option argument
        printf("optopt=%c ", optopt);
        break;
    }

    if (c == 0 || c == 'c' || c == 'd') {
      const struct option* longopt = &longopts[longindex];
      printf("longopt=%s ", longopt->name);
      if (longopt->has_arg == required_argument) {
        printf("optarg=%s ", optarg);
      }
      if (longopt->flag) {
        printf("*flag=%d ", *longopt->flag);
      }
    } else {
      printf("opt=%c ", c);
      if (c == 'a') {
        // without option argument
      } else if (c == 'b') {
        // with option argument
        printf("optarg=%s ", optarg);
      } else {
        // '?'
        printf("optopt=%c ", optopt);
        if (optopt == 'b') {
          // no option argument
        } else {
          // unknown option character
        }
        printf("\n");
        return -1; // error
      }
    }
    printf("\n");
  }

  // non-option or end of argument list
  while (optind < argc) {
    print_arg(argc, argv);
    printf("non-opt=%s \n", argv[optind]);
    optind++;
  }
  return 0;
}
