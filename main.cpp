#include <iostream>

#include <signal.h>
#include <stdlib.h>

/*
#include "BigDecimal/BigDecimal.h"
#include "BigDecimal/BigDecimal.cpp"
*/
using namespace std;


#include <sstream>
template <typename T>
std::string to_string(T value)
{
  //create an output string stream
  std::ostringstream os ;

  //throw the value into the string stream
  os << value ;

  //convert the string stream into a string and return
  return os.str() ;
}
#include <ctime>

#include <stdio.h>


#include <sys/ioctl.h>

#include "conio.h"

#include "complex.cpp"

#include <cmath> 

#include <iomanip>

#include <string>

#include "ppm.hpp"



const int WIDTH = 1200;
const int HEIGHT = 600;

int ROWS = 45;
int COLS = 190;



long int MAX_ITR = 1;

long double offsetX = 0.0;
long double offsetY = 0.0;

long double zoom = 0.05;

unsigned int rgb[3];

long double magnitude = 0;

void MAX_ITERATIONS()
{
	/* SOURCE: https://math.stackexchange.com/questions/16970/a-way-to-determine-the-ideal-number-of-maximum-iterations-for-an-arbitrary-zoom */
	//MAX_ITR = int(sqrt(2 * sqrt(abs(1-sqrt(5*(1/zoom))))) * 66.5);
	//MAX_ITR = sqrt(2 * sqrt(abs(1-sqrt(5*(1/zoom))))) * 66.5;
	MAX_ITR = ceil(abs(log(zoom)*log(zoom)*log(zoom)));
	if (MAX_ITR <= 64)
	    MAX_ITR = 64;
	
}

int mandelbrot(complex_number cn)
{
	//main_real = cn.real;
	//main_im = cn.im;
	complex_number last_cn = cn;
	complex_number original = cn;
	
	MAX_ITERATIONS();

	for(int x = 0; x < MAX_ITR; ++x)
	{
		complex_number pow_cn = last_cn.sqr();
		complex_number new_cn = pow_cn + original;
		last_cn = new_cn;
		
		//cout << last_cn.im << " and " << last_cn.real;
		long double radius = ((last_cn.im*last_cn.im) + (last_cn.real*last_cn.real));
		//cout << " equals " << radius << endl;
		if (radius > 4)
		{
			//cout << endl<<last_cn.im << " " << last_cn.real << endl;
			magnitude = radius;
			return x;
		}
	}
	return -1;
}


/* LINEAR INTERPOLATION: 
 * http://stackoverflow.com/questions/345187/math-mapping-numbers
 * https://en.wikipedia.org/wiki/Linear_interpolation
 * Y = (X-A)/(B-A) * (D-C) + C */
int map_num(double value, double minIn, double maxIn, double minOut, double maxOut)
{
	return (value - minIn)/(maxIn-minIn) * (maxOut - minOut) + minOut;
	//return ceil((value-minIn)/(maxIn-minIn)*(maxOut-minIn)+minOut);
}

unsigned int *getCharacter(int iter)
{
	
	//int part_iter = (iter * 255) / MAX_ITR;
	int part_iter = map_num(iter,0,MAX_ITR,30,250);

	//part_iter = 255 - part_iter;


/*
	int r = 200;
	int g = 255;
	int b = 100;
*/
	unsigned int r;
	unsigned int g;
	unsigned int b;
	
	double red_mul = 0.9;
	double green_mul = 0.2;
	double blue_mul = 0.1;
	
	
	if (iter == -1){
		r = 0;
		g = 0;
		b = 0;	
	}
	else if (iter < 1000)
	{
		red_mul = 0.90;
		green_mul = 0.85;
		blue_mul = 0.2;
	}
	else if (iter < 2000)
	{
		red_mul = 0.80;
		green_mul = 0.90;
		blue_mul = 0.15;
	}
	else if (iter < 4000)
	{
		red_mul = 0.70;
		green_mul = 0.80;
		blue_mul = 0.15;
	}
	else if (iter < 6000)
	{
		red_mul = 0.60;
		green_mul = 0.75;
		blue_mul = 0.20;
	}
	else if (iter < 8000)
	{
		red_mul = 0.50;
		green_mul = 0.75;
		blue_mul = 0.30;
	}
	else if (iter < 12000)
	{
		red_mul = 0.50;
		green_mul = 0.70;
		blue_mul = 0.40;
	}
	else if (iter < 16000)
	{
		red_mul = 0.40;
		green_mul = 0.70;
		blue_mul = 0.50;
	}
	else if (iter < 20000)
	{
		red_mul = 0.30;
		green_mul = 0.80;
		blue_mul = 0.60;
	} else {
		red_mul = 0.20;
		green_mul = 0.7;
		blue_mul = 0.6;
	}
	

	
	/*if (iter != -1)
	{
		r = part_iter * red_mul;
		g = part_iter * green_mul;
		b = part_iter * blue_mul;
	}*/
	
	
	if (iter != -1)
	{
		/*
		int exp_iter = map_num(iter,0,MAX_ITR,1,340);
		
		r = cos(exp_iter)*150 + 50;
		g = cos(exp_iter)*150 + 50;
		b = cos(exp_iter)*150 + 50*/;
		

		
		int exp_iter = map_num(iter,0,MAX_ITR,1,40);
		
		r = tan(exp_iter)*red_mul*100 + 50;
		g = tan(exp_iter)*green_mul*100 + 50;
		b = tan(exp_iter)*blue_mul*100 + 50;
		
		if (r > 250)
			r = 250;
		if (g > 250)
			g = 250;
		if (b > 250)
			b = 250;

/*	
		int exp_iter = map_num(iter,0,MAX_ITR,1,30);
		
		r = log2(exp_iter)*red_mul*100 + 30;

		g = log2(exp_iter)*green_mul*100 + 30;
		b = log2(exp_iter)*blue_mul*100 + 30;
		
		
		if ((log2(exp_iter)*red_mul*100 + 30) > 250)
			r = 200;
		if ((log2(exp_iter)*green_mul*100) > 250)
			g = 200;
		if ((log2(exp_iter)*blue_mul*100) > 250)
			b = 200;

*/


/*		int whl_iter = 3-map_num(iter,0,MAX_ITR,1,3);
	
		int WheelPos = 255 - floor(log(1/zoom) * 5 + 50);
		if(WheelPos < 85) {
			r = 255 - WheelPos;
			g = 0;
			b = WheelPos * whl_iter;
		} else if(WheelPos < 170) {
			WheelPos -= 85;
			r = 0;
			g = WheelPos * whl_iter;
			b = 255 - WheelPos * whl_iter;
		} else {
			WheelPos -= 170;
			r = WheelPos * whl_iter;
			g = 255 - WheelPos * whl_iter;
			b = 0;
		}
*/
	}
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
	
	return rgb;
	//return "\033[38;2;"+rgb+"m█\033[0m";
	
}


void mandelbrot_to_jpg(int resolution)
{
	long int png_width = 0;
	long int png_height = 0;
	int division = 0;
	if (resolution == '1')
	{
		png_width = 1920;
		png_height = 1080;
		division = 20;
	}
	else if (resolution == '2')
	{
		png_width = 960;
		png_height = 540;
		division = 10;
	}
	else if (resolution == '3')
	{
		png_width = 480;
		png_height = 270;
		division = 5;
	}
	else
	{
		return;
	}
	
	auto const width = size_t{png_width};
	auto const height = size_t{png_height};
	auto pixel_data = vector<uint8_t>(3* width * height * 3);


	
	for(int y=1;y<=png_height;y++)
	{
		for(int x=1; x<=png_width; x++)
		{
			/*if (x == png_width/2)
			{
				cout << "|";
				continue;
			}
			else if (y == png_height/2)
			{
				cout << "-";
				continue;
			}*/
			
			//cout << ceil(double(y)/double(png_height)*100) << "%" << endl;
			//printf("%0.3f %%", ceil(double(y)/double(png_height)*100));
			
			/* https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf */
			//float progress = ((
			//double(y)/double(png_height) + double(x)/double(png_width))/99);
			//float progress = (double)y*(double)x / (double)png_height*(double)png_width;
			float progress = (double)y / (double)png_height;
			
			int barwidth = 100;
		    cout << "[";
			int pos = barwidth * progress;
			for (int i = 0; i < barwidth; ++i) {
				if (i < pos) cout << "=";
				else if (i == pos) cout << ">";
				else std::cout << " ";
			}
			cout << "] " << round(float(progress * 100.0)*100) / 100<< " %   " << y << " x " << x << " px    \r";
			cout.flush();
			
			
			
			
			
			long double pos_real = (x-png_width/2)*(zoom/division) + offsetX;
			
			long double pos_imag = (y-png_height/2)*(zoom/division) + offsetY;
			
			
			
			complex_number cn = complex_number(pos_real, pos_imag);
			int iterations = mandelbrot(cn);
			unsigned int* int_rgb = getCharacter(iterations);
			
			int r = int_rgb[0];
			int g = int_rgb[1];
			int b = int_rgb[2];
			
			if (((r != 0) && (g != 0) && (b != 0)))
			{
				if (y != 1 && x != 1)
				{
					r = (pixel_data[3*(y*width+x-1)] + pixel_data[3*((y-1)*width+x)] + r*8) / 11;
					g = (pixel_data[3*(y*width+x-1)+1] + pixel_data[3*((y-1)*width+x)+1] + g*8) / 11;
					b = (pixel_data[3*(y*width+x-1)+2] + pixel_data[3*((y-1)*width+x)+2] + b*8) / 11;
				}
				else if (x != 1)
				{
					
					r = (pixel_data[3*(y*width+x-1)] + r*3) / 4;
					g = (pixel_data[3*(y*width+x-1)+1] + g*3) / 4;
					b = (pixel_data[3*(y*width+x-1)+2] + b*3) / 4;
				}
			}

		
		
			pixel_data[3*(y*width+x)] = r;
			pixel_data[3*(y*width+x)+1] = g;
			pixel_data[3*(y*width+x)+2] = b;

			
			
			//cout << "\n\nImaginairy position: " << pos_imag << ",\t Real part: " << pos_real << "\n\n";

			
			//complex_number cn = complex_number(pos_real,pos_imag);
			//int iterations = mandelbrot(cn);
			//cout << iterations << endl;
			//cout << getCharacter(iterations);
			
		}
		
	}
	
	string filename = "filename";
	auto ofs = ofstream((filename + ".ppm").c_str(), ios::binary);
	thinks::ppm::writeRgbImage(ofs, width, height, pixel_data);
	ofs.close();

	cout << "\nDone! Saved as " << filename << endl;
	cout << "\nDone! Converting to " << filename << ".png..." << endl;
	
	
	
	system(("convert '" + filename + ".ppm' '" + filename + ".png'").c_str());
	
	remove((filename + ".ppm").c_str());
	
	system(("eog " + filename + ".png").c_str());
	
}


void exiting()
{
	cout << endl << "Goodbye!" << endl;
	system("stty sane");
}

void exiting_c(int s)
{
	exit(0);
}

int main()
{
    atexit(exiting);
    signal(SIGINT,exiting_c);
   
    struct winsize windowsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowsize);

    ROWS = windowsize.ws_row - 6;
    COLS = windowsize.ws_col - 5;
    

    
    bool updated = true;
    while(true)
    {
		if (!updated)
		    continue;
		cout << "\033c"; // clear window
		
		clock_t begin_time = clock();
		
		
		for(int y=1;y<ROWS;y++)
		{
			for(int x=1; x<COLS; x++)
			{
				if (x == COLS/2 && y == ROWS/2)
				{
					cout << "+";
					continue;
				}
				if (x == COLS/2)
				{
					cout << "|";
					continue;
				}
				else if (y == ROWS/2)
				{
					cout << "-";
					continue;
				}
				
				
				
				
				long double pos_real = 0.5*(x-COLS/2)*zoom + offsetX;
				
				long double pos_imag = (y-ROWS/2)*zoom + offsetY;
				
				//cout << "\n\nImaginairy position: " << pos_imag << ",\t Real part: " << pos_real << "\n\n";
				
				complex_number cn = complex_number(pos_real,pos_imag);
				int iterations = mandelbrot(cn);
				//cout << iterations << endl;

				unsigned int* int_rgb = getCharacter(iterations);
				string rgb_ansi = to_string(int_rgb[0]) + ";" + to_string(int_rgb[1]) + ";" + to_string(int_rgb[2]);
				cout << "\033[38;2;"+rgb_ansi+"m█\033[0m";
				//cout << getCharacter(iterations);
			}
			cout << y << endl;
			
		}
		cout << "Zoom:\t\t\t" /* << fixed << setprecision(30)*/ <<zoom << endl;
		cout << "Zoom:\t\t\t" /* << fixed << setprecision(30)*/ <<1/zoom << endl;
		cout << "Max Iterations:\t\t" << MAX_ITR << endl;
		cout << "OffsetX:\t\t" << offsetX << endl;
		cout << "OffsetY:\t\t" << offsetY << endl;
		cout << "Time taken:\t\t" << double(clock() - begin_time) / CLOCKS_PER_SEC << " s" << endl;
		updated = false;
		
		
		while(!updated)
		{
			//cout << getch();
		    int ch = getch();
		    //cout << ch;
		    if (ch == 43)
		    {
				// zoom in (+)
				zoom /= 1.5;
				updated = true;
			}
			else if (ch == 45)
			{
				// zoom uit; (-)
				zoom *= 1.5;
				updated = true;
			}
			else if (ch == 65)
			{
				// up
				offsetY -= 0.5*(zoom*10);
				updated = true;
			}
			else if (ch == 66)
			{
				// down
				offsetY += 0.5*(zoom*10);
				updated = true;
			}
			else if (ch == 67)
	        {
				// left
				offsetX += 0.5*(zoom*10);
				updated = true;
			}
			else if (ch == 68)
			{
				//right
				offsetX -= 0.5*(zoom*10);
				updated = true;
			}
			else if (ch == 105)
			{
				// input (i)
				cout << "  What do you want to set?\n";
				cout << "----------------------------\n";
				cout << " 1) Zoom\n";
				cout << " 2) Max Iterations\n";
				cout << " 3) OffsetX\n";
				cout << " 4) OffsetY\n";
				cout << " 5) Cancel\n";
				
				char choice;
				
				cout << "\n $ ";
				cin >> setw(1) >> choice;
				//choice = choice[0];
				while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5')
				{
					cout << "Invalid option: " << choice;
				    cout << "\n $ ";
				    cin >> choice;
				    //choice = choice[0];
				}
				if (choice == '5')
				{
					updated = true;
				    continue;
				}
				else if (choice == '1')
				{
					cout << "\nSet new zoom $ ";
					cin >> zoom;
					updated = true;
					continue;
				}
				else if (choice == '2')
				{
					cout << "\nSet new Nax Iterations $ ";
					cin >> MAX_ITR;
					updated = true;
					continue;
				}
				else if (choice == '3')
				{
					cout << "\nSet new X-offset $ ";
					cin >> offsetX;
					updated = true;
					continue;
				}
				else if (choice == '4')
				{
					cout << "\nSet new Y-offset $ ";
					cin >> offsetY;
					updated = true;
					continue;
				}
			}
			else if (ch == 115)
			{
				// input (i)
				cout << "  Choose your resolution\n";
				cout << "----------------------------\n";
				cout << " 1) 1920 x 1080\n";
				cout << " 2) 960 x 540\n";
				cout << " 3) 480 x 270\n";
				
				char choice;
				
				cout << "\n $ ";
				cin >> setw(1) >> choice;
				//choice = choice[0];
				while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5')
				{
					cout << "Invalid option: " << choice;
				    cout << "\n $ ";
				    cin >> choice;
				    //choice = choice[0];
				}
				
				mandelbrot_to_jpg(choice);
				
				cout << "Press 5 to refresh." << endl;
				// save (s)
			}
			else if (ch == 118)
			{
			    // video (v)
			}
			else if (ch == 53)
			{
				// refresh (5)
				updated = true;
				continue;
			}
			else if (ch == 114)
			{
				// reset (r)
				zoom = 0.05;
				offsetX = 0;
				offsetY = 0;
				updated = true;
				continue;
			}
				
				
		}
		
		
		
		
	}



    return 0;
}
