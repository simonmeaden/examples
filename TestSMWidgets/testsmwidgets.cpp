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
#include "testsmwidgets.h"
#include <QApplication>
#include <Qt>

TestSMWidgets::TestSMWidgets(QWidget* parent)
  : QMainWindow(parent)
{
  initGui();

  m_max = m_hexBox->maximum();
  m_min = m_hexBox->minimum();

  m_maxBox->setValue(m_max);
  m_minBox->setValue(m_min);
}

QWidget* TestSMWidgets::initSpinFrame()
{
  QFrame* f = new QFrame(this);
  f->setFrameStyle(QFrame::StyledPanel);
  QGridLayout* l = new QGridLayout();
  f->setLayout(l);

  int row = 0;
  l->addWidget(initSpinBoxes(), row, 0);
  l->addWidget(initSpinMaxMin(), row, 1);

  row++;

  l->addWidget(initSpinBoxStatus(), row, 1);

  row++;

  return f;
}

QWidget* TestSMWidgets::initSpinBoxes()
{
  QGroupBox* f = new QGroupBox(tr("Spin Boxes"), this);
  QGridLayout* l = new QGridLayout();
  f->setLayout(l);

  int row = 0;

  QLabel* lbl = new QLabel(tr("Decimal :"), this);
  l->addWidget(lbl, row, 0);
  m_decBox = new ExSpinBox(ExSpinBox::Decimal, this);
  l->addWidget(m_decBox, row, 1);
  m_decLbl = new QLabel("0", this);
  l->addWidget(m_decLbl, row++, 2);
  connect(m_decBox, qOverload<int>(&ExSpinBox::valueChanged), this, &TestSMWidgets::decChanged);

  lbl = new QLabel(tr("Hexadecimal :"), this);
  l->addWidget(lbl, row, 0);
  m_hexBox = new ExSpinBox(ExSpinBox::Hexadecimal, this);
  l->addWidget(m_hexBox, row, 1);
  m_hexLbl = new QLabel("0", this);
  l->addWidget(m_hexLbl, row++, 2);
  connect(m_hexBox, qOverload<int>(&ExSpinBox::valueChanged), this, &TestSMWidgets::hexChanged);

  lbl = new QLabel(tr("Binary :"), this);
  l->addWidget(lbl, row, 0);
  m_binBox = new ExSpinBox(ExSpinBox::Binary, this);
  l->addWidget(m_binBox, row, 1);
  m_binLbl = new QLabel("0", this);
  l->addWidget(m_binLbl, row++, 2);
  connect(m_binBox, qOverload<int>(&ExSpinBox::valueChanged), this, &TestSMWidgets::binChanged);

  lbl = new QLabel(tr("Octal :"), this);
  l->addWidget(lbl, row, 0);
  m_octBox = new ExSpinBox(ExSpinBox::Octal, this);
  l->addWidget(m_octBox, row, 1);
  m_octLbl = new QLabel("0", this);
  l->addWidget(m_octLbl, row++, 2);
  connect(m_octBox, qOverload<int>(&ExSpinBox::valueChanged), this, &TestSMWidgets::octChanged);

  return f;
}

QWidget* TestSMWidgets::initSpinMaxMin()
{
  QGroupBox* f = new QGroupBox(tr("Values"), this);
  QGridLayout* l = new QGridLayout();
  f->setLayout(l);
  QLabel* lbl;

  int row = 0;

  lbl = new QLabel(tr("Value :"));
  l->addWidget(lbl, row, 0);

  m_valueEdit = new IntegerEdit(this);
  l->addWidget(m_valueEdit, row, 1);

  row++;

  lbl = new QLabel(tr("Max :"));
  l->addWidget(lbl, row, 0);

  m_maxBox = new QSpinBox(this);
  m_maxBox->setRange(-32768, 32767);
  connect(m_maxBox, qOverload<int>(&QSpinBox::valueChanged), this, &TestSMWidgets::checkMaxChanged);
  l->addWidget(m_maxBox, row, 1);

  row++;

  lbl = new QLabel(tr("Min :"));
  l->addWidget(lbl, row, 0);

  m_minBox = new QSpinBox(this);
  m_minBox->setRange(-32768, 32767);
  connect(m_minBox, qOverload<int>(&QSpinBox::valueChanged), this, &TestSMWidgets::checkMinChanged);
  l->addWidget(m_minBox, row, 1);

  row++;

  m_setRangeBtn = new QPushButton(tr("Set Range"));
  l->addWidget(m_setRangeBtn, row, 0, 1, 2);
  connect(m_setRangeBtn, &QPushButton::clicked, this, &TestSMWidgets::setSpinBoxRangeAndValue);

  row++;

  return f;

}

QWidget* TestSMWidgets::initSpinBoxStatus()
{
  QGroupBox* f = new QGroupBox(tr("Hex Setup"), this);
  QVBoxLayout* l = new QVBoxLayout();
  f->setLayout(l);

  m_showLeadingZeroesBox = new QCheckBox(tr("Show Leading Zeroes"), this);
  connect(m_showLeadingZeroesBox, &QCheckBox::stateChanged,
          this, &TestSMWidgets::leadingZeroesChanged);
  l->addWidget(m_showLeadingZeroesBox);

  QButtonGroup caseGrp;
  m_uppercaseBtn = new QRadioButton(tr("Digits in uppercase"), this);
  m_uppercaseBtn->setChecked(m_hexBox->charCase() == ExSpinBox::Uppercase);
  caseGrp.addButton(m_uppercaseBtn);
  connect(m_uppercaseBtn, &QRadioButton::clicked,
          this, &TestSMWidgets::caseChanged);
  l->addWidget(m_uppercaseBtn);

  m_lowercaseBtn = new QRadioButton(tr("Digits in lowercase"), this);
  m_lowercaseBtn->setChecked(m_hexBox->charCase() == ExSpinBox::Lowercase);
  caseGrp.addButton(m_lowercaseBtn);
  connect(m_lowercaseBtn, &QRadioButton::clicked,
          this, &TestSMWidgets::caseChanged);
  l->addWidget(m_lowercaseBtn);

  return f;
}

QWidget* TestSMWidgets::initLabelledWidgetsFrame()
{
  QFrame* f = new QFrame(this);
  f->setFrameStyle(QFrame::StyledPanel);
  QGridLayout* l = new QGridLayout();
  f->setLayout(l);

  int row = 0;

  QLabel* lbl = new QLabel(tr("Change Label Position"), this);
  l->addWidget(lbl, row, 0);

  QStringList labPosList;
  labPosList << tr("Left") << tr("Right");
  QComboBox* posBox = new QComboBox(this);
  posBox->addItems(labPosList);
  l->addWidget(posBox, row, 1);
  connect(posBox, &QComboBox::currentTextChanged, this, &TestSMWidgets::labelPositionChanged);
  posBox->setCurrentText(tr("Left"));

  row++;

  lbl = new QLabel(tr("Change Label Alignment"), this);
  l->addWidget(lbl, row, 0);

  row++;

  QGroupBox* hBox = new QGroupBox(tr("Horizontal:"), this);
  l->addWidget(hBox, row, 0);
  QButtonGroup* hGroup = new QButtonGroup(this);
  QVBoxLayout* hLayout = new QVBoxLayout();
  hBox->setLayout(hLayout);
  leftBtn = new QRadioButton(tr("Left"), this);
  leftBtn->setChecked(true);
  rightBtn = new QRadioButton(tr("Right"), this);
  hCentreBtn = new QRadioButton(tr("H Centre"), this);
  justifyBtn = new QRadioButton(tr("Justify"), this);
  hLayout->addWidget(leftBtn);
  hLayout->addWidget(rightBtn);
  hLayout->addWidget(hCentreBtn);
  hLayout->addWidget(justifyBtn);
  hGroup->addButton(leftBtn);
  hGroup->addButton(rightBtn);
  hGroup->addButton(hCentreBtn);
  hGroup->addButton(justifyBtn);
  hGroup->setExclusive(true);

  QGroupBox* vBox = new QGroupBox(tr("Vertical:"), this);
  l->addWidget(vBox, row, 1);
  QButtonGroup* vGroup = new QButtonGroup(this);
  QVBoxLayout* vLayout = new QVBoxLayout();
  vBox->setLayout(vLayout);
  topBtn = new QRadioButton(tr("Top"), this);
  topBtn->setChecked(true);
  bottomBtn = new QRadioButton(tr("Bottom"), this);
  vCentreBtn = new QRadioButton(tr("V Centre"), this);
  baselineBtn = new QRadioButton(tr("Baseline"), this);
  vLayout->addWidget(topBtn);
  vLayout->addWidget(bottomBtn);
  vLayout->addWidget(vCentreBtn);
  vLayout->addWidget(baselineBtn);
  vGroup->addButton(topBtn);
  vGroup->addButton(bottomBtn);
  vGroup->addButton(vCentreBtn);
  vGroup->addButton(baselineBtn);
  vGroup->setExclusive(true);

  connect(leftBtn, &QRadioButton::clicked, this, &TestSMWidgets::labelHAlignChanged);
  connect(rightBtn, &QRadioButton::clicked, this, &TestSMWidgets::labelHAlignChanged);
  connect(hCentreBtn, &QRadioButton::clicked, this, &TestSMWidgets::labelHAlignChanged);
  connect(justifyBtn, &QRadioButton::clicked, this, &TestSMWidgets::labelHAlignChanged);

  connect(topBtn, &QRadioButton::clicked, this, &TestSMWidgets::labelVAlignChanged);
  connect(bottomBtn, &QRadioButton::clicked, this, &TestSMWidgets::labelVAlignChanged);
  connect(vCentreBtn, &QRadioButton::clicked, this, &TestSMWidgets::labelVAlignChanged);
  connect(baselineBtn, &QRadioButton::clicked, this, &TestSMWidgets::labelVAlignChanged);

  row++;

  m_labSpinBox = new LabelledSpinBox(tr("Spin Box"), this);
  l->addWidget(m_labSpinBox, row, 0, 1, 2);

  row++;

  m_labHexSpinBox = new LabelledHexSpinBox(tr("Hex Spin Box"), this);
  l->addWidget(m_labHexSpinBox, row, 0, 1, 2);

  row++;

  m_labComboBox = new LabelledComboBox(tr("Combo Box"), this);
  l->addWidget(m_labComboBox, row, 0, 1, 2);

  return f;
}

void TestSMWidgets::initGui()
{
  QTabWidget* tabs = new QTabWidget(this);
  setCentralWidget(tabs);

  tabs->addTab(initSpinFrame(), tr("Spin Boxes"));
  tabs->addTab(initLabelledWidgetsFrame(), tr("Labelled Widgets"));
}

void TestSMWidgets::changeSpinBoxType(bool)
{
  if (m_hexBtn->isChecked()) {
    m_hexBox->setDisplayType(ExSpinBox::Hexadecimal);
    //    m_maxBox->setType(ExSpinBox::Hexadecimal);
    //    m_minBox->setType(ExSpinBox::Hexadecimal);
    m_minBox->setRange(-32768, 32767);
    m_maxBox->setRange(-32768, 32767);

  } else if (m_binaryBtn->isChecked()) {
    m_hexBox->setDisplayType(ExSpinBox::Binary);
    //    m_maxBox->setType(ExSpinBox::Binary);
    //    m_minBox->setType(ExSpinBox::Binary);
    m_minBox->setRange(-0xFF, 0xFF);
    m_maxBox->setRange(-0xFF, 0xFF);

  } else if (m_OctalBtn->isChecked()) {
    m_hexBox->setDisplayType(ExSpinBox::Octal);
    //    m_maxBox->setType(ExSpinBox::Octal);
    //    m_minBox->setType(ExSpinBox::Octal);
    m_minBox->setRange(-0xFFFF, 0xFFFF);
    m_maxBox->setRange(-0xFFFF, 0xFFFF);

  } else if (m_decimalBtn->isChecked()) {
    m_hexBox->setDisplayType(ExSpinBox::Decimal);
    //    m_maxBox->setType(ExSpinBox::Decimal);
    //    m_minBox->setType(ExSpinBox::Decimal);
    m_minBox->setRange(-1000, 1000);
    m_maxBox->setRange(-1000, 1000);
  }
}

void TestSMWidgets::leadingZeroesChanged(bool)
{
  m_hexBox->setShowLeadingZeroes(m_showLeadingZeroesBox->isChecked());
  m_octBox->setShowLeadingZeroes(m_showLeadingZeroesBox->isChecked());
  m_binBox->setShowLeadingZeroes(m_showLeadingZeroesBox->isChecked());
}

void TestSMWidgets::caseChanged(bool)
{
  if (m_uppercaseBtn->isChecked()) {
    m_hexBox->setCharCase(ExSpinBox::Uppercase);
    //    m_minBox->setCharCase(ExSpinBox::Uppercase);
    //    m_maxBox->setCharCase(ExSpinBox::Uppercase);

  } else if (m_lowercaseBtn->isChecked()) {
    m_hexBox->setCharCase(ExSpinBox::Lowercase);
    //    m_minBox->setCharCase(ExSpinBox::Lowercase);
    //    m_maxBox->setCharCase(ExSpinBox::Lowercase);

  }
}

void TestSMWidgets::setSpinBoxRangeAndValue()
{
  int max = m_maxBox->value();
  int min = m_minBox->value();
  int value = m_valueEdit->value();

  m_decBox->setRange(min, max);
  m_decBox->setValue(value);

  m_hexBox->setRange(min, max);
  m_hexBox->setValue(value);

  m_binBox->setRange(min, max);
  m_binBox->setValue(value);

  m_octBox->setRange(min, max);
  m_octBox->setValue(value);
}

void TestSMWidgets::checkMaxChanged(int value)
{
  // stops max decreasing to min
  if (value == m_min) {
    m_maxBox->setValue(m_max);

  } else {
    m_max = value;
  }
}

void TestSMWidgets::checkMinChanged(int value)
{
  // Stops min increasing to max
  if (value == m_max) {
    m_minBox->setValue(m_min);

  } else {
    m_min = value;
  }
}

void TestSMWidgets::octChanged(int value)
{
  m_octLbl->setText(QString::number(value));
}

void TestSMWidgets::hexChanged(int value)
{
  m_hexLbl->setText(QString::number(value));
}

void TestSMWidgets::decChanged(int value)
{
  m_decLbl->setText(QString::number(value));
}

void TestSMWidgets::binChanged(int value)
{
  m_octLbl->setText(QString::number(value));
}

void TestSMWidgets::labelPositionChanged(QString text)
{
  if (text == tr("Left")) {
    m_labSpinBox->setPosition(AbstractLabelledWidget::Left);
    m_labHexSpinBox->setPosition(AbstractLabelledWidget::Left);
    m_labComboBox->setPosition(AbstractLabelledWidget::Left);

  } else if (text == tr("Right")) {
    m_labSpinBox->setPosition(AbstractLabelledWidget::Right);
    m_labHexSpinBox->setPosition(AbstractLabelledWidget::Right);
    m_labComboBox->setPosition(AbstractLabelledWidget::Right);
  }
}

void TestSMWidgets::setLabelAlignment()
{
  m_labSpinBox->setAlignment(m_hAlign | m_vAlign);
  m_labHexSpinBox->setAlignment(m_hAlign | m_vAlign);
  m_labComboBox->setAlignment(m_hAlign | m_vAlign);
}

void TestSMWidgets::labelHAlignChanged(bool)
{
  QObject* button = sender();

  if (button == leftBtn) {
    m_hAlign = Qt::AlignLeft;

  } else if (button == rightBtn) {
    m_hAlign = Qt::AlignRight;

  } else if (button == hCentreBtn) {
    m_hAlign = Qt::AlignHCenter;

  } else if (button == justifyBtn) {
    m_hAlign = Qt::AlignJustify;
  }

  setLabelAlignment();
}

void TestSMWidgets::labelVAlignChanged(bool)
{
  QObject* button = sender();

  if (button == topBtn) {
    m_vAlign = Qt::AlignTop;

  } else if (button == bottomBtn) {
    m_vAlign = Qt::AlignBottom;

  } else if (button == vCentreBtn) {
    m_vAlign = Qt::AlignVCenter;

  } else if (button == baselineBtn) {
    m_vAlign = Qt::AlignBaseline;
  }

  setLabelAlignment();
}

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  TestSMWidgets w;
  w.show();

  return a.exec();
}
