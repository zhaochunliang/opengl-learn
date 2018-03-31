#ifndef OPENGL_LEARN_GISUTIL_H
#define OPENGL_LEARN_GISUTIL_H

class CGISUtil
{
public:
	static void degree2radian(const double& degree, double& radian);
	static void radian2degree(const double& radian, double& degree);

	static void LonLat2WebMercator(const double& lon, const double& lat, double& merc_x, double& merc_y);
	static void WebMercator2LonLat(const double& merc_x, const double& merc_y, double& lon, double& lat);

	static void WebMercator2Pixel(const double& merc_x, const double& merc_y, const int& zoom, double &pix_x, double &pix_y);
	static void Pixel2WebMercator(const double& pix_x, const double& pix_y, const int& zoom, double& merc_x, double& merc_y);

	static void getXYZWithDLonLat(const double& dlon, const double& dlat, double& x, double& y, double&z);
	static void getXYWithDLonLat(const double& dlon, const double& dlat, const int& zoom, int& x, int&y);

};
#endif // OPENGL_LEARN_GISUTIL_H