#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 10
#define COLS 10
#define TOTAL_SIZE 110

int main(int argc, char ** argv) {
  char matrix[ROWS][COLS];
  char pch[TOTAL_SIZE];
  int c;
  int index = 0;

  // 检查命令行参数数量
  if (argc != 2) {
    fprintf(stderr, "error\n");
    return EXIT_FAILURE;
  }

  // 打开文件
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "error\n");
    return EXIT_FAILURE;
  }

  // 逐个字符读取文件并检查
  while ((c = fgetc(f)) != EOF) {
    if (index >= TOTAL_SIZE) {
      fprintf(stderr, "error\n");
      fclose(f);
      return EXIT_FAILURE;
    }
    if (c >= 128) {
      fprintf(stderr, "error\n");
      fclose(f);
      return EXIT_FAILURE;
    }
    if (c == '\n' && index % (COLS + 1) != COLS) {
      fprintf(stderr, "error\n");
      fclose(f);
      return EXIT_FAILURE;
    }
    if (c != '\n' && index % (COLS + 1) == COLS) {
      fprintf(stderr, "error\n");
      fclose(f);
      return EXIT_FAILURE;
    }
    pch[index] = c;
    index++;
  }

  // 检查文件长度
  if (index != TOTAL_SIZE) {
    fprintf(stderr, "error\n");
    fclose(f);
    return EXIT_FAILURE;
  }

  // 矩阵旋转
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      matrix[j][ROWS - 1 - i] = pch[i * (COLS + 1) + j];
    }
  }

  // 输出旋转后的矩阵
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      fprintf(stdout, "%c", matrix[i][j]);
    }
    fprintf(stdout, "\n");
  }

  // 关闭文件
  if (fclose(f) != 0) {
    fprintf(stderr, "error\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
