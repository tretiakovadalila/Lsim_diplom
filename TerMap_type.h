#ifndef TERMAP_TYPE_H
#define TERMAP_TYPE_H

const double ANGLE_LSB	= 0.0001;	// Grazing and Elevation Angle LSB (rad)
const int NTILESMAX     = 2000000;	// 1000000;
const double H_WITHOUT_MAP=150.;			// heigh of stand point MFR above sea level without Terrain Map (m)

/*                   Surface Type Designation
                1  - highly densed urban area,
                2  - low densed urban area,
                3  - wooden area,
                4  - paddy, wheat, vegetable field,
                5  - paddy, marsh area,
                6  - sea area,
                7  - lake,river
*/

/* Out file structure with map features in radar Az-range grid */
typedef struct
{
    char title[128];
    short longitude[3];        // Radar stand point longitude: deg, min, sec
    short latitude[3];         // Radar stand point latitude: deg, min, sec
    short NAc,					// Number of cells on Azimuth (360/AzStep)
        NRc;					// Number of cells on Range (Rmax/RStep)
    double h0,					// Antenna location height in m above sea level = StandPointHeigt+ANT_HEIGHT
        RStep,				// Step on Range (m)
        AzStep,				// Step on Azimuth (rad)
        ElMax,				// Max of screening angle (rad)
        ElMin;				// Min of screening angle (rad)
    double reserved1;
    double reserved2;
    double reserved3;
    struct
    {
        short type;				// Surface element type
        short height;				// Surface element height (m)
        short Grazing;			// Sine of grazing angle (LSB=ANGLE_LSB). Grazing = 0 means invisible point
        short Elevation;			// Screening angle (LSB=ANGLE_LSB rad)
    } tile[NTILESMAX];			// Azimuth counts clockwise from the North!
} TerMap_type;

typedef struct             // Working map
{
    short n,                   // Number of points
        type,                  // Surface type
        height;                // Surface altitude (m)
    float rcs,                 // Visible area estimate (RCS)
        elev;                // Elevation
} WORK_MAP;

#endif
