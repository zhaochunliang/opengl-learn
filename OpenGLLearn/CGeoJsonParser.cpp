#include "CGeoJsonParser.h"
#include "Json/cJSON.h"
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

int CGeoJsonParser::LoadGeoJsonContent(const char* geojsonfile, std::vector<CountryInfo>& countryInfoVec)
{
	countryInfoVec.clear();
	std::ifstream src_json_file(geojsonfile, ios::in);
	if (!src_json_file.good())
	{
		return countryInfoVec.size();
	}

	std::stringstream buffer;  
	buffer << src_json_file.rdbuf();  
	std::string contents(buffer.str());
	cJSON *json = cJSON_Parse(contents.c_str());
	if (json)
	{
		cJSON* jsonChild      = json->child;
		while (jsonChild)
		{
			string strKey(jsonChild->string);
			if (strKey == "type")
			{
			}
			else if (strKey == "crs")
			{
			}
			else if (strKey == "features")
			{
				cJSON *pCountrySSjson = jsonChild->child;
				while (pCountrySSjson)
				{
					cJSON *pCountryjson = pCountrySSjson->child;
					CountryInfo countryInfo;
					while(pCountryjson)
					{
						string strCountryKey(pCountryjson->string);
						if (strCountryKey == "type")
						{
						}
						else if (strCountryKey == "id")
						{
							countryInfo.mCountryId = pCountryjson->valuestring;
						}
						else if (strCountryKey == "properties")
						{
							cJSON* pProperty = pCountryjson->child;
							while(pProperty)
							{
								string strProKey = pProperty->string;
								if (strProKey == "fips")
								{
									if (pProperty->valuestring)
									{
										countryInfo.mCountryId = pProperty->valuestring;
									}
								}
								else if (strProKey == "name")
								{
									countryInfo.mCountryName = pProperty->valuestring;
								}
								else if (strProKey == "lon")
								{
									countryInfo.mCountryCenter.x = (float)pProperty->valuedouble;
								}
								else if (strProKey == "lat")
								{
									countryInfo.mCountryCenter.y = (float)pProperty->valuedouble;
								}
								pProperty = pProperty->next;
							}
							//cout<< countryInfoVec.size() << ";Country:"<< countryInfo.mCountryId<<","<<countryInfo.mCountryName<<",("<<countryInfo.mCountryCenter.x <<","<< countryInfo.mCountryCenter.y <<")"<< endl;
						}
						else if (strCountryKey == "geometry")
						{
							cJSON *pGeometry = pCountryjson->child;
							bool isMultiPolygon = false;
							while (pGeometry)
							{
								string strGeoKey(pGeometry->string);
								if (strGeoKey == "type")
								{
									string strvalue = pGeometry->valuestring;
									if (strvalue == "Polygon")
									{
										isMultiPolygon = false;
									}
									else if (strvalue == "MultiPolygon")
									{
										isMultiPolygon = true;
									}
								}
								else if (strGeoKey == "coordinates")
								{
									cJSON* pPolygon = pGeometry->child;
									if (pPolygon && isMultiPolygon == false)
									{
										cJSON* pPolygon_ = pPolygon->child;
										TXPolygon polygon;
										while(pPolygon_)
										{
											Vector2F point;
											point.x   = pPolygon_->child->valuedouble;
											point.y   = pPolygon_->child->next->valuedouble;
											polygon.push_back(point);
											pPolygon_ = pPolygon_->next;
										}
										
										countryInfo.mCountryBoundary.push_back(polygon);
									}
									else if (pPolygon && isMultiPolygon == true)
									{
										cJSON* pPolygon__ = pPolygon->child;
										while (pPolygon__)
										{
											TXPolygon polygon;
											cJSON* pPolygon_ = pPolygon__->child;
											while(pPolygon_)
											{
												Vector2F point;
												point.x   = pPolygon_->child->valuedouble;
												point.y   = pPolygon_->child->next->valuedouble;
												polygon.push_back(point);
												pPolygon_ = pPolygon_->next;
											}
											countryInfo.mCountryBoundary.push_back(polygon);
											pPolygon__ = pPolygon__->next;
										}	
									}
								}
								pGeometry = pGeometry->next;
							}
						}
						pCountryjson = pCountryjson->next;
					}
					countryInfoVec.push_back(countryInfo);
					pCountrySSjson = pCountrySSjson->next;
				}
			}
			jsonChild = jsonChild->next;
		}
	}
    cJSON_Delete(json);
	return countryInfoVec.size();
}