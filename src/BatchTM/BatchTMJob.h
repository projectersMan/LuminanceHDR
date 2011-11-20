/**
 * This file is a part of LuminanceHDR package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2011 Davide Anastasia
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ----------------------------------------------------------------------
 *
 * Original Work
 * @author Davide Anastasia <davideanastasia@users.sourceforge.net>
 * This class splits the "Batch Tonemapping core" from the UI, to achieve a simpler
 * code, faster, easier to maintain and more clear to read
 *
 */

#ifndef __BATCH_TM_JOB__
#define __BATCH_TM_JOB__

#include <QThread>
#include <QMutex>
#include <QImage>

// Forward declaration
namespace pfs {
    class Frame;
}

class TonemappingOptions;

class BatchTMJob : public QThread {
  Q_OBJECT
public:
    BatchTMJob(int thread_id, QString filename, const QList<TonemappingOptions*>* tm_options, QString output_folder);
    virtual ~BatchTMJob();
signals:
    void done(int thread_id);
  void add_log_message(QString);
  //void update_progress_bar();
  void increment_progress_bar(int);
protected:
    void run();
private slots:
  void tm_failed();
  void tm_completed(QImage* newimage, quint16* newpixmap, const TonemappingOptions* opts);

private:
  int             m_thread_id;
  QString         m_file_name;
  const QList<TonemappingOptions*>* m_tm_options;
  QString         m_output_folder;
  QString         m_output_file_name_base;
  QString         m_ldr_output_format;
  
  //LoadHdrThread * m_load_thread;
  pfs::Frame    * m_working_frame;
  //TMOThread     * m_tmo_thread;
  QImage        * m_ldr_image;
  const quint16	* m_pixmap;
};

#endif // __BATCH_TM_JOB__
