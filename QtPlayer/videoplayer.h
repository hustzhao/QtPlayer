#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QThread>
#include <QImage>
#include <QString>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "libavutil/pixfmt.h"
#include "libswscale/swscale.h"
#include <libavutil/imgutils.h>
}


class VideoPlayer : public QThread
{
   Q_OBJECT
public:
  VideoPlayer();
  void setFileName(QString filename);
protected:
  void run() override;

private:
  void displayVideo(QImage image);
  int decode_packet(AVPacket *pPacket, AVCodecContext *pCodecContext, AVFrame *pFrame, AVFrame *pFrameRGB, uint8_t *out_buffer, struct SwsContext *img_convert_ctx);
  QString filename_{};

signals:
  void signalGetOneFrame(QImage);
};

#endif // VIDEOPLAYER_H
