#ifndef OPENGL_LEARN_GEOJSON_PARSER_H
#define OPENGL_LEARN_GEOJSON_PARSER_H

#include "CCommon.h"
#include <string>
#include <vector>

typedef     std::vector<Vector2F>            TXPolygon;
typedef     std::vector<TXPolygon>      MultiTXPolygon;

class CountryInfo
{
public:
	std::string                  mCountryId;
	std::string                  mCountryName;
	Vector2F                     mCountryCenter;
	MultiTXPolygon               mCountryBoundary;
};

class CGeoJsonParser
{
public:
	int LoadGeoJsonContent(const char* geojsonfile, std::vector<CountryInfo>& countryInfoVec); 
};
#endif  // OPENGL_LEARN_GEOJSON_PARSER_H