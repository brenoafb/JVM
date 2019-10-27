#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "classfile.h"
#include "frame.h"

typedef struct jvm {
  uint32_t pc;
  Frame *frame;
  uint8_t *heap;
  /*
  MethodArea ma;
  NativeMethodArea nma;
  */
} jvm;
