#ifndef ANTPOSITION_TYPE_H
#define ANTPOSITION_TYPE_H   /* to avoid repetition of this file include  */

/*-------------------------- Antenna Coordinates Structure ----------------------------------*/

typedef struct
{
    double time;			// time instant for antenna coordinates (sec)
    int    state;			// 0 - transient state, 1 - rotation
    int scan;				// revolution #
    double h;				// current height over sea level (m)
    double az_encoder;		// primary antenna beam azimuth relative ship direction (rad)
    double az;				// calculated antenna beam azimuth relative North direction (rad)
    double azvel;			// antenna rotation speed (rad/sec)
    double el;				// radar platform inclination relative horizon for the current azimuth angle
    double elvel;			// not used

} AntPosition_type;


#endif
