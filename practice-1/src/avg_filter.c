#include <math.h>
#include <stdio.h>
#include "data_inout.h"

#define NPIXELS 256 // 画素数
#define N 3         // 窓の大きさ

int main(void)
{
  unsigned char inputImg[NPIXELS][NPIXELS];
  char input_filename[] = "data/lenad";
  unsigned char outputImg[NPIXELS][NPIXELS];
  char output_filename[] = "data/output_avg7x7";
  int size = NPIXELS * NPIXELS;

  // データを読み込む
  read_image(inputImg, size, input_filename);

  for (int i = 0; i < NPIXELS; i++)
  {
    for (int j = 0; j < NPIXELS; j++)
    {
      int val = 0;
      int number = (2 * N + 1) * (2 * N + 1); // 窓に含まれるpixel数
      for (int k = -N; k <= N; k++)
      {
        for (int l = -N; l <= N; l++)
        {
          // 窓に含まれるpixelを順次見ていく
          int i2 = i + k;
          int j2 = j + l;
          if (i2 < 0 || i2 > NPIXELS - 1 || j2 < 0 || j2 > NPIXELS - 1)
            // データが入っていない配列の要素を参照しようとしている時
            number = number - 1; // 窓に含まれるpixel数を更新
          else
            val = val + inputImg[i2][j2];
        }
      }
      // outputImg[i][j] = (unsigned char)((float)val / (float)number + 0.5);
      outputImg[i][j] = (unsigned char)((float)val / (float)number);
    }
  }

  // データを書き込む
  write_image(outputImg, size, output_filename);
}