#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main() {
  int randomin = open("/dev/random", O_RDONLY);
  if (randomin == -1) {
    printf("errno: %d\terror: %s\n", errno, strerror(errno));
    return 0;
  }

  int randomout = open("random.out", O_CREAT | O_RDWR, 0664);
  if (randomout == -1) {
    printf("errno: %d\terror: %s\n", errno, strerror(errno));
    return 0;
  }


  printf("Generating random numbers ...\n");
  int arr[10];
  int i;
  for (i = 0; i < 10; i++) {
    int randomn;
    int n = read(randomin, &randomn, sizeof(randomn));
    if (n == -1) {
            printf("errno: %d\terror: %s\n", errno, strerror(errno));
            return 0;
    }
    arr[i] = randomn;
    printf("\trandom %d: %d\n", i, arr[i]);
  }
  printf("\n");

  printf("Writing numbers to file...\n\n");
  int k = write(randomout, &arr, sizeof(arr));
  if (k == -1) {
    printf("errno: %d\terror: %s\n", errno, strerror(errno));
    return 0;
  }

  printf("Reading numbers from file ...\n");
  int randomin2 = open("random.out", O_RDONLY);
  if (randomin2 == -1) {
    printf("errno: %d\terror: %s\n", errno, strerror(errno));
    return 0;
  }

  printf("Verification that written values were the same:\n");
  int arr2[10];
  int j = read(randomin2, arr2, sizeof(arr2));
  if (j == -1) {
    printf("errno: %d\terror: %s\n", errno, strerror(errno));
    return 0;
  }
  for (i = 0; i < 10; i++) {
    printf("\trandom %d: %d\n", i, arr2[i]);
  }

  return 0;
}
