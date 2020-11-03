#include <math.h>
#include <stdio.h>
#include "data_inout.h"

#define NPIXELS 256 // 画素数
#define N 1         // 窓の大きさ

int integral(unsigned char pixels[][3], int kernel[][3])
{
  int val = 0;
  for (int i = 0; i < 2 * N + 1; i++)
  {
    for (int j = 0; j < 2 * N + 1; j++)
    {
      val += pixels[i][j] * kernel[i][j];
    }
  }
  return val;
}

int main(void)
{
  unsigned char inputImg[NPIXELS][NPIXELS];
  char input_filename[] = "data/lena";
  unsigned char outputImg[NPIXELS][NPIXELS];
  char output_filename[] = "data/output_sobel";

  // sobel filterのkernel
  int Gh[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}; // 水平方向
  int Gv[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}}; // 垂直方向

  // データを読み込む
  read_image(inputImg, NPIXELS * NPIXELS, input_filename);

  for (int i = 0; i < NPIXELS; i++)
  {
    for (int j = 0; j < NPIXELS; j++)
    {
      unsigned char pixels[2 * N + 1][2 * N + 1]; // 窓に含まれる画素値

      // pixelsに値を格納する
      for (int k = -N; k <= N; k++)
      {
        int ix = k + N; // 配列pixelsのindex
        for (int l = -N; l <= N; l++)
        {
          int iy = l + N; // 配列pixelsのindex
          int i2 = i + k;
          int j2 = j + l;
          if (i2 < 0 || i2 > NPIXELS - 1 || j2 < 0 || j2 > NPIXELS - 1)
            // データが入っていない配列の要素を参照しようとしている時
            pixels[ix][iy] = 0;
          else
            pixels[ix][iy] = inputImg[i2][j2];
        }
      }

      // 畳み込み積分をした結果を得る
      int fx = integral(pixels, Gh);
      int fy = integral(pixels, Gv);
      // フィルタの出力結果
      int g = sqrt(fx * fx + fy * fy)*0.5;
      if (g > 255)
        g = 255;
      outputImg[i][j] = (unsigned char)g;
    }
  }

  // データを書き込む
  write_image(outputImg, NPIXELS * NPIXELS, output_filename);
}