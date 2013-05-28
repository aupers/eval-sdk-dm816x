#include <stdio.h>
#include <stdlib.h>

/* #define DIRECT_SYS_CALL */

#ifdef DIRECT_SYS_CALL
/* ARM EABI ONLY! */
static inline void do_write_trap(int fd, const void *buf, unsigned long count)
{
  __asm__ __volatile__ (
  "mov\tr0,%0\n\t"
  "mov\tr1,%1\n\t"
  "mov\tr2,%2\n\t"
  "mov\tr7,#4\n\t"  
  "swi\t0x900000\n\t"
        :
        : "r" ((long)(fd)),"r" ((long)(buf)),"r" ((long)(count))
        : "r0","r1","r2","r7", "lr");
}

/* A version of puts that doesn't use libc. */

void deb_puts(const char *string)
{
  unsigned long count;
  for(count = 0; string[count]; count++);
  do_write_trap(1, string, count);
}
#else
#define deb_puts(s)
#endif

int main(int argc, char **argv, char **envp)
{
  int i;

  /* Mandatory "Hello, world!" */

  deb_puts("Getting ready to say \"Hello, world\"\n");
  printf("Hello, world!\n");
  deb_puts("It has been said.\n");

  /* Print arguments */

  printf("argc\t= %d\n", argc);
  printf("argv\t= 0x%p\n", argv);

  for (i = 0; i < argc; i++)
    {
      printf("argv[%d]\t= ", i);
      if (argv[i])
	{
	  printf("(0x%p) \"%s\"\n", argv[i], argv[i]);
	}
      else
	{
	  printf("NULL?\n");
	}
    }

  printf("argv[%d]\t= 0x%p\n", argc, argv[argc]);

  /* Print environment variables */

  printf("envp\t= 0x%p\n", envp);

  for (i = 0; envp[i] != NULL; i++)
    {
      printf("envp[%d]\t= (0x%p) \"%s\"\n", i, envp[i], envp[i]);
    }
  printf("envp[%d]\t= 0x%p\n", i, envp[i]);

  printf("Goodbye, world!\n");
  return 0;
}
