//
// Created by 付旭炜 on 2019/2/27.
//
#include <string.h>

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

