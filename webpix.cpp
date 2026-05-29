#include <opencv2/opencv.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>

#define DEBUG 0
#define PICFILE "webpix.jpg"
#define SCREENSHOTFILE "screenshot.jpg"

using namespace cv;

class ScreenShot {
    Display* display;
    Window root;
    int x, y, width, height;
    XImage* img{nullptr};
    XWindowAttributes attributes;
public:
    ScreenShot(int x, int y, int width, int height):
        x(x),
        y(y),
        width(width),
        height(height) {
        display = XOpenDisplay(nullptr);
        root = DefaultRootWindow(display);
        if (DEBUG > 0)
    	    printf("   Before: x=%d, y=%d, w=%d, h=%d\n", x, y, width, height);
        attributes = {0};
        XGetWindowAttributes(display, root, &attributes);
        width = attributes.width;
        height = attributes.height;
        if (DEBUG > 0)
            printf("   After:  x=%d, y=%d, w=%d, h=%d\n", x, y, width, height);
    }

    void operator() (Mat& cvImg) {
        if (img != nullptr)
            XDestroyImage(img);
        img = XGetImage(display, root, x, y, width, height, AllPlanes, ZPixmap);
        cvImg = Mat(height, width, CV_8UC4, img->data);
    }

    ~ScreenShot() {
        if(img != nullptr)
            XDestroyImage(img);
        XCloseDisplay(display);
    }
};

#define WIDTH 800
#define HEIGHT 600

char screenshot(void) {
    printf("\n=> Screenshot (S=save, Q=quit)\n");
    ScreenShot screen(0, 0, WIDTH, HEIGHT);
    Mat img;
    char key = ' ';
    while (key != 'q') {
        // capture screenshot
        screen(img);
        // show captured image
        imshow("Screenshot", img);
        // check key
        key = waitKey(25) & 0xff;
        switch (key) {
            case 's':
                imwrite(SCREENSHOTFILE, img);
                printf("   Saved %s\n", SCREENSHOTFILE);
                break;
            case 'q':
                printf("   Quit screenshot\n");
                break;
        }
    }
    getchar(); // discard key in buffer
    destroyAllWindows();
    return key;
}

char webcam(void) {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        printf("*** Cannot open camera ***\n");
        return 1;
    }
    printf("\n=> Webcam (S=save, Q=quit)\n");
    Mat img;
    char key = ' ';
    while (key != 'q') {
        // capture webcam
        cap >> img;
        // show captured image
        imshow("Webcam", img);
        // check key
        key = waitKey(25) & 0xff;
        switch (key) {
            case 's':
                imwrite(PICFILE, img);
                printf("   Saved %s\n", PICFILE);
                break;
            case 'q':
                printf("   Quit webcam\n");
                break;
        }
    }
    getchar(); // discard key in buffer
    destroyAllWindows();
    return key;
}

int main() {
    printf("----- START -----\n");
    bool quit = false;
    while (!quit) {
        printf("\n----- MENU -----\n");
        printf("[S] Screenshot\n");
        printf("[W] Webcam\n");
        printf("[Q] Quit\n");
        printf("Select: ");
        char key = toupper(getchar());
        if (DEBUG > 0)
            printf("0x%02X '%c'\n", key, key);
        switch (key) {
            case 'S':
                screenshot();
                break;
            case 'W':
                webcam();
                break;
            case 'Q':
                quit = true;
                break;
            default:
                printf("*** INVALID KEY ***\n");
        }
    }
    printf("\n=> Quit\n");
    printf("----- END -----\n");
}
