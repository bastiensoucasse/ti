#ifndef CHANNEL_H
#define CHANNEL_H

/*
  extracts a channel from buffer PIXELS of size SIZE, with respect to parameter
  CHANNEL (0=red, 1=green, 2-blue) and returns a copy of the extracted channel
  allocated with malloc
*/
extern unsigned char *channel_extract(unsigned char *pixels, int size, int channel_number);


/*
  returns a buffer of pixel of size SIZE, allocated with malloc, resulting 
  from the composition of the three channels R_CHAN, G_CHAN and B_CHAN  
*/
extern unsigned char *channel_compose(unsigned char *r_chan,
				      unsigned char *g_chan,
				      unsigned char *b_chan,
				      size_t size);

/*
  returns a copy of channel PIXELS allocated with malloc
*/
extern unsigned char *channel_dup(unsigned char *pixels, int size);

#endif  /* CHANNEL_H */
