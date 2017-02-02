# install dependencies in parent directory
cd ..

# install tesseract dependence libraries and tools
sudo apt-get install autoconf automake libtool
sudo apt-get install autoconf-archive
sudo apt-get install pkg-config
sudo apt-get install libpng12-dev
sudo apt-get install libjpeg8-dev
sudo apt-get install libtiff5-dev
sudo apt-get install zlib1g-dev

# install tesseract training dependencies
sudo apt-get install libicu-dev
sudo apt-get install libpango1.0-dev
sudo apt-get install libcairo2-dev

# install leptonica
wget http://www.leptonica.com/source/leptonica-1.74.1.tar.gz
tar -zxvf leptonica-1.74.1.tar.gz
cd leptonica-1.74.1
./configure
sudo make install
cd ..
sudo rm -f leptonica-1.74.1.tar.gz

# install tesseract
sudo apt-get install git
git clone --depth 1 https://github.com/tesseract-ocr/tesseract.git
cd tesseract
./autogen.sh
./configure --enable-debug LDFLAGS="-L/usr/local/lib" CFLAGS="-I/usr/local/include"
sudo make install
sudo ldconfig

make training
sudo make training-install

# return to project
sudo apt-get autoremove
cd ../historic-document-ocr

# install tesseract language data
mkdir tessdata
cd tessdata
wget https://github.com/tesseract-ocr/tessdata/raw/4.00/eng.traineddata
cd ..
