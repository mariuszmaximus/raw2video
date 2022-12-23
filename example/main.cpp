#include <iostream>

#include <vector>
#include <string>

#include "raw2video.h"


int main(int, char**) 
{
    Raw2Video::Params params;
    params.width = 256;
    params.height = 256;
    params.fps = 10;
    params.bitrate = 1024*1024*64;
    params.preset = "medium";
    params.crf = 23;
    params.src_format = AV_PIX_FMT_BGRA;
    params.dst_format = AV_PIX_FMT_YUV420P;
    params.codec = AV_CODEC_ID_H264;

    // raw DATA MEMORY  
    std::vector<uint8_t> raw_RGBA (params.width * params.height * 4);

    auto fillRand=[&](Raw2Video &raw2video){
        for (int i=0; i<100; i++)
        {
            for(auto &one: raw_RGBA)
            {
                one = rand() % 256;	
            }
            raw2video.Write(raw_RGBA.data());
        }
        raw2video.Close();
    };

    Raw2Video file_H264_mp4("file_H264.mp4", params);
    fillRand(file_H264_mp4); 

    Raw2Video file_H264_mkv("file_H264.mkv", params);
    fillRand(file_H264_mkv); 
 
    Raw2Video file_H264_avi("file_H264.avi", params);
    fillRand(file_H264_avi); 

    params.codec = AV_CODEC_ID_H265;
    Raw2Video file_H265_avi("file_H265.avi", params);
    fillRand(file_H265_avi); 

    params.codec = AV_CODEC_ID_RAWVIDEO;
    Raw2Video file_RAWVIDEO_avi("file_RAWVIDEO.avi", params);
    fillRand(file_RAWVIDEO_avi); 




}
