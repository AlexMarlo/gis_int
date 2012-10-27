#ifndef GISMAPSTRUCTS_H_
#define GISMAPSTRUCTS_H_

#include <string>
#include <map>
#include <vector>
#include <utility>
#include <iostream>

#include <mapapi.h>

#undef max
#undef min
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

namespace gis
{

enum AGState
{
	AGSNone = 0,
	AGSSelect,
	AGSZoomIn,
	AGSZoomOut
};

class AGMAP
{
public:
	AGMAP();
	void clear();
	void init( HMAP par_hmap);
	void Print();

public:
	HMAP hmap;
	long int width;
	long int height;
	std::string path;
	double scale;
	double minScale;
	double maxScale;
	int bright;
	int contrast;
	int layerCount;
};

class AGSITE
{
public:
	AGSITE();
	void clear();
	void init( AGMAP par_agmap, HSITE par_hsite);
	void Print();

public:
	AGMAP agmap;
	HSITE hsite;
	HRSC hrsc;
	std::string path;
	CREATESITE cs;
	std::string rscPath;
	int layerCount;
};

class MapData
{
public:
	MapData();
	void clear();

public:
	AGMAP agmap;
	AGSITE agtmpsite;
	std::vector< AGSITE> agsites;
};

} /* namespace gis */

#endif //GISMAPSTRUCTS_H_
