#pragma once

#if !defined(_WIN32) && !defined(_WIN64)
#define DLR_API __attribute__((visibility("default")))
#else
#ifdef DLR_EXPORTS
#define DLR_API __declspec(dllexport)
#else
#define DLR_API 
#endif
#endif


#define DLR_VERSION                  "1.0.0.0623"

/**Successful. */
#define DLR_OK									 0 

/**Unknown error. */
#define DLRERR_UNKNOWN						-10000 

/**Not enough memory to perform the operation. */
#define DLRERR_NO_MEMORY					-10001 

/**Null pointer */
#define DLRERR_NULL_POINTER				-10002 

/**License invalid*/
#define DLRERR_LICENSE_INVALID				-10003 

/**File not found*/
#define DLRERR_FILE_NOT_FOUND				-10004 

/**Json parse failed*/
#define DLRERR_JSON_PARSE_FAILED			-10005 

/**Json type invalid*/
#define DLRERR_JSON_TYPE_INVALID			-10006 

/**Json key invalid*/
#define DLRERR_JSON_KEY_INVALID			-10007 

/**Json value invalid*/
#define DLRERR_JSON_VALUE_INVALID			-10008 

/**Json name key missing*/
#define DLRERR_JSON_NAME_KEY_MISSING           -10009

/**The value of the key "Name" is duplicated.*/
#define DLRERR_JSON_NAME_VALUE_DUPLICATED    -10010

/**Parameter value invalid*/
#define DLRERR_PARAMETER_VALUE_INVALID -10011

/**Template name invalid*/
#define DLRERR_TEMPLATE_NAME_INVALID -10012

/**License expired*/
#define DLRERR_LICENSE_EXPIRED -10013

/**Character Model file is not found*/
#define DLRERR_CHARACTER_MODEL_FILE_NOT_FOUND -10014

/**
* @enum DLRImagePixelFormat
*
* Describes the image pixel format.
*
*/
typedef enum DLRImagePixelFormat
{
	/**0:Black, 1:White */
	DLR_IPF_BINARY,

	/**0:White, 1:Black */
	DLR_IPF_BINARYINVERTED,

	/**8bit gray */
	DLR_IPF_GRAYSCALED,

	/**NV21 */
	DLR_IPF_NV21,

	/**16bit with RGB channel order stored in memory from high to low address*/
	DLR_IPF_RGB_565,

	/**16bit with RGB channel order stored in memory from high to low address*/
	DLR_IPF_RGB_555,

	/**24bit with RGB channel order stored in memory from high to low address*/
	DLR_IPF_RGB_888,

	/**32bit with ARGB channel order stored in memory from high to low address*/
	DLR_IPF_ARGB_8888,

	/**48bit with RGB channel order stored in memory from high to low address*/
	DLR_IPF_RGB_161616,

	/**64bit with ARGB channel order stored in memory from high to low address*/
	DLR_IPF_ARGB_16161616,

	/**32bit with ABGR channel order stored in memory from high to low address*/
	DLR_IPF_ABGR_8888,

	/**64bit with ABGR channel order stored in memory from high to low address*/
	DLR_IPF_ABGR_16161616,

	/**24bit with BGR channel order stored in memory from high to low address*/
	DLR_IPF_BGR_888

}DLRImagePixelFormat;

///**
//* @enum DLRTextColourMode
//*
//* Describes the text colour mode.
//*
//*/
//typedef enum
//{
//	/**Dark items on a light background*/
//	DLR_TCM_DARK_ON_LIGHT = 1,
//
//	/**Light items on a dark background*/
//	DLR_TCM_LIGHT_ON_DARK = 2,
//
//	/**Skip*/
//	DLR_TCM_SKIP = 0
//}DLRTextColourMode;

/**
* @enum DLRGrayscaleTransformationMode
*
* Describes the grayscale transformation mode.
*/
typedef enum DLRGrayscaleTransformationMode
{
	/**Transforms to inverted grayscale. Recommended for light on dark images. */
	DLR_GTM_INVERTED = 0x01,

	/**Keeps the original grayscale. Recommended for dark on light images. */
	DLR_GTM_ORIGINAL = 0x02,

	/**Reserved setting for grayscale transformation mode.*/
#if defined(_WIN32) || defined(_WIN64)
	DLR_GTM_REV = 0x80000000,
#else
	DLR_GTM_REV = -2147483648,
#endif

	/**Skips grayscale transformation. */
	DLR_GTM_SKIP = 0x00

}DLRGrayscaleTransformationMode;

/**
* @enum DLRRegionPredetectionMode
*
* Describes the region predetection mode.
*
*/
typedef enum DLRRegionPredetectionMode
{
	/**Auto*/
	DLR_RPM_AUTO = 0x01, 

	/**Takes the whole image as a region*/
	DLR_RPM_GENERAL = 0x02,

	/**Detects region using the general algorithm based on RGB colour contrast*/
	DLR_RPM_GENERAL_RGB_CONTRAST = 0x04,

	/**Detects region using the general algorithm based on gray contrast*/
	DLR_RPM_GENERAL_GRAY_CONTRAST = 0x08,

	/**Detects region using the general algorithm based on HSV colour contrast*/
	DLR_RPM_GENERAL_HSV_CONTRAST = 0x10,

	/**Reserved setting for region predection mode.*/
#if defined(_WIN32) || defined(_WIN64)
	DLR_RPM_REV = 0x80000000,
#else
	DLR_RPM_REV = -2147483648,
#endif

	/**Skip*/
	DLR_RPM_SKIP = 0
}DLRRegionPredetectionMode;

/**
* @enum DLRBinarizationMode
*
* Describes the binarization mode.
*
*/
typedef enum DLRBinarizationMode
{
	/**Not supported yet. */
	DLR_BM_AUTO = 0x01,

	/**Binarizes the image based on the local block. Check @ref BM for available argument settings.*/
	DLR_BM_LOCAL_BLOCK = 0x02,

	/**Performs image binarization based on the given threshold. Check @ref BM for available argument settings.*/
	DLR_BM_THRESHOLD = 0x04,

	/**Reserved setting for binarization mode.*/
#if defined(_WIN32) || defined(_WIN64)
	DLR_BM_REV = 0x80000000,
#else
	DLR_BM_REV = -2147483648,
#endif

	/**Skips the binarization. */
	DLR_BM_SKIP = 0x00
}DLRBinarizationMode;

/**
* @enum DLRImagePreprocessingMode
*
* Describes the image preprocessing mode.
*
*/
typedef enum DLRImagePreprocessingMode
{
	/**Not supported yet. */
	DLR_IPM_AUTO = 0x01,

	/**Takes the unpreprocessed image for following operations. */
	DLR_IPM_GENERAL = 0x02,

	/**Preprocesses the image using the gray equalization algorithm. Check @ref IPM for available argument settings.*/
	DLR_IPM_GRAY_EQUALIZE = 0x04,

	/**Preprocesses the image using the gray smoothing algorithm. Check @ref IPM for available argument settings.*/
	DLR_IPM_GRAY_SMOOTH = 0x08,

	/**Preprocesses the image using the sharpening and smoothing algorithm. Check @ref IPM for available argument settings.*/
	DLR_IPM_SHARPEN_SMOOTH = 0x10,

	/**Preprocesses the image using the morphology algorithm. Check @ref IPM for available argument settings.*/
	DLR_IPM_MORPHOLOGY = 0x20,

	/**Reserved setting for image preprocessing mode.*/
#if defined(_WIN32) || defined(_WIN64)
	DLR_IPM_REV = 0x80000000,
#else
	DLR_IPM_REV = -2147483648,
#endif

	/**Skips image preprocessing. */
	DLR_IPM_SKIP = 0x00
}DLRImagePreprocessingMode;

#pragma pack(push)
#pragma pack(1)

/**
* @struct DLRPoint
*
* Stores an x- and y-coordinate pair in two-dimensional space.
*
*/
typedef struct tagDLRPoint
{
	/**The X coordinate of the point.*/
	int x;

	/**The Y coordinate of the point.*/
	int y;
}DLRPoint;

/**
* @struct DLRImageData
*
* Stores the image data.
*
*/
typedef struct tagDLRImageData
{
	/**The length of the image data byte.*/
	int bytesLength;

	/**The image data content in a byte array.*/
	unsigned char* bytes;

	/**The width of the image in pixels.*/
	int width;

	/**The height of the image in pixels.*/
	int height;

	/**The stride(or scan width) of the image.*/
	int stride;

	/**The image pixel format used in the image byte array.*/
	DLRImagePixelFormat format;
}DLRImageData;

/**
* @struct DLRQuadrilateral
*
* Stores the quadrilateral.
*
*/
typedef struct tagDLRQuadrilateral
{
	/**The four points of the quadrilateral.*/
	DLRPoint points[4];

}DLRQuadrilateral;

/**
* @struct DLRRegion
*
* Stores the region info.
*
*/
typedef struct tagDLRRegion
{
	DLRPoint points[4];

	/**The coordinate type.*/
	int regionMeasuredByPercentage;
}DLRRegion;

/**
* @struct DLRRuntimeSettings
*
* Defines a struct to configure the runtime settings. These settings control the recognition process.
*
*/
typedef struct tagDLRRuntimeSettings
{
	/**Sets the number of the threads the algorithm will use to recognize text.*/
	int maxThreadCount;

	/**Sets the name of the CharacterModel.*/
	char characterModelName[64];

	/**Sets the text lines count of the text area.*/
	int linesCount;

	/**Sets the region predetection modes.
	*
	* @par Value range:
	* 	    Each array item can be any one of the DLRRegionPredetectionMode Enumeration items.
	* @par Default value:
	* 	    [DLR_RPM_GENERAL,DLR_RPM_SKIP,DLR_RPM_SKIP,DLR_RPM_SKIP,DLR_RPM_SKIP,DLR_RPM_SKIP,DLR_RPM_SKIP,DLR_RPM_SKIP]
	* @par Remarks:
	*     The array index represents the priority of the item. The smaller index is, the higher priority is.
	* @sa DLRRegionPredetectionMode
	*/
	DLRRegionPredetectionMode regionPredetectionModes[8];

	/**Sets the reference region to search for text.*/
	DLRRegion referenceRegion;

	/**Sets the text area relative to the reference region.*/
	DLRQuadrilateral textArea;

	/**Sets the mode and priority for the grayscale image conversion.
	*
	* @par Value range:
	* 	    Each array item can be any one of the DLRGrayscaleTransformationMode Enumeration items.
	* @par Default value:
	* 	    [DLR_GTM_ORIGINAL,DLR_GTM_SKIP,DLR_GTM_SKIP,DLR_GTM_SKIP,DLR_GTM_SKIP,DLR_GTM_SKIP,DLR_GTM_SKIP,DLR_GTM_SKIP]
	* @par Remarks:
	*     The array index represents the priority of the item. The smaller index is, the higher priority is.
	* @sa DLRGrayscaleTransformationMode
	*/
	DLRGrayscaleTransformationMode grayscaleTransformationModes[8];

	/**Reserved memory for the struct.*/
	char reserved[64];
}DLRRuntimeSettings;

/**
* @struct DLRCharacterResult
*
* Stores character result.
*
*/
typedef struct tagDLRCharacterResult
{
	/**The recognized character with highest confidence.*/
	char characterH;

	/**The recognized character with middle confidence.*/
	char characterM;

	/**The recognized character with lowest confidence.*/
	char characterL;

	/**The location of current character.*/
	DLRQuadrilateral location;

	/**Reserved memory for the struct.*/
	char reserved[32];
}DLRCharacterResult, *PDLRCharacterResult;

/**
* @struct DLRLineResult
*
* Stores line result.
*
*/
typedef struct tagLineResult
{
	/**The name of the line specification used to recognize current line result.*/
	const char* lineSpecificationName;

	/**The recognized text, ends by '\0'.*/
	const char* text;

	/**The character model used to recognize the text.*/
	const char* characterModelName;

	/**The localization of current line.*/
	DLRQuadrilateral location;

	/**The confidence of the result.*/
	int confidence;

	/**The character result count.*/
	int characterResultsCount;

	/**The character results array.*/
	PDLRCharacterResult* characterResults;

	/**Reserved memory for the struct.*/
	char reserved[64];
}DLRLineResult, *PDLRLineResult;

/**
* @struct DLRResult
*
* Stores result.
*
*/
typedef struct tagDLRResult
{
	/**The name of the reference region used to recognize current result.*/
	const char* refereneceRegionName;

	/**The name of the text area used to recognize current result.*/
	const char* textAreaName;

	/**The localization result.*/
	DLRQuadrilateral location;

	/**The confidence of the result.*/
	int confidence;

	/**The line result count.*/
	int lineResultsCount;

	/**The line results array.*/
	PDLRLineResult* lineResults;

	/**Reserved memory for the struct.*/
	char reserved[64];
}DLRResult, *PDLRResult;

/**
* @struct DLRResultArray
*
* Stores result array.
*
*/
typedef struct tagDLRResultArray
{
	/**The recognized results array.*/
	PDLRResult* results;

	/**The total count of recognized results.*/
	int resultsCount;
}DLRResultArray;

typedef struct tagTextResultArray TextResultArray;
typedef struct tagDM_LTSConnectionParameters DM_LTSConnectionParameters;

#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* Returns the error info string.
	*
	* @param [in] errorCode The error code.
	*
	* @return The error message.
	*
	*/
	DLR_API const char* DLR_GetErrorString(const int errorCode);

	/**
	* Returns the version info of the SDK.
	*
	* @return The version info string.
	*
	*/
	DLR_API const char* DLR_GetVersion();

	/**
	* Creates a Dynamsoft DLR instance.
	*
	* @return An DLR instance. If failed, return NULL.
	*
	*/
	DLR_API void* DLR_CreateInstance();

	/**
	* Destorys an instance of Dynamsoft DLR instance.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	*
	*/
	DLR_API void DLR_DestroyInstance(void* recognizer);

	/**
	* Reads product key and activates the SDK. 
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] pLicense The product key.
	* 			   
	* @return Returns error code. Returns 0 if the function operates successfully. You can call 
	* 		   DLR_GetErrorString() to get detailed error message.
	*/
	DLR_API int DLR_InitLicense(void* recognizer, const char* pLicense);

	/**
	* Gets current settings and save it into a struct.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in, out] pSettings The struct of runtime settings.
	* 
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DLR_GetErrorString() to get detailed error message.
	*/
	DLR_API int DLR_GetRuntimeSettings(void* recognizer, DLRRuntimeSettings* pSettings);

	/**
	* Updates runtime settings with a given struct.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] pSettings The struct of runtime settings.
	* @param [in, out] errorMsgBuffer The buffer is allocated by caller and the recommended length is 256. The error message will be copied to the bufer.
	* @param [in] errorMsgBufferLen The length of the allocated buffer.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can check errorMsgBuffer to get detailed error message.
	*/
	DLR_API int DLR_UpdateRuntimeSettings(void* recognizer, DLRRuntimeSettings* pSettings, char errorMsgBuffer[], const int errorMsgBufferLen);

	/**
	* Reset runtime settings.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	*
	*/
	DLR_API int DLR_ResetRuntimeSettings(void* recognizer);

	/**
	* Clear template settings.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	*
	*/
	DLR_API int DLR_ClearAppendedSettings(void* recognizer);

	/**
	* Appends DLRParameter settings in a string to the SDK object.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance. 
	* @param [in] content A json string that represents the content of the settings.
	* @param [in, out] errorMsgBuffer The buffer is allocated by caller and the recommended length is 256. The error message will be copied to the bufer.
	* @param [in] errorMsgBufferLen The length of the allocated buffer.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can check errorMsgBuffer to get detailed error message.
	*
	*/
	DLR_API int DLR_AppendSettingsFromString(void* recognizer, const char* content, char errorMsgBuffer[], const int errorMsgBufferLen);

	/**
	* Output DLRParameter settings into a file(JSON file).
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] outputFilePath The output file path which stores settings.
	* @param [in] templateName The name of the template which is to be output.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DLR_GetErrorString() to get detailed error message.
	*/
	DLR_API int DLR_OutputSettingsToFile(void* recognizer, const char* outputFilePath, const char* templateName);

	/**
	* Recognizes text from memory buffer containing image pixels in defined format.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] pImageDate A struct of DLRImageData that represents an image.
	* @param [in] templateName The template name.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DLR_GetErrorString() to get detailed error message.
	*
	*/
	DLR_API int DLR_RecognizeByBuffer(void* recognizer, const DLRImageData* pImageData, const char* templateName);

	/**
	* Recognizes text from a specified image file.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] fileName A string defining the file name.
	* @param [in] templateName The template name.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DLR_GetErrorString() to get detailed error message.
	*
	*/
	DLR_API int DLR_RecognizeByFile(void* recognizer, const char* fileName, const char* templateName);

	/**
	* Recognizes text from memory buffer containing image pixels in defined format according to barcode results from DBR SDK.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] pImageData A struct of DLRImageData that represents an image.
	* @param [in] DBRTextResultArray Text result array returned by DBR.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DLR_GetErrorString() to get detailed error message.
	*
	*/
	
	DLR_API int DLR_RecognizeBasedOnDBRResultsByBuffer(void* recognizer, const DLRImageData* pImageData, TextResultArray* DBRTextResultArray);

	/**
	* Recognizes text from a specified image file according to barcode results from DBR SDK.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] fileName A string defining the file name.
	* @param [in] DBRTextResultArray Text result array returned by DBR.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DLR_GetErrorString() to get detailed error message.
	*
	*/
	DLR_API int DLR_RecognizeBasedOnDBRResultsByFile(void* recognizer, const char* fileName, TextResultArray* DBRTextResultArray);

	/**
	* Get all recognized results.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param[in, out] pResults The results are allocated by our SDK and should be freed by calling the function DLR_FreeDLRResults.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DLR_GetErrorString() to get detailed error message.
	*
	*/
	DLR_API int DLR_GetAllDLRResults(void* recognizer, DLRResultArray** pResults);

	/**
	* Initializes a DM_LTSConnectionParameters struct with default values.
	*
	* @param [in, out] pLTSConnectionParameters The struct of DM_LTSConnectionParameters.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  DLR_GetErrorString() to get detailed error message.
	*
	*/
	DLR_API int DLR_InitLTSConnectionParameters(DM_LTSConnectionParameters *pLTSConnectionParameters);

	/**
	* Initializes the label recognition license and connects to the specified server for online verification.
	*
	* @param [in] pLTSConnectionParameters The struct DM_LTSConnectionParameters with customized settings.
	* @param [in, out] errorMsgBuffer The buffer is allocated by caller and the recommending length is 256. The error message will be copied to the buffer.
	* @param [in] errorMsgBufferLen The length of allocated buffer.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  DLR_GetErrorString() to get detailed error message.
	*
	*/
	DLR_API int DLR_InitLicenseFromLTS(DM_LTSConnectionParameters *pLTSConnectionParameters, char errorMsgBuffer[], const int errorMsgBufferLen);

	/**
	* Free memory allocated for recognized results.
	*
	* @param[in] pResults Recognized results.
	*
	*/
	DLR_API void DLR_FreeDLRResults(DLRResultArray** pResults);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

class LabelRecognitionInner;

namespace dynamsoft
{
	namespace dlr
	{

		class DLR_API CLabelRecognition
		{
		protected:
			LabelRecognitionInner * m_DLRInner;

		public:
			CLabelRecognition();

			~CLabelRecognition();

			/**
			* Returns the error info string.
			*
			* @param [in] errorCode The error code.
			*
			* @return The error message.
			*
			*/
			static const char* GetErrorString(const int errorCode);

			/**
			* Returns the version info of the SDK.
			*
			* @return The version info string.
			*
			*/
			static const char* GetVersion();

			/**
			* Reads product key and activates the SDK.
			*
			* @param [in] pLicense The product key.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*/
			int InitLicense(const char* pLicense);

			/**
			* Gets current settings and save it into a struct.
			*
			* @param [in, out] pSettings The struct of runtime settings.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*/
			int GetRuntimeSettings(DLRRuntimeSettings* pSettings);

			/**
			* Updates runtime settings with a given struct.
			*
			* @param [in] pSettings The struct of runtime settings.
			* @param [in, out] errorMsgBuffer The buffer is allocated by caller and the recommended length is 256. The error message will be copied to the bufer.
			* @param [in] errorMsgBufferLen The length of the allocated buffer.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can check errorMsgBuffer to get detailed error message.
			*
			*/
			int UpdateRuntimeSettings(DLRRuntimeSettings* pSettings, char errorMsgBuffer[], const int errorMsgBufferLen);

			/**
			* Reset runtime settings.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int ResetRuntimeSettings();

			/**
			* Clear template settings.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int ClearAppendedSettings();

			/**
			* Appends DLRParameter settings in a string to the SDK object.
			*
			* @param [in] content A json string that represents the content of the settings.
			* @param [in, out] errorMsgBuffer The buffer is allocated by caller and the recommended length is 256. The error message will be copied to the bufer.
			* @param [in] errorMsgBufferLen The length of the allocated buffer.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can check errorMsgBuffer to get detailed error message.
			*
			*/
			int AppendSettingsFromString(const char* content, char errorMsgBuffer[], const int errorMsgBufferLen);

			/**
			* Output DLRParameter settings into a file(JSON file).
			*
			* @param [in] outputFilePath The output file path which stores settings.
			* @param [in] templateName The name of the template which is to be output.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int OutputSettingsToFile(const char* outputFilePath, const char* templateName);

			/**
			* Recognizes text from memory buffer containing image pixels in defined format.
			*
			* @param [in] pImageDate A struct of DLRImageData that represents an image.
			* @param [in] templateName The template name.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int RecognizeByBuffer(const DLRImageData* pImageData, const char* templateName);

			/**
			* Recognizes text from a specified image file.
			*
			* @param [in] fileName A string defining the file name.
			* @param [in] templateName The template name.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int RecognizeByFile(const char* fileName, const char* templateName);

			/**
			* Recognizes text from memory buffer containing image pixels in defined format according to barcode results from DBR SDK.
			*
			* @param [in] pImageData A struct of DLRImageData that represents an image.
			* @param [in] DBRTextResultArray Text result array returned by DBR.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int RecognizeBasedOnDBRResultsByBuffer(const DLRImageData* pImageData, TextResultArray* DBRTextResultArray);

			/**
			* Recognizes text from a specified image file according to barcode results from DBR SDK.
			*
			* @param [in] fileName A string defining the file name.
			* @param [in] DBRTextResultArray Text result array returned by DBR.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int RecognizeBasedOnDBRResultsByFile(const char* fileName, TextResultArray* DBRTextResultArray);

			/**
			* Get all recognized results.
			*
			* @param[in, out] pResults The results are allocated by our SDK and should be freed by calling the function DLR_FreeDLRResults.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int GetAllDLRResults(DLRResultArray** pResults);

			/**
			* Initializes a DM_LTSConnectionParameters struct with default values.
			*
			* @param [in, out] pLTSConnectionParameters The struct of DM_LTSConnectionParameters.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		  DLR_GetErrorString() to get detailed error message. 
			*
			*/
			static int InitLTSConnectionParameters(DM_LTSConnectionParameters *pLTSConnectionParameters);

			/**
			* Initializes the label recognition license and connects to the specified server for online verification.
			*
			* @param [in] pLTSConnectionParameters The struct DM_LTSConnectionParameters with customized settings.
			* @param [in, out] errorMsgBuffer The buffer is allocated by caller and the recommending length is 256. The error message will be copied to the buffer.
			* @param [in] errorMsgBufferLen The length of allocated buffer.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		  DLR_GetErrorString() to get detailed error message.
			*
			*/
			static int InitLicenseFromLTS(DM_LTSConnectionParameters *pLTSConnectionParameters, char errorMsgBuffer[] = 0, const int errorMsgBufferLen = 0);

			/**
			* Free memory allocated for recognized results.
			*
			* @param[in] pResults Recognized results.
			*
			*/
			static void FreeDLRResults(DLRResultArray** pResults);

		private:
			CLabelRecognition(const CLabelRecognition& r);
			CLabelRecognition& operator=(const CLabelRecognition& r);
		};
	}
}
#endif