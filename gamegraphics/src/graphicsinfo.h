#ifndef GRAPHICS_INFO_H
#define GRAPHICS_INFO_H



typedef struct graphics_info_t { //all units MKS: meters, kilograms, seconds
    int ID;
    CollidableObject *obj
    int x;
    int y;
    int z;
    char* File; //BITMAP to used in rendering

} graphicsInfo;
#endif
