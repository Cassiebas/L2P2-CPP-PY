#include <ctime>
#include <iostream>
#include <vector> 
#include <raspicam/raspicam_cv.h>
#include <opencv2/tracking.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std; 

typedef struct _colors_{
    int iLowH;
    int iHighH;
    int iLowS;
    int iHighS;
    int iLowV;
    int iHighV;
} colors;

typedef struct _coords_ {
    int LastX;
    int LastY;
    int mLastX;
    int mLastY;
} coords;


int main ( int argc,char **argv ) {
   
    colors Colors;
    coords Coords;
    time_t timer_begin,timer_end;
    raspicam::RaspiCam_Cv Camera;
    
    //set camera params
    Camera.set(cv::CAP_PROP_FORMAT, CV_8UC3);
    Camera.set(cv::CAP_PROP_FPS, 50);
    //RPI Camera v2 supports 720p50fps so it resizes here ^
    Colors.iLowH = 151; Colors.iHighH = 179;
    Colors.iLowS = 101; Colors.iHighS = 217;
    Colors.iLowV = 44; Colors.iHighV = 66;
    Coords.LastX = -1; Coords.LastY = -1;
 
    //cv::namedWindow("Control", cv::WINDOW_AUTOSIZE);

    // cv::createTrackbar("LowH", "Control", &Colors.iLowH, 179);
    // cv::createTrackbar("HighH", "Control", &Colors.iHighH, 179);

    // cv::createTrackbar("LowS", "Control", &Colors.iLowS, 217);
    // cv::createTrackbar("HighS", "Control", &Colors.iHighS, 217);

    // cv::createTrackbar("LowV", "Control", &Colors.iLowV, 66);
    // cv::createTrackbar("HighV", "Control", &Colors.iHighV, 66);

    cv::Mat imgHSV, imgTmp, imgOriginal;

    Camera.grab();
    Camera.retrieve(imgOriginal);

    cv::Rect trackingBox;

    // cv::Mat imgLines = cv::Mat::zeros(imgTmp.size(), CV_8UC3);


    //Open camera
    cout<<"Opening Camera..."<<endl;
    
    if (!Camera.open())
    {
        cerr<<"Error opening the camera"<<endl;
        
        return -1;
    }
    
    //Start capture
    cout<<"Capturing" << endl;
    time(&timer_begin);

    int i;
    while (true)
    {
        cv::Mat imgOriginal;
        bool bSuccess = Camera.grab();
        Camera.retrieve(imgOriginal);

        if(!bSuccess)
        {
            cout << "Cannot read a frame from bitstream" << endl;
            return -1;
        }

        cv::cvtColor(imgOriginal, imgHSV, cv::COLOR_BGR2HSV);

        cv::Mat imgThresholded;

        cv::inRange(imgHSV, cv::Scalar(Colors.iLowH, Colors.iLowS, Colors.iLowV), cv::Scalar(Colors.iHighH, Colors.iHighS, Colors.iHighV), imgThresholded);

        cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)));
        cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)));

        cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)));
        cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5)));

        cv::Moments __moments = cv::moments(imgThresholded);

        double M01 = __moments.m01;
        double M10 = __moments.m10;
        double Area= __moments.m00;

        if(Area > 10000)
        {
            int posX = M10 / Area;
            int posY = M01 / Area;

            vector<cv::Point> pts;
            cv::findNonZero(imgThresholded, pts); 
            cv::Rect box = cv::boundingRect(pts);

            // for(i=0; i < pts.size(); i++ )
            // {
            //     cout << pts.at(i) << ' ';
            // }

            if(Coords.LastX >= 0 && Coords.LastY >= 0 && posX >= 0 && posY >= 0)
            {
                cv::rectangle(imgOriginal, box, cv::Scalar(255,0,0), 2);
            }
            Coords.LastX = posX;
            Coords.LastY = posY;
            // Coords.mLastX = mposX;
            // Coords.mLastY = mposY;
        }

        cv::imshow("Threshholded Image", imgThresholded);
       // imgOriginal = imgOriginal;
        

        cv::imshow("Original", imgOriginal);
       // imgOriginal = imgOriginal + imgLines;

        if(char c = (char) cv::waitKey(10) == 27)
        {
            cout << "esc key pressed by ueser" << endl;
            break;
        }
    }

    cout<<"Stop camera..."<<endl;
    Camera.release();
    
    //show time statistics
    time ( &timer_end ); /* get current time; same as: timer = time(NULL)  */

    double secondsElapsed = difftime ( timer_end,timer_begin );

    cout<< secondsElapsed<<" seconds elapsed "<< endl;
    

    return 0;
}