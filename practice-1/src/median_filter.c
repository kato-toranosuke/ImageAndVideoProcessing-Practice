#include <math.h>
#include <stdio.h>
#include "data_inout.h"

#define NPIXELS 256 // 画素数
#define N 3         // 窓の大きさ

// 配列内を昇順にsortする
void sort(int vals[], int count)
{
  for (int i = 0; i < count - 1; i++)
  {
    for (int j = 1; j < count; j++)
    {
      if (vals[j - 1] > vals[j])
      {
        int tmp = vals[j - 1];
        vals[j - 1] = vals[j];
        vals[j] = tmp;
      }
    }
  }

  return;
}

// sortされた配列から中央値を取得し、返す関数
int getMedian(int vals[], int count){
  int median = 0;
  if (count % 2 == 0)
  {
    // 要素数が偶数の場合
    int i = count / 2;
    median = vals[i] + vals[i - 1];
    median /= 2;
  }else{
    // 要素数が奇数の場合
    int i = (count - 1) / 2;
    median = vals[i];
  }
  return median;
}

int main(void)
{
  unsigned char inputImg[NPIXELS][NPIXELS];
  char input_filename[] = "data/lenad";
  unsigned char outputImg[NPIXELS][NPIXELS];
  char output_filename[] = "data/output_median7x7";

  // データを読み込む
  read_image(inputImg, NPIXELS * NPIXELS, input_filename);

  for (int i = 0; i < NPIXELS; i++)
  {
    for (int j = 0; j < NPIXELS; j++)
    {
      // 窓に含まれる画素を順次見ていく
      int number = (2 * N + 1) * (2 * N + 1); // 窓に含まれるpixel数
      int vals[number];
      int index = 0;

      for (int k = -N; k <= N; k++)
      {
        for (int l = -N; l <= N; l++)
        {
          int i2 = i + k;
          int j2 = j + l;
          if (i2 < 0 || i2 > NPIXELS - 1 || j2 < 0 || j2 > NPIXELS - 1)
            // データが入っていない配列の要素を参照しようとしている時
            number--; // 窓に含まれる画素数を更新
          else
          {
            vals[index] = inputImg[i2][j2];
            index++;
          }
        }
      }

      // sort
      sort(vals, number);
      // median
      int median = getMedian(vals, number);

      outputImg[i][j] = (unsigned char)median;
    }
  }
  
  // データを書き込む
  write_image(outputImg, NPIXELS * NPIXELS, output_filename);
}