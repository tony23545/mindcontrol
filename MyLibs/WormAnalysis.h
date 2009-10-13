/*
 * WormAnalysis.h
 *
 *  Created on: Oct 12, 2009
 *      Author: andy
 *
 *      This library contains functions that are specific to analyzing worms.
 *
 *      Functions in this library depend on:
 *      	AndysOpenCVLib.h
 *      	AndysComputations.h
 */

#ifndef WORMANALYSIS_H_
#define WORMANALYSIS_H_

typedef struct WormAnalysisParamStruct{
	int LengthScale;
	int LengthOffset;
	int BinThresh;
	int GaussSize;
} WormAnalysisParam;

typedef struct WormImageAnalysisStruct{
	CvSize SizeOfImage;
	IplImage* ImgOrig;
	IplImage* ImgSmooth;
	IplImage* ImgThresh;
	CvMemStorage* MemStorage;
	CvMemStorage* MemScratchStorage;
	CvSeq* Boundary;
	CvPoint* Head;
	CvPoint* Tail;
	int TailIndex;
	int HeadIndex;
	CvSeq* Centerline;
	CvSeq* SegmentCenterline;
	CvSeq* SegmentLeft;
	CvSeq* SegmentRight;
}WormAnalysisData;


typedef struct WormIlluminationStcut{
	IplImage* IlluminationPattern;
	CvSeq* SegmentCenterline;
	CvSeq* SegmentLeft;
	CvSeq* SegmentRight;
	int* IlluminationArr;
}WormIlluminationData;



/*
 *
 * Every function here should have the word Worm in it
 * because every function here is worm specific
 */



/************************************************************/
/* Creating, Destroying and Memory for 						*/
/*  WormAnalysisDataStruct 									*/
/*															*/
/************************************************************/


/*
 *  Create the WormAnalysisDataStruct
 *  Initialize Memory Storage
 *  Set all Pointers to Null.
 *  Run CvCreate Sequence
 *
 *  Note this does not allocate memory for images because the user may not know
 *  what size image is wanted yet.
 *
 *  To do that use LoadWormColorOriginal()
 *
 */
WormAnalysisData* CreateWormAnalysisDataStruct();




/*
 *
 * Clear's all the Memory and De-Allocates it
 */
void DestroyWormAnalysisDataStruct(WormAnalysisData* WormPtr);



/*
 * Create dynamic memory storage for the worm
 *
 */
void InitializeWormMemStorage(WormAnalysisData* Worm);

/*
 * Refersh dynamic memory storage for the worm
 * (clear the memory without freing it)
 *
 */
void RefreshWormMemStorage(WormAnalysisData* Worm);


/*
 * Clear and de-allocate the memory storage for the worm
 *
 */
void DeallocateWormMemStorage(WormAnalysisData* Worm);


/*
 * Create Blank Images for WormAnalysisData given the image size.
 *
 */
void InitializeEmptyWormImages(WormAnalysisData* Worm, CvSize ImageSize);

/*
 * This function is run after IntializeEmptyImages.
 * And it loads a color original into the WoirmAnalysisData strucutre.
 * The color image is converted to an 8 bit black and white.
 *
 *
 */
void LoadWormColorOriginal(WormAnalysisData* Worm, IplImage* ImgColorOrig);




/************************************************************/
/* Creating, Destroying WormAnalysisParam					*/
/*  					 									*/
/*															*/
/************************************************************/

/*
 *  Allocate memory for a WormAnalysisParam struct
 */
WormAnalysisParam* CreateWormAnalysisParam();

void DestroyWormAnalysisParam(WormAnalysisParam* ParamPtr);


/************************************************************/
/* Higher Level Routines									*/
/*  					 									*/
/*															*/
/************************************************************/


/*
 * Smooths, thresholds and finds the worms contour.
 * The original image must already be loaded into Worm.ImgOrig
 * The Smoothed image is deposited into Worm.ImgSmooth
 * The thresholded image is deposited into Worm.ImgThresh
 * The Boundary is placed in Worm.Boundary
 *
 */
void FindWormBoundary(WormAnalysisData* Worm, WormAnalysisParam* WormParams);





/*
 * Finds the Worm's Head and Tail.
 * Requires Worm->Boundary
 *
 */
int GivenBoundaryFindWormHeadTail(WormAnalysisData* Worm, WormAnalysisParam* Params);



/*
 * Illuminate a segment of the worm. Either the right, or left side.
 * Takes a sequence of the centerline. Uses the preceeding point to find a vector
 * along the centerline, than draws a rectangle perpendicular to this vector, a radius rsquared pixels
 * away from the centerline
 */
void IlluminateWormSegment(IplImage** image, CvSeq* centerline, CvSeq* Boundary, int segment);









#endif /* WORMANALYSIS_H_ */
