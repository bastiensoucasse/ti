#include "sed.h"
#include "colorimetric_data.h"
#include "xyz.h"

#include "MISSINGCODE.h"
/*
  sRGB transform (REC-709 with D65)

  static float rec709_m_XYZ_to_sRGB[3][3] = 
  {
  {  3.240479, -1.537150, -0.498535 },
  { -0.969256,  1.875992,  0.041556 },
  {  0.055648, -0.204043,  1.057311 } 
  };

*/

float
xyz_srgb_r(float cie_x, float cie_y, float cie_z)
{
XYZ_SRGB_R_MISSINGCODE
}

float
xyz_srgb_g(float cie_x, float cie_y, float cie_z)
{
XYZ_SRGB_G_MISSINGCODE
}

float
xyz_srgb_b(float cie_x, float cie_y, float cie_z)
{
XYZ_SRGB_B_MISSINGCODE
}


/* 
   Computation of CIE-XYZ of DSE e with a normalization corresponding to a light
   source s. Store the result at the address given by xyz supposed to be that of
   an array of three floats.
*/
void
xyz_from_sed(float *xyz, float *e, float k)
{
XYZ_FROM_SED_MISSINGCODE    
}


/*
  Computation of the normalization coefficient associated with a light source s
*/

float
xyz_get_k_from_s(float *s)
{
XYZ_GET_K_FROM_S_MISSINGCODE
    
    return k;
}
    
