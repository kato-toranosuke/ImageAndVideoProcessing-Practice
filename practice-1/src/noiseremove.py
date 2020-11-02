import numpy as np
from PIL import Image

def main():
    N = 1
    image1 = np.array(Image.open('lena.png'))
    image2 = np.zeros([256,256],'uint8')
    for i in range(256):
        for j in range(256):
            val = 0
            number = (2 * N + 1)**2
            for k in range(-N, N+1):
                for l in range(-N, N+1):
                    i2 = i + k
                    j2 = j + l
                    if i2<0 or i2>255 or j2 < 0 or j2>255:
                        number -=1
                    else:
                        val += image1[i2][j2]
            image2[i][j] = val/number+0.5
    Image.fromarray(image2).save('out.png')
    


if __name__ == '__main__':
    main()
