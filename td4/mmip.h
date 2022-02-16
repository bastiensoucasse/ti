#ifndef MMIP_H
#define MMIP_H

extern unsigned char *mmip_disk_erosion(unsigned char *channel, int width, int height, int radius);
extern unsigned char *mmip_disk_dilatation(unsigned char *channel, int width, int height, int radius);

extern unsigned char *mmip_disk_opening(unsigned char *channel, int width, int height, int radius);
extern unsigned char *mmip_disk_closing(unsigned char *channel, int width, int height, int radius);

extern unsigned char *mmip_disk_bgrad(unsigned char *channel, int width, int height, int radius);
extern unsigned char *mmip_disk_igrad(unsigned char *channel, int width, int height, int radius);
extern unsigned char *mmip_disk_ograd(unsigned char *channel, int width, int height, int radius);


#endif  /* MMIP_H */
