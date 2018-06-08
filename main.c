#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int16_t imul(int16_t Ax,int16_t Bx)
{
  // Returns:
  //   Ax = Ax * Bx
  int16_t sgn=1;
  int16_t res=0;
  int16_t word=1;
  int16_t MIN=-32768;

  if (Ax<0) {
    Ax=-Ax;
    sgn=-sgn;
  }
  if (Bx<0) {
    Bx=-Bx;
    sgn=-sgn;
  }

  LOOP:
    res=res<<1;
    if (res<0) {
      res=MIN;
      goto ERROR;
    }

    Ax=Ax<<1;
    if (Ax<0) {
      Ax=Ax-MIN;
      res=res+Bx;
      if (res<0) {
        res=MIN;
        goto ERROR;
      }
    }

    word=word+word+1;
  if (word>0) goto LOOP;

  if (sgn<0) {
    res=-res;
  }
  ERROR:
  return res;
}

int main(void)
{
  int16_t Ax,Bx,Mx;
  int i,j;

  for (i=-32767;i<=32767;i++) {
    for (j=-32767;j<=32767;j++) {
      Ax=(int16_t)i;
      Bx=(int16_t)j;
      Mx=imul(Ax,Bx);
      if (Mx!=-32768) {
        if (i*j!=Mx) printf("%6d %6d\n",i*j,Mx);
      } else {
        if ((i*j>=-32767)&&(i*j<=32767)) printf("%6d\n",i*j);
      }
    }
  }

  return 0;
}
