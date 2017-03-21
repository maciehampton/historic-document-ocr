#include <iostream>
#include <memory>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"

using namespace std;

using namespace cv;

int main(int argc, char *argv[]) {
	int top_x = stoi(argv[2]);
	int top_y = stoi(argv[3]);
	int width = stoi(argv[4]);
	int height = stoi(argv[5]);

	// Draw the bounding box on the image
	Mat img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	Rect r(top_x, top_y, width, height);
	rectangle(img, r, Scalar(255, 255, 0));
	
	// Display the image
	imshow("opencvtest",img);

	// Wait for user to close pop-up window
	waitKey(0);

	// Perform OCR on image
	char *outText;

	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();

	// Initialize tesseract-ocr with English, without specifying tessdata path
	if (api->Init(NULL, "eng")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}

	// Open input image with leptonica library
	Pix *image = pixRead(argv[1]);
	api->SetImage(image);
	api->SetRectangle(top_x, top_y, width, height);

	// Get OCR result
	outText = api->GetUTF8Text();
	printf("OCR output:\n%s", outText);

	// Destroy used object and release memory
	api->End();
	delete [] outText;
	pixDestroy(&image);

	return 0;
}
