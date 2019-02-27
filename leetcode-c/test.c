//
// Created by 付旭炜 on 2019/2/27.
//
#include <string.h>
#include <stdio.h>

void reverseString(char* s, int sSize) {
  if (s == NULL || sSize == 0) {
    return;
  }
  for (int i = 0; i < sSize / 2; ++i) {
    char tmp = s[i];
    s[i] = s[sSize - i - 1];
    s[sSize - i - 1] = tmp;
  }

  return;
}



int main() {
  char s1[] = "nmsl";
  char *s2 = NULL;
  char s3[] = "wsngg";

  reverseString(s1, strlen(s1));
  if (strcmp(s1, "lsmn") != 0) {
      fprintf(stderr, "nmsl error\n");
  }
  reverseString(s2, 9);
  if (s2 != NULL) {
    fprintf(stderr, "Null error");
  }
}