/* =========================================================================
   Copyright (c) 2010-2016, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.
   Portions of this software are copyright by UChicago Argonne, LLC.

                            -----------------
                  ViennaCL - The Vienna Computing Library
                            -----------------

   Project Head:    Karl Rupp                   rupp@iue.tuwien.ac.at

   (A list of authors and contributors can be found in the PDF manual)

   License:         MIT (X11), see file LICENSE in the base directory
============================================================================= */

/** \example blas2.cpp
*
*   In this tutorial the BLAS level 2 functionality in ViennaCL is demonstrated.
*
*   We start with including the required header files:
**/

// System headers
#include <iostream>


// ViennaCL headers
#include "viennacl/scalar.hpp"
#include "viennacl/vector.hpp"
#include "viennacl/matrix.hpp"
#include "viennacl/linalg/direct_solve.hpp"
#include "viennacl/linalg/prod.hpp"       //generic matrix-vector product
#include "viennacl/linalg/norm_2.hpp"     //generic l2-norm for vectors
#include "viennacl/linalg/lu.hpp"         //LU substitution routines
#include "viennacl/tools/random.hpp"


#include "viennacv/core/image.hpp"
#include "viennacv/core/image_filter.hpp"
#include "viennacv/core/image_format.hpp"

#include "Magick++.h"
// TODO: If you are on Windows, you will need this 
// InitializeMagick(*argv);
// Linux: sudo apt-get install libmagick++-dev
// More info here https://stackoverflow.com/questions/37759833/about-magick-how-to-write-the-cmakelists


/**
* We do not need any auxiliary functions in this example, so let us start directly in main():
**/
int main(int argc,char **argv)
{
  // Construct the image object. Seperating image construction from the 
  // the read operation ensures that a failure to read the image file 
  // doesn't render the image object useless. 
  Magick::Image image;
  try { 
    // Read a file into image object 
    image.read("../../data/SamplePNG_Adapted_Mesh.png");

    // Crop the image to specified size (width, height, xOffset, yOffset)
    // image.crop( Magick::Geometry(100,100, 100, 100) );

    // Write the image to a file 
    image.write( "logo.png" ); 
    image.separate(MagickCore::ChannelType::RedChannel).write("modified_red.png");
    image.separate(MagickCore::ChannelType::GreenChannel).write("modified_green.png");
    image.separate(MagickCore::ChannelType::BlueChannel).write("modified_blue.png");
  } 
  catch( std::exception &error_ ) 
    { 
      std::cout << "Caught exception: " << error_.what() << std::endl; 
      return 1; 
    } 
 
  std::cout << image.format() << ": " <<image.fileSize() << " = " << image.columns() <<" * "<< image.rows() << " * " << image.depth() << std::endl;

  std::cout << "Type = " << (int)image.type() << std::endl;
  // std::cout << image.fileSize() << (image.interlaceType()==MagickCore::InterlaceType::NoInterlace ) <<std::endl;

  size_t column_num = image.columns(); 
  size_t row_num = image.rows(); 
  // Calc what your range is. See http://www.imagemagick.org/Magick++/Color.html
  // There's also other helpful macros, and definitions in ImageMagick's header files
  int range = pow(2, image.modulusDepth()); std::cout << "Quantum Range: " << range << std::endl; 
  assert(range > 0); // Better do some assertion/error checking here
  // Allocate pixel view 
  Magick::PixelPacket *pixels = image.getPixels(0,0, column_num, row_num);
  


  typedef float   vcl_ScalarT;
  typedef viennacl::vector<vcl_ScalarT> vcl_VectorT;
  typedef viennacl::matrix<vcl_ScalarT> vcl_MatrixT;

  long pixel_index = 0; 
  size_t color_num = 4;


  std::vector< std::vector< std::vector<vcl_ScalarT> > >  stl_image_colpre(4);

  for (size_t color=0; color< color_num; color++)
  {
    stl_image_colpre[color].resize(row_num);
    for (ssize_t i=0; i < row_num; ++i) // i: row index, [0, 1,..., row_number-1]
      stl_image_colpre[color][i].resize(column_num);
  }

  for (ssize_t i=0; i < row_num; ++i) // i: row index, [0, 1,..., row_number-1]
  {
    for (ssize_t j= 0; j < column_num; ++j) // j: column index, [0, 1,..., column_num-1]
    {
      // TODO: Hard Code
      stl_image_colpre[0][i][j] = static_cast<vcl_ScalarT> (pixels[pixel_index].red);
      stl_image_colpre[1][i][j] = static_cast<vcl_ScalarT> (pixels[pixel_index].green);
      stl_image_colpre[2][i][j] = static_cast<vcl_ScalarT> (pixels[pixel_index].blue);
      stl_image_colpre[3][i][j] = static_cast<vcl_ScalarT> (pixels[pixel_index].opacity);
      pixel_index++;
    }
  }

  viennacv::image_colpre<vcl_ScalarT> vcl_image_colpre(stl_image_colpre);


  // TODO: change this part of code to the viennacl style parallel code
  // size_t shift=100;

  // viennacl::range vcl_r1(0, column_num - shift);   //the first 'dim_small' entries
  // viennacl::range vcl_r2(shift, column_num); //the last 'dim_small' entries
  // viennacl::range vcl_height(0, row_num);
  // for (size_t color=0; color< color_num; color++)
  //   viennacl::copy(stl_image_colpre[color], vcl_image_colpre[color]);
  // for (size_t color=0; color< color_num; color++) // TODO: There may be bugs here.
  // {
  //   viennacl::matrix_range<vcl_MatrixT>   vcl_A_sub1(vcl_image_colpre_handled[color], vcl_height, vcl_r1); //upper left part of A
  //   viennacl::matrix_range<vcl_MatrixT>   vcl_A_sub2(vcl_image_colpre[color], vcl_height, vcl_r2); //lower right part of A
  //   vcl_A_sub1 = vcl_A_sub2;
  // }
  
  // std::cout << "I am fine between convolve"<< std::endl;
  vcl_MatrixT kernel(5, 5);
  kernel.clear();
  kernel(2, 1) = 1.0/2; kernel(2, 2) = 0.0; kernel(2, 3) = 1.0/2;
  // std::cout << kernel << std::endl; 

  std::vector<std::pair<size_t, size_t>> vec;
  vec.push_back(std::make_pair<int,int>(2, 3));
  vec.push_back(std::make_pair<int,int>(2, 1));
  // vec.push_back(std::make_pair(20,30));

  viennacv::convolve<vcl_ScalarT>(vcl_image_colpre, kernel);

  viennacv::image_colpre<vcl_ScalarT> gray_image( 1, 
                                                  vcl_image_colpre.get_row_num(),
                                                  vcl_image_colpre.get_column_num());
  viennacv::image_colpre<vcl_ScalarT> sobel_image( 1, 
                                                  vcl_image_colpre.get_row_num(),
                                                  vcl_image_colpre.get_column_num());
  viennacv::image_colpre<vcl_ScalarT> gaussian_image( 1, 
                                                  vcl_image_colpre.get_row_num(),
                                                  vcl_image_colpre.get_column_num());
  viennacv::format_transform<vcl_ScalarT> (vcl_image_colpre, gray_image, viennacv::Gray);
  // viennacl::copy(gray_image, &stl_image_colpre);
  viennacv::filter::gaussian<vcl_ScalarT>(gray_image, (vcl_ScalarT)6.0, gaussian_image);
  viennacl::copy(gaussian_image, &stl_image_colpre);

  
  
  

  // If this is not done, then image pixels will not be modified.

  // TODO: supplement the direct transfer interface to and from (-> & <-) Magick++   
  // Magick::Image modified_image = Magick::Image(Magick::Geometry(column_num, row_num), Magick::Color("black"));
  // // Set the image type to TrueColor DirectClass representation.
  // modified_image.modifyImage();
  // modified_image.type(Magick::ImageType::TrueColorMatteType);
  // Magick::PixelPacket * modified_pixels = modified_image.setPixels(0,0, column_num, row_num);  // FIXME: I don't know why, but if you delete this line, there will be bugs when you access pixels[pixel_index++];
  // pixel_index = 0; 
  // std::cout << row_num << ",  " << column_num << std::endl;
  // for (ssize_t i=0; i < row_num; ++i) // i: row index, [0, 1,..., row_number-1]
  // {
  //   // std::cout << "Line " <<i << " has been finished."<<std::endl;
  //   for (ssize_t j= 0; j < column_num; ++j) // j: column index, [0, 1,..., column_num-1]
  //   {
  //     modified_pixels[pixel_index].red = (Magick::Quantum)stl_image_colpre[0][i][j];
  //     modified_pixels[pixel_index].green = (Magick::Quantum)stl_image_colpre[1][i][j];
  //     modified_pixels[pixel_index].blue = (Magick::Quantum)stl_image_colpre[2][i][j];
  //     modified_pixels[pixel_index].opacity = (Magick::Quantum)stl_image_colpre[3][i][j];
  //     pixel_index++;
  //   }
  // }
  // modified_image.syncPixels();
  // modified_image.write("./modified_RGB.png");
  // std::cout << "Written the RGB png" << std::endl;

  Magick::Image modified_image = Magick::Image(Magick::Geometry(column_num, row_num), Magick::Color("black"));
  // Set the image type to TrueColor DirectClass representation.
  modified_image.modifyImage();
  modified_image.type(Magick::ImageType::GrayscaleType);
  Magick::PixelPacket * modified_pixels = modified_image.setPixels(0,0, column_num, row_num);  // FIXME: I don't know why, but if you delete this line, there will be bugs when you access pixels[pixel_index++];
  pixel_index = 0; 
  std::cout << row_num << ",  " << column_num << std::endl;
  for (ssize_t i=0; i < row_num; ++i) // i: row index, [0, 1,..., row_number-1]
  {
    // std::cout << "Line " <<i << " has been finished."<<std::endl;
    for (ssize_t j= 0; j < column_num; ++j) // j: column index, [0, 1,..., column_num-1]
    {
      modified_pixels[pixel_index].red = (Magick::Quantum)stl_image_colpre[0][i][j];
      modified_pixels[pixel_index].green = (Magick::Quantum)stl_image_colpre[0][i][j];
      modified_pixels[pixel_index].blue = (Magick::Quantum)stl_image_colpre[0][i][j];
      pixel_index++;
    }
  }
  modified_image.syncPixels();
  modified_image.write("./modified_gray.png");
  std::cout << "Written the gray png" << std::endl;


  /**
  *  That's it.
  **/
  std::cout << "!!!! TUTORIAL COMPLETED SUCCESSFULLY !!!!" << std::endl;

  return EXIT_SUCCESS;
}

