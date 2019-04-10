/* IMPORTANT NOTES:
 * This is just a sample code.
 * You may/should change/delete many parts of this file.
 * You can just get some hints on how to start your code here.
 * DO NOT consider this file as a template. 
 */
#include <iostream>
#include "bmplib.h"
#include <cstdlib>
#include <cmath>
#define PATH_IN "./EE355/ee355-lab6-PengfeiChang/"
#define PATH_OUT "./EE355/ee355-lab6-PengfeiChang/"
using namespace std;

void showMainMenu(){
    cout << "0: Exit \n";
    cout << "1: Flip 90 degrees \n";
    cout << "2: Flip 180 degrees \n";
    cout << "3: Mirror \n";
    cout << "4: Gray Scaling \n";
    cout << "5: Color inversion \n";

    cout << "6: Zoom in \n";
}


void flip90(string filename, unsigned char dest[SIZE][SIZE][3]){

    unsigned char src[SIZE][SIZE][3];
    readRGBBMP(filename.c_str(), src);

    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            for (int k=0; k<3; k++)
            {
                dest[i][j][k] = src[SIZE-1-j][i][k];
            }
        }
    }

   
}

void flip180(string filename, unsigned char dest[SIZE][SIZE][3]){

    unsigned char src[SIZE][SIZE][3];
    readRGBBMP(filename.c_str(), src);

    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            for (int k=0; k<3; k++)
            {
                dest[i][j][k] = src[SIZE-1-i][SIZE-1-j][k];
            }
        }
    }
   
}
void mirror(string filename, unsigned char dest[SIZE][SIZE][3]){

    unsigned char src[SIZE][SIZE][3];
    readRGBBMP(filename.c_str(), src);
    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            for(int k=0; k<3; k++)
            {
                dest[i][j][k] = src[i][SIZE-j][k];
            }
        }

    }

   
}

void gray_saling(string filename, unsigned char dest[SIZE][SIZE]){

    unsigned char src[SIZE][SIZE][3];
    readRGBBMP(filename.c_str(), src);
 

    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            unsigned char r = src[i][j][0];
            unsigned char g = src[i][j][1];
            unsigned char b = src[i][j][2];
            dest[i][j] = (unsigned char)(.299*r + .587*g + .114*b);
        }   
    }
   
}

void color_inversion(string filename, unsigned char dest[SIZE][SIZE][3]){

    unsigned char src[SIZE][SIZE][3];
    readRGBBMP(filename.c_str(), src);

    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            for (int c=0; c<3; c++) {
                dest[i][j][c] = 255-src[i][j][c];
            }
        }
    }
   
   
}

void zoom(string filename, unsigned char dest[SIZE][SIZE][3]){

    unsigned char src[SIZE][SIZE][3];
    readRGBBMP(filename.c_str(), src);

   
}

int main(){

    int option;
    unsigned char res [SIZE][SIZE][3];
    while(1){
        cout << "\033[2J\033[1;1H";
        showMainMenu();
        cout << "Select an option: ";
        cin >> option;
        switch(option){
            case 0:
                cout << "EXIT \n";;
                return 0;
            case 1: 
                cout << "Flip 90 degrees \n";
                flip90("./fruit.bmp", res);
                writeRGBBMP("image_flip90.bmp", res);
                break;
            case 2: 
                cout << "Flip 180 degrees \n";;
                flip180("./fruit.bmp", res);
                writeRGBBMP("image_flip180.bmp", res);
                break;
            case 3:
                cout << "Mirror \n";
                mirror("./fruit.bmp", res);
                writeRGBBMP("image_mirror.bmp", res);
                break;
            case 4:
                cout << "Gray Scaling \n";
                unsigned char dest[SIZE][SIZE];
                gray_saling("./fruit.bmp", dest);
                writeGSBMP("image_gray_scaling.bmp", dest);
                break;

            case 5:
                cout << "Color inversion \n";
                color_inversion("./fruit.bmp", res);
                writeRGBBMP("image_color_inversion.bmp", res);
                break;
            case 6:
                cout << "Zoom in \n";
                zoom("./fruit.bmp", res);
                writeRGBBMP("image_zoom.bmp", res);
                break;

            default:
                cout << "OPTION NOT FOUND! \n";
                break;
        }
    }

    return 0;
}
