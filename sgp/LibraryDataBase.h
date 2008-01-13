#ifndef _LIBRARY_DATABASE_H
#define _LIBRARY_DATABASE_H

#include "Types.h"
#include "FileMan.h"

#define	FILENAME_SIZE									256


#define NUM_FILES_TO_ADD_AT_A_TIME		20
#define INITIAL_NUM_HANDLES						20


#define	REAL_FILE_LIBRARY_ID					1022

#define	DB_BITS_FOR_LIBRARY							10
#define	DB_BITS_FOR_FILE_ID							22

#define	DB_EXTRACT_LIBRARY( exp )				( exp >> DB_BITS_FOR_FILE_ID )
#define	DB_EXTRACT_FILE_ID( exp )				( exp & 0x3FFFFF )

#define DB_ADD_LIBRARY_ID( exp )				( exp << DB_BITS_FOR_FILE_ID )
#define DB_ADD_FILE_ID( exp )						( exp & 0xC00000 )


extern	CHAR8	gzCdDirectory[ SGPFILENAME_LEN ];


typedef struct
{
	STR			pFileName;
	UINT32	uiFileLength;
	UINT32	uiFileOffset;
} FileHeaderStruct;


typedef struct
{
	UINT32	uiFilePosInFile;							// current position in the file
	const FileHeaderStruct* pFileHeader;
} FileOpenStruct;




typedef struct
{
	STR			sLibraryPath;
	FILE* hLibraryHandle;
	UINT16	usNumberOfEntries;
	BOOLEAN	fLibraryOpen;
//	BOOLEAN	fAnotherFileAlreadyOpenedLibrary;				//this variable is set when a file is opened from the library and reset when the file is close.  No 2 files can have access to the library at 1 time.
	UINT32	uiIdOfOtherFileAlreadyOpenedLibrary;				//this variable is set when a file is opened from the library and reset when the file is close.  No 2 files can have access to the library at 1 time.
	INT32		iNumFilesOpen;
	INT32		iSizeOfOpenFileArray;
	FileHeaderStruct *pFileHeader;
	FileOpenStruct	*pOpenFiles;

//
//	Temp:	Total memory used for each library ( all memory allocated
//
	#ifdef JA2TESTVERSION
		UINT32	uiTotalMemoryAllocatedForLibrary;
	#endif

} LibraryHeaderStruct;


typedef struct
{
	INT32		iNumFilesOpen;
	INT32		iSizeOfOpenFileArray;
	FILE** pRealFilesOpen;
} RealFileHeaderStruct;


typedef struct
{
	STR			sManagerName;
	LibraryHeaderStruct	*pLibraries;
	UINT16	usNumberOfLibraries;
	BOOLEAN	fInitialized;
	RealFileHeaderStruct RealFiles;
} DatabaseManagerHeaderStruct;


//*************************************************************************
//
//  NOTE!  The following structs are also used by the datalib98 utility
//
//*************************************************************************


#define FILE_OK							0
#define FILE_DELETED				0xff
#define FILE_OLD						1
#define FILE_DOESNT_EXIST		0xfe


typedef struct
{
	CHAR8		sLibName[ FILENAME_SIZE ];
	CHAR8		sPathToLibrary[ FILENAME_SIZE ];
	INT32		iEntries;
	INT32		iUsed;
	UINT16	iSort;
	UINT16	iVersion;
	BOOLEAN	fContainsSubDirectories;
	INT32		iReserved;
} LIBHEADER;
CASSERT(sizeof(LIBHEADER) == 532)


#ifdef __cplusplus
extern "C" {
#endif


//The FileDatabaseHeader
extern DatabaseManagerHeaderStruct gFileDataBase;


BOOLEAN InitializeFileDatabase(const char* LibFilenames[], UINT LibCount);
BOOLEAN ShutDownFileDatabase(void);
BOOLEAN CheckIfFileExistInLibrary(const char *pFileName);
HWFILE OpenFileFromLibrary(const char *pName);
HWFILE CreateRealFileHandle(FILE* hFile);
/* Close an individual file that is contained in the library */
BOOLEAN CloseLibraryFile(HWFILE);
BOOLEAN GetLibraryAndFileIDFromLibraryFileHandle( HWFILE hlibFile, INT16 *pLibraryID, UINT32 *pFileNum );
BOOLEAN LoadDataFromLibrary(HWFILE, void* pData, UINT32 uiBytesToRead);
BOOLEAN LibraryFileSeek(HWFILE, UINT32 uiDistance, UINT8 uiHowToSeek);

BOOLEAN IsLibraryOpened( INT16 sLibraryID );

BOOLEAN GetLibraryFileTime( INT16 sLibraryID, UINT32 uiFileNum, SGP_FILETIME	*pLastWriteTime );


#ifdef __cplusplus
}
#endif



#endif
