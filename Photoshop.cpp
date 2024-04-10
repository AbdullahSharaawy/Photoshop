//  Purpose: this the photoshop able to do these the operations on the iamge: flip , gray scale , black and white , invers , darken and light 
// Author 1: Ahmed Magdy Hassan Ali , 20230030 , Section 19
// Author 2: Abdullah Adel Eid Sharaawy , 20230522 , Section 20
// Author 3: Zeyad Elsayed mahmoud youssef , 20230153 , Section 20
// Emails: abdallahsharawy200@gmail.com , zsyd48827@gmail.com , ahmed900900gh7n10@gmail.com 
// ID1:20230030-he did these function: GrayscaleConversion() and DarkenandLightenImage()
/* ID2:20230522-he did these functions:ReadFileName(),convert_to_BlackAndWhite(string  n_image), Convert_to_FlippedVertical(string  n_image),
Convert_to_FlippedHorizontal(string  n_image), Save(string n_image,Image image),BlackAndWhite(string n_image),FlippedHorizontal(string n_image),
FlippedVertical(string  n_image);
*/
// ID3:20230153-he did these funcion: invers(Image n_image) and InversImage(string n_image)
// Version : v1.0
// Date    : 27/03/2024
#include<fstream>
#include "Image_Class.h"
#include<string>
#include<cmath>
#include<algorithm>
#include<regex>
#include<limits>
#include<iostream>
using namespace std;
string ReadFileName();
string ReadNewName();
Image convert_to_BlackAndWhite(string  n_image);
Image Convert_to_FlippedVertical(string  n_image);
Image Convert_to_FlippedHorizontal(string  n_image);
void Save(string n_image,Image image);
void BlackAndWhite(string n_image);
void FlippedHorizontal(string n_image);
void FlippedVertical(string  n_image);
Image inverse(Image n_image);
void InverseImage(string n_image);
Image GrayscaleConversion(string  n_image);
Image DarkenandLightenImage(string  n_image);
void GrayScale(string n_image);
void DarkenAndLighiten(string n_image);
int ReadOneDiminsion(string message);
Image Resize(float n_width , float n_height , string  n_image);
void change_diminsions(float n_width , float n_height , string n_image);
bool IsValid_index(int index , int diminsion);
int ReadIndex(string message , int diminsion);
Image Crop(string n_image);
void Crop_( string n_image);
void StartPhotoshop();
int main()
{
    //start the program
    StartPhotoshop();
}
void StartPhotoshop()
{
    string n_image;
    n_image=ReadFileName();
    int choise;
    //read name of file from the user
    cout<<"what do you want like to do ! \n";
        cout<<"1] Black and white \n";
        cout<<"2] flipped vertical \n";
        cout<<"3] flipped horizontal \n";
        cout<<"4] Grayscale \n"<<"5] Darken and lighten \n";
        cout<<"6] Inverse \n";
        cout<<"7] Resize \n";
        cout<<"8] Crop \n";
        cout<<"9] Exist \n";
    do
    {
        cout<<"please enter a number from 1 to 7! ";
        cin>>choise;
        //input your choise agian if it is not valid
        if(cin.fill())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    } while (choise !=1 && choise !=2 && choise !=3 && choise !=4 && choise !=5 && choise !=6 && choise !=7 && choise !=8 && choise !=9);
    switch (choise)
    {
        case 1:
        BlackAndWhite(n_image);
        break;
        case 2:
        FlippedVertical( n_image);
        break;
        case 3:
        FlippedHorizontal( n_image);
        break;
        case 4:
        GrayScale(n_image);
        break;
        case 5:
        DarkenAndLighiten(n_image);
        break;
        case 6:
        InverseImage(n_image);
        break;
        //exist from the program
        case 7:
        change_diminsions(ReadOneDiminsion("please enter the new width! ") , ReadOneDiminsion("please enter the new height! ") ,  n_image);
        break;
        case 8:
        Crop_(n_image);
        break;
        case 9:
        return;
        break;

    }
    StartPhotoshop();
}
//read name of image from the user
string ReadFileName()
{
     string n_image;
     const regex pattern("[^\\s]+(.*?)\\.(jpg|jpeg|png|gif|JPG|JPEG|PNG|GIF)$");
     cout<<"please enter the name of image where it ends with .(jpg|jpeg|png|gif|JPG|JPEG|PNG|GIF)! ";
     //read name from the user
     getline(cin,n_image);
     ifstream image(n_image);
     //iput the name again if it is not valid
        while(!regex_match(n_image,pattern) || !ifstream(n_image).good())
     {
        if(!regex_match(n_image,pattern))
        {
        cout<<"Invalid filename format. Please enter a valid name ending with an image extension! ";
        getline(cin,n_image);
        continue;
       }
       if(!ifstream(n_image).good()){
        cout<<"this image does not exist, please enter a valid name ";
        getline(cin,n_image);
        continue;}
     }
     return n_image;
}
string ReadNewName()
{
     string n_image;
     const regex pattern("[^\\s]+(.*?)\\.(jpg|jpeg|png|gif|JPG|JPEG|PNG|GIF)$");
     cout<<"please enter the name of image where it ends with .(jpg|jpeg|png|gif|JPG|JPEG|PNG|GIF)! ";
     //read name from the user
     getline(cin,n_image);
     //iput the name again if it is not valid
        while(!regex_match(n_image,pattern) )
     {
        if(!regex_match(n_image,pattern))
        {
        cout<<"Invalid filename format. Please enter a valid name ending with an image extension! ";
        getline(cin,n_image);
       }
     }
     return n_image;
}
//convert the image to Black and White
Image convert_to_BlackAndWhite(string  n_image)
{
    Image image(n_image);
    int avg=0;   
    //i represent about number of row
    for(int i=0 ; i<image.width ; ++i)
    {
        //j represent about number of column
        for(int j=0 ; j<image.height;++j)
        {
            //convert each pixel to gray scale
             for(int k=0 ; k<image.channels;++k)
        {
            avg+=image(i,j,k);
        }   
        avg/=3;
        //convert each pixel to black or white
        for(int k=0 ; k<image.channels;++k)
        {
            if(avg>128)image(i,j,k)=255; //if bright
            else image(i,j,k)=0; 
        }   
        }
    }
    return image;
}
//save the new image in the disk
void Save(string n_image,Image image)
{
      int choise;
 do
{
 cout<<"are you want save it!\n";
 cout<<"1] save \n2] No save\n";
 cin>>choise;
 //input your choise agian if it is not equal 1 or 2
 if(cin.fill())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
}while(choise!=1 && choise!=2);  
if(choise==1)
{
    do
{
    cout<<"1] save it with the same name \n2] save it with a new name\n";
    cin>>choise;
    //input your choise agian if it is not equal 1 or 2
    if(cin.fill())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    
}while(choise!=1 && choise!=2);
if(choise==1)image.saveImage(n_image);
else 
{
    
    n_image=ReadNewName();
    image.saveImage(n_image);
}
} 
else StartPhotoshop();   
  cout<<"the process finished sucsessfuly (* _ *)\n";
}

void BlackAndWhite(string n_image)
{
    Save(n_image,convert_to_BlackAndWhite( n_image));
}
void FlippedVertical(string n_image)
{
    Save(n_image,Convert_to_FlippedVertical(n_image));
}
void FlippedHorizontal(string n_image)
{
    Save(n_image,Convert_to_FlippedHorizontal(n_image));
}
// make the image Flipped Vertical 
Image Convert_to_FlippedVertical(string  n_image)
{
    Image image(n_image);   
    int w=image.width;
    int h=image.height;
    Image image2(w,h);   
    //i represent about number of row
    for(int i=0 ; i<image.width ; ++i)
    {
        //j represent about number of column
        for(int j=0 ; j<image.height;++j)
        {
            for(int k=0 ; k<3 ; ++k)
            {
                  image2(i,j,k)=image(i,image.height-j-1,k);   
            }
        }
        
    }
    return image2;
}
Image Convert_to_FlippedHorizontal(string  n_image)
{
    Image image(n_image);   
    int w=image.width;
    int h=image.height;
    Image image2(w,h);   
    //i represent about number of row
    for(int i=0 ; i<image.width ; ++i)
    {
        //j represent about number of column
        for(int j=0 ; j<image.height;++j)
        {
            for(int k=0 ; k<3 ; ++k)
            {
                  image2(i,j,k)=image(image.width-i-1,j,k);   
            }
        }
        
    }
    return image2;
}

//function to do Grayscale conversion
Image GrayscaleConversion(string n_image){
//taking the photo name from the user with the extension to apply the filter on it
Image image(n_image);
//turning image into gray
for(int i = 0;i < image.width;i++){
    for(int j = 0;j < image.height;j++){
        unsigned int grayscale = 0;
        for(int k = 0;k < 3;k++){
            if(k == 0){
                grayscale += 0.21 * image(i,j,k);
            }
            else if(k==1){
                grayscale += 0.72 * image(i,j,k);
            }
            else{
                grayscale += 0.07 * image(i,j,k);
            }
        }
        for(int k = 0;k < 3;k++){
            image(i,j,k) = grayscale;
        }
    }
}
//saving the image after doing the effects
return image;
}
//function to darken the image by 50% or lighten it by 50%
Image DarkenandLightenImage(string n_image){
//choosing between lighten or darken the image
cout<<"enter 1 if you want to darken an image,enter 2 if you want to lighten an image:";
string choosenfilter;
getline(cin,choosenfilter);
regex validation2("[1|2]");
//validation of the user choice in case of darken or lighten
while(!regex_match(choosenfilter,validation2)){
    cout<<"you didn't enter 1 or 2,enter 1 if you want to darken an image,enter 2 if you want to lighten an image:";
    getline(cin,choosenfilter);
}
//taking the image name with extension to apply filter on it
Image image(n_image);
//darken the image by 50%
if(choosenfilter == "1"){
    for(int i = 0;i < image.width;i++){
        for(int j = 0;j < image.height;j++){
            for(int k = 0;k < 3;k++){
                image(i,j,k) = image(i,j,k) * 0.5;
            }
        }
    }
    //saving the image after doing the effects on it
    return image;
}
//lighten the image by 50%
else if(choosenfilter == "2"){
    for(int i = 0;i < image.width;i++){
        for(int j = 0;j < image.height;j++){
            for(int k = 0;k < 3;k++){
                double intensity = image(i,j,k) * 1.5;
                if(intensity < 255){
                    image(i,j,k) = intensity;
                }
                else if(intensity >= 255){
                    image(i,j,k) = 255;
                }
                }
            }
        }
 //saving the image after doing the effects on it
    return image;
}
}
//function to get the inverse photo
Image inverse(Image image)
{
   // create a new amege with the same width and height.
    Image new_image(image.width,image.height);
    //enter to the loop to modify the new photo.
    //w is represnt the number of the row .
    for(int w =0;w<image.width;w++)
    {
        //h is represnt the number of the column .
        for (int h= 0;h<image.height;h++)
        {
            //h is represnt the number of the pixels .
            for(int p=0; p<3;p++)
            {
                //we can get the inverse photo by subtract the original form 255.
                new_image(w,h,p)=255-image(w,h,p);
            }
        }
    }

    return new_image;
}
void InverseImage(string n_image)
{
    //save the inversed image .
    Save(n_image,inverse(n_image));
}
void GrayScale(string n_image)
{
    //save the inversed image .
    Save(n_image,GrayscaleConversion(n_image));
}
void DarkenAndLighiten(string n_image)
{
    //save the inversed image .
    Save(n_image,DarkenandLightenImage(n_image));
}
bool IsValid_index(int index , int diminsion)
{

    return (index<diminsion && index>-1)?  true :  false;
}
int ReadIndex(string message, int dimension) {
  int index;
  while (true) {
    cout << message;
    cin >> index;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input. Please enter a valid index! ";
    } else if (IsValid_index(index, dimension)) {
      break;
    } else {
      cout << "Index out of range. Please enter a value between 0 and " << dimension - 1 << "! ";
    }
  }
  return index;
}

Image Crop(string n_image)
{
    Image image(n_image);  
    int width,height,x,y;
    width=ReadOneDiminsion("please enter the new width! ");
    height=ReadOneDiminsion("please enter the new height! ");
    cout<<"please enter x and y input as the starting point (upper left corner of the part to keep) \n";
    x=ReadIndex("please enter x, (x,y)! " ,image.width);
    y=ReadIndex("please enter y, (x,y)! ",image.height);
    int coutner_h, coutnter_w=width;
    Image image2(width,height);   
    //i represent about number of row
    for(int i=x ; coutnter_w>0 ; ++i)
    {
        coutner_h=height;
        //j represent about number of column
        for(int j=y ; coutner_h>0;++j)
        {
            for(int k=0 ; k<3 ; ++k)
            {
                  image2(i-x,j-y,k)=image(i,j,k);   
            }
            --coutner_h;
        }
        --coutnter_w;
    }
    
    return image2;
}
void Crop_( string n_image)
{
    Save(n_image,Crop(n_image));
}
int ReadOneDiminsion(string message)
{
    int diminsion;
    do
    {
        cout<<message;
        cin>>diminsion;
        if(cin.fill())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    } while (diminsion<=0);
    return diminsion;
}
Image Resize(float n_width , float n_height , string n_image)
{
    Image original_img(n_image);
    Image n_img(n_width,n_height);
     int original_width=original_img.width;
     int original_height=original_img.height;
     float scale_x ,scale_y;
     scale_x=original_width/n_width;
     scale_y=original_height/n_height;
     //i represent about number of row
     for(int i=0 ; i<n_width ; i++)
    {
        //j represent about number of column
        for(int j=0 ; j<n_height;j++)
        {
            for(int k=0 ; k<3 ; ++k)
            {
                  n_img(i,j,k)=original_img(round(i*scale_x),round(j*scale_y),k);   
            }
        }
        
    }
     
    return n_img;
}
void change_diminsions(float n_width , float n_height , string n_image)
{
    Save(n_image,Resize( n_width ,  n_height ,  n_image));
}

