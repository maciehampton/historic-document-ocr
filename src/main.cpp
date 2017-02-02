#include <iostream>
#include <memory>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc == 1) {
		return 1;
	}

	tesseract::TessBaseAPI tess;

	if (tess.Init("./tessdata", "eng")) {
		cout << "OCRTesseract: Could not initialize tesseract." << endl;
		return 1;
	}

	// setup
	tess.SetPageSegMode(tesseract::PageSegMode::PSM_AUTO);
	tess.SetVariable("save_best_choices", "T");

	// read image
	auto pixs = pixRead(argv[1]);
	if (!pixs) {
		cout << "Cannot open input file: " << argv[1] << endl;
		return 1;
	}

	// recognize
	tess.SetImage(pixs);
	tess.Recognize(0);

	// get result and delete[] returned char* string
	cout << unique_ptr<char[]>(tess.GetUTF8Text()).get() << endl;

	// cleanup
	tess.Clear();
	pixDestroy(&pixs);

	return 0;
}
