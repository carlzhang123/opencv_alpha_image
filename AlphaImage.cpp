// 代码片作者：Carl Zhang，转载请注明。

#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include "opencv/cv.h"
#include "opencv/highgui.h"

int main()
{
    uchar r, g, b;
    // 获取灰度图像。
    cv::Mat image = ("image.jpg", 0);
    cv::Mat image_canny;
    
    // 二值化图像。
    cv::threshold(image, image, threshold_low, threshold_high, CV_THRESH_OTSU);
    
    // 获取图像边缘。
    cv::Canny(image, image_canny, lowThreshold, lowThreshold*ratio, kernel_size);
    
    // 反色。
    cv::Mat newBImg(image_canny.rows, image_canny.cols, image_canny.type());
    uchar* newBImgData = newBImg.data;
    uchar* binaryData = image_canny.data;
    int step = image_canny.step / sizeof(uchar);
    
    for (int i = 0; i<image_canny.rows; i++)
        for (int j = 0; j<image_canny.cols; j++)
            newBImgData[i*step + j] = 255 - binaryData[i*step + j];
	
    image_canny = newBImg.clone();
    
    // 把canny图像从灰度转为BGRA 4通道图像。
    cv::cvtColor(image_canny, image_canny, CV_GRAY2BGRA);
    
    for (int i = 0; i < image_canny.rows; i++)
        for (int j = 0; j < image_canny.cols; j++)
        {
            // R
            r = image_canny.at<cv::Vec4b>(i, j)[2];	
            // G
            g = image_canny.at<cv::Vec4b>(i, j)[1];	
            // B
            b = image_canny.at<cv::Vec4b>(i, j)[0];	
            
            if (r > 200 && b > 200 && g > 200)
            {
                // A
                image_canny.at<cv::Vec4b>(i, j)[3] = 0;	
            }
        }
    	
    cv::imshow("alpha", image_canny);
    cv::imwrite("alpha.png", image_canny);
    
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}