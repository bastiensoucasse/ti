#ifndef XYZ_H
#define XYZ_H

extern float xyz_srgb_r(float cie_x, float cie_y, float cie_z);
extern float xyz_srgb_g(float cie_x, float cie_y, float cie_z);
extern float xyz_srgb_b(float cie_x, float cie_y, float cie_z);

extern float xyz_get_k_from_s(float *s);
extern void xyz_from_sed(float *xyz, float *e, float k);

#endif  /* XYZ2RGB_H */

