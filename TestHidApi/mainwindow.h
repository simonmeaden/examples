/*
  Copyright 2020 Simon Meaden

  Permission is hereby granted, free of charge, to any person obtaining a copy
                                                of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
                                                          copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

    @author: Simon Meaden

*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QByteArray>
#include <QFrame>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QTabWidget>
#include <QTableView>
#include <QThread>
#include <QTimer>

#include <qhidapi.h>
#include <qhiddeviceinfo.h>
#include <qhiddeviceinfomodel.h>
#include <qhiddeviceinfoview.h>
#include <hexformatdelegate.h>

struct udev;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

signals:

public slots:

protected slots:
  void udevData();
  void hidData();
  //    void udevMonitoring();
  void connectDevice();
  void disconnectDevice();
  void rescan(ushort mVendorId = 0x0, ushort mProductId = 0x0);
  int sendOutputReport();
  int sendFeatureReport();
  int getFeatureReport();
  void clear();
  void timeout();

protected:
  QHidApi* pHidApi;
  QList<QHidDeviceInfo> mDevices;
  QHidDeviceInfoModel mModel;
  QTableView* pInfoView;
  QPushButton* pConnectBtn, *pDisconnectBtn, *pSescanBtn, *pClearBtn,
               *pOutputBtn, *pFeatureBtn, *pGetFeatureBtn;
  QPlainTextEdit* pInputText /*, *udevMonitor*/;
  QLineEdit* pOutputTextEdit, *pFeatureTextEdit, *pGetFeatureTextEdit;
  QSpinBox* pOutputLenBox, *pFeatureLenBox, *pOutputIdBox, *pFeatureIdBox,
            *pGetFeatureIdBox;
  QLabel* pConnectedLbl;
  QTabWidget* pTabs, *pUdevTabs;

  quint32 mConnectedDevice;
  ushort mVendorId, mProductId, mReleaseNumber;
  QString mManufacturer, mProduct;
  QString mSerialNumber;

  void initBuild();
  QFrame* initInfoFrame();
  QFrame* initDataFrame();
  QFrame* initInputFrame();

private:
};

#endif // MAINWINDOW_H
