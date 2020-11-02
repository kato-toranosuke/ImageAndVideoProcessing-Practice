#include <math.h>
#include <stdio.h>
#include "data_inout.h"

#define NPIXELS 256
#define N 3

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

int getMedian(int vals[], int count){
  int median = 0;
  if (count % 2 == 0)
  {
    int i = count / 2;
    median = vals[i] + vals[i - 1];
    median /= 2;
  }else{
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

  read_image(inputImg, NPIXELS * NPIXELS, input_filename);

  for (int i = 0; i < NPIXELS; i++)
  {
    for (int j = 0; j < NPIXELS; j++)
    {
      int number = (2 * N + 1) * (2 * N + 1);
      int vals[number];
      int index = 0;

      for (int k = -N; k <= N; k++)
      {
        for (int l = -N; l <= N; l++)
        {
          int i2 = i + k;
          int j2 = j + l;
          if (i2 < 0 || i2 > NPIXELS - 1 || j2 < 0 || j2 > NPIXELS - 1)
            number--;
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

  write_image(outputImg, NPIXELS * NPIXELS, output_filename);
}