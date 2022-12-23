
#include <stdint.h>
extern "C"
{
#include <libavutil\pixfmt.h>			// AVPixelFormat
#include <libavcodec\codec_id.h>		// AVCodecID
}
// presets:
//
// ultrafast
// superfast
// veryfast
// faster
// fast
// medium – default preset
// slow
// slower
// veryslow

// CRF
// What is the Constant Rate Factor?
// The Constant Rate Factor (CRF) is the default quality (and rate control) setting for the x264 and x265 encoders, 
// and it’s also available for libvpx. With x264 and x265, you can set the values between 0 and 51, 
// where lower values would result in better quality, at the expense of higher file sizes. 
// Higher values mean more compression, but at some point you will notice the quality degradation.
// For x264, sane values are between 18 and 28. The default is 23, so you can use this as a starting point.

class Raw2Video
{
public:
	struct Params
	{
		uint32_t width;
		uint32_t height;
		double fps;
		uint32_t bitrate;
		const char *preset;

		uint32_t crf; //0–51

		enum AVPixelFormat src_format;
		enum AVPixelFormat dst_format;
		AVCodecID codec;
	};

	Raw2Video() = default;
	Raw2Video(const char *filename, const Params &params);
	~Raw2Video();

	bool Open(const char *filename, const Params &params);

	void Close();

	bool Write(const unsigned char *data);

	bool IsOpen() const;

private:
	bool FlushPackets();

private:
	bool mIsOpen = false;

	struct Context
	{
		struct AVFormatContext *format_context = nullptr;
		struct AVStream *stream = nullptr;
		struct AVCodecContext *codec_context = nullptr;
		struct AVFrame *frame = nullptr;
		struct SwsContext *sws_context = nullptr;
		struct AVCodec *codec = nullptr;
		
		uint32_t frame_index = 0;
	};

	Context mContext = {};
};