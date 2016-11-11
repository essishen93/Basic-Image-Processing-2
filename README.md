This README file is the Introduction of "EE569_hw2_4946850713_Shen.zip" and 
                    the Guidance of compiling and running the projects.

The source code outside the .zip file is just a sample. Please unzip the .zip file to see and run the complete project.

#################################################

Except problem_1_(6) SVM which was built on Microsoft Visual C++ 2010 Expression Edition, WIN7 (x64)
because there is no “CvSVM” in opencv 3.0.0
All other the projects were built on Xcode(7.0.1), OS X
The version of opencv is 3.0.0

#################################################

The Steps of running a projects: (Xcode)
1) open Xcode
2) open a project in the "EE569_hw2_4946850713_Shen.zip"
3) click “command+B” to build 
4) click “command+R” to run

The Steps of running a projects: (Microsoft Visual C++)
1) open Microsoft Visual C++ or Microsoft Visual Studio
2) open a project in the "EE569_hw2_4946850713_Shen.zip"
   (may wait a few minutes for upgrading if you use the latest Microsoft Visual)
3) click "Build->Build Solution" 
4) click "Debug->Start Debugging"
5) run the code

#################################################
  
Problem 1 (a):   get 25-D feature vectors of the image

Project:         GetFV_p1a->GetFV_p1a(.xcodeproj)

Source File:     main.cpp 
                 get_FV.cpp
                 get_Normalized.cpp 
                 functions.h

Input Image:     grass_##.raw
                 straw_##.raw
                 unknown_##.raw

Output files:    feature_vector_grass.txt & grass.txt    (25-D feature vectors of grass image)
                 feature_vector_straw.txt & straw.txt    (25-D feature vectors of straw image)
                 feature_vector_unknown.txt & unknown.txt(25-D feature vectors of unknown image)

#################################################
  
Problem 1 (a):   Minimum Mean Distance Classifier

Project:         Min_Mean->Min_Mean(.xcodeproj)

Source File:     main.cpp 

Input file:      feature_vector_grass.txt
                 feature_vector_straw.txt
                 feature_vector_unknown.txt

Output results:  display in 'All Output' console

#################################################

  
Problem 1 (a):   Minimum Mean Distance Classifier+PCA

Project:         PCA->PCA(.xcodeproj)

Source File:     main.cpp 

Input file:      feature_vector_grass.txt
                 feature_vector_straw.txt
                 feature_vector_unknown.txt

Output results:  display in 'All Output' console

#################################################
  
Problem 1 (a):   Minimum Mean Distance Classifier+LDA

Project:         LDA->LDA(.xcodeproj)

Source File:     main.cpp 

Input file:      feature_vector_grass.txt
                 feature_vector_straw.txt
                 feature_vector_unknown.txt

Output results:  display in 'All Output' console

#################################################
  
Problem 1 (b):   get 25-D feature vectors of the image

Project:         GetFV_p1b->GetFV_p1b(.xcodeproj)

Source File:     main.cpp 
                 get_FV.cpp
                 normalized.cpp 
                 functions.h

Input Image:     grass_##.raw
                 straw_##.raw
                 leather_##.raw
                 sand_##.raw

Output files:    feature_vector_grass.txt & grass.txt    (25-D feature vectors of grass image)
                 feature_vector_straw.txt & straw.txt    (25-D feature vectors of straw image)
                 feature_vector_leather.txt & leather.txt(25-D feature vectors of leather image)
                 feature_vector_sand.txt & sand.txt      (25-D feature vectors of sand image)

#################################################
  
Problem 1 (b):   Grass vs Non-grass

Project:         SVM_grass->Min_Mean->Min_Mean(.vcproj)

Source File:     main.cpp 
                 input_FV.cpp
                 min_mean.cpp 
                 functions.h

Input file:      feature_vector_grass.txt
                 feature_vector_straw.txt
                 feature_vector_leather.txt
                 feature_vector_sand.txt

Output results:  display in 'All Output' console

#################################################
  
Problem 1 (b):   Straw vs Non-straw

Project:         SVM_straw->Min_Mean->Min_Mean(.vcproj)

Source File:     main.cpp 
                 input_FV.cpp
                 min_mean.cpp 
                 functions.h

Input file:      feature_vector_grass.txt
                 feature_vector_straw.txt
                 feature_vector_leather.txt
                 feature_vector_sand.txt

Output results:  display in 'All Output' console

#################################################
  
Problem 1 (b):   Leather vs Non-leather

Project:         SVM_leather->Min_Mean->Min_Mean(.vcproj)

Source File:     main.cpp 
                 input_FV.cpp
                 min_mean.cpp 
                 functions.h

Input file:      feature_vector_grass.txt
                 feature_vector_straw.txt
                 feature_vector_leather.txt
                 feature_vector_sand.txt

Output results:  display in 'All Output' console

#################################################
  
Problem 1 (b):   Sand vs Non-sand

Project:         SVM_sand->Min_Mean->Min_Mean(.vcproj)

Source File:     main.cpp 
                 input_FV.cpp
                 min_mean.cpp 
                 functions.h

Input file:      feature_vector_grass.txt
                 feature_vector_straw.txt
                 feature_vector_leather.txt
                 feature_vector_sand.txt

Output results:  display in 'All Output' console

#################################################
  
Problem 2 (a):   Sobel Edge Detection & Non Maximum Supression

Project:         Sobel_ED->Sobel_ED(.xcodeproj)

Source File:     main.cpp 
                 rgbTogray.cpp
                 SobelED.cpp
                 NmsED.cpp 
                 functions.h

Input image:     Farm.raw
                 Cougar.raw

Output image:    Farm_gray.raw          (gray image)
                 Farm_edge_10.raw       (Sobel:10%)
                 Farm_edge_15.raw       (Sobel:15%)
                 Farm_edge_nms_10.raw   (Sobel+NMS:10%)
                 Farm_edge_nms_15.raw   (Sobel+NMS:10%)

                 Cougar_gray.raw        (gray image)
                 Cougar_edge_10.raw     (Sobel:10%)
                 Cougar_edge_15.raw     (Sobel:15%)
                 Cougar_edge_nms_10.raw (Sobel+NMS:10%)
                 Cougar_edge_nms_15.raw (Sobel+NMS:10%)

#################################################
  
Problem 2 (b):   Canny Edge Detection 

Project:         Canny_ED->Canny_ED(.xcodeproj)

Source File:     main.cpp 
                 rgbTogray.cpp
                 functions.h

Input image:     Farm.raw
                 Cougar.raw

Output image:    Farm_canny.raw         (edge map)
                 Cougar_canny.raw       (edge map))
                

#################################################
  
Problem 2 (c)
Problem 2 (d):   Structure Edge Detection 

Instructions:    Because we use other people’s codes for this part. So there are only
                 some codes for reading raw image and creating struct of ground truth 
                 for the evaluation of performance of edge detection.    

M-file name:     zReadRaw.m
                 newEvl.m    
                
#################################################
  


