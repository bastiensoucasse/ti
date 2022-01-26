#include "xyz.h"
#include "colorimetric_data.h"
#include "sed.h"

#include "MISSINGCODE.h"

/*
  sRGB transform (REC-709 with D65)
*/
static float rec709_m_XYZ_to_sRGB[3][3] = {
    { 3.240479, -1.537150, -0.498535 },
    { -0.969256, 1.875992, 0.041556 },
    { 0.055648, -0.204043, 1.057311 }
};

float xyz_srgb_r(float cie_x, float cie_y, float cie_z)
{
    return rec709_m_XYZ_to_sRGB[0][0] * cie_x + rec709_m_XYZ_to_sRGB[0][1] * cie_y + rec709_m_XYZ_to_sRGB[0][2] * cie_z;
}

float xyz_srgb_g(float cie_x, float cie_y, float cie_z)
{
    return rec709_m_XYZ_to_sRGB[1][0] * cie_x + rec709_m_XYZ_to_sRGB[1][1] * cie_y + rec709_m_XYZ_to_sRGB[1][2] * cie_z;
}

float xyz_srgb_b(float cie_x, float cie_y, float cie_z)
{
    return rec709_m_XYZ_to_sRGB[2][0] * cie_x + rec709_m_XYZ_to_sRGB[2][1] * cie_y + rec709_m_XYZ_to_sRGB[2][2] * cie_z;
}

/* 
   Computation of CIE-XYZ of DSE e with a normalization corresponding to a light
   source s. Store the result at the address given by xyz supposed to be that of
   an array of three floats.
*/
void xyz_from_sed(float* xyz, float* e, float k)
{
    float* ep = sed_dup(e);
    sed_multiply_by(ep, cie_x_bar);
    xyz[0] = k * sed_sum(ep);

    sed_copy(ep, e);
    sed_multiply_by(ep, cie_y_bar);
    xyz[1] = k * sed_sum(ep);

    sed_copy(ep, e);
    sed_multiply_by(ep, cie_z_bar);
    xyz[2] = k * sed_sum(ep);

    free(ep);
}

/*
  Computation of the normalization coefficient associated with a light source s
*/
float xyz_get_k_from_s(float* s)
{
    float* tmp = sed_dup(s);

    sed_multiply_by(tmp, cie_y_bar);
    float k = 1 / sed_sum(tmp);

    free(tmp);
    return k;
}
