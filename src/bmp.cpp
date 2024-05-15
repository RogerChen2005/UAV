#include <bmp.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t signature;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t pixelDataOffset;
    uint32_t dibHeaderSize;
    uint32_t width;
    uint32_t height;
    uint16_t colorPlanes;
    uint16_t bitsPerPixel;
    uint32_t compressionMethod;
    uint32_t imageSize;
    uint32_t horizontalResolution;
    uint32_t verticalResolution;
    uint32_t colorsInPalette;
    uint32_t importantColors;
};
#pragma pack(pop)

void rgb::change (const unsigned char r,const unsigned char g,const unsigned char b){
    this->r = r;
    this->g = g;
    this->b = b;
}

bool writeBMP(const char* filename, rgb* pixels, int width, int height) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Error: Failed to open file for writing: " << filename << std::endl;
        return false;
    }
    BMPHeader header;
    header.signature = 0x4D42; // BM
    header.fileSize = sizeof(BMPHeader) + width * height * sizeof(char);
    header.reserved1 = 0;
    header.reserved2 = 0;
    header.pixelDataOffset = sizeof(BMPHeader);
    header.dibHeaderSize = 40;
    header.width = width;
    header.height = height;
    header.colorPlanes = 1;
    header.bitsPerPixel = 24; // Change to 32 if you want 32-bit BMP
    header.compressionMethod = 0;
    header.imageSize = width * height * sizeof(char);
    header.horizontalResolution = 2835; // 72 DPI
    header.verticalResolution = 2835; // 72 DPI
    header.colorsInPalette = 0;
    header.importantColors = 0;

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    file.write(reinterpret_cast<const char*>(pixels), width*height*3);
    file.close();
    return true;
}

bmp::bmp(char ** data,int width,int height)
{
    this->width = width;
    this->height = height;
    this->_data = new rgb[width*height];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++){
            int start = i*width+j;
            unsigned char dat = data[i][j]*255;
            this->_data[start].change(dat,dat,dat);
        }
    }
}

bmp::~bmp(){
    delete[] this->_data;
}

void bmp::draw(std::vector<pos>& path,double h){
    int length = path.size();
    for(const pos& x:path){
        this->_data[x.x+x.y*this->width].change(255*(1-h),255*h,255*h);
    }
}

void bmp::exports(const char * filename){
    if(writeBMP(filename,this->_data,this->width,this->height)){
        std::cout << "Output Successful!" << std::endl;
    }
}