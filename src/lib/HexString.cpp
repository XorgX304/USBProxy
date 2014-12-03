/*
 * This file is part of USBProxy.
 */

#include <linux/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HexString.h"
#include <endian.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN
static const __u16 hexAscii[256]={
		0x3030, 0x3130, 0x3230, 0x3330, 0x3430, 0x3530, 0x3630, 0x3730, 0x3830, 0x3930, 0x6130, 0x6230, 0x6330, 0x6430, 0x6530, 0x6630,
		0x3031, 0x3131, 0x3231, 0x3331, 0x3431, 0x3531, 0x3631, 0x3731, 0x3831, 0x3931, 0x6131, 0x6231, 0x6331, 0x6431, 0x6531, 0x6631,
		0x3032, 0x3132, 0x3232, 0x3332, 0x3432, 0x3532, 0x3632, 0x3732, 0x3832, 0x3932, 0x6132, 0x6232, 0x6332, 0x6432, 0x6532, 0x6632,
		0x3033, 0x3133, 0x3233, 0x3333, 0x3433, 0x3533, 0x3633, 0x3733, 0x3833, 0x3933, 0x6133, 0x6233, 0x6333, 0x6433, 0x6533, 0x6633,
		0x3034, 0x3134, 0x3234, 0x3334, 0x3434, 0x3534, 0x3634, 0x3734, 0x3834, 0x3934, 0x6134, 0x6234, 0x6334, 0x6434, 0x6534, 0x6634,
		0x3035, 0x3135, 0x3235, 0x3335, 0x3435, 0x3535, 0x3635, 0x3735, 0x3835, 0x3935, 0x6135, 0x6235, 0x6335, 0x6435, 0x6535, 0x6635,
		0x3036, 0x3136, 0x3236, 0x3336, 0x3436, 0x3536, 0x3636, 0x3736, 0x3836, 0x3936, 0x6136, 0x6236, 0x6336, 0x6436, 0x6536, 0x6636,
		0x3037, 0x3137, 0x3237, 0x3337, 0x3437, 0x3537, 0x3637, 0x3737, 0x3837, 0x3937, 0x6137, 0x6237, 0x6337, 0x6437, 0x6537, 0x6637,
		0x3038, 0x3138, 0x3238, 0x3338, 0x3438, 0x3538, 0x3638, 0x3738, 0x3838, 0x3938, 0x6138, 0x6238, 0x6338, 0x6438, 0x6538, 0x6638,
		0x3039, 0x3139, 0x3239, 0x3339, 0x3439, 0x3539, 0x3639, 0x3739, 0x3839, 0x3939, 0x6139, 0x6239, 0x6339, 0x6439, 0x6539, 0x6639,
		0x3061, 0x3161, 0x3261, 0x3361, 0x3461, 0x3561, 0x3661, 0x3761, 0x3861, 0x3961, 0x6161, 0x6261, 0x6361, 0x6461, 0x6561, 0x6661,
		0x3062, 0x3162, 0x3262, 0x3362, 0x3462, 0x3562, 0x3662, 0x3762, 0x3862, 0x3962, 0x6162, 0x6262, 0x6362, 0x6462, 0x6562, 0x6662,
		0x3063, 0x3163, 0x3263, 0x3363, 0x3463, 0x3563, 0x3663, 0x3763, 0x3863, 0x3963, 0x6163, 0x6263, 0x6363, 0x6463, 0x6563, 0x6663,
		0x3064, 0x3164, 0x3264, 0x3364, 0x3464, 0x3564, 0x3664, 0x3764, 0x3864, 0x3964, 0x6164, 0x6264, 0x6364, 0x6464, 0x6564, 0x6664,
		0x3065, 0x3165, 0x3265, 0x3365, 0x3465, 0x3565, 0x3665, 0x3765, 0x3865, 0x3965, 0x6165, 0x6265, 0x6365, 0x6465, 0x6565, 0x6665,
		0x3066, 0x3166, 0x3266, 0x3366, 0x3466, 0x3566, 0x3666, 0x3766, 0x3866, 0x3966, 0x6166, 0x6266, 0x6366, 0x6466, 0x6566, 0x6666};
#elif __BYTE_ORDER == __BIG_ENDIAN
static const __u16 hexAscii[256]={
		0x3030, 0x3031, 0x3032, 0x3033, 0x3034, 0x3035, 0x3036, 0x3037, 0x3038, 0x3039, 0x3061, 0x3062, 0x3063, 0x3064, 0x3065, 0x3066,
		0x3130, 0x3131, 0x3132, 0x3133, 0x3134, 0x3135, 0x3136, 0x3137, 0x3138, 0x3139, 0x3161, 0x3162, 0x3163, 0x3164, 0x3165, 0x3166,
		0x3230, 0x3231, 0x3232, 0x3233, 0x3234, 0x3235, 0x3236, 0x3237, 0x3238, 0x3239, 0x3261, 0x3262, 0x3263, 0x3264, 0x3265, 0x3266,
		0x3330, 0x3331, 0x3332, 0x3333, 0x3334, 0x3335, 0x3336, 0x3337, 0x3338, 0x3339, 0x3361, 0x3362, 0x3363, 0x3364, 0x3365, 0x3366,
		0x3430, 0x3431, 0x3432, 0x3433, 0x3434, 0x3435, 0x3436, 0x3437, 0x3438, 0x3439, 0x3461, 0x3462, 0x3463, 0x3464, 0x3465, 0x3466,
		0x3530, 0x3531, 0x3532, 0x3533, 0x3534, 0x3535, 0x3536, 0x3537, 0x3538, 0x3539, 0x3561, 0x3562, 0x3563, 0x3564, 0x3565, 0x3566,
		0x3630, 0x3631, 0x3632, 0x3633, 0x3634, 0x3635, 0x3636, 0x3637, 0x3638, 0x3639, 0x3661, 0x3662, 0x3663, 0x3664, 0x3665, 0x3666,
		0x3730, 0x3731, 0x3732, 0x3733, 0x3734, 0x3735, 0x3736, 0x3737, 0x3738, 0x3739, 0x3761, 0x3762, 0x3763, 0x3764, 0x3765, 0x3766,
		0x3830, 0x3831, 0x3832, 0x3833, 0x3834, 0x3835, 0x3836, 0x3837, 0x3838, 0x3839, 0x3861, 0x3862, 0x3863, 0x3864, 0x3865, 0x3866,
		0x3930, 0x3931, 0x3932, 0x3933, 0x3934, 0x3935, 0x3936, 0x3937, 0x3938, 0x3939, 0x3961, 0x3962, 0x3963, 0x3964, 0x3965, 0x3966,
		0x6130, 0x6131, 0x6132, 0x6133, 0x6134, 0x6135, 0x6136, 0x6137, 0x6138, 0x6139, 0x6161, 0x6162, 0x6163, 0x6164, 0x6165, 0x6166,
		0x6230, 0x6231, 0x6232, 0x6233, 0x6234, 0x6235, 0x6236, 0x6237, 0x6238, 0x6239, 0x6261, 0x6262, 0x6263, 0x6264, 0x6265, 0x6266,
		0x6330, 0x6331, 0x6332, 0x6333, 0x6334, 0x6335, 0x6336, 0x6337, 0x6338, 0x6339, 0x6361, 0x6362, 0x6363, 0x6364, 0x6365, 0x6366,
		0x6430, 0x6431, 0x6432, 0x6433, 0x6434, 0x6435, 0x6436, 0x6437, 0x6438, 0x6439, 0x6461, 0x6462, 0x6463, 0x6464, 0x6465, 0x6466,
		0x6530, 0x6531, 0x6532, 0x6533, 0x6534, 0x6535, 0x6536, 0x6537, 0x6538, 0x6539, 0x6561, 0x6562, 0x6563, 0x6564, 0x6565, 0x6566,
		0x6630, 0x6631, 0x6632, 0x6633, 0x6634, 0x6635, 0x6636, 0x6637, 0x6638, 0x6639, 0x6661, 0x6662, 0x6663, 0x6664, 0x6665, 0x6666};
#endif

char* hex_string_wide(const void* buf,int length,int width) {
	char* result;
	if (!length) {
	  result = (char *)malloc(1);
	  *result=0;
	  return result;
	}
	int lines=length/width;

	result = (char *)malloc(length * 3 + lines+2);
	__u8* inbuf=(__u8*)buf;
	result[length * 3+lines+1] = 0;
	result[0]='\n';
	result[1]='\t';

	__u16* p=(__u16*)(result+2);
	*p=hexAscii[inbuf[0]];
  int i;
  int curLine=1;
  for (i = 1; i < length; i++) {
	  if (i%width) {
		  result[i * 3 + curLine] = ' ';
		  p=(__u16*)(result+i*3+curLine+1);
		  *p=hexAscii[inbuf[i]];
	  } else {
		  result[i*3+curLine]='\n';
		  result[i*3+curLine+1]='\t';
		  curLine++;
		  p=(__u16*)(result+i*3+curLine+1);
		  *p=hexAscii[inbuf[i]];
	  }
  }
  return result;
}

char* hex_string(const void* buf,int length) {
  char* result;
  if (!length) {
	  result = (char *)malloc(1);
	  *result=0;
	  return result;
  }
  if (length>32) return hex_string_wide(buf,length,32);
  result = (char *)malloc(length * 3);
  __u8* inbuf=(__u8*)buf;
  result[length * 3-1] = 0;
  __u16* p=(__u16*)result;

  *p=hexAscii[inbuf[0]];
  int i;

  for (i = 1; i < length; i++) {
	  result[i * 3 - 1] = ' ';
	  p=(__u16*)(result+i*3);
	  *p=hexAscii[inbuf[i]];
  }
  return result;
}
