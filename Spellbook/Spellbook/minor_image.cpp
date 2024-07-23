//#include iostream
//#include opencv2opencv.hpp
//#include windows.h
//
//Function to capture the screen
//cvMat captureScreen() {
//    HWND hwnd = GetDesktopWindow();
//    HDC hdcScreen = GetDC(hwnd);
//    HDC hdcMemory = CreateCompatibleDC(hdcScreen);
//
//    RECT rect;
//    GetClientRect(hwnd, &rect);
//    int width = rect.right;
//    int height = rect.bottom;
//
//    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
//    SelectObject(hdcMemory, hBitmap);
//
//    BitBlt(hdcMemory, 0, 0, width, height, hdcScreen, 0, 0, SRCCOPY);
//    ReleaseDC(hwnd, hdcScreen);
//
//    BITMAPINFOHEADER bi = { sizeof(BITMAPINFOHEADER), width, -height, 1, 32, BI_RGB };
//    cvMat mat(height, width, CV_8UC4);
//    GetDIBits(hdcMemory, hBitmap, 0, height, mat.data, (BITMAPINFO)&bi, DIB_RGB_COLORS);
//
//    DeleteObject(hBitmap);
//    DeleteDC(hdcMemory);
//
//    return mat;
//}
//
//Function to detect the target image
//bool detectImage(cvMat& screen, cvMat& target) {
//    cvMat result;
//    cvmatchTemplate(screen, target, result, cvTM_CCOEFF_NORMED);
//    double minVal, maxVal;
//    cvPoint minLoc, maxLoc;
//    cvminMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
//    return maxVal  0.8;  Adjust the threshold as needed
//}
//
//Function to be triggered
//void onImageDetected() {
//    stdcout  Image detected!stdendl;
//}
//
//int main() {
//    Load the target image
//        cvMat target = cvimread(target.png, cvIMREAD_COLOR);
//    if (target.empty()) {
//        stdcerr  Could not load target image!stdendl;
//        return -1;
//    }
//
//    while (true) {
//        Capture the screen
//            cvMat screen = captureScreen();
//
//        Detect the target image
//            if (detectImage(screen, target)) {
//                onImageDetected();
//            }
//
//        Sleep for a while
//            Sleep(1000);  Adjust the delay as needed
//    }
//
//    return 0;
//}