#include <jni.h>
#include <string>
#include <stdio.h>
#include <android/log.h>
//方便用日誌檢視

#include <fstream>
#include<iostream>
#include<cmath>
//#define readavn
//#define AVCID MD2
#define LOG_D(...)  __android_log_print(ANDROID_LOG_DEBUG, "poi", __VA_ARGS__)
//使用巨集來呼叫日誌庫

void writeMD2();
void writeAVN();
void writesystemAVN();
extern "C" JNIEXPORT jstring JNICALL
Java_com_rextron_jnireadfile_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

//    LOG_D("poi WRITE");
//    FILE* file = NULL;
//    file = fopen("/data/data/com.rextron.jnireadfile/sku_id.txt","w");    //建立檔案
//    if(file == NULL){        //容錯
//        LOG_D("檔案建立失敗%s","fail");
//    }
//    fwrite("MD2",3,1,file);            //往檔案中寫檔案
//    fclose(file);                    //關閉檔案

    //writeMD2();
    //writeAVN();
    //writesystemAVN();

    FILE          *fp;
    char filePath[] = "/data/data/com.rextron.jnireadfile/sku_id.txt";
    char          value[256];
    long          lSize;
    fp = fopen(filePath, "r");
    if(fp){
        fseek (fp , 0 , SEEK_END);
        lSize = ftell (fp);
        fseek (fp , 0 , 0);
        if(lSize > 0) {
            fread(value, 1, lSize, fp);
            value[lSize]='\0';
        }
        fclose(fp);
        LOG_D("value:%s",value);
        if ((value[0] == 'A' && value[1] == 'V')
            && (value[2] == 'N' )){
            LOG_D("AVN check value:%s",value);
            #define AVCIDAVN 1
//#define AVCIDMD2
        }
        if ((value[0] == 'M' && value[1] == 'D')
            && (value[2] == '2' )){
            LOG_D("MD2 check value:%s",value);
//            #define AVCIDMD2
            #define AVCIDAVN 0
        }
    } else {
        LOG_D("Can not open file\n");
    }
    #if  AVCIDAVN==0
    LOG_D("AVCIDAVN  0");
    #else
        LOG_D("read MD2 ");
    #endif
    return env->NewStringUTF(hello.c_str());
   // return env->NewStringUTF(buffer);
}
void writeMD2(){
    LOG_D("WRITE Md2");
    FILE* file = NULL;
    file = fopen("/data/data/com.rextron.jnireadfile/sku_id.txt","w");    //建立檔案
    if(file == NULL){        //容錯
        LOG_D("檔案建立失敗%s","fail");
    }
    fwrite("MD2",3,1,file);            //往檔案中寫檔案
    fclose(file);                    //關閉檔案
}

void writeAVN(){
    LOG_D("WRITE AVN");
    FILE* file = NULL;
    file = fopen("/data/data/com.rextron.jnireadfile/sku_id.txt","w");    //建立檔案
    if(file == NULL){        //容錯
        LOG_D("檔案建立失敗%s","fail");
    }
    fwrite("AVN",3,1,file);            //往檔案中寫檔案
    fclose(file);                    //關閉檔案
}

void writesystemAVN(){//need root
    LOG_D("WRITE system AVN");
    FILE* file = NULL;
    file = fopen("/system/sku_id.txt","w");    //建立檔案
    if(file == NULL){        //容錯
        LOG_D("檔案建立失敗%s","fail");
    }
    fwrite("AVN",3,1,file);            //往檔案中寫檔案
    fclose(file);                    //關閉檔案
}