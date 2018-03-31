#include "CGISUtil.h"
#include <math.h>
#include <UrlMon.h>

#pragma comment(lib,"urlmon.lib")

#define  M_PI        3.14159265358979323846
#define  M_Radius    6378137.0
#define  M_W1Len     20037508.3427892
#define  M_W2Len     40075016.6855784
#define  M_TileSize  256


void CGISUtil::degree2radian(const double& degree, double& radian)
{
	radian = (M_PI / 180.0f) * degree;                  // ((2 * M_PI) / 360.0f) * degree;
}

void CGISUtil::radian2degree(const double& radian, double& degree)
{
	degree = (180.0f / M_PI) * radian;                  // (360.0f / (2 * M_PI)) * radian;
}

void CGISUtil::LonLat2WebMercator(const double& lon, const double& lat, double& merc_x, double& merc_y)
{
	merc_x = (lon / 180.0f) * (M_PI * M_Radius);
	merc_y = log(tan((90+lat)*M_PI/360)) / (M_PI/180);  
	merc_y = (merc_y / 180.f) * (M_PI * M_Radius);  

}

void CGISUtil::WebMercator2LonLat(const double& merc_x, const double& merc_y, double& lon, double& lat)
{
	lon = merc_x / (M_PI * M_Radius) * 180.0f;
	lat = merc_y / (M_PI * M_Radius) * 180.0f;
	lat = 180.0f / M_PI * (2 * atan(exp(lat * M_PI / 180)) - M_PI / 2); 
}

void CGISUtil::WebMercator2Pixel(const double& merc_x, const double& merc_y, const int& zoom, double &pix_x, double &pix_y)
{
	double pixelOfThisZoom        = M_TileSize * pow(2.0f, zoom);
	double resolutionOfThisZoom   = M_W2Len  / pixelOfThisZoom;
	pix_x = merc_x / resolutionOfThisZoom + pixelOfThisZoom / 2;
	pix_y = merc_y / resolutionOfThisZoom + pixelOfThisZoom / 2;


}

void CGISUtil::Pixel2WebMercator(const double& pix_x, const double& pix_y, const int& zoom, double& merc_x, double& merc_y)
{
	double pixelOfThisZoom        = M_TileSize * pow(2.0f, zoom);
	double resolutionOfThisZoom   = M_W2Len  / pixelOfThisZoom;

	merc_x = (pix_x - pixelOfThisZoom/2) * resolutionOfThisZoom;
	merc_y = (pix_y - pixelOfThisZoom/2) * resolutionOfThisZoom;
}

void CGISUtil::getXYZWithDLonLat(const double& dlon, const double& dlat, double& x, double& y, double&z)
{
	double rlon = 0, rlat = 0;
	degree2radian(dlon, rlon);
	degree2radian(dlat, rlat);

	double sinLat = sin(rlat);   
	double cosLat = cos(rlat);

	double sinLon = sin(rlon);       
	double cosLon = cos(rlon);

	x = cosLat * sinLon;
	y = sinLat;
	z = cosLat * cosLon;

}

void CGISUtil::getXYWithDLonLat(const double& dlon, const double& dlat, const int& zoom, int& x, int&y)
{
	double merc_x(0.0), merc_y(0.0);
	LonLat2WebMercator(dlon, dlat, merc_x, merc_y);

	double pixel_x(0.0), pixel_y(0.0);
	WebMercator2Pixel(merc_x, merc_y, zoom, pixel_x, pixel_y);

	x = (int)floor(pixel_x / 256);
	y = (int)floor(pixel_y / 256);

}