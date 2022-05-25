#ifndef MOVIEPREVIEW_H
#define MOVIEPREVIEW_H

#include <QObject>
#include <QImage>
class MoviePreview : public QObject
{
    Q_OBJECT
public:
    static MoviePreview *instance();

    bool isFile(const QString & path);
    bool isVideo(const QString & path);
    QImage getMoviePreview(const QString &path);
    QImage getTextImage(const QString &path);
    bool ffmpegIsExist();
private :
    explicit MoviePreview(QObject *parent = nullptr);
    bool m_exitFFmpeg = false;
    static MoviePreview *m_moviePreview;
};

#endif // MOVIEPREVIEW_H
