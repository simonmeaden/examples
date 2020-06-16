/**
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
*/
#ifndef TESTHEXSPINBOX_H
#define TESTHEXSPINBOX_H

#include <QCheckBox>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QSpinBox>
#include <QTabWidget>
#include <QIntValidator>
#include <QLineEdit>

#include <QtDebug>

#include <exspinbox.h>
#include <labelledwidgets.h>
#include <extabwidget.h>

class IntegerEdit : public QWidget
{
public:
  explicit IntegerEdit(QWidget* parent)
    : QWidget(parent) {
    QVBoxLayout l;
    setLayout(&l);
    m_editor = new QLineEdit(this);
    m_editor->setValidator(new QIntValidator(this));
    setValue(0);
  }

  QSize sizeHint() const override {
    return m_editor->sizeHint();
  }

  void setValue(int value) {
    m_editor->setText(QString::number(value));
  }
  int value() {
    return m_editor->text().toInt();
  }

private:
  QLineEdit* m_editor;
};

class TestSMWidgets : public QMainWindow
{
  Q_OBJECT
public:
  explicit TestSMWidgets(QWidget* parent = nullptr);

private:
  ExSpinBox* m_hexBox, *m_decBox, *m_binBox, *m_octBox;
  QLabel* m_hexLbl, *m_decLbl, *m_binLbl, *m_octLbl;
  QSpinBox* m_maxBox, *m_minBox;
  QRadioButton* m_hexBtn, *m_binaryBtn, *m_OctalBtn, *m_decimalBtn;
  QPushButton* m_setRangeBtn;
  QCheckBox* m_showLeadingZeroesBox;
  QRadioButton* m_uppercaseBtn, *m_lowercaseBtn;
  int m_max, m_min;
  IntegerEdit* m_valueEdit;

  LabelledSpinBox* m_labSpinBox;
  LabelledHexSpinBox* m_labHexSpinBox;
  LabelledComboBox* m_labComboBox;
  Qt::Alignment m_vAlign, m_hAlign;
  QRadioButton* leftBtn;
  QRadioButton* rightBtn;
  QRadioButton* hCentreBtn;
  QRadioButton* justifyBtn;
  QRadioButton* topBtn;
  QRadioButton* bottomBtn;
  QRadioButton* vCentreBtn;
  QRadioButton* baselineBtn;

  void initGui();
  // spin boxes
  QWidget* initSpinFrame();
  QWidget* initSpinBoxes();
  QWidget* initSpinMaxMin();
  //  QWidget* initSpinBoxType();
  QWidget* initSpinBoxStatus();
  // labelled widgets
  QWidget* initLabelledWidgetsFrame();

  // qhexspinbox stuff.
  void changeSpinBoxType(bool);
  void leadingZeroesChanged(bool);
  void caseChanged(bool);
  void setSpinBoxRangeAndValue();
  void checkMaxChanged(int value);
  void checkMinChanged(int value);
  void octChanged(int value);
  void hexChanged(int value);
  void decChanged(int value);
  void binChanged(int value);

  // labelledwidgets stuff.
  void labelPositionChanged(QString text);
  void labelHAlignChanged(bool);
  void labelVAlignChanged(bool);
  void setLabelAlignment();
};

#endif // TESTHEXSPINBOX_H
