// tesseract_learn.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include <Magick++.h> // ImageMagick C++ API

#include <iostream>
#include <fstream>
using namespace std;

int writetofile(const char* in, const char* path) {
    ofstream myfile;
    myfile.open(path);
    myfile << in << "\n";
    myfile.close();
    return true;
}

int writetofile(const char* in, const string path) {
    return writetofile(in, path.c_str());
}

//using namespace Magick;
using namespace std;

int main()
{
    char* outText;


    string input_pdf = "D:\\misc\\fortesting\\samplpdf.pdf";
    string output_jpg = "D:\\misc\\fortesting\\output.jpg";
    string output_text = "D:\\misc\\fortesting\\output.txt";
    try{
        Magick::Image image;
        image.density("1000x1000");
        image.read(input_pdf);
        //image.resize(Magick::Geometry(image.columns() * 2, image.rows() * 2)); // Double the size

        image.write(output_jpg);

    }

    catch (const Magick::Exception& error) {
        // Handle any exceptions or errors
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }


    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init("D:\\misc\\tessdata-main\\", "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    Pix* imagepix = pixRead(output_jpg.c_str());
    api->SetImage(imagepix);
    // Get OCR result
    outText = api->GetUTF8Text();
    writetofile(outText,output_text);
    printf("OCR output:\n%s", outText);

    // Destroy used object and release memory
    api->End();
    delete api;
    delete[] outText;
    pixDestroy(&imagepix);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
