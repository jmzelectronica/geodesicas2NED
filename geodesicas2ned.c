#include <stdio.h>
#include <math.h>

// Definir la estructura para las coordenadas geodésicas
typedef struct {
    double lat;     // Latitud en grados decimales
    double lon;     // Longitud en grados decimales
    double alt;     // Altitud en metros
} GeodeticCoord;

// Definir la estructura para las coordenadas NED
typedef struct {
    double north;   // Componente Norte en metros
    double east;    // Componente Este en metros
    double down;    // Componente Abajo en metros
} NEDCoord;

// Función para convertir coordenadas geodésicas a coordenadas NED
NEDCoord geodetic_to_ned(GeodeticCoord geodetic, GeodeticCoord reference) {
    NEDCoord ned;
    double lat_ref_rad = reference.lat * M_PI / 180.0;
    double lon_ref_rad = reference.lon * M_PI / 180.0;
    double lat_rad = geodetic.lat * M_PI / 180.0;
    double lon_rad = geodetic.lon * M_PI / 180.0;

    double dLat = lat_rad - lat_ref_rad;
    double dLon = lon_rad - lon_ref_rad;
    double sin_lat_ref = sin(lat_ref_rad);
    double cos_lat_ref = cos(lat_ref_rad);
    double sin_lat = sin(lat_rad);
    double cos_lat = cos(lat_rad);

    double Rn = 6378137.0 / sqrt(1.0 - 0.006694379990141 * sin_lat_ref * sin_lat_ref);
    double Re = Rn * cos_lat_ref;

    ned.north = dLat * (Rn + geodetic.alt) - dLon * sin_lat_ref * cos_lat_ref * Re;
    ned.east = dLon * cos_lat_ref * Re;
    ned.down = -geodetic.alt;

    return ned;
}

int main() {
    // Coordenadas geodésicas de punto objetivo
    GeodeticCoord target_coord = {40.7128, -74.0060, 10}; // Latitud, longitud, altitud (Nueva York, por ejemplo)

    // Coordenadas geodésicas de referencia (punto de origen)
    GeodeticCoord reference_coord = {0, 0, 0}; // Latitud, longitud, altitud (punto de origen)

    // Convertir coordenadas geodésicas a coordenadas NED
    NEDCoord ned_coord = geodetic_to_ned(target_coord, reference_coord);

    // Mostrar las coordenadas NED
    printf("Coordenadas NED:\n");
    printf("Norte: %.2f m\n", ned_coord.north);
    printf("Este: %.2f m\n", ned_coord.east);
    printf("Abajo: %.2f m\n", ned_coord.down);

    return 0;
}
