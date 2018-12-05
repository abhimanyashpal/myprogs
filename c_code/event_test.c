#include <sys/eventfd.h>
#include <sys/time.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>             /* Definition of uint64_t */

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

pthread_t event_th;
pthread_t trigger_th;

typedef unsigned char bool;
bool sigint_recvd;

void *
test_event (void *d)
{
    int efd = (int)d;
    fd_set rfds;
    int retval;
    size_t s = 0;
    uint64_t u;

    if (!efd) {
      handle_error("NO EVENT FD......");
    }

    printf("\nStarting consumer....");
    fflush(stdout);

    while (1 && !sigint_recvd) {

        FD_ZERO(&rfds);
        FD_SET(efd,&rfds);

        //Block on the event
        retval = select(efd+1, &rfds,NULL,NULL,NULL);

        if (retval == -1) {
          handle_error("select failed....");
        }

        if (retval > 0) {
          if (FD_ISSET(efd, &rfds)) {
            printf("\nEvent received.....");
            s = read(efd, &u, sizeof(uint64_t));
            if (s != sizeof(uint64_t))
              handle_error("Invalid read in event fd...");
            }
            printf("\nRead %lu",u);
            fflush(stdout);
            usleep(1000000); //Simulating a delay for allowing multiple events to be queued.
        }

        if (retval == 0) {
          handle_error("select 0 retval seen...");
        }
    }
    printf("\n Exit consumer....");
    fflush(stdout);
    return NULL;

}

uint16_t n = 10;

void *
trigger_event (void *d)
{
  int efd = (int) d;
  int retval = 0;
  size_t s,i;
  uint64_t u;

  struct timeval tv;

  /* Wait up to five seconds. */
  tv.tv_sec = 5;
  tv.tv_usec = 0;

  printf("\nStarting consumer....");
  fflush(stdout);
  if (!efd)
    {
      handle_error ("Trigger thread exiting...");
    }

  while (1)
    {
      tv.tv_sec = 2;
      tv.tv_usec = 0;
      select (0,NULL, NULL, NULL, &tv);

      u = 1UL;
      for (i = 0; i < n; i++)
      {
         s = write (efd, &u, sizeof (uint64_t));
         if (s != sizeof (uint64_t))
         {
           printf ("\nFailed to write....");
         }
      }
      //return NULL;
    }

    printf("\n Exit trigger....");
    fflush(stdout);
    return NULL;
}

void
sigint_hdlr (int d)
{
   sigint_recvd = 1;
}


int
main (int argc, char **argv)
{
  int efd, j;
  uint64_t u;
  ssize_t s;

  efd = eventfd (0, EFD_SEMAPHORE);
  //efd = eventfd (0, 0);
  if (efd == -1)
    handle_error ("eventfd");

  signal(SIGINT, sigint_hdlr);

  if (pthread_create (&event_th, NULL, test_event, (void *) efd) != 0)
  {
      printf ("\nFailed to create event consumer thread....");
      return -1;
  }

  if (pthread_create (&trigger_th, NULL, trigger_event, (void *) efd) != 0)
  {
      printf ("\nFailed to create trigger thread....");
      return -1;
  }

  pthread_join(event_th, NULL);
  pthread_join(trigger_th, NULL);

}
