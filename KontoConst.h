#ifndef KONTOCONST_H
#define KONTOCONST_H

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

#include "io/BufPageManager.h"

typedef unsigned int uint;

typedef char* KontoPage;
typedef unsigned int KontoKeyIndex; 
typedef unsigned int KontoKeyType;
typedef char* charptr;

struct KontoRPos;

class KontoIndex;

enum KontoResult {
    // META
    KR_ERROR                    = 0x00000000,
    KR_OK                       = 0x00000001,
    KR_NULL_PTR                 = 0x00000002,
    // FILE
    KR_FILE_CREATE_FAIL         = 0x00000200,
    KR_FILE_OPEN_FAIL           = 0x00000201,
    // ERROR IN KONTORECORD
    KR_FIELD_ALREARY_DEFINED    = 0x00000100,
    KR_PAGE_TOO_GREAT           = 0x00000101,
    KR_RECORD_INDEX_TOO_GREAT   = 0x00000102,
    KR_UNDEFINED_FIELD          = 0x00000103,
    KR_DATA_TOO_LONG            = 0x00000104,
    KR_TYPE_NOT_MATCHING        = 0x00000105,
    KR_NO_SUCH_COLUMN           = 0x00000106,
    // ERROR IN KONTOINDEX
    KR_EMPTY_KEYLIST            = 0x00000200,
    KR_NOT_FOUND                = 0x00000201,
    KR_LAST_IPOS                = 0x00000202,
    // ERROR IN KONTODBMGR
    KR_NOT_USING_DATABASE       = 0x00000300,
    KR_NO_SUCH_DATABASE         = 0x00000301,
    KR_DATABASE_NAME_EXISTS     = 0x00000302,
    // ERROR ABOUT PRIMARY KEY  
    KR_PRIMARY_REDECLARATION    = 0x00000400,
    KR_PRIMARY_REPETITION       = 0x00000401,
    KR_NO_PRIMARY               = 0x00000402,
    KR_NO_SUCH_FOREIGN          = 0x00000403
};

const KontoKeyType KT_INT        = 0x0;
const KontoKeyType KT_STRING     = 0x1;
const KontoKeyType KT_FLOAT      = 0x2;

const int DEFAULT_INT_VALUE = 0;
const double DEFAULT_FLOAT_VALUE = 0.0f;

string get_filename(string filename);

string strip_filename(string filename);

void debug_assert(bool assertion, std::string message);

std::vector<string> get_files(string prefix);

std::vector<string> get_directories();

std::vector<string> get_index_key_names(string fullFilename);

void remove_file(string filename);

void rename_file(string old, string newname); 

vector<string> get_directories();

bool directory_exist(string str);

void create_directory(string str);

void remove_directory(string str);

bool file_exist(string dir, string file);

vector<string> get_lines(string dir, string file);

void save_lines(string dir, string file, const vector<string>& lines);

// VALUE INTEGER
inline uint& VI(char* ptr){return *(uint*)(ptr);}
// VALUE INTEGER PLUS
inline uint& VIP(charptr& ptr){ptr+=4; return *(uint*)(ptr-4);}
// COPY STRING
inline void CS(char* dest, charptr& ptr){
    strcpy(dest, ptr); int len = strlen(dest); ptr+=len+1;
}
// COPY STRING
inline void CS(string& dest, charptr& ptr){
    dest = ptr; int len = dest.length(); ptr+=len+1;
}
// NEW COPY STRING
inline void NCS(charptr& dest, charptr& ptr, uint len){
    dest = new char[len];
    memcpy(dest, ptr, len); ptr+=len;
}
// PASTE STRING
inline void PS(charptr& dest, char* src){
    strcpy(dest, src); dest += strlen(src) + 1;
} 
// PASTE STRING
inline void PS(charptr& dest, const string& src) {
    strcpy(dest, src.c_str()); dest+=src.length()+1;
}
// PASTE DATA
inline void PD(charptr& dest, charptr src, uint cnt) {
    memcpy(dest, src, cnt); dest+=cnt;
}
// PLUS EMPTY
inline void PE(charptr& dest, uint cnt) {
    memset(dest, 0, cnt); dest += cnt;
}

#endif