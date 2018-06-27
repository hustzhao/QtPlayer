#include "videoplayer.h"
#include <QDebug>
#include <QImage>

#define SDL_MAIN_HANDLED



VideoPlayer::VideoPlayer()
{
}

void VideoPlayer::Init() {
  qDebug()<<"Init.";
  av_register_all();

  return;
}

void VideoPlayer::setFileName(QString filename) {
    filename_ = filename;
}

void VideoPlayer::run() {

  char file_path[1024 + 1] = {0};;
  strcpy(file_path,filename_.toUtf8().data());

  AVFormatContext *pFormatContext = avformat_alloc_context();
  if (!pFormatContext) {
    return;
  }

  if (avformat_open_input(&pFormatContext, file_path, NULL, NULL) != 0) {
    return;
  }

  if (avformat_find_stream_info(pFormatContext,  NULL) < 0) {
    return;
  }

  AVCodec *pCodec = NULL;
  AVCodecParameters *pCodecParameters =  NULL;
  int video_stream_index = -1;
  struct SwsContext *img_convert_ctx = NULL;
  AVFrame* pFrameRGB = NULL;
  uint8_t *out_buffer = NULL;
  int numBytes = 0;

  for (unsigned int i = 0; i < pFormatContext->nb_streams; i++) {
    AVCodecParameters *pLocalCodecParameters =  NULL;
    pLocalCodecParameters = pFormatContext->streams[i]->codecpar;
    AVCodec *pLocalCodec = NULL;

    pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);

    if (pLocalCodec==NULL) {
      return;
    }

    if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
      video_stream_index = i;
      pCodec = pLocalCodec;
      pCodecParameters = pLocalCodecParameters;

    } else if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO) {
      ;
    }

  }

  AVCodecContext *pCodecContext = avcodec_alloc_context3(pCodec);
  if (!pCodecContext)
  {
    return;
  }

  if (avcodec_parameters_to_context(pCodecContext, pCodecParameters) < 0)
  {
    return;
  }

  if (avcodec_open2(pCodecContext, pCodec, NULL) < 0)
  {
    return;
  }

  AVFrame *pFrame = av_frame_alloc();
  if (!pFrame)
  {
    return;
  }

  pFrameRGB = av_frame_alloc();

  img_convert_ctx = sws_getContext(pCodecContext->width, pCodecContext->height,
          pCodecContext->pix_fmt, pCodecContext->width, pCodecContext->height,
          AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);

  numBytes = avpicture_get_size(AV_PIX_FMT_RGB32,
                                pCodecContext->width,pCodecContext->height);


  out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));

  avpicture_fill((AVPicture *) pFrameRGB, out_buffer, AV_PIX_FMT_RGB32,
          pCodecContext->width, pCodecContext->height);

  AVPacket *pPacket = av_packet_alloc();
  if (!pPacket)
  {
    return;
  }

  int response = 0;

  while (av_read_frame(pFormatContext, pPacket) >= 0)
  {
    if (pPacket->stream_index == video_stream_index) {
      response = decode_packet(pPacket, pCodecContext, pFrame, pFrameRGB, out_buffer, img_convert_ctx);
      if (response < 0)
        break;
    }
    av_packet_unref(pPacket);
  }

  avformat_close_input(&pFormatContext);
  avformat_free_context(pFormatContext);
  av_packet_free(&pPacket);
  av_frame_free(&pFrame);
  avcodec_free_context(&pCodecContext);


}

void VideoPlayer::displayVideo(QImage image) {
  emit signalGetOneFrame(image);
}

int VideoPlayer::decode_packet(AVPacket *pPacket, AVCodecContext *pCodecContext,
                               AVFrame *pFrame, AVFrame *pFrameRGB, uint8_t *out_buffer, struct SwsContext *img_convert_ctx)
{
  int response = avcodec_send_packet(pCodecContext, pPacket);

  if (response < 0) {
    return response;
  }

  while (response >= 0)
  {
    response = avcodec_receive_frame(pCodecContext, pFrame);
    if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
      break;
    } else if (response < 0) {
      return response;
    }

    if (response >= 0) {
      sws_scale(img_convert_ctx,
              (uint8_t const * const *) pFrame->data,
              pFrame->linesize, 0, pCodecContext->height, pFrameRGB->data,
              pFrameRGB->linesize);

      QImage tmpImg((uchar *)out_buffer,pCodecContext->width,pCodecContext->height,QImage::Format_RGB32);
      QImage image = tmpImg.copy(); //把图像复制一份 传递给界面显示
      emit signalGetOneFrame(image);  //发送信号

      av_frame_unref(pFrame);
    }
  }

  return 0;
}

void VideoPlayer::SaveFrame(AVFrame *pFrame, int width, int height,int index)
{

  FILE *pFile;
  char szFilename[32];
  int  y;

  // Open file
  sprintf(szFilename, "frame%d.ppm", index);
  pFile=fopen(szFilename, "wb");

  if(pFile==NULL)
    return;

  // Write header
  fprintf(pFile, "P6 %d %d 255 ", width, height);

  // Write pixel data
  for(y=0; y<height; y++)
  {
    fwrite(pFrame->data[0]+y*pFrame->linesize[0], 1, width*3, pFile);
  }

  // Close file
  fclose(pFile);

}
