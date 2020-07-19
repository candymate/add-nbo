#include <stdio.h>
#include <stdint.h>
#include <string.h>

// bool type : https://ra2kstar.tistory.com/145
typedef enum {true, false} bool;

bool detect_hbo(); // return true if little endian, else false

int main(int argc, char* argv[]) {
  // check argc
  if (argc != 3) {
    puts("Usage : ./add-nbo <file 1> <file 2>");
    return -1;
  }

  // open two files
  FILE* f1 = fopen(argv[1], "rb");
  FILE* f2 = fopen(argv[2], "rb");
  if(f1 == NULL) {
    printf("File open error : %s is not a valid file\n", argv[1]);
    return -1;
  }
  if(f2 == NULL) {
    printf("File open error : %s is not a valid file\n", argv[2]);
    return -1;
  }
  
  // read values
  char buf1[4];
  char buf2[4];
  memset(buf1, 0, 4);
  memset(buf2, 0, 4);
  if(fread(buf1, 1, 4, f1) != 4) {
    printf("File read error : %s is invalid\n", argv[1]);
  }
  if(fread(buf2, 1, 4, f2) != 4) {
    printf("File read error : %s is invalid\n", argv[2]);
  }
  fclose(f2);
  fclose(f1);

  uint32_t val1, val2;
  // change to hbo : detect hbo and reverse byte order manually
  if(detect_hbo()) {
    // puts("host byte order : little endian");
    val1 = *((uint32_t*)&buf1);
    val2 = *((uint32_t*)&buf2);
    val1 = ((val1 & 0xff000000) >> 24) | ((val1 & 0xff0000) >> 8) | ((val1 & 0xff00) << 8) | ((val1 & 0xff) << 24);
    val2 = ((val2 & 0xff000000) >> 24) | ((val2 & 0xff0000) >> 8) | ((val2 & 0xff00) << 8) | ((val2 & 0xff) << 24);
  }
  else {
    // puts("host byte order : big endian");
    val1 = *((uint32_t*)&buf1);
    val2 = *((uint32_t*)&buf2);
  }

  // print result
  printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", val1, val1, val2, val2, val1+val2, val1+val2);

  return 0;
}

bool detect_hbo() {
  char buf[5] = "\x44\x33\x22\x11";
  uint32_t a = 0x11223344;
  uint32_t* ptr = (uint32_t*)&buf;

  return *ptr == a;
}