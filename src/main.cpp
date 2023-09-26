#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char** argv) {
    // Sample Image
    cv::Mat img = cv::imread("icon.png", cv::IMREAD_UNCHANGED);

    // Check if Image got found and loaded properly
    if(img.data != nullptr) {
        std::string windowName = "OpenCV Template";
        cv::namedWindow(windowName, cv::WINDOW_NORMAL);
        cv::imshow(windowName, img);
        cv::waitKey(0);
        cv::destroyAllWindows();
        cv::imwrite("icon_copy.png", img);
    } else {
        std::cout << "Image not found!\n";
    }

    return 0;
}
