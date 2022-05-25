#include "moviepreview.h"
#include <QProcess>
#include <QDebug>
#include <QFileInfo>
#include <QPainter>

MoviePreview * MoviePreview::m_moviePreview = nullptr;


MoviePreview *MoviePreview::instance()
{
    if(!m_moviePreview){
        m_moviePreview=new MoviePreview();
    }
    return m_moviePreview;
}

bool MoviePreview::isFile(const QString &path)
{
    return QFileInfo(path).isFile();
}

bool MoviePreview::isVideo(const QString &path)
{
    const QStringList videoFiletypes = {"avs2", "3g2", "3ga", "3gp", "3gp2"
                                        , "3gpp", "amv", "asf", "asx", "avf", "avi", "bdm"
                                        , "bdmv", "bik", "clpi", "cpi", "dat", "divx", "drc"
                                        , "dv", "dvr-ms", "f4v", "flv", "gvi", "gxf", "hdmov"
                                        , "hlv", "iso", "letv", "lrv", "m1v", "m2p", "m2t"
                                        , "m2ts", "m2v", "m3u", "m3u8", "m4v", "mkv", "moov"
                                        , "mov", "mov", "mp2", "mp2v", "mp4", "mp4v", "mpe"
                                        , "mpeg", "mpeg1", "mpeg2", "mpeg4", "mpg", "mpl", "mpls"
                                        , "mpv", "mpv2", "mqv", "mts", "mts", "mtv", "mxf", "mxg"
                                        , "nsv", "nuv", "ogg", "ogm", "ogv", "ogx", "ps", "qt"
                                        , "qtvr", "ram", "rec", "rm", "rm", "rmj", "rmm", "rms"
                                        , "rmvb", "rmx", "rp", "rpl", "rv", "rvx", "thp", "tod"
                                        , "tp", "trp", "ts", "tts", "txd", "vcd", "vdr", "vob"
                                        , "vp8", "vro", "webm", "wm", "wmv", "wtv", "xesc", "xspf"
                                       };
    QFileInfo temDir(path);
    QString fileName = temDir.suffix().toLower();
    return videoFiletypes.contains(fileName);
}

QImage MoviePreview::getMoviePreview(const QString &path)
{
    QImage image =getTextImage(path);
    if (!m_exitFFmpeg) {
        return image;
    }

    QByteArray output;
    try {
        QProcess ffmpeg;
        QStringList cmds{"-nostats", "-loglevel", "0",
                         "-i", path,
                         "-f", "image2pipe",
                         "-vcodec", "png",
                         "-frames:v", "1",
                         "-vf","scale=256:144",
                         "-"};
        ffmpeg.start("ffmpeg", cmds, QIODevice::ReadOnly);
        if (!ffmpeg.waitForFinished(1000)) {
            qWarning() << ffmpeg.errorString();
            return image;
        }
        output = ffmpeg.readAllStandardOutput();
    } catch (std::logic_error &e) {
        qWarning() << e.what();
        return image;
    }

    if (!output.isNull()) {
        if (image.loadFromData(output, "png")) {
            return image;
        } else {
            QString processResult(output);
            processResult = processResult.split(QRegExp("[\n]"), QString::SkipEmptyParts).last();
            if (!processResult.isEmpty()) {
                if (image.loadFromData(processResult.toLocal8Bit().data(), "png")) {
                    return image;
                }
            }
        }
    }
    if(image.isNull()){
        image = getTextImage(path);
    }

    return image;
}

QImage MoviePreview::getTextImage(const QString &path)
{
    QString text;
    if (path.isEmpty()) {
        text = "ERROR!!";
    } else if (QFileInfo(path).isFile()) {
        text = QFileInfo(path).completeBaseName();
    } else {
        text = path;
    }
    QSize size(256, 144); //指定图片大小;
    QImage image(size, QImage::Format_ARGB32); //以ARGB32格式构造一个QImage,
    QPainter painter(&image); //为这个QImage构造一个QPainter
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    QPen pen = painter.pen();
    pen.setColor(Qt::red);
    QFont font = painter.font();
    font.setBold(true);//加粗
    font.setPixelSize(30);//改变字体大小
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(image.rect(), Qt::AlignCenter, text);

    return image;
}

bool MoviePreview::ffmpegIsExist()
{
    return m_exitFFmpeg;
}

MoviePreview::MoviePreview(QObject *parent)
 : QObject(parent)
{
    int reIndex= QProcess::execute("ffmpeg");
    if(reIndex>0){
        m_exitFFmpeg = true;
    }else {
        m_exitFFmpeg = false;
    }
}
