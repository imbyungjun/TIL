#OpenCV in Xcode
-
**1. Download**

* **OpenCV**  
Click download OpenCV for Linux/Mac at here.  **http://opencv.org/downloads.html**  

* **XCode**  
You can download Xcode in App Store.

* **CMake**  
You can download gui version of cmake at here. (.dmg)  
**http://www.cmake.org/download/**
	
**2. Install**

* Unzip OpenCV-3.0.0. And create two new folders in OpenCV-3.0.0/ directory. StaticLibs/ and SharedLibs/.  

* Install CMake and open it.  
Click Browse Source and navigate to OpenCV folder.  
Click Browse Build and navigate to your StaticLib folder.  
Click Configure and select Unix Makefiles option and click OK.  
Then, CMake will perform some tasks and finally you can get red boxes in CMake window.  
And you have to uncheck and add some options.  
	- Uncheck **BUILD\_SHARED\_LIBS**
	- Uncheck **BUILD\_TESTS**
	- Add path **CMAKE\_OSX\_SYSROOT** like this. (It can be set by default)  
**/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk**
	- Add "x86_64" to **CMAKE\_OSX\_ARCHITECTURES**
	- Uncheck **WITH\_1394**
	- Uncheck **WITH_FFMPEG**

	Then, click Configure again, then click Generate.
	
* Open Terminal and type these commands.

		$ cd opencv-3.0.0/staticlibs/
		$ make
		$ sudo make install
		
	If there's no error messages, installation is completed.
	
* Repeat it with change directory StaticLibs -> SharedLibs


**3. Make openCV project in Xcode**

* Open Xcode and select create a new project.  
And select OS X - Command Line Tool.

* Click your project then, you can see four tabs in main window.  Click Build Settings and option All.  
Find **Search Paths** and edit **Header Search Paths** like this  
		
		/usr/local/include
		
* Edit Library Search Paths 

		/usr/local/lib
		


* Then, find **Linking** tab, edit **Other Linker Flags**

		-lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videoio -lopencv_videostab


* Open Xcode preferences, select location tab.  
Click Advanced.  
Change the location button from Unique to Legacy.  
Now, you can build your opencv project.

  
--  


**Example Code for OpenCV**

	#include <opencv2/objdetect/objdetect.hpp>
	#include <opencv2/highgui/highgui.hpp>
	#include <opencv2/imgproc/imgproc.hpp>

	#include <iostream>
	#include <stdio.h>

	using namespace std;
	using namespace cv;


	int main( int argc, const char** argv )
	{
    	CvCapture* capture = 0;
    	Mat frame, frameCopy, image;

    	capture = cvCaptureFromCAM( 0 ); //0=default, -1=any camera, 1..99=your camera
    	if(!capture) cout << "No camera detected" << endl;

	    cvNamedWindow( "result", 1 );
	
	    if( capture )
	    {
	        cout << "In capture ..." << endl;
	        for(;;)
	        {
	            IplImage* iplImg = cvQueryFrame( capture );
	            frame = iplImg;
	            if( frame.empty() )
	                break;
	            if( iplImg->origin == IPL_ORIGIN_TL )
	                frame.copyTo( frameCopy );
	            else
	                flip( frame, frameCopy, 0 );
	
	            if( waitKey( 10 ) >= 0 )
	                cvReleaseCapture( &capture );
	        }
	
	        waitKey(0);
	
	    cvDestroyWindow("result");
	
	    return 0;
	    }
	}
