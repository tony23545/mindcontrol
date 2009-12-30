/*
 * TransformLib.h
 *
 *  Created on: Oct 15, 2009
 *      Author: andy
 *
 *      The Transformation Library is the library that deals with transforming between
 *      the camera, OpenCV and the DLP. This was formerly called CalibLib because all of the
 *      calibration functions are handled in this library.
 *
 *      The idea is Calibration Library can include both the Talk2Camera and Talk2DLP libraries.
 *
 */

#ifndef TRANSFORMLIB_H_
#define TRANSFORMLIB_H_


#ifndef WORMANALYSIS_H_
 #error "#include WormAnalaysis.h" must appear in source files before "#include Transform.h" because one depends on the other.
#endif



/*
 * This structure contains information about calibrating the DLP to the CCD
 *
 */
typedef struct CalibDataStruct{
	int* CCD2DLPLookUp;
	CvSize SizeOfDLP;
	CvSize SizeOfCCD;
} CalibData;



/*
 * Transform's the binary image from the frame in Cam and transforms it DLP space.
 * Copies it into the DLP frame and also converts it to IlpImage and copies that to the DLP
 * frame also.
 *
 */
int TransformFrameCam2DLP(Frame* Cam, Frame* DLP, CalibData* Calib);




/*
 * Create and allocate memory for the CalibData structure
 *
 * Currently SizeOfCCD is stored but not really used
 *
 */
CalibData* CreateCalibData( CvSize SizeOfDLP, CvSize SizeOfCCD);

/*
 * Deallocate memory for CalibData object
 */
void DestroyCalibData(CalibData* Calib);




/*
 * Read In Calibration Frome File
 *
 * Returns 1 if open failed.
 * Returns -1 if open succesfully but read fails.
 */

int LoadCalibFromFile(CalibData* Calib, char * filename);




/*
 *  This function takes a lookup table generated by the CalibrationTest() function in calibrate.c
 *  It takes pointers to pre-allocated memory for the images fromCCD and forDLP which are
 *  unsigned character arrays in the Y800 format as employed by the Discovery 4000 DLP and the
 *  ImagingSource Camera. These are allocated with a function such as
 *
 *  fromCCD = (unsigned char *) malloc(NSIZEX * NSIZEY * sizeof(unsigned char));
 *
 *  nsizex and nsizey are ints that contain the x & y dimensionf the camera and the DLP. This will all change when we purchase a new camera
 *  with different sizes.
 *
 *  Currently ccdsizex and ccdsizey are simply placeholders, they don't do anything.
 *
 *  If DEBUG_FLAG !=0, then print debugging information.
 *
 *
 */
int ConvertCharArrayImageFromCam2DLP(int *CCD2DLPLookUp,  unsigned char* fromCCD,unsigned char* forDLP, int nsizex, int nsizey, int ccdsizex, int ccdsizey, int DEBUG_FLAG);

/*
 * Converts a CvPoint (x,y) camera space to DLP space.
 * This uses the lookup table generated by the CalibrationTest() function in calibrate.c
 *
 *  Currently ccdsizex and ccdsizey are simply placeholders, they don't do anything.
 *  In other words this assumes that both the camera and DLP are the simesize, namely 102
 *
 *	If DEBUG_FLAG !=0, then print debugging information.
 *
 *
 */
int cvtPtCam2DLP(CvPoint camPt, CvPoint* DLPpt,CalibData* Calib);

/*
 * Takes a SegmentedWorm and transforms all of the points from Camera to DLP coordinates
 *
 */
int TransformSegWormCam2DLP(SegmentedWorm* camWorm, SegmentedWorm* dlpWorm, CalibData* Calib);



#endif /* TRANSFORMLIB_H_ */
