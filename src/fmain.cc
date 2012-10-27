#include <math.h>

#include "fmain.h"

MapData::MapData()
{
	clear();
}

void MapData::clear()
{
	agmap.clear();
	agtmpsite.clear();
	agsites.clear();
}

AGMAP::AGMAP()
{
	clear();
}

void AGMAP::clear()
{
	hmap = 0;
	width = 0;
	height = 0;
	path = "";
	scale = 0;
	minScale = 4000;
	maxScale = 1000000;
}

void AGMAP::init( HMAP par_hmap)
{
	char str[4096];
	hmap = par_hmap;
	mapGetPictureSize( hmap, &width, &height);
	scale = mapGetRealShowScale( hmap);
	layerCount = mapGetLayerCount( hmap);
	strcpy( str, mapGetMapPath( hmap));
	path = std::string( str);
}

void AGMAP::Print()
{
	std::cout << "AGMAP:" << std::endl;
	std::cout << "hmap       = " << hmap << std::endl;
	std::cout << "width      = " << width;
	std::cout << "height     = " << height << std::endl;
	std::cout << "path       = '" << path << "'" << std::endl;
	std::cout << "scale      = " << scale << std::endl;
	std::cout << "minScale   = " << minScale << std::endl;
	std::cout << "maxScale   = " << maxScale << std::endl;
	std::cout << "bright     = " << bright << std::endl;
	std::cout << "contrast   = " << contrast << std::endl;
	std::cout << "layerCount = " << layerCount << std::endl;
}

AGSITE::AGSITE()
{
	clear();
}

void AGSITE::clear()
{
	hsite = 0;
	path = "";
	memset( &cs, 0, sizeof(CREATESITE));

	hrsc = 0;
	rscPath = "";
}

void AGSITE::init( AGMAP par_agmap, HSITE par_hsite)
{
	char str[4096];

	agmap = par_agmap;
	hsite = par_hsite;
	strcpy( str, mapGetSiteFileName( agmap.hmap, hsite));
	path = std::string( str);
	hrsc = mapGetRscIdent( agmap.hmap, hsite);
	mapGetRscFileName( hrsc, str, 4096);
	rscPath = std::string( str);
	layerCount = mapGetSiteLayerCount( agmap.hmap, hsite);
}

void AGSITE::Print()
{
	std::cout << "AGSITE:" << std::endl;
	agmap.Print();
	std::cout << "hsite      = " << hsite << std::endl;
	std::cout << "hrsc       = " << hrsc << std::endl;
	std::cout << "path       = '" << path << "'" << std::endl;
	std::cout << "rscPath    = '" << rscPath << "'" << std::endl;
	std::cout << "layerCount = " << layerCount << std::endl;
}

/* RIP */
