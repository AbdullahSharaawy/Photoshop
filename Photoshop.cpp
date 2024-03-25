#include "Image_Class.h"
#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
string ReadFileName();
int ReadOneDiminsion(string message);
Image Resize(float n_width , float n_height , string  n_image);
void change_diminsions(float n_width , float n_height , string n_image);
Image convert_to_BlackAndWhite(string  n_image);
Image Convert_to_FlippedVertical(string  n_image);
void Save(string n_image,Image image);
void BlackAndWhite(string n_image);
void FlippedVertical(string  n_image);
int main()
{
    string n_image;
    char cha;
    n_image=ReadFileName();
    do
    {
        cout<<"what do you want like to do ! \n";
        cout<<"1] Black and white \n";
        cout<<"2] flipped vertical \n";
        cout<<"3] flipped vertical \n";
        cout<<"4] Resize \n";
        cin>>cha;
    } while (cha !='1' && cha !='2' && cha !='4');
    switch (cha)
    {
        case '1':
        BlackAndWhite(n_image);
        break;
        case 2:
        FlippedVertical( n_image);
        break;
        case 3:
        BlackAndWhite(n_image);
        break;
        case '4':
        change_diminsions(ReadOneDiminsion("please enter the width ") , ReadOneDiminsion("please enter the height ") , n_image);
        break;
    default:
        break;
    }
}
string ReadFileName()
{
     string n_image;
     cout<<"please enter the name of file! ";
     //read name from the user
     getline(cin,n_image);
     return n_image;
}
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
void Save(string n_image,Image image)
{
     char YN;
 do
{
 cout<<"are you want save it! Y/N ";
 cin>>YN;
}while(YN!='Y' && YN!='N');  
if(YN=='Y')
{
    do
{
    cout<<"are you want save it with the same name or a new one! Y/N ";
    cin>>YN;
}while(YN!='Y' && YN!='N');
if(YN=='Y')image.saveImage(n_image);
else 
{
    cout<<"please enter the new name ";
    cin.ignore(1,'\n');
    //read name from the user
    getline(cin,n_image);
    image.saveImage(n_image);
}
}    
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
                  image2(i,j,k)=image(i,image.height-j,k);   
            }
        }
        
    }
    return image2;
}
Image Crop(string  n_image)
{
    Image image(n_image);   
    int w=image.width;
    int h=image.height;
    int width,height,x,y;
    cout<<"please enter the width and height /n";
    cin>>width>>height;
    cout<<"please enter x and y input as the starting point (upper left corner of the part to keep) /n";
    cin>>x>>y;
    Image image2(width,height);   
    //i represent about number of row
    for(int i=x ; i<width+x ; ++i)
    {
        //j represent about number of column
        for(int j=y ; j<height+y;++j)
        {
            for(int k=0 ; k<3 ; ++k)
            {
                  image2(i,j,k)=image(i,j,k);   
            }
        }
        
    }
    return image2;
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
    } while (diminsion<0);
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
