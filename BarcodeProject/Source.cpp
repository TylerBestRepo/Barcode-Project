////////////////////////////////////////////////////////////////
// Skeleton program for TRC3500
// Grabs images from a USB camera using OpenCV
// Written by Andy Russell 09th February 2006
// Modified by Michael Curtis 2011-2012 - updated for newer OpenCV
/////////////////////////////////////////////////////////////////
#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;
using namespace cv;

////////////////////////////////////////////////////////////////
// main - initialises OpenCV and captures an image and changes it
////////////////////////////////////////////////////////////////

void printString(const std::string& str) {
	std::cout << str << std::endl;
}

// Hard coding in the possibilities
string myFunction(int T1, int T2, int T4) {
	if (T1 == 2) {
		if (T2 == 2) {
			return "E6";
		}
		else if (T2 == 3) {
			return "O0";
		}
		else if (T2 == 4) {
			return "E4";
		}
		else if (T2 == 5) {
			return "O3";
		}
	}
	else if (T1 == 3) {
		if (T2 == 2) {
			return "O9";
		}
		else if (T2 == 3) {
			if (T4 == 2) {
				return "E2";
			}
			else if (T4 == 3) {
				return "E8";
			}
			else {
				return "There is an error somewhere";
			}
		}
		else if (T2 == 4) {
			if (T4 == 2) {
				return "O1";
			}
			else if (T4 == 3) {
				return "O7";
			}
			else {
				return "There is an error somewhere";
			}
		}
		else if (T2 == 5) {
			return "E5";
		}
	}
	else if (T1 == 4) {
		if (T2 == 2) {
			return "E9";
		}
		else if (T2 == 3) {
			if (T4 == 2) {
				return "O2";
			}
			else if (T4 == 1) {
				return "O8";
			}
			else {
				return "There is an error somewhere - T1-4, T4";
			}
		}
		else if (T2 == 4) {
			if (T4 == 1) {
				return "E1";
			}
			else if (T4 == 2) {
				return "E7";
			}
			else {
				cout << "T1 = " << T1 << " " << "T2 = " << T2 << " " << "T4 = " << T4 << endl;
				return "There is an error somewhere - is it here?";
			}
		}
		else if (T2 == 5) {
			return "O5";
		}
	}
	else if (T1 == 5) {
		if (T2 == 2) {
			return "O6";
		}
		else if (T2 == 3) {
			return "E0";
		}
		else if (T2 == 4) {
			return "O4";
		}
		else if (T2 == 5) {
			return "E3";
		}
	}
	// Add a return statement here to handle all other cases
	return "Invalid input";
}


int main()
{
	CvCapture* capture = 0;
	IplImage* processedImage = 0;

	cout << "Tyler's USB camera program" << endl << "Press 'q' to quit" << endl;
	cout << "Press 'p' to to take a still image" << endl;

	// Initializes capturing video from camera
	/*capture = cvCaptureFromCAM(1);
	if (!capture) {
		fprintf(stderr, "Could not initialize capturing...\n");
		return -1;
	}*/


	// Creates window
	cvNamedWindow("Camera image", 1);

	// Camera image
	IplImage* frame = 0;

	// Grabs and returns a frame from camera
	//frame = cvQueryFrame(capture);

	frame = cvLoadImage("barcodeCrop.png");

	// Print details of image
	cout << "image width =" << frame->width << " height =" << frame->height;
	cout << " depth =" << frame->depth << " channels =" << frame->nChannels << endl;

	bool tidyUp = true;

	// Defining a variable for max and min grey values to get a better threshold
	double minGray = 255, maxGray = 0;


	// Shows the resulting image in the window

	//// convert the whole image to gray
	for (int y = 0; y < frame->height; y++) {
		for (int x = 0; x < frame->width; x++) {
			// this is a pointer to the start of the current row.
			//  note: the image is stored as a 1-d array which is mapped back
			//  into 2-space by multiplying the widthstep (the image width rounded to
			//  a "nice" value, eg a multiple of 4 or 8 depending on the os and cpu)
			//  by the row number.
			uchar* row = (uchar*)(frame->imageData + frame->widthStep * y);
			 // Make sure to add this dynamic thresholding to the non static image getter
			int gray = (row[x * 3] + row[x * 3 + 1] + row[x * 3 + 2]) / 3;
			if (gray > maxGray){
				maxGray = gray;
			}
			else if (gray < minGray) {
				minGray = gray;
			}
			row[x * 3] = gray;
			row[x * 3 + 1] = gray;
			row[x * 3 + 2] = gray;
		}
	}

	double threshold = (minGray + maxGray) / 2;

	cvShowImage("Camera image", frame);

	do {

		// If you select a block of code and use the key sequence Ctrl+K+C, 
		// you'll comment out the section of code. Ctrl+K+U will uncomment the code.

		// Grabs and returns a frame from camera
		//frame = cvqueryframe(capture);
		//if (!frame) {
		//	break;
		//}

		//// convert the whole image to gray
		//for (int y = 0; y < frame->height; y++) {
		//	for (int x = 0; x < frame->width; x++) {
		//		// this is a pointer to the start of the current row.
		//		//  note: the image is stored as a 1-d array which is mapped back
		//		//  into 2-space by multiplying the widthstep (the image width rounded to
		//		//  a "nice" value, eg a multiple of 4 or 8 depending on the os and cpu)
		//		//  by the row number.
		//		uchar *row = (uchar*)(frame->imagedata + frame->widthstep * y);

		//		int gray = (row[x * 3] + row[x * 3 + 1] + row[x * 3 + 2]) / 3;

		//		row[x * 3] = gray;
		//		row[x * 3 + 1] = gray;
		//		row[x * 3 + 2] = gray;
		//	}
		//}


		//// Shows the resulting image in the window
		//cvShowImage("Camera image", frame);



		if ('p' == cvWaitKey(1)) {
			tidyUp = false;
			break;
		}
	} while ('q' != cvWaitKey(10));


	if (tidyUp == true) {
		//tidy up
		// Releases the CvCapture structure
		cvReleaseCapture(&capture);
		// Destroys all the HighGUI windows
		cvDestroyAllWindows();
	}
	else {
		std::cout << "Frame should hopefully remain static" << std::endl;
		// Now looping through all of the indexes within frame to threshold them
		//int threshold = 80;
		// Loop over all pixels and set values below threshold to zero
		for (int y = 0; y < frame->height; y++) {
			// Pointer to the start of the current row
			uchar* row = (uchar*)(frame->imageData + frame->widthStep * y);
			for (int x = 0; x < frame->width; x++) {
				// Calculate average intensity across all three channels
				int gray = (row[x * 3] + row[x * 3 + 1] + row[x * 3 + 2]) / 3;
				if (gray < threshold) {
					row[x * 3] = 0;
					row[x * 3 + 1] = 0;
					row[x * 3 + 2] = 0;
				}
				else {
					row[x * 3] = 255;
					row[x * 3 + 1] = 255;
					row[x * 3 + 2] = 255;
				}
			}
		}
		cvShowImage("Camera image", frame);
		std::cout << "Press 'g' to find the moments of inertia!" << std::endl;
		std::cout << "Press 'm' to go back to camera and retake picture" << std::endl;
		// Initialize with the image dimensions
		int minX = frame->width, minY = frame->height, maxX = 0, maxY = 0;
		do {
			if ('g' == cvWaitKey(1)) {
				double areaCounter = 0;
				double iPixelCount = 0;
				double jPixelCount = 0;
				double m11 = 0, m20 = 0, m02 = 0;
				double m01, m10 = 0, m00 = 0;
				double i0 = 0, j0 = 0;
				double thirdAxis, topCalc, bottomCalc;
				for (int y = 0; y < frame->height; y++) {
					// Pointer to the start of the current row
					uchar* row = (uchar*)(frame->imageData + frame->widthStep * y);
					for (int x = 0; x < frame->width; x++) {
						// Calculate average intensity across all three channels
						int gray = (row[x * 3] + row[x * 3 + 1] + row[x * 3 + 2]) / 3;
						if (gray == 0) {
							areaCounter++;
							iPixelCount += y;
							jPixelCount += x;
							m11 += x * y;
							m20 += y * y;
							m02 += x * x;

							if (x < minX) {
								minX = x;
							}
							if (x > maxX) {
								maxX = x;
							}

							// Check if this is the topmost or bottommost white pixel
							if (y < minY) {
								minY = y;
							}
							if (y > maxY) {
								maxY = y;
							}
						}
					}
				}
				//std::cout << "Oth moment of inertia give the area as: " << areaCounter << " pixels" << std::endl;

				m01 = jPixelCount;
				m10 = iPixelCount;
				m00 = areaCounter;
				i0 = m10 / m00;
				j0 = m01 / m00;

				topCalc = 2 * (m00*m11 - m10 * m01);
				bottomCalc = (m00*m20 - (m10*m10)) - (m00*m02 - (m01*m01));
				thirdAxis = atan(topCalc / bottomCalc)* (180.0 / 3.14159265358979323846);

				double thirdAxis2 = atan2(topCalc, bottomCalc) * (180.0 / 3.14159265358979323846);


				
				int length = 600;

				// When on campus next week copy this section from the computers there. 

				double x1 = 0, y1 = 0, x2 = 0, y2 = 0;

				x1 = (int)round(j0 + length * cos(thirdAxis2 * CV_PI / 180.0));
				y1 = (int)round(i0 + length * sin(thirdAxis2 * CV_PI / 180.0));
				x2 = (int)round(j0 - length * cos(thirdAxis2 * CV_PI / 180.0));
				y2 = (int)round(i0 - length * sin(thirdAxis2 * CV_PI / 180.0));

				//std::cout << "1st moment of inertia give the coordinates as: (" << j0 << "," << i0 << ") ." << std::endl;
				
				int middleX = (maxX + minX)/2;
				int middleY = (maxY - minY)/2;

				// If the gradient is angled then should move in the x and y direction in that angle using trig
				// then round to the nearest int 

				int startX = middleX;
				int barcodeCountLeft = 0;
				// declare an empty vector for the left hand side of the barcode intensities
				std::vector<int> LHSintensities;
				


				// Going from the middle to the start here
				// Pointer to the start of the current row
				uchar* row = (uchar*)(frame->imageData + frame->widthStep * middleY);

				// Loop through each pixel in the row, starting at the specified x-coordinate
				for (int x = minX; x <= startX; x++) {
					// Calculate average intensity across all three channels
					int gray = (row[x * 3] + row[x * 3 + 1] + row[x * 3 + 2]) / 3;

					// Check if the intensity is 0 and y-coordinate is at middleY
					if (gray == 0) {
						// Increment pixel count
						barcodeCountLeft++;

						cvCircle(frame, cvPoint(x, middleY), 1, CV_RGB(255, 255, 0), -1);
						// Adding the whites to the array to keep track of
						LHSintensities.push_back(0);

						///cout << gray << ",";
					}
					else if (gray == 255) {
						LHSintensities.push_back(255);
						cvCircle(frame, cvPoint(x, middleY), 1, CV_RGB(0, 255, 255), -1);
						//cout << gray << ",";
					}
				}


				std::cout << "The number of black pixels in the barcode from the start to the center is: " << barcodeCountLeft << std::endl;
			   
				//std::cout << "2nd moment of inertia give the angle: " << thirdAxis2 << std::endl;
				//cvCircle(frame, cvPoint(j0, i0), 5, CV_RGB(255, 0, 0), -1);
				cvCircle(frame, cvPoint(middleX, middleY), 1, CV_RGB(255, 255, 255), -1);
				//cvLine(frame, cvPoint(x1, y1), cvPoint(x2,y2) ,CV_RGB(0, 255, 0), 2);
				cvShowImage("Camera image", frame);

				// Printing the LHS barcode intensities
				for (int i : LHSintensities) {
					std::cout << i << " ";
				}
				std::cout << std::endl;
				
				//// This is a more one time code use
				//std::ofstream file("LHSIntensities.csv"); // open the output file in write mode
				//// write the vector elements to the file as comma-separated values
				//for (int y : LHSintensities) {
				//	file << y << ",";
				//}
				//file << std::endl;

				//// close the file
				//file.close();

				// code imported from my laptop using the LHSintesities array

				// Need to count the number of pixels in the bar sections

				std::vector<int> blackSequential;
				std::vector<int> whiteSequential;

				vector<pair<int, bool>> countVector;
				int currentCounter = 0;
				int previousPixel = LHSintensities[0];

				for (int i = 0; i < LHSintensities.size(); i++) {
					//cout << "values has a type of: " << typeid(values[i]).name() << endl;
					if (LHSintensities[i] == previousPixel) {
						currentCounter++;
					}
					else {
						countVector.push_back(make_pair(currentCounter, previousPixel));
						currentCounter = 1;
						previousPixel = LHSintensities[i];
						//cout << "Previous pixel in else has type: " << typeid(previousPixel).name() << endl;
					}
				}

				// Add the last sequence to the countVector
				countVector.push_back(make_pair(currentCounter, previousPixel));

				for (int i = 0; i < countVector.size(); i++) {
					int length = countVector[i].first;
					bool colour = countVector[i].second;
					if (colour == 0) {
						if (i < 3) {
							cout << "Sequence length: " << length << ", color: Black - Guard Bit" << endl;
						}
						else {
							cout << "Sequence length: " << length << ", color: Black" << endl;
						}


					}
					else {
						if (i < 3) {
							cout << "Sequence length: " << length << ", color: White - Guard Bit" << endl;
						}
						else {
							cout << "Sequence length: " << length << ", color: White" << endl;
						}

					}
				}


				// LHS must start with a 0 and end with a 1
				// White Black White Black is the sequence i must find


				// The vector should start at the first guard bar
				// If the first two lengths are equal then it should be good to go

				// find the median of the first four to elimate outliers
				int totalFirst4 = countVector[0].first + countVector[1].first + countVector[2].first + countVector[3].first;

				int barLength = round(totalFirst4 / 4);
				cout << "The total number is: " << totalFirst4 << endl;
				cout << "The rounded number is: " << barLength << endl;

				bool numberStart = true;
				int numAdded = 0;
				int t1, t2, t4;
				string result;
				float lengthAdjustedNumber;
				std::vector<int> currentSequence;
				std::vector<string> decodedNumbers;

				// Hard coding the guard bar skipping
				// 0 = black in mine
				for (int i = 3; i < countVector.size(); i++) {
					if (numAdded < 4) {
						// lengthAdjustedNumber = round(countVector[i].first/barLength);
						lengthAdjustedNumber = std::round(static_cast<double>(countVector[i].first) / barLength);
						currentSequence.push_back(lengthAdjustedNumber);
						//cout << lengthAdjustedNumber;
						numAdded++;
						//cout << countVector[i].first << " ";
					}
					else {
						// This is where the logic needs to go to use the t-values to decode
						t1 = currentSequence[3] + currentSequence[2];
						t2 = currentSequence[2] + currentSequence[1];
						t4 = currentSequence[0];
						// First set of t values is wrong then subsequent ones are wrong. not sure why just yet.

						//cout  << endl;
						// cout << "T1 = " << t1 << " T2 = " << t2 << " T4 = " << t4 << endl;
						// Make some sort of look up function i reckon
						result = myFunction(t1, t2, t4);
						//cout << result << endl;
						// Add the found number to the vector
						decodedNumbers.push_back(result);
						// Reset everything for the next number
						currentSequence.clear();
						numAdded = 0;

						// By doing this i-- here im making sure a number doesnt get skipped over
						i--;
					}
				}



				cout << endl << "The decoded LHS barcode is: ";

				for (int last = 0; last < decodedNumbers.size(); last++)
				{
					cout << decodedNumbers[last] << " ";
				}

				cout << endl;



				// To start at the middle of the barcode do i get the first and last non zero intensities
				// and find the midpoint in the x and y direction?
				// Or potentially find the gradinent for half of the image (hopefully always all barcode)

			}
			else if ('m' == cvWaitKey(1)) {
				main();
			}
		} while ('q' != cvWaitKey(1));


		//tidy up
		// Releases the CvCapture structure
		cvReleaseCapture(&capture);
		// Destroys all the HighGUI windows
		cvDestroyAllWindows();
	}


	return 0;

} //end of main