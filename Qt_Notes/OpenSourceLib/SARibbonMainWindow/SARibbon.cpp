//����˺꣬��SA_RIBBON_EXPORT����Ϊ��
#ifndef SA_RIBBON_BAR_NO_EXPORT
#define SA_RIBBON_BAR_NO_EXPORT
#endif
//����˺꣬��SA_COLOR_WIDGETS_API����Ϊ��
#ifndef SA_COLOR_WIDGETS_NO_DLL
#define SA_COLOR_WIDGETS_NO_DLL
#endif

/*** Start of inlined file: SARibbonAmalgamTemplateHeaderGlue.h ***/
// This file provides an extra level of indirection for the @remap in the template
#include "SARibbon.h"

/*** End of inlined file: SARibbonAmalgamTemplateHeaderGlue.h ***/

// disable warnings about unsafe standard library calls
#ifdef _MSC_VER
#pragma push_macro("_CRT_SECURE_NO_WARNINGS")
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma warning(push)
#pragma warning(disable : 4996)  // deprecated POSIX names
#endif

/*** Start of inlined file: SAColorMenu.cpp ***/
#include <QWidgetAction>
#include <QColorDialog>
#include <QDebug>
#include <QLabel>
#include <QGridLayout>
#include <QPainter>

class SAColorMenu::PrivateData
{
    SA_COLOR_WIDGETS_DECLARE_PUBLIC(SAColorMenu)
public:
    PrivateData(SAColorMenu* p);
    QColor getColorByDialog();
    void recordCustomColor(const QColor& c);
    QWidgetAction* addWidget(QWidget* w);
    //����һ������ɫ��icon
    QIcon createNoneColorIcon(QSize baseSize = QSize(32, 32));

public:
    QLabel* mTitleLabel { nullptr };  ///< ������ɫ����
    QWidgetAction* mTitleLabelAction { nullptr };
    SAColorPaletteGridWidget* mThemeColorsWidget { nullptr };  ///< ������ɫ
    QWidgetAction* mThemeColorPaletteAction { nullptr };       ///< ThemeColorsPalette��Ӧ��action
    QAction* mCustomColorAction { nullptr };                   ///< �Զ�����ɫaction
    SAColorGridWidget* mCustomColorsWidget { nullptr };        ///< �Զ�����ɫ��¼
    QWidgetAction* mCustomColorsWidgetAction { nullptr };      ///< �Զ�����ɫ���ڶ�Ӧ��action
    QAction* mNoneColorAction { nullptr };                     ///< ����ɫaction
    QList< QColor > mCustomColors;
    int mMaxCustomColorSize { 10 };                        ///< ��¼�����Զ�����ɫ����
    QScopedPointer< QColorDialog > mColorDlg { nullptr };  ///<��ɫ�Ի���
};

SAColorMenu::PrivateData::PrivateData(SAColorMenu* p) : q_ptr(p)
{
}

QColor SAColorMenu::PrivateData::getColorByDialog()
{
    if (nullptr == mColorDlg) {
        mColorDlg.reset(new QColorDialog());
    }
    if (QDialog::Accepted == mColorDlg->exec()) {
        return mColorDlg->currentColor();
    }
    return QColor();
}

void SAColorMenu::PrivateData::recordCustomColor(const QColor& c)
{
    if (mCustomColors.size() < mMaxCustomColorSize) {
        mCustomColors.push_back(c);
    } else {
        //���������������ƶ�
        for (int i = 1; i < mCustomColors.size(); ++i) {
            mCustomColors[ i - 1 ] = mCustomColors[ i ];
        }
        mCustomColors.back() = c;
    }
}

QWidgetAction* SAColorMenu::PrivateData::addWidget(QWidget* w)
{
    QWidgetAction* wa = new QWidgetAction(q_ptr);
    wa->setDefaultWidget(w);
    q_ptr->addAction(wa);
    return wa;
}

QIcon SAColorMenu::PrivateData::createNoneColorIcon(QSize baseSize)
{
    QPixmap pixmap(baseSize);
    pixmap.fill(Qt::transparent);
    QPainter p(&pixmap);
    SAColorToolButton::paintNoneColor(&p, QRect(0, 0, pixmap.width(), pixmap.height()).adjusted(1, 1, -1, -1));
    return QIcon(pixmap);
}
//===================================================
// SAColorMenu
//===================================================

SAColorMenu::SAColorMenu(QWidget* parent) : QMenu(parent), d_ptr(new SAColorMenu::PrivateData(this))
{
    init(SA::getStandardColorList());
}

SAColorMenu::SAColorMenu(const QString& title, QWidget* parent)
    : QMenu(title, parent), d_ptr(new SAColorMenu::PrivateData(this))
{
    init(SA::getStandardColorList());
}

SAColorMenu::~SAColorMenu()
{
}

/**
 * @brief ���ٰ�ColorToolButton
 * @param btn
 */
void SAColorMenu::bindToColorToolButton(SAColorToolButton* btn)
{
    if (!btn) {
        return;
    }
    if (btn->menu() != this) {
        btn->setMenu(this);
    }
    connect(this, &SAColorMenu::selectedColor, btn, &SAColorToolButton::setColor);
}

/**
 * @brief ThemeColorsPalette��Ӧ��action
 * @return
 */
QWidgetAction* SAColorMenu::getThemeColorsPaletteAction() const
{
    return d_ptr->mThemeColorPaletteAction;
}

/**
 * @brief CustomColorsWidget��Ӧ��action
 * @return
 */
QWidgetAction* SAColorMenu::getCustomColorsWidgetAction() const
{
    return d_ptr->mCustomColorsWidgetAction;
}

/**
 * @brief �Զ�����ɫaction
 * @return
 */
QAction* SAColorMenu::getCustomColorAction() const
{
    return d_ptr->mCustomColorAction;
}

/**
 * @brief ��ȡThemeColorsPalette
 * @return
 */
SAColorPaletteGridWidget* SAColorMenu::getColorPaletteGridWidget() const
{
    return d_ptr->mThemeColorsWidget;
}

/**
 * @brief ��ȡ�Զ�����ɫgrid
 * @return
 */
SAColorGridWidget* SAColorMenu::getCustomColorsWidget() const
{
    return d_ptr->mCustomColorsWidget;
}

/**
 * @brief ����û����ɫ��action������ѡ������ɫ
 *
 * ����ɫѡ�лᷢ��selectedColor(QColor())
 * @param on
 */
void SAColorMenu::enableNoneColorAction(bool on)
{
    //����ɫĬ�������Զ�����ɫ���Ϸ�
    if (on) {
        if (d_ptr->mNoneColorAction) {
            if (actions().contains(d_ptr->mNoneColorAction)) {
                //�Ѿ�������NoneColorAction,�˳�
                return;
            } else {
                insertAction(d_ptr->mCustomColorAction, d_ptr->mNoneColorAction);
            }
        } else {
            QIcon ic                = d_ptr->createNoneColorIcon();
            d_ptr->mNoneColorAction = new QAction(ic, tr("None"), this);
            connect(d_ptr->mNoneColorAction, &QAction::triggered, this, &SAColorMenu::onNoneColorActionTriggered);
            insertAction(d_ptr->mCustomColorAction, d_ptr->mNoneColorAction);
        }
    } else {
        removeAction(d_ptr->mNoneColorAction);
        // remove����ʱ��ɾ��action
    }
}

/**
 * @brief ��ȡNone Color Action
 *
 * @note ע�⣬enableNoneColorAction(true),֮��Ų���nullptr
 * @return ���û�н���NoneColorAction���᷵��nullptr
 */
QAction* SAColorMenu::getNoneColorAction() const
{
    return d_ptr->mNoneColorAction;
}

/**
 * @brief ����һ�������ۺ�����Ϊ�����û��Զ��������actionҲ�ܹ���menu�����Ե��ô˲ۺ�����ʵ��selectedColor�ź��Լ�menu������
 * @param c
 */
void SAColorMenu::emitSelectedColor(const QColor& c)
{
    emit selectedColor(c);
    hide();
}

void SAColorMenu::init(const QList< QColor >& themeCls)
{
    d_ptr->mTitleLabel = new QLabel(this);
    d_ptr->mTitleLabel->setText(tr("Theme Colors"));
    d_ptr->mTitleLabelAction = d_ptr->addWidget(d_ptr->mTitleLabel);

    d_ptr->mThemeColorsWidget = new SAColorPaletteGridWidget(themeCls, this);
    d_ptr->mThemeColorsWidget->setColorCheckable(false);
    d_ptr->mThemeColorPaletteAction = d_ptr->addWidget(d_ptr->mThemeColorsWidget);

    d_ptr->mCustomColorAction = new QAction(tr("Custom Color"), this);  // cn:�Զ�����ɫ
    addAction(d_ptr->mCustomColorAction);

    QSize clrSize              = d_ptr->mThemeColorsWidget->getColorIconSize();
    d_ptr->mCustomColorsWidget = new SAColorGridWidget(this);
    d_ptr->mCustomColorsWidget->setRowMinimumHeight(0, clrSize.height());
    d_ptr->mCustomColorsWidget->setHorizontalSpacerToRight();
    d_ptr->mCustomColorsWidget->setColorIconSize(clrSize);
    d_ptr->mCustomColorsWidget->setColumnCount(d_ptr->mMaxCustomColorSize);
    d_ptr->mCustomColorsWidget->setColorCheckable(false);
    d_ptr->mCustomColorsWidgetAction = d_ptr->addWidget(d_ptr->mCustomColorsWidget);

    connect(d_ptr->mCustomColorAction, &QAction::triggered, this, &SAColorMenu::onCustomColorActionTriggered);
    connect(d_ptr->mThemeColorsWidget, &SAColorPaletteGridWidget::colorClicked, this, &SAColorMenu::emitSelectedColor);
    connect(d_ptr->mCustomColorsWidget, &SAColorGridWidget::colorClicked, this, &SAColorMenu::emitSelectedColor);
}

/**
 * @brief �Զ�����ɫ
 * @param on
 */
void SAColorMenu::onCustomColorActionTriggered(bool on)
{
    Q_UNUSED(on);
    QColor c = d_ptr->getColorByDialog();
    if (c.isValid()) {
        d_ptr->recordCustomColor(c);
        d_ptr->mCustomColorsWidget->setColorList(d_ptr->mCustomColors);
        updateGeometry();
        emitSelectedColor(c);
    }
}

/**
 * @brief ����ɫ
 * @param on
 */
void SAColorMenu::onNoneColorActionTriggered(bool on)
{
    Q_UNUSED(on);
    emitSelectedColor(QColor());
}

/*** End of inlined file: SAColorMenu.cpp ***/

/*** Start of inlined file: SAColorGridWidget.cpp ***/
#include <QGridLayout>
#include <cmath>
#include <QButtonGroup>

class SAColorGridWidget::PrivateData
{
    SA_COLOR_WIDGETS_DECLARE_PUBLIC(SAColorGridWidget)
public:
    PrivateData(SAColorGridWidget* p);
    //��ȡColorToolButton
    SAColorToolButton* getColorToolButtonAt(int index);
    SAColorToolButton* getColorToolButtonAt(int r, int c);
    SAColorToolButton* getCheckedButton() const;
    void updateGridColor(bool isRemoveSpacer = false);
    void updateGridColorSize();
    void updateGridColorCheckable();
    void iterationColorBtns(SAColorGridWidget::FunColorBtn fn);
    void removeAt(int r, int c);
    void setColorAt(const QColor& clr, int r, int c);
    bool isSpacer(int r, int c) const;

public:
    QList< QColor > mColors;
    QGridLayout* mGridLayout { nullptr };
    QButtonGroup* mButtonGroup { nullptr };
    QSize mIconSize { 16, 16 };
    int mColumnCount { 8 };  ///< �������������������������ƥ��,�������-1����0��˵�����޶���������������ֻ��һ��
    bool mColorCheckable;    ///<������ɫ�Ƿ���checkable
    bool mHorizontalSpacerToRight { false };  ///< ���ұ��Ƿ��е���
};

SAColorGridWidget::PrivateData::PrivateData(SAColorGridWidget* p) : q_ptr(p)
{
    mGridLayout = new QGridLayout(p);
    p->setLayout(mGridLayout);
    mGridLayout->setSpacing(0);
    mGridLayout->setContentsMargins(1, 1, 1, 1);
    mButtonGroup = new QButtonGroup(p);
    mButtonGroup->setExclusive(true);
    p->setMinimumHeight(mIconSize.height());
    p->setMinimumWidth(mIconSize.width());
}

SAColorToolButton* SAColorGridWidget::PrivateData::getColorToolButtonAt(int index)
{
    QLayoutItem* item = mGridLayout->itemAt(index);
    if (nullptr == item) {
        return nullptr;
    }
    return qobject_cast< SAColorToolButton* >(item->widget());
}

SAColorToolButton* SAColorGridWidget::PrivateData::getColorToolButtonAt(int r, int c)
{
    QLayoutItem* item = mGridLayout->itemAtPosition(r, c);
    if (nullptr == item) {
        return nullptr;
    }
    return qobject_cast< SAColorToolButton* >(item->widget());
}

SAColorToolButton* SAColorGridWidget::PrivateData::getCheckedButton() const
{
    return qobject_cast< SAColorToolButton* >(mButtonGroup->checkedButton());
}

/**
 * @brief ����mColors���²���
 */
void SAColorGridWidget::PrivateData::updateGridColor(bool isRemoveSpacer)
{
    int row = 1;
    int col = mColumnCount;
    if (col <= 0) {
        col = mColors.size();
    } else {
        row = std::ceil(mColors.size() / (float)col);
    }
    int index = 0;
    for (int r = 0; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            if (index < mColors.size()) {
                setColorAt(mColors[ index ], r, c);
                ++index;
            } else {
                removeAt(r, c);
            }
        }
    }
    //������൥Ԫ��
    int nowGridRow = mGridLayout->rowCount();
    int nowGridCol = mGridLayout->columnCount();
    if (nowGridRow > row) {
        //��������
        for (int r = row; r < nowGridRow; ++r) {
            for (int c = 0; c < nowGridCol; ++c) {
                removeAt(r, c);
            }
        }
    }
    if (nowGridCol > col) {
        //����������
        for (int r = 0; r < row; ++r) {
            for (int c = col; c < nowGridCol; ++c) {
                if (isRemoveSpacer) {
                    removeAt(r, c);
                } else {
                    if (!isSpacer(r, c)) {
                        removeAt(r, c);
                    }
                }
            }
        }
    }
}

/**
 * @brief ����colorsize
 */
void SAColorGridWidget::PrivateData::updateGridColorSize()
{
    QSize s = mIconSize;
    iterationColorBtns([ s ](SAColorToolButton* btn) {
        if (btn) {
            btn->setIconSize(s);
        }
    });
}

void SAColorGridWidget::PrivateData::updateGridColorCheckable()
{
    bool v = mColorCheckable;
    iterationColorBtns([ v ](SAColorToolButton* btn) {
        if (btn) {
            btn->setCheckable(v);
        }
    });
}

/**
 * @brief �������е�button
 * @param fn
 */
void SAColorGridWidget::PrivateData::iterationColorBtns(FunColorBtn fn)
{
    int cnt = mGridLayout->count();
    for (int i = 0; i < cnt; ++i) {
        SAColorToolButton* tl = getColorToolButtonAt(i);
        fn(tl);
    }
}

/**
 * @brief ɾ�����񴰿�
 * @param r
 * @param c
 */
void SAColorGridWidget::PrivateData::removeAt(int r, int c)
{
    QLayoutItem* item = mGridLayout->itemAtPosition(r, c);
    if (item) {
        QWidget* w = item->widget();
        mGridLayout->removeItem(item);
        delete item;
        if (w) {
            w->deleteLater();
        }
    }
}

void SAColorGridWidget::PrivateData::setColorAt(const QColor& clr, int r, int c)
{
    QLayoutItem* item = mGridLayout->itemAtPosition(r, c);
    if (item) {
        SAColorToolButton* tl = qobject_cast< SAColorToolButton* >(item->widget());
        if (tl) {
            tl->setColor(clr);
        }
    } else {
        SAColorToolButton* tl = new SAColorToolButton(q_ptr);
        tl->setToolButtonStyle(Qt::ToolButtonIconOnly);
        tl->setIconSize(mIconSize);
        tl->setMargins(QMargins(4, 4, 4, 4));
        tl->setColor(clr);
        tl->setCheckable(mColorCheckable);
        tl->setAutoRaise(true);
        mButtonGroup->addButton(tl, r + c);
        mGridLayout->addWidget(tl, r, c);
    }
}

bool SAColorGridWidget::PrivateData::isSpacer(int r, int c) const
{
    QLayoutItem* item = mGridLayout->itemAtPosition(r, c);
    if (item) {
        if (QSpacerItem* si = dynamic_cast< QSpacerItem* >(item)) {
            return true;
        }
    }
    return false;
}

//==============================================================
// SAColorGridWidget
//==============================================================

SAColorGridWidget::SAColorGridWidget(QWidget* par) : QWidget(par), d_ptr(new SAColorGridWidget::PrivateData(this))
{
    connect(d_ptr->mButtonGroup, QOverload< QAbstractButton* >::of(&QButtonGroup::buttonClicked), this, &SAColorGridWidget::onButtonClicked);
    connect(d_ptr->mButtonGroup, QOverload< QAbstractButton* >::of(&QButtonGroup::buttonPressed), this, &SAColorGridWidget::onButtonPressed);
    connect(d_ptr->mButtonGroup, QOverload< QAbstractButton* >::of(&QButtonGroup::buttonReleased), this, &SAColorGridWidget::onButtonReleased);
    connect(d_ptr->mButtonGroup, QOverload< QAbstractButton*, bool >::of(&QButtonGroup::buttonToggled), this, &SAColorGridWidget::onButtonToggled);
}

SAColorGridWidget::~SAColorGridWidget()
{
}

/**
 * @brief �����������������������������ƥ��,�������-1����0��˵�����޶���������������ֻ��һ��
 * @param c
 */
void SAColorGridWidget::setColumnCount(int c)
{
    d_ptr->mColumnCount = c;
    d_ptr->updateGridColor(true);
    if (d_ptr->mHorizontalSpacerToRight) {
        setHorizontalSpacerToRight();
    }
    updateGeometry();
}

/**
 * @brief ������ɫ�б�
 * @param c
 */
void SAColorGridWidget::setColorList(const QList< QColor >& cls)
{
    d_ptr->mColors = cls;
    d_ptr->updateGridColor();
    updateGeometry();
}

/**
 * @brief ��ȡ��ɫ�б�
 * @return
 */
QList< QColor > SAColorGridWidget::getColorList() const
{
    return d_ptr->mColors;
}

/**
 * @brief ��ȡ���
 * @return
 */
int SAColorGridWidget::getSpacing() const
{
    return d_ptr->mGridLayout->spacing();
}

/**
 * @brief ���ü��
 * @param v
 */
void SAColorGridWidget::setSpacing(int v)
{
    d_ptr->mGridLayout->setSpacing(v);
}

/**
 * @brief ��ȡ��ɫ������
 * @return
 */
int SAColorGridWidget::getColorCount() const
{
    return d_ptr->mColors.size();
}

/**
 * @brief ����ͼ�� size
 * @return
 */
void SAColorGridWidget::setColorIconSize(const QSize& s)
{
    d_ptr->mIconSize = s;
    setMinimumHeight(s.height());
    setMinimumWidth(s.width());
    d_ptr->updateGridColorSize();
}

/**
 * @brief ��ȡͼ�� size
 * @return
 */
QSize SAColorGridWidget::getColorIconSize() const
{
    return d_ptr->mIconSize;
}

/**
 * @brief ������ɫ�Ƿ���checkable
 *
 * checkable����ɫ��ť�ǿ�checked��
 * @param on
 */
void SAColorGridWidget::setColorCheckable(bool on)
{
    d_ptr->mColorCheckable = on;
    d_ptr->updateGridColorCheckable();
}

/**
 * @brief ��ɫ�Ƿ���checkable
 * @return
 */
bool SAColorGridWidget::isColorCheckable() const
{
    return d_ptr->mColorCheckable;
}

/**
 * @brief ��ȡ��ǰѡ�е���ɫ
 * @return
 */
QColor SAColorGridWidget::getCurrentCheckedColor() const
{
    QAbstractButton* btn = d_ptr->mButtonGroup->checkedButton();
    if (nullptr == btn) {
        return QColor();
    }
    SAColorToolButton* t = qobject_cast< SAColorToolButton* >(btn);
    if (nullptr == t) {
        return QColor();
    }
    return t->getColor();
}

/**
 * @brief ��ȡindex��Ӧ��colorbutton
 * @param index
 * @return ���û�з���nullptr
 */
SAColorToolButton* SAColorGridWidget::getColorButton(int index) const
{
    return d_ptr->getColorToolButtonAt(index);
}

/**
 * @brief ��ͬGridLayout��VerticalSpacing����
 * @param v
 */
void SAColorGridWidget::setVerticalSpacing(int v)
{
    d_ptr->mGridLayout->setVerticalSpacing(v);
}
/**
 * @brief ��ͬGridLayout��VerticalSpacing����
 * @return
 */
int SAColorGridWidget::getVerticalSpacing() const
{
    return d_ptr->mGridLayout->verticalSpacing();
}
/**
 * @brief ��ͬGridLayout��HorizontalSpacing����
 * @param v
 */
void SAColorGridWidget::setHorizontalSpacing(int v)
{
    d_ptr->mGridLayout->setHorizontalSpacing(v);
}
/**
 * @brief ��ͬGridLayout��HorizontalSpacing����
 * @return
 */
int SAColorGridWidget::getHorizontalSpacing() const
{
    return d_ptr->mGridLayout->horizontalSpacing();
}

/**
 * @brief ���ѡ��״̬����ʱû����ɫ��ѡ�е�
 */
void SAColorGridWidget::clearCheckedState()
{
    if (d_ptr->mButtonGroup->exclusive()) {
        SAColorToolButton* btn = d_ptr->getCheckedButton();
        if (btn) {
            d_ptr->mButtonGroup->setExclusive(false);
            btn->setChecked(false);
            d_ptr->mButtonGroup->setExclusive(true);
        }
    } else {
        d_ptr->iterationColorBtns([](SAColorToolButton* btn) {
            if (btn->isChecked()) {
                btn->setChecked(false);
            }
        });
    }
}

void SAColorGridWidget::iterationColorBtns(SAColorGridWidget::FunColorBtn fn)
{
    d_ptr->iterationColorBtns(fn);
}

void SAColorGridWidget::setRowMinimumHeight(int row, int minSize)
{
    d_ptr->mGridLayout->setRowMinimumHeight(row, minSize);
}

void SAColorGridWidget::setHorizontalSpacerToRight(bool on)
{
    if (on) {
        QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        d_ptr->mGridLayout->addItem(horizontalSpacer, 0, d_ptr->mColumnCount, 1, 1);
    } else {
        d_ptr->removeAt(0, d_ptr->mColumnCount);
    }
    d_ptr->mHorizontalSpacerToRight = on;
}

void SAColorGridWidget::onButtonClicked(QAbstractButton* btn)
{
    SAColorToolButton* t = qobject_cast< SAColorToolButton* >(btn);
    if (t) {
        emit colorClicked(t->getColor());
    }
}

void SAColorGridWidget::onButtonPressed(QAbstractButton* btn)
{
    SAColorToolButton* t = qobject_cast< SAColorToolButton* >(btn);
    if (t) {
        emit colorPressed(t->getColor());
    }
}

void SAColorGridWidget::onButtonToggled(QAbstractButton* btn, bool on)
{
    SAColorToolButton* t = qobject_cast< SAColorToolButton* >(btn);
    if (t) {
        emit colorToggled(t->getColor(), on);
    }
}

QSize SAColorGridWidget::sizeHint() const
{
    return d_ptr->mGridLayout->sizeHint();
    //    int w = d_ptr->mIconSize.width() + d_ptr->mGridLayout->verticalSpacing();
    //    int h = d_ptr->mIconSize.height();
    //    if (d_ptr->mColumnCount > 0) {
    //        h *= d_ptr->mColumnCount;
    //        if (!d_ptr->mColors.empty()) {
    //            int r = std::ceil(d_ptr->mColors.size() / (float)(d_ptr->mColumnCount));
    //            if (r > 0) {
    //                w *= r;
    //            }
    //        }
    //    }
    //    return QSize(w, h);
}

void SAColorGridWidget::onButtonReleased(QAbstractButton* btn)
{
    SAColorToolButton* t = qobject_cast< SAColorToolButton* >(btn);
    if (t) {
        emit colorReleased(t->getColor());
    }
}

namespace SA
{

QList< QColor > getStandardColorList()
{
    static QList< QColor > s_standardColorList({ QColor(192, 0, 0),
                                                 QColor(255, 0, 0),
                                                 QColor(255, 192, 0),
                                                 QColor(255, 255, 0),
                                                 QColor(146, 208, 80),
                                                 QColor(0, 176, 80),
                                                 QColor(0, 176, 240),
                                                 QColor(0, 112, 192),
                                                 QColor(0, 32, 96),
                                                 QColor(112, 48, 160) });
    return s_standardColorList;
}
}

/*** End of inlined file: SAColorGridWidget.cpp ***/

/*** Start of inlined file: SAColorPaletteGridWidget.cpp ***/
// Qt
#include <QMenu>
#include <QWidgetAction>
#include <QVBoxLayout>
#include <QColorDialog>
// SA

class SAColorPaletteGridWidget::PrivateData
{
    SA_COLOR_WIDGETS_DECLARE_PUBLIC(SAColorPaletteGridWidget)
public:
    PrivateData(SAColorPaletteGridWidget* p);
    //����color palette
    QList< QColor > makeColorPalette(const QList< QColor >& clrList) const;

public:
    QList< int > mFactor { 180, 160, 140, 75, 50 };  ///< palette�ı������ӣ�������QColor��lighter����ִ��
    QVBoxLayout* mLayout { nullptr };                ///< ��ֱ����
    SAColorGridWidget* mMainColorList { nullptr };   ///< ���������ʾ��׼��ɫ
    SAColorGridWidget* mPaletteColorGrid { nullptr };  ///< �����������3����ɫ��2�а�ɫ��palette
};

SAColorPaletteGridWidget::PrivateData::PrivateData(SAColorPaletteGridWidget* p) : q_ptr(p)
{
    mLayout = new QVBoxLayout(p);
    p->setLayout(mLayout);
    mMainColorList    = new SAColorGridWidget(p);
    mPaletteColorGrid = new SAColorGridWidget(p);
    mLayout->addWidget(mMainColorList);
    mLayout->addWidget(mPaletteColorGrid);
    mLayout->setContentsMargins(1, 1, 1, 1);
    mLayout->setSpacing(8);
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    mMainColorList->setSizePolicy(sizePolicy);
    mPaletteColorGrid->setSizePolicy(sizePolicy);
    mMainColorList->setColumnCount(0);
    mPaletteColorGrid->setVerticalSpacing(0);
}

QList< QColor > SAColorPaletteGridWidget::PrivateData::makeColorPalette(const QList< QColor >& clrList) const
{
    QList< QColor > res;
    for (int f : qAsConst(mFactor)) {
        for (const QColor& c : qAsConst(clrList)) {
            res.append(c.lighter(f));
        }
    }
    return res;
}
//==============================================================
// name
//==============================================================

/**
 * @brief ʹ��Ĭ�ϵı�׼��ɫ����һ��color palette
 * @param par
 */
SAColorPaletteGridWidget::SAColorPaletteGridWidget(QWidget* par) : QWidget(par), d_ptr(new PrivateData(this))
{
    init();
    setColorList(SA::getStandardColorList());
}

/**
 * @brief ����ָ������ɫ����һ��color palette
 * @param cls
 * @param par
 */
SAColorPaletteGridWidget::SAColorPaletteGridWidget(const QList< QColor >& cls, QWidget* par)
    : QWidget(par), d_ptr(new PrivateData(this))
{
    init();
    setColorList(cls);
}

SAColorPaletteGridWidget::~SAColorPaletteGridWidget()
{
}
void SAColorPaletteGridWidget::init()
{
    connect(d_ptr->mMainColorList, &SAColorGridWidget::colorClicked, this, &SAColorPaletteGridWidget::onMainColorClicked);
    connect(d_ptr->mPaletteColorGrid, &SAColorGridWidget::colorClicked, this, &SAColorPaletteGridWidget::onPaletteColorClicked);
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    setSizePolicy(sizePolicy);
    setColorIconSize(QSize(10, 10));
}

/**
 * @brief ������ɫϵ�У���ɫϵ�еĸ�����������ɫ����������paletteɫ�������factor��������
 * @param cls
 */
void SAColorPaletteGridWidget::setColorList(const QList< QColor >& cls)
{
    d_ptr->mMainColorList->setColumnCount(0);
    d_ptr->mMainColorList->setColorList(cls);
    d_ptr->mPaletteColorGrid->setColumnCount(cls.size());
    d_ptr->mPaletteColorGrid->setColorList(d_ptr->makeColorPalette(cls));
}

/**
 * @brief ��ȡ��ɫϵ��
 * @return
 */
QList< QColor > SAColorPaletteGridWidget::getColorList() const
{
    return d_ptr->mMainColorList->getColorList();
}

/**
 * @brief ������ɫ��ǳ����factor��factor������palette��������factor��5��������5��
 *
 * Ĭ��Ϊ{ 180, 160, 140, 75, 50 },�൱�ڻ���5�У�ÿ��ϵ����Ա�׼��ɫִ��QColor::lighter����
 * @param factor
 */
void SAColorPaletteGridWidget::setFactor(const QList< int >& factor)
{
    d_ptr->mFactor = factor;
    d_ptr->mPaletteColorGrid->setColorList(d_ptr->makeColorPalette(d_ptr->mMainColorList->getColorList()));
}

/**
 * @brief ��ȡɫ��
 * @return
 */
QList< int > SAColorPaletteGridWidget::getFactor() const
{
    return d_ptr->mFactor;
}

/**
 * @brief ������ɫ��ĳߴ磬Ĭ��Ϊ10*10
 * @param s
 */
void SAColorPaletteGridWidget::setColorIconSize(const QSize& s)
{
    d_ptr->mMainColorList->setColorIconSize(s);
    d_ptr->mPaletteColorGrid->setColorIconSize(s);
}

QSize SAColorPaletteGridWidget::getColorIconSize() const
{
    return d_ptr->mMainColorList->getColorIconSize();
}

/**
 * @brief ������ɫ���Ƿ��ܱ�checked
 * @param on
 */
void SAColorPaletteGridWidget::setColorCheckable(bool on)
{
    d_ptr->mMainColorList->setColorCheckable(on);
    d_ptr->mPaletteColorGrid->setColorCheckable(on);
}

bool SAColorPaletteGridWidget::isColorCheckable() const
{
    return d_ptr->mMainColorList->isColorCheckable();
}

void SAColorPaletteGridWidget::onMainColorClicked(const QColor& c)
{
    d_ptr->mPaletteColorGrid->clearCheckedState();
    emit colorClicked(c);
}

void SAColorPaletteGridWidget::onPaletteColorClicked(const QColor& c)
{
    d_ptr->mMainColorList->clearCheckedState();
    emit colorClicked(c);
}

/*** End of inlined file: SAColorPaletteGridWidget.cpp ***/

/*** Start of inlined file: SAColorToolButton.cpp ***/
#include <QApplication>
#include <QPaintEvent>
#include <QStylePainter>
#include <QStyleOption>
#include <QStyleOptionToolButton>
#include <QResizeEvent>
#include <QDebug>
#define SAColorToolButton_DEBUG_PRINT 0
class SAColorToolButton::PrivateData
{
    SA_COLOR_WIDGETS_DECLARE_PUBLIC(SAColorToolButton)
public:
    PrivateData(SAColorToolButton* p);
    void calcSizeOfToolButtonIconOnly(const QStyleOptionToolButton& opt, QRect& iconRect, QRect& textRect, QRect& colorRect);
    void calcSizeOfToolButtonTextOnly(const QStyleOptionToolButton& opt, QRect& iconRect, QRect& textRect, QRect& colorRect);
    void calcSizeOfToolButtonTextBesideIcon(const QStyleOptionToolButton& opt, QRect& iconRect, QRect& textRect, QRect& colorRect);
    void calcSizeOfToolButtonTextUnderIcon(const QStyleOptionToolButton& opt, QRect& iconRect, QRect& textRect, QRect& colorRect);
    QPixmap createIconPixmap(const QStyleOptionToolButton& opt, const QRect& iconRect);
    QRect getButtonRect(const QStyleOptionToolButton& opt);
    QRect getIndicatorRect(const QStyleOptionToolButton& opt);
    QStyle::State getButtonStyleState(const QStyleOptionToolButton& opt);
    QStyle::State getButtonMenuStyleState(const QStyleOptionToolButton& opt);

public:
    QColor mColor { Qt::white };
    int mSpacing { 2 };                ///< ���
    QMargins mMargins { 3, 3, 3, 3 };  ///< box

    static int s_indicatorArrorWidth;  ///< �˵����
};

int SAColorToolButton::PrivateData::s_indicatorArrorWidth = 8;

SAColorToolButton::PrivateData::PrivateData(SAColorToolButton* p) : q_ptr(p)
{
}

void SAColorToolButton::PrivateData::calcSizeOfToolButtonIconOnly(const QStyleOptionToolButton& opt, QRect& iconRect, QRect& textRect, QRect& colorRect)
{
    //ȷ���ı�����
    textRect         = QRect();
    QRect buttonRect = getButtonRect(opt);
    if (opt.icon.isNull()) {
        colorRect = buttonRect;
        iconRect  = QRect();
    } else {
        QSize tmpSize = opt.iconSize;
        if (tmpSize.isNull()) {
            tmpSize = QSize(16, 16);
        }
        tmpSize         = buttonRect.size().boundedTo(tmpSize);
        int colorHeight = tmpSize.height() / 4;
        int totalHeight = colorHeight + tmpSize.height() + mSpacing;
        if (totalHeight > buttonRect.height()) {
            //���ߣ���ʱҪͨ���߶ȷ���tmpSize��colorHeight
            colorHeight = (buttonRect.height() - mSpacing) / 5;
            tmpSize.setHeight(colorHeight * 4);
            if (opt.iconSize.height() > 0) {
                tmpSize.setWidth(tmpSize.height() * opt.iconSize.width() / opt.iconSize.height());  //�ȱ���
            }
            tmpSize = buttonRect.size().boundedTo(tmpSize);
        }
        //��icon����ɫλ��ͼ������
        int y = (buttonRect.height() - colorHeight - mSpacing - tmpSize.height()) / 2;  //(ButtonHeight-TotalHeight)/2
        int x = (buttonRect.width() - tmpSize.width()) / 2;
        iconRect  = QRect(buttonRect.left() + x, buttonRect.top() + y, tmpSize.width(), tmpSize.height());
        colorRect = QRect(iconRect.x(), iconRect.bottom() + mSpacing, iconRect.width(), colorHeight);
    }
}

/**
 * @brief ���ı�����������5������ʾ��ɫ
 * @param opt
 * @param iconRect
 * @param textRect
 * @param colorRect �����5������ʾ��ɫ
 */
void SAColorToolButton::PrivateData::calcSizeOfToolButtonTextOnly(const QStyleOptionToolButton& opt, QRect& iconRect, QRect& textRect, QRect& colorRect)
{
    QRect buttonRect = getButtonRect(opt);
    iconRect         = QRect();
    QSize colorSize  = opt.iconSize;
    if (colorSize.isNull()) {
        colorSize = QSize(16, 16);
    }
    colorSize = buttonRect.size().boundedTo(colorSize);
    colorRect = QRect(buttonRect.left(),
                      buttonRect.top() + (buttonRect.height() - colorSize.height()) / 2,
                      colorSize.width(),
                      colorSize.height());
    textRect  = buttonRect.adjusted(colorRect.right() + mSpacing, 0, 0, 0);
}

void SAColorToolButton::PrivateData::calcSizeOfToolButtonTextBesideIcon(const QStyleOptionToolButton& opt,
                                                                        QRect& iconRect,
                                                                        QRect& textRect,
                                                                        QRect& colorRect)
{
    QRect buttonRect = getButtonRect(opt);
    if (opt.icon.isNull()) {
        QSize colorSize = opt.iconSize;
        if (colorSize.isNull()) {
            colorSize = QSize(16, 16);
        }
        // ˵��û��icon
        // ��ʱ���ж���color
        // iconRect=Null
        colorSize = buttonRect.size().boundedTo(colorSize);
        iconRect  = QRect();
        colorRect = QRect(buttonRect.left(),
                          buttonRect.top() + (buttonRect.height() - colorSize.height()) / 2,
                          colorSize.width(),
                          colorSize.height());
        textRect  = buttonRect.adjusted(colorRect.width() + mSpacing, 0, 0, 0);
    } else {  //��ͼ��
        QSize tmpSize = opt.iconSize;
        if (tmpSize.isNull()) {
            tmpSize = QSize(16, 16);
        }
        tmpSize         = buttonRect.size().boundedTo(tmpSize);
        int colorHeight = tmpSize.height() / 4;
        int totalHeight = colorHeight + tmpSize.height() + mSpacing;
        if (totalHeight > buttonRect.height()) {
            //���ߣ���ʱҪͨ���߶ȷ���tmpSize��colorHeight
            colorHeight = (buttonRect.height() - mSpacing) / 5;
            tmpSize.setHeight(colorHeight * 4);
            tmpSize.setWidth(tmpSize.height());  //��������Ҳ����Ϊ������
        }
        //��icon����ɫλ��ͼ������
        int y = (buttonRect.height() - colorHeight - mSpacing - tmpSize.height()) / 2;  //(ButtonHeight-TotalHeight)/2
        iconRect  = QRect(buttonRect.left(), buttonRect.top() + y, tmpSize.width(), tmpSize.height());
        colorRect = QRect(iconRect.x(), iconRect.bottom() + mSpacing, iconRect.width(), colorHeight);
        textRect  = buttonRect.adjusted(iconRect.right() + mSpacing, 0, 0, 0);
    }
}

void SAColorToolButton::PrivateData::calcSizeOfToolButtonTextUnderIcon(const QStyleOptionToolButton& opt,
                                                                       QRect& iconRect,
                                                                       QRect& textRect,
                                                                       QRect& colorRect)
{
    QRect buttonRect = getButtonRect(opt);
    QSize tmpSize    = opt.iconSize;
    if (tmpSize.isNull()) {
        tmpSize = QSize(16, 16);
    }
    //��ȡ����߶�
    int textHeight = opt.fontMetrics.height();
    tmpSize        = buttonRect.size().boundedTo(tmpSize);
    if (opt.icon.isNull()) {
        int totalHeight = textHeight + opt.iconSize.height() + mSpacing;
        if (totalHeight < buttonRect.height()) {
            //�㹻��
            colorRect = QRect(buttonRect.left() + (buttonRect.width() - tmpSize.width()) / 2,
                              buttonRect.top() + (buttonRect.height() - totalHeight) / 2,
                              tmpSize.width(),
                              opt.iconSize.height());
        } else {
            //�ռ䲻��
            colorRect = QRect(buttonRect.left() + (buttonRect.width() - tmpSize.width()) / 2,
                              buttonRect.top() + mSpacing,
                              tmpSize.width(),
                              opt.iconSize.height());
        }
        iconRect = QRect();
        textRect = QRect(buttonRect.left(), colorRect.bottom() + mSpacing, buttonRect.width(), textHeight);

    } else {
        //��ͼ��
        int colorHeight = tmpSize.height() / 4;
        int totalHeight = textHeight + opt.iconSize.height() + colorHeight + 2 * mSpacing;
        if (totalHeight < buttonRect.height()) {
            //�߶ȿռ��㹻
            //�Ȳ���icon
            iconRect = QRect(buttonRect.left() + (buttonRect.width() - tmpSize.width()) / 2,
                             buttonRect.top() + (buttonRect.height() - totalHeight) / 2,
                             tmpSize.width(),
                             opt.iconSize.height());

        } else {
            //�ռ䲻��
            iconRect = QRect(buttonRect.left() + (buttonRect.width() - tmpSize.width()) / 2,
                             buttonRect.top() + mSpacing,
                             tmpSize.width(),
                             opt.iconSize.height());
        }
        colorRect = QRect(iconRect.x(), iconRect.bottom() + mSpacing, iconRect.width(), colorHeight);
        textRect  = QRect(buttonRect.left(), colorRect.bottom() + mSpacing, buttonRect.width(), textHeight);
    }
}

QPixmap SAColorToolButton::PrivateData::createIconPixmap(const QStyleOptionToolButton& opt, const QRect& iconRect)
{
    if (opt.icon.isNull()) {
        return (QPixmap());
    }
    //��ͼ��
    QIcon::State state = opt.state & QStyle::State_On ? QIcon::On : QIcon::Off;
    QIcon::Mode mode;
    if (!(opt.state & QStyle::State_Enabled)) {
        mode = QIcon::Disabled;
    } else if ((opt.state & QStyle::State_MouseOver) && (opt.state & QStyle::State_AutoRaise)) {
        mode = QIcon::Active;
    } else {
        mode = QIcon::Normal;
    }
    // return (opt.icon.pixmap(this->window()->windowHandle(), opt.rect.size().boundedTo(realConSize), mode, state));
    return (opt.icon.pixmap(iconRect.size(), mode, state));
}

/**
 * @brief ��ȡ��ť�ľ�������
 * @param opt
 * @return
 */
QRect SAColorToolButton::PrivateData::getButtonRect(const QStyleOptionToolButton& opt)
{
    QRect btnRect = q_ptr->style()->subControlRect(QStyle::CC_ToolButton, &opt, QStyle::SC_ToolButton, q_ptr);
    return btnRect.marginsRemoved(mMargins);
}

/**
 * @brief ��ȡToolButtonMenu������
 * @note ע�⣬�������QStyleOptionToolButton::MenuButtonPopup|QStyleOptionToolButton::HasMenu�µ��ô˺��������ص���QRect()
 * @param opt
 * @return
 */
QRect SAColorToolButton::PrivateData::getIndicatorRect(const QStyleOptionToolButton& opt)
{
    if (opt.features & QStyleOptionToolButton::MenuButtonPopup || opt.features & QStyleOptionToolButton::HasMenu) {
        return q_ptr->style()->subControlRect(QStyle::CC_ToolButton, &opt, QStyle::SC_ToolButtonMenu, q_ptr);
    }
    return QRect();
}

/**
 * @brief ����Qt qcommonStyleԴ�룬��QStyleOptionToolButton��style����
 * @param opt
 * @return
 */
QStyle::State SAColorToolButton::PrivateData::getButtonStyleState(const QStyleOptionToolButton& opt)
{
    QStyle::State bflags = opt.state & ~QStyle::State_Sunken;
    if (bflags & QStyle::State_AutoRaise) {
        if (!(bflags & QStyle::State_MouseOver) || !(bflags & QStyle::State_Enabled)) {
            bflags &= ~QStyle::State_Raised;
        }
    }
    if (opt.state & QStyle::State_Sunken) {
        if (opt.activeSubControls & QStyle::SC_ToolButton) {
            bflags |= QStyle::State_Sunken;
        }
    }
    return bflags;
}

/**
 * @brief ����Qt qcommonStyleԴ�룬��QStyleOptionToolButton��style����
 * @param opt
 * @return
 */
QStyle::State SAColorToolButton::PrivateData::getButtonMenuStyleState(const QStyleOptionToolButton& opt)
{
    QStyle::State mflags = opt.state & ~QStyle::State_Sunken;
    if (mflags & QStyle::State_AutoRaise) {
        if (!(mflags & QStyle::State_MouseOver) || !(mflags & QStyle::State_Enabled)) {
            mflags &= ~QStyle::State_Raised;
        }
    }
    if (opt.state & QStyle::State_Sunken) {
        mflags |= QStyle::State_Sunken;
    }
    return mflags;
}

//==============================================================
// SAColorToolButton
//==============================================================
SAColorToolButton::SAColorToolButton(QWidget* parent) : QToolButton(parent), d_ptr(new PrivateData(this))
{
    QStyleOptionToolButton opt;
    initStyleOption(&opt);
    connect(this, &QToolButton::clicked, this, &SAColorToolButton::onButtonClicked);
}

SAColorToolButton::~SAColorToolButton()
{
}

/**
 * @brief ��ȡ��ɫ
 * @return
 */
QColor SAColorToolButton::getColor() const
{
    return d_ptr->mColor;
}

/**
 * @brief ����Margins
 * @param mg
 */
void SAColorToolButton::setMargins(const QMargins& mg)
{
    d_ptr->mMargins = mg;
    repaint();
}

QMargins SAColorToolButton::getMargins() const
{
    return d_ptr->mMargins;
}

/**
 * @brief ��������ɫ��ʾ
 * @param p
 * @param colorRect ���Ƶ�����
 */
void SAColorToolButton::paintNoneColor(QPainter* p, const QRect& colorRect)
{
    p->save();
    QPen pen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap);
    p->setPen(pen);
    p->setRenderHint(QPainter::SmoothPixmapTransform, true);
    p->setRenderHint(QPainter::Antialiasing, true);
    int ss = colorRect.width() / 3;
    p->drawLine(QPoint(colorRect.x() + ss, colorRect.bottom()), QPoint(colorRect.right() - ss, colorRect.top()));
    pen.setColor(Qt::black);
    p->setPen(pen);
    p->drawRect(colorRect);
    p->restore();
}

/**
 * @brief ������ɫ
 * @note �ᷢ��@sa colorChanged �ź�
 * @param c
 */
void SAColorToolButton::setColor(const QColor& c)
{
    if (d_ptr->mColor != c) {
        d_ptr->mColor = c;
        repaint();
        emit colorChanged(c);
    }
}

/**
 * @brief ����������������λ��
 * @param opt
 * @param iconRect ͼ������
 * @param textRect �ı�����
 * @param colorRect ��ɫ����
 */
void SAColorToolButton::calcRect(const QStyleOptionToolButton& opt, QRect& iconRect, QRect& textRect, QRect& colorRect)
{
    switch (opt.toolButtonStyle) {
    case Qt::ToolButtonTextOnly:
        d_ptr->calcSizeOfToolButtonTextOnly(opt, iconRect, textRect, colorRect);
        break;
    case Qt::ToolButtonTextBesideIcon:
        d_ptr->calcSizeOfToolButtonTextBesideIcon(opt, iconRect, textRect, colorRect);
        break;
    case Qt::ToolButtonTextUnderIcon:
        d_ptr->calcSizeOfToolButtonTextUnderIcon(opt, iconRect, textRect, colorRect);
        break;
    case Qt::ToolButtonFollowStyle:
    case Qt::ToolButtonIconOnly:
        d_ptr->calcSizeOfToolButtonIconOnly(opt, iconRect, textRect, colorRect);
        break;
    default:
        d_ptr->calcSizeOfToolButtonIconOnly(opt, iconRect, textRect, colorRect);
        break;
    }
}

void SAColorToolButton::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);
    QStylePainter p(this);

    QStyleOptionToolButton opt;

    initStyleOption(&opt);
    QRect iconRect, colorRect, textRect;
    calcRect(opt, iconRect, textRect, colorRect);
    paintButton(&p, opt);
    //����ͼ��
    paintIcon(&p, iconRect, opt);
    //��������
    paintText(&p, textRect, opt);
    //������ɫ
    paintColor(&p, colorRect, d_ptr->mColor, opt);
}

void SAColorToolButton::resizeEvent(QResizeEvent* e)
{
    //��resizeevent�����ͼ����ĳߴ磬�����ڻ�ͼ������ʵʱ�������Ч��
    QToolButton::resizeEvent(e);
}

/**
 * @brief sizeHint����
 * @return
 */
QSize SAColorToolButton::sizeHint() const
{
    ensurePolished();
    QStyleOptionToolButton opt;
    initStyleOption(&opt);
    int w = 0, h = 0;
    if (Qt::ToolButtonIconOnly == opt.toolButtonStyle || Qt::ToolButtonFollowStyle == opt.toolButtonStyle) {
        //���ı��޹�
        w = opt.iconSize.width() + d_ptr->mMargins.left() + d_ptr->mMargins.right();
        h = opt.iconSize.height() + d_ptr->mMargins.top() + d_ptr->mMargins.bottom();
    } else if (Qt::ToolButtonTextOnly == opt.toolButtonStyle || Qt::ToolButtonTextBesideIcon == opt.toolButtonStyle) {
        QSize textSize = opt.fontMetrics.size(Qt::TextSingleLine | Qt::TextShowMnemonic, opt.text);
        textSize.setHeight(textSize.height() + 4);
        QSize iconSize = opt.iconSize;
        if (!opt.icon.isNull()) {
            //��ͼ�꣬Ҫ��iconsize�߶ȵ�1/4����ɫ
            iconSize.setHeight(iconSize.height() + iconSize.height() / 4 + d_ptr->mSpacing);
        }
        w = textSize.width() + d_ptr->mSpacing + iconSize.width() + d_ptr->mMargins.left() + d_ptr->mMargins.right();
        h = qMax(textSize.height(), iconSize.height()) + d_ptr->mMargins.top() + d_ptr->mMargins.bottom();
    } else if (Qt::ToolButtonTextUnderIcon == opt.toolButtonStyle) {
        QSize textSize = opt.fontMetrics.size(Qt::TextSingleLine | Qt::TextShowMnemonic, opt.text);
        textSize.setHeight(textSize.height() + 4);
        QSize iconSize = opt.iconSize;
        if (!opt.icon.isNull()) {
            //��ͼ�꣬Ҫ��iconsize�߶ȵ�1/4����ɫ
            iconSize.setHeight(iconSize.height() + iconSize.height() / 4 + d_ptr->mSpacing);
        }
        w = qMax(textSize.width(), iconSize.width()) + d_ptr->mMargins.left() + d_ptr->mMargins.right();
        h = textSize.height() + iconSize.height() + d_ptr->mSpacing + d_ptr->mMargins.top() + d_ptr->mMargins.bottom();
    }
    opt.rect.setSize(QSize(w, h));  // PM_MenuButtonIndicator depends on the height
    if (opt.features & QStyleOptionToolButton::MenuButtonPopup || opt.features & QStyleOptionToolButton::HasMenu) {
        w += style()->pixelMetric(QStyle::PM_MenuButtonIndicator, &opt, this);
    }
    //! Qt6.4 ȡ����QApplication::globalStrut
    return style()->sizeFromContents(QStyle::CT_ToolButton, &opt, QSize(w, h), this).expandedTo(QSize(2, 2));
}

void SAColorToolButton::onButtonClicked(bool checked)
{
    emit colorClicked(getColor(), checked);
}

/**
 * @brief ���ư�ť
 * @param p
 * @param opt
 */
void SAColorToolButton::paintButton(QStylePainter* p, const QStyleOptionToolButton& opt)
{
    bool autoRaise = opt.state & QStyle::State_AutoRaise;
    //���ư�ť
    if (autoRaise) {
        style()->drawPrimitive(QStyle::PE_PanelButtonTool, &opt, p, this);
    } else {
        style()->drawPrimitive(QStyle::PE_PanelButtonBevel, &opt, p, this);
    }
    if (opt.features & QStyleOptionToolButton::MenuButtonPopup) {
        QStyleOption tool = opt;
        tool.state        = d_ptr->getButtonMenuStyleState(opt);
        tool.rect         = d_ptr->getIndicatorRect(opt);
        //        if (tool.state & (QStyle::State_Sunken | QStyle::State_On | QStyle::State_Raised)) {
        //            style()->drawPrimitive(QStyle::PE_IndicatorButtonDropDown, &tool, &p, this);
        //        }
        style()->drawPrimitive(QStyle::PE_IndicatorArrowDown, &tool, p, this);
    }

    //����focus
    if (opt.state & QStyle::State_HasFocus) {
        QStyleOptionFocusRect fr;
        fr.QStyleOption::operator=(opt);
        fr.rect.adjust(3, 3, -3, -3);
        if (opt.features & QStyleOptionToolButton::MenuButtonPopup) {
            fr.rect.adjust(0, 0, style()->pixelMetric(QStyle::PM_MenuButtonIndicator, &opt, this), 0);
        }
        style()->drawPrimitive(QStyle::PE_FrameFocusRect, &fr, p, this);
    }
}

/**
 * @brief ����icon
 * @param p
 * @param iconRect
 * @param opt icon��Ϣ��QStyleOptionToolButton��ȡ
 */
void SAColorToolButton::paintIcon(QStylePainter* p, const QRect& iconRect, const QStyleOptionToolButton& opt)
{
    if (!iconRect.isNull()) {
        QPixmap pm = d_ptr->createIconPixmap(opt, iconRect);
        style()->drawItemPixmap(p, iconRect, Qt::AlignCenter, pm);
    }
}

/**
 * @brief �����ı�
 * @param p
 * @param textRect
 * @param opt
 */
void SAColorToolButton::paintText(QStylePainter* p, const QRect& textRect, const QStyleOptionToolButton& opt)
{
    if (opt.text.isEmpty()) {
        return;
    }
    if (Qt::ToolButtonIconOnly == opt.toolButtonStyle) {
        return;
    }
    p->save();
    p->setFont(opt.font);
    int alignment = Qt::TextShowMnemonic;
    //��ݼ����»���
    if (!style()->styleHint(QStyle::SH_UnderlineShortcut, &opt, this)) {
        alignment |= Qt::TextHideMnemonic;
    }
    alignment |= Qt::AlignHCenter | Qt::AlignVCenter;
    style()->drawItemText(p,
                          QStyle::visualRect(opt.direction, opt.rect, textRect),
                          alignment,
                          opt.palette,
                          opt.state & QStyle::State_Enabled,
                          opt.text,
                          QPalette::ButtonText);
    p->restore();
}

/**
 * @brief ����color
 * @param p
 * @param iconRect
 * @param opt
 */
void SAColorToolButton::paintColor(QStylePainter* p, const QRect& colorRect, const QColor& color, const QStyleOptionToolButton& opt)
{
    Q_UNUSED(opt);
    if (colorRect.isNull()) {
        return;
    }
    //������ɫ
    if (color.isValid()) {
        p->fillRect(colorRect, color);
    } else {
        paintNoneColor(p, colorRect);
    }
}

/*** End of inlined file: SAColorToolButton.cpp ***/

// sa ribbon

/*** Start of inlined file: SAFramelessHelper.cpp ***/
#include <QRect>
#include <QRubberBand>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QApplication>
#include <QDebug>

class SAPrivateFramelessWidgetData;

/*****
 * FramelessHelperPrivate
 * �洢�����Ӧ�����ݼ��ϣ��Լ��Ƿ���ƶ�������������
 *****/
class SAFramelessHelper::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SAFramelessHelper)
    friend class SAPrivateFramelessWidgetData;

public:
    PrivateData(SAFramelessHelper* p);
    QHash< QWidget*, SAPrivateFramelessWidgetData* > m_widgetDataHash;
    bool m_bWidgetMovable { true };
    bool m_bWidgetResizable { true };
    bool m_bRubberBandOnResize { true };
    bool m_bRubberBandOnMove { true };
};

SAFramelessHelper::PrivateData::PrivateData(SAFramelessHelper* p) : q_ptr(p)
{
}

/*****
 * CursorPosCalculator
 * ��������Ƿ�λ�����ϡ��ҡ��¡����Ͻǡ����½ǡ����Ͻǡ����½�
 *****/
class SAPrivateFramelessCursorPosCalculator
{
public:
    explicit SAPrivateFramelessCursorPosCalculator();
    void reset();
    void recalculate(const QPoint& globalMousePos, const QRect& frameRect);

public:
    bool m_bOnEdges { true };
    bool m_bOnLeftEdge { true };
    bool m_bOnRightEdge { true };
    bool m_bOnTopEdge { true };
    bool m_bOnBottomEdge { true };
    bool m_bOnTopLeftEdge { true };
    bool m_bOnBottomLeftEdge { true };
    bool m_bOnTopRightEdge { true };
    bool m_bOnBottomRightEdge { true };

    static int m_nBorderWidth;
    static int m_nTitleHeight;
};

int SAPrivateFramelessCursorPosCalculator::m_nBorderWidth = 5;
int SAPrivateFramelessCursorPosCalculator::m_nTitleHeight = 30;

/***** CursorPosCalculator *****/
SAPrivateFramelessCursorPosCalculator::SAPrivateFramelessCursorPosCalculator()
{
    reset();
}

void SAPrivateFramelessCursorPosCalculator::reset()
{
    m_bOnEdges           = false;
    m_bOnLeftEdge        = false;
    m_bOnRightEdge       = false;
    m_bOnTopEdge         = false;
    m_bOnBottomEdge      = false;
    m_bOnTopLeftEdge     = false;
    m_bOnBottomLeftEdge  = false;
    m_bOnTopRightEdge    = false;
    m_bOnBottomRightEdge = false;
}

void SAPrivateFramelessCursorPosCalculator::recalculate(const QPoint& gMousePos, const QRect& frameRect)
{
    int globalMouseX = gMousePos.x();
    int globalMouseY = gMousePos.y();

    int frameX = frameRect.x();
    int frameY = frameRect.y();

    int frameWidth  = frameRect.width();
    int frameHeight = frameRect.height();

    m_bOnLeftEdge = (globalMouseX >= frameX && globalMouseX <= frameX + m_nBorderWidth);

    m_bOnRightEdge = (globalMouseX >= frameX + frameWidth - m_nBorderWidth && globalMouseX <= frameX + frameWidth);

    m_bOnTopEdge = (globalMouseY >= frameY && globalMouseY <= frameY + m_nBorderWidth);

    m_bOnBottomEdge = (globalMouseY >= frameY + frameHeight - m_nBorderWidth && globalMouseY <= frameY + frameHeight);

    m_bOnTopLeftEdge     = m_bOnTopEdge && m_bOnLeftEdge;
    m_bOnBottomLeftEdge  = m_bOnBottomEdge && m_bOnLeftEdge;
    m_bOnTopRightEdge    = m_bOnTopEdge && m_bOnRightEdge;
    m_bOnBottomRightEdge = m_bOnBottomEdge && m_bOnRightEdge;

    m_bOnEdges = m_bOnLeftEdge || m_bOnRightEdge || m_bOnTopEdge || m_bOnBottomEdge;
}

/*****
 * WidgetData
 * ���������ʽ���ƶ����塢���Ŵ���
 *****/
class SAPrivateFramelessWidgetData
{
public:
    explicit SAPrivateFramelessWidgetData(SAFramelessHelper::PrivateData* pd, QWidget* pTopLevelWidget);
    ~SAPrivateFramelessWidgetData();
    QWidget* widget();

    // ��������¼�-���������¡��ͷš��ƶ�
    bool handleWidgetEvent(QEvent* event);

    // ������Ƥ��״̬
    void updateRubberBandStatus();

private:
    // ���������ʽ
    void updateCursorShape(const QPoint& gMousePos);

    // ���ô����С
    void resizeWidget(const QPoint& gMousePos);

    // �ƶ�����
    void moveWidget(const QPoint& gMousePos);

    // ������갴��
    bool handleMousePressEvent(QMouseEvent* event);

    // ��������ͷ�
    bool handleMouseReleaseEvent(QMouseEvent* event);

    // ��������ƶ�
    bool handleMouseMoveEvent(QMouseEvent* event);

    // ��������뿪
    bool handleLeaveEvent(QEvent* event);

    // ����������
    bool handleHoverMoveEvent(QHoverEvent* event);

    //�������˫���¼�
    bool handleDoubleClickedMouseEvent(QMouseEvent* event);

private:
    SAFramelessHelper::PrivateData* d;
    QRubberBand* m_pRubberBand;
    QWidget* m_pWidget;
    QPoint m_ptDragPos;
    SAPrivateFramelessCursorPosCalculator m_pressedMousePos;
    SAPrivateFramelessCursorPosCalculator m_moveMousePos;
    bool m_bLeftButtonPressed;
    bool m_bCursorShapeChanged;
    bool m_bLeftButtonTitlePressed;
    Qt::WindowFlags m_windowFlags;
};

/***** WidgetData *****/
SAPrivateFramelessWidgetData::SAPrivateFramelessWidgetData(SAFramelessHelper::PrivateData* pd, QWidget* pTopLevelWidget)
{
    d                         = pd;
    m_pWidget                 = pTopLevelWidget;
    m_bLeftButtonPressed      = false;
    m_bCursorShapeChanged     = false;
    m_bLeftButtonTitlePressed = false;
    m_pRubberBand             = NULL;

    m_windowFlags = m_pWidget->windowFlags();
    m_pWidget->setMouseTracking(true);
    m_pWidget->setAttribute(Qt::WA_Hover, true);

    updateRubberBandStatus();
}

SAPrivateFramelessWidgetData::~SAPrivateFramelessWidgetData()
{
    m_pWidget->setMouseTracking(false);
    m_pWidget->setWindowFlags(m_windowFlags);
    m_pWidget->setAttribute(Qt::WA_Hover, false);

    delete m_pRubberBand;
    m_pRubberBand = NULL;
}

QWidget* SAPrivateFramelessWidgetData::widget()
{
    return (m_pWidget);
}

bool SAPrivateFramelessWidgetData::handleWidgetEvent(QEvent* event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
        return (handleMousePressEvent(static_cast< QMouseEvent* >(event)));

    case QEvent::MouseButtonRelease:
        return (handleMouseReleaseEvent(static_cast< QMouseEvent* >(event)));

    case QEvent::MouseMove:
        return (handleMouseMoveEvent(static_cast< QMouseEvent* >(event)));

    case QEvent::Leave:
        return (handleLeaveEvent(static_cast< QMouseEvent* >(event)));

    case QEvent::HoverMove:
        return (handleHoverMoveEvent(static_cast< QHoverEvent* >(event)));

    case QEvent::MouseButtonDblClick:
        return (handleDoubleClickedMouseEvent(static_cast< QMouseEvent* >(event)));

    default:
        break;
    }
    return (false);
}

void SAPrivateFramelessWidgetData::updateRubberBandStatus()
{
    if (d->m_bRubberBandOnMove || d->m_bRubberBandOnResize) {
        if (NULL == m_pRubberBand) {
            m_pRubberBand = new QRubberBand(QRubberBand::Rectangle);
        }
    } else {
        delete m_pRubberBand;
        m_pRubberBand = NULL;
    }
}

void SAPrivateFramelessWidgetData::updateCursorShape(const QPoint& gMousePos)
{
    if (m_pWidget->isFullScreen() || m_pWidget->isMaximized()) {
        if (m_bCursorShapeChanged) {
            m_pWidget->unsetCursor();
        }
        return;
    }

    m_moveMousePos.recalculate(gMousePos, m_pWidget->frameGeometry());

    if (m_moveMousePos.m_bOnTopLeftEdge || m_moveMousePos.m_bOnBottomRightEdge) {
        m_pWidget->setCursor(Qt::SizeFDiagCursor);
        m_bCursorShapeChanged = true;
    } else if (m_moveMousePos.m_bOnTopRightEdge || m_moveMousePos.m_bOnBottomLeftEdge) {
        m_pWidget->setCursor(Qt::SizeBDiagCursor);
        m_bCursorShapeChanged = true;
    } else if (m_moveMousePos.m_bOnLeftEdge || m_moveMousePos.m_bOnRightEdge) {
        m_pWidget->setCursor(Qt::SizeHorCursor);
        m_bCursorShapeChanged = true;
    } else if (m_moveMousePos.m_bOnTopEdge || m_moveMousePos.m_bOnBottomEdge) {
        m_pWidget->setCursor(Qt::SizeVerCursor);
        m_bCursorShapeChanged = true;
    } else {
        if (m_bCursorShapeChanged) {
            m_pWidget->unsetCursor();
            m_bCursorShapeChanged = false;
        }
    }
}

void SAPrivateFramelessWidgetData::resizeWidget(const QPoint& gMousePos)
{
    QRect origRect;

    if (d->m_bRubberBandOnResize) {
        origRect = m_pRubberBand->frameGeometry();
    } else {
        origRect = m_pWidget->frameGeometry();
    }

    int left   = origRect.left();
    int top    = origRect.top();
    int right  = origRect.right();
    int bottom = origRect.bottom();

    origRect.getCoords(&left, &top, &right, &bottom);

    int minWidth  = m_pWidget->minimumWidth();
    int minHeight = m_pWidget->minimumHeight();

    if (m_pressedMousePos.m_bOnTopLeftEdge) {
        left = gMousePos.x();
        top  = gMousePos.y();
    } else if (m_pressedMousePos.m_bOnBottomLeftEdge) {
        left   = gMousePos.x();
        bottom = gMousePos.y();
    } else if (m_pressedMousePos.m_bOnTopRightEdge) {
        right = gMousePos.x();
        top   = gMousePos.y();
    } else if (m_pressedMousePos.m_bOnBottomRightEdge) {
        right  = gMousePos.x();
        bottom = gMousePos.y();
    } else if (m_pressedMousePos.m_bOnLeftEdge) {
        left = gMousePos.x();
    } else if (m_pressedMousePos.m_bOnRightEdge) {
        right = gMousePos.x();
    } else if (m_pressedMousePos.m_bOnTopEdge) {
        top = gMousePos.y();
    } else if (m_pressedMousePos.m_bOnBottomEdge) {
        bottom = gMousePos.y();
    }

    QRect newRect(QPoint(left, top), QPoint(right, bottom));

    if (newRect.isValid()) {
        if (minWidth > newRect.width()) {
            if (left != origRect.left()) {
                newRect.setLeft(origRect.left());
            } else {
                newRect.setRight(origRect.right());
            }
        }
        if (minHeight > newRect.height()) {
            if (top != origRect.top()) {
                newRect.setTop(origRect.top());
            } else {
                newRect.setBottom(origRect.bottom());
            }
        }

        if (d->m_bRubberBandOnResize) {
            m_pRubberBand->setGeometry(newRect);
        } else {
            m_pWidget->setGeometry(newRect);
        }
    }
}

void SAPrivateFramelessWidgetData::moveWidget(const QPoint& gMousePos)
{
    if (d->m_bRubberBandOnMove) {
        m_pRubberBand->move(gMousePos - m_ptDragPos);
    } else {
        m_pWidget->move(gMousePos - m_ptDragPos);
    }
}

bool SAPrivateFramelessWidgetData::handleMousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_bLeftButtonPressed      = true;
        m_bLeftButtonTitlePressed = event->pos().y() < m_moveMousePos.m_nTitleHeight;

        QRect frameRect = m_pWidget->frameGeometry();
        m_pressedMousePos.recalculate(event->globalPos(), frameRect);

        m_ptDragPos = event->globalPos() - frameRect.topLeft();

        if (m_pressedMousePos.m_bOnEdges) {
            if (m_pWidget->isMaximized()) {
                //���������״̬ʱ������߽粻���κδ���
                return (false);
            }
            if (d->m_bRubberBandOnResize) {
                m_pRubberBand->setGeometry(frameRect);
                m_pRubberBand->show();
                return (true);
            }
        } else if (d->m_bRubberBandOnMove && m_bLeftButtonTitlePressed) {
            if (m_pWidget->isMaximized()) {
                //���������״̬ʱ����������������κδ���
                return (false);
            }
            m_pRubberBand->setGeometry(frameRect);
            m_pRubberBand->show();
            return (true);
        }
    }
    return (false);
}

bool SAPrivateFramelessWidgetData::handleMouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_bLeftButtonPressed      = false;
        m_bLeftButtonTitlePressed = false;
        m_pressedMousePos.reset();
        if (m_pRubberBand && m_pRubberBand->isVisible()) {
            m_pRubberBand->hide();
            m_pWidget->setGeometry(m_pRubberBand->geometry());
            return (true);
        }
    }
    return (false);
}

bool SAPrivateFramelessWidgetData::handleMouseMoveEvent(QMouseEvent* event)
{
    if (m_bLeftButtonPressed) {
        if (d->m_bWidgetResizable && m_pressedMousePos.m_bOnEdges) {
            if (m_pWidget->isMaximized()) {
                //���������״̬ʱ������߽粻���κδ���
                return (false);
            }
            resizeWidget(event->globalPos());
            return (true);
        } else if (d->m_bWidgetMovable && m_bLeftButtonTitlePressed) {
            if (m_pWidget->isMaximized()) {
                //��������ڵ��������λ��
                QRect normalGeometry = m_pWidget->normalGeometry();
                m_pWidget->showNormal();
                QPoint p = event->globalPos();
                p.ry() -= 10;
                p.rx() -= (normalGeometry.width() / 2);
                m_pWidget->move(p);
                //��ʱҪ����m_ptDragPos
                m_ptDragPos = QPoint(normalGeometry.width() / 2, 10);
                return (true);
            }
            moveWidget(event->globalPos());
            return (true);
        }
        return (false);
    } else if (d->m_bWidgetResizable) {
        updateCursorShape(event->globalPos());
    }
    return (false);
}

bool SAPrivateFramelessWidgetData::handleLeaveEvent(QEvent* event)
{
    Q_UNUSED(event)
    if (!m_bLeftButtonPressed) {
        m_pWidget->unsetCursor();
        return (true);
    }
    return (false);
}

bool SAPrivateFramelessWidgetData::handleHoverMoveEvent(QHoverEvent* event)
{
    if (d->m_bWidgetResizable) {
        updateCursorShape(m_pWidget->mapToGlobal(event->pos()));
    }
    return (false);
}

bool SAPrivateFramelessWidgetData::handleDoubleClickedMouseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        if (m_pWidget) {
            SARibbonMainWindow* mainwindow = qobject_cast< SARibbonMainWindow* >(m_pWidget);
            if (mainwindow) {
                if (mainwindow->windowButtonFlags() & Qt::WindowMaximizeButtonHint) {
                    //����󻯰�ť��ʾʱ�Ž���shownormal����
                    bool titlePressed = event->pos().y() < m_moveMousePos.m_nTitleHeight;
                    if (titlePressed) {
                        if (m_pWidget->isMaximized()) {
                            m_pWidget->showNormal();
                        } else {
                            m_pWidget->showMaximized();
                        }
                        return (true);
                    }
                }
            }
        }
    }
    return (false);
}

//===================================================
// SAFramelessHelper
//===================================================
SAFramelessHelper::SAFramelessHelper(QObject* parent) : QObject(parent), d_ptr(new SAFramelessHelper::PrivateData(this))
{
    d_ptr->m_bWidgetMovable      = true;
    d_ptr->m_bWidgetResizable    = true;
    d_ptr->m_bRubberBandOnResize = false;
    d_ptr->m_bRubberBandOnMove   = false;
    if (parent) {
        QWidget* w = qobject_cast< QWidget* >(parent);
        if (w) {
            w->setWindowFlags(w->windowFlags() | Qt::FramelessWindowHint);
            setWidgetMovable(true);       //���ô�����ƶ�
            setWidgetResizable(true);     //���ô��������
            setRubberBandOnMove(false);   //������Ƥ��Ч��-���ƶ�
            setRubberBandOnResize(true);  //������Ƥ��Ч��-������
            activateOn(w);                //���ǰ����
        }
    }
}

SAFramelessHelper::~SAFramelessHelper()
{
    QList< QWidget* > keys = d_ptr->m_widgetDataHash.keys();
    int size               = keys.size();

    for (int i = 0; i < size; ++i) {
        delete d_ptr->m_widgetDataHash.take(keys[ i ]);
    }
}

bool SAFramelessHelper::eventFilter(QObject* obj, QEvent* event)
{
    switch (event->type()) {
    case QEvent::MouseMove:
    case QEvent::HoverMove:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick:
    case QEvent::Leave: {
        SAPrivateFramelessWidgetData* data = d_ptr->m_widgetDataHash.value(static_cast< QWidget* >(obj));
        if (data) {
            return (data->handleWidgetEvent(event));
        }
        break;
    }

    default:
        break;
    }
    return (QObject::eventFilter(obj, event));
}

void SAFramelessHelper::activateOn(QWidget* topLevelWidget)
{
    if (!d_ptr->m_widgetDataHash.contains(topLevelWidget)) {
        SAPrivateFramelessWidgetData* data = new SAPrivateFramelessWidgetData(d_ptr.get(), topLevelWidget);
        d_ptr->m_widgetDataHash.insert(topLevelWidget, data);

        topLevelWidget->installEventFilter(this);
    }
}

void SAFramelessHelper::removeFrom(QWidget* topLevelWidget)
{
    SAPrivateFramelessWidgetData* data = d_ptr->m_widgetDataHash.take(topLevelWidget);

    if (data) {
        topLevelWidget->removeEventFilter(this);
        delete data;
    }
}

void SAFramelessHelper::setRubberBandOnMove(bool movable)
{
    d_ptr->m_bRubberBandOnMove                  = movable;
    QList< SAPrivateFramelessWidgetData* > list = d_ptr->m_widgetDataHash.values();

    foreach (SAPrivateFramelessWidgetData* data, list) {
        data->updateRubberBandStatus();
    }
}

void SAFramelessHelper::setWidgetMovable(bool movable)
{
    d_ptr->m_bWidgetMovable = movable;
}

void SAFramelessHelper::setWidgetResizable(bool resizable)
{
    d_ptr->m_bWidgetResizable = resizable;
}

void SAFramelessHelper::setRubberBandOnResize(bool resizable)
{
    d_ptr->m_bRubberBandOnResize                = resizable;
    QList< SAPrivateFramelessWidgetData* > list = d_ptr->m_widgetDataHash.values();

    foreach (SAPrivateFramelessWidgetData* data, list) {
        data->updateRubberBandStatus();
    }
}

void SAFramelessHelper::setBorderWidth(int width)
{
    if (width > 0) {
        SAPrivateFramelessCursorPosCalculator::m_nBorderWidth = width;
    }
}

void SAFramelessHelper::setTitleHeight(int height)
{
    if (height > 0) {
        SAPrivateFramelessCursorPosCalculator::m_nTitleHeight = height;
    }
}

bool SAFramelessHelper::widgetMovable()
{
    return (d_ptr->m_bWidgetMovable);
}

bool SAFramelessHelper::widgetResizable()
{
    return (d_ptr->m_bWidgetResizable);
}

bool SAFramelessHelper::rubberBandOnMove()
{
    return (d_ptr->m_bRubberBandOnMove);
}

bool SAFramelessHelper::rubberBandOnResisze()
{
    return (d_ptr->m_bRubberBandOnResize);
}

uint SAFramelessHelper::borderWidth()
{
    return (SAPrivateFramelessCursorPosCalculator::m_nBorderWidth);
}

uint SAFramelessHelper::titleHeight()
{
    return (SAPrivateFramelessCursorPosCalculator::m_nTitleHeight);
}

/*** End of inlined file: SAFramelessHelper.cpp ***/

/*** Start of inlined file: SARibbonApplicationButton.cpp ***/
#define SARIBBON_APPLICATION_BUTTON_MINIMUM_WIDTH 40
SARibbonApplicationButton::SARibbonApplicationButton(QWidget* parent) : QToolButton(parent)
{
    setFocusPolicy(Qt::NoFocus);
    setAutoRaise(true);
    setPopupMode(QToolButton::InstantPopup);
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setMinimumWidth(SARIBBON_APPLICATION_BUTTON_MINIMUM_WIDTH);
}

SARibbonApplicationButton::SARibbonApplicationButton(const QString& text, QWidget* parent) : QToolButton(parent)
{
    setFocusPolicy(Qt::NoFocus);
    setAutoRaise(true);
    setPopupMode(QToolButton::InstantPopup);
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setText(text);
    setMinimumWidth(SARIBBON_APPLICATION_BUTTON_MINIMUM_WIDTH);
}

SARibbonApplicationButton::SARibbonApplicationButton(const QIcon& icon, const QString& text, QWidget* parent)
    : QToolButton(parent)
{
    setFocusPolicy(Qt::NoFocus);
    setAutoRaise(true);
    setPopupMode(QToolButton::InstantPopup);
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setIcon(icon);
    setText(text);
    setMinimumWidth(SARIBBON_APPLICATION_BUTTON_MINIMUM_WIDTH);
}

/*** End of inlined file: SARibbonApplicationButton.cpp ***/

/*** Start of inlined file: SAWindowButtonGroup.cpp ***/
#include <QToolButton>
#include <QResizeEvent>
#include <QStyle>
#include <QDebug>
#include <QScopedPointer>

//Ϊ�˱���ʹ�ô˿�ܵ�app������ȫ�ֵ�qpushbutton �� qss��ʽӰ��˰�ť��������һ����

/**
 * @brief The SAWindowButtonGroupPrivate class
 */
class SAWindowButtonGroup::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SAWindowButtonGroup)
public:
    SAWindowToolButton* buttonClose { nullptr };
    SAWindowToolButton* buttonMinimize { nullptr };
    SAWindowToolButton* buttonMaximize { nullptr };
    int mCloseStretch { 4 };
    int mMaxStretch { 3 };
    int mMinStretch { 3 };
    qreal mIconscale { 0.5 };
    Qt::WindowFlags mFlags;
    PrivateData(SAWindowButtonGroup* p) : q_ptr(p), mFlags(Qt::WindowFlags())
    {
    }

    void setupMinimizeButton(bool on)
    {
        SAWindowButtonGroup* par = q_ptr;

        if (on) {
            if (buttonMinimize) {
                buttonMinimize->deleteLater();
                buttonMinimize = nullptr;
            }
            buttonMinimize = new SAWindowToolButton(par);
            buttonMinimize->setObjectName(QStringLiteral("SAMinimizeWindowButton"));
            buttonMinimize->setFixedSize(30, RibbonSubElementStyleOpt.titleBarHeight() - 2);
            buttonMinimize->setFocusPolicy(Qt::NoFocus);  //������ץ��
            buttonMinimize->setIconSize(buttonMinimize->size() * mIconscale);
            buttonMinimize->show();
            par->connect(buttonMinimize, &QAbstractButton::clicked, par, &SAWindowButtonGroup::minimizeWindow);
        } else {
            if (buttonMinimize) {
                delete buttonMinimize;
                buttonMinimize = nullptr;
            }
        }
        updateSize();
    }

    void setupMaximizeButton(bool on)
    {
        SAWindowButtonGroup* par = q_ptr;

        if (on) {
            if (buttonMaximize) {
                buttonMaximize->deleteLater();
                buttonMaximize = nullptr;
            }
            buttonMaximize = new SAWindowToolButton(par);
            buttonMaximize->setObjectName(QStringLiteral("SAMaximizeWindowButton"));
            buttonMaximize->setFixedSize(30, RibbonSubElementStyleOpt.titleBarHeight() - 2);
            buttonMaximize->setCheckable(true);
            buttonMaximize->setFocusPolicy(Qt::NoFocus);  //������ץ��
            buttonMaximize->setIconSize(buttonMaximize->size() * mIconscale);
            buttonMaximize->show();
            par->connect(buttonMaximize, &QAbstractButton::clicked, par, &SAWindowButtonGroup::maximizeWindow);
        } else {
            if (buttonMaximize) {
                delete buttonMaximize;
                buttonMaximize = nullptr;
            }
        }
        updateSize();
    }

    void setupCloseButton(bool on)
    {
        SAWindowButtonGroup* par = q_ptr;

        if (on) {
            if (buttonClose) {
                buttonClose->deleteLater();
                buttonClose = nullptr;
            }
            buttonClose = new SAWindowToolButton(par);
            buttonClose->setObjectName(QStringLiteral("SACloseWindowButton"));
            buttonClose->setFixedSize(40, RibbonSubElementStyleOpt.titleBarHeight() - 2);
            buttonClose->setFocusPolicy(Qt::NoFocus);  //������ץ��
            // buttonClose->setFlat(true);
            par->connect(buttonClose, &QAbstractButton::clicked, par, &SAWindowButtonGroup::closeWindow);
            buttonClose->setIconSize(buttonClose->size() * mIconscale);
            buttonClose->show();
        } else {
            if (buttonClose) {
                delete buttonClose;
                buttonClose = nullptr;
            }
        }
        updateSize();
    }

    void updateSize()
    {
        q_ptr->setFixedSize(sizeHint());
        resize(q_ptr->size());
        //        int span = 0;

        //        if (buttonClose) {
        //            buttonClose->move(q_d->width()-buttonClose->width()
        //                , q_d->y());
        //            span = buttonClose->width();
        //        }
        //        if (buttonMaximize) {
        //            buttonMaximize->move(q_d->width()-buttonMaximize->width()-span
        //                , q_d->y());
        //            span += buttonMaximize->width();
        //        }
        //        if (buttonMinimize) {
        //            buttonMinimize->move(q_d->width()-buttonMinimize->width()-span
        //                , q_d->y());
        //        }
    }

    void resize(QSize size)
    {
        qreal tw = 0;

        if (buttonClose) {
            tw += mCloseStretch;
        }
        if (buttonMaximize) {
            tw += mMaxStretch;
        }
        if (buttonMinimize) {
            tw += mMinStretch;
        }
        //������ť

        int x = 0;

        if (buttonMinimize) {
            int w = (mMinStretch / tw) * size.width();
            // buttonMinimize->setGeometry(x, 0, w, size.height());
            //�ܵ�qss��ʽӰ��ᵼ����С��ȡ��߶����ò��ˣ����Ҫ����fixsize��move
            buttonMinimize->setFixedSize(w, size.height());
            buttonMinimize->move(x, 0);
            x += w;
        }
        if (buttonMaximize) {
            int w = (mMaxStretch / tw) * size.width();
            // buttonMaximize->setGeometry(x, 0, w, size.height());
            //�ܵ�qss��ʽӰ��ᵼ����С��ȡ��߶����ò��ˣ����Ҫ����fixsize��move
            buttonMaximize->setFixedSize(w, size.height());
            buttonMaximize->move(x, 0);
            x += w;
        }
        if (buttonClose) {
            int w = (mCloseStretch / tw) * size.width();
            // buttonClose->setGeometry(x, 0, w, size.height());
            //�ܵ�qss��ʽӰ��ᵼ����С��ȡ��߶����ò��ˣ����Ҫ����fixsize��move
            buttonClose->setFixedSize(w, size.height());
            buttonClose->move(x, 0);
        }
    }

    QSize sizeHint() const
    {
        int width  = 0;
        int height = RibbonSubElementStyleOpt.titleBarHeight();

        if (buttonClose) {
            width += 40;
        }
        if (buttonMaximize) {
            width += 30;
        }
        if (buttonMinimize) {
            width += 30;
        }
        return (QSize(width, height));
    }
};

//===================================================
// SAWindowToolButton
//===================================================
SAWindowToolButton::SAWindowToolButton(QWidget* p) : QPushButton(p)
{
    setFlat(true);
}

SAWindowButtonGroup::SAWindowButtonGroup(QWidget* parent)
    : QWidget(parent), d_ptr(new SAWindowButtonGroup::PrivateData(this))
{
    updateWindowFlag();
    if (parent) {
        parent->installEventFilter(this);
    }
}

/**
 * @brief ���캯����ǿ��ʹ��flags����������parent��flags���й���
 * @param parent
 * @param flags
 */
SAWindowButtonGroup::SAWindowButtonGroup(QWidget* parent, Qt::WindowFlags flags)
    : QWidget(parent), d_ptr(new SAWindowButtonGroup::PrivateData(this))
{
    d_ptr->mFlags = flags;
    updateWindowFlag();
    if (parent) {
        parent->installEventFilter(this);
    }
}

SAWindowButtonGroup::~SAWindowButtonGroup()
{
}

void SAWindowButtonGroup::setupMinimizeButton(bool on)
{
    d_ptr->setupMinimizeButton(on);
}

void SAWindowButtonGroup::setupMaximizeButton(bool on)
{
    d_ptr->setupMaximizeButton(on);
}

void SAWindowButtonGroup::setupCloseButton(bool on)
{
    d_ptr->setupCloseButton(on);
}

void SAWindowButtonGroup::updateWindowFlag()
{
    Qt::WindowFlags flags = parentWidget()->windowFlags();

    d_ptr->mFlags = flags;

    setupMinimizeButton(flags & Qt::WindowMinimizeButtonHint);

    setupMaximizeButton(flags & Qt::WindowMaximizeButtonHint);

    setupCloseButton(flags & Qt::WindowCloseButtonHint);
}

/**
 * @brief �˺��������ڿ�����С��󻯺͹رհ�ť����ʾ
 * @param flags
 */
void SAWindowButtonGroup::updateWindowFlag(Qt::WindowFlags flags)
{
    if (flags & Qt::WindowCloseButtonHint) {
        d_ptr->mFlags |= Qt::WindowCloseButtonHint;
    } else {
        d_ptr->mFlags &= (~Qt::WindowCloseButtonHint);
    }

    if (flags & Qt::WindowMaximizeButtonHint) {
        d_ptr->mFlags |= Qt::WindowMaximizeButtonHint;
    } else {
        d_ptr->mFlags &= (~Qt::WindowMaximizeButtonHint);
    }

    if (flags & Qt::WindowMinimizeButtonHint) {
        d_ptr->mFlags |= Qt::WindowMinimizeButtonHint;
    } else {
        d_ptr->mFlags &= (~Qt::WindowMinimizeButtonHint);
    }
    setupMinimizeButton(flags & Qt::WindowMinimizeButtonHint);

    setupMaximizeButton(flags & Qt::WindowMaximizeButtonHint);

    setupCloseButton(flags & Qt::WindowCloseButtonHint);
}

/**
 * @brief ���ð�ť�Ŀ�ȱ���,���հ�ť��Ƚ����մ˱�����������
 * @param close �رհ�ť����
 * @param max ��󻯰�ť����
 * @param min ��С����ť����
 */
void SAWindowButtonGroup::setButtonWidthStretch(int close, int max, int min)
{
    d_ptr->mMaxStretch   = max;
    d_ptr->mMinStretch   = min;
    d_ptr->mCloseStretch = close;
}

/**
 * @brief ���ð�ť�����ű���
 * @param iconscale ��ֵԽС��ťԽС
 */
void SAWindowButtonGroup::setIconScale(qreal iconscale)
{
    d_ptr->mIconscale = iconscale;
}

/**
 * @brief ���ô���״̬�������С����ť״̬��
 * @param s
 */
void SAWindowButtonGroup::setWindowStates(Qt::WindowStates s)
{
    if (d_ptr->buttonMaximize) {
        bool on = s.testFlag(Qt::WindowMaximized);
        d_ptr->buttonMaximize->setChecked(on);
        d_ptr->buttonMaximize->setToolTip(on ? tr("Restore") : tr("Maximize"));
    }
}

/**
 * @brief �˺������ص�flags������ Qt::WindowCloseButtonHint��Qt::WindowMaximizeButtonHint��Qt::WindowMinimizeButtonHint
 * ����
 *
 * @return
 */
Qt::WindowFlags SAWindowButtonGroup::windowButtonFlags() const
{
    Qt::WindowFlags f = Qt::Widget;  // widget��000

    if (d_ptr->mFlags & Qt::WindowCloseButtonHint) {
        f |= Qt::WindowCloseButtonHint;
    }
    if (d_ptr->mFlags & Qt::WindowMaximizeButtonHint) {
        f |= Qt::WindowMaximizeButtonHint;
    }
    if (d_ptr->mFlags & Qt::WindowMinimizeButtonHint) {
        f |= Qt::WindowMinimizeButtonHint;
    }
    return (f);
}

QSize SAWindowButtonGroup::sizeHint() const
{
    return (d_ptr->sizeHint());
}

bool SAWindowButtonGroup::eventFilter(QObject* watched, QEvent* e)
{
    //���ڼ��������ڸı�ߴ�
    if (watched == parentWidget()) {
        switch (e->type()) {
        case QEvent::Resize:
            parentResize();
            break;

        default:
            break;
        }
    }
    return (false);  //���ض��κ��¼�
}

void SAWindowButtonGroup::parentResize()
{
    QWidget* par = parentWidget();

    if (par) {
        QSize parSize = par->size();
        move(parSize.width() - width() - 1, 0);
    }
}

void SAWindowButtonGroup::resizeEvent(QResizeEvent* e)
{
    d_ptr->resize(e->size());
}

void SAWindowButtonGroup::closeWindow()
{
    if (parentWidget()) {
        parentWidget()->close();
    }
}

void SAWindowButtonGroup::minimizeWindow()
{
    if (parentWidget()) {
        parentWidget()->showMinimized();
    }
}

void SAWindowButtonGroup::maximizeWindow()
{
    QWidget* par = parentWidget();

    if (par) {
        if (par->isMaximized()) {
            par->showNormal();
        } else {
            par->showMaximized();
        }
    }
}

/*** End of inlined file: SAWindowButtonGroup.cpp ***/

/*** Start of inlined file: SARibbonToolButton.cpp ***/
#include <QApplication>
#include <QStylePainter>
#include <QStyleOptionToolButton>
#include <QAction>
#include <QStyleOptionFocusRect>
#include <QStyleOption>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QCursor>
#include <QTextOption>

/**
 * @def �������ֻ���ʱ2���ı��ľ��θ߶�ϵ������ϵ��������������ĸ߶�
 *
 * fontMetrics.lineSpacing*ϵ�� = �ı�����߶�
 */
#define SARIBBONTOOLBUTTON_WORDWRAP_TEXT_FACTOR 2.05

/**
 * @def �������ֲ�����ʱ�����ı��ľ��θ߶�ϵ������ϵ��������������ĸ߶�
 *
 * fontMetrics.lineSpacing*ϵ�� = �ı�����߶�
 */
#define SARIBBONTOOLBUTTON_NOWORDWRAP_TEXT_FACTOR 1.2

/**
 * @def ����С��ť�ľ��θ߶�ϵ������ϵ��������������ĸ߶�
 *
 * fontMetrics.lineSpacing*ϵ�� = �ı�����߶�
 */
#define SARIBBONTOOLBUTTON_SMALLBUTTON_TEXT_FACTOR 1.4

/**
 * @def �ı���ȹ���ʱ�Ŀ�ȱȸ߶�ϵ��
 *
 * ������ϵ���Ŀ��ʱ����ʼ���Ի��У����簴ť�߶�Ϊh����������ı��Ŀ�ȴ���h*ϵ�����򴥷����й���
 */
#define SARIBBONTOOLBUTTON_WORDWRAP_WIDTH_PER_HEIGHT_RATIO 1.4

/**
 * @def �����˺���ӡһЩ������Ϣ
 */
#define SA_RIBBON_TOOLBUTTON_DEBUG_PRINT 0

#define SARIBBONTOOLBUTTON_DEBUG_DRAW 0

#if SARIBBONTOOLBUTTON_DEBUG_DRAW
#define SARIBBONTOOLBUTTON_DEBUG_DRAW_RECT(p, rect)                                                                    \
    do {                                                                                                               \
        p.save();                                                                                                      \
        p.setPen(Qt::red);                                                                                             \
        p.setBrush(QBrush());                                                                                          \
        p.drawRect(rect);                                                                                              \
        p.restore();                                                                                                   \
    } while (0)

#else
#define SARIBBONTOOLBUTTON_DEBUG_DRAW_RECT(p, rect)
#endif
namespace SA
{

QDebug operator<<(QDebug debug, const QStyleOptionToolButton& opt)
{
    debug << "=============="
          << "\nQStyleOption(" << (QStyleOption)opt << ")"
          << "\n  QStyleOptionComplex:"
             "\n     subControls("
          << opt.subControls
          << " ) "
             "\n     activeSubControls("
          << opt.activeSubControls
          << "\n  QStyleOptionToolButton"
             "\n     features("
          << opt.features
          << ")"
             "\n     toolButtonStyle("
          << opt.toolButtonStyle << ")";

    return (debug);
}

}
//===================================================
// SARibbonToolButton::PrivateData
//===================================================

class SARibbonToolButton::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonToolButton)
public:
    PrivateData(SARibbonToolButton* p);
    //�������λ�ø��°�ť����Ϣ
    void updateStatusByMousePosition(const QPoint& pos);
    //���»�ͼ��صĳߴ�
    void updateDrawRect(const QStyleOptionToolButton& opt);
    //����SizeHint
    void updateSizeHint(const QStyleOptionToolButton& opt);
    //�����漰����rect�ߴ�
    void calcDrawRects(const QStyleOptionToolButton& opt, QRect& iconRect, QRect& textRect, QRect& indicatorArrowRect, int spacing, int indicatorLen) const;
    //����С��ťģʽ�µĳߴ�
    void calcSmallButtonDrawRects(const QStyleOptionToolButton& opt,
                                  QRect& iconRect,
                                  QRect& textRect,
                                  QRect& indicatorArrowRect,
                                  int spacing,
                                  int indicatorLen) const;
    //�����ťģʽ�µĳߴ�
    void calcLargeButtonDrawRects(const QStyleOptionToolButton& opt,
                                  QRect& iconRect,
                                  QRect& textRect,
                                  QRect& indicatorArrowRect,
                                  int spacing,
                                  int indicatorLen) const;
    //���ݰ�ť�ĳߴ����iconsize(ע�������buttonRect���Ѿ���ȥmSpacing�����)
    QSize adjustIconSize(const QRect& buttonRect, const QSize& originIconSize) const;
    //�ж��Ƿ���Indicator
    bool hasIndicator(const QStyleOptionToolButton& opt) const;
    //����sizehint
    QSize calcSizeHint(const QStyleOptionToolButton& opt);
    QSize calcSmallButtonSizeHint(const QStyleOptionToolButton& opt);
    QSize calcLargeButtonSizeHint(const QStyleOptionToolButton& opt);

    //�����ı����ƾ��εĸ߶�
    int calcTextDrawRectHeight(const QStyleOptionToolButton& opt) const;
    //����һ�����ŵ��ı����
    int estimateLargeButtonTextWidth(int buttonHeight,
                                     int textDrawRectHeight,
                                     const QString& text,
                                     const QFontMetrics& fm,
                                     float widthHeightRatio = SARIBBONTOOLBUTTON_WORDWRAP_WIDTH_PER_HEIGHT_RATIO,
                                     int maxTrycount        = 3);
    QPixmap createIconPixmap(const QStyleOptionToolButton& opt, const QSize& iconsize) const;
    //��ȡ���ֵĶ��䷽ʽ
    int getTextAlignment() const;
    //ȷ�������Ƿ�ȷ��Ҫ������ʾ
    bool isTextNeedWrap() const;
    //������\n�����޳�����QString::simplified��һ��
    static QString simplified(const QString& str);

public:
    bool mMouseOnSubControl { false };  ///< ������ڱ��MenuButtonPopupģʽ�£�������ı�����
    bool mMenuButtonPressed { false };  ///< ����Indicator�ı䣬���hitButton������QToolButton��hitButton
    bool mWordWrap { false };           ///< ����Ƿ����ֻ��� @default false
    SARibbonToolButton::RibbonButtonType mButtonType { SARibbonToolButton::LargeButton };
    int mSpacing { 1 };              ///< ��ť�ͱ߿�ľ���
    int mIndicatorLen { 8 };         ///< Indicator�ĳ���
    QRect mDrawIconRect;             ///< ��¼icon�Ļ���λ��
    QRect mDrawTextRect;             ///< ��¼text�Ļ���λ��
    QRect mDrawIndicatorArrowRect;   ///< ��¼IndicatorArrow�Ļ���λ��
    QSize mSizeHint;                 ///< �������õ�sizehint
    bool mIsTextNeedWrap { false };  ///< ��������Ƿ���Ҫ������ʾ
public:
    static bool s_enableWordWrap;  ///< ��liteģʽ���Ƿ��������ֻ��У����������ͼ����ԱȽ�С��Ĭ�ϲ�����
};

//��̬������ʼ��
bool SARibbonToolButton::PrivateData::s_enableWordWrap = false;

SARibbonToolButton::PrivateData::PrivateData(SARibbonToolButton* p) : q_ptr(p)
{
}

/**
 * @brief ��������λ�ø���״̬����Ҫ�����ж�����Ƿ�λ��subcontrol
 *
 * �˺�����ҪӦ����action menuģʽ��
 * @param pos
 */
void SARibbonToolButton::PrivateData::updateStatusByMousePosition(const QPoint& pos)
{
    bool isMouseOnSubControl(false);
    if (SARibbonToolButton::LargeButton == mButtonType) {
        isMouseOnSubControl = mDrawTextRect.united(mDrawIndicatorArrowRect).contains(pos);
    } else {
        //С��ťģʽ�ͺ���ͨtoolbuttonһ��
        isMouseOnSubControl = mDrawIndicatorArrowRect.contains(pos);
    }

    if (mMouseOnSubControl != isMouseOnSubControl) {
        mMouseOnSubControl = isMouseOnSubControl;
        //��icon�䵽text������ˢ��һ��
        q_ptr->update();
    }
}

/**
 * @brief ���»�ͼ�ļ����ؼ��ߴ�
 *
 * ������
 *
 * - DrawIconRect ����ͼ��ľ�������
 *
 * - DrawTextRect �����ı��ľ�������
 *
 * - DrawIndicatorArrowRect ���Ʋ˵��¼�ͷ�ľ�������
 *
 * @param opt
 */
void SARibbonToolButton::PrivateData::updateDrawRect(const QStyleOptionToolButton& opt)
{
    if (!mSizeHint.isValid()) {
        updateSizeHint(opt);
    }
    //�ȸ���IndicatorLen
    mIndicatorLen = q_ptr->style()->pixelMetric(QStyle::PM_MenuButtonIndicator, &opt, q_ptr);
    if (mIndicatorLen < 3) {
        if (SARibbonToolButton::LargeButton == mButtonType) {
            mIndicatorLen = 8;
        } else {
            mIndicatorLen = 12;  //С��ťģʽ������Ϊ10
        }
    }
    calcDrawRects(opt, mDrawIconRect, mDrawTextRect, mDrawIndicatorArrowRect, mSpacing, mIndicatorLen);
}

/**
 * @brief ����sizehint
 * @param opt
 */
void SARibbonToolButton::PrivateData::updateSizeHint(const QStyleOptionToolButton& opt)
{
    mSizeHint = calcSizeHint(opt);
}

/**
 * @brief �����ͼ�ļ����ؼ�����
 * @param opt
 * @param iconRect  ����ͼ��ľ�������
 * @param textRect �����ı��ľ�������
 * @param indicatorArrowRect ���Ʋ˵��¼�ͷ�ľ�������
 * @param spacing
 * @param indicatorLen
 */
void SARibbonToolButton::PrivateData::calcDrawRects(const QStyleOptionToolButton& opt,
                                                    QRect& iconRect,
                                                    QRect& textRect,
                                                    QRect& indicatorArrowRect,
                                                    int spacing,
                                                    int indicatorLen) const
{
    if (SARibbonToolButton::LargeButton == mButtonType) {
        calcLargeButtonDrawRects(opt, iconRect, textRect, indicatorArrowRect, spacing, indicatorLen);

    } else {
        calcSmallButtonDrawRects(opt, iconRect, textRect, indicatorArrowRect, spacing, indicatorLen);
    }
}

/**
 * @brief ����С��ťģʽ�µĻ��Ƴߴ�
 * @param opt
 * @param iconRect
 * @param textRect
 * @param indicatorArrowRect
 * @param spacing
 * @param indicatorLen
 */
void SARibbonToolButton::PrivateData::calcSmallButtonDrawRects(const QStyleOptionToolButton& opt,
                                                               QRect& iconRect,
                                                               QRect& textRect,
                                                               QRect& indicatorArrowRect,
                                                               int spacing,
                                                               int indicatorLen) const
{
    switch (opt.toolButtonStyle) {
    case Qt::ToolButtonIconOnly: {
        if (hasIndicator(opt)) {
            // �ڽ���ͼ���Сģʽ��ʾʱ��Ԥ��һ��������ͷλ��
            iconRect           = opt.rect.adjusted(spacing, spacing, -indicatorLen - spacing, -spacing);
            indicatorArrowRect = QRect(opt.rect.right() - indicatorLen - spacing, iconRect.y(), indicatorLen, iconRect.height());
        } else {
            iconRect           = opt.rect.adjusted(spacing, spacing, -spacing, -spacing);
            indicatorArrowRect = QRect();
        }
        //�ı�����Ϊ��
        textRect = QRect();
    } break;
    case Qt::ToolButtonTextOnly: {
        if (hasIndicator(opt)) {
            // �ڽ���ͼ���Сģʽ��ʾʱ��Ԥ��һ��������ͷλ��
            textRect           = opt.rect.adjusted(spacing, spacing, -indicatorLen - spacing, -spacing);
            indicatorArrowRect = QRect(opt.rect.right() - indicatorLen - spacing, spacing, indicatorLen, textRect.height());
        } else {
            textRect           = opt.rect.adjusted(spacing, spacing, -spacing, -spacing);
            indicatorArrowRect = QRect();
        }
        //��ͼ����Ϊ��
        iconRect = QRect();
    } break;
    default: {
        bool hasInd = hasIndicator(opt);
        // icon Beside��under����һ����
        QRect buttonRect = q_ptr->rect();
        buttonRect.adjust(spacing, spacing, -spacing, -spacing);
        //������IconRect
        if (opt.icon.isNull()) {
            //û��ͼ��
            iconRect = QRect();
        } else {
            QSize iconSize = adjustIconSize(buttonRect, opt.iconSize);
            iconRect = QRect(buttonRect.x(), buttonRect.y(), iconSize.width(), qMax(iconSize.height(), buttonRect.height()));
        }
        //������TextRect
        if (opt.text.isEmpty()) {
            textRect = QRect();
        } else {
            //���в˵���û�˵��������
            int adjx = iconRect.isValid() ? (iconRect.width() + spacing) : 0;  //��buttonRect�ϱ任��������û��ͼ���ǲ���ƫ��spacing
            if (hasInd) {
                textRect = buttonRect.adjusted(adjx, 0, -indicatorLen, 0);
            } else {
                textRect = buttonRect.adjusted(adjx, 0, 0, 0);  //��buttonRect�ϱ任��������û��ͼ���ǲ���ƫ��spacing
            }
        }
        //�������Indicator
        if (hasInd) {
            if (textRect.isValid()) {
                indicatorArrowRect = QRect(buttonRect.right() - indicatorLen + 1, textRect.y(), indicatorLen, textRect.height());
            } else if (iconRect.isValid()) {
                indicatorArrowRect = QRect(buttonRect.right() - indicatorLen + 1, iconRect.y(), indicatorLen, iconRect.height());
            } else {
                indicatorArrowRect = buttonRect;
            }
        } else {
            indicatorArrowRect = QRect();
        }
    }
    }
}

/**
 * @brief �����ťģʽ�µĻ��Ƴߴ磨��ͨ��
 * @param opt
 * @param iconRect
 * @param textRect
 * @param indicatorArrowRect
 * @param spacing
 * @param indicatorLen
 */
void SARibbonToolButton::PrivateData::calcLargeButtonDrawRects(const QStyleOptionToolButton& opt,
                                                               QRect& iconRect,
                                                               QRect& textRect,
                                                               QRect& indicatorArrowRect,
                                                               int spacing,
                                                               int indicatorLen) const
{
    //! 3��ģʽ��ͼ��Ƚϴ����ֻ�������£�indicator�ᶯ̬����
    //�Ȼ�ȡ���־��εĸ߶�
    int textHeight  = calcTextDrawRectHeight(opt);
    bool hIndicator = hasIndicator(opt);
    if (!hIndicator) {
        //û�в˵�����len����Ϊ0
        indicatorLen       = 0;
        indicatorArrowRect = QRect();
    }
    //����Ҫ�ж������Ƿ�Ҫ������ʾ��������ʾ�����ֵ�indicatorArrowRect������λ�ò�һ��
    //�Ȳ���textRect
    if (isEnableWordWrap()) {
        //�ڻ���ģʽ��
        if (isTextNeedWrap()) {
            //������ֵ�ȷ���У�indicator�������ұ�
            textRect = QRect(spacing, opt.rect.bottom() - spacing - textHeight, opt.rect.width() - 2 * spacing - indicatorLen, textHeight);
            if (hIndicator) {
                indicatorArrowRect = QRect(textRect.right(), textRect.y() + textRect.height() / 2, indicatorLen, textHeight / 2);
            }
        } else {
            //������ֲ���Ҫ���У�indicator���°���
            textRect = QRect(spacing, opt.rect.bottom() - spacing - textHeight, opt.rect.width() - 2 * spacing, textHeight);
            if (hIndicator) {
                int dy = textRect.height() / 2;
                dy += (dy - indicatorLen) / 2;
                indicatorArrowRect = QRect(textRect.x(), textRect.y() + dy, textRect.width(), indicatorLen);
            }
        }
    } else {
        //���ֲ����У�indicator�������ұ�
        int y = opt.rect.bottom() - spacing - textHeight;
        if (hIndicator) {
            //�Ȳ���indicator
            indicatorArrowRect = QRect(opt.rect.right() - indicatorLen - spacing, y, indicatorLen, textHeight);
            textRect           = QRect(spacing, y, indicatorArrowRect.x() - spacing, textHeight);
        } else {
            textRect = QRect(spacing, y, opt.rect.width() - 2 * spacing, textHeight);
        }
    }
    //ʣ�¾���icon����
    iconRect = QRect(spacing, spacing, opt.rect.width() - 2 * spacing, textRect.top() - 2 * spacing);
}

/**
 * @brief ��Ӧiconsize
 * @param buttonRect
 * @param originIconSize
 * @return
 */
QSize SARibbonToolButton::PrivateData::adjustIconSize(const QRect& buttonRect, const QSize& originIconSize) const
{
    QSize iconSize = originIconSize;
    if (iconSize.height() > buttonRect.height()) {
        //˵��ͼ���icon����Ҫƥ�䵽buttonRect
        iconSize.setHeight(buttonRect.height());
        //�ȱ������ÿ��
        iconSize.setWidth(originIconSize.width() * iconSize.height() / originIconSize.height());
    }
    return iconSize;
}

/**
 * @brief �ж��Ƿ���Indicator
 * @param opt
 * @return
 */
bool SARibbonToolButton::PrivateData::hasIndicator(const QStyleOptionToolButton& opt) const
{
    return ((opt.features & QStyleOptionToolButton::MenuButtonPopup) || (opt.features & QStyleOptionToolButton::HasMenu));
}

/**
 * @brief ����sizehint
 *
 * �˺����ǳ��ؼ�����Ϊ���гߴ���㶼�ǻ���ԭʼ��rect����
 * @param opt
 * @return
 */
QSize SARibbonToolButton::PrivateData::calcSizeHint(const QStyleOptionToolButton& opt)
{
    if (SARibbonToolButton::LargeButton == mButtonType) {
        return calcLargeButtonSizeHint(opt);
    }
    return calcSmallButtonSizeHint(opt);
}

QSize SARibbonToolButton::PrivateData::calcSmallButtonSizeHint(const QStyleOptionToolButton& opt)
{
    int w = 0, h = 0;

    switch (opt.toolButtonStyle) {
    case Qt::ToolButtonIconOnly: {
        w = opt.iconSize.width() + 2 * mSpacing;
        h = opt.iconSize.height() + 2 * mSpacing;
    } break;
    case Qt::ToolButtonTextOnly: {
        QSize textSize = opt.fontMetrics.size(Qt::TextShowMnemonic, simplified(opt.text));
        textSize.setWidth(textSize.width() + SA_FONTMETRICS_WIDTH(opt.fontMetrics, (QLatin1Char(' '))) * 2);
        textSize.setHeight(calcTextDrawRectHeight(opt));
        w = textSize.width() + 2 * mSpacing;
        h = textSize.height() + 2 * mSpacing;
    } break;
    default: {
        //�ȼ���icon�ĳߴ�
        w = opt.iconSize.width() + 2 * mSpacing;
        h = opt.iconSize.height() + 2 * mSpacing;
        //�ټ����ı��ĳ���
        if (!opt.text.isEmpty()) {
            QSize textSize = opt.fontMetrics.size(Qt::TextShowMnemonic, simplified(opt.text));
            textSize.setWidth(textSize.width() + SA_FONTMETRICS_WIDTH(opt.fontMetrics, (QLatin1Char(' '))) * 2);
            textSize.setHeight(calcTextDrawRectHeight(opt));
            w += mSpacing;
            w += textSize.width();
            h = qMax(h, (textSize.height() + (2 * mSpacing)));
        } else {
            //û���ı���ʱ��ҲҪ����һ�¸߶�
            QSize textSize = opt.fontMetrics.size(Qt::TextShowMnemonic, " ");
            h              = qMax(h, (textSize.height() + (2 * mSpacing)));
        }
    }
    }
    if (hasIndicator(opt)) {
        //����indicator�İ�ť����ȳߴ�Ҫ��չ
        w += mIndicatorLen;
    }
    if (w < 16) {
        w = 16;
    }
    //! Qt6.4 ȡ����QApplication::globalStrut
    return QSize(w, h).expandedTo(QSize(2, 2));
}

QSize SARibbonToolButton::PrivateData::calcLargeButtonSizeHint(const QStyleOptionToolButton& opt)
{
    int w = 0, h = opt.fontMetrics.lineSpacing() * 4.5;  // 3*1.5
    if (SARibbonPannel* pannel = qobject_cast< SARibbonPannel* >(q_ptr->parent())) {
        //���ڽ�����SARibbonPannel�Ļ����ϵĴ�ť���Ѹ߶�����ΪSARibbonPannel����Ĵ�ť�߶�
        h = pannel->largeHeight();
    }
    //��������Ŀ����Ϊ���
    w = estimateLargeButtonTextWidth(h, calcTextDrawRectHeight(opt), opt.text, opt.fontMetrics);
    w += (2 * mSpacing);
    //�ж��Ƿ���Ҫ����indicator
    if (isEnableWordWrap() && isTextNeedWrap()) {
        w += mIndicatorLen;
    }

    if (w < 22) {
        w = 22;
    }
    //! Qt6.4 ȡ����QApplication::globalStrut
    return QSize(w, h).expandedTo(QSize(2, 2));
}

/**
 * @brief �����ı��߶�
 * @param opt
 * @return
 */
int SARibbonToolButton::PrivateData::calcTextDrawRectHeight(const QStyleOptionToolButton& opt) const
{
    if (SARibbonToolButton::LargeButton == mButtonType) {
        if (isEnableWordWrap()) {
            return opt.fontMetrics.lineSpacing() * SARIBBONTOOLBUTTON_WORDWRAP_TEXT_FACTOR;
        } else {
            return opt.fontMetrics.lineSpacing() * SARIBBONTOOLBUTTON_NOWORDWRAP_TEXT_FACTOR;
        }
    }
    //С��ť
    return opt.fontMetrics.lineSpacing() * SARIBBONTOOLBUTTON_SMALLBUTTON_TEXT_FACTOR;
}

/**
 * @brief ����һ�����ŵ����ֳߴ磬�ڿ��Ի��е�����»���л��У���ֻ�ỻһ��
 * @param buttonHeight ��ť�ĸ߶�
 * @param textDrawRectHeight �ı����Ƶĸ߶�
 * @param fm QFontMetrics
 * @param widthHeightRatio ��߱ȣ����/�߶ȵı�ֵ��������������ֵ�������г��Ի����Ի�ȡ���͵Ŀ��
 * @param maxTrycount ���Դ���
 * @return
 */
int SARibbonToolButton::PrivateData::estimateLargeButtonTextWidth(int buttonHeight,
                                                                  int textDrawRectHeight,
                                                                  const QString& text,
                                                                  const QFontMetrics& fm,
                                                                  float widthHeightRatio,
                                                                  int maxTrycount)
{

    QSize textSize;
    int space        = SA_FONTMETRICS_WIDTH(fm, (QLatin1Char(' '))) * 2;
    int hintMaxWidth = buttonHeight * widthHeightRatio;  ///< ����Ŀ��
    if (isEnableWordWrap()) {
        textSize = fm.size(Qt::TextShowMnemonic, text);
        textSize.setWidth(textSize.width() + space);

        if (textSize.height() > fm.lineSpacing() * 1.1) {
            //! ˵�����ִ��л��з������û��ֶ����У����������ֱ�ӷ�������ߴ磬�����й���
            mIsTextNeedWrap = true;  // ������Ҫ������ʾ���������
            return textSize.width();
        }

        //��ʱ����Ҫ�����ı��ĳ���
        if (textSize.width() <= hintMaxWidth) {
            //��Χ����ֱ�ӷ���
            mIsTextNeedWrap = false;  // ���ֲ���Ҫ������ʾ���������
            return textSize.width();
        }

        //! ���ڿ�߱ȳ��Խ������ֻ���
        //! �����ȶ��ı������𽥼ӳ����㣬һֱ����ԭ������һ��Ϊֹ
        int trycount  = 0;
        int alignment = Qt::TextShowMnemonic | Qt::TextWordWrap;
        //����Ӣ�����壬ֱ�ӿ�ȼ������޷�������ȫ��ʾ���еģ���Ҫ����Ԥ��
        QRect textRect(0, 0, textSize.width(), textDrawRectHeight);
        do {
            //! �ȼ��������ı��Ľ��վ���
            //! ��һ�뿪ʼ�𽥵���
            //! ��1��Ϊ w/2 + w/2 * (0/3)
            //! ��2��Ϊ w/2 + w/2 * (1/3)
            //! ��3��Ϊ w/2 + w/2 * (2/3)
            textRect.setWidth(textSize.width() / 2 + (textSize.width() / 2) * (float(trycount) / maxTrycount));
            textRect = fm.boundingRect(textRect, alignment, text);
            if (textRect.height() <= (fm.lineSpacing() * 2)) {
                //��֤������
                mIsTextNeedWrap = true;  // ������Ҫ������ʾ���������
                return textRect.width();
            }
            ++trycount;
#if SARIBBONTOOLBUTTON_DEBUG_DRAW
            if (trycount > 1) {
                qDebug() << "estimateLargeButtonTextWidth,origin textSize=" << textSize << ",trycount=" << trycount
                         << ",textRect=" << textRect;
            }
#endif
        } while (trycount < 3);
        //������˵��ǰ��ĳ���ʧ�ܣ�����ʹ��ԭʼ�ĳ���
        return textSize.width();
    }

    //! ˵���ǲ�����

    mIsTextNeedWrap = false;  // ���ֲ���Ҫ������ʾ���������
    //���ֲ���������£���simplified����
    textSize = fm.size(Qt::TextShowMnemonic, simplified(text));
    textSize.setWidth(textSize.width() + space);
    if (textSize.width() < hintMaxWidth) {
        //��Χ����ֱ�ӷ���
        return textSize.width();
    }
    if (textSize.width() > q_ptr->maximumWidth()) {
        //�����˼��ޣ��ͷ��ؼ���
        return q_ptr->maximumWidth();
    }
    return hintMaxWidth;
}

QPixmap SARibbonToolButton::PrivateData::createIconPixmap(const QStyleOptionToolButton& opt, const QSize& iconsize) const
{
    if (opt.icon.isNull()) {  //û����ͼ��
        return (QPixmap());
    }
    QIcon::State state = (opt.state & QStyle::State_On) ? QIcon::On : QIcon::Off;
    QIcon::Mode mode;
    if (!(opt.state & QStyle::State_Enabled)) {
        mode = QIcon::Disabled;
    } else if ((opt.state & QStyle::State_MouseOver) && (opt.state & QStyle::State_AutoRaise)) {
        mode = QIcon::Active;
    } else {
        mode = QIcon::Normal;
    }
    return (opt.icon.pixmap(iconsize - QSize(2, 2), mode, state));
}

int SARibbonToolButton::PrivateData::getTextAlignment() const
{
    int alignment = Qt::TextShowMnemonic;
    if (SARibbonToolButton::LargeButton == mButtonType) {
        if (isEnableWordWrap()) {
            alignment |= Qt::TextWordWrap | Qt::AlignTop | Qt::AlignHCenter;  //���е�����£���������
        } else {
            alignment |= Qt::AlignCenter;
        }
    } else {
        alignment |= Qt::AlignCenter;
    }
    return alignment;
}

/**
 * @brief ȷ�������Ƿ�ȷ��Ҫ������ʾ
 * @return
 */
bool SARibbonToolButton::PrivateData::isTextNeedWrap() const
{
    return mIsTextNeedWrap;
}

/**
 * @brief ������\n�����޳�
 * @param str
 * @return
 */
QString SARibbonToolButton::PrivateData::simplified(const QString& str)
{
    QString res = str;
    res.remove('\n');
    return res;
}
//===================================================
// SARibbonToolButton
//===================================================

SARibbonToolButton::SARibbonToolButton(QWidget* parent)
    : QToolButton(parent), d_ptr(new SARibbonToolButton::PrivateData(this))
{
    setAutoRaise(true);
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setButtonType(SmallButton);
    setMouseTracking(true);
}

SARibbonToolButton::SARibbonToolButton(QAction* defaultAction, QWidget* parent)
    : QToolButton(parent), d_ptr(new SARibbonToolButton::PrivateData(this))
{
    setAutoRaise(true);
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setDefaultAction(defaultAction);
    setButtonType(SmallButton);
    setMouseTracking(true);
}

SARibbonToolButton::~SARibbonToolButton()
{
}

/**
 * @brief ����ƶ��¼�
 *
 * ����Ribbon��Indicator��������Toolbutton��һ��������޷���QStyleOptionToolButton��activeSubControls��״̬
 *
 * �����Ҫ���²�������λ�������°�ť��ǰ��һЩ״̬
 * @param e
 */
void SARibbonToolButton::mouseMoveEvent(QMouseEvent* e)
{
    d_ptr->updateStatusByMousePosition(e->pos());
    QToolButton::mouseMoveEvent(e);
}

/**
 * @brief SARibbonToolButton::mousePressEvent
 * @param e
 */
void SARibbonToolButton::mousePressEvent(QMouseEvent* e)
{
    if ((e->button() == Qt::LeftButton) && (popupMode() == MenuButtonPopup)) {
        d_ptr->updateStatusByMousePosition(e->pos());
        if (d_ptr->mMouseOnSubControl) {
            d_ptr->mMenuButtonPressed = true;
            showMenu();
            // showmenu���������жϵ�ǰ�����λ���Ƿ�����subcontrol
            d_ptr->updateStatusByMousePosition(mapFromGlobal(QCursor::pos()));
            return;
        }
    }
    d_ptr->mMenuButtonPressed = false;
    //! ע������Ҫ��QAbstractButton��mousePressEvent��������QToolButton��mousePressEvent
    //! QToolButton��mousePressEvent��Ҫ��Ϊ�˵����˵������ﵯ���˵��ķ�ʽ�ǲ�һ���ģ���˲���ִ��QToolButton��mousePressEvent
    QAbstractButton::mousePressEvent(e);
}

void SARibbonToolButton::mouseReleaseEvent(QMouseEvent* e)
{
    d_ptr->mMenuButtonPressed = false;
    QToolButton::mouseReleaseEvent(e);
}

void SARibbonToolButton::focusOutEvent(QFocusEvent* e)
{
    d_ptr->mMouseOnSubControl = false;
    QToolButton::focusOutEvent(e);
}

void SARibbonToolButton::leaveEvent(QEvent* e)
{
    d_ptr->mMouseOnSubControl = false;
    QToolButton::leaveEvent(e);
}

bool SARibbonToolButton::hitButton(const QPoint& pos) const
{
    if (QToolButton::hitButton(pos)) {
        return (!d_ptr->mMenuButtonPressed);
    }
    return (false);
}

/**
 * @brief ��resizeevent�����ͼ����ĳߴ磬�����ڻ�ͼ������ʵʱ�������Ч��
 * @param e
 */
void SARibbonToolButton::resizeEvent(QResizeEvent* e)
{
#if SA_RIBBON_TOOLBUTTON_DEBUG_PRINT
    qDebug() << "SARibbonToolButton::resizeEvent, text=" << text() << " obj=" << objectName() << " size=" << e->size();
#endif
    //��resizeevent�����ͼ����ĳߴ磬�����ڻ�ͼ������ʵʱ�������Ч��
    QToolButton::resizeEvent(e);
    updateRect();
}

/**
 * @brief toolbutton�ĳߴ�ȷ�����ȶ�������ĳߴ磬�ٶ���icon�ĳߴ磬�Ե����ϣ���֤��������ʾ����
 * @note m_sizeHint��ˢ����Ҫע��
 * @return
 */
QSize SARibbonToolButton::sizeHint() const
{
    //    if (!d_ptr->mSizeHint.isValid() || d_ptr->mSizeHint.width() <= 22) {  // 22�Ǹ���sizehint����Сֵ�����С�����ֵ�����¼���һ��
    //        QStyleOptionToolButton opt;
    //        initStyleOption(&opt);
    //        d_ptr->updateSizeHint(opt);
    //    }
    QStyleOptionToolButton opt;
    initStyleOption(&opt);
    d_ptr->updateSizeHint(opt);
    return d_ptr->mSizeHint;
}

void SARibbonToolButton::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);
    QPainter p(this);
    QStyleOptionToolButton opt;
    initStyleOption(&opt);
    if (opt.features & QStyleOptionToolButton::MenuButtonPopup || opt.features & QStyleOptionToolButton::HasMenu) {
        //�ڲ˵�������ʧ����Ҫͨ���˷���ȡ�������ͣ��
        if (!rect().contains(mapFromGlobal(QCursor::pos()))) {
            opt.state &= ~QStyle::State_MouseOver;
        }
    }
    paintButton(p, opt);
    paintIcon(p, opt, d_ptr->mDrawIconRect);
    paintText(p, opt, d_ptr->mDrawTextRect);
    paintIndicator(p, opt, d_ptr->mDrawIndicatorArrowRect);
}

/**
 * @brief ���ư�ť
 * @param p
 * @param opt
 */
void SARibbonToolButton::paintButton(QPainter& p, const QStyleOptionToolButton& opt)
{
    // QStyle::State_Sunken ����ť����ȥ��
    // QStyle::State_On ����ť��checked
    // QStyle::State_MouseOver ����ǰ���λ�ڰ�ť����
    QStyleOption tool = opt;
    bool autoRaise    = opt.state & QStyle::State_AutoRaise;
    //���ư�ť
    if (autoRaise) {
        //�����Ϊ��ʵ�ְ�ť�����ȥ��(QStyle::State_Sunken),�ܳ���ѡ�е�״̬
        if (opt.state & QStyle::State_Sunken) {
            tool.state &= ~QStyle::State_MouseOver;
        }
        style()->drawPrimitive(QStyle::PE_PanelButtonTool, &tool, &p, this);
    } else {
        style()->drawPrimitive(QStyle::PE_PanelButtonBevel, &tool, &p, this);
    }
    //���MenuButtonPopup��ribbon��ʽ���������
    if ((opt.subControls & QStyle::SC_ToolButton) && (opt.features & QStyleOptionToolButton::MenuButtonPopup)) {
        if (opt.state & QStyle::State_MouseOver) {                       //����ڰ�ť�ϲŽ��л���
            if (!(opt.activeSubControls & QStyle::SC_ToolButtonMenu)) {  //��ť�Ĳ˵�����ʱ��������
                if (LargeButton == d_ptr->mButtonType) {                 //��ťģʽ
                    if (d_ptr->mMouseOnSubControl) {                     //��ʱ�����indecater��
                        //���������������ͼ����ʾΪ����
                        tool.rect  = d_ptr->mDrawIconRect;
                        tool.state = (QStyle::State_Raised);  //��ͼ��������ʾΪ����
                        if (autoRaise) {
                            style()->drawPrimitive(QStyle::PE_PanelButtonTool, &tool, &p, this);
                        } else {
                            style()->drawPrimitive(QStyle::PE_PanelButtonBevel, &tool, &p, this);
                        }
                    } else {
                        //�����ͼ��������������ʾΪ����
                        tool.state = (QStyle::State_Raised);  //��ͼ��������ʾΪ����
                        //���ֺ�Indicator����ʾ����
                        tool.rect = d_ptr->mDrawTextRect.united(d_ptr->mDrawIndicatorArrowRect);
                        if (autoRaise) {
                            style()->drawPrimitive(QStyle::PE_PanelButtonTool, &tool, &p, this);
                        } else {
                            style()->drawPrimitive(QStyle::PE_PanelButtonBevel, &tool, &p, this);
                        }
                    }
                } else {                              //С��ťģʽ
                    if (d_ptr->mMouseOnSubControl) {  //��ʱ�����indecater��
                        //���������������ͼ���������ʾΪ����
                        tool.rect  = d_ptr->mDrawIconRect.united(d_ptr->mDrawTextRect);
                        tool.state = (QStyle::State_Raised);  //��ͼ��������ʾΪ����
                        if (autoRaise) {
                            style()->drawPrimitive(QStyle::PE_PanelButtonTool, &tool, &p, this);
                        } else {
                            style()->drawPrimitive(QStyle::PE_PanelButtonBevel, &tool, &p, this);
                        }
                    } else {
                        //�����ͼ��������������ʾΪ����
                        tool.state = (QStyle::State_Raised);  //��ͼ��������ʾΪ����
                        //���ֺ�Indicator����ʾ����
                        tool.rect = d_ptr->mDrawIndicatorArrowRect;
                        if (autoRaise) {
                            style()->drawPrimitive(QStyle::PE_PanelButtonTool, &tool, &p, this);
                        } else {
                            style()->drawPrimitive(QStyle::PE_PanelButtonBevel, &tool, &p, this);
                        }
                    }
                }
            }
        }
    }
    //����Focus
    //    if (opt.state & QStyle::State_HasFocus) {
    //        QStyleOptionFocusRect fr;
    //        fr.QStyleOption::operator=(opt);
    //        fr.rect.adjust(d_ptr->mSpacing, d_ptr->mSpacing, -d_ptr->mSpacing, -d_ptr->mSpacing);
    //        style()->drawPrimitive(QStyle::PE_FrameFocusRect, &fr, &p, this);
    //    }
}

/**
 * @brief ����ͼ��
 * @param p
 * @param opt
 */
void SARibbonToolButton::paintIcon(QPainter& p, const QStyleOptionToolButton& opt, const QRect& iconDrawRect)
{
    if (!iconDrawRect.isValid()) {
        return;
    }

    QPixmap pm = d_ptr->createIconPixmap(opt, iconDrawRect.size());
    style()->drawItemPixmap(&p, iconDrawRect, Qt::AlignCenter, pm);
    SARIBBONTOOLBUTTON_DEBUG_DRAW_RECT(p, iconDrawRect);
}

/**
 * @brief �����ı�
 * @param p
 * @param opt
 */
void SARibbonToolButton::paintText(QPainter& p, const QStyleOptionToolButton& opt, const QRect& textDrawRect)
{
    int alignment = d_ptr->getTextAlignment();

    if (!style()->styleHint(QStyle::SH_UnderlineShortcut, &opt, this)) {
        alignment |= Qt::TextHideMnemonic;
    }
    QString text;
    if (isSmallRibbonButton()) {
        text = opt.fontMetrics.elidedText(PrivateData::simplified(opt.text), Qt::ElideRight, textDrawRect.width(), alignment);
    } else {
        if (!isEnableWordWrap()) {
            text = opt.fontMetrics.elidedText(PrivateData::simplified(opt.text), Qt::ElideRight, textDrawRect.width(), alignment);
        } else {
            text = opt.text;
        }
    }

    style()->drawItemText(&p, textDrawRect, alignment, opt.palette, opt.state & QStyle::State_Enabled, text, QPalette::ButtonText);

    SARIBBONTOOLBUTTON_DEBUG_DRAW_RECT(p, textDrawRect);
}

/**
 * @brief ����Indicator
 * @param p
 * @param opt
 */
void SARibbonToolButton::paintIndicator(QPainter& p, const QStyleOptionToolButton& opt, const QRect& indicatorDrawRect)
{
    if (!indicatorDrawRect.isValid() || !d_ptr->hasIndicator(opt)) {
        return;
    }

    QStyleOption tool = opt;
    tool.rect         = indicatorDrawRect;
    style()->drawPrimitive(QStyle::PE_IndicatorArrowDown, &tool, &p, this);
    SARIBBONTOOLBUTTON_DEBUG_DRAW_RECT(p, indicatorDrawRect);
}

void SARibbonToolButton::drawArrow(const QStyle* style,
                                   const QStyleOptionToolButton* toolbutton,
                                   const QRect& rect,
                                   QPainter* painter,
                                   const QWidget* widget)
{
    QStyle::PrimitiveElement pe;

    switch (toolbutton->arrowType) {
    case Qt::LeftArrow:
        pe = QStyle::PE_IndicatorArrowLeft;
        break;

    case Qt::RightArrow:
        pe = QStyle::PE_IndicatorArrowRight;
        break;

    case Qt::UpArrow:
        pe = QStyle::PE_IndicatorArrowUp;
        break;

    case Qt::DownArrow:
        pe = QStyle::PE_IndicatorArrowDown;
        break;

    default:
        return;
    }
    QStyleOption arrowOpt = *toolbutton;

    arrowOpt.rect = rect;
    style->drawPrimitive(pe, &arrowOpt, painter, widget);
}

void SARibbonToolButton::changeEvent(QEvent* e)
{
    if (e) {
        if (e->type() == QEvent::FontChange) {
            //˵������ı䣬��Ҫ���¼����������ص���Ϣ
            updateRect();
        }
    }
    QToolButton::changeEvent(e);
}

void SARibbonToolButton::actionEvent(QActionEvent* e)
{
    QToolButton::actionEvent(e);
    updateRect();
}

/**
 * @brief ��ť��ʽ
 * @sa setButtonType
 * @return
 */
SARibbonToolButton::RibbonButtonType SARibbonToolButton::buttonType() const
{
    return (d_ptr->mButtonType);
}

/**
 * @brief ���ð�ť��ʽ
 * @note ���ð�ť��ʽ���̻����setToolButtonStyle�����Ҫ�ı�toolButtonStyle,������ΪQt::ToolButtonIconOnly,��Ҫ�ڴ˺���֮������
 * @param buttonType
 */
void SARibbonToolButton::setButtonType(const RibbonButtonType& buttonType)
{
    d_ptr->mButtonType = buttonType;
    //����iconrect
    //��������������ֵĸ߶�

    if (LargeButton == buttonType) {
        setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
    } else {
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    }

    updateRect();
}

/**
 * @brief �Ƿ���С��ť
 * @return
 */
bool SARibbonToolButton::isSmallRibbonButton() const
{
    return (d_ptr->mButtonType == SmallButton);
}

/**
 * @brief �Ƿ��Ǵ�ť
 * @return
 */
bool SARibbonToolButton::isLargeRibbonButton() const
{
    return (d_ptr->mButtonType == LargeButton);
}

QSize SARibbonToolButton::minimumSizeHint() const
{
    return (sizeHint());
}

/**
 * @brief ����Ǽ�����Ҫ���εļ��
 * @return
 */
int SARibbonToolButton::spacing() const
{
    return d_ptr->mSpacing;
}

void SARibbonToolButton::updateRect()
{
    QStyleOptionToolButton opt;
    initStyleOption(&opt);
    //    d_ptr->updateSizeHint(opt);
    d_ptr->updateDrawRect(opt);
}

/**
 * @brief ������liteģʽ���Ƿ��������ֻ��У����������ͼ����ԱȽ�С��Ĭ�ϲ�����
 * @param on
 * @note �˺����ĵ��������ribbonbar����֮ǰ���ã��ҵ���֮����Ҫ����@sa SARibbonStyleOption::recalc ˢ��
 * @code
 * RibbonSubElementStyleOpt.recalc();
 * @endcode
 */
void SARibbonToolButton::setEnableWordWrap(bool on)
{
    SARibbonToolButton::PrivateData::s_enableWordWrap = on;
}

/**
 * @brief ��liteģʽ���Ƿ��������ֻ���
 * @return
 */
bool SARibbonToolButton::isEnableWordWrap()
{
    return SARibbonToolButton::PrivateData::s_enableWordWrap;
}

bool SARibbonToolButton::event(QEvent* e)
{
    switch (e->type()) {
    case QEvent::WindowDeactivate:
        d_ptr->mMouseOnSubControl = false;
        break;
    case QEvent::ActionChanged:
    case QEvent::ActionRemoved:
    case QEvent::ActionAdded: {
        d_ptr->mMouseOnSubControl = false;
        updateRect();
    } break;

    default:
        break;
    }

    return (QToolButton::event(e));
}

/*** End of inlined file: SARibbonToolButton.cpp ***/

/*** Start of inlined file: SARibbonColorToolButton.cpp ***/
#include <QStylePainter>
#include <QStyleOptionToolButton>
#include <QDebug>

//===================================================
// SARibbonColorToolButton::PrivateData
//===================================================
const int c_ribbonbutton_color_height = 5;  ///< ��ɫ��ĸ߶�

class SARibbonColorToolButton::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonColorToolButton)
public:
    PrivateData(SARibbonColorToolButton* p);
    QPixmap createIconPixmap(const QStyleOptionToolButton& opt, const QSize& iconsize) const;
    QIcon createColorIcon(const QColor& c, const QSize& size) const;

public:
    QColor mColor;                                                                                ///< ��¼��ɫ
    SARibbonColorToolButton::ColorStyle mColorStyle { SARibbonColorToolButton::ColorUnderIcon };  ///< ��ɫ��ʾ��ʽ
    QIcon mOldIcon;                                                                               ///< ��¼�ɵ�icon
};

SARibbonColorToolButton::PrivateData::PrivateData(SARibbonColorToolButton* p) : q_ptr(p)
{
}

QPixmap SARibbonColorToolButton::PrivateData::createIconPixmap(const QStyleOptionToolButton& opt, const QSize& iconsize) const
{
    if (opt.icon.isNull()) {  //û����ͼ��
        return QPixmap();
    }
    //��icon����icon�·�������ɫ
    QIcon::State state = (opt.state & QStyle::State_On) ? QIcon::On : QIcon::Off;
    QIcon::Mode mode;
    if (!(opt.state & QStyle::State_Enabled)) {
        mode = QIcon::Disabled;
    } else if ((opt.state & QStyle::State_MouseOver) && (opt.state & QStyle::State_AutoRaise)) {
        mode = QIcon::Active;
    } else {
        mode = QIcon::Normal;
    }
    QSize realIconSize = iconsize - QSize(0, c_ribbonbutton_color_height + 1);
    QPixmap pixmap     = opt.icon.pixmap(q_ptr->window()->windowHandle(), realIconSize, mode, state);
    QPixmap res(pixmap.size() + QSize(4, c_ribbonbutton_color_height + 4));  //����ϣ���ɫ����2px
    res.fill(Qt::transparent);
    QPainter painter(&res);
    int xpixmap   = (res.width() - pixmap.width()) / 2;
    int ypixmap   = (res.height() - c_ribbonbutton_color_height - 2 - pixmap.height()) / 2;  //����Ҫ��ȥ2������1����������ż��������Ӱ��
    QRect rpixmap = QRect(xpixmap, ypixmap, pixmap.width(), pixmap.height());
    painter.drawPixmap(rpixmap, pixmap);
    QRect colorRect = rpixmap.adjusted(0, pixmap.height() + 1, 0, c_ribbonbutton_color_height + 1);
    if (mColor.isValid()) {
        painter.fillRect(colorRect, mColor);
    } else {
        QPen pen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap);
        painter.setPen(pen);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.setRenderHint(QPainter::Antialiasing, true);
        int ss = colorRect.width() / 3;
        painter.drawLine(QPoint(colorRect.x() + ss, colorRect.bottom()), QPoint(colorRect.right() - ss, colorRect.top()));
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawRect(colorRect);
    }
    return res;
}

QIcon SARibbonColorToolButton::PrivateData::createColorIcon(const QColor& c, const QSize& size) const
{
    QPixmap res(size);
    res.fill(Qt::transparent);
    QPainter painter(&res);
    if (c.isValid()) {
        painter.fillRect(QRect(1, 1, res.height() - 2, res.width() - 2), c);
    } else {
        QPen pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap);
        painter.setPen(pen);
        painter.drawRect(QRect(1, 1, res.height() - 2, res.width() - 2));
        pen.setColor(Qt::red);
        painter.setPen(pen);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.drawLine(QPoint(1, size.height()), QPoint(size.width() - 1, 1));
    }
    return QIcon(res);
}

//===================================================
// SARibbonColorToolButton
//===================================================

SARibbonColorToolButton::SARibbonColorToolButton(QWidget* parent)
    : SARibbonToolButton(parent), d_ptr(new SARibbonColorToolButton::PrivateData(this))
{
    connect(this, &QAbstractButton::clicked, this, &SARibbonColorToolButton::onButtonClicked);
}

SARibbonColorToolButton::SARibbonColorToolButton(QAction* defaultAction, QWidget* parent)
    : SARibbonToolButton(defaultAction, parent), d_ptr(new SARibbonColorToolButton::PrivateData(this))
{
    connect(this, &QAbstractButton::clicked, this, &SARibbonColorToolButton::onButtonClicked);
}

SARibbonColorToolButton::~SARibbonColorToolButton()
{
}

/**
 * @brief ��ȡ��ťά������ɫ
 * @return
 */
QColor SARibbonColorToolButton::getColor() const
{
    return d_ptr->mColor;
}

/**
 * @brief ������ɫ��ʾ����ʽ
 * @param s
 */
void SARibbonColorToolButton::setColorStyle(SARibbonColorToolButton::ColorStyle s)
{
    if (d_ptr->mColorStyle == s) {
        return;
    }
    d_ptr->mColorStyle = s;
    if (ColorUnderIcon == s) {
        setIcon(d_ptr->mOldIcon);
    } else {
        d_ptr->mOldIcon = icon();
        setIcon(d_ptr->createColorIcon(d_ptr->mColor, QSize(32, 32)));
    }
    repaint();
}

/**
 * @brief ��ɫ��ʾ����ʽ
 * @return
 */
SARibbonColorToolButton::ColorStyle SARibbonColorToolButton::colorStyle() const
{
    return d_ptr->mColorStyle;
}

/**
 * @brief ������׼����ɫ�˵�
 * @return
 */
SAColorMenu* SARibbonColorToolButton::setupStandardColorMenu()
{
    setPopupMode(QToolButton::MenuButtonPopup);
    SAColorMenu* m = new SAColorMenu(this);
    m->enableNoneColorAction(true);
    QAction* customColor = m->getCustomColorAction();
    if (customColor) {
        customColor->setIcon(QIcon(":/image/resource/define-color.svg"));
    }
    connect(m, &SAColorMenu::selectedColor, this, &SARibbonColorToolButton::setColor);
    setMenu(m);

    updateRect();
    return m;
}

/**
 * @brief ���ð�ť����ɫ
 *
 * ��ʱ������һ���µ�icon
 * @note �ᷢ��@sa colorChanged �ź�
 * @param c
 */
void SARibbonColorToolButton::setColor(const QColor& c)
{
    if (d_ptr->mColor != c) {
        d_ptr->mColor = c;
        if (ColorFillToIcon == colorStyle()) {
            setIcon(d_ptr->createColorIcon(c, QSize(32, 32)));
        }
        repaint();
        emit colorChanged(c);
    }
}

void SARibbonColorToolButton::onButtonClicked(bool checked)
{
    emit colorClicked(d_ptr->mColor, checked);
}

/**
 * @brief ��дpaintIcon����������ɫ�ӵ�icon����
 * @param p
 * @param opt
 * @param iconDrawRect
 */
void SARibbonColorToolButton::paintIcon(QPainter& p, const QStyleOptionToolButton& opt, const QRect& iconDrawRect)
{
    if (ColorUnderIcon == colorStyle()) {
        //��icon
        QPixmap pm = d_ptr->createIconPixmap(opt, iconDrawRect.size());
        style()->drawItemPixmap(&p, iconDrawRect, Qt::AlignCenter, pm);
    } else {
        SARibbonToolButton::paintIcon(p, opt, iconDrawRect);
    }
}

/*** End of inlined file: SARibbonColorToolButton.cpp ***/

/*** Start of inlined file: SARibbonLineWidgetContainer.cpp ***/
#include <QHBoxLayout>

SARibbonLineWidgetContainer::SARibbonLineWidgetContainer(QWidget* par) : QWidget(par), m_innerWidget(nullptr)
{
    m_labelPrefix    = new QLabel(this);
    m_labelSuffix    = new QLabel(this);
    QHBoxLayout* lay = new QHBoxLayout();

    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(0);
    lay->addWidget(m_labelPrefix);
    lay->addWidget(m_labelSuffix);
    setLayout(lay);
}

void SARibbonLineWidgetContainer::setWidget(QWidget* innerWidget)
{
    QHBoxLayout* lay = static_cast< QHBoxLayout* >(layout());

    if (m_innerWidget) {
        lay->replaceWidget(m_innerWidget, innerWidget);
    } else {
        lay->insertWidget(1, innerWidget);
    }
    m_innerWidget = innerWidget;
}

void SARibbonLineWidgetContainer::setPrefix(const QString& str)
{
    m_labelPrefix->setText(str);
}

void SARibbonLineWidgetContainer::setSuffix(const QString& str)
{
    m_labelSuffix->setText(str);
}

QLabel* SARibbonLineWidgetContainer::labelPrefix() const
{
    return (m_labelPrefix);
}

QLabel* SARibbonLineWidgetContainer::labelSuffix() const
{
    return (m_labelSuffix);
}

/*** End of inlined file: SARibbonLineWidgetContainer.cpp ***/

/*** Start of inlined file: SARibbonActionsManager.cpp ***/
#include <QMap>
#include <QHash>
#include <QDebug>

class SARibbonActionsManager::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonActionsManager)
public:
    PrivateData(SARibbonActionsManager* p);
    void clear();

    QMap< int, QList< QAction* > > mTagToActions;   ///< tag : QList<QAction*>
    QMap< int, QString > mTagToName;                ///< tag��Ӧ������
    QHash< QString, QAction* > mKeyToAction;        ///< key��Ӧaction
    QMap< QAction*, QString > mActionToKey;         ///< action��Ӧkey
    QMap< int, SARibbonCategory* > mTagToCategory;  ///< ������autoRegisteActions����������
    int mSale;  ///< ���������ɹ̶���id�����û�����������keyʱ��id����msale���ɣ�ֻҪSARibbonActionsManager�ĵ���registeAction˳�򲻱䣬���ɵ�id�����䣬��Ϊ���ǻ�������ʵ�ֵ�
};

SARibbonActionsManager::PrivateData::PrivateData(SARibbonActionsManager* p) : q_ptr(p), mSale(0)
{
}

void SARibbonActionsManager::PrivateData::clear()
{
    mTagToActions.clear();
    mTagToName.clear();
    mKeyToAction.clear();
    mActionToKey.clear();
    mTagToCategory.clear();
    mSale = 0;
}

SARibbonActionsManager::SARibbonActionsManager(SARibbonMainWindow* p)
    : QObject(p), d_ptr(new SARibbonActionsManager::PrivateData(this))
{
    autoRegisteActions(p);
}

SARibbonActionsManager::~SARibbonActionsManager()
{
}

/**
 * @brief ����tag��Ӧ�����֣�ͨ��������Եõ�tag���ı���ӳ��
 * @param tag
 * @param name
 * @note ��֧�ֶ����ԵĻ����£��������л�ʱ��Ҫ�������ã��Ը�������
 */
void SARibbonActionsManager::setTagName(int tag, const QString& name)
{
    d_ptr->mTagToName[ tag ] = name;
}

/**
 * @brief ��ȡtag��Ӧ����������
 * @param tag
 * @return
 */
QString SARibbonActionsManager::tagName(int tag) const
{
    return (d_ptr->mTagToName.value(tag, ""));
}

/**
 * @brief �Ƴ�tag
 * @note ע�⣬��������ǳ���ʱ
 * @param tag
 */
void SARibbonActionsManager::removeTag(int tag)
{
    QList< QAction* > oldacts = actions(tag);

    //��ʼ�Ƴ�
    d_ptr->mTagToActions.remove(tag);
    d_ptr->mTagToName.remove(tag);
    //��ʼ������Ҫ�Ƴ��ܱ��action
    QList< QAction* > needRemoveAct;
    QList< QAction* > total;

    for (auto i = d_ptr->mTagToActions.begin(); i != d_ptr->mTagToActions.end(); ++i) {
        total += i.value();
    }
    for (QAction* a : qAsConst(oldacts)) {
        if (!total.contains(a)) {
            needRemoveAct.append(a);
        }
    }
    //���ܱ��Ƴ�action
    for (QAction* a : qAsConst(needRemoveAct)) {
        auto i = d_ptr->mActionToKey.find(a);
        if (i != d_ptr->mActionToKey.end()) {
            d_ptr->mKeyToAction.remove(i.value());
            d_ptr->mActionToKey.erase(i);
        }
    }
}

/**
 * @brief ��actionע�ᵽ�������У�ʵ��action�Ĺ���
 * @param act
 * @param tag tag�ǿ��԰���λ���е��ӣ��� @ref ActionTag ���
 * Ҫ�����Լ��ı�ǩ�����鶨�����@ref ActionTag::UserDefineActionTag ��ֵ��
 * registeAction��tag��ֱ�Ӽ�¼��ȥ�ģ����Ҫ�����ǩ���棬��registe֮ǰ�Ȼ��tag
 * @param key key��action��Ӧ��key��һ��keyֻ��Ӧһ��action���ǲ���action�Ĺؼ�
 * ,Ĭ�����Ϊһ��QString(),��ʱkey��QAction��objectName
 * @note ͬһ��action���ע�᲻ͬ��tag����ͨ��tag������action����ͨ��actionֻ�����������һ��ע���tag
 * @note tag�������ᴥ��actionTagChanged�ź�
 */
bool SARibbonActionsManager::registeAction(QAction* act, int tag, const QString& key, bool enableEmit)
{
    if (nullptr == act) {
        return (false);
    }
    QString k = key;

    if (k.isEmpty()) {
        k = QString("id_%1_%2").arg(d_ptr->mSale++).arg(act->objectName());
    }
    if (d_ptr->mKeyToAction.contains(k)) {
        qWarning() << "key: " << k << " have been exist,you can set key in an unique value when use SARibbonActionsManager::registeAction";
        return (false);
    }
    d_ptr->mKeyToAction[ k ]   = act;
    d_ptr->mActionToKey[ act ] = k;
    //��¼tag �� action
    bool isneedemit = !(d_ptr->mTagToActions.contains(tag));  //��¼�Ƿ���Ҫ�����ź�

    d_ptr->mTagToActions[ tag ].append(act);
    //�󶨲�
    connect(act, &QObject::destroyed, this, &SARibbonActionsManager::onActionDestroyed);
    if (isneedemit && enableEmit) {
        //˵������tag
        emit actionTagChanged(tag, false);
    }
    return (true);
}

/**
 * @brief ȡ��action��ע��
 *
 * ���tag��Ӧ�����һ��action��������tagҲ��һ��ɾ��
 * @param act
 * @note tag��ɾ���ᴥ��actionTagChanged�ź�
 * @note ���action�����˶��tag����Щtag���action���ᱻɾ������Ӧ��keyҲͬ��
 */
void SARibbonActionsManager::unregisteAction(QAction* act, bool enableEmit)
{
    if (nullptr == act) {
        return;
    }
    //�󶨲�
    disconnect(act, &QObject::destroyed, this, &SARibbonActionsManager::onActionDestroyed);
    removeAction(act, enableEmit);
}

/**
 * @brief �Ƴ�action
 *
 * ���Ƴ��ڴ�����
 * @param act
 * @param enableEmit
 */
void SARibbonActionsManager::removeAction(QAction* act, bool enableEmit)
{
    QList< int > deletedTags;                     //��¼ɾ����tag�����ڴ���actionTagChanged
    QMap< int, QList< QAction* > > tagToActions;  ///< tag : QList<QAction*>

    for (auto i = d_ptr->mTagToActions.begin(); i != d_ptr->mTagToActions.end(); ++i) {
        //�Ѳ���act������ת�Ƶ�tagToActions��tagToActionKeys�У�֮���ٺ�m_d����滻
        auto tmpi = tagToActions.insert(i.key(), QList< QAction* >());
        int count = 0;
        for (int j = 0; j < i.value().size(); ++j) {
            if (i.value()[ j ] != act) {
                tmpi.value().append(act);
                ++count;
            }
        }
        if (0 == count) {
            //˵�����tagû������
            tagToActions.erase(tmpi);
            deletedTags.append(i.key());
        }
    }
    //ɾ��mKeyToAction
    QString key = d_ptr->mActionToKey.value(act);

    d_ptr->mActionToKey.remove(act);
    d_ptr->mKeyToAction.remove(key);

    //�û�
    d_ptr->mTagToActions.swap(tagToActions);
    //�����ź�
    if (enableEmit) {
        for (int tagdelete : qAsConst(deletedTags)) {
            emit actionTagChanged(tagdelete, true);
        }
    }
}

/**
 * @brief ��ͬactions
 * @param tag
 * @return
 */
QList< QAction* >& SARibbonActionsManager::filter(int tag)
{
    return (actions(tag));
}

/**
 * @brief ����tag�õ�actions
 * @param tag
 * @return
 */
QList< QAction* >& SARibbonActionsManager::actions(int tag)
{
    return (d_ptr->mTagToActions[ tag ]);
}

const QList< QAction* > SARibbonActionsManager::actions(int tag) const
{
    return (d_ptr->mTagToActions[ tag ]);
}

/**
 * @brief ��ȡ���еı�ǩ
 * @return
 */
QList< int > SARibbonActionsManager::actionTags() const
{
    return (d_ptr->mTagToActions.keys());
}

/**
 * @brief ͨ��key��ȡaction
 * @param key
 * @return ���û��key������nullptr
 */
QAction* SARibbonActionsManager::action(const QString& key) const
{
    return (d_ptr->mKeyToAction.value(key, nullptr));
}

/**
 * @brief ͨ��action�ҵ�key
 * @param act
 * @return ����Ҳ���������QString()
 */
QString SARibbonActionsManager::key(QAction* act) const
{
    return (d_ptr->mActionToKey.value(act, QString()));
}

/**
 * @brief �������й����action��
 * @return
 */
int SARibbonActionsManager::count() const
{
    return (d_ptr->mKeyToAction.size());
}

/**
 * @brief �������й����actions
 * @return
 */
QList< QAction* > SARibbonActionsManager::allActions() const
{
    return (d_ptr->mKeyToAction.values());
}

/**
 * @brief �Զ�����SARibbonMainWindow��action
 * �˺��������@ref SARibbonMainWindow �µ�������object���ҵ�actionע�ᣬ
 * �����������@ref SARibbonCategory,��SARibbonCategory�µ�action��SARibbonCategory��title name���з���
 *
 * �˺����������category�µ�action����tag��ע�ᣬ���ص�QMap<int, SARibbonCategory *>�Ǽ�¼��category��Ӧ��tag
 *
 * �˺��������SARibbonMainWindow�����action���������κ�һ��category�µ���ΪNotInRibbonCategoryTag��ǩע�ᣬĬ�����ֻḳ��not
 * in ribbon�� ����ͨ��@ref setTagName �ı�
 *
 * @param w
 * @return
 * @note �˺����ĵ��������category�����˱������ã���Ϊ����category�ı�����Ϊ��ǩ������
 */
QMap< int, SARibbonCategory* > SARibbonActionsManager::autoRegisteActions(SARibbonMainWindow* w)
{
    QMap< int, SARibbonCategory* > res;
    //�ȱ���SARibbonMainWindow�µ������Ӷ��󣬰�����action�ҵ�
    QSet< QAction* > mainwindowActions;

    for (QObject* o : qAsConst(w->children())) {
        if (QAction* a = qobject_cast< QAction* >(o)) {
            //˵����action
            if (!a->objectName().isEmpty()) {
                mainwindowActions.insert(a);
            }
        }
    }
    //��ʼ����ÿ��category������action
    SARibbonBar* bar = w->ribbonBar();

    if (nullptr == bar) {
        //��ribbonģʽ��ֱ���˳�
        return (res);
    }
    QSet< QAction* > categoryActions;
    QList< SARibbonCategory* > categorys = bar->categoryPages();
    int tag                              = AutoCategoryDistinguishBeginTag;

    for (SARibbonCategory* c : qAsConst(categorys)) {
        QList< SARibbonPannel* > pannels = c->pannelList();
        for (SARibbonPannel* p : qAsConst(pannels)) {
            categoryActions += autoRegisteWidgetActions(p, tag, false);
        }
        setTagName(tag, c->categoryName());
        res[ tag ] = c;
        ++tag;
    }
    //�ҵ����ڹ�������actions
    QSet< QAction* > notincategory = mainwindowActions - categoryActions;

    for (QAction* a : qAsConst(notincategory)) {
        if (!a->objectName().isEmpty()) {
            registeAction(a, NotInRibbonCategoryTag, a->objectName(), false);
        }
    }
    if (notincategory.size() > 0) {
        setTagName(NotInRibbonCategoryTag, tr("not in ribbon"));
    }
    for (auto i = res.begin(); i != res.end(); ++i) {
        connect(i.value(), &SARibbonCategory::windowTitleChanged, this, &SARibbonActionsManager::onCategoryTitleChanged);
    }
    d_ptr->mTagToCategory = res;
    return (res);
}

/**
 * @brief �Զ�����action
 * @param w
 * @param tag
 * @param enableEmit
 * @return ���سɹ�����SARibbonActionsManager�����action
 */
QSet< QAction* > SARibbonActionsManager::autoRegisteWidgetActions(QWidget* w, int tag, bool enableEmit)
{
    QSet< QAction* > res;
    QList< QAction* > was = w->actions();

    for (QAction* a : qAsConst(was)) {
        if (res.contains(a) || a->objectName().isEmpty()) {
            //�ظ����ݲ��ظ�����
            //û��object name������
            continue;
        }
        if (registeAction(a, tag, a->objectName(), enableEmit)) {
            res.insert(a);
        }
    }
    return (res);
}

/**
 * @brief ���ݱ������action
 * @param text
 * @return
 */
QList< QAction* > SARibbonActionsManager::search(const QString& text)
{
    QList< QAction* > res;

    if (text.isEmpty()) {
        return (res);
    }
    QStringList kws = text.split(" ");

    if (kws.isEmpty()) {
        kws.append(text);
    }
    QList< QAction* > acts = d_ptr->mActionToKey.keys();

    for (const QString& k : qAsConst(kws)) {
        for (auto i = d_ptr->mActionToKey.begin(); i != d_ptr->mActionToKey.end(); ++i) {
            if (i.key()->text().contains(k, Qt::CaseInsensitive)) {
                res.append(i.key());
            }
        }
    }
    return (res);
}

void SARibbonActionsManager::clear()
{
    d_ptr->clear();
}

SARibbonMainWindow* SARibbonActionsManager::ribbonWindow() const
{
    return (qobject_cast< SARibbonMainWindow* >(parent()));
}

/**
 * @brief action ��deleteʱ���������˲۰ѹ����actionɾ��
 * @param o
 * @note ����������ᴥ��actionTagChanged�ź�
 */
void SARibbonActionsManager::onActionDestroyed(QObject* o)
{
    QAction* act = static_cast< QAction* >(o);

    removeAction(act, false);
}

/**
 * @brief autoRegisteActions����������˲ۣ��ڱ�ǩ���ݸı�ʱ�ı�tag ��Ӧ �ı�
 * @param title
 */
void SARibbonActionsManager::onCategoryTitleChanged(const QString& title)
{
    SARibbonCategory* c = qobject_cast< SARibbonCategory* >(sender());

    if (nullptr == c) {
        return;
    }
    int tag = d_ptr->mTagToCategory.key(c, -1);

    if (tag == -1) {
        return;
    }
    setTagName(tag, title);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// SARibbonActionsModel
////////////////////////////////////////////////////////////////////////////////////////////////////////

class SARibbonActionsManagerModel::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonActionsManagerModel)
public:
    PrivateData(SARibbonActionsManagerModel* p);
    void updateRef();
    int count() const;
    QAction* at(int index);
    bool isNull() const;

public:
    SARibbonActionsManager* mMgr { nullptr };
    int mTag { SARibbonActionsManager::CommonlyUsedActionTag };
    QString mSeatchText;
    QList< QAction* > mActions;
};

SARibbonActionsManagerModel::PrivateData::PrivateData(SARibbonActionsManagerModel* p) : q_ptr(p)
{
}

void SARibbonActionsManagerModel::PrivateData::updateRef()
{
    if (isNull()) {
        return;
    }
    if (!mSeatchText.isEmpty()) {
        mActions = mMgr->search(mSeatchText);
    } else {
        mActions = mMgr->actions(mTag);
    }
}

int SARibbonActionsManagerModel::PrivateData::count() const
{
    if (isNull()) {
        return (0);
    }
    return (mActions.size());
}

QAction* SARibbonActionsManagerModel::PrivateData::at(int index)
{
    if (isNull()) {
        return (nullptr);
    }
    if (index >= count()) {
        return (nullptr);
    }
    return (mActions.at(index));
}

bool SARibbonActionsManagerModel::PrivateData::isNull() const
{
    return (mMgr == nullptr);
}

//===================================================
// SARibbonActionsManagerModel
//===================================================

SARibbonActionsManagerModel::SARibbonActionsManagerModel(QObject* p)
    : QAbstractListModel(p), d_ptr(new SARibbonActionsManagerModel::PrivateData(this))
{
}

SARibbonActionsManagerModel::SARibbonActionsManagerModel(SARibbonActionsManager* m, QObject* p)
    : QAbstractListModel(p), d_ptr(new SARibbonActionsManagerModel::PrivateData(this))
{
    setupActionsManager(m);
}

SARibbonActionsManagerModel::~SARibbonActionsManagerModel()
{
}

int SARibbonActionsManagerModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {  //�Ƕ���
        return (0);
    }
    //����
    return (d_ptr->count());
}

QVariant SARibbonActionsManagerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    if (role != Qt::DisplayRole) {
        return (QVariant());
    }
    if (Qt::Horizontal == orientation) {
        return (tr("action name"));
    }
    return (QVariant());
}

Qt::ItemFlags SARibbonActionsManagerModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return (Qt::NoItemFlags);
    }
    return (Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

QVariant SARibbonActionsManagerModel::data(const QModelIndex& index, int role) const
{
    QAction* act = indexToAction(index);

    if (nullptr == act) {
        return (QVariant());
    }

    switch (role) {
    case Qt::DisplayRole:
        return (act->text());

    case Qt::DecorationRole:
        return (act->icon());

    default:
        break;
    }
    return (QVariant());
}

void SARibbonActionsManagerModel::setFilter(int tag)
{
    d_ptr->mTag = tag;
    update();
}

void SARibbonActionsManagerModel::update()
{
    beginResetModel();
    d_ptr->updateRef();
    endResetModel();
}

void SARibbonActionsManagerModel::setupActionsManager(SARibbonActionsManager* m)
{
    d_ptr->mMgr     = m;
    d_ptr->mTag     = SARibbonActionsManager::CommonlyUsedActionTag;
    d_ptr->mActions = m->filter(d_ptr->mTag);
    connect(m, &SARibbonActionsManager::actionTagChanged, this, &SARibbonActionsManagerModel::onActionTagChanged);
    update();
}

void SARibbonActionsManagerModel::uninstallActionsManager()
{
    if (!d_ptr->isNull()) {
        disconnect(d_ptr->mMgr, &SARibbonActionsManager::actionTagChanged, this, &SARibbonActionsManagerModel::onActionTagChanged);
        d_ptr->mMgr = nullptr;
        d_ptr->mTag = SARibbonActionsManager::CommonlyUsedActionTag;
    }
    update();
}

QAction* SARibbonActionsManagerModel::indexToAction(QModelIndex index) const
{
    if (!index.isValid()) {
        return (nullptr);
    }
    if (index.row() >= d_ptr->count()) {
        return (nullptr);
    }
    return (d_ptr->at(index.row()));
}

/**
 * @brief ����
 * @param text
 */
void SARibbonActionsManagerModel::search(const QString& text)
{
    d_ptr->mSeatchText = text;
    update();
}

void SARibbonActionsManagerModel::onActionTagChanged(int tag, bool isdelete)
{
    if (isdelete && (tag == d_ptr->mTag)) {
        d_ptr->mTag = SARibbonActionsManager::UnknowActionTag;
        update();
    } else {
        if (tag == d_ptr->mTag) {
            update();
        }
    }
}

/*** End of inlined file: SARibbonActionsManager.cpp ***/

/*** Start of inlined file: SARibbonDrawHelper.cpp ***/
SARibbonDrawHelper::SARibbonDrawHelper()
{
}

QPixmap SARibbonDrawHelper::iconToPixmap(const QIcon& icon, QWidget* widget, const QStyleOption* opt, const QSize& icoSize)
{
    QIcon::Mode mode;
    QIcon::State state;

    if (!(opt->state & QStyle::State_Enabled)) {
        mode = QIcon::Disabled;
    } else if ((opt->state & QStyle::State_MouseOver) && (opt->state & QStyle::State_AutoRaise)) {
        mode = QIcon::Active;
    } else {
        mode = QIcon::Normal;
    }

    if (opt->state & QStyle::State_Selected || opt->state & QStyle::State_On) {
        state = QIcon::On;
    } else {
        state = QIcon::Off;
    }
    return (icon.pixmap(icoSize, mode, state));
}

void SARibbonDrawHelper::drawIcon(const QIcon& icon, QPainter* painter, const QStyleOption* opt, int x, int y, int width, int height)
{
    QIcon::Mode mode;
    QIcon::State state;

    if (!(opt->state & QStyle::State_Enabled)) {
        mode = QIcon::Disabled;
    } else if ((opt->state & QStyle::State_MouseOver) && (opt->state & QStyle::State_AutoRaise)) {
        mode = QIcon::Active;
    } else {
        mode = QIcon::Normal;
    }

    if (opt->state & QStyle::State_Selected || opt->state & QStyle::State_On) {
        state = QIcon::On;
    } else {
        state = QIcon::Off;
    }

    icon.paint(painter, x, y, width, height, Qt::AlignCenter, mode, state);
}

void SARibbonDrawHelper::drawIcon(const QIcon& icon, QPainter* painter, const QStyleOption* opt, const QRect& rect)
{
    QIcon::Mode mode;
    QIcon::State state;

    if (!(opt->state & QStyle::State_Enabled)) {
        mode = QIcon::Disabled;
    } else if ((opt->state & QStyle::State_MouseOver) && (opt->state & QStyle::State_AutoRaise)) {
        mode = QIcon::Active;
    } else {
        mode = QIcon::Normal;
    }

    if (opt->state & QStyle::State_Selected || opt->state & QStyle::State_On) {
        state = QIcon::On;
    } else {
        state = QIcon::Off;
    }

    icon.paint(painter, rect, Qt::AlignCenter, mode, state);
}

QSize SARibbonDrawHelper::iconActualSize(const QIcon& icon, const QStyleOption* opt, const QSize& iconSize)
{
    QIcon::Mode mode;
    QIcon::State state;

    if (!(opt->state & QStyle::State_Enabled)) {
        mode = QIcon::Disabled;
    } else if ((opt->state & QStyle::State_MouseOver) && (opt->state & QStyle::State_AutoRaise)) {
        mode = QIcon::Active;
    } else {
        mode = QIcon::Normal;
    }

    if (opt->state & QStyle::State_Selected || opt->state & QStyle::State_On) {
        state = QIcon::On;
    } else {
        state = QIcon::Off;
    }
    return (icon.actualSize(iconSize, mode, state));
}

void SARibbonDrawHelper::drawText(const QString& text, QStylePainter* painter, const QStyleOption* opt, Qt::Alignment al, int x, int y, int width, int height)
{
    painter->drawItemText(QRect(x, y, width, height), al, opt->palette, opt->state & QStyle::State_Enabled, text);
}

void SARibbonDrawHelper::drawText(const QString& text, QStylePainter* painter, const QStyleOption* opt, Qt::Alignment al, const QRect& rect)
{
    painter->drawItemText(rect, al, opt->palette, opt->state & QStyle::State_Enabled, text);
}

/*** End of inlined file: SARibbonDrawHelper.cpp ***/

/*** Start of inlined file: SARibbonLineEdit.cpp ***/
#include <QStyleOption>

SARibbonLineEdit::SARibbonLineEdit(QWidget* parent) : QLineEdit(parent)
{
}

/*** End of inlined file: SARibbonLineEdit.cpp ***/

/*** Start of inlined file: SARibbonCheckBox.cpp ***/
#include <QStyleOption>

SARibbonCheckBox::SARibbonCheckBox(QWidget* parent) : QCheckBox(parent)
{
}

/*** End of inlined file: SARibbonCheckBox.cpp ***/

/*** Start of inlined file: SARibbonComboBox.cpp ***/
SARibbonComboBox::SARibbonComboBox(QWidget* parent) : QComboBox(parent)
{
}

/*** End of inlined file: SARibbonComboBox.cpp ***/

/*** Start of inlined file: SARibbonButtonGroupWidget.cpp ***/
#include <QHBoxLayout>
#include <QDebug>
#include <QMargins>
#include <QChildEvent>
#include <QActionEvent>
#include <QWidgetAction>
#include <QApplication>

//===================================================
// SAPrivateRibbonButtonGroupWidgetItem
//===================================================
class SAPrivateRibbonButtonGroupWidgetItem
{
public:
    QAction* action;
    QWidget* widget;
    bool customWidget;
    bool operator==(QAction* action);
    bool operator==(const SAPrivateRibbonButtonGroupWidgetItem& w);

    SAPrivateRibbonButtonGroupWidgetItem();
    SAPrivateRibbonButtonGroupWidgetItem(QAction* a, QWidget* w, bool cw);
};

//===================================================
// SARibbonButtonGroupWidget::PrivateData
//===================================================
class SARibbonButtonGroupWidget::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonButtonGroupWidget)
public:
    PrivateData(SARibbonButtonGroupWidget* p);
    void init();

public:
    QList< SAPrivateRibbonButtonGroupWidgetItem > mItems;  ///< ���ڼ�¼���й����item
};

SARibbonButtonGroupWidget::PrivateData::PrivateData(SARibbonButtonGroupWidget* p) : q_ptr(p)
{
}

void SARibbonButtonGroupWidget::PrivateData::init()
{
    QHBoxLayout* layout = new QHBoxLayout(q_ptr);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    q_ptr->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

//===================================================
// SARibbonButtonGroupWidgetItem
//===================================================

bool SAPrivateRibbonButtonGroupWidgetItem::operator==(QAction* action)
{
    return (this->action == action);
}

bool SAPrivateRibbonButtonGroupWidgetItem::operator==(const SAPrivateRibbonButtonGroupWidgetItem& w)
{
    return (this->action == w.action);
}

SAPrivateRibbonButtonGroupWidgetItem::SAPrivateRibbonButtonGroupWidgetItem()
    : action(nullptr), widget(nullptr), customWidget(false)
{
}

SAPrivateRibbonButtonGroupWidgetItem::SAPrivateRibbonButtonGroupWidgetItem(QAction* a, QWidget* w, bool cw)
    : action(a), widget(w), customWidget(cw)
{
}

//===================================================
// SARibbonButtonGroupWidget
//===================================================

SARibbonButtonGroupWidget::SARibbonButtonGroupWidget(QWidget* parent)
    : QFrame(parent), d_ptr(new SARibbonButtonGroupWidget::PrivateData(this))
{
    d_ptr->init();
}

SARibbonButtonGroupWidget::~SARibbonButtonGroupWidget()
{
    for (SAPrivateRibbonButtonGroupWidgetItem& item : d_ptr->mItems) {
        if (QWidgetAction* widgetAction = qobject_cast< QWidgetAction* >(item.action)) {
            if (item.customWidget) {
                widgetAction->releaseWidget(item.widget);
            }
        }
    }
}

QAction* SARibbonButtonGroupWidget::addAction(QAction* a)
{
    QWidget::addAction(a);
    return (a);
}

/**
 * @brief ����action
 * @note action������Ȩ��SARibbonButtonGroupWidget
 * @param text
 * @param icon
 * @param popMode
 * @return
 */
QAction* SARibbonButtonGroupWidget::addAction(const QString& text, const QIcon& icon, QToolButton::ToolButtonPopupMode popMode)
{
    QAction* a = new QAction(icon, text, this);

    addAction(a);
    SARibbonToolButton* btn = qobject_cast< SARibbonToolButton* >(d_ptr->mItems.back().widget);
    btn->setPopupMode(popMode);
    return (a);
}

QAction* SARibbonButtonGroupWidget::addMenu(QMenu* menu, QToolButton::ToolButtonPopupMode popMode)
{
    QAction* a = menu->menuAction();

    addAction(a);
    SARibbonToolButton* btn = qobject_cast< SARibbonToolButton* >(d_ptr->mItems.back().widget);
    btn->setPopupMode(popMode);
    return (a);
}

QAction* SARibbonButtonGroupWidget::addSeparator()
{
    QAction* a = new QAction(this);

    a->setSeparator(true);
    addAction(a);
    return (a);
}

QAction* SARibbonButtonGroupWidget::addWidget(QWidget* w)
{
    QWidgetAction* a = new QWidgetAction(this);

    a->setDefaultWidget(w);
    w->setAttribute(Qt::WA_Hover);
    addAction(a);
    return (a);
}

QSize SARibbonButtonGroupWidget::sizeHint() const
{
    return (layout()->sizeHint());
}

QSize SARibbonButtonGroupWidget::minimumSizeHint() const
{
    return (layout()->minimumSize());
}

/**
 * @brief ����action���¼�
 *
 * ���ﴦ����ActionAdded��ActionChanged��ActionRemoved�����¼�
 * ActionAddedʱ�����ɴ���
 * @param e
 */
void SARibbonButtonGroupWidget::actionEvent(QActionEvent* e)
{
    SAPrivateRibbonButtonGroupWidgetItem item;

    item.action = e->action();

    switch (e->type()) {
    case QEvent::ActionAdded: {
        if (QWidgetAction* widgetAction = qobject_cast< QWidgetAction* >(item.action)) {
            widgetAction->setParent(this);
            item.widget = widgetAction->requestWidget(this);
            if (item.widget != nullptr) {
                item.widget->setAttribute(Qt::WA_LayoutUsesWidgetRect);
                item.widget->show();
                item.customWidget = true;
            }
        } else if (item.action->isSeparator()) {
            SARibbonSeparatorWidget* sp = RibbonSubElementDelegate->createRibbonSeparatorWidget(this);
            sp->setTopBottomMargins(3, 3);
            item.widget = sp;
        }
        //����widget���Զ�����SARibbonToolbutton
        if (!item.widget) {
            SARibbonToolButton* button = RibbonSubElementDelegate->createRibbonToolButton(this);
            button->setAutoRaise(true);
            button->setFocusPolicy(Qt::NoFocus);
            button->setButtonType(SARibbonToolButton::SmallButton);
            button->setToolButtonStyle(Qt::ToolButtonIconOnly);
            button->setDefaultAction(item.action);
            //����QAction���������ð�ť�Ĵ�С

            QObject::connect(button, &SARibbonToolButton::triggered, this, &SARibbonButtonGroupWidget::actionTriggered);
            item.widget = button;
        }
        layout()->addWidget(item.widget);
        d_ptr->mItems.append(item);
    } break;

    case QEvent::ActionChanged: {
        //�ò������»���
        layout()->invalidate();
    } break;

    case QEvent::ActionRemoved: {
        item.action->disconnect(this);
        auto i = d_ptr->mItems.begin();
        for (; i != d_ptr->mItems.end();) {
            QWidgetAction* widgetAction = qobject_cast< QWidgetAction* >(i->action);
            if ((widgetAction != 0) && i->customWidget) {
                widgetAction->releaseWidget(i->widget);
            } else {
                // destroy the QToolButton/QToolBarSeparator
                i->widget->hide();
                i->widget->deleteLater();
            }
            i = d_ptr->mItems.erase(i);
        }
        layout()->invalidate();
    } break;

    default:
        break;
    }
}

/*** End of inlined file: SARibbonButtonGroupWidget.cpp ***/

/*** Start of inlined file: SARibbonStackedWidget.cpp ***/
#include <QEventLoop>
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>

/**
 * @brief The SARibbonStackedWidgetPrivate class
 */
class SARibbonStackedWidget::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonStackedWidget)
public:
    QEventLoop* eventLoop { nullptr };
    bool isAutoResize { true };

public:
    PrivateData(SARibbonStackedWidget* p) : q_ptr(p)
    {
    }

    void init()
    {
        // Parent->setFocusPolicy(Qt::StrongFocus);
    }
};

SARibbonStackedWidget::SARibbonStackedWidget(QWidget* parent)
    : QStackedWidget(parent), d_ptr(new SARibbonStackedWidget::PrivateData(this))
{
    d_ptr->init();
    setNormalMode();
}

SARibbonStackedWidget::~SARibbonStackedWidget()
{
    if (d_ptr->eventLoop) {
        d_ptr->eventLoop->exit();
    }
}

void SARibbonStackedWidget::setPopupMode()
{
    setMouseTracking(true);
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setFrameShape(QFrame::Panel);
}

bool SARibbonStackedWidget::isPopupMode() const
{
    return (windowFlags() & Qt::Popup);
}

void SARibbonStackedWidget::setNormalMode()
{
    if (d_ptr->eventLoop) {
        d_ptr->eventLoop->exit();
        d_ptr->eventLoop = nullptr;
    }
    setMouseTracking(false);
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    setFrameShape(QFrame::NoFrame);
}

bool SARibbonStackedWidget::isNormalMode() const
{
    return (!isPopupMode());
}

void SARibbonStackedWidget::exec()
{
    show();
    if (!isPopupMode()) {
        d_ptr->eventLoop = nullptr;
        return;
    }
    QEventLoop event;

    d_ptr->eventLoop = &event;
    event.exec();
    d_ptr->eventLoop = nullptr;
}

/**
 * @brief ����stacked����Ĵ��ڻ�����stacked�Ĵ�С�仯���仯��С
 *
 * Ĭ��Ϊtrue
 * @param autoresize
 */
void SARibbonStackedWidget::setAutoResize(bool autoresize)
{
    d_ptr->isAutoResize = autoresize;
}

bool SARibbonStackedWidget::isAutoResize() const
{
    return (d_ptr->isAutoResize);
}

/**
 * @brief ����tabbar��moveTab�����������������ڵ�index
 * @param from
 * @param to
 * @note �˲����ᴥ��widgetRemoved(int index)�ź�
 */
void SARibbonStackedWidget::moveWidget(int from, int to)
{
    QWidget* w = widget(from);

    removeWidget(w);
    insertWidget(to, w);
}

void SARibbonStackedWidget::hideEvent(QHideEvent* e)
{
    if (isPopupMode()) {
        if (d_ptr->eventLoop) {
            d_ptr->eventLoop->exit();
        }
    }
    setFocus();
    emit hidWindow();

    QStackedWidget::hideEvent(e);
}

/*** End of inlined file: SARibbonStackedWidget.cpp ***/

/*** Start of inlined file: SARibbonSeparatorWidget.cpp ***/
#include <QStylePainter>
#include <QPainter>
#include <QDebug>

SARibbonSeparatorWidget::SARibbonSeparatorWidget(int height, QWidget* parent)
    : QWidget(parent), m_topMargins(4), m_bottomMargins(4)
{
    setFixedSize(6, height);
}

SARibbonSeparatorWidget::SARibbonSeparatorWidget(QWidget* parent) : QWidget(parent), m_topMargins(4), m_bottomMargins(4)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setFixedWidth(6);
}

QSize SARibbonSeparatorWidget::sizeHint() const
{
    return (QSize(6, height()));
}

/**
 * @brief ���÷ָ��ߵ����¾���
 * @param top �ϱ߽磬Ĭ��Ϊ4
 * @param bottom �±߽磬Ĭ��Ϊ4
 */
void SARibbonSeparatorWidget::setTopBottomMargins(int top, int bottom)
{
    m_topMargins    = top;
    m_bottomMargins = bottom;
}

void SARibbonSeparatorWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setPen(palette().window().color().darker(114));
    int x1 = rect().center().x();

    painter.drawLine(QPoint(x1, rect().top() + m_topMargins), QPoint(x1, rect().bottom() - m_bottomMargins));
}

/*** End of inlined file: SARibbonSeparatorWidget.cpp ***/

/*** Start of inlined file: SARibbonCtrlContainer.cpp ***/
#include <QHBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QStylePainter>
#include <QDebug>
#include <QLabel>

/**
 * @brief The SARibbonCtrlContainerPrivate class
 */
class SARibbonCtrlContainer::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonCtrlContainer)
public:
    QWidget* containerWidget { nullptr };
    QHBoxLayout* horizontalLayout { nullptr };
    QLabel* labelPixmap { nullptr };
    QLabel* labelText { nullptr };
    QSize iconSize { 24, 24 };
    QIcon icon;
    PrivateData(SARibbonCtrlContainer* p) : q_ptr(p)
    {
        horizontalLayout = new QHBoxLayout(p);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);

        labelPixmap = new QLabel(p);
        labelPixmap->setObjectName(QString::fromUtf8("labelPixmap"));
        labelPixmap->setAlignment(Qt::AlignCenter);
        horizontalLayout->addWidget(labelPixmap);

        labelText = new QLabel(p);
        labelText->setObjectName(QString::fromUtf8("labelText"));
        horizontalLayout->addWidget(labelText);
    }

    void setContainerWidget(QWidget* w)
    {
        if (containerWidget) {
            //ԭ����widget
            QWidget* oldwidget = containerWidget;
            takeContainerWidget(oldwidget);
            oldwidget->deleteLater();
        }
        containerWidget = w;
        if (!w) {
            return;
        }
        if (w->parent() != q_ptr) {
            w->setParent(q_ptr);
        }
        // ContainerWidget��Զ�����ұ�
        horizontalLayout->insertWidget(horizontalLayout->count(), w);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        w->setSizePolicy(sizePolicy);
    }

    void takeContainerWidget(QWidget* w)
    {
        int i = horizontalLayout->indexOf(w);
        if (i >= 0) {
            QLayoutItem* item = horizontalLayout->takeAt(i);
            delete item;
        }
    }
};

//===================================================
// SARibbonCtrlContainer
//===================================================
SARibbonCtrlContainer::SARibbonCtrlContainer(QWidget* parent)
    : QWidget(parent), d_ptr(new SARibbonCtrlContainer::PrivateData(this))
{
}

SARibbonCtrlContainer::~SARibbonCtrlContainer()
{
}

QWidget* SARibbonCtrlContainer::getContainerWidget()
{
    return (d_ptr->containerWidget);
}

const QWidget* SARibbonCtrlContainer::getContainerWidget() const
{
    return (d_ptr->containerWidget);
}

void SARibbonCtrlContainer::setEnableShowIcon(bool b)
{
    d_ptr->labelPixmap->setVisible(b);
}

void SARibbonCtrlContainer::setEnableShowTitle(bool b)
{
    d_ptr->labelText->setVisible(b);
}

/**
 * @brief �ж��Ƿ������������
 * @return
 */
bool SARibbonCtrlContainer::hasContainerWidget() const
{
    return (d_ptr->containerWidget != nullptr);
}

/**
 * @brief ����ͼ��
 * @param i
 */
void SARibbonCtrlContainer::setIcon(const QIcon& i)
{
    d_ptr->icon = i;
    d_ptr->labelPixmap->setPixmap(i.pixmap(d_ptr->iconSize));
}

/**
 * @brief ��ȡͼ��
 * @return
 */
QIcon SARibbonCtrlContainer::getIcon() const
{
    return d_ptr->icon;
}

/**
 * @brief ��������
 * @param t
 */
void SARibbonCtrlContainer::setText(const QString& t)
{
    d_ptr->labelText->setText(t);
}

/**
 * @brief ��ȡ����
 * @return
 */
QString SARibbonCtrlContainer::getText() const
{
    return d_ptr->labelText->text();
}

void SARibbonCtrlContainer::setContainerWidget(QWidget* w)
{
    d_ptr->setContainerWidget(w);
}

/*** End of inlined file: SARibbonCtrlContainer.cpp ***/

/*** Start of inlined file: SARibbonQuickAccessBar.cpp ***/
#include <QGuiApplication>

/**
 * @brief The SARibbonQuickAccessBarPrivate class
 */
class SARibbonQuickAccessBar::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonQuickAccessBar)
public:
    PrivateData(SARibbonQuickAccessBar* p);

public:
    SARibbonButtonGroupWidget* groupWidget { nullptr };
};
SARibbonQuickAccessBar::PrivateData::PrivateData(SARibbonQuickAccessBar* p) : q_ptr(p)
{
}

//===================================================
// SARibbonQuickAccessBar
//===================================================
SARibbonQuickAccessBar::SARibbonQuickAccessBar(QWidget* parent)
    : SARibbonCtrlContainer(parent), d_ptr(new SARibbonQuickAccessBar::PrivateData(this))
{
    d_ptr->groupWidget = new SARibbonButtonGroupWidget(this);
    setContainerWidget(d_ptr->groupWidget);
}

SARibbonQuickAccessBar::~SARibbonQuickAccessBar()
{
}

void SARibbonQuickAccessBar::addSeparator()
{
    d_ptr->groupWidget->addSeparator();
}

void SARibbonQuickAccessBar::addAction(QAction* act)
{
    d_ptr->groupWidget->addAction(act);
}

void SARibbonQuickAccessBar::addWidget(QWidget* w)
{
    d_ptr->groupWidget->addWidget(w);
}

void SARibbonQuickAccessBar::addMenu(QMenu* m, QToolButton::ToolButtonPopupMode popMode)
{
    d_ptr->groupWidget->addMenu(m, popMode);
}

/*** End of inlined file: SARibbonQuickAccessBar.cpp ***/

/*** Start of inlined file: SARibbonTabBar.cpp ***/
SARibbonTabBar::SARibbonTabBar(QWidget* parent) : QTabBar(parent), m_tabMargin(6, 0, 0, 0)
{
    setExpanding(false);
}

const QMargins& SARibbonTabBar::tabMargin() const
{
    return (m_tabMargin);
}

void SARibbonTabBar::setTabMargin(const QMargins& tabMargin)
{
    m_tabMargin = tabMargin;
}

/*** End of inlined file: SARibbonTabBar.cpp ***/

/*** Start of inlined file: SARibbonControlButton.cpp ***/
SARibbonControlButton::SARibbonControlButton(QWidget* parent) : QToolButton(parent)
{
}

/*** End of inlined file: SARibbonControlButton.cpp ***/

/*** Start of inlined file: SARibbonMenu.cpp ***/
#include <QWidgetAction>

SARibbonMenu::SARibbonMenu(QWidget* parent) : QMenu(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

SARibbonMenu::SARibbonMenu(const QString& title, QWidget* parent) : QMenu(title, parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

QAction* SARibbonMenu::addRibbonMenu(SARibbonMenu* menu)
{
    return (QMenu::addMenu(menu));
}

SARibbonMenu* SARibbonMenu::addRibbonMenu(const QString& title)
{
    SARibbonMenu* menu = new SARibbonMenu(title, this);

    return (menu);
}

SARibbonMenu* SARibbonMenu::addRibbonMenu(const QIcon& icon, const QString& title)
{
    SARibbonMenu* menu = new SARibbonMenu(title, this);

    menu->setIcon(icon);
    return (menu);
}

QAction* SARibbonMenu::addWidget(QWidget* w)
{
    QWidgetAction* action = new QWidgetAction(this);

    action->setDefaultWidget(w);
    addAction(action);
    return (action);
}

/*** End of inlined file: SARibbonMenu.cpp ***/

/*** Start of inlined file: SARibbonPannelOptionButton.cpp ***/
#include <QAction>

SARibbonPannelOptionButton::SARibbonPannelOptionButton(QWidget* parent) : QToolButton(parent)
{
    setAutoRaise(true);
    setCheckable(false);
    setToolButtonStyle(Qt::ToolButtonIconOnly);
    setFixedSize(16, 16);
    setIconSize(QSize(10, 10));
    setIcon(QIcon(":/image/resource/ribbonPannelOptionButton.png"));
}

void SARibbonPannelOptionButton::connectAction(QAction* action)
{
    connect(this, &SARibbonPannelOptionButton::clicked, action, &QAction::trigger);
}

/*** End of inlined file: SARibbonPannelOptionButton.cpp ***/

/*** Start of inlined file: SARibbonPannelItem.cpp ***/
SARibbonPannelItem::SARibbonPannelItem(QWidget* widget) : QWidgetItem(widget), action(nullptr), customWidget(false)
{
}

bool SARibbonPannelItem::isEmpty() const
{
    return (action == 0 || !action->isVisible());
}

/*** End of inlined file: SARibbonPannelItem.cpp ***/

/*** Start of inlined file: SARibbonPannelLayout.cpp ***/
#include <QWidgetAction>
#include <QQueue>
#include <set>

#define SARibbonPannelLayout_DEBUG_PRINT 0
#define HELP_DRAW_RECT(p, rect)                                                                                        \
    do {                                                                                                               \
        p.save();                                                                                                      \
        QPen _pen(Qt::DashLine);                                                                                       \
        _pen.setColor(Qt::blue);                                                                                       \
        p.setPen(_pen);                                                                                                \
        p.setBrush(QBrush());                                                                                          \
        p.drawRect(rect);                                                                                              \
        p.restore();                                                                                                   \
    } while (0)

QMargins SARibbonPannelLayout::s_contentsMargins = QMargins(1, 1, 1, 1);

SARibbonPannelLayout::SARibbonPannelLayout(QWidget* p)
    : QLayout(p), m_columnCount(0), m_expandFlag(false), m_dirty(true)
{
    setSpacing(1);
    SARibbonPannel* tb = qobject_cast< SARibbonPannel* >(p);

    if (!tb) {
        return;
    }
}

SARibbonPannelLayout::~SARibbonPannelLayout()
{
    while (!m_items.isEmpty()) {
        SARibbonPannelItem* item = m_items.takeFirst();
        if (QWidgetAction* widgetAction = qobject_cast< QWidgetAction* >(item->action)) {
            if (item->customWidget) {
                widgetAction->releaseWidget(item->widget());
            }
        }
        delete item;
    }
}

/**
 * @brief ͨ��action��������������actionEvent���action��
 * @param action
 * @return û�в鵽����-1
 */
int SARibbonPannelLayout::indexOf(QAction* action) const
{
    for (int i = 0; i < m_items.count(); ++i) {
        if (m_items.at(i)->action == action) {
            return (i);
        }
    }
    return (-1);
}

void SARibbonPannelLayout::addItem(QLayoutItem* item)
{
    Q_UNUSED(item);
    qWarning("SARibbonPannelLayout::addItem(): please use addAction() instead");
    return;
}

/**
 * @brief SARibbonPannel��Ҫͨ���˺��������action
 * @param act
 * @param rp ���ֲ���
 */
void SARibbonPannelLayout::insertAction(int index, QAction* act, SARibbonPannelItem::RowProportion rp)
{
    index                    = qMax(0, index);
    index                    = qMin(m_items.count(), index);
    SARibbonPannelItem* item = createItem(act, rp);

    if (item) {
        m_items.insert(index, item);
        //�����Ҫ���¼���ߴ�
        invalidate();
    }
}

QLayoutItem* SARibbonPannelLayout::itemAt(int index) const
{
    if ((index < 0) || (index >= m_items.count())) {
        return (nullptr);
    }
    return (m_items.at(index));
}

QLayoutItem* SARibbonPannelLayout::takeAt(int index)
{
    if ((index < 0) || (index >= m_items.count())) {
        return (nullptr);
    }
    SARibbonPannelItem* item = m_items.takeAt(index);

    QWidgetAction* widgetAction = qobject_cast< QWidgetAction* >(item->action);

    if ((widgetAction != 0) && item->customWidget) {
        widgetAction->releaseWidget(item->widget());
    } else {
        // destroy the QToolButton/QToolBarSeparator
        item->widget()->hide();
        item->widget()->deleteLater();
    }

    invalidate();
    return (item);
}

int SARibbonPannelLayout::count() const
{
    return (m_items.count());
}

bool SARibbonPannelLayout::isEmpty() const
{
    return (m_items.isEmpty());
}

void SARibbonPannelLayout::invalidate()
{
    m_dirty = true;
    QLayout::invalidate();
}

Qt::Orientations SARibbonPannelLayout::expandingDirections() const
{
    return (Qt::Horizontal);
}

QSize SARibbonPannelLayout::minimumSize() const
{
    return (m_sizeHint);
}

QSize SARibbonPannelLayout::sizeHint() const
{
    return (m_sizeHint);
}

/**
 * @brief ͨ��action��ȡSARibbonPannelItem
 * @param action
 * @return ���û�з���nullptr
 */
SARibbonPannelItem* SARibbonPannelLayout::pannelItem(QAction* action) const
{
    int index = indexOf(action);

    if (index >= 0) {
        return (m_items[ index ]);
    }
    return (nullptr);
}

/**
 * @brief ��ȡ���һ����ӵ�item
 * @return ���û�з���nullptr
 */
SARibbonPannelItem* SARibbonPannelLayout::lastItem() const
{
    if (m_items.isEmpty()) {
        return (nullptr);
    }
    return (m_items.last());
}

/**
 * @brief ��ȡ������ɵĴ���
 * @return ����޴��ڻ���itemΪ�գ�����nullptr
 */
QWidget* SARibbonPannelLayout::lastWidget() const
{
    SARibbonPannelItem* item = lastItem();

    if (item) {
        return (item->widget());
    }
    return (nullptr);
}

/**
 * @brief �ƶ�����item
 * @param from
 * @param to
 * @note �ƶ�������ж�ʧЧ����Ҫ���²���
 */
void SARibbonPannelLayout::move(int from, int to)
{
    if (from == to) {
        return;
    }
    if (to < 0) {
        to = 0;
    }
    if (to >= count()) {
        to = count() - 1;
    }
    m_items.move(from, to);
    invalidate();
}

/**
 * @brief �ж��Ƿ���Ҫ���²���
 * @return
 */
bool SARibbonPannelLayout::isDirty() const
{
    return (m_dirty);
}

/**
 * @brief �����ͼ��ĸ߶�
 * @param setrect
 * @param pannel
 * @return
 */
int SARibbonPannelLayout::calcLargeHeight(const QRect& setrect, const SARibbonPannel* pannel)
{
    const QMargins& mag = pannelContentsMargins();
    return setrect.height() - mag.top() - mag.bottom() - pannel->titleHeight();
}

/**
 * @brief ȫ�ֵ�contentsMargins
 *
 * ����ribbonbar�ĸ߶ȹ�����ҪԤ��֪��pannel��contentsMargins��������Ҫ����Ϊȫ�֣�
 * ���⣬����Ϊȫ��Ҳ��Ϊ�˷���ͳһ
 *
 * @return
 */
const QMargins& SARibbonPannelLayout::pannelContentsMargins()
{
    return s_contentsMargins;
}

/**
 * @brief ȫ�ֵ�contentsMargins
 * @note SARibbonStyleOption���õ��˺������������ú�������Ҫ�ֶ����¼���SARibbonStyleOption������,@sa SARibbonStyleOption::recalc
 * @sa SARibbonStyleOption
 * @param m
 */
void SARibbonPannelLayout::setPannelContentsMargins(const QMargins& m)
{
    s_contentsMargins = m;
}

/**
 * @brief ��������action
 */
void SARibbonPannelLayout::layoutActions()
{
    if (m_dirty) {
        updateGeomArray(geometry());
    }
    QList< QWidget* > showWidgets, hideWidgets;

#if SARibbonPannelLayout_DEBUG_PRINT
    qDebug() << "\r\n\r\n =============================================="
                "\r\n SARibbonPannelLayout::layoutActions"
             << " \r\n name:" << parentWidget()->windowTitle() << " sizehint:" << this->sizeHint();
#endif
    for (SARibbonPannelItem* item : qAsConst(m_items)) {
        if (item->isEmpty()) {
            hideWidgets << item->widget();
        } else {
            item->setGeometry(item->itemWillSetGeometry);
            //            item->widget()->setFixedSize(item->itemWillSetGeometry.size());
            //            item->widget()->move(item->itemWillSetGeometry.topLeft());
            showWidgets << item->widget();
#if SARibbonPannelLayout_DEBUG_PRINT
            qDebug() << "[" << item->rowIndex << "," << item->columnIndex << "]"
                     << " -> " << item->itemWillSetGeometry << ":" << item->widget()->metaObject()->className();
#endif
        }
    }

    // ���������������show��hide��Ϊ��ᴥ��SARibbonPannelLayout���ػ棬����ѭ�����ƣ��ǳ�Ӱ��Ч��
    for (QWidget* w : qAsConst(showWidgets)) {
        w->show();
    }
    for (QWidget* w : qAsConst(hideWidgets)) {
        w->hide();
    }
}

/**
 * @brief ��actionת��Ϊitem
 *
 * �˺����ο�QToolBarItem *QToolBarLayout::createItem(QAction *action)
 *
 * ������ͨQAction���˺����ᴴ��SARibbonToolButton��SARibbonToolButton�����Ͳο�SARibbonPannelItem::RowProportion��
 * @param action
 * @param rp �и�ռ�����
 * @return ת����SARibbonPannelItem
 * @note ÿ��SARibbonPannelItem���ն���Я��һ��widget���������QWidgetAction�Ļ�����ֱ��ʹ��QWidgetAction����widget��
 * ������ڲ�����һ��SARibbonToolButton
 *
 */
SARibbonPannelItem* SARibbonPannelLayout::createItem(QAction* action, SARibbonPannelItem::RowProportion rp)
{
    bool customWidget      = false;
    QWidget* widget        = nullptr;
    SARibbonPannel* pannel = qobject_cast< SARibbonPannel* >(parentWidget());

    if (!pannel) {
        return (nullptr);
    }
    if (QWidgetAction* widgetAction = qobject_cast< QWidgetAction* >(action)) {
        widget = widgetAction->requestWidget(pannel);
        if (widget != nullptr) {
            widget->setAttribute(Qt::WA_LayoutUsesWidgetRect);
            customWidget = true;  //���Ϊtrue�����Ƴ���ʱ���ǲ����������ڽ���ɾ����falseĬ�ϻ����ɾ����SARibbonSeparatorWidget��SARibbonToolButton
        }
    } else if (action->isSeparator()) {
        SARibbonSeparatorWidget* sep = RibbonSubElementDelegate->createRibbonSeparatorWidget(pannel);
        widget                       = sep;
    }
    //����widget���Զ�����SARibbonToolbutton
    if (!widget) {
        SARibbonToolButton::RibbonButtonType buttonType = ((rp == SARibbonPannelItem::Large) ? SARibbonToolButton::LargeButton
                                                                                             : SARibbonToolButton::SmallButton);

        SARibbonToolButton* button = RibbonSubElementDelegate->createRibbonToolButton(pannel);
        button->setFocusPolicy(Qt::NoFocus);
        button->setButtonType(buttonType);
        button->setDefaultAction(action);
        //����QAction���������ð�ť�Ĵ�С

        QObject::connect(button, &SARibbonToolButton::triggered, pannel, &SARibbonPannel::actionTriggered);
        widget = button;
    }
    //��ʱ�ܻ���widget
    widget->hide();
    SARibbonPannelItem* result = new SARibbonPannelItem(widget);

    result->rowProportion = rp;
    result->customWidget  = customWidget;
    result->action        = action;
    return (result);
}

/**
 * @brief ���³ߴ�
 */
void SARibbonPannelLayout::updateGeomArray(const QRect& setrect)
{
    SARibbonPannel* pannel = qobject_cast< SARibbonPannel* >(parentWidget());

    if (!pannel) {
        return;
    }

#if SARibbonPannelLayout_DEBUG_PRINT
    qDebug() << "SARibbonPannelLayout::updateGeomArray(" << setrect << ")";
#endif
    int height          = setrect.height();
    const QMargins& mag = pannelContentsMargins();
    const int spacing   = this->spacing();
    int x               = mag.left();
    //��ȡpannel�Ĳ���ģʽ 3�л���2��
    // rowcount ��ribbon���У���2�к�3������
    const short rowCount = (pannel->pannelLayoutMode() == SARibbonPannel::ThreeRowMode) ? 3 : 2;
    // largeHeight�Ƕ�Ӧlargeռ�ȵĸ߶�,pannel->titleHeight()������ģʽ����0
    const int largeHeight = calcLargeHeight(setrect, pannel);

    m_largeHeight = largeHeight;
    //����smallHeight�ĸ߶�
    const int smallHeight = (largeHeight - (rowCount - 1) * spacing) / rowCount;
    // Medium�е�yλ��
    const int yMediumRow0 = (2 == rowCount) ? mag.top() : (mag.top() + ((largeHeight - 2 * smallHeight) / 3));
    const int yMediumRow1 = (2 == rowCount) ? (mag.top() + smallHeight + spacing)
                                            : (mag.top() + ((largeHeight - 2 * smallHeight) / 3) * 2 + smallHeight);
    // Small�е�yλ��
    const int ySmallRow0 = mag.top();
    const int ySmallRow1 = mag.top() + smallHeight + spacing;
    const int ySmallRow2 = mag.top() + 2 * (smallHeight + spacing);
    // row���ڼ�¼�¸�itemӦ�����ڵڼ��У�item->rowIndex���ڼ�¼��ǰ���ڵڼ��У�
    // item->rowIndex��Ҫ����SARibbonPannelItem::Medium
    short row  = 0;
    int column = 0;
    //��¼ÿ�����Ŀ��
    int columMaxWidth = 0;
    //��¼�ܿ��
    int totalWidth = 0;

    int itemCount = m_items.count();

#if SARibbonPannelLayout_DEBUG_PRINT
    qDebug() << "\r\n\r\n============================================="
             << "\r\nSARibbonPannelLayout::updateGeomArray()"
             << " setrect:" << setrect << "\r\npannel name:" << pannel->windowTitle()
             << "\r\n largeHeight:" << largeHeight << "\r\n smallHeight:" << smallHeight << "\r\n rowCount:" << rowCount;
#endif

    //���е�һ������ռ��
    SARibbonPannelItem::RowProportion thisColumnRP0 = SARibbonPannelItem::None;
    SARibbonPannelItem* lastGeomItem                = nullptr;  //��¼���һ������λ�õ�item
    for (int i = 0; i < itemCount; ++i) {
        SARibbonPannelItem* item = m_items.at(i);
        if (item->isEmpty()) {
            //�����hide��ֱ������
#if SARibbonPannelLayout_DEBUG_PRINT
            qDebug() << item->widget()->metaObject()->className() << "is hide"
                     << " row:" << row << " col:" << column;
#endif
            item->rowIndex    = -1;
            item->columnIndex = -1;
            continue;
        }

        QSize hint           = item->sizeHint();
        Qt::Orientations exp = item->expandingDirections();
        if (item->widget()) {
            //�д�����ˮƽ��չ������Ϊ��չ
            if ((item->widget()->sizePolicy().horizontalPolicy() & QSizePolicy::ExpandFlag)) {
                m_expandFlag = true;
            }
        }
        SARibbonPannelItem::RowProportion rp = item->rowProportion;
        if (SARibbonPannelItem::None == rp) {
            //Ϊ������ռ�ȵ��Ǵ�ֱ��չ���Ͷ���ΪLargeռ�ȣ��������smallռ��
            if (exp & Qt::Vertical) {
                rp = SARibbonPannelItem::Large;
            } else {
                rp = SARibbonPannelItem::Small;
            }
        }
        //��ʼ����ռ�Ⱥ�layoutmode������
        switch (rp) {
        case SARibbonPannelItem::Large: {
            // ������Large��������Ǵ������еĵ�һ�У�����Ҫ���л��д���
            // ��largeһֱ��������һ�еĿ�ʼ
            if (row != 0) {
                x += (columMaxWidth + spacing);
                ++column;
                row           = 0;
                columMaxWidth = 0;
            }
            //
            item->rowIndex            = 0;
            item->columnIndex         = column;
            item->itemWillSetGeometry = QRect(x, mag.top(), hint.width(), largeHeight);
            columMaxWidth             = hint.width();
            //���У�x�Զ��������¸����꣬�������ӣ��������㣬����п����
            x += (columMaxWidth + spacing);
            row           = 0;
            columMaxWidth = 0;
            ++column;
        } break;

        case SARibbonPannelItem::Medium: {
            // 2��ģʽ��Medium��small�ȼ�
            if (2 == rowCount) {
                if (0 == row) {
                    item->rowIndex            = 0;
                    item->columnIndex         = column;
                    item->itemWillSetGeometry = QRect(x, yMediumRow0, hint.width(), smallHeight);
                    thisColumnRP0             = SARibbonPannelItem::Medium;
                    columMaxWidth             = hint.width();
                    //�¸�rowΪ1
                    row = 1;
                    // x����
                } else {
                    item->rowIndex            = 1;
                    item->columnIndex         = column;
                    item->itemWillSetGeometry = QRect(x, yMediumRow1, hint.width(), smallHeight);
                    //���ϸ����бȽϵõ�����
                    columMaxWidth = qMax(columMaxWidth, hint.width());
                    //���У�x�Զ��������¸����꣬�������ӣ��������㣬����п����
                    x += (columMaxWidth + spacing);
                    row           = 0;
                    columMaxWidth = 0;
                    ++column;
                }
            } else {
                // 3��ģʽ
                if (0 == row) {
                    item->rowIndex            = 0;
                    item->columnIndex         = column;
                    item->itemWillSetGeometry = QRect(x, yMediumRow0, hint.width(), smallHeight);
                    thisColumnRP0             = SARibbonPannelItem::Medium;
                    columMaxWidth             = hint.width();
                    row                       = 1;
                    // x����
                } else if (1 == row) {
                    item->rowIndex            = 1;
                    item->columnIndex         = column;
                    item->itemWillSetGeometry = QRect(x, yMediumRow1, hint.width(), smallHeight);
                    columMaxWidth             = qMax(columMaxWidth, hint.width());
                    //���У�x�Զ��������¸����꣬�������ӣ��������㣬����п����
                    x += (columMaxWidth + spacing);
                    row           = 0;
                    columMaxWidth = 0;
                    ++column;
                } else {
                    //����ģʽһ������ᷢ���ڵ�ǰ��ǰ������Small�������һ��Medium
                    //��ʱ��Ҫ�Ȼ���
                    //���У�x�Զ��������¸����꣬�������ӣ��������㣬����п����
                    x += (columMaxWidth + spacing);
                    ++column;
                    //���к��ʱ�ȼ���0 == row
                    item->rowIndex            = 0;
                    item->columnIndex         = column;
                    item->itemWillSetGeometry = QRect(x, yMediumRow0, hint.width(), smallHeight);
                    thisColumnRP0             = SARibbonPannelItem::Medium;
                    columMaxWidth             = hint.width();
                    row                       = 1;
                }
            }
        } break;

        case SARibbonPannelItem::Small: {
            if (0 == row) {
                //��һ��
                item->rowIndex            = 0;
                item->columnIndex         = column;
                item->itemWillSetGeometry = QRect(x, ySmallRow0, hint.width(), smallHeight);
                thisColumnRP0             = SARibbonPannelItem::Small;
                columMaxWidth             = hint.width();
                //�¸�rowΪ1
                row = 1;
                // x����
            } else if (1 == row) {
                //�ڶ���
                item->rowIndex            = 1;
                item->columnIndex         = column;
                item->itemWillSetGeometry = QRect(x, ySmallRow1, hint.width(), smallHeight);
                if ((3 == rowCount) && (SARibbonPannelItem::Medium == thisColumnRP0)) {
                    //����ģʽ�����ҵ�һ����Medium
                    item->itemWillSetGeometry = QRect(x, yMediumRow1, hint.width(), smallHeight);
                }
                //���ϸ����бȽϵõ�����
                columMaxWidth = qMax(columMaxWidth, hint.width());
                //����Ҫ�����л������У�ȷ���Ƿ�Ҫ����
                if (2 == rowCount) {
                    //����ģʽ������
                    //���У�x�Զ��������¸����꣬�������ӣ��������㣬����п����
                    x += (columMaxWidth + spacing);
                    row           = 0;
                    columMaxWidth = 0;
                    ++column;
                } else {
                    //����ģʽ��������������
                    row = 2;
                    // x����
                }
                if ((3 == rowCount) && (SARibbonPannelItem::Medium == thisColumnRP0)) {
                    //����ģʽ�����ҵ�һ����Medium������
                    //���У�x�Զ��������¸����꣬�������ӣ��������㣬����п����
                    x += (columMaxWidth + spacing);
                    row           = 0;
                    columMaxWidth = 0;
                    ++column;
                }
            } else {
                //������
                item->rowIndex            = 2;
                item->columnIndex         = column;
                item->itemWillSetGeometry = QRect(x, ySmallRow2, hint.width(), smallHeight);
                //���ϸ����бȽϵõ�����
                columMaxWidth = qMax(columMaxWidth, hint.width());
                //���У�x�Զ��������¸����꣬�������ӣ��������㣬����п����
                x += (columMaxWidth + spacing);
                row           = 0;
                columMaxWidth = 0;
                ++column;
            }
        } break;

        default:
            //�����ܳ���
            break;
        }
        lastGeomItem = item;
#if SARibbonPannelLayout_DEBUG_PRINT
        qDebug() << item->widget()->metaObject()->className() << " rp:" << rp << " row:" << item->rowIndex
                 << " col:" << item->columnIndex << " new row:" << row << " new column:" << column
                 << " itemWillSetGeometry:" << item->itemWillSetGeometry << " sizeHint:" << hint << " x:" << x;
#endif
    }
    //���һ��Ԫ�أ���������
    // 2022-06-20 �˾䱾����ѭ�����棬������һ��Ԫ�����أ��ᵼ���޷�������жϵ����쳣
    if (lastGeomItem) {  //���һ��Ԫ�أ�����totalWidth
        if (lastGeomItem->columnIndex != column) {
            //˵�����һ��Ԫ�ش������λ�ã������˻��У���ʱ��ʵ������Ҫ��1��ֱ�ӵ���column����
            m_columnCount = column;
            //�������һ��Ԫ�ش����˻��У�xֵ����һ�е�λ�ã�ֱ����ΪtotalWidth
            totalWidth = x + mag.right();
        } else {
            //˵�����һ��Ԫ�ش��ڷ����λ�ã�û�д�����һ�����У���ʱ��ʵ��������column����+1
            m_columnCount = column + 1;
            //�������һ��Ԫ��δ�������У���Ҫ����totalWidth
            totalWidth = x + columMaxWidth + spacing + mag.right();
        }
    }
    //����optionButton����£���2��ģʽ����Ҫ����totalWidth
    if (pannel->isTwoRow()) {
        if (pannel->isHaveOptionAction()) {
            totalWidth += pannel->optionActionButtonSize().width();
        }
    }
    //�����������д��ں���������չ���ԵĴ���
    if (totalWidth < setrect.width()) {
        //˵������������չ���ԵĴ���
        recalcExpandGeomArray(setrect);
    }
    this->m_sizeHint = QSize(totalWidth, height);
}

void SARibbonPannelLayout::recalcExpandGeomArray(const QRect& setrect)
{
    //��������չ�ĳߴ�
    int expandwidth = setrect.width() - this->m_sizeHint.width();

    if (expandwidth <= 0) {
        //û�б�Ҫ����
        return;
    }
    //����չ��Ϣ
    struct _columnExpandInfo
    {
        int oldColumnWidth      = 0;   ///< ԭ�����п�
        int columnMaximumWidth  = -1;  ///< �е������
        int columnExpandedWidth = 0;   ///< ��չ���еĿ��
        QList< SARibbonPannelItem* > expandItems;
    };
    //�˱������ڼ�¼����ˮƽ��չ���кͿؼ����ڲ��ֽ�����������пռ䣬�Ͱ�ˮƽ��չ�Ŀؼ�������չ
    QMap< int, _columnExpandInfo > columnExpandInfo;

    for (SARibbonPannelItem* item : qAsConst(m_items)) {
        if ((!item->isEmpty()) && item->expandingDirections() & Qt::Horizontal) {
            //ֻ��ȡ�ɼ���
            QMap< int, _columnExpandInfo >::iterator i = columnExpandInfo.find(item->columnIndex);
            if (i == columnExpandInfo.end()) {
                i = columnExpandInfo.insert(item->columnIndex, _columnExpandInfo());
            }
            i.value().expandItems.append(item);
        }
    }
    if (columnExpandInfo.size() <= 0) {
        //û����Ҫ��չ�ľ��˳�
        return;
    }
    //��ȡ�����չ���кͿؼ��󣬼����Ӧ���еĳߴ�
    //��������չ�ĳߴ�
    int oneColCanexpandWidth = expandwidth / columnExpandInfo.size();

    for (QMap< int, _columnExpandInfo >::iterator i = columnExpandInfo.begin(); i != columnExpandInfo.end();) {
        int& oldColumnWidth     = i.value().oldColumnWidth;
        int& columnMaximumWidth = i.value().columnMaximumWidth;
        this->columnWidthInfo(i.key(), oldColumnWidth, columnMaximumWidth);
        if ((oldColumnWidth <= 0) || (oldColumnWidth > columnMaximumWidth)) {
            //���С��0˵��û������У����������쳣��ɾ������
            // oldColumnWidth > columnMaximumWidthҲ���쳣
            i = columnExpandInfo.erase(i);
            continue;
        }
        //��ʼ����
        int colwidth = oneColCanexpandWidth + oldColumnWidth;  //����չ��
        if (colwidth >= columnMaximumWidth) {
            //�������Ҫ��
            i.value().columnExpandedWidth = columnMaximumWidth;
        } else {
            i.value().columnExpandedWidth = colwidth;
        }
        ++i;
    }
    //���µ����ߴ�
    //���ڻ��漰�����еı���������Ҫ���ж�����һ��
    for (auto i = columnExpandInfo.begin(); i != columnExpandInfo.end(); ++i) {
        int moveXLen = i.value().columnExpandedWidth - i.value().oldColumnWidth;
        for (SARibbonPannelItem* item : qAsConst(m_items)) {
            if (item->isEmpty() || (item->columnIndex < i.key())) {
                //֮ǰ���в��ù�
                continue;
            }
            if (item->columnIndex == i.key()) {
                //���е���չ
                if (i.value().expandItems.contains(item)) {
                    //������Ҫ��չ��item����չ�ߴ�
                    item->itemWillSetGeometry.setWidth(i.value().columnExpandedWidth);
                } else {
                    //���в���չ��ģ�鱣��ԭ���ĳߴ�
                    continue;
                }
            } else {
                //������ƶ�
                item->itemWillSetGeometry.moveLeft(item->itemWillSetGeometry.x() + moveXLen);
            }
        }
    }
}

/**
 * @brief ���������е�����
 * @return <��������������>
 */
// QMap<int, QRect> SARibbonPannelLayout::columnsGeometry() const
//{
//    QMap<int, QRect> res;
//    for (SARibbonPannelItem *item:m_items){
//        if(item->isEmpty()){
//           continue;
//        }
//        QMap<int, QRect>::iterator i = res.find(item->columnIndex);
//        if(i == res.end())
//        {
//            QRect r = item->geometry();
//            r.setY(this->contentsMargins().top());
//            r.setHeight(m_largeHeight);
//            i = res.insert(item->columnIndex,r);
//        }
//        if(item->itemWillSetGeometry.width() > i.value().width()){
//            i.value().setWidth(item->itemWillSetGeometry.width());
//        }
//    }
//    return res;
//}

/**
 * @brief �������������㴰�ڵĿ�ȣ��Լ������
 * @param colindex
 * @param width �������û������У�����-1
 * @param maximum �������û������У�����-1
 */
void SARibbonPannelLayout::columnWidthInfo(int colindex, int& width, int& maximum) const
{
    width   = -1;
    maximum = -1;
    for (SARibbonPannelItem* item : m_items) {
        if (!item->isEmpty() && (item->columnIndex == colindex)) {
            width   = qMax(width, item->itemWillSetGeometry.width());
            maximum = qMax(maximum, item->widget()->maximumWidth());
        }
    }
}

void SARibbonPannelLayout::setGeometry(const QRect& rect)
{
    m_dirty = false;
    updateGeomArray(rect);
    QLayout::setGeometry(rect);
    layoutActions();
}

/*** End of inlined file: SARibbonPannelLayout.cpp ***/

/*** Start of inlined file: SARibbonPannel.cpp ***/
#include <QApplication>
#include <QResizeEvent>
#include <QAction>
#include <QIcon>
#include <QDebug>
#include <QGridLayout>
#include <QFontMetrics>
#include <QPainter>
#include <QApplication>
#include <QWidgetAction>
#include <QMenu>

#define HELP_DRAW_RECT(p, rect)                                                                                        \
    do {                                                                                                               \
        p.save();                                                                                                      \
        QPen _pen(Qt::DashLine);                                                                                       \
        _pen.setColor(Qt::blue);                                                                                       \
        p.setPen(_pen);                                                                                                \
        p.setBrush(QBrush());                                                                                          \
        p.drawRect(rect);                                                                                              \
        p.restore();                                                                                                   \
    } while (0)

class SARibbonPannel::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonPannel)
public:
    PrivateData(SARibbonPannel* p);
    //����m_pannelLayoutMode����gridLayoutӦ�����ӵ�����
    int rowadded();
    void createLayout();

    //�������һ����ӵ�action��Ӧ��button��ǰ�������һ����toolbutton�����򷵻�nullptr
    SARibbonToolButton* lastAddActionButton();

public:
    bool m_isCanCustomize { true };  ///< ��¼�Ƿ���Զ���
    int m_row { 0 };  ///< ��¼Сaction���ڵ�gridLayout������gridLayout�ܹ�����Ϊ6�У���������3�л�2�еİ�ť����
    SARibbonPannel::PannelLayoutMode m_pannelLayoutMode { SARibbonPannel::ThreeRowMode };  ///< pannel�Ĳ���ģʽ��Ĭ��Ϊ3��ģʽThreeRowMode
    SARibbonPannelLayout* m_layout { nullptr };
    SARibbonPannelOptionButton* m_optionActionButton { nullptr };  ///< ��������y����
    QPoint m_nextElementPosition;
    static int s_pannelTitleHeight;  ///< pannel��������ȫ�ָ߶�,Ĭ��Ϊ18
};

int SARibbonPannel::PrivateData::s_pannelTitleHeight = 15;

SARibbonPannel::PrivateData::PrivateData(SARibbonPannel* p) : q_ptr(p)
{
    createLayout();
}

int SARibbonPannel::PrivateData::rowadded()
{
    switch (m_pannelLayoutMode) {
    case SARibbonPannel::ThreeRowMode:
        return (2);

    case SARibbonPannel::TwoRowMode:
        return (3);

    default:
        break;
    }
    return (2);
}

void SARibbonPannel::PrivateData::createLayout()
{
    m_layout = new SARibbonPannelLayout(q_ptr);
    m_layout->setSpacing(2);
    m_layout->setContentsMargins(2, 2, 2, 2);
}

SARibbonToolButton* SARibbonPannel::PrivateData::lastAddActionButton()
{
    QWidget* w = m_layout->lastWidget();

    return (qobject_cast< SARibbonToolButton* >(w));
}

//==================================================
// SARibbonPannel
//==================================================

SARibbonPannel::SARibbonPannel(QWidget* parent) : QWidget(parent), d_ptr(new SARibbonPannel::PrivateData(this))
{
    setPannelLayoutMode(ThreeRowMode);
}

SARibbonPannel::SARibbonPannel(const QString& name, QWidget* parent)
    : QWidget(parent), d_ptr(new SARibbonPannel::PrivateData(this))
{
    setPannelLayoutMode(ThreeRowMode);
    setPannelName(name);
}

SARibbonPannel::~SARibbonPannel()
{
}

/**
 * @brief ��action�����������ý�action�У�action����Я����������
 * @param action
 * @param rp
 */
void SARibbonPannel::setActionRowProportionProperty(QAction* action, SARibbonPannelItem::RowProportion rp)
{
    if (action == nullptr) {
        return;
    }
    action->setProperty(SARibbonPannelItemRowProportionPropertyName, int(rp));
}

/**
 * @brief ��ȡaction��������
 * @param action
 * @return
 */
SARibbonPannelItem::RowProportion SARibbonPannel::getActionRowProportionProperty(QAction* action)
{
    bool isok = false;
    int r     = action->property(SARibbonPannelItemRowProportionPropertyName).toInt(&isok);

    if (isok) {
        return (static_cast< SARibbonPannelItem::RowProportion >(r));
    }
    return (SARibbonPannelItem::Large);
}

/**
 * @brief ����action������Ϊ�������Ծ�����ribbon pannel����ʾ��ʽ
 * @param action ��Ҫ���õ�action����action�����Ѿ���pannel��ӹ�
 * @param rp ��Ϊ
 */
void SARibbonPannel::setActionRowProportion(QAction* action, SARibbonPannelItem::RowProportion rp)
{
    if (action == nullptr) {
        return;
    }
    SARibbonPannelLayout* lay = d_ptr->m_layout;

    setActionRowProportionProperty(action, rp);
    if (lay) {
        SARibbonPannelItem* it = lay->pannelItem(action);
        if (it) {
            it->rowProportion = rp;
            lay->invalidate();
        }
    }
}

/**
 * @brief ���action
 * @param action action
 * @param rp ָ��action����ռ��
 * @return ���ض�Ӧ��SARibbonToolButton������Ǵ��ڣ����ص�toolbuttonΪnullptr
 */
SARibbonToolButton* SARibbonPannel::addAction(QAction* action, SARibbonPannelItem::RowProportion rp)
{
    if (action == nullptr) {
        return nullptr;
    }
    setActionRowProportionProperty(action, rp);
    addAction(action);

    return (d_ptr->lastAddActionButton());
}

/**
 * @brief ��Ӵ�ͼ��
 *
 * @param action
 * @sa ������ȡactiom��Ӧ��SARibbonToolButton,����ʹ��@ref actionToRibbonToolButton ����
 */
SARibbonToolButton* SARibbonPannel::addLargeAction(QAction* action)
{
    return (addAction(action, SARibbonPannelItem::Large));
}

/**
 * @brief ������ģʽ�£�ǿ�Ƽ�Ϊ2��action
 * @note ������ģʽ�£�Medium��Small�ȼ�
 * ��ҪӦ����ThreeRowMode��
 * @param action
 * @sa ������ȡactiom��Ӧ��SARibbonToolButton,����ʹ��@ref actionToRibbonToolButton ����
 */
SARibbonToolButton* SARibbonPannel::addMediumAction(QAction* action)
{
    return (addAction(action, SARibbonPannelItem::Medium));
}

/**
 * @brief ���Сͼ��
 * @param action
 * @sa ������ȡactiom��Ӧ��SARibbonToolButton,����ʹ��@ref actionToRibbonToolButton ����
 */
SARibbonToolButton* SARibbonPannel::addSmallAction(QAction* action)
{
    return (addAction(action, SARibbonPannelItem::Small));
}

/**
 * @brief ���һ��action
 * @param act
 * @param popMode ��ť����ʽ
 * @param rp action��pannel�е�ռλ�����Ĭ���Ǵ�ͼ��
 */
void SARibbonPannel::addAction(QAction* act, QToolButton::ToolButtonPopupMode popMode, SARibbonPannelItem::RowProportion rp)
{
    if (act == nullptr) {
        return;
    }
    setActionRowProportionProperty(act, rp);
    addAction(act);
    SARibbonToolButton* btn = d_ptr->lastAddActionButton();

    if (btn) {
        btn->setPopupMode(popMode);
    }
}

/**
 * @brief ���ɲ����һ��action
 *
 * ������Դ�action��������SARibbonPannel�������action
 *
 * @note action�ĸ���������ΪSARibbonPannel��SARibbonPannel��ɾ��ʱ����ɾ���Ӷ��󣬻�����actionҲɾ����
 * ��������actionҲɾ������Ҫ��action�������ø�����
 *
 * @param text action������
 * @param icon action��ͼ��
 * @param popMode ��ť����ʽ
 * @param rp action��pannel�е�ռλ�����Ĭ���Ǵ�ͼ��
 * @return ������ӵ�action
 */
QAction* SARibbonPannel::addAction(const QString& text, const QIcon& icon, QToolButton::ToolButtonPopupMode popMode, SARibbonPannelItem::RowProportion rp)
{
    QAction* action = new QAction(icon, text, this);
    addAction(action, popMode, rp);
    return (action);
}

/**
 * @brief ���һ����ͨ�˵�
 * @param menu
 * @param rp
 * @param popMode,�˵�����ģʽ��Ĭ��InstantPopupģʽ
 * @return
 */
SARibbonToolButton* SARibbonPannel::addMenu(QMenu* menu, SARibbonPannelItem::RowProportion rp, QToolButton::ToolButtonPopupMode popMode)
{
    if (menu == nullptr) {
        return nullptr;
    }
    QAction* action = menu->menuAction();

    addAction(action, rp);
    SARibbonToolButton* btn = d_ptr->lastAddActionButton();

    btn->setPopupMode(popMode);
    return (btn);
}

/**
 * @brief ���һ��ActionMenu
 * @param action
 * @param menu
 * @param rp
 * @return
 */
SARibbonToolButton* SARibbonPannel::addActionMenu(QAction* action, QMenu* menu, SARibbonPannelItem::RowProportion rp)
{
    SARibbonToolButton* btn = addAction(action, rp);
    if (nullptr == btn) {
        return nullptr;
    }
    btn->setMenu(menu);
    btn->setPopupMode(QToolButton::MenuButtonPopup);
    return (btn);
}

/**
 * @brief ���action menu,action menu��һ�������menu,���ɵ������action��Ҳ�ɵ����˵�
 * @param action ���������action����pannel�У�ͼ���Դ�action��ͼ��Ϊ׼
 * @param menu ��Ҫ������menu
 * @return ����
 */
SARibbonToolButton* SARibbonPannel::addLargeActionMenu(QAction* action, QMenu* menu)
{
    return (addActionMenu(action, menu, SARibbonPannelItem::Large));
}

SARibbonToolButton* SARibbonPannel::addLargeMenu(QMenu* menu, QToolButton::ToolButtonPopupMode popMode)
{
    return (addMenu(menu, SARibbonPannelItem::Large, popMode));
}

SARibbonToolButton* SARibbonPannel::addSmallMenu(QMenu* menu, QToolButton::ToolButtonPopupMode popMode)
{
    return (addMenu(menu, SARibbonPannelItem::Small, popMode));
}

/**
 * @brief ��Ӵ���
 *
 * @param w
 * @param rp
 * @return ����action(QWidgetAction)
 * @note SARibbonPannel���������˴����ڴ棬��delete SARibbonPannelʱ���˴��������������SARibbonPannel�����ᱻɾ��
 */
QAction* SARibbonPannel::addWidget(QWidget* w, SARibbonPannelItem::RowProportion rp)
{
    QWidgetAction* action = new QWidgetAction(this);

    action->setDefaultWidget(w);
    w->setAttribute(Qt::WA_Hover);
    setActionRowProportionProperty(action, rp);
    addAction(action);
    return (action);
}

/**
 * @brief ��Ӵ���,ռ��ribbon��һ��
 * @param w
 * @return ����action(QWidgetAction)
 */
QAction* SARibbonPannel::addSmallWidget(QWidget* w)
{
    return (addWidget(w, SARibbonPannelItem::Small));
}

/**
 * @brief ��Ӵ���,ռ��ribbon��һ��
 * @param w
 * @return
 */
QAction* SARibbonPannel::addMediumWidget(QWidget* w)
{
    return (addWidget(w, SARibbonPannelItem::Medium));
}

/**
 * @brief ��Ӵ��ڣ�ռ��������
 * @param w
 * @return ����action(QWidgetAction)
 */
QAction* SARibbonPannel::addLargeWidget(QWidget* w)
{
    return (addWidget(w, SARibbonPannelItem::Large));
}

/**
 * @brief SARibbonPannel::addGallery
 * @return
 * @note SARibbonPannel��ӵ��SARibbonGallery�Ĺ���Ȩ
 */
SARibbonGallery* SARibbonPannel::addGallery()
{
    SARibbonGallery* gallery = RibbonSubElementDelegate->createRibbonGallery(this);

    addWidget(gallery, SARibbonPannelItem::Large);

    setExpanding();
    return (gallery);
}

/**
 * @brief ��ӷָ���
 * @param top �ϱ߾� @default 6
 * @param bottom �±߾� @default 6
 */
QAction* SARibbonPannel::addSeparator(int top, int bottom)
{
    QAction* action = new QAction(this);

    action->setSeparator(true);
    setActionRowProportionProperty(action, SARibbonPannelItem::Large);
    addAction(action);
    QWidget* w                   = d_ptr->m_layout->lastWidget();
    SARibbonSeparatorWidget* sep = qobject_cast< SARibbonSeparatorWidget* >(w);

    if (sep) {
        sep->setTopBottomMargins(top, bottom);
    }
    return (action);
}

/**
 * @brief ��pannel�а�action��Ӧ��button��ȡ���������actionû�ж�Ӧ��button���ͷ���nullptr
 * @param action
 * @return ���actionû�ж�Ӧ��button���ͷ���nullptr
 */
SARibbonToolButton* SARibbonPannel::actionToRibbonToolButton(QAction* action)
{
    SARibbonPannelLayout* lay = qobject_cast< SARibbonPannelLayout* >(layout());

    if (lay) {
        int index = lay->indexOf(action);
        if (index == -1) {
            return (nullptr);
        }
        QLayoutItem* item       = lay->takeAt(index);
        SARibbonToolButton* btn = qobject_cast< SARibbonToolButton* >(item ? item->widget() : nullptr);
        return (btn);
    }
    return (nullptr);
}

/**
 * @brief ��ȡpannel���������toolbutton
 * @return
 */
QList< SARibbonToolButton* > SARibbonPannel::ribbonToolButtons() const
{
    const QObjectList& objs = children();
    QList< SARibbonToolButton* > res;

    for (QObject* o : objs) {
        SARibbonToolButton* b = qobject_cast< SARibbonToolButton* >(o);
        if (b) {
            res.append(b);
        }
    }
    return (res);
}

/**
 * @brief ����PannelLayoutMode
 * @param mode
 */
void SARibbonPannel::setPannelLayoutMode(SARibbonPannel::PannelLayoutMode mode)
{
    //������ͬ�жϣ��������Խ���ǿ�Ʋ���
    //    if (d_ptr->m_pannelLayoutMode == mode) {
    //        return;
    //    }
    d_ptr->m_pannelLayoutMode = mode;
    resetLayout(mode);
    resetLargeToolButtonStyle();
}

SARibbonPannel::PannelLayoutMode SARibbonPannel::pannelLayoutMode() const
{
    return (d_ptr->m_pannelLayoutMode);
}

/**
 * @brief ��Ӳ���action�����Ҫȥ��������nullptrָ�뼴�ɣ�SARibbonPannel�����QAction������Ȩ���й���
 * @param action
 * @note Ҫȥ��OptionActionֱ�Ӵ���nullptr����
 * @note SARibbonPannel����QAction��destroy���й���������ⲿ��action����delete����Ҫ�ȴ���nullptr��addOptionAction
 */
void SARibbonPannel::addOptionAction(QAction* action)
{
    if (nullptr == action) {
        if (d_ptr->m_optionActionButton) {
            delete d_ptr->m_optionActionButton;
            d_ptr->m_optionActionButton = nullptr;
        }
        return;
    }
    if (nullptr == d_ptr->m_optionActionButton) {
        d_ptr->m_optionActionButton = RibbonSubElementDelegate->createRibbonPannelOptionButton(this);
    }
    d_ptr->m_optionActionButton->setFixedSize(optionActionButtonSize());
    d_ptr->m_optionActionButton->setIconSize(optionActionButtonSize() - QSize(-2, -2));
    d_ptr->m_optionActionButton->connectAction(action);
    updateGeometry();  //֪ͨlayout�������²���
    repaint();
}

/**
 * @brief �ж��Ƿ����OptionAction
 * @return ���ڷ���true
 */
bool SARibbonPannel::isHaveOptionAction() const
{
    return (d_ptr->m_optionActionButton != nullptr);
}

QSize SARibbonPannel::maxHightIconSize(const QSize& size, int h)
{
    if (size.height() < h) {
        return (size * ((float)h / size.height()));
    }
    return (size);
}

void SARibbonPannel::paintEvent(QPaintEvent* event)
{
    QPainter p(this);

    //! 1. ���Ʊ���
#ifdef SA_RIBBON_DEBUG_HELP_DRAW
    HELP_DRAW_RECT(p, rect());
#endif
    if (ThreeRowMode == pannelLayoutMode()) {
        const int th = titleHeight();
        QFont f      = font();
        f.setPixelSize(th * 0.8);
        p.setFont(f);
        if (d_ptr->m_optionActionButton) {
            p.drawText(1, height() - th, width() - d_ptr->m_optionActionButton->width() - 4, th, Qt::AlignCenter, pannelName());
#ifdef SA_RIBBON_DEBUG_HELP_DRAW
            QRect r = QRect(1, height() - th, width() - m_d->m_optionActionButton->width() - 4, th - 2);
            HELP_DRAW_RECT(p, r);
#endif
        } else {
            p.drawText(1, height() - th, width(), th, Qt::AlignCenter, pannelName());
#ifdef SA_RIBBON_DEBUG_HELP_DRAW
            QRect r = QRect(1, height() - th, width(), th);
            HELP_DRAW_RECT(p, r);
#endif
        }
    }

    QWidget::paintEvent(event);
}

QSize SARibbonPannel::sizeHint() const
{
    QSize laySize = layout()->sizeHint();
    int maxWidth  = laySize.width() + 2;

    if (ThreeRowMode == pannelLayoutMode()) {
        //����ģʽ
        QFontMetrics fm = fontMetrics();
        QSize titleSize = fm.size(Qt::TextShowMnemonic, pannelName());
        if (d_ptr->m_optionActionButton) {
            // optionActionButton�Ŀ����ҪԤ��
            titleSize.setWidth(titleSize.width() + d_ptr->m_optionActionButton->width() + 4);
        }
        maxWidth = qMax(maxWidth, titleSize.width());
    }
    return (QSize(maxWidth, laySize.height()));
}

QSize SARibbonPannel::minimumSizeHint() const
{
    return (layout()->minimumSize());
}

/**
 * @brief ��pannel����Ϊ��չģʽ����ʱ��Ŵ�ˮƽ����
 * @param isExpanding
 */
void SARibbonPannel::setExpanding(bool isExpanding)
{
    setSizePolicy(isExpanding ? QSizePolicy::Expanding : QSizePolicy::Preferred, QSizePolicy::Fixed);
}

/**
 * @brief �жϴ�pannel�Ƿ�Ϊ��ˮƽ����չģʽ
 * @return ����չģʽ����true
 */
bool SARibbonPannel::isExpanding() const
{
    QSizePolicy sp = sizePolicy();

    return (sp.horizontalPolicy() == QSizePolicy::Expanding);
}

/**
 * @brief �������߶ȣ���������ģʽ����Ч
 * @return
 */
int SARibbonPannel::titleHeight() const
{
    return (isTwoRow() ? 0 : pannelTitleHeight());
}

/**
 * @brief ����optionActionButton�ĳߴ�
 * @return
 */
QSize SARibbonPannel::optionActionButtonSize() const
{
    return (isTwoRow() ? QSize(12, 12) : QSize(pannelTitleHeight(), pannelTitleHeight()));
}

/**
 * @brief action��Ӧ�Ĳ���index���˲���һ�������ƶ����������岻��
 * @param act
 * @return û�в鵽����-1
 */
int SARibbonPannel::actionIndex(QAction* act) const
{
    return (d_ptr->m_layout->indexOf(act));
}

/**
 * @brief �ƶ�action
 * @param from Ҫ�ƶ�action��λ�ã�ͨ��@ref actionIndex ��ȡ
 * @param to Ҫ�ƶ���λ��
 */
void SARibbonPannel::moveAction(int from, int to)
{
    d_ptr->m_layout->move(from, to);
    updateGeometry();  //֪ͨlayout�������²���
}

/**
 * @brief �ж��Ƿ�����Զ���
 * @return
 */
bool SARibbonPannel::isCanCustomize() const
{
    return (d_ptr->m_isCanCustomize);
}

/**
 * @brief �����Ƿ�����Զ���
 * @param b
 */
void SARibbonPannel::setCanCustomize(bool b)
{
    d_ptr->m_isCanCustomize = b;
}

QString SARibbonPannel::pannelName() const
{
    return (windowTitle());
}

/**
 * @brief SARibbonPannel::setPannelTitle pannel�ı���
 * @note ע��ᴥ��windowTitleChange�ź�
 * @param title ����
 */
void SARibbonPannel::setPannelName(const QString& title)
{
    setWindowTitle(title);
    update();
}

/**
 * @brief ��ȡ��ͼ��ĸ߶�
 * @return
 */
int SARibbonPannel::largeHeight() const
{
    return SARibbonPannelLayout::calcLargeHeight(rect(), this);
}

/**
 * @brief �������е�pannel�ı������߶ȣ��б���@sa titleHeight �˺����Ǿ�̬��������ȡ����ȫ�ֵĸ߶�
 * �� @sa titleHeight ��������ݵ�ǰ����������ر������߶ȣ���2������·���0
 *
 * @return
 */
int SARibbonPannel::pannelTitleHeight()
{
    return SARibbonPannel::PrivateData::s_pannelTitleHeight;
}

/**
 * @brief ����pannel��ȫ�ָ߶ȣ��˺����Ǹ�ȫ�ֵ�Ӱ��
 * @note SARibbonStyleOption���õ��˺������������ú�������Ҫ�ֶ����¼���SARibbonStyleOption������,@sa SARibbonStyleOption::recalc
 * @sa SARibbonStyleOption
 * @param h
 */
void SARibbonPannel::setPannelTitleHeight(int h)
{
    SARibbonPannel::PrivateData::s_pannelTitleHeight = h;
}

void SARibbonPannel::resetLayout(PannelLayoutMode newmode)
{
    Q_UNUSED(newmode);
    layout()->setSpacing(TwoRowMode == newmode ? 4 : 2);
    updateGeometry();  //֪ͨlayout�������²���
}

/**
 * @brief ���ô�ť������
 */
void SARibbonPannel::resetLargeToolButtonStyle()
{
    QList< SARibbonToolButton* > btns = ribbonToolButtons();

    for (SARibbonToolButton* b : qAsConst(btns)) {
        if ((nullptr == b) || (SARibbonToolButton::LargeButton != b->buttonType())) {
            continue;
        }
        b->updateRect();
        b->repaint();
    }
}

void SARibbonPannel::resizeEvent(QResizeEvent* event)
{
    //! 1.�ƶ�������ť������
    if (d_ptr->m_optionActionButton) {
        if (ThreeRowMode == pannelLayoutMode()) {
            d_ptr->m_optionActionButton->move(width() - d_ptr->m_optionActionButton->width() - 2,
                                              height() - titleHeight()
                                                      + (titleHeight() - d_ptr->m_optionActionButton->height()) / 2);
        } else {
            d_ptr->m_optionActionButton->move(width() - d_ptr->m_optionActionButton->width(),
                                              height() - d_ptr->m_optionActionButton->height());
        }
    }
    //! 2.resize���������÷ָ��ߵĸ߶�
    //! ���ڷָ����ڲ����У�ֻҪ�ָ����㹻�߾Ϳ��ԣ�����Ҫ��������
    return (QWidget::resizeEvent(event));
}

/**
 * @brief ����action���¼�
 *
 * ���ﴦ����ActionAdded��ActionChanged��ActionRemoved�����¼�
 *
 * ActionAddedʱ�򲼾��������action��������ͬʱ������@ref SARibbonPannelLayout::createItem ����
 * �˺����������ɴ��ڣ�����QRibbonToolButton
 *
 * ActionChangedʱ���ò������¼���ߴ磬����category�������²��֣��п���category������Ҫ���µ����ߴ�
 *
 * ActionRemoved���Ƴ����ֹ����QLayoutItem���������ڴ�������ʱ����Ҳ�����أ�ͬʱ����
 *
 * @param e
 * @note ����action�¼�������category�������²���
 *
 */
void SARibbonPannel::actionEvent(QActionEvent* e)
{
    QAction* action             = e->action();
    QWidgetAction* widgetAction = qobject_cast< QWidgetAction* >(action);

    switch (e->type()) {
    case QEvent::ActionAdded: {
        SARibbonPannelLayout* lay = d_ptr->m_layout;
        if (nullptr != widgetAction) {
            if (widgetAction->parent() != this) {
                widgetAction->setParent(this);
            }
        }
        int index = layout()->count();
        if (e->before()) {
            //˵���ǲ���
            index = lay->indexOf(action);
            if (-1 == index) {
                index = layout()->count();  //�Ҳ�����ʱ��Ͳ��뵽���
            }
        }
        lay->insertAction(index, action, getActionRowProportionProperty(action));
        //����pannel�ĳߴ緢���仯����Ҫ��categoryҲ����
        if (parentWidget()) {
            QApplication::postEvent(parentWidget(), new QEvent(QEvent::LayoutRequest));
        }
    } break;

    case QEvent::ActionChanged: {
        //�ò������»���
        layout()->invalidate();
        //����pannel�ĳߴ緢���仯����Ҫ��categoryҲ����
        if (parentWidget()) {
            QApplication::postEvent(parentWidget(), new QEvent(QEvent::LayoutRequest));
        }
    } break;

    case QEvent::ActionRemoved: {
        SARibbonPannelLayout* lay = d_ptr->m_layout;
        action->disconnect(this);
        int index = lay->indexOf(action);
        if (index != -1) {
            QLayoutItem* item = lay->takeAt(index);
            delete item;
        }
        //����pannel�ĳߴ緢���仯����Ҫ��categoryҲ����
        if (parentWidget()) {
            QApplication::postEvent(parentWidget(), new QEvent(QEvent::LayoutRequest));
        }
    } break;

    default:
        break;
    }
}

/**
 * @brief ��ȡ����item
 * @return
 */
const QList< SARibbonPannelItem* >& SARibbonPannel::ribbonPannelItem() const
{
    return (d_ptr->m_layout->m_items);
}

/*** End of inlined file: SARibbonPannel.cpp ***/

/*** Start of inlined file: SARibbonCategory.cpp ***/
#include <QList>
#include <QResizeEvent>
#include <QPainter>
#include <QLinearGradient>
#include <QDebug>
#include <QApplication>

#include <QHBoxLayout>

#include <QList>
#include <QMap>

/**
 * @brief The SARibbonCategoryItem class
 */
class SAPrivateRibbonCategoryItem
{
public:
    SAPrivateRibbonCategoryItem()
    {
    }

    bool isEmpty() const
    {
        if (pannelWidget) {
            return (pannelWidget->isHidden());
        }
        return (true);
    }

    bool isNull() const
    {
        return (pannelWidget == nullptr);
    }

public:
    SARibbonPannel* pannelWidget { nullptr };
    SARibbonSeparatorWidget* separatorWidget { nullptr };
    QRect mWillSetGeometry;           ///< pannel��Ҫ���õ�Geometry
    QRect mWillSetSeparatorGeometry;  ///< pannel��Ҫ���õ�Separator��Geometry
};

///
/// \brief ribbonҳ�Ĵ�����
/// �����Ҫ�޸��ػ�SARibbonCategory������ͨ������SARibbonCategory::setProxy
///
class SARibbonCategory::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonCategory)
public:
    PrivateData(SARibbonCategory* p);

    SARibbonPannel* addPannel(const QString& title);
    SARibbonPannel* insertPannel(const QString& title, int index);
    void addPannel(SARibbonPannel* pannel);
    void insertPannel(int index, SARibbonPannel* pannel);

    //��pannel��Category���Ƴ����������٣���ʱpannel������Ȩ�黹������
    bool takePannel(SARibbonPannel* pannel);

    //�Ƴ�Pannel��Category��ֱ�ӻ���SARibbonPannel�ڴ�
    bool removePannel(SARibbonPannel* pannel);
    void setBackgroundBrush(const QBrush& brush);
    SARibbonCategory* ribbonCategory();
    const SARibbonCategory* ribbonCategory() const;
    void setRibbonPannelLayoutMode(SARibbonPannel::PannelLayoutMode m);
    SARibbonPannel::PannelLayoutMode ribbonPannelLayoutMode() const;

    //�������е�Pannel
    QList< SARibbonPannel* > pannelList();

    //��������Ԫ�ص�SizeHint����ܺ�
    int totalSizeHintWidth() const;

    //����category�������Ŀ�ȣ�ȥ���߽�
    QSize categoryContentSize() const;

    //����item�Ĳ���,�˺��������doItemLayout
    void updateItemGeometry();

    //ʵ�ʲ���
    void doItemLayout();

    //
    void onLeftScrollButtonClicked();
    void onRightScrollButtonClicked();
    void doWheelEvent(QWheelEvent* event);

public:
    bool mIsRightScrollBtnShow { false };  ///< ����ҹ�����ť�Ƿ���Ҫ��ʾ
    bool mIsLeftScrollBtnShow { false };   ///< ����������ť�Ƿ���Ҫ��ʾ
    bool mIsContextCategory { false };     ///< ����Ƿ��������ı�ǩ
    bool mIsCanCustomize { true };         ///< ����Ƿ�����Զ���
    int mTotalWidth { 0 };                 ///< category���ܳ�
    int mXBase { 0 };
    SARibbonPannel::PannelLayoutMode mDefaultPannelLayoutMode { SARibbonPannel::ThreeRowMode };
    SARibbonBar* mBar { nullptr };
    SARibbonCategoryScrollButton* mLeftScrollBtn { nullptr };
    SARibbonCategoryScrollButton* mRightScrollBtn { nullptr };
    QSize mSizeHint { 50, 50 };
    QMargins mContentsMargins { 1, 1, 1, 1 };
    QList< SAPrivateRibbonCategoryItem > mItemList;
};
SARibbonCategory::PrivateData::PrivateData(SARibbonCategory* p) : q_ptr(p)
{
}

/**
 * @brief ��������Ԫ�ص�SizeHint����ܺ�
 * @return
 */
int SARibbonCategory::PrivateData::totalSizeHintWidth() const
{
    int total    = 0;
    QMargins mag = mContentsMargins;

    if (!mag.isNull()) {
        total += (mag.left() + mag.right());
    }
    //�ȼ����ܳ�
    for (const SAPrivateRibbonCategoryItem& item : qAsConst(mItemList)) {
        if (item.isEmpty()) {
            //�����hide��ֱ������
            continue;
        }
        QSize pannelSize = item.pannelWidget->sizeHint();
        QSize SeparatorSize(0, 0);
        if (item.separatorWidget) {
            SeparatorSize = item.separatorWidget->sizeHint();
        }
        total += pannelSize.width();
        total += SeparatorSize.width();
    }
    return (total);
}

QSize SARibbonCategory::PrivateData::categoryContentSize() const
{
    const SARibbonCategory* category = ribbonCategory();
    QSize s                          = category->size();
    QMargins mag                     = mContentsMargins;

    if (!mag.isNull()) {
        s.rheight() -= (mag.top() + mag.bottom());
        s.rwidth() -= (mag.right() + mag.left());
    }
    return (s);
}

SARibbonPannel* SARibbonCategory::PrivateData::addPannel(const QString& title)
{
    return (insertPannel(title, mItemList.size()));
}

SARibbonPannel* SARibbonCategory::PrivateData::insertPannel(const QString& title, int index)
{
    SARibbonPannel* pannel = RibbonSubElementDelegate->createRibbonPannel(ribbonCategory());

    pannel->setPannelName(title);
    pannel->setObjectName(title);
    insertPannel(index, pannel);
    return (pannel);
}

void SARibbonCategory::PrivateData::addPannel(SARibbonPannel* pannel)
{
    insertPannel(mItemList.size(), pannel);
}

void SARibbonCategory::PrivateData::insertPannel(int index, SARibbonPannel* pannel)
{
    if (nullptr == pannel) {
        return;
    }
    if (pannel->parentWidget() != q_ptr) {
        pannel->setParent(q_ptr);
    }
    pannel->setPannelLayoutMode(ribbonPannelLayoutMode());
    pannel->installEventFilter(q_ptr);
    index = qMax(0, index);
    index = qMin(mItemList.size(), index);
    SAPrivateRibbonCategoryItem item;

    item.pannelWidget = pannel;
    //�ָ���
    item.separatorWidget = RibbonSubElementDelegate->createRibbonSeparatorWidget(q_ptr);
    //����list��
    mItemList.insert(index, item);
    //�����Ҫ���¼���ߴ�
    updateItemGeometry();
    pannel->setVisible(true);
}

bool SARibbonCategory::PrivateData::takePannel(SARibbonPannel* pannel)
{
    SAPrivateRibbonCategoryItem item;

    for (int i = 0; i < mItemList.size(); ++i) {
        if (pannel == mItemList[ i ].pannelWidget) {
            item = mItemList.takeAt(i);
        }
    }
    if (item.isNull()) {
        return (false);
    }
    if (item.separatorWidget) {
        item.separatorWidget->hide();
        //��Ӧ�ķָ���ɾ������pannel��ɾ��
        item.separatorWidget->deleteLater();
    }
    return (true);
}

bool SARibbonCategory::PrivateData::removePannel(SARibbonPannel* pannel)
{
    if (takePannel(pannel)) {
        pannel->hide();
        pannel->deleteLater();
        return (true);
    }
    return (false);
}

void SARibbonCategory::PrivateData::setBackgroundBrush(const QBrush& brush)
{
    QPalette p = ribbonCategory()->palette();

    p.setBrush(QPalette::Window, brush);
    ribbonCategory()->setPalette(p);
}

QList< SARibbonPannel* > SARibbonCategory::PrivateData::pannelList()
{
    QList< SARibbonPannel* > res;

    for (const SAPrivateRibbonCategoryItem& i : qAsConst(mItemList)) {
        if (!i.isNull()) {
            res.append(i.pannelWidget);
        }
    }
    return (res);
}

SARibbonCategory* SARibbonCategory::PrivateData::ribbonCategory()
{
    return (q_ptr);
}

const SARibbonCategory* SARibbonCategory::PrivateData::ribbonCategory() const
{
    return (q_ptr);
}

/**
 * @brief ����pannel��ģʽ
 *
 * ��@ref SARibbonBar����@ref SARibbonBar::setRibbonStyle ����ʱ��������е�SARibbonCategory���ô˺���
 * ���µ�SARibbonPannel::PannelLayoutMode���ý�ȥ
 *
 * �˺���ΪSARibbonCategory::setRibbonPannelLayoutMode�Ĵ���
 * ��SARibbonCategory���У��˺���Ϊprotected����Ҫ��SARibbonBar::setRibbonStyleʱ�Żᴥ��
 * @param m
 */
void SARibbonCategory::PrivateData::setRibbonPannelLayoutMode(SARibbonPannel::PannelLayoutMode m)
{
    // ������ͬ�жϣ���������ͨ���˺���ǿ�����²���
    //    if (mDefaultPannelLayoutMode == m) {
    //        return;
    //    }
    mDefaultPannelLayoutMode    = m;
    QList< SARibbonPannel* > ps = pannelList();

    for (SARibbonPannel* p : qAsConst(ps)) {
        p->setPannelLayoutMode(m);
    }
    updateItemGeometry();
}

SARibbonPannel::PannelLayoutMode SARibbonCategory::PrivateData::ribbonPannelLayoutMode() const
{
    return (mDefaultPannelLayoutMode);
}

void SARibbonCategory::PrivateData::updateItemGeometry()
{
    SARibbonCategory* category = ribbonCategory();
    QSize contentSize          = categoryContentSize();
    int y                      = 0;
    int x                      = 0;

    if (!mContentsMargins.isNull()) {
        y = mContentsMargins.top();
        x = mContentsMargins.left();
    }
    // total ���ܿ�����x����ϵ��x��������ϵ
    int total = totalSizeHintWidth();
    //��¼������չ������
    int canExpandingCount = 0;
    //��չ�Ŀ��
    int expandWidth = 0;

    //���total < categoryWidth,m_d->mXBase��������Ϊ0
    //�ж��Ƿ񳬹��ܳ���
#ifdef SA_RIBBON_DEBUG_HELP_DRAW
    qDebug() << "\r\n\r\n============================================="
             << "\r\nSARibbonCategoryPrivate::updateItemGeometry"
             << "\r\npannel name:" << category->windowTitle() << "\r\n height:" << height
             << "\r\n first total:" << total << "\r\n y:" << y << "\r\n expandWidth:" << expandWidth;
#endif
    if (total <= contentSize.width()) {
        //����Ǳ���һ��ʼtotalWidth > categorySize.width()��ͨ��������ť������m_d->mBaseX
        //��֮�����˴���ߴ磬������totalWidth < categorySize.width()����category��ԭ��λ��
        //�޷���ʾ�����������mBaseX����Ϊ0
        mXBase = 0;
        //
        for (const SAPrivateRibbonCategoryItem& item : qAsConst(mItemList)) {
            if (!item.isEmpty()) {
                if (item.pannelWidget->isExpanding()) {
                    // pannel����չ
                    ++canExpandingCount;
                }
            }
        }
        //�������չ�Ŀ��
        if (canExpandingCount > 0) {
            expandWidth = (contentSize.width() - total) / canExpandingCount;
        } else {
            expandWidth = 0;
        }
    }
    total = 0;  // total���¼���
    x += mXBase;

    //�Ȱ���sizeHint�������еĳߴ�
    for (SAPrivateRibbonCategoryItem& item : mItemList) {
        if (item.isEmpty()) {
            //�����hide��ֱ������
            if (item.separatorWidget) {
                // pannel hide�ָ���ҲҪhide
                item.separatorWidget->hide();
            }
            item.mWillSetGeometry          = QRect(0, 0, 0, 0);
            item.mWillSetSeparatorGeometry = QRect(0, 0, 0, 0);
            continue;
        }
        SARibbonPannel* p = item.pannelWidget;
        if (nullptr == p) {
            qDebug() << "unknow widget in SARibbonCategoryLayout";
            continue;
        }
        QSize pannelSize = p->sizeHint();
        QSize SeparatorSize(0, 0);
        if (item.separatorWidget) {
            SeparatorSize = item.separatorWidget->sizeHint();
        }
        if (p->isExpanding()) {
            //����չ���Ͱ�pannel��չ�����
            pannelSize.setWidth(pannelSize.width() + expandWidth);
        }
        int w                 = pannelSize.width();
        item.mWillSetGeometry = QRect(x, y, w, contentSize.height());
        x += w;
        total += w;
        w                              = SeparatorSize.width();
        item.mWillSetSeparatorGeometry = QRect(x, y, w, contentSize.height());
        x += w;
        total += w;
    }
    mTotalWidth = total;
    //�жϹ�����ť�Ƿ���ʾ
    if (total > contentSize.width()) {
        //�����ܳ��ȣ���Ҫ��ʾ������ť
        if (0 == mXBase) {
            //�Ѿ��ƶ���������Ҫ���������ƶ�
            mIsRightScrollBtnShow = true;
            mIsLeftScrollBtnShow  = false;
        } else if (mXBase <= (contentSize.width() - total)) {
            //�Ѿ��ƶ������ң���Ҫ���������ƶ�
            mIsRightScrollBtnShow = false;
            mIsLeftScrollBtnShow  = true;
        } else {
            //�ƶ����м����߶����Զ�
            mIsRightScrollBtnShow = true;
            mIsLeftScrollBtnShow  = true;
        }
    } else {
        //˵��total С�� categoryWidth
        mIsRightScrollBtnShow = false;
        mIsLeftScrollBtnShow  = false;
    }
    QWidget* cp      = category->parentWidget();
    int parentHeight = (nullptr == cp) ? contentSize.height() : cp->height();
    int parentWidth  = (nullptr == cp) ? total : cp->width();
    mSizeHint        = QSize(parentWidth, parentHeight);
    doItemLayout();
}

void SARibbonCategory::PrivateData::doItemLayout()
{
    SARibbonCategory* category = ribbonCategory();

    //����������ť��λ����Զ����
    mLeftScrollBtn->setGeometry(0, 0, 12, category->height());
    mRightScrollBtn->setGeometry(category->width() - 12, 0, 12, category->height());
    QList< QWidget* > showWidgets, hideWidgets;

    for (const SAPrivateRibbonCategoryItem& item : qAsConst(mItemList)) {
        if (item.isNull()) {
            continue;
        }
        if (item.isEmpty()) {
            hideWidgets << item.pannelWidget;
            if (item.separatorWidget) {
                hideWidgets << item.separatorWidget;
            }
        } else {
            //            item.pannelWidget->setFixedSize(item.mWillSetGeometry.size());
            //            item.pannelWidget->move(item.mWillSetGeometry.topLeft());
            item.pannelWidget->setGeometry(item.mWillSetGeometry);
            showWidgets << item.pannelWidget;
            if (item.separatorWidget) {
                item.separatorWidget->setGeometry(item.mWillSetSeparatorGeometry);
                showWidgets << item.separatorWidget;
            }
#ifdef SA_RIBBON_DEBUG_HELP_DRAW
            qDebug() << "SARibbonCategoryLayout::doLayout() =";
            qDebug() << "\r\n     pannel:" << item.pannelWidget->windowTitle() << "\r\n     pannel geo:" << item.mWillSetGeometry
                     << "\r\n     sep geo:" << item.mWillSetSeparatorGeometry;
#endif
        }
    }

    mRightScrollBtn->setVisible(mIsRightScrollBtnShow);
    mLeftScrollBtn->setVisible(mIsLeftScrollBtnShow);
    if (mIsRightScrollBtnShow) {
        mRightScrollBtn->raise();
    }
    if (mIsLeftScrollBtnShow) {
        mLeftScrollBtn->raise();
    }
    // ���������������show��hide��Ϊ��ᴥ��SARibbonPannelLayout���ػ棬����ѭ�����ƣ��ǳ�Ӱ��Ч��
    for (QWidget* w : qAsConst(showWidgets)) {
        w->show();
    }
    for (QWidget* w : qAsConst(hideWidgets)) {
        w->hide();
    }
}

void SARibbonCategory::PrivateData::onLeftScrollButtonClicked()
{
    int width = categoryContentSize().width();
    //���ܿ�
    int totalWidth = mTotalWidth;

    if (totalWidth > width) {
        int tmp = mXBase + width;
        if (tmp > 0) {
            tmp = 0;
        }
        mXBase = tmp;
    } else {
        mXBase = 0;
    }
    updateItemGeometry();
}

void SARibbonCategory::PrivateData::onRightScrollButtonClicked()
{
    int width = categoryContentSize().width();
    //���ܿ�
    int totalWidth = mTotalWidth;

    if (totalWidth > width) {
        int tmp = mXBase - width;
        if (tmp < (width - totalWidth)) {
            tmp = width - totalWidth;
        }
        mXBase = tmp;
    } else {
        mXBase = 0;
    }
    updateItemGeometry();
}

void SARibbonCategory::PrivateData::doWheelEvent(QWheelEvent* event)
{
    QSize contentSize = categoryContentSize();
    //���ܿ�
    int totalWidth = mTotalWidth;

    if (totalWidth > contentSize.width()) {
        //���ʱ�������Ч
        int scrollpix = 40;
        // Qt6 ȡ����QWheelEvent::delta����
        //��Ҫ���淽���ɼ���qt5/6
        QPoint numPixels  = event->pixelDelta();
        QPoint numDegrees = event->angleDelta() / 8;
        if (!numPixels.isNull()) {
            if (numDegrees.y() < 0) {
                scrollpix = -scrollpix;
            }
        } else if (!numDegrees.isNull()) {
            if (numDegrees.y() < 0) {
                scrollpix = -scrollpix;
            }
        }
        mXBase += scrollpix;
        if (mXBase > 0) {
            mXBase = 0;
        } else if ((mXBase + totalWidth) < contentSize.width()) {
            mXBase = contentSize.width() - totalWidth;
        }
        updateItemGeometry();
    } else {
        //��ʱ�����账���¼����ѹ����¼��Ϸ��ø���Ҳ�ܽ���
        event->ignore();
        mXBase = 0;
    }
}

SARibbonCategory::SARibbonCategory(QWidget* p) : QWidget(p), d_ptr(new SARibbonCategory::PrivateData(this))
{
    setAutoFillBackground(true);
    setBackgroundBrush(Qt::white);
    d_ptr->mLeftScrollBtn  = new SARibbonCategoryScrollButton(Qt::LeftArrow, this);
    d_ptr->mRightScrollBtn = new SARibbonCategoryScrollButton(Qt::RightArrow, this);
    d_ptr->mLeftScrollBtn->setVisible(false);
    d_ptr->mRightScrollBtn->setVisible(false);
    connect(d_ptr->mLeftScrollBtn, &QToolButton::clicked, this, &SARibbonCategory::onLeftScrollButtonClicked);
    connect(d_ptr->mRightScrollBtn, &QToolButton::clicked, this, &SARibbonCategory::onRightScrollButtonClicked);
}

SARibbonCategory::~SARibbonCategory()
{
}

/**
 * @brief category������,��ͬwindowTitle����
 * @return
 */
QString SARibbonCategory::categoryName() const
{
    return (windowTitle());
}

/**
 * @brief ����category���֣���ͬsetWindowTitle
 * @param title
 */
void SARibbonCategory::setCategoryName(const QString& title)
{
    setWindowTitle(title);
}

/**
 * @brief ����pannel��ģʽ
 *
 * ��@ref SARibbonBar ����@ref SARibbonBar::setRibbonStyle ����ʱ��������е�SARibbonCategory���ô˺���
 * ���µ�SARibbonPannel::PannelLayoutMode���ý�ȥ
 * @param m
 */
void SARibbonCategory::setRibbonPannelLayoutMode(SARibbonPannel::PannelLayoutMode m)
{
    d_ptr->setRibbonPannelLayoutMode(m);
}

SARibbonPannel::PannelLayoutMode SARibbonCategory::ribbonPannelLayoutMode() const
{
    return (d_ptr->ribbonPannelLayoutMode());
}

/**
 * @brief ���pannel
 *
 * @note pannel������Ȩ��SARibbonCategory�������벻Ҫ���ⲿ�����������
 * @param title pannel�ı��⣬��office/wps������ģʽ�»���ʾ��pannel���·�
 * @return �������ɵ�@ref SARibbonPannel ָ��
 * @see ��SARibbonPannel�������������ο� @ref SARibbonCategory::takePannel
 */
SARibbonPannel* SARibbonCategory::addPannel(const QString& title)
{
    return (d_ptr->addPannel(title));
}

/**
 * @brief �½�һ��pannel�������뵽indexλ��
 * @param title pannel��title
 * @param index �����λ�ã����index����category��pannel�ĸ����������뵽���
 * @return �������ɵ�@ref SARibbonPannel ָ��
 * @note ���
 */
SARibbonPannel* SARibbonCategory::insertPannel(const QString& title, int index)
{
    return (d_ptr->insertPannel(title, index));
}

/**
 * @brief ͨ�����ֲ���pannel
 * @param title
 * @return �����������ֻ�᷵�ص�һ������������
 */
SARibbonPannel* SARibbonCategory::pannelByName(const QString& title) const
{
    for (const SAPrivateRibbonCategoryItem& i : qAsConst(d_ptr->mItemList)) {
        if (i.pannelWidget) {
            if (i.pannelWidget->pannelName() == title) {
                return (i.pannelWidget);
            }
        }
    }
    return (nullptr);
}

/**
 * @brief ͨ��ObjectName����pannel
 * @param objname
 * @return
 */
SARibbonPannel* SARibbonCategory::pannelByObjectName(const QString& objname) const
{
    for (const SAPrivateRibbonCategoryItem& i : qAsConst(d_ptr->mItemList)) {
        if (i.pannelWidget) {
            if (i.pannelWidget->objectName() == objname) {
                return (i.pannelWidget);
            }
        }
    }
    return (nullptr);
}

/**
 * @brief ͨ�������ҵ�pannel���������������Χ���᷵��nullptr
 * @param index
 * @return �������������Χ���᷵��nullptr
 */
SARibbonPannel* SARibbonCategory::pannelByIndex(int index) const
{
    return (d_ptr->mItemList.value(index).pannelWidget);
}

/**
 * @brief ����pannel��Ӧ������
 * @param p
 * @return ����Ҳ���������-1
 */
int SARibbonCategory::pannelIndex(SARibbonPannel* p) const
{
    int c = pannelCount();

    for (int i = 0; i < c; ++i) {
        if (d_ptr->mItemList[ i ].pannelWidget == p) {
            return (i);
        }
    }
    return (-1);
}

/**
 * @brief �ƶ�һ��Pannel��from index��to index
 * @param from Ҫ�ƶ�pannel��index
 * @param to Ҫ�ƶ�����λ��
 */
void SARibbonCategory::movePannel(int from, int to)
{
    if (from == to) {
        return;
    }
    if (to < 0) {
        to = 0;
    }
    if (to >= pannelCount()) {
        to = pannelCount() - 1;
    }
    d_ptr->mItemList.move(from, to);
    d_ptr->updateItemGeometry();
}

/**
 * @brief ���pannel
 * @param pannel pannel������ȨSARibbonCategory������
 */
void SARibbonCategory::addPannel(SARibbonPannel* pannel)
{
    d_ptr->addPannel(pannel);
}

/**
 * @brief qt designerר��
 * @param pannel
 */
void SARibbonCategory::addPannel(QWidget* pannel)
{
    SARibbonPannel* p = qobject_cast< SARibbonPannel* >(pannel);

    if (p) {
        addPannel(p);
    }
}

/**
 * @brief ��pannel����SARibbonCategory�Ĺ���
 * @param pannel ��Ҫ��ȡ��pannel
 * @return �ɹ�����true�����򷵻�false
 */
bool SARibbonCategory::takePannel(SARibbonPannel* pannel)
{
    return (d_ptr->takePannel(pannel));
}

/**
 * @brief �Ƴ�Pannel��Category��ֱ�ӻ���SARibbonPannel�ڴ�
 * @param pannel ��Ҫ�Ƴ���pannel
 * @note �Ƴ���pannelΪҰָ�룬һ������꽨���pannelָ������Ϊnullptr
 *
 * �˲�����ͬ�ڣ�
 *
 * @code
 * SARibbonPannel* pannel;
 * ...
 * category->takePannel(pannel);
 * pannel->hide();
 * pannel->deleteLater();
 * @endcode
 */
bool SARibbonCategory::removePannel(SARibbonPannel* pannel)
{
    return (d_ptr->removePannel(pannel));
}

/**
 * @brief �Ƴ�pannel
 * @param index pannel����������������᷵��false
 * @return �ɹ�����true
 */
bool SARibbonCategory::removePannel(int index)
{
    SARibbonPannel* p = pannelByIndex(index);

    if (nullptr == p) {
        return (false);
    }
    return (removePannel(p));
}

///
/// \brief SARibbonCategory::setBackgroundBrush
/// \param brush
///
void SARibbonCategory::setBackgroundBrush(const QBrush& brush)
{
    d_ptr->setBackgroundBrush(brush);
}

/**
 * @brief ����Category�µ�����pannel
 * @return
 */
QList< SARibbonPannel* > SARibbonCategory::pannelList() const
{
    return (d_ptr->pannelList());
}

QSize SARibbonCategory::sizeHint() const
{
    return (d_ptr->mSizeHint);
}

/**
 * @brief �����ContextCategory���˺�������true
 * @return
 */
bool SARibbonCategory::isContextCategory() const
{
    return (d_ptr->mIsContextCategory);
}

/**
 * @brief ����pannel�ĸ���
 * @return
 */
int SARibbonCategory::pannelCount() const
{
    return (d_ptr->mItemList.size());
}

/**
 * @brief �ж��Ƿ�����Զ���
 * @return
 */
bool SARibbonCategory::isCanCustomize() const
{
    return (d_ptr->mIsCanCustomize);
}

/**
 * @brief �����Ƿ�����Զ���
 * @param b
 */
void SARibbonCategory::setCanCustomize(bool b)
{
    d_ptr->mIsCanCustomize = b;
}

/**
 * @brief ��ȡ��Ӧ��ribbonbar
 * @return ���û�м���ribbonbar�Ĺ�����ֵΪnull
 */
SARibbonBar* SARibbonCategory::ribbonBar() const
{
    return (d_ptr->mBar);
}

/**
 * @brief ˢ��category�Ĳ��֣������ڸı�ribbon��ģʽ֮�����
 */
void SARibbonCategory::updateItemGeometry()
{
    QList< SARibbonPannel* > ps = pannelList();
    for (SARibbonPannel* p : qAsConst(ps)) {
        p->updateGeometry();
    }
    d_ptr->updateItemGeometry();
}

void SARibbonCategory::onLeftScrollButtonClicked()
{
    d_ptr->onLeftScrollButtonClicked();
}

void SARibbonCategory::onRightScrollButtonClicked()
{
    d_ptr->onRightScrollButtonClicked();
}

/**
 * @brief SARibbonCategory::event
 * @param event
 * @return
 */
bool SARibbonCategory::event(QEvent* e)
{
    switch (e->type()) {
    case QEvent::LayoutRequest: {
        d_ptr->updateItemGeometry();
    } break;

    default:
        break;
    }
    return (QWidget::event(e));
}

void SARibbonCategory::resizeEvent(QResizeEvent* e)
{
    QWidget::resizeEvent(e);
    //    QSize delta = e->size() - e->oldSize();

    //    //�ߴ�û��Ͳ��ù�
    //    if (delta.isNull()) {
    //        return;
    //    }
    d_ptr->updateItemGeometry();
}

bool SARibbonCategory::eventFilter(QObject* watched, QEvent* event)
{
    if (nullptr == watched) {
        return (false);
    }
    SARibbonPannel* pannel = qobject_cast< SARibbonPannel* >(watched);

    if (pannel) {
        switch (event->type()) {
        case QEvent::HideToParent: {
            //���غ���ʾ��Ҫ���²���
            // layout()->invalidate();
        } break;

        case QEvent::ShowToParent: {
            //���غ���ʾ��Ҫ���²���
            // layout()->invalidate();
        } break;

        default:
            break;
        }
    }
    return (false);
}

/**
 * @brief �ڳ����߽�����£����ֿɹ���pannel
 * @param event
 */
void SARibbonCategory::wheelEvent(QWheelEvent* event)
{
    d_ptr->doWheelEvent(event);
}

/**
 * @brief �������������ı�ǩ
 * @param isContextCategory
 */
void SARibbonCategory::markIsContextCategory(bool isContextCategory)
{
    d_ptr->mIsContextCategory = isContextCategory;
}

/**
 * @brief ����ribbonbar���˺������ṩ��ribbonbar����
 * @param bar ribbonbarָ��
 */
void SARibbonCategory::setRibbonBar(SARibbonBar* bar)
{
    d_ptr->mBar = bar;
}

//===================================================
// SARibbonCategoryScrollButton
//===================================================
SARibbonCategoryScrollButton::SARibbonCategoryScrollButton(Qt::ArrowType arr, QWidget* p) : QToolButton(p)
{
    setArrowType(arr);
}

/*** End of inlined file: SARibbonCategory.cpp ***/

/*** Start of inlined file: SARibbonCategoryLayout.cpp ***/
#include <QLayoutItem>

#include <QApplication>
#include <QDebug>

/**
 * @brief The SARibbonCategoryLayoutPrivate class
 */
class SARibbonCategoryLayout::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonCategoryLayout)
public:
    PrivateData(SARibbonCategoryLayout* p);
    //��������Ԫ�ص�sizehint�ܿ��
    int totalSizeHintWidth() const;

public:
    bool mDirty { true };
    bool mIsRightScrollBtnShow { false };                       ///< ����ҹ�����ť�Ƿ���Ҫ��ʾ
    bool mIsLeftScrollBtnShow { false };                        ///< ����������ť�Ƿ���Ҫ��ʾ
    SARibbonCategoryScrollButton* mLeftScrollBtn { nullptr };   ///< �������޷���ʾʱ��ʾ�İ�ť
    SARibbonCategoryScrollButton* mRightScrollBtn { nullptr };  ///< �������޷���ʾʱ��ʾ�İ�ť
    int mTotalWidth { 0 };
    int mXBase { 0 };
    QSize mSizeHint { 50, 50 };
    QList< SARibbonCategoryLayoutItem* > mItemList;
};

//=============================================================
// SARibbonCategoryLayoutPrivate
//=============================================================

SARibbonCategoryLayout::PrivateData::PrivateData(SARibbonCategoryLayout* p) : q_ptr(p)
{
}

/**
 * @brief ��������Ԫ�ص�SizeHint����ܺ�
 * @return
 */
int SARibbonCategoryLayout::PrivateData::totalSizeHintWidth() const
{
    int total    = 0;
    QMargins mag = q_ptr->contentsMargins();

    if (!mag.isNull()) {
        total += (mag.left() + mag.right());
    }
    //�ȼ����ܳ�
    for (SARibbonCategoryLayoutItem* item : qAsConst(mItemList)) {
        if (item->isEmpty()) {
            //�����hide��ֱ������
            continue;
        }
        QSize pannelSize = item->widget()->sizeHint();
        QSize SeparatorSize(0, 0);
        if (item->separatorWidget) {
            SeparatorSize = item->separatorWidget->sizeHint();
        }
        total += pannelSize.width();
        total += SeparatorSize.width();
    }
    return (total);
}

//=============================================================
// SARibbonCategoryLayout
//=============================================================

SARibbonCategoryLayout::SARibbonCategoryLayout(SARibbonCategory* parent)
    : QLayout(parent), d_ptr(new SARibbonCategoryLayout::PrivateData(this))
{
    setContentsMargins(1, 1, 1, 1);
    d_ptr->mLeftScrollBtn  = new SARibbonCategoryScrollButton(Qt::LeftArrow, parent);
    d_ptr->mRightScrollBtn = new SARibbonCategoryScrollButton(Qt::RightArrow, parent);
    d_ptr->mLeftScrollBtn->setVisible(false);
    d_ptr->mRightScrollBtn->setVisible(false);
    connect(d_ptr->mLeftScrollBtn, &QToolButton::clicked, this, &SARibbonCategoryLayout::onLeftScrollButtonClicked);
    connect(d_ptr->mRightScrollBtn, &QToolButton::clicked, this, &SARibbonCategoryLayout::onRightScrollButtonClicked);
}

SARibbonCategoryLayout::~SARibbonCategoryLayout()
{
    QLayoutItem* item = Q_NULLPTR;

    while ((item = takeAt(0))) {
        delete item;
    }
}

SARibbonCategory* SARibbonCategoryLayout::ribbonCategory()
{
    return (qobject_cast< SARibbonCategory* >(parentWidget()));
}

void SARibbonCategoryLayout::addItem(QLayoutItem* item)
{
    Q_UNUSED(item);
    qWarning() << tr("in SARibbonCategoryLayout cannot addItem,use addPannel instead");
    invalidate();
}

/**
 * @brief ����pannel��layout
 * @param index ����
 * @return
 * @note ע�⣬pannel�Ǻͷָ���һ��ģ������ֻ����һ��pannel��Ӧ��layout
 */
QLayoutItem* SARibbonCategoryLayout::itemAt(int index) const
{
    SARibbonCategoryLayoutItem* item = d_ptr->mItemList.value(index, nullptr);

    return (item);
}

/**
 * @brief ��ȡlayout
 * @param index
 * @return
 */
QLayoutItem* SARibbonCategoryLayout::takeAt(int index)
{
    return (takePannelItem(index));
}

SARibbonCategoryLayoutItem* SARibbonCategoryLayout::takePannelItem(int index)
{
    if ((index >= 0) && (index < d_ptr->mItemList.size())) {
        invalidate();
        SARibbonCategoryLayoutItem* item = d_ptr->mItemList.takeAt(index);
        if (item->widget()) {
            item->widget()->hide();
        }
        if (item->separatorWidget) {
            item->separatorWidget->hide();
        }
        return (item);
    }
    return (nullptr);
}

SARibbonCategoryLayoutItem* SARibbonCategoryLayout::takePannel(SARibbonPannel* pannel)
{
    for (int i = 0; i < d_ptr->mItemList.size(); ++i) {
        SARibbonCategoryLayoutItem* item = d_ptr->mItemList[ i ];
        if (item->widget() == pannel) {
            return (takePannelItem(i));
        }
    }
    return (nullptr);
}

int SARibbonCategoryLayout::count() const
{
    return (d_ptr->mItemList.size());
}

void SARibbonCategoryLayout::addPannel(SARibbonPannel* pannel)
{
    insertPannel(d_ptr->mItemList.count(), pannel);
}

/**
 * @brief ����һ��pannel
 * @param index ����
 * @param pannel
 * @return ���ض�Ӧ�ķָ���SARibbonSeparatorWidget
 * @note ��SARibbonCategoryLayout�Ĳ����У�һ��pannel��Я��һ���ָ���
 */
void SARibbonCategoryLayout::insertPannel(int index, SARibbonPannel* pannel)
{
    index                            = qMax(0, index);
    index                            = qMin(d_ptr->mItemList.count(), index);
    SARibbonCategoryLayoutItem* item = new SARibbonCategoryLayoutItem(pannel);

    //�ָ���
    item->separatorWidget = RibbonSubElementDelegate->createRibbonSeparatorWidget(parentWidget());
    //����list��
    d_ptr->mItemList.insert(index, item);
    //�����Ҫ���¼���ߴ�
    invalidate();
}

QSize SARibbonCategoryLayout::sizeHint() const
{
    return (d_ptr->mSizeHint);
}

QSize SARibbonCategoryLayout::minimumSize() const
{
    return (d_ptr->mSizeHint);
}

/**
 * @brief SARibbonCategory��������stacked widget
 * @return
 */
Qt::Orientations SARibbonCategoryLayout::expandingDirections() const
{
    return (Qt::Horizontal | Qt::Vertical);
}

void SARibbonCategoryLayout::invalidate()
{
    d_ptr->mDirty = true;
    QLayout::invalidate();
}

/**
 * @brief ���³ߴ�
 */
void SARibbonCategoryLayout::updateGeometryArr()
{
    SARibbonCategory* category = qobject_cast< SARibbonCategory* >(parentWidget());

    int categoryWidth = category->width();
    QMargins mag      = contentsMargins();
    int height        = category->height();
    int y             = 0;

    if (!mag.isNull()) {
        y = mag.top();
        height -= (mag.top() + mag.bottom());
        categoryWidth -= (mag.right() + mag.left());
    }
    // total ���ܿ�����x����ϵ��x��������ϵ
    int total = d_ptr->totalSizeHintWidth();

    //��չ�Ŀ��
    int expandWidth = 0;

    //���total < categoryWidth,m_d->mXBase��������Ϊ0
    //�ж��Ƿ񳬹��ܳ���
#ifdef SA_RIBBON_DEBUG_HELP_DRAW
    qDebug() << "\r\n\r\n============================================="
             << "\r\nSARibbonCategoryLayout::updateGeometryArr"
             << "\r\npannel name:" << category->windowTitle() << "\r\n height:" << height
             << "\r\n first total:" << total << "\r\n y:" << y << "\r\n expandWidth:" << expandWidth;
#endif
    if (total > categoryWidth) {
        //�����ܳ��ȣ���Ҫ��ʾ������ť
        if (0 == d_ptr->mXBase) {
            //�Ѿ��ƶ���������Ҫ���������ƶ�
            d_ptr->mIsRightScrollBtnShow = true;
            d_ptr->mIsLeftScrollBtnShow  = false;
        } else if (d_ptr->mXBase <= (categoryWidth - total)) {
            //�Ѿ��ƶ������ң���Ҫ���������ƶ�
            d_ptr->mIsRightScrollBtnShow = false;
            d_ptr->mIsLeftScrollBtnShow  = true;
        } else {
            //�ƶ����м����߶����Զ�
            d_ptr->mIsRightScrollBtnShow = true;
            d_ptr->mIsLeftScrollBtnShow  = true;
        }
    } else {
        //��¼������չ������
        int canExpandingCount = 0;
        //˵��total С�� categoryWidth
        d_ptr->mIsRightScrollBtnShow = false;
        d_ptr->mIsLeftScrollBtnShow  = false;
        //����Ǳ���һ��ʼtotalWidth > categorySize.width()��ͨ��������ť������m_d->mBaseX
        //��֮�����˴���ߴ磬������totalWidth < categorySize.width()����category��ԭ��λ��
        //�޷���ʾ�����������mBaseX����Ϊ0
        d_ptr->mXBase = 0;
        //

        for (SARibbonCategoryLayoutItem* item : qAsConst(d_ptr->mItemList)) {
            if (SARibbonPannel* p = qobject_cast< SARibbonPannel* >(item->widget())) {
                if (p->isExpanding()) {
                    // pannel����չ
                    ++canExpandingCount;
                }
            }
        }
        //�������չ�Ŀ��
        if (canExpandingCount > 0) {
            expandWidth = (categoryWidth - total) / canExpandingCount;
        } else {
            expandWidth = 0;
        }
    }
    total = 0;  // total���¼���
    int x = d_ptr->mXBase;

    //�Ȱ���sizeHint�������еĳߴ�
    for (SARibbonCategoryLayoutItem* item : qAsConst(d_ptr->mItemList)) {
        if (item->isEmpty()) {
            //�����hide��ֱ������
            if (item->separatorWidget) {
                // pannel hide�ָ���ҲҪhide
                item->separatorWidget->hide();
            }
            item->mWillSetGeometry          = QRect(0, 0, 0, 0);
            item->mWillSetSeparatorGeometry = QRect(0, 0, 0, 0);
            continue;
        }
        SARibbonPannel* p = qobject_cast< SARibbonPannel* >(item->widget());
        if (nullptr == p) {
            qDebug() << "unknow widget in SARibbonCategoryLayout";
            continue;
        }
        QSize pannelSize = p->sizeHint();
        QSize SeparatorSize(0, 0);
        if (item->separatorWidget) {
            SeparatorSize = item->separatorWidget->sizeHint();
        }
        if (p->isExpanding()) {
            //����չ���Ͱ�pannel��չ�����
            pannelSize.setWidth(pannelSize.width() + expandWidth);
        }
        int w                  = pannelSize.width();
        item->mWillSetGeometry = QRect(x, y, w, height);
        x += w;
        total += w;
        w                               = SeparatorSize.width();
        item->mWillSetSeparatorGeometry = QRect(x, y, w, height);
        x += w;
        total += w;
    }
    d_ptr->mTotalWidth = total;
    QWidget* cp        = category->parentWidget();
    int parentHeight   = (nullptr == cp) ? height : cp->height();
    int parentWidth    = (nullptr == cp) ? total : cp->width();
#ifdef SA_RIBBON_DEBUG_HELP_DRAW
    qDebug() << "\r\n mSizeHint:[ " << parentHeight << "," << parentWidth;
    for (int i = 0; i < m_d->mItemList.size(); ++i) {
        qDebug() << "\r\n [ " << i << "]"
                 << " geo:" << m_d->mItemList[ i ]->mWillSetGeometry
                 << " sep geo:" << m_d->mItemList[ i ]->mWillSetSeparatorGeometry;
    }
#endif
    d_ptr->mSizeHint = QSize(parentWidth, parentHeight);
}

/**
 * @brief ִ��layout����
 */
void SARibbonCategoryLayout::doLayout()
{
    if (d_ptr->mDirty) {
        updateGeometryArr();
    }
    SARibbonCategory* category = qobject_cast< SARibbonCategory* >(parentWidget());

    //����������ť��λ����Զ����
    d_ptr->mLeftScrollBtn->setGeometry(0, 0, 12, category->height());
    d_ptr->mRightScrollBtn->setGeometry(category->width() - 12, 0, 12, category->height());
    QList< QWidget* > showWidgets, hideWidgets;

    for (SARibbonCategoryLayoutItem* item : qAsConst(d_ptr->mItemList)) {
        if (item->isEmpty()) {
            hideWidgets << item->widget();
            if (item->separatorWidget) {
                hideWidgets << item->separatorWidget;
            }
        } else {
            item->widget()->setFixedSize(item->mWillSetGeometry.size());
            item->widget()->move(item->mWillSetGeometry.topLeft());
            //            item->setGeometry(item->mWillSetGeometry);
            showWidgets << item->widget();
            if (item->separatorWidget) {
                item->separatorWidget->setGeometry(item->mWillSetSeparatorGeometry);
                showWidgets << item->separatorWidget;
            }
#ifdef SA_RIBBON_DEBUG_HELP_DRAW
            qDebug() << "SARibbonCategoryLayout::doLayout() =";
            qDebug() << "\r\n     pannel:" << item->widget()->windowTitle() << "\r\n     pannel geo:" << item->mWillSetGeometry
                     << "\r\n     sep geo:" << item->mWillSetSeparatorGeometry;
#endif
        }
    }

    d_ptr->mRightScrollBtn->setVisible(d_ptr->mIsRightScrollBtnShow);
    d_ptr->mLeftScrollBtn->setVisible(d_ptr->mIsLeftScrollBtnShow);
    if (d_ptr->mIsRightScrollBtnShow) {
        d_ptr->mRightScrollBtn->raise();
    }
    if (d_ptr->mIsLeftScrollBtnShow) {
        d_ptr->mLeftScrollBtn->raise();
    }
    // ���������������show��hide��Ϊ��ᴥ��SARibbonPannelLayout���ػ棬����ѭ�����ƣ��ǳ�Ӱ��Ч��
    for (QWidget* w : qAsConst(showWidgets)) {
        w->show();
    }
    for (QWidget* w : qAsConst(hideWidgets)) {
        w->hide();
    }
}

/**
 * @brief ��������pannels
 * @return
 */
QList< SARibbonPannel* > SARibbonCategoryLayout::pannels() const
{
    QList< SARibbonPannel* > res;

    for (SARibbonCategoryLayoutItem* item : qAsConst(d_ptr->mItemList)) {
        SARibbonPannel* p = qobject_cast< SARibbonPannel* >(item->widget());
        res.append(p);
    }
    return (res);
}

void SARibbonCategoryLayout::onLeftScrollButtonClicked()
{
    SARibbonCategory* category = qobject_cast< SARibbonCategory* >(parentWidget());
    int width                  = category->width();
    //���ܿ�
    int totalWidth = d_ptr->mTotalWidth;

    if (totalWidth > width) {
        int tmp = d_ptr->mXBase + width;
        if (tmp > 0) {
            tmp = 0;
        }
        d_ptr->mXBase = tmp;
    } else {
        d_ptr->mXBase = 0;
    }
    invalidate();
}

void SARibbonCategoryLayout::onRightScrollButtonClicked()
{
    SARibbonCategory* category = qobject_cast< SARibbonCategory* >(parentWidget());
    int width                  = category->width();
    //���ܿ�
    int totalWidth = d_ptr->mTotalWidth;

    if (totalWidth > width) {
        int tmp = d_ptr->mXBase - width;
        if (tmp < (width - totalWidth)) {
            tmp = width - totalWidth;
        }
        d_ptr->mXBase = tmp;
    } else {
        d_ptr->mXBase = 0;
    }
    invalidate();
}

void SARibbonCategoryLayout::setGeometry(const QRect& rect)
{
    d_ptr->mDirty = false;
    updateGeometryArr();
    QLayout::setGeometry(rect);
    doLayout();
}
//=============================================================
// SARibbonCategoryLayoutItem
//=============================================================

SARibbonCategoryLayoutItem::SARibbonCategoryLayoutItem(SARibbonPannel* w) : QWidgetItem(w)
{
    separatorWidget = nullptr;
}

/*** End of inlined file: SARibbonCategoryLayout.cpp ***/

/*** Start of inlined file: SARibbonContextCategory.cpp ***/
#include <QList>
#include <QVariant>

#include <QDebug>

/**
 * @brief The SARibbonCategoryData class
 */
class SAPrivateRibbonCategoryData
{
public:
    SARibbonCategory* categoryPage;
};

/**
 * @brief The SARibbonContextCategoryPrivate class
 */
class SARibbonContextCategory::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonContextCategory)
public:
    PrivateData(SARibbonContextCategory* p);

public:
    QList< SAPrivateRibbonCategoryData > categoryDataList;
    QVariant contextID;
    QColor contextColor;
    QString contextTitle;
};
SARibbonContextCategory::PrivateData::PrivateData(SARibbonContextCategory* p) : q_ptr(p)
{
}

//===================================================
// SARibbonContextCategory
//===================================================
SARibbonContextCategory::SARibbonContextCategory(QWidget* parent)
    : QObject(parent), d_ptr(new SARibbonContextCategory::PrivateData(this))
{
}

SARibbonContextCategory::~SARibbonContextCategory()
{
}

/**
 * @brief ��ӱ�ǩ
 * @param title ��ǩ����
 */
SARibbonCategory* SARibbonContextCategory::addCategoryPage(const QString& title)
{
    SARibbonCategory* category = RibbonSubElementDelegate->createRibbonCategory(parentWidget());
    category->setCategoryName(title);
    addCategoryPage(category);
    return (category);
}

/**
 * @brief ��ӱ�ǩ
 * @param page
 */
void SARibbonContextCategory::addCategoryPage(SARibbonCategory* category)
{
    if (isHaveCategory(category)) {
        // cn:SARibbonContextCategory�Ѿ����б�ǩ��%1��������
        qWarning() << tr("SARibbonContextCategory have category %1,will skip").arg(category->categoryName());
        return;
    }
    category->markIsContextCategory(true);
    connect(category, &SARibbonCategory::windowTitleChanged, this, &SARibbonContextCategory::onCategoryTitleChanged);
    SAPrivateRibbonCategoryData catData;
    catData.categoryPage = category;
    d_ptr->categoryDataList.append(catData);
    category->installEventFilter(this);
    emit categoryPageAdded(category);
}

int SARibbonContextCategory::categoryCount() const
{
    return (d_ptr->categoryDataList.count());
}

void SARibbonContextCategory::setId(const QVariant& id)
{
    d_ptr->contextID = id;
}

QVariant SARibbonContextCategory::id() const
{
    return (d_ptr->contextID);
}

void SARibbonContextCategory::setContextColor(const QColor color)
{
    d_ptr->contextColor = color;
}

QColor SARibbonContextCategory::contextColor() const
{
    return (d_ptr->contextColor);
}

QWidget* SARibbonContextCategory::parentWidget() const
{
    return (qobject_cast< QWidget* >(parent()));
}

bool SARibbonContextCategory::eventFilter(QObject* watched, QEvent* e)
{
    if (nullptr == watched) {
        return (false);
    }
    switch (e->type()) {
    case QEvent::Close: {
        SARibbonCategory* c = qobject_cast< SARibbonCategory* >(watched);
        if (c) {
#ifdef SA_RIBBON_DEBUG_HELP_DRAW
            qDebug() << " -----------> close event";
#endif
            takeCategory(c);
        }
    } break;

    default:
        break;
    }
    return (false);
}

/**
 * @brief ��ȡ�����ı�ǩ�ı���
 * @return
 */
QString SARibbonContextCategory::contextTitle() const
{
    return (d_ptr->contextTitle);
}

/**
 * @brief ���������ı�ǩ�ı��⣬�������officeģʽ����ʾ @ref SARibbonBar::RibbonStyle
 * @param contextTitle
 * @note �˺����ᴥ���ź�@sa contextTitleChanged
 */
void SARibbonContextCategory::setContextTitle(const QString& contextTitle)
{
    d_ptr->contextTitle = contextTitle;
    emit contextTitleChanged(contextTitle);
}

/**
 * @brief ��ȡ��Ӧ��tabҳ
 * @param index
 * @return
 */
SARibbonCategory* SARibbonContextCategory::categoryPage(int index)
{
    return (d_ptr->categoryDataList[ index ].categoryPage);
}

/**
 * @brief ��ȡ���е�SARibbonCategory*
 * @return
 */
QList< SARibbonCategory* > SARibbonContextCategory::categoryList() const
{
    QList< SARibbonCategory* > res;

    for (const SAPrivateRibbonCategoryData& c : qAsConst(d_ptr->categoryDataList)) {
        res.append(c.categoryPage);
    }
    return (res);
}

/**
 * @brief �Ƴ����category����ʱSARibbonContextCategory���ٹ������category
 * @param category
 * @return �ɹ��Ƴ�����true
 */
bool SARibbonContextCategory::takeCategory(SARibbonCategory* category)
{
    for (int i = 0; i < d_ptr->categoryDataList.size(); ++i) {
        if (d_ptr->categoryDataList[ i ].categoryPage == category) {
            d_ptr->categoryDataList.takeAt(i);
            return (true);
        }
    }
    return (false);
}

/**
 * @brief �ж��������Ƿ�ά���˴�SARibbonCategory
 * @param category
 * @return
 */
bool SARibbonContextCategory::isHaveCategory(SARibbonCategory* category) const
{
    for (int i = 0; i < d_ptr->categoryDataList.size(); ++i) {
        if (d_ptr->categoryDataList[ i ].categoryPage == category) {
            return (true);
        }
    }
    return (false);
}

void SARibbonContextCategory::onCategoryTitleChanged(const QString& title)
{
    SARibbonCategory* category = qobject_cast< SARibbonCategory* >(sender());
    if (category) {
        emit categoryTitleChanged(category, title);
    }
}

/*** End of inlined file: SARibbonContextCategory.cpp ***/

/*** Start of inlined file: SARibbonGalleryItem.cpp ***/
SARibbonGalleryItem::SARibbonGalleryItem() : m_flags(Qt::ItemIsEnabled | Qt::ItemIsSelectable), m_action(nullptr)
{
}

SARibbonGalleryItem::SARibbonGalleryItem(const QString& text, const QIcon& icon)
    : m_flags(Qt::ItemIsEnabled | Qt::ItemIsSelectable), m_action(nullptr)
{
    setText(text);
    setIcon(icon);
    setTextAlignment(Qt::AlignTop | Qt::AlignHCenter);
}

SARibbonGalleryItem::SARibbonGalleryItem(QAction* act) : m_flags(Qt::ItemIsEnabled | Qt::ItemIsSelectable)
{
    setTextAlignment(Qt::AlignTop | Qt::AlignHCenter);
    setAction(act);
}

SARibbonGalleryItem::~SARibbonGalleryItem()
{
}

void SARibbonGalleryItem::setData(int role, const QVariant& data)
{
    m_datas[ role ] = data;
}

QVariant SARibbonGalleryItem::data(int role) const
{
    if (m_action) {
        switch (role) {
        case Qt::DisplayRole:
            return (m_action->text());

        case Qt::ToolTipRole:
            return (m_action->toolTip());

        case Qt::DecorationRole:
            return (m_action->icon());
        default:
            break;
        }
    }
    return (m_datas.value(role));
}

void SARibbonGalleryItem::setText(const QString& text)
{
    setData(Qt::DisplayRole, text);
}

QString SARibbonGalleryItem::text() const
{
    if (m_action) {
        return (m_action->text());
    }
    return (data(Qt::DisplayRole).toString());
}

void SARibbonGalleryItem::setToolTip(const QString& text)
{
    setData(Qt::ToolTipRole, text);
}

QString SARibbonGalleryItem::toolTip() const
{
    if (m_action) {
        return (m_action->toolTip());
    }
    return (data(Qt::ToolTipRole).toString());
}

void SARibbonGalleryItem::setIcon(const QIcon& ico)
{
    setData(Qt::DecorationRole, ico);
}

QIcon SARibbonGalleryItem::icon() const
{
    if (m_action) {
        return (m_action->icon());
    }
    return (qvariant_cast< QIcon >(data(Qt::DecorationRole)));
}

bool SARibbonGalleryItem::isSelectable() const
{
    return (m_flags & Qt::ItemIsSelectable);
}

void SARibbonGalleryItem::setSelectable(bool isSelectable)
{
    if (isSelectable) {
        m_flags |= Qt::ItemIsSelectable;
    } else {
        m_flags = (m_flags & (~Qt::ItemIsSelectable));
    }
}

bool SARibbonGalleryItem::isEnable() const
{
    if (m_action) {
        return (m_action->isEnabled());
    }
    return (m_flags & Qt::ItemIsEnabled);
}

void SARibbonGalleryItem::setEnable(bool isEnable)
{
    if (m_action) {
        m_action->setEnabled(isEnable);
    }

    if (isEnable) {
        m_flags |= Qt::ItemIsEnabled;
    } else {
        m_flags = (m_flags & (~Qt::ItemIsEnabled));
    }
}

void SARibbonGalleryItem::setFlags(Qt::ItemFlags flag)
{
    m_flags = flag;
    if (m_action) {
        m_action->setEnabled(flag & Qt::ItemIsEnabled);
    }
}

Qt::ItemFlags SARibbonGalleryItem::flags() const
{
    return (m_flags);
}

void SARibbonGalleryItem::setAction(QAction* act)
{
    m_action = act;
    if (nullptr == m_action) {
        return;
    }
    if (act->isEnabled()) {
        m_flags |= Qt::ItemIsEnabled;
    } else {
        m_flags = (m_flags & (~Qt::ItemIsEnabled));
    }
}

QAction* SARibbonGalleryItem::action()
{
    return (m_action);
}

void SARibbonGalleryItem::setTextAlignment(Qt::Alignment a)
{
    setData(Qt::TextAlignmentRole, (int)a);
}

Qt::Alignment SARibbonGalleryItem::getTextAlignment() const
{
    return qvariant_cast< Qt::Alignment >(data(Qt::TextAlignmentRole));
}

/*** End of inlined file: SARibbonGalleryItem.cpp ***/

/*** Start of inlined file: SARibbonGalleryGroup.cpp ***/
#include <QPainter>
#include <QDebug>
#include <QActionGroup>
#include <QItemSelectionModel>

/**
 * @brief The SARibbonGalleryGroupPrivate class
 */
class SARibbonGalleryGroup::PrivateData
{
public:
    SARibbonGalleryGroup* q_ptr;
    QString mGroupTitle;
    SARibbonGalleryGroup::GalleryGroupStyle mPreStyle { SARibbonGalleryGroup::IconWithText };
    SARibbonGalleryGroup::DisplayRow mDisplayRow { SARibbonGalleryGroup::DisplayOneRow };
    bool mBlockRecalc { false };
    int mGridMinimumWidth { 0 };             ///< grid��С���
    int mGridMaximumWidth { 0 };             ///< grid�����
    QActionGroup* mActionGroup { nullptr };  ///< ����GalleryGroup�����actions�������actiongroup����
public:
    PrivateData(SARibbonGalleryGroup* p) : q_ptr(p)
    {
        mActionGroup = new QActionGroup(p);
        p->connect(mActionGroup, &QActionGroup::triggered, p, &SARibbonGalleryGroup::triggered);
        p->connect(mActionGroup, &QActionGroup::hovered, p, &SARibbonGalleryGroup::hovered);
    }
};

//===================================================
// SARibbonGalleryGroupItemDelegate
//===================================================

SARibbonGalleryGroupItemDelegate::SARibbonGalleryGroupItemDelegate(SARibbonGalleryGroup* group, QObject* parent)
    : QStyledItemDelegate(parent), m_group(group)
{
}

void SARibbonGalleryGroupItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (nullptr == m_group) {
        return;
    }
    switch (m_group->getGalleryGroupStyle()) {
    case SARibbonGalleryGroup::IconWithText:
        paintIconWithText(painter, option, index);
        break;
    case SARibbonGalleryGroup::IconWithWordWrapText:
        paintIconWithTextWordWrap(painter, option, index);
        break;
    case SARibbonGalleryGroup::IconOnly:
        paintIconOnly(painter, option, index);
        break;
    default:
        paintIconWithText(painter, option, index);
        break;
    }
}

void SARibbonGalleryGroupItemDelegate::paintIconOnly(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyle* style = m_group->style();
    int sp        = m_group->spacing();
    sp += 3;
    painter->save();
    painter->setClipRect(option.rect);
    style->drawPrimitive(QStyle::PE_PanelItemViewItem, &option, painter, m_group);
    // draw the icon
    QRect iconRect = option.rect;

    iconRect.adjust(sp, sp, -sp, -sp);
    QIcon ico = qvariant_cast< QIcon >(index.data(Qt::DecorationRole));

    ico.paint(painter, iconRect, Qt::AlignCenter, QIcon::Normal, QIcon::On);
    painter->restore();
}

void SARibbonGalleryGroupItemDelegate::paintIconWithText(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

void SARibbonGalleryGroupItemDelegate::paintIconWithTextWordWrap(QPainter* painter,
                                                                 const QStyleOptionViewItem& option,
                                                                 const QModelIndex& index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

QSize SARibbonGalleryGroupItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(index);
    Q_UNUSED(option);
    return m_group->gridSize();
}

//===================================================
// SARibbonGalleryGroupModel
//===================================================

SARibbonGalleryGroupModel::SARibbonGalleryGroupModel(QObject* parent) : QAbstractListModel(parent)
{
}

SARibbonGalleryGroupModel::~SARibbonGalleryGroupModel()
{
    clear();
}

int SARibbonGalleryGroupModel::rowCount(const QModelIndex& parent) const
{
    return (parent.isValid() ? 0 : m_items.size());
}

Qt::ItemFlags SARibbonGalleryGroupModel::flags(const QModelIndex& index) const
{
    if (!index.isValid() || (index.row() >= m_items.size())) {
        return (Qt::NoItemFlags);
    }
    return (m_items.at(index.row())->flags());
}

QVariant SARibbonGalleryGroupModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || (index.row() >= m_items.count())) {
        return (QVariant());
    }
    return (m_items.at(index.row())->data(role));
}

QModelIndex SARibbonGalleryGroupModel::index(int row, int column, const QModelIndex& parent) const
{
    if (hasIndex(row, column, parent)) {
        return (createIndex(row, column, m_items.at(row)));
    }
    return (QModelIndex());
}

bool SARibbonGalleryGroupModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid() || (index.row() >= m_items.count())) {
        return (false);
    }

    m_items.at(index.row())->setData(role, value);
    return (true);
}

void SARibbonGalleryGroupModel::clear()
{
    beginResetModel();
    for (int i = 0; i < m_items.count(); ++i) {
        if (m_items.at(i)) {
            delete m_items.at(i);
        }
    }
    m_items.clear();
    endResetModel();
}

SARibbonGalleryItem* SARibbonGalleryGroupModel::at(int row) const
{
    return (m_items.value(row));
}

void SARibbonGalleryGroupModel::insert(int row, SARibbonGalleryItem* item)
{
    beginInsertRows(QModelIndex(), row, row);
    m_items.insert(row, item);
    endInsertRows();
}

SARibbonGalleryItem* SARibbonGalleryGroupModel::take(int row)
{
    if ((row < 0) || (row >= m_items.count())) {
        return (0);
    }

    beginRemoveRows(QModelIndex(), row, row);
    SARibbonGalleryItem* item = m_items.takeAt(row);

    endRemoveRows();
    return (item);
}

void SARibbonGalleryGroupModel::append(SARibbonGalleryItem* item)
{
    beginInsertRows(QModelIndex(), m_items.count(), m_items.count() + 1);
    m_items.append(item);
    endInsertRows();
}

//===================================================
// SARibbonGalleryGroup
//===================================================
SARibbonGalleryGroup::SARibbonGalleryGroup(QWidget* w)
    : QListView(w), d_ptr(new SARibbonGalleryGroup::PrivateData(this))
{
    setViewMode(QListView::IconMode);
    setResizeMode(QListView::Adjust);
    setSelectionRectVisible(true);
    setUniformItemSizes(true);
    setSpacing(1);
    setItemDelegate(new SARibbonGalleryGroupItemDelegate(this, this));
    connect(this, &QAbstractItemView::clicked, this, &SARibbonGalleryGroup::onItemClicked);
    SARibbonGalleryGroupModel* m = new SARibbonGalleryGroupModel(this);
    setModel(m);
}

SARibbonGalleryGroup::~SARibbonGalleryGroup()
{
}

/**
 * @brief �Ƿ��ֹ����
 * @param on
 */
void SARibbonGalleryGroup::setRecalcGridSizeBlock(bool on)
{
    d_ptr->mBlockRecalc = on;
}

bool SARibbonGalleryGroup::isRecalcGridSizeBlock() const
{
    return d_ptr->mBlockRecalc;
}

/**
 * @brief ���¼���grid��icon�ĳߴ�
 */
void SARibbonGalleryGroup::recalcGridSize()
{
    recalcGridSize(height());
}

void SARibbonGalleryGroup::recalcGridSize(int galleryHeight)
{
    if (isRecalcGridSizeBlock()) {
        return;
    }
    // ����ͨ��DisplayRow����GridSize
    int dr = static_cast< int >(getDisplayRow());
    if (dr < 1) {
        dr = 1;
    } else if (dr > 3) {
        dr = 3;
    }
    int h = galleryHeight / dr;
    if (h <= 1) {
        h = galleryHeight;
    }
    int w = h;
    if (getGridMinimumWidth() > 0) {
        if (w < getGridMinimumWidth()) {
            w = getGridMinimumWidth();
        }
    }
    if (getGridMaximumWidth() > 0) {
        if (w > getGridMaximumWidth()) {
            w = getGridMaximumWidth();
        }
    }
    setGridSize(QSize(w, h));
    //��ͨ��GalleryGroupStyleȷ��icon�ĳߴ�
    const int shiftpix = 4;  // ������ƶ����أ�qt������ƶ���ͼ����ʱ���ƶ�һ�£����û���ȷ�Ķ�̬������������ֺ����ᳬ����ʾ��Χ�����Ҫ�ڴ˻���������һ��
    switch (getGalleryGroupStyle()) {
    case IconWithText: {
        int textHeight = fontMetrics().lineSpacing();
        int iconHeight = h - textHeight - 2 * spacing() - shiftpix;
        if (iconHeight > 0) {
            setIconSize(QSize(w - 2 * spacing() - shiftpix, iconHeight));
        } else {
            setIconSize(QSize(w - 2 * spacing() - shiftpix, h - 2 * spacing() - shiftpix));
        }
        break;
    }
    case IconWithWordWrapText: {
        int textHeight = fontMetrics().lineSpacing() * 2;
        int iconHeight = h - textHeight;
        if (iconHeight > 0) {
            setIconSize(QSize(w - 2 * spacing() - shiftpix, iconHeight - 2 * spacing() - shiftpix));
        } else {
            setIconSize(QSize(w - 2 * spacing() - shiftpix, h - 2 * spacing() - shiftpix));
        }
        break;
    }
    case IconOnly: {
        setIconSize(QSize(w - 2 * spacing() - shiftpix, h - 2 * spacing() - shiftpix));
        break;
    }
    default: {
        setIconSize(QSize(w - 2 * spacing() - shiftpix, h - 2 * spacing() - shiftpix));
        break;
    }
    }
#if 0
	qDebug() << "SARibbonGalleryGroup::recalcGridSize(" << galleryHeight << "): gridSize=" << gridSize()
			 << " iconSize=" << iconSize();
#endif
}

///
/// \brief ����Ĭ�ϵ�Ԥ����ʽ
/// \param style
///
void SARibbonGalleryGroup::setGalleryGroupStyle(SARibbonGalleryGroup::GalleryGroupStyle style)
{
    d_ptr->mPreStyle = style;
    if (style == IconWithWordWrapText) {
        setWordWrap(true);
    }
    recalcGridSize();
}

SARibbonGalleryGroup::GalleryGroupStyle SARibbonGalleryGroup::getGalleryGroupStyle() const
{
    return d_ptr->mPreStyle;
}

void SARibbonGalleryGroup::addItem(const QString& text, const QIcon& icon)
{
    if (nullptr == groupModel()) {
        return;
    }
    addItem(new SARibbonGalleryItem(text, icon));
}

/**
 * @brief ���һ����Ŀ
 *
 * @param item ��Ŀ���ڴ�����Ȩ����SARibbonGalleryGroup����
 */
void SARibbonGalleryGroup::addItem(SARibbonGalleryItem* item)
{
    if (nullptr == groupModel()) {
        return;
    }
    groupModel()->append(item);
}

void SARibbonGalleryGroup::addActionItem(QAction* act)
{
    if (nullptr == groupModel()) {
        return;
    }
    d_ptr->mActionGroup->addAction(act);
    groupModel()->append(new SARibbonGalleryItem(act));
}

void SARibbonGalleryGroup::addActionItemList(const QList< QAction* >& acts)
{
    SARibbonGalleryGroupModel* model = groupModel();

    if (nullptr == model) {
        return;
    }
    for (QAction* a : acts) {
        d_ptr->mActionGroup->addAction(a);
    }
    for (int i = 0; i < acts.size(); ++i) {
        model->append(new SARibbonGalleryItem(acts[ i ]));
    }
}

///
/// \brief ����һ��model�����model�ĸ�����SARibbonGalleryGroup�����Ҫ����model����Ҫ�ֶ�����model�ĸ���
///
void SARibbonGalleryGroup::setupGroupModel()
{
    setModel(new SARibbonGalleryGroupModel(this));
}

SARibbonGalleryGroupModel* SARibbonGalleryGroup::groupModel()
{
    return (qobject_cast< SARibbonGalleryGroupModel* >(model()));
}

void SARibbonGalleryGroup::setGroupTitle(const QString& title)
{
    d_ptr->mGroupTitle = title;
    emit groupTitleChanged(d_ptr->mGroupTitle);
}

QString SARibbonGalleryGroup::getGroupTitle() const
{
    return (d_ptr->mGroupTitle);
}

void SARibbonGalleryGroup::selectByIndex(int i)
{
    SARibbonGalleryGroupModel* model = groupModel();

    if (nullptr == model) {
        return;
    }
    QModelIndex ind               = model->index(i, 0, QModelIndex());
    QItemSelectionModel* selmodel = selectionModel();

    if (selmodel) {
        selmodel->select(ind, QItemSelectionModel::SelectCurrent);
    }
}

/**
 * @brief ������ʾ������
 * @param r
 */
void SARibbonGalleryGroup::setDisplayRow(DisplayRow r)
{
    d_ptr->mDisplayRow = r;
    recalcGridSize();
}

/**
 * @brief Gallery��ʾ������
 * @return
 */
SARibbonGalleryGroup::DisplayRow SARibbonGalleryGroup::getDisplayRow() const
{
    return d_ptr->mDisplayRow;
}

/**
 * @brief ����grid��С�Ŀ�ȣ�Ĭ��Ϊ0�������ƣ�
 * @param w
 */
void SARibbonGalleryGroup::setGridMinimumWidth(int w)
{
    d_ptr->mGridMinimumWidth = w;
}

/**
 * @brief grid��С�Ŀ�ȣ�Ĭ��Ϊ0�������ƣ�
 * @return
 */
int SARibbonGalleryGroup::getGridMinimumWidth() const
{
    return d_ptr->mGridMinimumWidth;
}

/**
 * @brief ����grid���Ŀ�ȣ�Ĭ��Ϊ0�������ƣ�
 * @param w
 */
void SARibbonGalleryGroup::setGridMaximumWidth(int w)
{
    d_ptr->mGridMaximumWidth = w;
}

/**
 * @brief grid���ĵĿ�ȣ�Ĭ��Ϊ0�������ƣ�
 * @param w
 */
int SARibbonGalleryGroup::getGridMaximumWidth() const
{
    return d_ptr->mGridMaximumWidth;
}

/**
 * @brief ��ȡSARibbonGalleryGroup�����actiongroup
 * @return
 */
QActionGroup* SARibbonGalleryGroup::getActionGroup() const
{
    return d_ptr->mActionGroup;
}

void SARibbonGalleryGroup::onItemClicked(const QModelIndex& index)
{
    if (index.isValid()) {
        SARibbonGalleryItem* item = (SARibbonGalleryItem*)index.internalPointer();
        if (item) {
            QAction* act = item->action();
            if (act) {
                act->activate(QAction::Trigger);
            }
        }
    }
}

void SARibbonGalleryGroup::onItemEntered(const QModelIndex& index)
{
    if (index.isValid()) {
        SARibbonGalleryItem* item = (SARibbonGalleryItem*)index.internalPointer();
        if (item) {
            QAction* act = item->action();
            if (act) {
                act->activate(QAction::Hover);
            }
        }
    }
}

/*** End of inlined file: SARibbonGalleryGroup.cpp ***/

/*** Start of inlined file: SARibbonGallery.cpp ***/
#include <QIcon>
#include <QApplication>
#define ICON_ARROW_UP QIcon(":/image/resource/ArrowUp.png")
#define ICON_ARROW_DOWN QIcon(":/image/resource/ArrowDown.png")
#define ICON_ARROW_MORE QIcon(":/image/resource/ArrowMore.png")

#include <QResizeEvent>
#include <QDebug>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QLabel>

#include <QActionGroup>

/**
 * @brief The SARibbonGalleryPrivate class
 */
class SARibbonGallery::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonGallery)
public:
    static int sGalleryButtonMaximumWidth;
    SARibbonControlButton* buttonUp { nullptr };
    SARibbonControlButton* buttonDown { nullptr };
    SARibbonControlButton* buttonMore { nullptr };
#if 0
	SARibbonMenu *popupWidget;
#else
    SARibbonGalleryViewport* popupWidget { nullptr };
#endif
    SARibbonGalleryGroup* viewportGroup { nullptr };
    QBoxLayout* btnLayout { nullptr };
    QBoxLayout* layout { nullptr };
    PrivateData(SARibbonGallery* p) : q_ptr(p)
    {
    }

    void init()
    {
        buttonUp   = new SARibbonControlButton(q_ptr);
        buttonDown = new SARibbonControlButton(q_ptr);
        buttonMore = new SARibbonControlButton(q_ptr);
        buttonUp->setToolButtonStyle(Qt::ToolButtonIconOnly);
        buttonDown->setToolButtonStyle(Qt::ToolButtonIconOnly);
        buttonMore->setToolButtonStyle(Qt::ToolButtonIconOnly);
        buttonUp->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        buttonDown->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        buttonMore->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        buttonUp->setObjectName(QStringLiteral("SARibbonGalleryButtonUp"));
        buttonDown->setObjectName(QStringLiteral("SARibbonGalleryButtonDown"));
        buttonMore->setObjectName(QStringLiteral("SARibbonGalleryButtonMore"));
        buttonUp->setMaximumWidth(sGalleryButtonMaximumWidth);
        buttonDown->setMaximumWidth(sGalleryButtonMaximumWidth);
        buttonMore->setMaximumWidth(sGalleryButtonMaximumWidth);
        buttonUp->setIcon(ICON_ARROW_UP);
        buttonDown->setIcon(ICON_ARROW_DOWN);
        buttonMore->setIcon(ICON_ARROW_MORE);
        q_ptr->connect(buttonUp, &QAbstractButton::clicked, q_ptr, &SARibbonGallery::pageUp);
        q_ptr->connect(buttonDown, &QAbstractButton::clicked, q_ptr, &SARibbonGallery::pageDown);
        q_ptr->connect(buttonMore, &QAbstractButton::clicked, q_ptr, &SARibbonGallery::showMoreDetail);
        //�ź�ת��
        q_ptr->connect(q_ptr, &SARibbonGallery::triggered, q_ptr, &SARibbonGallery::onTriggered);
        popupWidget   = nullptr;
        viewportGroup = nullptr;
        btnLayout     = new QBoxLayout(QBoxLayout::TopToBottom);
        btnLayout->setSpacing(0);
        btnLayout->setContentsMargins(0, 0, 0, 0);
        btnLayout->addWidget(buttonUp);
        btnLayout->addWidget(buttonDown);
        btnLayout->addWidget(buttonMore);
        layout = new QBoxLayout(QBoxLayout::RightToLeft);
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addLayout(btnLayout);
        layout->addStretch();
        q_ptr->setLayout(layout);
    }

    bool isValid() const
    {
        return (q_ptr != nullptr);
    }

    void createPopupWidget()
    {
        if (nullptr == popupWidget) {
#if 0
			popupWidget = new SARibbonMenu(Parent);
#else
            popupWidget = new SARibbonGalleryViewport(q_ptr);
#endif
        }
    }

    void setViewPort(SARibbonGalleryGroup* v)
    {
        if (nullptr == viewportGroup) {
            viewportGroup = RibbonSubElementDelegate->createRibbonGalleryGroup(q_ptr);
            layout->addWidget(viewportGroup, 1);
        }
        viewportGroup->setRecalcGridSizeBlock(true);
        viewportGroup->setGalleryGroupStyle(v->getGalleryGroupStyle());
        viewportGroup->setDisplayRow(v->getDisplayRow());
        viewportGroup->setSpacing(v->spacing());
        viewportGroup->setGridMaximumWidth(v->getGridMaximumWidth());
        viewportGroup->setGridMinimumWidth(v->getGridMinimumWidth());
        viewportGroup->setRecalcGridSizeBlock(false);
        viewportGroup->recalcGridSize(viewportGroup->height());
        viewportGroup->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        viewportGroup->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        viewportGroup->setModel(v->model());
        viewportGroup->show();
    }
};

//��̬������ʼ��

/**
 * @brief SARibbonGalleryPrivate::sGalleryButtonMaximumWidth
 */
int SARibbonGallery::PrivateData::sGalleryButtonMaximumWidth = 15;

//===================================================
// SARibbonGalleryViewport
//===================================================

SARibbonGalleryViewport::SARibbonGalleryViewport(QWidget* parent) : QWidget(parent)
{
    setWindowFlags(Qt::Popup);
    QPalette pl = palette();
    pl.setBrush(QPalette::Window, pl.brush(QPalette::Base));
    setPalette(pl);
    m_layout = new QVBoxLayout(this);
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0, 0, 0, 0);
}

/**
 * @brief ��Ӵ��ڲ�������
 * @param w
 */
void SARibbonGalleryViewport::addWidget(QWidget* w)
{
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_layout->addWidget(w);
}

/**
 * @brief ��Ӵ��ڣ�������
 * @param w
 * @param title
 */
void SARibbonGalleryViewport::addWidget(QWidget* w, const QString& title)
{
    QLabel* label = new QLabel(this);
    label->setText(title);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_layout->addWidget(label);
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_layout->addWidget(w);
    _widgetToTitleLable[ w ] = label;
}

/**
 * @brief ͨ��SARibbonGalleryGroup��ȡ��Ӧ�ı��⣬�û�����ͨ���˺�������QLabel������
 * @param g
 * @return ���û�й���group��������nullptr
 */
QLabel* SARibbonGalleryViewport::getWidgetTitleLabel(QWidget* w)
{
    return _widgetToTitleLable.value(w, nullptr);
}

/**
 * @brief �Ƴ�����
 * @param w
 */
void SARibbonGalleryViewport::removeWidget(QWidget* w)
{
    QLabel* label = getWidgetTitleLabel(w);
    if (label) {
        m_layout->removeWidget(label);
    }
    m_layout->removeWidget(w);
}

/**
 * @brief widget�ı���ı�
 * @param g
 * @param title
 */
void SARibbonGalleryViewport::widgetTitleChanged(QWidget* w, const QString& title)
{
    QLabel* l = getWidgetTitleLabel(w);
    if (l) {
        l->setText(title);
    }
}

//===================================================
// SARibbonGallery
//===================================================

SARibbonGallery::SARibbonGallery(QWidget* parent) : QFrame(parent), d_ptr(new SARibbonGallery::PrivateData(this))
{
    d_ptr->init();
    setFrameShape(QFrame::Box);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumWidth(200);
}

SARibbonGallery::~SARibbonGallery()
{
}

QSize SARibbonGallery::sizeHint() const
{
    return (QSize(100, 62));
}

/**
 * @brief ��ȡһ���հ�SARibbonGalleryGroup
 * @return
 */
SARibbonGalleryGroup* SARibbonGallery::addGalleryGroup()
{
    SARibbonGalleryGroup* group = RibbonSubElementDelegate->createRibbonGalleryGroup(this);
    addGalleryGroup(group);
    return (group);
}

/**
 * @brief ���һ��SARibbonGalleryGroup
 * @param group
 */
void SARibbonGallery::addGalleryGroup(SARibbonGalleryGroup* group)
{
    group->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    SARibbonGalleryViewport* viewport = ensureGetPopupViewPort();
    viewport->addWidget(group, group->getGroupTitle());
    connect(group, &QAbstractItemView::clicked, this, &SARibbonGallery::onItemClicked);
    connect(group, &SARibbonGalleryGroup::groupTitleChanged, this, [ group, viewport ](const QString& t) {
        viewport->widgetTitleChanged(group, t);
    });
    connect(group, &SARibbonGalleryGroup::triggered, this, &SARibbonGallery::triggered);
    connect(group, &SARibbonGalleryGroup::hovered, this, &SARibbonGallery::hovered);
    setCurrentViewGroup(group);
}

/**
 * @brief ���һ��actions
 * @param title actions�������
 * @param actions
 * @return ����SARibbonGalleryGroup���û�����ͨ���޸�SARibbonGalleryGroup���Կ�������ʾ����
 */
SARibbonGalleryGroup* SARibbonGallery::addCategoryActions(const QString& title, QList< QAction* > actions)
{
    SARibbonGalleryGroup* group = RibbonSubElementDelegate->createRibbonGalleryGroup(this);
    if (!title.isEmpty()) {
        group->setGroupTitle(title);
    }
    group->addActionItemList(actions);
    addGalleryGroup(group);
    return (group);
}

void SARibbonGallery::setCurrentViewGroup(SARibbonGalleryGroup* group)
{
    d_ptr->setViewPort(group);
    QApplication::postEvent(this, new QResizeEvent(size(), size()));
}

SARibbonGalleryGroup* SARibbonGallery::currentViewGroup() const
{
    return (d_ptr->viewportGroup);
}

/**
 * @brief ��ȡ��������
 * @return
 */
SARibbonGalleryViewport* SARibbonGallery::getPopupViewPort() const
{
    return d_ptr->popupWidget;
}

/**
 * @brief �������ұ��������ư�ť������ȣ�Ĭ��15��
 * @param w
 */
void SARibbonGallery::setGalleryButtonMaximumWidth(int w)
{
    SARibbonGallery::PrivateData::sGalleryButtonMaximumWidth = w;
}

/**
 * @brief �Ϸ�ҳ
 */
void SARibbonGallery::pageDown()
{
    if (d_ptr->viewportGroup) {
        QScrollBar* vscrollBar = d_ptr->viewportGroup->verticalScrollBar();
        int v                  = vscrollBar->value();
        v += vscrollBar->singleStep();
        vscrollBar->setValue(v);
    }
}

/**
 * @brief �·�ҳ
 */
void SARibbonGallery::pageUp()
{
    if (d_ptr->viewportGroup) {
        QScrollBar* vscrollBar = d_ptr->viewportGroup->verticalScrollBar();
        int v                  = vscrollBar->value();
        v -= vscrollBar->singleStep();
        vscrollBar->setValue(v);
    }
}

/**
 * @brief ��ʾ���ഥ����Ĭ�ϵ����ڲ������SARibbonGalleryViewport���û������ش˺���ʵ���Զ���ĵ���
 */
void SARibbonGallery::showMoreDetail()
{
    if (nullptr == d_ptr->popupWidget) {
        return;
    }
    QSize popupMenuSize = d_ptr->popupWidget->sizeHint();
    QPoint start        = mapToGlobal(QPoint(0, 0));

    int width = d_ptr->viewportGroup->width();  // viewport

    width += qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent);  // scrollbar
    d_ptr->popupWidget->setGeometry(start.x(), start.y(), width, popupMenuSize.height());
    d_ptr->popupWidget->show();
}

void SARibbonGallery::onItemClicked(const QModelIndex& index)
{
    QObject* obj                = sender();
    SARibbonGalleryGroup* group = qobject_cast< SARibbonGalleryGroup* >(obj);
    if (group) {
        setCurrentViewGroup(group);
        SARibbonGalleryGroup* curGroup = currentViewGroup();
        curGroup->scrollTo(index);
        curGroup->setCurrentIndex(index);
    }
}

void SARibbonGallery::onTriggered(QAction* action)
{
    Q_UNUSED(action);
    //�����رյ�������
    if (d_ptr->popupWidget) {
        if (d_ptr->popupWidget->isVisible()) {
            d_ptr->popupWidget->hide();
        }
    }
}

SARibbonGalleryViewport* SARibbonGallery::ensureGetPopupViewPort()
{
    if (nullptr == d_ptr->popupWidget) {
        d_ptr->createPopupWidget();
    }
    return (d_ptr->popupWidget);
}

void SARibbonGallery::resizeEvent(QResizeEvent* event)
{
    QFrame::resizeEvent(event);
    //��SARibbonGalleryViewport����SARibbonGalleryGroup���óߴ�
    int h = layout()->contentsRect().height();
    if (d_ptr->viewportGroup) {
        h = d_ptr->viewportGroup->height();
        d_ptr->viewportGroup->recalcGridSize();
    }
    if (d_ptr->popupWidget) {
        QLayout* lay = d_ptr->popupWidget->layout();
        if (!lay) {
            return;
        }
        int c = lay->count();
        for (int i = 0; i < c; ++i) {
            QLayoutItem* item = lay->itemAt(i);
            if (!item) {
                continue;
            }
            QWidget* w = item->widget();
            if (!w) {
                continue;
            }
            SARibbonGalleryGroup* g = qobject_cast< SARibbonGalleryGroup* >(w);
            if (!g) {
                continue;
            }
            g->recalcGridSize(h);
        }
    }
}

void SARibbonGallery::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);
}

/*** End of inlined file: SARibbonGallery.cpp ***/

/*** Start of inlined file: SARibbonBar.cpp ***/
#include <QApplication>
#include <QPainter>

#include <QSet>
#include <QResizeEvent>
#include <QVariant>
#include <QLinearGradient>
#include <QDebug>
#include <QApplication>
#include <QAction>
#include <QHoverEvent>
#include <QTimer>
#include <QStyleOptionMenuItem>

#define HELP_DRAW_RECT(p, rect)                                                                                        \
    do {                                                                                                               \
        p.save();                                                                                                      \
        QPen _pen(Qt::DashDotDotLine);                                                                                 \
        _pen.setColor(QColor(219, 26, 59));                                                                            \
        p.setPen(_pen);                                                                                                \
        p.setBrush(QBrush());                                                                                          \
        p.drawRect(rect);                                                                                              \
        p.restore();                                                                                                   \
    } while (0)

class _SAContextCategoryManagerData
{
public:
    SARibbonContextCategory* contextCategory;
    QList< int > tabPageIndex;
    bool operator==(const SARibbonContextCategory* contextPage)
    {
        return (this->contextCategory == contextPage);
    }
};

class _SARibbonTabData
{
public:
    SARibbonCategory* category;
    int index;
    _SARibbonTabData() : category(nullptr), index(-1)
    {
    }
};
Q_DECLARE_METATYPE(_SARibbonTabData)

class SARibbonBar::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonBar)
public:
    QAbstractButton* mApplicationButton;
    SARibbonTabBar* mRibbonTabBar;
    SARibbonStackedWidget* mStackedContainerWidget;
    QList< _SAContextCategoryManagerData > mCurrentShowingContextCategory;
    QList< SARibbonContextCategory* > mContextCategoryList;  ///< ������е������ı�ǩ
    QList< _SARibbonTabData > mHidedCategory;
    int mIconRightBorderPosition;  ///< ������xֵ����Сֵ������ͼ��Ϳ��������ť����ֵ����Ҫ�仯
    SARibbonControlButton* mMinimumCategoryButton;  ///< ������尴ť
    SARibbonButtonGroupWidget* mRightButtonGroup;   ///< ��tab bar�ұߵİ�ťȺ
    SARibbonQuickAccessBar* mQuickAccessBar;        ///< ������Ӧ��
    SARibbonBar::RibbonStyle mRibbonStyle;          ///< ribbon�ķ��
    SARibbonBar::RibbonStyle mLastShowStyle;        ///< ribbon�ķ��
    SARibbonBar::RibbonMode mCurrentRibbonMode;     ///< ��¼��ǰģʽ
    QSize mWindowButtonSize;                        ///< ��SARibbonMainWindow���ߵ�windowbutton�ĳߴ�
    QList< QColor > mContextCategoryColorList;      ///< contextCategory��ɫϵ
    int mContextCategoryColorListIndex;             ///< ��¼contextCategoryɫϵ����
    QColor mTitleTextColor;                         ///< ����������ɫ
    QColor mTabBarBaseLineColor;                    ///< tabbar �ײ������һ������������������ɫ
    Qt::Alignment mTitleAligment;                   ///< ������뷽ʽ
    PrivateData(SARibbonBar* par)
        : q_ptr(par)
        , mApplicationButton(nullptr)
        , mRibbonTabBar(nullptr)
        , mStackedContainerWidget(nullptr)
        , mIconRightBorderPosition(1)
        , mMinimumCategoryButton(nullptr)
        , mRightButtonGroup(nullptr)
        , mRibbonStyle(SARibbonBar::OfficeStyle)
        , mLastShowStyle(SARibbonBar::OfficeStyle)
        , mCurrentRibbonMode(SARibbonBar::NormalRibbonMode)
        , mWindowButtonSize(RibbonSubElementStyleOpt.titleBarHeight() * 4, RibbonSubElementStyleOpt.titleBarHeight())
        , mContextCategoryColorListIndex(-1)
        , mTitleTextColor(Qt::black)
        , mTabBarBaseLineColor(186, 201, 219)
        , mTitleAligment(Qt::AlignCenter)
    {
        mContextCategoryColorList << QColor(201, 89, 156)  // õ��
                                  << QColor(242, 203, 29)  // ��
                                  << QColor(255, 157, 0)   // ��
                                  << QColor(14, 81, 167)   // ��
                                  << QColor(228, 0, 69)    // ��
                                  << QColor(67, 148, 0)    // ��
                ;
    }

    void init()
    {
        mApplicationButton = RibbonSubElementDelegate->createRibbonApplicationButton(q_ptr);
        q_ptr->connect(mApplicationButton, &QAbstractButton::clicked, q_ptr, &SARibbonBar::applicationButtonClicked);
        mRibbonTabBar = RibbonSubElementDelegate->createRibbonTabBar(q_ptr);
        mRibbonTabBar->setObjectName(QStringLiteral("objSARibbonTabBar"));
        mRibbonTabBar->setDrawBase(false);
        q_ptr->connect(mRibbonTabBar, &QTabBar::currentChanged, q_ptr, &SARibbonBar::onCurrentRibbonTabChanged);
        q_ptr->connect(mRibbonTabBar, &QTabBar::tabBarClicked, q_ptr, &SARibbonBar::onCurrentRibbonTabClicked);
        q_ptr->connect(mRibbonTabBar, &QTabBar::tabBarDoubleClicked, q_ptr, &SARibbonBar::onCurrentRibbonTabDoubleClicked);
        q_ptr->connect(mRibbonTabBar, &QTabBar::tabMoved, q_ptr, &SARibbonBar::onTabMoved);
        //
        mStackedContainerWidget = RibbonSubElementDelegate->createRibbonStackedWidget(q_ptr);
        mRibbonTabBar->setObjectName(QStringLiteral("objSAStackedContainerWidget"));
        mStackedContainerWidget->connect(mStackedContainerWidget, &SARibbonStackedWidget::hidWindow, q_ptr, &SARibbonBar::onStackWidgetHided);
        mStackedContainerWidget->installEventFilter(q_ptr);
        setNormalMode();
        //
        mQuickAccessBar = RibbonSubElementDelegate->createQuickAccessBar(q_ptr);
        mQuickAccessBar->setObjectName(QStringLiteral("objSARibbonQuickAccessBar"));
        mQuickAccessBar->setIcon(q_ptr->windowIcon());
    }

    void setApplicationButton(QAbstractButton* btn)
    {
        if (mApplicationButton) {
            delete mApplicationButton;
        }
        if (btn) {
            if (btn->parent() != q_ptr) {
                btn->setParent(q_ptr);
            }
            btn->move(0, q_ptr->titleBarHeight());
            q_ptr->connect(btn, &QAbstractButton::clicked, q_ptr, &SARibbonBar::applicationButtonClicked);
        }
        mApplicationButton = btn;
    }

    bool isContainContextCategoryInList(SARibbonContextCategory* contextCategory)
    {
        for (int i = 0; i < mCurrentShowingContextCategory.size(); ++i) {
            if (mCurrentShowingContextCategory[ i ] == contextCategory) {
                return (true);
            }
        }
        return (false);
    }

    void setHideMode()
    {
        mCurrentRibbonMode = SARibbonBar::MinimumRibbonMode;
        this->mStackedContainerWidget->setPopupMode();
        this->mStackedContainerWidget->setFocusPolicy(Qt::NoFocus);
        this->mStackedContainerWidget->clearFocus();
        this->mRibbonTabBar->setFocus();
        this->mStackedContainerWidget->hide();
        q_ptr->setFixedHeight(mRibbonTabBar->geometry().bottom());
    }

    void setNormalMode()
    {
        mCurrentRibbonMode = SARibbonBar::NormalRibbonMode;
        this->mStackedContainerWidget->setNormalMode();
        this->mStackedContainerWidget->setFocus();
        this->mStackedContainerWidget->show();
    }

    QColor getContextCategoryColor()
    {
        if (mContextCategoryColorList.isEmpty()) {
            mContextCategoryColorListIndex = -1;
            return (QColor());
        }
        ++mContextCategoryColorListIndex;
        if ((mContextCategoryColorListIndex >= mContextCategoryColorList.size()) || (mContextCategoryColorListIndex < 0)) {
            mContextCategoryColorListIndex = 0;
        }
        return (mContextCategoryColorList.at(mContextCategoryColorListIndex));
    }

    void updateTabData()
    {
        int tabcount = mRibbonTabBar->count();

        for (int i = 0; i < tabcount; ++i) {
            QVariant var = mRibbonTabBar->tabData(i);
            if (var.isValid()) {
                _SARibbonTabData p = var.value< _SARibbonTabData >();
                p.index            = i;
                mRibbonTabBar->setTabData(i, QVariant::fromValue(p));
            }
        }
        //ˢ����tabdata��ϢҲҪ����ˢ��ContextCategory��Ϣ
        for (_SAContextCategoryManagerData& cd : mCurrentShowingContextCategory) {
            cd.tabPageIndex.clear();
            for (int i = 0; i < cd.contextCategory->categoryCount(); ++i) {
                SARibbonCategory* category = cd.contextCategory->categoryPage(i);
                for (int t = 0; t < tabcount; ++t) {
                    QVariant v = mRibbonTabBar->tabData(t);
                    if (v.isValid()) {
                        _SARibbonTabData d = v.value< _SARibbonTabData >();
                        if (d.category == category) {
                            cd.tabPageIndex.append(t);
                        }
                    } else {
                        cd.tabPageIndex.append(-1);
                    }
                }
            }
        }
    }
};

//===================================================
// SARibbonBar
//===================================================

/**
 * @brief SARibbonBar���캯��
 * @param parent
 */
SARibbonBar::SARibbonBar(QWidget* parent) : QMenuBar(parent), d_ptr(new SARibbonBar::PrivateData(this))
{
    d_ptr->init();
    if (parent) {
        connect(parent, &QWidget::windowTitleChanged, this, &SARibbonBar::onWindowTitleChanged);
        connect(parent, &QWidget::windowIconChanged, this, &SARibbonBar::onWindowIconChanged);
    }
    setRibbonStyle(OfficeStyle);
}

SARibbonBar::~SARibbonBar()
{
}
/**
 * @brief �ж���ʽ�Ƿ�Ϊ����
 * @param s
 * @return ���з���true������false����ǰ��3��
 */
bool SARibbonBar::isTwoRowStyle(SARibbonBar::RibbonStyle s)
{
    return ((s & 0xFF00) > 0);
}

/**
 * @brief �ж��Ƿ���office��ʽ
 * @param s
 * @return Office��ʽ����true���������wps��ʽ
 */
bool SARibbonBar::isOfficeStyle(SARibbonBar::RibbonStyle s)
{
    return ((s & 0xFF) == 0);
}

/**
 * @brief ��ȡ�汾��Ϣ
 * @return {SA_RIBBON_BAR_VERSION_MAJ}.{SA_RIBBON_BAR_VERSION_MIN}.{SA_RIBBON_BAR_VERSION_PAT}
 */
QString SARibbonBar::versionString()
{
    return QString("%1.%2.%3").arg(SA_RIBBON_BAR_VERSION_MAJ).arg(SA_RIBBON_BAR_VERSION_MIN).arg(SA_RIBBON_BAR_VERSION_PAT);
}

/**
 * @brief ����applicationButton
 * @return Ĭ�ϵ�applicationButton��@ref SARibbonApplicationButton ���ɣ�ͨ��@ref setApplicationButton ������Ϊ����button
 */
QAbstractButton* SARibbonBar::applicationButton()
{
    return (d_ptr->mApplicationButton);
}

/**
 * @brief ����applicationButton,��������أ����Դ���nullptr
 *
 * Ĭ�ϻ���һ��SARibbonApplicationButton�������ȡ�����ɴ���nullptr�������Զ����buttonҲ���Դ���
 *
 * @note applicationButton������Ȩ��SARibbonBar���У���Ҫ���ⲿ��applicationButton����delete����
 * @param btn applicationButtonָ�룬���Դ���@ref SARibbonApplicationButton��
 * SA�Ѿ���SARibbonApplicationButton��������ʽ����
 */
void SARibbonBar::setApplicationButton(QAbstractButton* btn)
{
    d_ptr->setApplicationButton(btn);
    if (btn) {
        if (btn->objectName().isEmpty()) {
            btn->setObjectName(QStringLiteral("SARibbonApplicationButton"));
        }
        btn->setVisible(true);
        // btn->setGeometry(applicationButtonGeometry());
    }
    //��������Ϊʲô������resize
    QApplication::postEvent(this, new QResizeEvent(size(), size()));
}

/**
 * @brief ����tabbar
 * @return SARibbonTabBarָ��
 * @sa SARibbonTabBar
 */
SARibbonTabBar* SARibbonBar::ribbonTabBar()
{
    return (d_ptr->mRibbonTabBar);
}

/**
 * @brief ���һ����ǩ
 * �����Ҫɾ����ֱ��delete���ɣ�SARibbonBar�������д���
 * @param title ��ǩ���֣�Ĭ�������SARibbonCategory��object nameҲ������Ϊtitle
 * @return ����һ��������������Category�������������ؼ�
 * @sa SARibbonCategory
 */
SARibbonCategory* SARibbonBar::addCategoryPage(const QString& title)
{
    SARibbonCategory* category = RibbonSubElementDelegate->createRibbonCategory(this);

    // catagory->setFixedHeight(categoryHeight());
    category->setObjectName(title);
    category->setCategoryName(title);
    addCategoryPage(category);
    return (category);
}

/**
 * @brief ���һ����ǩ
 * @param category
 */
void SARibbonBar::addCategoryPage(SARibbonCategory* category)
{
    if (nullptr == category) {
        return;
    }
    int index = d_ptr->mRibbonTabBar->addTab(category->categoryName());

    category->setRibbonPannelLayoutMode(isTwoRowStyle() ? SARibbonPannel::TwoRowMode : SARibbonPannel::ThreeRowMode);

    _SARibbonTabData tabdata;

    tabdata.category = category;
    tabdata.index    = index;
    category->setRibbonBar(this);
    d_ptr->mRibbonTabBar->setTabData(index, QVariant::fromValue(tabdata));

    d_ptr->mStackedContainerWidget->insertWidget(index, category);
    connect(category, &QWidget::windowTitleChanged, this, &SARibbonBar::onCategoryWindowTitleChanged);
    QApplication::postEvent(this, new QResizeEvent(size(), size()));
}

/**
 * @brief qtdesignerר��
 * @param category
 */
void SARibbonBar::addCategoryPage(QWidget* category)
{
    SARibbonCategory* c = qobject_cast< SARibbonCategory* >(category);

    if (c) {
        addCategoryPage(c);
    }
}

/**
 * @brief ���һ��category��category��λ����index�������ǰcategory��������index�������뵽���
 * @param title category�ı���
 * @param index category��λ��
 * @return
 */
SARibbonCategory* SARibbonBar::insertCategoryPage(const QString& title, int index)
{
    SARibbonCategory* category = RibbonSubElementDelegate->createRibbonCategory(this);

    category->setObjectName(title);
    category->setCategoryName(title);
    insertCategoryPage(category, index);
    return (category);
}

void SARibbonBar::insertCategoryPage(SARibbonCategory* category, int index)
{
    if (nullptr == category) {
        return;
    }
    category->setRibbonPannelLayoutMode(isTwoRowStyle() ? SARibbonPannel::TwoRowMode : SARibbonPannel::ThreeRowMode);
    int i = d_ptr->mRibbonTabBar->insertTab(index, category->categoryName());

    _SARibbonTabData tabdata;

    tabdata.category = category;
    tabdata.index    = i;
    d_ptr->mRibbonTabBar->setTabData(i, QVariant::fromValue(tabdata));
    d_ptr->mStackedContainerWidget->insertWidget(index, category);

    connect(category, &QWidget::windowTitleChanged, this, &SARibbonBar::onCategoryWindowTitleChanged);
    //����index��Ϣ
    d_ptr->updateTabData();
    QApplication::postEvent(this, new QResizeEvent(size(), size()));
}

/**
 * @brief ͨ�����ֲ���Category
 * @param title Category�����֣��ȱ�ǩ�ı���
 * @return ���û���ҵ���������nullptr������������������ص�һ����ѯ�������֣���ˣ���������������ǩ
 * @note ���ڷ����ԭ�򣬿���title��仯����������ͨ���̶����ݲ���category��Ӧ��ʹ�� @ref categoryByObjectName
 * @see categoryByObjectName
 */
SARibbonCategory* SARibbonBar::categoryByName(const QString& title) const
{
    int c = d_ptr->mStackedContainerWidget->count();

    for (int i = 0; i < c; ++i) {
        SARibbonCategory* w = qobject_cast< SARibbonCategory* >(d_ptr->mStackedContainerWidget->widget(i));
        if (w) {
            if (w->categoryName() == title) {
                return (w);
            }
        }
    }
    return (nullptr);
}

/**
 * @brief ͨ��ObjectName����Category
 * @param objname
 * @return ���û���ҵ���������nullptr�������ͬ����ObjectName�������ص�һ����ѯ�������֣���ˣ���������ObjectName����
 * @see categoryByName
 */
SARibbonCategory* SARibbonBar::categoryByObjectName(const QString& objname) const
{
    int c = d_ptr->mStackedContainerWidget->count();

    for (int i = 0; i < c; ++i) {
        SARibbonCategory* w = qobject_cast< SARibbonCategory* >(d_ptr->mStackedContainerWidget->widget(i));
        if (w) {
            if (w->objectName() == objname) {
                return (w);
            }
        }
    }
    return (nullptr);
}

/**
 * @brief ͨ�������ҵ�category���������������Χ���᷵��nullptr
 * @param index ����
 * @return �������������Χ���᷵��nullptr
 * @note �����ʱ�������ı�ǩ�������ĵı�ǩҲ�᷵��
 * @note ͨ���������ҵ�category������visible״̬��category�����ͨ��@ref hideCategory ���صı�ǩ��ͨ���������Ҳ�����
 * @note ͨ��@ref categoryByObjectName �����ҵ����м�����ı�ǩ��
 * �����õ�ribbonbar��������б�ǩ������ͨ������@ref categoryPages �õ�
 * @see categoryIndex categoryByObjectName categoryByName
 */
SARibbonCategory* SARibbonBar::categoryByIndex(int index) const
{
    QVariant var = d_ptr->mRibbonTabBar->tabData(index);

    if (var.isValid()) {
        _SARibbonTabData p = var.value< _SARibbonTabData >();
        return (p.category);
    }
    return (nullptr);
}

/**
 * @brief ����category,������ɾ������ȡ�ߣ�ֻ������
 * @param category
 */
void SARibbonBar::hideCategory(SARibbonCategory* category)
{
    int tabcount = d_ptr->mRibbonTabBar->count();

    for (int i = 0; i < tabcount; ++i) {
        QVariant var = d_ptr->mRibbonTabBar->tabData(i);
        if (var.isValid()) {
            _SARibbonTabData p = var.value< _SARibbonTabData >();
            if (p.category == category) {
                d_ptr->mHidedCategory.append(p);
                d_ptr->mRibbonTabBar->removeTab(i);  //������tab�Ƴ�
                //ע��Category���غ�contex��λ�þͻᷢ���仯����Ҫ����
                d_ptr->updateTabData();
                return;
            }
        }
    }
}

/**
 * @brief ��ʾ�����ص�category
 * @param category
 */
void SARibbonBar::showCategory(SARibbonCategory* category)
{
    for (auto i = d_ptr->mHidedCategory.begin(); i != d_ptr->mHidedCategory.end(); ++i) {
        if (i->category == category) {
            //˵��Ҫ��ʾ
            int index = d_ptr->mRibbonTabBar->insertTab(i->index, i->category->categoryName());
            i->index  = index;
            d_ptr->mRibbonTabBar->setTabData(index, QVariant::fromValue(*i));
            d_ptr->mHidedCategory.erase(i);  //�Ƴ�
            //����index��Ϣ
            d_ptr->updateTabData();
            raiseCategory(category);
            return;
        }
    }
    raiseCategory(category);
}

/**
 * @brief �ж����category�Ƿ�����ʾ״̬��Ҳ����tabbar�����category
 * @param category
 * @return
 */
bool SARibbonBar::isCategoryVisible(const SARibbonCategory* c) const
{
    int tabindex = categoryIndex(c);

    return (tabindex >= 0);
}

/**
 * @brief ��ȡcategory������
 * @param c
 * @return ����Ҳ���������-1
 */
int SARibbonBar::categoryIndex(const SARibbonCategory* c) const
{
    int tabcount = d_ptr->mRibbonTabBar->count();

    for (int i = 0; i < tabcount; ++i) {
        QVariant var = d_ptr->mRibbonTabBar->tabData(i);
        if (var.isValid()) {
            _SARibbonTabData p = var.value< _SARibbonTabData >();
            if (p.category == c) {
                return (i);
            }
        }
    }
    return (-1);
}

/**
 * @brief �ƶ�һ��Category��from index��to index
 * @param from
 * @param to
 */
void SARibbonBar::moveCategory(int from, int to)
{
    d_ptr->mRibbonTabBar->moveTab(from, to);
    //��ʱҪˢ������tabdata��index��Ϣ
    d_ptr->updateTabData();
    //����ᴥ��tabMoved�źţ���tabMoved�ź��е���stacked�ﴰ�ڵ�λ��
}

/**
 * @brief ��ȡ��ǰ��ʾ�����е�SARibbonCategory������δ��ʾ��SARibbonContextCategory��SARibbonCategoryҲһ������
 *
 * @return
 */
QList< SARibbonCategory* > SARibbonBar::categoryPages(bool getAll) const
{
    int c = d_ptr->mStackedContainerWidget->count();
    QList< SARibbonCategory* > res;

    for (int i = 0; i < c; ++i) {
        SARibbonCategory* w = qobject_cast< SARibbonCategory* >(d_ptr->mStackedContainerWidget->widget(i));
        if (w) {
            if (!getAll && w->isContextCategory()) {
                //����getall����������ʱ����
                continue;
            }
            res.append(w);
        }
    }
    return (res);
}

/**
 * @brief �Ƴ�SARibbonCategory
 *
 * SARibbonBar����delete SARibbonCategory*�������SARibbonCategory������SARibbonBar�Ĺ���
 * ������tabbar���Ƴ��������Ƴ���ʹ�ô˺�������Զ�SARibbonCategory����delete
 * @param category
 */
void SARibbonBar::removeCategory(SARibbonCategory* category)
{
    int index     = tabIndex(category);
    bool isupdate = false;
    if (index >= 0) {
        d_ptr->mRibbonTabBar->removeTab(index);
        isupdate = true;
    }
    d_ptr->mStackedContainerWidget->removeWidget(category);
    //ͬʱ��֤���category�Ƿ���contexcategory���

    for (SARibbonContextCategory* c : qAsConst(d_ptr->mContextCategoryList)) {
        c->takeCategory(category);
    }
    //��ʱҪˢ������tabdata��index��Ϣ
    if (isupdate) {
        d_ptr->updateTabData();
    }
    //�Ƴ������Ҫ�ػ�
    repaint();
    QApplication::postEvent(this, new QResizeEvent(size(), size()));
}

/**
 * @brief ��������ı�ǩ
 *
 * �����ı�ǩ������ʱ�򴥷��ı�ǩ����Ҫ�û��ֶ�����
 *
 * ����@ref SARibbonContextCategory::addCategoryPage ���������ı�ǩ�����SARibbonCategory��
 * �������ı�ǩ��ӵ�SARibbonCategory��ֻ���������ı�ǩ��ʾ��ʱ��Ż���ʾ
 * @param title �����ı�ǩ�ı��⣬��Officeģʽ�»���ʾ����wpsģʽ�²���ʾ��Ĭ�������SARibbonContextCategory��object nameҲ������Ϊtitle
 * @param color �����ı�ǩ����ɫ�����ָ��Ϊ��QColor(),����ʹ��SARibbonBar��Ĭ��ɫϵ
 * @param id �����ı�ǩ��id���Ա���в���
 * @return ���������ı�ǩָ��
 * @note SARibbonBarӵ��SARibbonContextCategory�Ĺ���Ȩ���û��������ⲿֱ��delete,���Ҫɾ��������@ref destroyContextCategory ����
 */
SARibbonContextCategory* SARibbonBar::addContextCategory(const QString& title, const QColor& color, const QVariant& id)
{
    SARibbonContextCategory* context = RibbonSubElementDelegate->createRibbonContextCategory(this);

    context->setObjectName(title);
    context->setContextTitle(title);
    context->setId(id);
    context->setContextColor(color.isValid() ? color : d_ptr->getContextCategoryColor());
    addContextCategory(context);
    return (context);
}

/**
 * @brief ��������ı�ǩ
 * @param context
 */
void SARibbonBar::addContextCategory(SARibbonContextCategory* context)
{
    if (nullptr == context) {
        return;
    }
    connect(context, &SARibbonContextCategory::categoryPageAdded, this, &SARibbonBar::onContextsCategoryPageAdded);
    connect(context, &SARibbonContextCategory::categoryTitleChanged, this, &SARibbonBar::onContextsCategoryCategoryNameChanged);
    // remove��û�а󶨣���Ҫ��remove����stacked��Ҳ������ʾ��remove��delete�Ļ���stacked��Ҳ��ɾ��
    if (currentRibbonStyle() == WpsLiteStyle) {
        resizeInWpsLiteStyle();
    }
    d_ptr->mContextCategoryList.append(context);
}

/**
 * @brief ��ʾ�����ı�ǩ
 * @param context �����ı�ǩָ��
 */
void SARibbonBar::showContextCategory(SARibbonContextCategory* context)
{
    if (isContextCategoryVisible(context)) {
        return;
    }
    _SAContextCategoryManagerData contextCategoryData;

    contextCategoryData.contextCategory = context;
    for (int i = 0; i < context->categoryCount(); ++i) {
        SARibbonCategory* category = context->categoryPage(i);
        //�˾����ģʽ�ظ����ò�����ж������
        category->setRibbonPannelLayoutMode(isTwoRowStyle() ? SARibbonPannel::TwoRowMode : SARibbonPannel::ThreeRowMode);
        //�л�ģʽ���ı�߶ȣ������ı�ǩ��ʾʱҪ��֤��ʾ����
        // category->setFixedHeight(categoryHeight());
        int index = d_ptr->mRibbonTabBar->addTab(category->categoryName());
        contextCategoryData.tabPageIndex.append(index);

        _SARibbonTabData tabdata;
        tabdata.category = category;
        tabdata.index    = index;
        d_ptr->mRibbonTabBar->setTabData(index, QVariant::fromValue(tabdata));
    }
    d_ptr->mCurrentShowingContextCategory.append(contextCategoryData);
    //���������Ķ��������׷�ӣ�����Ҫ����updateTabData();
    QApplication::postEvent(this, new QResizeEvent(size(), size()));
}

/**
 * @brief ���������ı�ǩ
 * @param context �����ı�ǩָ��
 */
void SARibbonBar::hideContextCategory(SARibbonContextCategory* context)
{
    bool needResize = false;
    int indexOffset = 0;

    for (int i = 0; i < d_ptr->mCurrentShowingContextCategory.size(); ++i) {
        if (d_ptr->mCurrentShowingContextCategory[ i ].contextCategory == context) {
            const QList< int >& indexs = d_ptr->mCurrentShowingContextCategory[ i ].tabPageIndex;
            for (int j = indexs.size() - 1; j >= 0; --j) {
                d_ptr->mRibbonTabBar->removeTab(indexs[ j ]);
                ++indexOffset;
            }
            //ע�⣬��ɾ��ContextCategory��tab����žͻ�ı䣬��ʱ�����tab����Ķ�Ҫ�����������
            needResize = true;
            d_ptr->mCurrentShowingContextCategory.removeAt(i);
            //�Ƴ���ContextCategory����Ҫbreak
            break;
        }
    }
    if (needResize) {
        d_ptr->updateTabData();
        QApplication::postEvent(this, new QResizeEvent(size(), size()));
    }
}

/**
 * @brief �ж��������Ƿ�����ʾ״̬
 * @param context
 * @return ����ʾ״̬����true
 * @sa setContextCategoryVisible
 */
bool SARibbonBar::isContextCategoryVisible(SARibbonContextCategory* context)
{
    return (d_ptr->isContainContextCategoryInList(context));
}

/**
 * @brief ���������ı�ǩ����ʾ״̬
 *
 * �����ı�ǩ�ĵ�ǰ��ʾ״̬��ͨ�� @ref isContextCategoryVisible �����ж�
 * @param context �����ı�ǩ
 * @param visible ��ʾ״̬��trueΪ��ʾ
 */
void SARibbonBar::setContextCategoryVisible(SARibbonContextCategory* context, bool visible)
{
    if (nullptr == context) {
        return;
    }
    if (visible) {
        showContextCategory(context);
    } else {
        hideContextCategory(context);
    }
}

/**
 * @brief ��ȡ���е������ı�ǩ
 * @return ���������ı�ǩ�б�
 */
QList< SARibbonContextCategory* > SARibbonBar::contextCategoryList() const
{
    return (d_ptr->mContextCategoryList);
}

/**
 * @brief ���������ı�ǩ�������ı�ǩ��SARibbonCategoryҲ����֮����
 * @param context ��Ҫ���ٵ������ı�ǩָ��
 */
void SARibbonBar::destroyContextCategory(SARibbonContextCategory* context)
{
    if (nullptr == context) {
        return;
    }
    //! 1����������ı�ǩ��ʾ�У�������
    if (isContextCategoryVisible(context)) {
        hideContextCategory(context);
    }
    //! 2��ɾ�������ı�ǩ���������
    d_ptr->mContextCategoryList.removeAll(context);
    //!
    QList< SARibbonCategory* > res = context->categoryList();

    for (SARibbonCategory* c : qAsConst(res)) {
        c->hide();
        c->deleteLater();
    }
    context->deleteLater();
    QApplication::postEvent(this, new QResizeEvent(size(), size()));
}

/**
 * @brief ����Ϊ��С/����ģʽ
 *
 * ����ģʽ�£�ֻ����ʾtabbar��������ʾ���ݣ�Ĭ��״̬����ʾģʽ
 *
 * Ĭ����˫��tabbar���л�������ʾģʽ���������ô˹��ܣ��������� @ref onCurrentRibbonTabDoubleClicked
 * ���������Ժ��������κδ�����
 *
 * @param isMinimum ����Ϊtrueʱ���л�ΪMinimumģʽ
 * @see �˺�����ı�@ref RibbonState ״̬��ͨ��@ref currentRibbonState �������Բ鿴��ǰ״̬
 */
void SARibbonBar::setMinimumMode(bool isMinimum)
{
#ifdef SA_RIBBON_DEBUG_HELP_DRAW
    qDebug() << "SARibbonBar::setHideMode " << isMinimum;
#endif
    if (isMinimum) {
        d_ptr->setHideMode();
    } else {
        d_ptr->setNormalMode();
    }
    QResizeEvent resizeEvent(size(), size());
    QApplication::sendEvent(this, &resizeEvent);
    //�����ź�
    emit ribbonModeChanged(isMinimum ? MinimumRibbonMode : NormalRibbonMode);
}

///
/// \brief ��ǰribbon�Ƿ�������ģʽ
/// \return
///
bool SARibbonBar::isMinimumMode() const
{
    return (d_ptr->mStackedContainerWidget->isPopupMode());
}

///
/// \brief ������ʾ����ribbon��ť
///
void SARibbonBar::showMinimumModeButton(bool isShow)
{
    if (isShow) {
        activeRightButtonGroup();
        if (nullptr == d_ptr->mMinimumCategoryButton) {
            d_ptr->mMinimumCategoryButton = RibbonSubElementDelegate->createHidePannelButton(this);
            d_ptr->mMinimumCategoryButton->ensurePolished();  // ������ʽͼ��
            QAction* action = new QAction(d_ptr->mMinimumCategoryButton);
            action->setIcon(style()->standardIcon(isMinimumMode() ? QStyle::SP_TitleBarUnshadeButton : QStyle::SP_TitleBarShadeButton,
                                                  0,
                                                  d_ptr->mMinimumCategoryButton));
            connect(action, &QAction::triggered, this, [ = ]() {
                this->setMinimumMode(!isMinimumMode());
                action->setIcon(style()->standardIcon(isMinimumMode() ? QStyle::SP_TitleBarUnshadeButton : QStyle::SP_TitleBarShadeButton,
                                                      0,
                                                      d_ptr->mMinimumCategoryButton));
            });
            d_ptr->mMinimumCategoryButton->setDefaultAction(action);
            d_ptr->mRightButtonGroup->addWidget(d_ptr->mMinimumCategoryButton);
            update();
        }
    } else {
        if (nullptr != d_ptr->mMinimumCategoryButton) {
            d_ptr->mMinimumCategoryButton->hide();
            d_ptr->mMinimumCategoryButton->deleteLater();
            d_ptr->mMinimumCategoryButton = nullptr;
        }
    }
    QResizeEvent resizeEvent(size(), size());

    QApplication::sendEvent(this, &resizeEvent);
}

///
/// \brief �Ƿ���ʾ����ribbon��ť
/// \return
///
bool SARibbonBar::haveShowMinimumModeButton() const
{
    return (nullptr != d_ptr->mMinimumCategoryButton);
}

int SARibbonBar::tabBarHeight() const
{
    return (RibbonSubElementStyleOpt.tabBarHeight());
}

int SARibbonBar::titleBarHeight() const
{
    return (RibbonSubElementStyleOpt.titleBarHeight());
}

void SARibbonBar::onWindowTitleChanged(const QString& title)
{
    Q_UNUSED(title);
    update();
}

void SARibbonBar::onWindowIconChanged(const QIcon& i)
{
    if (quickAccessBar()) {
        quickAccessBar()->setIcon(i);
    }
}

/**
 * @brief category�����ַ����ı䴥��
 * @param title
 */
void SARibbonBar::onCategoryWindowTitleChanged(const QString& title)
{
    //ȫ������һ��
    Q_UNUSED(title);
    updateCategoryTitleToTabName();
    /*
    SARibbonCategory* w = qobject_cast< SARibbonCategory* >(sender());

    if (nullptr == w) {
            return;
    }
    for (int i = 0; i < d_ptr->mRibbonTabBar->count(); ++i) {
            //����tab����ܶ࣬������Ч������
            QVariant var = d_ptr->mRibbonTabBar->tabData(i);
            if (var.isValid()) {
                    _SARibbonTabData p = var.value< _SARibbonTabData >();
                    if (w == p.category) {
                            d_ptr->mRibbonTabBar->setTabText(i, title);
                    }
            }
    }
    */
}

///
/// \brief ribbon����ʾ��������
///
void SARibbonBar::onStackWidgetHided()
{
    // m_d->ribbonTabBar->repaint();
}

/**
 * @brief ��ǩ�л������ۺ���
 * @param index
 */
void SARibbonBar::onCurrentRibbonTabChanged(int index)
{
    QVariant var               = d_ptr->mRibbonTabBar->tabData(index);
    SARibbonCategory* category = nullptr;

    if (var.isValid()) {
        _SARibbonTabData p = var.value< _SARibbonTabData >();
        category           = p.category;
    }
    if (category) {
        if (d_ptr->mStackedContainerWidget->currentWidget() != category) {
            d_ptr->mStackedContainerWidget->setCurrentWidget(category);
        }
        if (isMinimumMode()) {
            d_ptr->mRibbonTabBar->clearFocus();
            if (!d_ptr->mStackedContainerWidget->isVisible()) {
                if (d_ptr->mStackedContainerWidget->isPopupMode()) {
                    //��stackedContainerWidget����ǰ���ȸ�tabbarһ��QHoverEvent,��tabbar֪������Ѿ��ƿ�
                    QHoverEvent ehl(QEvent::HoverLeave,
                                    d_ptr->mRibbonTabBar->mapToGlobal(QCursor::pos()),
                                    d_ptr->mRibbonTabBar->mapToGlobal(QCursor::pos()));
                    QApplication::sendEvent(d_ptr->mRibbonTabBar, &ehl);
                    resizeStackedContainerWidget();
                    d_ptr->mStackedContainerWidget->setFocus();
                    d_ptr->mStackedContainerWidget->exec();
                    //����Сģʽ�£�ÿ����ʾ��stackedContainerWidget���tab��
                    //��index����Ϊ-1������ÿ�ε�����ᴥ��onCurrentRibbonTabChanged
                }
            } else {
            }
        }
    }
    emit currentRibbonTabChanged(index);
}

/**
 * @brief ribbon tab bar����
 *
 * ��ʵ�ֱ�����eventfilter�д���stackedwidget��QEvent::MouseButtonDblClick�¼���tabbar�У�����ᵼ��˫�������ε���
 *
 * �����¼���������Ӧ���ͬһ��tabʱ
 * @param index
 */
void SARibbonBar::onCurrentRibbonTabClicked(int index)
{
    if (index != d_ptr->mRibbonTabBar->currentIndex()) {
        //����ı�ǩ��һ��ͨ��changed��ȥ����
        return;
    }
    if (this->isMinimumMode()) {
        if (!this->d_ptr->mStackedContainerWidget->isVisible()) {
            if (this->d_ptr->mStackedContainerWidget->isPopupMode()) {
                //��stackedContainerWidget����ǰ���ȸ�tabbarһ��QHoverEvent,��tabbar֪������Ѿ��ƿ�
                QHoverEvent ehl(QEvent::HoverLeave,
                                d_ptr->mRibbonTabBar->mapToGlobal(QCursor::pos()),
                                d_ptr->mRibbonTabBar->mapToGlobal(QCursor::pos()));
                QApplication::sendEvent(d_ptr->mRibbonTabBar, &ehl);
                //����ǰ������һ��λ�ã������ƶ���λ���쳣
                resizeStackedContainerWidget();
                this->d_ptr->mStackedContainerWidget->setFocus();
                this->d_ptr->mStackedContainerWidget->exec();
            }
        }
    }
}

/**
 * @brief ribbon tab bar˫��
 *
 * Ĭ�������˫�����л���С������ģʽ
 * @param index
 */
void SARibbonBar::onCurrentRibbonTabDoubleClicked(int index)
{
    Q_UNUSED(index);
    setMinimumMode(!isMinimumMode());
}

void SARibbonBar::onContextsCategoryPageAdded(SARibbonCategory* category)
{
    Q_ASSERT_X(category != nullptr, "onContextsCategoryPageAdded", "add nullptr page");
    d_ptr->mStackedContainerWidget->addWidget(category);  //����stackedWidget��append�������ط���Ӧ��ʹ��insert
}

/**
 * @brief �����ı�ǩ����ı�ǩ�����ַ����任
 * @param category
 * @param title
 */
void SARibbonBar::onContextsCategoryCategoryNameChanged(SARibbonCategory* category, const QString& title)
{
    Q_UNUSED(category);
    Q_UNUSED(title);
    updateCategoryTitleToTabName();
}

/**
 * @brief ��ǩ�ƶ����ź�
 * @param from
 * @param to
 */
void SARibbonBar::onTabMoved(int from, int to)
{
    //����stacked widget��˳�򣬵���˳����Ϊ�˵���categoryPages�������ص�QList<SARibbonCategory *>˳���tabbarһ��
    d_ptr->mStackedContainerWidget->moveWidget(from, to);
}

/**
 * @brief ����SARibbonCategory*ָ�����tabbar��index
 *
 * @param c SARibbonCategory��Ӧ��QObjectָ��
 * @return ���û���ҵ�������-1
 * @note �˺����������SARibbonCategory*���κη�������˿�����SARibbonCategory��destroyed���е���
 */
int SARibbonBar::tabIndex(SARibbonCategory* obj)
{
    const int size = d_ptr->mRibbonTabBar->count();

    for (int i = 0; i < size; ++i) {
        QVariant v = d_ptr->mRibbonTabBar->tabData(i);
        if (v.isValid()) {
            _SARibbonTabData innervalue = v.value< _SARibbonTabData >();
            if (innervalue.category == obj) {
                return (i);
            }
        }
    }
    //����Ҳ����ʹ�stackedwidget����

    return (-1);
}

void SARibbonBar::updateRibbonElementGeometry()
{
    //������ʽ����SARibbonCategory�Ĳ�����ʽ
    QList< SARibbonCategory* > categorys = categoryPages();

    for (SARibbonCategory* c : qAsConst(categorys)) {
        c->setRibbonPannelLayoutMode(SARibbonBar::isTwoRowStyle(currentRibbonStyle()) ? SARibbonPannel::TwoRowMode
                                                                                      : SARibbonPannel::ThreeRowMode);
    }

    //������ʽ����bar�ĸ߶�
    if (NormalRibbonMode == currentRibbonState()) {
        setFixedHeight(mainBarHeight());
    }
    //    //��Сģʽʱ��bar�ĸ߶���resize֮�����
    //    else if(MinimumRibbonMode == currentRibbonState()){
    //        //������Сģʽ��ʱ��bar�ĸ߶�Ϊtabbar��bottom
    //        setFixedHeight(m_d->ribbonTabBar->geometry().bottom());
    //    }
}

void SARibbonBar::activeRightButtonGroup()
{
    if (nullptr == d_ptr->mRightButtonGroup) {
        d_ptr->mRightButtonGroup = RibbonSubElementDelegate->craeteButtonGroupWidget(this);
        d_ptr->mRightButtonGroup->setFrameShape(QFrame::NoFrame);
    }
    d_ptr->mRightButtonGroup->show();
}

SARibbonButtonGroupWidget* SARibbonBar::rightButtonGroup()
{
    activeRightButtonGroup();
    return (d_ptr->mRightButtonGroup);
}

SARibbonQuickAccessBar* SARibbonBar::quickAccessBar()
{
    return (d_ptr->mQuickAccessBar);
}

/**
 * @brief ����ribbonbar�ķ�񣬴˺�����������������Ԫ�أ�����button�Ĳ��ַ�ʽ��
 * �����Ǵ����б䵽���еĹ��̣���������ݽ϶�
 * @note �˺������Զ�����ResizeEvent������Ҫ�ֶ�����
 * @note Ĭ�������2��ģʽ������,�����������ģʽ���У��ڵ���SARibbonBar::setRibbonStyle����SARibbonToolButton::setEnableWordWrap(true)
 * ,ͬʱ�ٵ���updateRibbonElementGeometry()ˢ�²���
 * @param v ��ʽ����@ref SARibbonBar::RibbonStyle
 */
void SARibbonBar::setRibbonStyle(SARibbonBar::RibbonStyle v)
{
    d_ptr->mRibbonStyle   = v;
    d_ptr->mLastShowStyle = v;
    d_ptr->mQuickAccessBar->setEnableShowIcon(isOfficeStyle(v));
    //Ĭ�������2��ģʽ������
    //�����������ģʽ���У��ڵ���SARibbonBar::setRibbonStyle����SARibbonToolButton::setEnableWordWrap(true)
    SARibbonToolButton::setEnableWordWrap(!isTwoRowStyle(v));

    updateRibbonElementGeometry();
    QSize oldSize = size();
    QSize newSize(oldSize.width(), mainBarHeight());
    QResizeEvent es(newSize, oldSize);

    QApplication::sendEvent(this, &es);
    if (MinimumRibbonMode == currentRibbonState()) {
        //������Сģʽ��ʱ��bar�ĸ߶�Ϊtabbar��bottom,�������������resize event֮��
        setFixedHeight(d_ptr->mRibbonTabBar->geometry().bottom());
    }
    emit ribbonStyleChanged(d_ptr->mRibbonStyle);
}

/**
 * @brief ���ص�ǰribbon�ķ��
 * @return ���ص�ǰribbon�ķ��
 */
SARibbonBar::RibbonStyle SARibbonBar::currentRibbonStyle() const
{
    return (d_ptr->mRibbonStyle);
}

SARibbonBar::RibbonMode SARibbonBar::currentRibbonState() const
{
    return (d_ptr->mCurrentRibbonMode);
}

///
/// \brief �л�����Ӧ��ǩ
/// \param index ��ǩ����
///
void SARibbonBar::setCurrentIndex(int index)
{
    d_ptr->mRibbonTabBar->setCurrentIndex(index);
    // onCurrentRibbonTabChanged(index);
}

/**
 * @brief ���ص�ǰ��tab����
 * @return ��ǰ������
 */
int SARibbonBar::currentIndex()
{
    return (d_ptr->mRibbonTabBar->currentIndex());
}

///
/// \brief ȷ����ǩ��ʾ������tab���л�����Ӧҳ
/// \param category ��ǩָ��
///
void SARibbonBar::raiseCategory(SARibbonCategory* category)
{
    int index = d_ptr->mStackedContainerWidget->indexOf(category);

    if (index >= 0) {
        setCurrentIndex(index);
    }
}

/**
 * @brief �жϵ�ǰ����ʽ�Ƿ�Ϊ����
 * @return
 */
bool SARibbonBar::isTwoRowStyle() const
{
    return (SARibbonBar::isTwoRowStyle(d_ptr->mRibbonStyle));
}

/**
 * @brief �жϵ�ǰ����ʽ�Ƿ�Ϊoffice��ʽ
 * @return
 */
bool SARibbonBar::isOfficeStyle() const
{
    return (SARibbonBar::isOfficeStyle(currentRibbonStyle()));
}

/**
 * @brief ����saribbonbar��window button�ĳߴ�,��ֵ��SARibbonMainWindow���룬
 * ���������С���رհ�ť�Ĵ�С������ʾ��������ʱ��ü���ߴ�
 * @param size
 */
void SARibbonBar::setWindowButtonSize(const QSize& size)
{
    d_ptr->mWindowButtonSize = size;
}

/**
 * @brief ���ñ����������ɫ
 *
 * ����ʱmainwindow��windowTitle�����Ҫ���ñ��⣬ֱ�ӵ���SARibbonMainWindow::setWindowTitle ��������
 * @param clr
 * @note �˺�������ˢ�£�ˢ�������е���repaint
 */
void SARibbonBar::setWindowTitleTextColor(const QColor& clr)
{
    d_ptr->mTitleTextColor = clr;
}

/**
 * @brief ��ȡ�����������ɫ
 * @return
 */
QColor SARibbonBar::windowTitleTextColor() const
{
    return d_ptr->mTitleTextColor;
}

/**
 * @brief tabbar �ײ������һ���������˽ӿڶ���������ɫ
 * @param clr
 */
void SARibbonBar::setTabBarBaseLineColor(const QColor& clr)
{
    d_ptr->mTabBarBaseLineColor = clr;
}

/**
 * @brief ��ȡtabbar�ײ�������ɫ
 * @return
 */
QColor SARibbonBar::tabBarBaseLineColor() const
{
    return d_ptr->mTabBarBaseLineColor;
}

/**
 * @brief ����ribbon�Ĳ������ݣ��˺���������һЩ�ؼ��Գߴ�仯������ribbon����Ԫ�صĲ���
 *
 * @note �˺������ý����������ڸ���Ҫ�󳡺ϵ���
 */
void SARibbonBar::updateRibbonGeometry()
{
    updateRibbonElementGeometry();
    QList< SARibbonCategory* > categorys = categoryPages();
    for (SARibbonCategory* c : qAsConst(categorys)) {
        c->updateItemGeometry();
    }
}

/**
 * @brief ���ñ���Ķ��뷽ʽ
 * @param al
 */
void SARibbonBar::setWindowTitleAligment(Qt::Alignment al)
{
    d_ptr->mTitleAligment = al;
}

/**
 * @brief ��ȡ����Ķ��뷽ʽ
 * @return
 */
Qt::Alignment SARibbonBar::windowTitleAligment() const
{
    return d_ptr->mTitleAligment;
}

/**
 * @brief ����ribbonbar�İ�ť����������
 * @param on
 */
void SARibbonBar::setEnableWordWrap(bool on)
{
    SARibbonToolButton::setEnableWordWrap(on);
    updateRibbonGeometry();
}

/**
 * @brief �ж��Ƿ�������
 * @return
 */
bool SARibbonBar::isEnableWordWrap() const
{
    return SARibbonToolButton::isEnableWordWrap();
}

bool SARibbonBar::eventFilter(QObject* obj, QEvent* e)
{
    if (obj) {
        //�������ĵ�ʱ�ڴ���ģʽ�µİ�ť����
        if ((obj == cornerWidget(Qt::TopLeftCorner)) || (obj == cornerWidget(Qt::TopRightCorner))) {
            if ((QEvent::UpdateLater == e->type()) || (QEvent::MouseButtonRelease == e->type())
                || (QEvent::WindowActivate == e->type())) {
                QApplication::postEvent(this, new QResizeEvent(size(), size()));
            }
        } else if (obj == d_ptr->mStackedContainerWidget) {
            //��stack ��popupģʽʱ���������stackedContainerWidget�������ʱ���������ribbonTabBar�ϵ��
            //��ô���Ե���ε�����ѵ���·���ribbonTabBar,�������Ա���stackedContainerWidget�ڵ��ribbonTabBar��
            //��������ʾ��������˸
            if ((QEvent::MouseButtonPress == e->type()) || (QEvent::MouseButtonDblClick == e->type())) {
                if (d_ptr->mStackedContainerWidget->isPopupMode()) {
                    QMouseEvent* mouseEvent = static_cast< QMouseEvent* >(e);
                    if (!d_ptr->mStackedContainerWidget->rect().contains(mouseEvent->pos())) {
                        QWidget* clickedWidget = QApplication::widgetAt(mouseEvent->globalPos());
                        if (clickedWidget == d_ptr->mRibbonTabBar) {
                            const QPoint targetPoint = clickedWidget->mapFromGlobal(mouseEvent->globalPos());
                            QMouseEvent* evPress     = new QMouseEvent(mouseEvent->type(),
                                                                   targetPoint,
                                                                   mouseEvent->globalPos(),
                                                                   mouseEvent->button(),
                                                                   mouseEvent->buttons(),
                                                                   mouseEvent->modifiers());
                            QApplication::postEvent(clickedWidget, evPress);
                            return (true);
                        }
                    }
                }
            }
        }
        //        if (SAWindowButtonGroup *g = qobject_cast<SAWindowButtonGroup *>(obj)) {
        //            if (e->type() == QEvent::Resize) {
        //                m_d->windowButtonSize = g->size();
        //            }
        //        }
    }
    return (QMenuBar::eventFilter(obj, e));
}

/**
 * @brief �����������tabbar�Ŀ�ȣ���Ҫ���wpsģʽ
 */
int SARibbonBar::calcMinTabBarWidth() const
{
    // 20200831
    // tabBarWidth�Ŀ��ԭ��ΪendX - x;������Ҫ����ʵ�ʽ��е���
    //Ϊ�˰�tabbarû��tab�Ĳ��ֲ�ռ�ã�����Ŀ����Ҫ����tab��size���������ã���tabbar�ĳ��ȸոպã��������ó�
    // mainwindow�Ŀռ䣬��������¼����Ӷ�ʵ���϶��Ȳ���������tabbarռ����������������޷������mainwindow
    //����tab��ռ�õĿ��
    const QMargins& mg = d_ptr->mRibbonTabBar->tabMargin();
    int mintabBarWidth = 0;

    for (int i = 0; i < d_ptr->mRibbonTabBar->count(); ++i) {
        mintabBarWidth += d_ptr->mRibbonTabBar->tabRect(i).width();
    }
    mintabBarWidth += (mg.left() + mg.right());
    return (mintabBarWidth);
}

/**
 * @brief mainBarHeight�ļ���߶�
 *
 * �п���SARibbonBar::height��mainBarHeight����ȣ��������������RibbonState::MinimumRibbonMode״̬��
 * @return �߶�
 */
int SARibbonBar::mainBarHeight() const
{
    return RibbonSubElementStyleOpt.ribbonBarHeight(currentRibbonStyle());
}

/**
 * @brief �������е�category title��Ӧ��tab��
 *
 * �˺���������е�category�����ֺ�tab����ƥ�䣬���ƥ�䲻�ϻ���������tab��
 */
void SARibbonBar::updateCategoryTitleToTabName()
{
    SARibbonTabBar* tab = d_ptr->mRibbonTabBar;
    for (int i = 0; i < tab->count(); ++i) {
        //����tab����ܶ࣬������Ч������
        QVariant var = tab->tabData(i);
        if (var.isValid()) {
            _SARibbonTabData p = var.value< _SARibbonTabData >();
            if (p.category && p.category->categoryName() != tab->tabText(i)) {
                tab->setTabText(i, p.category->categoryName());
            }
        }
    }
}

void SARibbonBar::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);
    if (isOfficeStyle()) {
        paintInNormalStyle();
    } else {
        paintInWpsLiteStyle();
    }
#ifdef SA_RIBBON_DEBUG_HELP_DRAW
    QPainter p(this);
    HELP_DRAW_RECT(p, m_d->quickAccessBar->geometry());
    HELP_DRAW_RECT(p, m_d->ribbonTabBar->geometry());
    HELP_DRAW_RECT(p, m_d->stackedContainerWidget->geometry());
#endif
}

void SARibbonBar::paintInNormalStyle()
{
    QPainter p(this);

    //!
    paintBackground(p);
    //! ��ʾ�����ı�ǩ
    p.save();
    QList< _SAContextCategoryManagerData > contextCategoryDataList = d_ptr->mCurrentShowingContextCategory;
    bool isCurrentSelectContextCategoryPage                        = false;

    QPoint contextCategoryRegion(width(), -1);
    QMargins border = contentsMargins();
    for (int i = 0; i < contextCategoryDataList.size(); ++i) {
        QRect contextTitleRect;
        QList< int > indexs = contextCategoryDataList[ i ].tabPageIndex;
        QColor clr          = contextCategoryDataList[ i ].contextCategory->contextColor();
        if (!indexs.isEmpty()) {
            contextTitleRect = d_ptr->mRibbonTabBar->tabRect(indexs.first());
            QRect endRect    = d_ptr->mRibbonTabBar->tabRect(indexs.last());
            contextTitleRect.setRight(endRect.right());
            contextTitleRect.translate(d_ptr->mRibbonTabBar->x(), d_ptr->mRibbonTabBar->y());
            contextTitleRect.setHeight(d_ptr->mRibbonTabBar->height() - 1);  //��1���أ�����tabbar���߸���
            contextTitleRect -= d_ptr->mRibbonTabBar->tabMargin();
            //�����򶥲���չ�����ڶ���
            contextTitleRect.setTop(border.top());
            //����
            paintContextCategoryTab(p, contextCategoryDataList[ i ].contextCategory->contextTitle(), contextTitleRect, clr);
            //���������ı�ǩ�ķ�Χ�����ڿ��Ʊ���������ʾ
            if (contextTitleRect.left() < contextCategoryRegion.x()) {
                contextCategoryRegion.setX(contextTitleRect.left());
            }
            if (contextTitleRect.right() > contextCategoryRegion.y()) {
                contextCategoryRegion.setY(contextTitleRect.right());
            }
        }
        isCurrentSelectContextCategoryPage = indexs.contains(d_ptr->mRibbonTabBar->currentIndex());
        if (isCurrentSelectContextCategoryPage) {
            QPen pen;
            pen.setColor(clr);
            pen.setWidth(1);
            p.setPen(pen);
            p.setBrush(Qt::NoBrush);
            p.drawRect(d_ptr->mStackedContainerWidget->geometry());
            isCurrentSelectContextCategoryPage = false;
        }
    }
    p.restore();
    //! ��ʾ�����
    QWidget* parWindow = parentWidget();

    if (parWindow) {
        QRect titleRegion;
        if (contextCategoryRegion.y() < 0) {
            titleRegion.setRect(d_ptr->mQuickAccessBar->geometry().right() + 1,
                                border.top(),
                                width() - d_ptr->mIconRightBorderPosition - border.right()
                                        - d_ptr->mWindowButtonSize.width() - d_ptr->mQuickAccessBar->geometry().right() - 1,
                                titleBarHeight());
        } else {
            int leftwidth = contextCategoryRegion.x() - d_ptr->mQuickAccessBar->geometry().right() - d_ptr->mIconRightBorderPosition;
            int rightwidth = width() - contextCategoryRegion.y() - d_ptr->mWindowButtonSize.width();
            //            if (width() - contextCategoryRegion.y() > contextCategoryRegion.x()-x) {
            if (rightwidth > leftwidth) {
                //˵���ұߵ������һ�㣬������ʾ���ң���ʾ���ұ���Ҫ��ȥwindowbutton���
                titleRegion.setRect(contextCategoryRegion.y(), border.top(), rightwidth, titleBarHeight());
            } else {
                //˵����ߵĴ�һ��
                titleRegion.setRect(d_ptr->mIconRightBorderPosition + d_ptr->mQuickAccessBar->geometry().right(),
                                    border.top(),
                                    leftwidth,
                                    titleBarHeight());
            }
        }
#ifdef SA_RIBBON_DEBUG_HELP_DRAW
        p.save();
        p.setBrush(QColor(255, 0, 0, 120));
        p.drawRect(titleRegion);
        p.restore();
#endif
        paintWindowTitle(p, parWindow->windowTitle(), titleRegion);
    }
}

void SARibbonBar::paintInWpsLiteStyle()
{
    QPainter p(this);
    //!
    paintBackground(p);
    //! ��ʾ�����ı�ǩ
    p.save();
    QList< _SAContextCategoryManagerData > contextCategoryDataList = d_ptr->mCurrentShowingContextCategory;
    bool isCurrentSelectContextCategoryPage                        = false;
    QMargins border                                                = contentsMargins();
    for (int i = 0; i < contextCategoryDataList.size(); ++i) {
        QRect contextTitleRect;
        QList< int > indexs = contextCategoryDataList[ i ].tabPageIndex;
        QColor clr          = contextCategoryDataList[ i ].contextCategory->contextColor();
        if (!indexs.isEmpty()) {
            contextTitleRect = d_ptr->mRibbonTabBar->tabRect(indexs.first());
            QRect endRect    = d_ptr->mRibbonTabBar->tabRect(indexs.last());
            contextTitleRect.setRight(endRect.right());
            contextTitleRect.translate(d_ptr->mRibbonTabBar->x(), d_ptr->mRibbonTabBar->y());
            contextTitleRect.setHeight(d_ptr->mRibbonTabBar->height() - 1);
            contextTitleRect -= d_ptr->mRibbonTabBar->tabMargin();
            //�����򶥲���չ�����ڶ���
            contextTitleRect.setTop(border.top());
            //����
            paintContextCategoryTab(p, QString(), contextTitleRect, clr);
        }
        isCurrentSelectContextCategoryPage = indexs.contains(d_ptr->mRibbonTabBar->currentIndex());
        if (isCurrentSelectContextCategoryPage) {
            QPen pen;
            pen.setColor(clr);
            pen.setWidth(1);
            p.setPen(pen);
            p.setBrush(Qt::NoBrush);
            p.drawRect(d_ptr->mStackedContainerWidget->geometry());
            isCurrentSelectContextCategoryPage = false;
        }
    }
    p.restore();
    //! ��ʾ�����

    QWidget* parWindow = parentWidget();

    if (parWindow) {
        int start = d_ptr->mRibbonTabBar->x() + d_ptr->mRibbonTabBar->width();
        int width = d_ptr->mQuickAccessBar->x() - start;
        if (width > 20) {
            QRect titleRegion(start, border.top(), width, titleBarHeight());
#ifdef SA_RIBBON_DEBUG_HELP_DRAW
            p.save();
            p.setBrush(QColor(255, 0, 0, 120));
            p.drawRect(titleRegion);
            p.restore();
#endif
            paintWindowTitle(p, parWindow->windowTitle(), titleRegion);
        }
    }
}

void SARibbonBar::resizeStackedContainerWidget()
{
    QMargins border = contentsMargins();
    if (d_ptr->mStackedContainerWidget->isPopupMode()) {
        //����ģʽʱ���߶�
        QPoint absPosition = mapToGlobal(QPoint(border.left(), d_ptr->mRibbonTabBar->geometry().bottom() + 1));
        d_ptr->mStackedContainerWidget->setGeometry(absPosition.x(),
                                                    absPosition.y(),
                                                    width() - border.left() - border.right(),
                                                    mainBarHeight() - d_ptr->mRibbonTabBar->geometry().bottom()
                                                            - border.bottom() - 1);
    } else {
        d_ptr->mStackedContainerWidget->setGeometry(border.left(),
                                                    d_ptr->mRibbonTabBar->geometry().bottom() + 1,
                                                    width() - border.left() - border.right(),
                                                    mainBarHeight() - d_ptr->mRibbonTabBar->geometry().bottom()
                                                            - border.bottom() - 1);
    }
}

/**
 * @brief ˢ������ContextCategoryManagerData������ڵ���һ��Categoryɾ��ʱ����
 */
void SARibbonBar::updateContextCategoryManagerData()
{
    const int c = d_ptr->mRibbonTabBar->count();

    for (_SAContextCategoryManagerData& cd : d_ptr->mCurrentShowingContextCategory) {
        cd.tabPageIndex.clear();
        for (int i = 0; i < cd.contextCategory->categoryCount(); ++i) {
            SARibbonCategory* category = cd.contextCategory->categoryPage(i);
            for (int t = 0; t < c; ++t) {
                QVariant v = d_ptr->mRibbonTabBar->tabData(t);
                if (v.isValid()) {
                    _SARibbonTabData d = v.value< _SARibbonTabData >();
                    if (d.category == category) {
                        cd.tabPageIndex.append(t);
                    }
                } else {
                    cd.tabPageIndex.append(-1);
                }
            }
        }
    }
}

/**
 * @brief ���������ı�ǩ�ı���
 * @param painter ��ͼQPainter
 * @param title �����ı�ǩ��title
 * @param contextRect �����ı�ǩ�Ļ�������
 * @param color �����ı�ǩ�������ɫ
 */
void SARibbonBar::paintContextCategoryTab(QPainter& painter, const QString& title, QRect contextRect, const QColor& color)
{
    //���������ı�ǩ
    //������5���ص�ʵ�����λ�ڶ���
    QMargins border = contentsMargins();
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawRect(QRect(contextRect.x(), border.top(), contextRect.width(), 5));

    //ʣ�°���ɫ����90%
    QColor gColor = color.lighter(190);

    //��ȥ֮ǰ��5����
    contextRect -= QMargins(0, 5, 0, 0);
    painter.fillRect(contextRect, gColor);

    //ֻ����officeģʽ�²���Ҫ���Ʊ���
    if (isOfficeStyle()) {
        if (!title.isEmpty()) {
            contextRect.setBottom(d_ptr->mRibbonTabBar->geometry().top());
            painter.setPen(color);
            painter.drawText(contextRect, Qt::AlignCenter, title);
        }
    }
    painter.restore();
}

void SARibbonBar::resizeEvent(QResizeEvent* e)
{
    Q_UNUSED(e);
    if (isOfficeStyle()) {
        resizeInOfficeStyle();
    } else {
        resizeInWpsLiteStyle();
    }
    update();
}

/**
 * @brief ��дmoveevent��Ϊ�����ƶ�ʱ����isPopupMode״̬�µ�stackedContainerWidgetλ��
 * @param event
 */
void SARibbonBar::moveEvent(QMoveEvent* event)
{
    if (d_ptr->mStackedContainerWidget) {
        if (d_ptr->mStackedContainerWidget->isPopupMode()) {
            //����ģʽʱ�����ڷ������ƶ���ͬ������StackedContainerWidget��λ��
            resizeStackedContainerWidget();
        }
    }
    QWidget::moveEvent(event);
}

void SARibbonBar::resizeInOfficeStyle()
{
    updateRibbonElementGeometry();
    QMargins border = contentsMargins();
    int x           = border.left();
    int y           = border.top();

    // cornerWidget - TopLeftCorner
    const int validTitleBarHeight = titleBarHeight();
    const int tabH                = tabBarHeight();

    x += d_ptr->mIconRightBorderPosition + 5;
    if (QWidget* connerL = cornerWidget(Qt::TopLeftCorner)) {
        if (connerL->isVisible()) {
            QSize connerSize = connerL->sizeHint();
            if (connerSize.height() < validTitleBarHeight) {
                int detal = (validTitleBarHeight - connerSize.height()) / 2;
                connerL->setGeometry(x, y + detal, connerSize.width(), connerSize.height());
            } else {
                connerL->setGeometry(x, y, connerSize.width(), validTitleBarHeight);
            }
            x = connerL->geometry().right() + 5;
        }
    }
    // quick access bar��λ
    if (d_ptr->mQuickAccessBar) {
        if (d_ptr->mQuickAccessBar->isVisible()) {
            if (d_ptr->mQuickAccessBar->height() != validTitleBarHeight) {
                d_ptr->mQuickAccessBar->setFixedHeight(validTitleBarHeight);
            }
            QSize quickAccessBarSize = d_ptr->mQuickAccessBar->sizeHint();
            d_ptr->mQuickAccessBar->setGeometry(x, y, quickAccessBarSize.width(), validTitleBarHeight);
        }
    }
    //�ڶ��У���ʼ����applicationButton��tabbar��tabBarRightSizeButtonGroupWidget��TopRightCorner
    x = border.left();
    y += validTitleBarHeight;
    // applicationButton ��λ
    if (d_ptr->mApplicationButton) {
        if (d_ptr->mApplicationButton->isVisible()) {
            d_ptr->mApplicationButton->setGeometry(x, y, d_ptr->mApplicationButton->size().width(), tabH);
            x = d_ptr->mApplicationButton->geometry().right();
        }
    }
    // top right��һ��Ҫ���õģ����ڶ��ĵ����ڣ��Ӵ��ڵ����ŵȰ�ť����ͨ���������ʵ�֣�
    //�����������һ��Ҫ�����ң�����ȶ�������ڽ��в���
    // cornerWidget - TopRightCorner
    //��ȡ���ұߵ�λ��
    int endX = width() - border.right();

    if (QWidget* connerW = cornerWidget(Qt::TopRightCorner)) {
        if (connerW->isVisible()) {
            QSize connerSize = connerW->sizeHint();
            endX -= connerSize.width();
            if (connerSize.height() < tabH) {
                int detal = (tabH - connerSize.height()) / 2;
                connerW->setGeometry(endX, y + detal, connerSize.width(), connerSize.height());
            } else {
                connerW->setGeometry(endX, y, connerSize.width(), tabH);
            }
        }
    }
    // applicationButton��TopRightCorner��ɶ�λ���ſ��Զ�λtab bar
    // tab bar ��λ

    // tabBar �ұߵĸ��Ӱ�ť�飬����һ��ḽ��һЩ���Ƶ�¼�Ȱ�ť��
    if (d_ptr->mRightButtonGroup && d_ptr->mRightButtonGroup->isVisible()) {
        QSize wSize = d_ptr->mRightButtonGroup->sizeHint();
        endX -= wSize.width();
        d_ptr->mRightButtonGroup->setGeometry(endX, y, wSize.width(), tabH);
    }
    //���ȷ��tabbar���
    int tabBarWidth = endX - x;
    d_ptr->mRibbonTabBar->setGeometry(x, y, tabBarWidth, tabH);

    resizeStackedContainerWidget();
}

void SARibbonBar::resizeInWpsLiteStyle()
{
    updateRibbonElementGeometry();
    QMargins border = contentsMargins();
    int x           = border.left();
    int y           = border.top();

    const int validTitleBarHeight = titleBarHeight();

    //�Ȳ����ұ�����
    // cornerWidget - TopRightCorner
    int endX = width() - border.right() - d_ptr->mWindowButtonSize.width();

    if (QWidget* connerW = cornerWidget(Qt::TopRightCorner)) {
        if (connerW->isVisible()) {
            QSize connerSize = connerW->sizeHint();
            endX -= connerSize.width();
            if (connerSize.height() < validTitleBarHeight) {
                int detal = (validTitleBarHeight - connerSize.height()) / 2;
                connerW->setGeometry(endX, y + detal, connerSize.width(), connerSize.height());
            } else {
                connerW->setGeometry(endX, y, connerSize.width(), validTitleBarHeight);
            }
        }
    }

    // tabBar �ұߵĸ��Ӱ�ť��
    if (d_ptr->mRightButtonGroup && d_ptr->mRightButtonGroup->isVisible()) {
        QSize wSize = d_ptr->mRightButtonGroup->sizeHint();
        endX -= wSize.width();
        d_ptr->mRightButtonGroup->setGeometry(endX, y, wSize.width(), validTitleBarHeight);
    }
    // quick access bar��λ
    if (d_ptr->mQuickAccessBar) {
        if (d_ptr->mQuickAccessBar->isVisible()) {
            QSize quickAccessBarSize = d_ptr->mQuickAccessBar->sizeHint();
            endX -= quickAccessBarSize.width();
            d_ptr->mQuickAccessBar->setGeometry(endX, y, quickAccessBarSize.width(), validTitleBarHeight);
        }
    }
    // cornerWidget - TopLeftCorner
    if (QWidget* connerL = cornerWidget(Qt::TopLeftCorner)) {
        if (connerL->isVisible()) {
            QSize connerSize = connerL->sizeHint();
            endX -= connerSize.width();
            if (connerSize.height() < validTitleBarHeight) {
                int detal = (validTitleBarHeight - connerSize.height()) / 2;
                connerL->setGeometry(endX, y + detal, connerSize.width(), connerSize.height());
            } else {
                connerL->setGeometry(endX, y, connerSize.width(), validTitleBarHeight);
            }
        }
    }

    // tab ��yֵ��Ҫ���¼���
    int tabH = tabBarHeight();

    if (tabH > validTitleBarHeight) {
        //����ֱ�Ӱ�tabH����ΪvalidTitleBarHeight
        tabH = validTitleBarHeight;
    }
    y = y + validTitleBarHeight - tabH;  //���tabH��С�������ԣ���tab�ײ���title�ĵײ�����

    // applicationButton ��λ����TabBarͬ��
    if (d_ptr->mApplicationButton) {
        if (d_ptr->mApplicationButton->isVisible()) {
            d_ptr->mApplicationButton->setGeometry(x, y, d_ptr->mApplicationButton->size().width(), tabH);
            x = d_ptr->mApplicationButton->geometry().right() + 2;
        }
    }
    // tab bar ��λ wpsģʽ��applicationButton���ұ߾���tab bar
    int tabBarWidth = endX - x;
    // 20200831
    // tabBarWidth�Ŀ��ԭ��ΪendX - x;������Ҫ����ʵ�ʽ��е���
    //Ϊ�˰�tabbarû��tab�Ĳ��ֲ�ռ�ã�����Ŀ����Ҫ����tab��size���������ã���tabbar�ĳ��ȸոպã��������ó�
    // mainwindow�Ŀռ䣬��������¼����Ӷ�ʵ���϶��Ȳ���������tabbarռ����������������޷������mainwindow
    //����tab��ռ�õĿ��
    int mintabBarWidth = calcMinTabBarWidth();

    if (mintabBarWidth < tabBarWidth) {
        tabBarWidth = mintabBarWidth;
    }
    d_ptr->mRibbonTabBar->setGeometry(x, y, tabBarWidth, tabH);

    //��������stackedContainer
    resizeStackedContainerWidget();
}

void SARibbonBar::paintBackground(QPainter& painter)
{
    painter.save();
    //��tabbar�»���һ����
    const int lineY = d_ptr->mRibbonTabBar->geometry().bottom();
    QPen pen(d_ptr->mTabBarBaseLineColor);
    QMargins border = contentsMargins();

    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    painter.drawLine(QPoint(border.left(), lineY), QPoint(width() - border.right() - 1, lineY));
    painter.restore();
}

///
/// \brief ���Ʊ�����
/// \param painter
/// \param title ����
/// \param contextCategoryRegion ��ǰ��ʾ�������ı�ǩ�ķ�Χ�������ı�ǩ�ǿ����ڵ��������ģ������Ҫ֪�������ı�ǩ�ķ�Χ
/// x��ʾ��߽磬y��ʾ�ұ߽�
///
void SARibbonBar::paintWindowTitle(QPainter& painter, const QString& title, const QRect& titleRegion)
{
    painter.save();
    painter.setPen(d_ptr->mTitleTextColor);
    painter.drawText(titleRegion, d_ptr->mTitleAligment, title);
    painter.restore();
}

/*** End of inlined file: SARibbonBar.cpp ***/

/*** Start of inlined file: SARibbonStyleOption.cpp ***/
#include <QApplication>
#include <QDebug>
SARibbonStyleOption::SARibbonStyleOption()
{
    init();
}

SARibbonStyleOption::~SARibbonStyleOption()
{
}

int SARibbonStyleOption::ribbonBarHeight(SARibbonBar::RibbonStyle s) const
{
    switch (s) {
    case SARibbonBar::OfficeStyle:
        return m_ribbonbarHeightOfficeStyleThreeRow;
    case SARibbonBar::OfficeStyleTwoRow:
        return m_ribbonbarHeightOfficeStyleTwoRow;
    case SARibbonBar::WpsLiteStyle:
        return m_ribbonbarHeightWPSStyleThreeRow;
    case SARibbonBar::WpsLiteStyleTwoRow:
        return m_ribbonbarHeightWPSStyleTwoRow;
    default:
        break;
    }
    return m_ribbonbarHeightOfficeStyleThreeRow;
}

/**
 * @brief �������߶�
 * @return
 */
int SARibbonStyleOption::titleBarHeight() const
{
    return m_titleBarHeight;
}

int SARibbonStyleOption::tabBarHeight() const
{
    return m_tabBarHeight;
}

void SARibbonStyleOption::recalc()
{
    updateMainbarHeight();
}

/**
 * @brief ����ribbon�ĸ߶�
 *
 * @note ���ô˺���֮ǰ�������
 * @param s
 * @return
 */
int SARibbonStyleOption::calcMainbarHeight(SARibbonBar::RibbonStyle s) const
{
    switch (s) {
    case SARibbonBar::WpsLiteStyle:
        // ���Ǽ�ȥm_titleBarHeightԭ���ǻ���wps����ʽʱ���������Ǵ��ڣ�ֻ�ǰ�bar���ڱ������ϣ��൱��û��bar
        return m_ribbonbarHeightOfficeStyleThreeRow - m_tabBarHeight;
    case SARibbonBar::WpsLiteStyleTwoRow:
        //����ģʽ�ѱ�����ȥ��
        return m_ribbonbarHeightOfficeStyleThreeRow * 0.9 - m_tabBarHeight - SARibbonPannel::pannelTitleHeight();
    case SARibbonBar::OfficeStyleTwoRow:
        return m_ribbonbarHeightOfficeStyleThreeRow * 0.9 - SARibbonPannel::pannelTitleHeight();
    default:
        break;
    }
    return m_ribbonbarHeightOfficeStyleThreeRow;
}

void SARibbonStyleOption::init()
{
    QFontMetrics fm = QApplication::fontMetrics();
    int lineSpacing = fm.lineSpacing();

    m_titleBarHeight                     = lineSpacing * 1.8;
    m_tabBarHeight                       = lineSpacing * 1.5;
    m_ribbonbarHeightOfficeStyleThreeRow = m_titleBarHeight + m_tabBarHeight + (lineSpacing * 1.5) * 3
                                           + SARibbonPannel::pannelTitleHeight()
                                           + SARibbonPannelLayout::pannelContentsMargins().bottom()
                                           + SARibbonPannelLayout::pannelContentsMargins().top();
    updateMainbarHeight();
}

void SARibbonStyleOption::updateMainbarHeight()
{
    m_ribbonbarHeightWPSStyleThreeRow  = calcMainbarHeight(SARibbonBar::WpsLiteStyle);
    m_ribbonbarHeightOfficeStyleTwoRow = calcMainbarHeight(SARibbonBar::OfficeStyleTwoRow);
    m_ribbonbarHeightWPSStyleTwoRow    = calcMainbarHeight(SARibbonBar::WpsLiteStyleTwoRow);
}

/**
 * @brief ��SARibbonStyleOption���
 * @param debug
 * @param c
 * @return
 */
QDebug operator<<(QDebug debug, const SARibbonStyleOption& c)
{
    QDebugStateSaver saver(debug);
    Q_UNUSED(saver);
    debug.nospace() << "fontMetrics.lineSpacing=" << QApplication::fontMetrics().lineSpacing()
                    << ",SARibbonStyleOption(titleBarHeight=" << c.titleBarHeight() << ",tabBarHeight=" << c.tabBarHeight()
                    << "\n,ribbonBarHeight(OfficeStyle)=" << c.ribbonBarHeight(SARibbonBar::OfficeStyle)
                    << "\n,ribbonBarHeight(OfficeStyleTwoRow)=" << c.ribbonBarHeight(SARibbonBar::OfficeStyleTwoRow)
                    << "\n,ribbonBarHeight(WpsLiteStyle)=" << c.ribbonBarHeight(SARibbonBar::WpsLiteStyle)
                    << "\n,ribbonBarHeight(WpsLiteStyleTwoRow)=" << c.ribbonBarHeight(SARibbonBar::WpsLiteStyleTwoRow);
    return debug;
}

/*** End of inlined file: SARibbonStyleOption.cpp ***/

/*** Start of inlined file: SARibbonElementFactory.cpp ***/
#include <QApplication>
#include <QFontMetrics>

SARibbonElementFactory::SARibbonElementFactory() : mStyleOption(new SARibbonStyleOption())
{
}

SARibbonElementFactory::~SARibbonElementFactory()
{
}

SARibbonTabBar* SARibbonElementFactory::createRibbonTabBar(QWidget* parent)
{
    return (new SARibbonTabBar(parent));
}

SARibbonApplicationButton* SARibbonElementFactory::createRibbonApplicationButton(QWidget* parent)
{
    return (new SARibbonApplicationButton(parent));
}

SARibbonCategory* SARibbonElementFactory::createRibbonCategory(QWidget* parent)
{
    return (new SARibbonCategory(parent));
}

SARibbonContextCategory* SARibbonElementFactory::createRibbonContextCategory(QWidget* parent)
{
    return (new SARibbonContextCategory(parent));
}

SARibbonPannel* SARibbonElementFactory::createRibbonPannel(QWidget* parent)
{
    return (new SARibbonPannel(parent));
}

SARibbonSeparatorWidget* SARibbonElementFactory::createRibbonSeparatorWidget(int value, QWidget* parent)
{
    return (new SARibbonSeparatorWidget(value, parent));
}

SARibbonSeparatorWidget* SARibbonElementFactory::createRibbonSeparatorWidget(QWidget* parent)
{
    return (new SARibbonSeparatorWidget(parent));
}

SARibbonGallery* SARibbonElementFactory::createRibbonGallery(QWidget* parent)
{
    return (new SARibbonGallery(parent));
}

SARibbonGalleryGroup* SARibbonElementFactory::createRibbonGalleryGroup(QWidget* parent)
{
    return (new SARibbonGalleryGroup(parent));
}

SARibbonToolButton* SARibbonElementFactory::createRibbonToolButton(QWidget* parent)
{
    return (new SARibbonToolButton(parent));
}

SARibbonStackedWidget* SARibbonElementFactory::createRibbonStackedWidget(SARibbonBar* parent)
{
    return (new SARibbonStackedWidget(parent));
}

SARibbonControlButton* SARibbonElementFactory::createHidePannelButton(SARibbonBar* parent)
{
    SARibbonControlButton* btn = new SARibbonControlButton(parent);

    btn->setAutoRaise(false);
    btn->setObjectName(QStringLiteral("SARibbonBarHidePannelButton"));
    btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    btn->setFixedSize(parent->tabBarHeight() - 4, parent->tabBarHeight() - 4);
    return (btn);
}

SARibbonButtonGroupWidget* SARibbonElementFactory::craeteButtonGroupWidget(QWidget* parent)
{
    return (new SARibbonButtonGroupWidget(parent));
}

SARibbonQuickAccessBar* SARibbonElementFactory::createQuickAccessBar(QWidget* parent)
{
    return (new SARibbonQuickAccessBar(parent));
}

SARibbonStyleOption& SARibbonElementFactory::getRibbonStyleOption()
{
    return (*mStyleOption);
}

/**
 * @brief ����style����
 * @param opt
 */
void SARibbonElementFactory::setRibbonStyleOption(SARibbonStyleOption* opt)
{
    mStyleOption.reset(opt);
}

/**
 * @brief ����SARibbonPannelOptionButton
 * @param pannel ������pannel
 * @return
 * @sa @ref SARibbonPannelOptionButton
 */
SARibbonPannelOptionButton* SARibbonElementFactory::createRibbonPannelOptionButton(SARibbonPannel* pannel)
{
    return (new SARibbonPannelOptionButton(pannel));
}

/*** End of inlined file: SARibbonElementFactory.cpp ***/

/*** Start of inlined file: SARibbonElementManager.cpp ***/
SARibbonElementManager::SARibbonElementManager()
{
    mFactory.reset(new SARibbonElementFactory());
}

SARibbonElementManager::~SARibbonElementManager()
{
}

SARibbonElementManager* SARibbonElementManager::instance()
{
    static SARibbonElementManager s_instance;

    return (&(s_instance));
}

SARibbonElementFactory* SARibbonElementManager::factory()
{
    return (mFactory.data());
}

void SARibbonElementManager::setupFactory(SARibbonElementFactory* delegate)
{
    mFactory.reset(delegate);
}

/*** End of inlined file: SARibbonElementManager.cpp ***/

/*** Start of inlined file: SARibbonCustomizeData.cpp ***/
#include <QDebug>
#include <QObject>
////////////////////////////////////////////////////////////////////////////////////////////////////////
/// SARibbonCustomizeData
////////////////////////////////////////////////////////////////////////////////////////////////////////

SARibbonCustomizeData::SARibbonCustomizeData()
    : indexValue(-1), actionRowProportionValue(SARibbonPannelItem::Large), m_type(UnknowActionType), m_actionsManagerPointer(nullptr)
{
}

SARibbonCustomizeData::SARibbonCustomizeData(ActionType type, SARibbonActionsManager* mgr)
    : indexValue(-1), actionRowProportionValue(SARibbonPannelItem::Large), m_type(type), m_actionsManagerPointer(mgr)
{
}

/**
 * @brief ��ȡCustomizeData��action type
 * @return
 */
SARibbonCustomizeData::ActionType SARibbonCustomizeData::actionType() const
{
    return (m_type);
}

/**
 * @brief ����CustomizeData��action type
 * @param a
 */
void SARibbonCustomizeData::setActionType(SARibbonCustomizeData::ActionType a)
{
    m_type = a;
}

/**
 * @brief �ж��Ƿ���һ��������CustomizeData
 *
 * ʵ���߼�actionType() != UnknowActionType
 * @return ���õ�CustomizeData����true
 */
bool SARibbonCustomizeData::isValid() const
{
    return (actionType() != UnknowActionType);
}

/**
 * @brief Ӧ��SARibbonCustomizeData��SARibbonMainWindow
 * @param m
 * @return ���Ӧ��ʧ�ܣ�����false,���actionType==UnknowActionTypeֱ�ӷ���false
 */
bool SARibbonCustomizeData::apply(SARibbonMainWindow* m) const
{
    SARibbonBar* bar = m->ribbonBar();

    if (nullptr == bar) {
        return (false);
    }
    switch (actionType()) {
    case UnknowActionType:
        return (false);

    case AddCategoryActionType: {
        //��ӱ�ǩ
        SARibbonCategory* c = bar->insertCategoryPage(keyValue, indexValue);
        if (nullptr == c) {
            return (false);
        }
        c->setObjectName(categoryObjNameValue);
        SARibbonCustomizeData::setCanCustomize(c);
        return (true);
    }

    case AddPannelActionType: {
        //���pannel
        SARibbonCategory* c = bar->categoryByObjectName(categoryObjNameValue);
        if (nullptr == c) {
            return (false);
        }
        SARibbonPannel* p = c->insertPannel(keyValue, indexValue);
        p->setObjectName(pannelObjNameValue);
        SARibbonCustomizeData::setCanCustomize(p);
        return (true);
    }

    case AddActionActionType: {
        if (nullptr == m_actionsManagerPointer) {
            return (false);
        }
        SARibbonCategory* c = bar->categoryByObjectName(categoryObjNameValue);
        if (nullptr == c) {
            return (false);
        }
        SARibbonPannel* pannel = c->pannelByObjectName(pannelObjNameValue);
        if (nullptr == pannel) {
            return (false);
        }
        QAction* act = m_actionsManagerPointer->action(keyValue);
        if (nullptr == act) {
            return (false);
        }
        SARibbonCustomizeData::setCanCustomize(act);
        pannel->addAction(act, actionRowProportionValue);
        return (true);
    }

    case RemoveCategoryActionType: {
        SARibbonCategory* c = bar->categoryByObjectName(categoryObjNameValue);
        if (nullptr == c) {
            return (false);
        }
        bar->removeCategory(c);
        return (true);
    }

    case RemovePannelActionType: {
        SARibbonCategory* c = bar->categoryByObjectName(categoryObjNameValue);
        if (nullptr == c) {
            return (false);
        }
        SARibbonPannel* pannel = c->pannelByObjectName(pannelObjNameValue);
        if (nullptr == pannel) {
            return (false);
        }
        c->removePannel(pannel);
        return (true);
    }

    case RemoveActionActionType: {
        SARibbonCategory* c = bar->categoryByObjectName(categoryObjNameValue);
        if (nullptr == c) {
            return (false);
        }
        SARibbonPannel* pannel = c->pannelByObjectName(pannelObjNameValue);
        if (nullptr == pannel) {
            return (false);
        }
        QAction* act = m_actionsManagerPointer->action(keyValue);
        if (nullptr == act) {
            return (false);
        }
        pannel->removeAction(act);
        return (true);
    }

    case ChangeCategoryOrderActionType: {
        SARibbonCategory* c = bar->categoryByObjectName(categoryObjNameValue);
        if (nullptr == c) {
            return (false);
        }
        int currentindex = bar->categoryIndex(c);
        if (-1 == currentindex) {
            return (false);
        }
        int toindex = currentindex + indexValue;
        bar->moveCategory(currentindex, toindex);
        return (true);
    }

    case ChangePannelOrderActionType: {
        SARibbonCategory* c = bar->categoryByObjectName(categoryObjNameValue);
        if (nullptr == c) {
            return (false);
        }
        SARibbonPannel* pannel = c->pannelByObjectName(pannelObjNameValue);
        if (nullptr == pannel) {
            return (false);
        }
        int pannelIndex = c->pannelIndex(pannel);
        if (-1 == pannelIndex) {
            return (false);
        }
        c->movePannel(pannelIndex, pannelIndex + indexValue);
        return (true);
    }

    case ChangeActionOrderActionType: {
        SARibbonCategory* c = bar->categoryByObjectName(categoryObjNameValue);
        if (nullptr == c) {
            return (false);
        }
        SARibbonPannel* pannel = c->pannelByObjectName(pannelObjNameValue);
        if (nullptr == pannel) {
            return (false);
        }
        QAction* act = m_actionsManagerPointer->action(keyValue);
        if (nullptr == act) {
            return (false);
        }
        int actindex = pannel->actionIndex(act);
        if (actindex <= -1) {
            return (false);
        }
        pannel->moveAction(actindex, actindex + indexValue);
        return (true);
    }

    case RenameCategoryActionType: {
        SARibbonCategory* c = bar->categoryByObjectName(categoryObjNameValue);
        if (nullptr == c) {
            return (false);
        }
        c->setCategoryName(keyValue);
        return (true);
    }

    case RenamePannelActionType: {
        SARibbonCategory* c = bar->categoryByObjectName(categoryObjNameValue);
        if (nullptr == c) {
            return (false);
        }
        SARibbonPannel* pannel = c->pannelByObjectName(pannelObjNameValue);
        if (nullptr == pannel) {
            return (false);
        }
        pannel->setPannelName(keyValue);
        return (true);
    }

    case VisibleCategoryActionType: {
        SARibbonCategory* c = bar->categoryByObjectName(categoryObjNameValue);
        if (nullptr == c) {
            return (false);
        }
        if (1 == indexValue) {
            bar->showCategory(c);
        } else {
            bar->hideCategory(c);
        }
        return (true);
    }

    default:
        break;
    }
    return (false);
}

/**
 * @brief ��ȡactionmanagerָ��
 * @return
 */
SARibbonActionsManager* SARibbonCustomizeData::actionManager()
{
    return (m_actionsManagerPointer);
}

/**
 * @brief ����ActionsManager
 * @param mgr
 */
void SARibbonCustomizeData::setActionsManager(SARibbonActionsManager* mgr)
{
    m_actionsManagerPointer = mgr;
}

/**
 * @brief ����һ��AddCategoryActionType��SARibbonCustomizeData
 * @param title category �ı���
 * @param index categoryҪ�����λ��
 * @param objName category��object name
 * @return ����AddCategoryActionType��SARibbonCustomizeData
 */
SARibbonCustomizeData SARibbonCustomizeData::makeAddCategoryCustomizeData(const QString& title, int index, const QString& objName)
{
    SARibbonCustomizeData d(AddCategoryActionType);

    d.indexValue           = index;
    d.keyValue             = title;
    d.categoryObjNameValue = objName;
    return (d);
}

/**
 * @brief ����һ��AddPannelActionType��SARibbonCustomizeData
 * @param title pannel�ı���
 * @param index pannel��index
 * @param categoryobjName pannel��category��objectname
 * @param objName pannel��objname
 * @return ����AddPannelActionType��SARibbonCustomizeData
 */
SARibbonCustomizeData SARibbonCustomizeData::makeAddPannelCustomizeData(const QString& title,
                                                                        int index,
                                                                        const QString& categoryobjName,
                                                                        const QString& objName)
{
    SARibbonCustomizeData d(AddPannelActionType);

    d.indexValue           = index;
    d.keyValue             = title;
    d.pannelObjNameValue   = objName;
    d.categoryObjNameValue = categoryobjName;
    return (d);
}

/**
 * @brief ���action
 * @param key action������
 * @param mgr action������
 * @param rp ����action��ռλ���
 * @param categoryObjName action��ӵ���category��objname
 * @param pannelObjName action��ӵ���category�µ�pannel��objname
 * @param index action��ӵ���pannel������
 * @return
 */
SARibbonCustomizeData SARibbonCustomizeData::makeAddActionCustomizeData(const QString& key,
                                                                        SARibbonActionsManager* mgr,
                                                                        SARibbonPannelItem::RowProportion rp,
                                                                        const QString& categoryObjName,
                                                                        const QString& pannelObjName)
{
    SARibbonCustomizeData d(AddActionActionType, mgr);

    d.keyValue                 = key;
    d.categoryObjNameValue     = categoryObjName;
    d.pannelObjNameValue       = pannelObjName;
    d.actionRowProportionValue = rp;

    return (d);
}

/**
 * @brief ����һ��RenameCategoryActionType��SARibbonCustomizeData
 * @param newname ������
 * @param index category������
 * @return ����RenameCategoryActionType��SARibbonCustomizeData
 */
SARibbonCustomizeData SARibbonCustomizeData::makeRenameCategoryCustomizeData(const QString& newname, const QString& categoryobjName)
{
    SARibbonCustomizeData d(RenameCategoryActionType);

    if (categoryobjName.isEmpty()) {
        qDebug() << QObject::tr("SARibbon Warning !!! customize rename category,"
                                "but get an empty category object name,"
                                "if you want to customize SARibbon,"
                                "please make sure every element has been set object name.");
    }
    d.keyValue             = newname;
    d.categoryObjNameValue = categoryobjName;
    return (d);
}

/**
 * @brief ����һ��RenamePannelActionType��SARibbonCustomizeData
 * @param newname pannel������
 * @param indexValue pannel������
 * @param categoryobjName pannel��Ӧ��category��object name
 * @return ����RenamePannelActionType��SARibbonCustomizeData
 */
SARibbonCustomizeData SARibbonCustomizeData::makeRenamePannelCustomizeData(const QString& newname,
                                                                           const QString& categoryobjName,
                                                                           const QString& pannelObjName)
{
    SARibbonCustomizeData d(RenamePannelActionType);

    if (pannelObjName.isEmpty() || categoryobjName.isEmpty()) {
        qDebug() << QObject::tr("SARibbon Warning !!! customize rename pannel,"
                                "but get an empty category/pannel object name,"
                                "if you want to customize SARibbon,"
                                "please make sure every element has been set object name.");
    }
    d.keyValue             = newname;
    d.pannelObjNameValue   = pannelObjName;
    d.categoryObjNameValue = categoryobjName;
    return (d);
}

/**
 * @brief ��ӦChangeCategoryOrderActionType
 * @param categoryobjName ��Ҫ�ƶ���categoryobjName
 * @param moveindex �ƶ�λ�ã�-1�������ϣ������ƶ�һ��λ�ã�1�������£����ң��ƶ�һ��λ��
 * @return
 */
SARibbonCustomizeData SARibbonCustomizeData::makeChangeCategoryOrderCustomizeData(const QString& categoryobjName, int moveindex)
{
    SARibbonCustomizeData d(ChangeCategoryOrderActionType);

    if (categoryobjName.isEmpty()) {
        qDebug() << QObject::tr("SARibbon Warning !!! customize change category order,"
                                "but get an empty category object name,"
                                "if you want to customize SARibbon,"
                                "please make sure every element has been set object name.");
    }
    d.categoryObjNameValue = categoryobjName;
    d.indexValue           = moveindex;
    return (d);
}

/**
 * @brief ��ӦChangePannelOrderActionType
 * @param categoryobjName ��Ҫ�ƶ���pannel��Ӧ��categoryobjName
 * @param pannelObjName ��Ҫ�ƶ���pannelObjName
 * @param moveindex �ƶ�λ�ã�-1�������ϣ������ƶ�һ��λ�ã�1�������£����ң��ƶ�һ��λ��
 * @return
 */
SARibbonCustomizeData SARibbonCustomizeData::makeChangePannelOrderCustomizeData(const QString& categoryobjName,
                                                                                const QString& pannelObjName,
                                                                                int moveindex)
{
    SARibbonCustomizeData d(ChangePannelOrderActionType);

    if (categoryobjName.isEmpty() || pannelObjName.isEmpty()) {
        qDebug() << QObject::tr("SARibbon Warning !!! customize change pannel order,"
                                "but get an empty category/pannel object name,"
                                "if you want to customize SARibbon,"
                                "please make sure every element has been set object name.");
    }
    d.categoryObjNameValue = categoryobjName;
    d.pannelObjNameValue   = pannelObjName;
    d.indexValue           = moveindex;
    return (d);
}

/**
 * @brief ��ӦChangeActionOrderActionType
 * @param categoryobjName ��Ҫ�ƶ���pannel��Ӧ��categoryobjName
 * @param pannelObjName ��Ҫ�ƶ���pannelObjName
 * @param key SARibbonActionsManager�����key��
 * @param mgr SARibbonActionsManagerָ��
 * @param moveindex �ƶ�λ�ã�-1�������ϣ������ƶ�һ��λ�ã�1�������£����ң��ƶ�һ��λ��
 * @return
 */
SARibbonCustomizeData SARibbonCustomizeData::makeChangeActionOrderCustomizeData(const QString& categoryobjName,
                                                                                const QString& pannelObjName,
                                                                                const QString& key,
                                                                                SARibbonActionsManager* mgr,
                                                                                int moveindex)
{
    SARibbonCustomizeData d(ChangeActionOrderActionType, mgr);

    if (categoryobjName.isEmpty() || pannelObjName.isEmpty() || key.isEmpty()) {
        qDebug() << QObject::tr("SARibbon Warning !!! customize change action order,"
                                "but get an empty category/pannel/action object name,"
                                "if you want to customize SARibbon,"
                                "please make sure every element has been set object name.");
    }
    d.categoryObjNameValue = categoryobjName;
    d.pannelObjNameValue   = pannelObjName;
    d.keyValue             = key;
    d.indexValue           = moveindex;
    return (d);
}

/**
 * @brief ��ӦRemoveCategoryActionType
 * @param categoryobjName ��Ҫ�Ƴ���objname
 * @return
 */
SARibbonCustomizeData SARibbonCustomizeData::makeRemoveCategoryCustomizeData(const QString& categoryobjName)
{
    SARibbonCustomizeData d(RemoveCategoryActionType);

    if (categoryobjName.isEmpty()) {
        qDebug() << QObject::tr("SARibbon Warning !!! customize remove category,"
                                "but get an empty category object name,"
                                "if you want to customize SARibbon,"
                                "please make sure every element has been set object name.");
    }
    d.categoryObjNameValue = categoryobjName;
    return (d);
}

/**
 * @brief ��ӦRemovePannelActionType
 * @param categoryobjName pannel��Ӧ��category��obj name
 * @param pannelObjName pannel��Ӧ�� obj name
 * @return
 */
SARibbonCustomizeData SARibbonCustomizeData::makeRemovePannelCustomizeData(const QString& categoryobjName, const QString& pannelObjName)
{
    SARibbonCustomizeData d(RemovePannelActionType);

    if (categoryobjName.isEmpty() || pannelObjName.isEmpty()) {
        qDebug() << QObject::tr("SARibbon Warning !!! customize remove pannel,"
                                "but get an empty category/pannel object name,"
                                "if you want to customize SARibbon,"
                                "please make sure every element has been set object name.");
    }
    d.categoryObjNameValue = categoryobjName;
    d.pannelObjNameValue   = pannelObjName;
    return (d);
}

/**
 * @brief ��ӦRemoveActionActionType
 * @param categoryobjName pannel��Ӧ��category��obj name
 * @param pannelObjName pannel��Ӧ�� obj name
 * @param key SARibbonActionsManager�����key��
 * @param mgr SARibbonActionsManagerָ��
 * @return
 */
SARibbonCustomizeData SARibbonCustomizeData::makeRemoveActionCustomizeData(const QString& categoryobjName,
                                                                           const QString& pannelObjName,
                                                                           const QString& key,
                                                                           SARibbonActionsManager* mgr)
{
    SARibbonCustomizeData d(RemoveActionActionType, mgr);

    if (categoryobjName.isEmpty() || pannelObjName.isEmpty() || key.isEmpty()) {
        qDebug() << QObject::tr("SARibbon Warning !!! customize remove action,"
                                "but get an empty category/pannel/action object name,"
                                "if you want to customize SARibbon,"
                                "please make sure every element has been set object name.");
    }
    d.categoryObjNameValue = categoryobjName;
    d.pannelObjNameValue   = pannelObjName;
    d.keyValue             = key;
    return (d);
}

/**
 * @brief SARibbonCustomizeData::makeVisibleCategoryCustomizeData
 * @param categoryobjName
 * @param isShow
 * @return
 */
SARibbonCustomizeData SARibbonCustomizeData::makeVisibleCategoryCustomizeData(const QString& categoryobjName, bool isShow)
{
    SARibbonCustomizeData d(VisibleCategoryActionType);

    if (categoryobjName.isEmpty()) {
        qDebug() << QObject::tr("SARibbon Warning !!! customize visible category,"
                                "but get an empty category object name,"
                                "if you want to customize SARibbon,"
                                "please make sure every element has been set object name.");
    }
    d.categoryObjNameValue = categoryobjName;
    d.indexValue           = isShow ? 1 : 0;
    return (d);
}

/**
 * @brief �ж��������ԣ��Ƿ������Զ���
 * @param obj
 * @return
 */
bool SARibbonCustomizeData::isCanCustomize(QObject* obj)
{
    QVariant v = obj->property(SA_RIBBON_BAR_PROP_CAN_CUSTOMIZE);

    if (v.isValid()) {
        return (v.toBool());
    }
    return (false);
}

/**
 * @brief �����������������Զ���
 * @param obj
 * @param canbe
 */
void SARibbonCustomizeData::setCanCustomize(QObject* obj, bool canbe)
{
    obj->setProperty(SA_RIBBON_BAR_PROP_CAN_CUSTOMIZE, canbe);
}

QList< SARibbonCustomizeData > remove_indexs(const QList< SARibbonCustomizeData >& csd, const QList< int >& willremoveIndex);

QList< SARibbonCustomizeData > remove_indexs(const QList< SARibbonCustomizeData >& csd, const QList< int >& willremoveIndex)
{
    QList< SARibbonCustomizeData > res;

    for (int i = 0; i < csd.size(); ++i) {
        if (!willremoveIndex.contains(i)) {
            res << csd[ i ];
        }
    }
    return (res);
}

/**
 * @brief ��QList<SARibbonCustomizeData>���м򻯲���
 *
 * �˺�����ִ�����²�����
 * 1�����ͬһ��category/pannel�������ֵ���Ӻ�ɾ�����������Ƴ���ǰһ����ӣ���һ��ɾ����
 *
 * 2�����VisibleCategoryActionType�������������ֵĲ���ֻ�������һ��
 *
 * 3�����RenameCategoryActionType��RenamePannelActionType������ֻ�������һ��
 *
 * 4�����������ChangeCategoryOrderActionType��ChangePannelOrderActionType��ChangeActionOrderActionType���кϲ�Ϊһ��������
 * ����ϲ���ԭ�ز�������ɾ��
 *
 * @param csd
 * @return ���ؼ򻯵�QList<SARibbonCustomizeData>
 */
QList< SARibbonCustomizeData > SARibbonCustomizeData::simplify(const QList< SARibbonCustomizeData >& csd)
{
    int size = csd.size();

    if (size <= 1) {
        return (csd);
    }
    QList< SARibbonCustomizeData > res;
    QList< int > willremoveIndex;  //��¼Ҫɾ����index

    //! ��������������ֵ���Ӻ�ɾ�����������Ż�
    for (int i = 1; i < size; ++i) {
        if ((csd[ i - 1 ].actionType() == AddCategoryActionType) && (csd[ i ].actionType() == RemoveCategoryActionType)) {
            if (csd[ i - 1 ].categoryObjNameValue == csd[ i ].categoryObjNameValue) {
                willremoveIndex << i - 1 << i;
            }
        } else if ((csd[ i - 1 ].actionType() == AddPannelActionType) && (csd[ i ].actionType() == RemovePannelActionType)) {
            if ((csd[ i - 1 ].pannelObjNameValue == csd[ i ].pannelObjNameValue)
                && (csd[ i - 1 ].categoryObjNameValue == csd[ i ].categoryObjNameValue)) {
                willremoveIndex << i - 1 << i;
            }
        } else if ((csd[ i - 1 ].actionType() == AddActionActionType) && (csd[ i ].actionType() == RemoveActionActionType)) {
            if ((csd[ i - 1 ].keyValue == csd[ i ].keyValue) && (csd[ i - 1 ].pannelObjNameValue == csd[ i ].pannelObjNameValue)
                && (csd[ i - 1 ].categoryObjNameValue == csd[ i ].categoryObjNameValue)) {
                willremoveIndex << i - 1 << i;
            }
        }
    }
    res = remove_indexs(csd, willremoveIndex);
    willremoveIndex.clear();

    //! ɸѡVisibleCategoryActionType�������������ֵĲ���ֻ�������һ��
    size = res.size();
    for (int i = 1; i < size; ++i) {
        if ((res[ i - 1 ].actionType() == VisibleCategoryActionType) && (res[ i ].actionType() == VisibleCategoryActionType)) {
            if (res[ i - 1 ].categoryObjNameValue == res[ i ].categoryObjNameValue) {
                //Ҫ��֤��������ͬһ������
                willremoveIndex << i - 1;  //ɾ��ǰһ��ֻ�������һ��
            }
        }
    }
    res = remove_indexs(res, willremoveIndex);
    willremoveIndex.clear();

    //! ���RenameCategoryActionType��RenamePannelActionType������ֻ�豣�����һ��
    size = res.size();
    for (int i = 0; i < size; ++i) {
        if (res[ i ].actionType() == RenameCategoryActionType) {
            //����ѯ�������ѯ����ͬһ��Category�������������������ɾ������
            for (int j = i + 1; j < size; ++j) {
                if ((res[ j ].actionType() == RenameCategoryActionType)
                    && (res[ i ].categoryObjNameValue == res[ j ].categoryObjNameValue)) {
                    willremoveIndex << i;
                }
            }
        } else if (res[ i ].actionType() == RenamePannelActionType) {
            //����ѯ�������ѯ����ͬһ��pannel�������������������ɾ������
            for (int j = i + 1; j < size; ++j) {
                if ((res[ j ].actionType() == RenamePannelActionType) && (res[ i ].pannelObjNameValue == res[ j ].pannelObjNameValue)
                    && (res[ i ].categoryObjNameValue == res[ j ].categoryObjNameValue)) {
                    willremoveIndex << i;
                }
            }
        }
    }
    res = remove_indexs(res, willremoveIndex);
    willremoveIndex.clear();

    //! ���������ChangeCategoryOrderActionType��ChangePannelOrderActionType��ChangeActionOrderActionType���кϲ�
    size = res.size();
    for (int i = 1; i < size; ++i) {
        if ((res[ i - 1 ].actionType() == ChangeCategoryOrderActionType) && (res[ i ].actionType() == ChangeCategoryOrderActionType)
            && (res[ i - 1 ].categoryObjNameValue == res[ i ].categoryObjNameValue)) {
            //˵����������˳���������ǰһ��indexvalue�ͺ�һ��indexvalue��ӣ�ǰһ��ɾ��
            res[ i ].indexValue += res[ i - 1 ].indexValue;
            willremoveIndex << i - 1;
        } else if ((res[ i - 1 ].actionType() == ChangePannelOrderActionType) && (res[ i ].actionType() == ChangePannelOrderActionType)
                   && (res[ i - 1 ].pannelObjNameValue == res[ i ].pannelObjNameValue)
                   && (res[ i - 1 ].categoryObjNameValue == res[ i ].categoryObjNameValue)) {
            //˵����������˳���������ǰһ��indexvalue�ͺ�һ��indexvalue��ӣ�ǰһ��ɾ��
            res[ i ].indexValue += res[ i - 1 ].indexValue;
            willremoveIndex << i - 1;
        } else if ((res[ i - 1 ].actionType() == ChangeActionOrderActionType)
                   && (res[ i ].actionType() == ChangeActionOrderActionType) && (res[ i - 1 ].keyValue == res[ i ].keyValue)
                   && (res[ i - 1 ].pannelObjNameValue == res[ i ].pannelObjNameValue)
                   && (res[ i - 1 ].categoryObjNameValue == res[ i ].categoryObjNameValue)) {
            //˵����������˳���������ǰһ��indexvalue�ͺ�һ��indexvalue��ӣ�ǰһ��ɾ��
            res[ i ].indexValue += res[ i - 1 ].indexValue;
            willremoveIndex << i - 1;
        }
    }
    res = remove_indexs(res, willremoveIndex);
    willremoveIndex.clear();

    //! ��һ���������ܻ����indexvalueΪ0��������˲�����indexvalueΪ0��ɾ��
    size = res.size();
    for (int i = 0; i < size; ++i) {
        if ((res[ i ].actionType() == ChangeCategoryOrderActionType) || (res[ i ].actionType() == ChangePannelOrderActionType)
            || (res[ i ].actionType() == ChangeActionOrderActionType)) {
            if (0 == res[ i ].indexValue) {
                willremoveIndex << i;
            }
        }
    }
    res = remove_indexs(res, willremoveIndex);
    willremoveIndex.clear();
    return (res);
}

/*** End of inlined file: SARibbonCustomizeData.cpp ***/

/*** Start of inlined file: SARibbonCustomizeWidget.cpp ***/
#include <QDebug>
#include <QtCore/QVariant>
#include <QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QListView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include <QStandardItemModel>
#include <QButtonGroup>
#include <QInputDialog>
#include <QLineEdit>
#include <QDateTime>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include <QFile>
#include <QMessageBox>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// SARibbonCustomizeWidget
////////////////////////////////////////////////////////////////////////////////////////////////////////

bool sa_customize_datas_to_xml(QXmlStreamWriter* xml, const QList< SARibbonCustomizeData >& cds)
{
    if (cds.size() <= 0) {
        return (false);
    }

    xml->writeStartElement("sa-ribbon-customize");
    for (const SARibbonCustomizeData& d : cds) {
        xml->writeStartElement("customize-data");
        xml->writeAttribute("type", QString::number(d.actionType()));
        xml->writeAttribute("index", QString::number(d.indexValue));
        xml->writeAttribute("key", d.keyValue);
        xml->writeAttribute("category", d.categoryObjNameValue);
        xml->writeAttribute("pannel", d.pannelObjNameValue);
        xml->writeAttribute("row-prop", QString::number(d.actionRowProportionValue));

        xml->writeEndElement();
    }
    xml->writeEndElement();
    if (xml->hasError()) {
        qWarning() << "write has error";
    }
    return (true);
}

QList< SARibbonCustomizeData > sa_customize_datas_from_xml(QXmlStreamReader* xml, SARibbonActionsManager* mgr)
{
    //���ҵ�"sa-ribbon-customize"
    while (!xml->atEnd()) {
        qDebug() << "name:" << xml->name() << " qualifiedName:" << xml->qualifiedName();

        if (xml->isStartElement() && (xml->name().toString() == "sa-ribbon-customize")) {
            break;
        }
        xml->readNext();
    }
    QList< SARibbonCustomizeData > res;

    //��ʼ����"customize-data"
    while (!xml->atEnd()) {
        if (xml->isStartElement() && (xml->name().toString() == "customize-data")) {
            //���ȶ�ȡ����type
            SARibbonCustomizeData d;
            QXmlStreamAttributes attrs = xml->attributes();
            if (!attrs.hasAttribute("type")) {
                //˵���쳣���������
                xml->readNextStartElement();
                continue;
            }
            bool isOk = false;
            int v     = xml->attributes().value("type").toInt(&isOk);
            if (!isOk) {
                //˵���쳣���������
                xml->readNextStartElement();
                continue;
            }
            d.setActionType(static_cast< SARibbonCustomizeData::ActionType >(v));
            //��ʼ��ȡ�Ӷ���
            if (attrs.hasAttribute("index")) {
                v = xml->attributes().value("index").toInt(&isOk);
                if (isOk) {
                    d.indexValue = v;
                }
            }
            if (attrs.hasAttribute("key")) {
                d.keyValue = attrs.value("key").toString();
            }
            if (attrs.hasAttribute("category")) {
                d.categoryObjNameValue = attrs.value("category").toString();
            }
            if (attrs.hasAttribute("pannel")) {
                d.pannelObjNameValue = attrs.value("pannel").toString();
            }
            if (attrs.hasAttribute("row-prop")) {
                v = xml->attributes().value("row-prop").toInt(&isOk);
                if (isOk) {
                    d.actionRowProportionValue = static_cast< SARibbonPannelItem::RowProportion >(v);
                }
            }
            d.setActionsManager(mgr);
            res.append(d);
        }
        xml->readNext();
    }
    if (xml->hasError()) {
        qWarning() << xml->errorString();
    }
    return (res);
}

int sa_customize_datas_apply(const QList< SARibbonCustomizeData >& cds, SARibbonMainWindow* w)
{
    int c = 0;

    for (const SARibbonCustomizeData& d : cds) {
        if (d.apply(w)) {
            ++c;
        }
    }
    return (c);
}

bool sa_apply_customize_from_xml_file(const QString& filePath, SARibbonMainWindow* w, SARibbonActionsManager* mgr)
{
    QFile f(filePath);

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return (false);
    }
    f.seek(0);
    QXmlStreamReader xml(&f);

    return (SARibbonCustomizeWidget::fromXml(&xml, w, mgr));
}

/**
 * @brief ����SARibbonCustomizeWidget��Ui
 */
class SARibbonCustomizeWidgetUi
{
public:
    QHBoxLayout* horizontalLayoutMain;
    QVBoxLayout* verticalLayoutSelect;
    QLabel* labelSelectAction;
    QHBoxLayout* horizontalLayoutSearch;
    QComboBox* comboBoxActionIndex;
    QLineEdit* lineEditSearchAction;
    QListView* listViewSelect;
    QVBoxLayout* verticalLayoutMidButtons;
    QSpacerItem* verticalSpacerUp;
    QPushButton* pushButtonAdd;
    QPushButton* pushButtonDelete;
    QPushButton* pushButtonReset;
    QSpacerItem* verticalSpacerDown;
    QLabel* labelProportion;
    QComboBox* comboBoxActionProportion;
    QVBoxLayout* verticalLayoutResult;
    QLabel* labelCustomize;
    QHBoxLayout* horizontalLayoutCategorySelect;
    QRadioButton* radioButtonMainCategory;
    QRadioButton* radioButtonAllCategory;
    QButtonGroup* radioButtonGroup;
    QTreeView* treeViewResult;
    QHBoxLayout* horizontalLayoutActionOptBtns;
    QPushButton* pushButtonNewCategory;
    QPushButton* pushButtonNewPannel;
    QPushButton* pushButtonRename;
    QVBoxLayout* verticalLayoutRightButtons;
    QSpacerItem* verticalSpacerUp2;
    QToolButton* toolButtonUp;
    QToolButton* toolButtonDown;
    QSpacerItem* verticalSpacerDown2;

    void setupUi(QWidget* customizeWidget)
    {
        if (customizeWidget->objectName().isEmpty()) {
            customizeWidget->setObjectName(QStringLiteral("SARibbonCustomizeWidget"));
        }
        customizeWidget->resize(800, 600);
        horizontalLayoutMain = new QHBoxLayout(customizeWidget);
        horizontalLayoutMain->setObjectName(QStringLiteral("horizontalLayoutMain"));
        verticalLayoutSelect = new QVBoxLayout();
        verticalLayoutSelect->setObjectName(QStringLiteral("verticalLayoutSelect"));
        labelSelectAction = new QLabel(customizeWidget);
        labelSelectAction->setObjectName(QStringLiteral("labelSelectAction"));

        verticalLayoutSelect->addWidget(labelSelectAction);

        horizontalLayoutSearch = new QHBoxLayout();
        horizontalLayoutSearch->setObjectName(QStringLiteral("horizontalLayoutSearch"));
        comboBoxActionIndex = new QComboBox(customizeWidget);
        comboBoxActionIndex->setObjectName(QStringLiteral("comboBoxActionIndex"));
        comboBoxActionIndex->setEditable(false);

        horizontalLayoutSearch->addWidget(comboBoxActionIndex);

        lineEditSearchAction = new QLineEdit(customizeWidget);
        lineEditSearchAction->setObjectName(QStringLiteral("lineEditSearchAction"));

        horizontalLayoutSearch->addWidget(lineEditSearchAction);

        verticalLayoutSelect->addLayout(horizontalLayoutSearch);

        listViewSelect = new QListView(customizeWidget);
        listViewSelect->setObjectName(QStringLiteral("listViewSelect"));

        verticalLayoutSelect->addWidget(listViewSelect);

        horizontalLayoutMain->addLayout(verticalLayoutSelect);

        verticalLayoutMidButtons = new QVBoxLayout();
        verticalLayoutMidButtons->setObjectName(QStringLiteral("verticalLayoutMidButtons"));
        verticalSpacerUp = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutMidButtons->addItem(verticalSpacerUp);

        pushButtonAdd = new QPushButton(customizeWidget);
        pushButtonAdd->setObjectName(QStringLiteral("pushButtonAdd"));
        pushButtonAdd->setEnabled(false);

        verticalLayoutMidButtons->addWidget(pushButtonAdd);

        pushButtonDelete = new QPushButton(customizeWidget);
        pushButtonDelete->setObjectName(QStringLiteral("pushButtonDelete"));
        pushButtonDelete->setEnabled(false);

        verticalLayoutMidButtons->addWidget(pushButtonDelete);

        verticalSpacerDown = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutMidButtons->addItem(verticalSpacerDown);

        labelProportion = new QLabel(customizeWidget);
        labelProportion->setObjectName(QStringLiteral("labelProportion"));
        verticalLayoutMidButtons->addWidget(labelProportion);

        comboBoxActionProportion = new QComboBox(customizeWidget);
        comboBoxActionProportion->setObjectName(QStringLiteral("comboBoxActionProportion"));
        comboBoxActionProportion->setEditable(false);
        verticalLayoutMidButtons->addWidget(comboBoxActionProportion);
        horizontalLayoutMain->addLayout(verticalLayoutMidButtons);

        verticalLayoutResult = new QVBoxLayout();
        verticalLayoutResult->setObjectName(QStringLiteral("verticalLayoutResult"));
        labelCustomize = new QLabel(customizeWidget);
        labelCustomize->setObjectName(QStringLiteral("labelCustomize"));

        verticalLayoutResult->addWidget(labelCustomize);

        horizontalLayoutCategorySelect = new QHBoxLayout();
        horizontalLayoutCategorySelect->setObjectName(QStringLiteral("horizontalLayoutCategorySelect"));
        radioButtonMainCategory = new QRadioButton(customizeWidget);
        radioButtonMainCategory->setObjectName(QStringLiteral("radioButtonMainCategory"));
        radioButtonMainCategory->setChecked(false);

        horizontalLayoutCategorySelect->addWidget(radioButtonMainCategory);

        radioButtonAllCategory = new QRadioButton(customizeWidget);
        radioButtonAllCategory->setObjectName(QStringLiteral("radioButtonAllCategory"));
        radioButtonAllCategory->setChecked(true);

        horizontalLayoutCategorySelect->addWidget(radioButtonAllCategory);

        radioButtonGroup = new QButtonGroup(customizeWidget);
        radioButtonGroup->addButton(radioButtonMainCategory);
        radioButtonGroup->addButton(radioButtonAllCategory);

        verticalLayoutResult->addLayout(horizontalLayoutCategorySelect);

        treeViewResult = new QTreeView(customizeWidget);
        treeViewResult->setObjectName(QStringLiteral("treeViewResult"));
        treeViewResult->setHeaderHidden(true);
        treeViewResult->setSelectionMode(QAbstractItemView::SingleSelection);
        treeViewResult->setAnimated(true);                                   //֧�ֶ���
        treeViewResult->setEditTriggers(QAbstractItemView::NoEditTriggers);  //������ֱ����item��������

        verticalLayoutResult->addWidget(treeViewResult);

        horizontalLayoutActionOptBtns = new QHBoxLayout();
        horizontalLayoutActionOptBtns->setObjectName(QStringLiteral("horizontalLayoutActionOptBtns"));
        pushButtonNewCategory = new QPushButton(customizeWidget);
        pushButtonNewCategory->setObjectName(QStringLiteral("pushButtonNewCategory"));

        horizontalLayoutActionOptBtns->addWidget(pushButtonNewCategory);

        pushButtonNewPannel = new QPushButton(customizeWidget);
        pushButtonNewPannel->setObjectName(QStringLiteral("pushButtonNewPannel"));

        horizontalLayoutActionOptBtns->addWidget(pushButtonNewPannel);

        pushButtonRename = new QPushButton(customizeWidget);
        pushButtonRename->setObjectName(QStringLiteral("pushButtonRename"));

        horizontalLayoutActionOptBtns->addWidget(pushButtonRename);

        pushButtonReset = new QPushButton(customizeWidget);
        pushButtonReset->setObjectName(QStringLiteral("pushButtonReset"));
        horizontalLayoutActionOptBtns->addWidget(pushButtonReset);

        verticalLayoutResult->addLayout(horizontalLayoutActionOptBtns);

        horizontalLayoutMain->addLayout(verticalLayoutResult);

        verticalLayoutRightButtons = new QVBoxLayout();
        verticalLayoutRightButtons->setObjectName(QStringLiteral("verticalLayoutRightButtons"));
        verticalSpacerUp2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutRightButtons->addItem(verticalSpacerUp2);

        toolButtonUp = new QToolButton(customizeWidget);
        toolButtonUp->setObjectName(QStringLiteral("pushButtonUp"));
        toolButtonUp->setArrowType(Qt::UpArrow);
        toolButtonUp->setAutoRaise(true);

        verticalLayoutRightButtons->addWidget(toolButtonUp);

        toolButtonDown = new QToolButton(customizeWidget);
        toolButtonDown->setObjectName(QStringLiteral("pushButtonDown"));
        toolButtonDown->setArrowType(Qt::DownArrow);
        toolButtonDown->setAutoRaise(true);

        verticalLayoutRightButtons->addWidget(toolButtonDown);

        verticalSpacerDown2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayoutRightButtons->addItem(verticalSpacerDown2);

        horizontalLayoutMain->addLayout(verticalLayoutRightButtons);

        retranslateUi(customizeWidget);
    }  // setupUi

    void retranslateUi(QWidget* customizeWidget)
    {
        customizeWidget->setWindowTitle(QApplication::translate("SARibbonCustomizeWidget", "Customize Widget", Q_NULLPTR));
        labelSelectAction->setText(QApplication::translate("SARibbonCustomizeWidget", "Please Select", Q_NULLPTR));  // cn:��ѡ��
        lineEditSearchAction->setInputMask(QString());
        lineEditSearchAction->setText(QString());
        lineEditSearchAction->setPlaceholderText(QApplication::translate("SARibbonCustomizeWidget", "Find Command", Q_NULLPTR));  // cn:��������
        pushButtonAdd->setText(QApplication::translate("SARibbonCustomizeWidget", "Add >>", Q_NULLPTR));  // cn:��� >>
        pushButtonDelete->setText(QApplication::translate("SARibbonCustomizeWidget", "<< Remove", Q_NULLPTR));  // cn:<< �Ƴ�
        labelCustomize->setText(QApplication::translate("SARibbonCustomizeWidget", "Customize the Ribbon", Q_NULLPTR));  // cn:�Զ��幦����
        radioButtonMainCategory->setText(QApplication::translate("SARibbonCustomizeWidget", "Main Category", Q_NULLPTR));  // cn:��ѡ�
        radioButtonAllCategory->setText(QApplication::translate("SARibbonCustomizeWidget", "All Category", Q_NULLPTR));  // cn:����ѡ�
        pushButtonNewCategory->setText(QApplication::translate("SARibbonCustomizeWidget", "New Category", Q_NULLPTR));  // cn:�½�ѡ�
        pushButtonNewPannel->setText(QApplication::translate("SARibbonCustomizeWidget", "New Group", Q_NULLPTR));  // cn:�½���
        pushButtonRename->setText(QApplication::translate("SARibbonCustomizeWidget", "Rename", Q_NULLPTR));  // cn:������
        pushButtonReset->setText(QApplication::translate("SARibbonCustomizeWidget", "reset", Q_NULLPTR));  // cn:����
        labelProportion->setText(QApplication::translate("SARibbonCustomizeWidget", "proportion:", Q_NULLPTR));  // cn:����
    }  // retranslateUi
};

/**
 * @brief ����SARibbonCustomizeWidget��ҵ���߼�
 */
class SARibbonCustomizeWidget::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonCustomizeWidget)
public:
    SARibbonCustomizeWidget::RibbonTreeShowType mShowType { SARibbonCustomizeWidget::ShowAllCategory };  ///< ��ʾ����
    SARibbonMainWindow* mRibbonWindow { nullptr };         ///< ����SARibbonMainWindow��ָ��
    SARibbonActionsManager* mActionMgr { nullptr };        ///< action������
    SARibbonActionsManagerModel* mAcionModel { nullptr };  ///< action��������Ӧ��model
    QStandardItemModel* mRibbonModel { nullptr };          ///< ���ںܳ�ribbon����
    int mCustomizeCategoryCount { 0 };                     ///< ��¼�Զ���Category�ĸ���
    int mCustomizePannelCount { 0 };                       ///< ��¼�Զ���Pannel�ĸ���
public:
    PrivateData(SARibbonCustomizeWidget* p);
    void updateModel();

    QList< SARibbonCustomizeData > mCustomizeDatas;     ///< ��¼���е��Զ��嶯��
    QList< SARibbonCustomizeData > mOldCustomizeDatas;  ///< ��¼�ɵ��Զ��嶯��
    //����һ�����id�����磺pre_QDateTime::currentMSecsSinceEpoch_suf
    static QString makeRandomObjName(const QString& pre);

    int itemLevel(QStandardItem* item) const;

    //
    bool isCustomizeItem(QStandardItem* item) const;

    //��itemת��Ϊcategory
    SARibbonCategory* itemToCategory(QStandardItem* item) const;

    //��itemת��ΪSARibbonPannel
    SARibbonPannel* itemToPannel(QStandardItem* item) const;

    //��ȡitem��Ӧ��object name
    QString itemObjectName(QStandardItem* item) const;

    //�ж��Ƿ�����Զ���
    bool isItemCanCustomize(QStandardItem* item) const;

    //��itemתΪaction
    QAction* itemToAction(QStandardItem* item) const;
};

SARibbonCustomizeWidget::PrivateData::PrivateData(SARibbonCustomizeWidget* p)
    : q_ptr(p), mAcionModel(new SARibbonActionsManagerModel(p)), mRibbonModel(new QStandardItemModel(p))
{
}

void SARibbonCustomizeWidget::PrivateData::updateModel()
{
    if (mRibbonWindow == nullptr) {
        return;
    }
    mRibbonModel->clear();
    SARibbonBar* ribbonbar               = mRibbonWindow->ribbonBar();
    QList< SARibbonCategory* > categorys = ribbonbar->categoryPages();

    for (const SARibbonCategory* c : qAsConst(categorys)) {
        if ((mShowType == SARibbonCustomizeWidget::ShowMainCategory) && c->isContextCategory()) {
            //�����ֻ��ʾ�����ݣ�����������ı�ǩ�ͺ���
            continue;
        }
        QStandardItem* ci = new QStandardItem();
        if (c->isContextCategory()) {
            ci->setText(QString("[%1]").arg(c->windowTitle()));
        } else {
            ci->setText(c->windowTitle());
        }
        if (c->isCanCustomize() && !c->isContextCategory()) {
            //�����ı�ǩ������ʾ���ش���
            ci->setCheckable(true);
            ci->setCheckState(ribbonbar->isCategoryVisible(c) ? Qt::Checked : Qt::Unchecked);
            ci->setData(true, SARibbonCustomizeWidget::CanCustomizeRole);  //�������ǿ����Զ����
        }
        ci->setData(0, SARibbonCustomizeWidget::LevelRole);
        ci->setData(QVariant::fromValue< qintptr >(qintptr(c)), SARibbonCustomizeWidget::PointerRole);
        QList< SARibbonPannel* > pannels = c->pannelList();
        for (const SARibbonPannel* p : qAsConst(pannels)) {
            QStandardItem* pi = new QStandardItem(p->windowTitle());
            pi->setData(1, SARibbonCustomizeWidget::LevelRole);
            pi->setData(QVariant::fromValue< qintptr >(qintptr(p)), SARibbonCustomizeWidget::PointerRole);
            if (p->isCanCustomize()) {
                pi->setData(true, SARibbonCustomizeWidget::CanCustomizeRole);  //�������ǿ����Զ����
            }
            ci->appendRow(pi);
            const QList< SARibbonPannelItem* >& items = p->ribbonPannelItem();
            for (SARibbonPannelItem* i : qAsConst(items)) {
                if (i->action->isSeparator()) {
                    continue;
                }
                QStandardItem* ii = new QStandardItem();
                if (i->customWidget) {
                    //������Զ��崰��
                    if (i->widget()->windowTitle().isEmpty() && i->widget()->windowIcon().isNull()) {
                        delete ii;
                        continue;  //�������ɶҲû�У�������
                    }
                    ii->setText(i->widget()->windowTitle());
                    ii->setIcon(i->widget()->windowIcon());
                    if (SARibbonCustomizeData::isCanCustomize(i->widget())) {
                        ii->setData(true, SARibbonCustomizeWidget::CanCustomizeRole);  //�������ǿ����Զ����
                    }
                } else {
                    //�����Զ��壬˵����action
                    ii->setText(i->action->text());
                    ii->setIcon(i->action->icon());
                    if (SARibbonCustomizeData::isCanCustomize(i->action)) {
                        ii->setData(true, SARibbonCustomizeWidget::CanCustomizeRole);  //�������ǿ����Զ����
                    }
                }
                ii->setData(2, SARibbonCustomizeWidget::LevelRole);
                ii->setData(QVariant::fromValue< qintptr >(qintptr(i)), SARibbonCustomizeWidget::PointerRole);
                pi->appendRow(ii);
            }
        }
        mRibbonModel->appendRow(ci);
    }
}

/**
 * @brief ����һ�����id�����磺pre_QDateTime::currentMSecsSinceEpoch
 * @param pre ǰ׺
 * @return
 */
QString SARibbonCustomizeWidget::PrivateData::makeRandomObjName(const QString& pre)
{
    return (QString("%1_%2").arg(pre).arg(QDateTime::currentMSecsSinceEpoch()));
}

/**
 * @brief ��ȡitem��level
 * @param item
 * @return
 */
int SARibbonCustomizeWidget::PrivateData::itemLevel(QStandardItem* item) const
{
    return (item->data(SARibbonCustomizeWidget::LevelRole).toInt());
}

/**
 * @brief �ж�itemnΪ�Զ����item���Զ����item������CustomizeRole��ɫ
 * @param item
 * @return
 */
bool SARibbonCustomizeWidget::PrivateData::isCustomizeItem(QStandardItem* item) const
{
    if (nullptr == item) {
        return (false);
    }
    return (item->data(SARibbonCustomizeWidget::CustomizeRole).isValid());
}

/**
 * @brief ��itemת��Ϊcategory
 * @param item
 * @return�޷�ת������nullptr
 */
SARibbonCategory* SARibbonCustomizeWidget::PrivateData::itemToCategory(QStandardItem* item) const
{
    int level = item->data(SARibbonCustomizeWidget::LevelRole).toInt();

    if (level != 0) {
        return (nullptr);
    }
    qintptr p = item->data(SARibbonCustomizeWidget::PointerRole).value< qintptr >();

    return (reinterpret_cast< SARibbonCategory* >(p));
}

/**
 * @brief ��itemת��Ϊpannel
 * @param item
 * @return �޷�ת������nullptr
 */
SARibbonPannel* SARibbonCustomizeWidget::PrivateData::itemToPannel(QStandardItem* item) const
{
    int level = item->data(SARibbonCustomizeWidget::LevelRole).toInt();

    if (level != 1) {
        return (nullptr);
    }
    qintptr p = item->data(SARibbonCustomizeWidget::PointerRole).value< qintptr >();

    return (reinterpret_cast< SARibbonPannel* >(p));
}

/**
 * @brief ��ȡitem��Ӧ��objectname
 * @param item
 * @return ����޷���ȡ������һ���յ�QString
 */
QString SARibbonCustomizeWidget::PrivateData::itemObjectName(QStandardItem* item) const
{
    QString objName;

    if (isCustomizeItem(item)) {
        //˵�����Զ����
        objName = item->data(SARibbonCustomizeWidget::CustomizeObjNameRole).toString();
    } else {
        //˵������Ƿ��Զ����
        int level = itemLevel(item);
        if (0 == level) {
            SARibbonCategory* category = itemToCategory(item);
            if (category) {
                objName = category->objectName();
            }
        } else if (1 == level) {
            SARibbonPannel* pannel = itemToPannel(item);
            if (pannel) {
                objName = pannel->objectName();
            }
        }
    }
    return (objName);
}

/**
 * @brief �ж�item�Ƿ���Զ���
 * @param item
 * @return
 */
bool SARibbonCustomizeWidget::PrivateData::isItemCanCustomize(QStandardItem* item) const
{
    if (nullptr == item) {
        return (false);
    }
    QVariant v = item->data(SARibbonCustomizeWidget::CanCustomizeRole);

    if (v.isValid()) {
        return (v.toBool());
    }
    return (false);
}

/**
 * @brief ��item תΪaction
 * @param item
 * @return
 */
QAction* SARibbonCustomizeWidget::PrivateData::itemToAction(QStandardItem* item) const
{
    if (2 != itemLevel(item)) {
        return (nullptr);
    }
    //����Ҫ�ǳ�ע�⣬SARibbonCustomizeWidget::CustomizeRoleΪtrueʱ��˵��������Զ�������ݣ�
    //��ʱPointerRole���ŵ���actionָ�룬����SARibbonPannelItem
    QAction* act = nullptr;

    if (item->data(SARibbonCustomizeWidget::CustomizeRole).toBool()) {
        act = reinterpret_cast< QAction* >(item->data(SARibbonCustomizeWidget::PointerRole).value< qintptr >());
    } else {
        SARibbonPannelItem* pi = reinterpret_cast< SARibbonPannelItem* >(
                item->data(SARibbonCustomizeWidget::PointerRole).value< qintptr >());
        act = (pi->action);
    }
    return (act);
}

//===================================================
// SARibbonCustomizeWidget
//===================================================
/**
 * @brief SARibbonCustomizeWidget::SARibbonCustomizeWidget
 * @param ribbonWindow ������Ҫ�����SARibbonMainWindowָ��
 * @param parent ���ڽ������ɵ�parent�����Ժ�SARibbonMainWindowһ��
 * @param f ͬQWidget::QWidget�ĵڶ�������
 */
SARibbonCustomizeWidget::SARibbonCustomizeWidget(SARibbonMainWindow* ribbonWindow, QWidget* parent, Qt::WindowFlags f)
    : QWidget(parent, f), ui(new SARibbonCustomizeWidgetUi), d_ptr(new SARibbonCustomizeWidget::PrivateData(this))
{
    d_ptr->mRibbonWindow = ribbonWindow;

    ui->setupUi(this);
    ui->listViewSelect->setModel(d_ptr->mAcionModel);
    ui->treeViewResult->setModel(d_ptr->mRibbonModel);
    initConnection();
    updateModel();
}

SARibbonCustomizeWidget::~SARibbonCustomizeWidget()
{
    delete ui;
}

void SARibbonCustomizeWidget::initConnection()
{
    //    �����Ҫqt5.8����֧��
    //    connect(ui->comboBoxActionIndex, QOverload<int>::of(&QComboBox::currentIndexChanged)
    //        , this, &SARibbonCustomizeWidget::onComboBoxActionIndexCurrentIndexChanged);
    connect(ui->comboBoxActionIndex,
            static_cast< void (QComboBox::*)(int) >(&QComboBox::currentIndexChanged),
            this,
            &SARibbonCustomizeWidget::onComboBoxActionIndexCurrentIndexChanged);
    //    �����Ҫqt5.8����֧��
    //    connect(ui->radioButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked)
    //        , this, &SARibbonCustomizeWidget::onRadioButtonGroupButtonClicked);
    connect(ui->radioButtonGroup,
            static_cast< void (QButtonGroup::*)(QAbstractButton*) >(&QButtonGroup::buttonClicked),
            this,
            &SARibbonCustomizeWidget::onRadioButtonGroupButtonClicked);
    connect(ui->pushButtonNewCategory, &QPushButton::clicked, this, &SARibbonCustomizeWidget::onPushButtonNewCategoryClicked);
    connect(ui->pushButtonNewPannel, &QPushButton::clicked, this, &SARibbonCustomizeWidget::onPushButtonNewPannelClicked);
    connect(ui->pushButtonRename, &QPushButton::clicked, this, &SARibbonCustomizeWidget::onPushButtonRenameClicked);
    connect(ui->pushButtonAdd, &QPushButton::clicked, this, &SARibbonCustomizeWidget::onPushButtonAddClicked);
    connect(ui->pushButtonDelete, &QPushButton::clicked, this, &SARibbonCustomizeWidget::onPushButtonDeleteClicked);
    connect(ui->listViewSelect, &QAbstractItemView::clicked, this, &SARibbonCustomizeWidget::onListViewSelectClicked);
    connect(ui->treeViewResult, &QAbstractItemView::clicked, this, &SARibbonCustomizeWidget::onTreeViewResultClicked);
    connect(ui->toolButtonUp, &QToolButton::clicked, this, &SARibbonCustomizeWidget::onToolButtonUpClicked);
    connect(ui->toolButtonDown, &QToolButton::clicked, this, &SARibbonCustomizeWidget::onToolButtonDownClicked);
    connect(d_ptr->mRibbonModel, &QStandardItemModel::itemChanged, this, &SARibbonCustomizeWidget::onItemChanged);
    connect(ui->lineEditSearchAction, &QLineEdit::textEdited, this, &SARibbonCustomizeWidget::onLineEditSearchActionTextEdited);
    connect(ui->pushButtonReset, &QPushButton::clicked, this, &SARibbonCustomizeWidget::onPushButtonResetClicked);
}

/**
 * @brief ����action������
 * @param mgr
 */
void SARibbonCustomizeWidget::setupActionsManager(SARibbonActionsManager* mgr)
{
    d_ptr->mActionMgr = mgr;
    if (d_ptr->mActionMgr) {
        d_ptr->mAcionModel->uninstallActionsManager();
    }
    d_ptr->mAcionModel->setupActionsManager(mgr);
    //������߸�ѡ��
    QList< int > tags = mgr->actionTags();

    ui->comboBoxActionIndex->clear();
    for (int tag : qAsConst(tags)) {
        ui->comboBoxActionIndex->addItem(mgr->tagName(tag), tag);
    }
}

bool SARibbonCustomizeWidget::isChanged() const
{
    return (d_ptr->mCustomizeDatas.size() > 0);
}

/**
 * @brief ��ȡmodel
 * @return
 */
const QStandardItemModel* SARibbonCustomizeWidget::model() const
{
    return (d_ptr->mRibbonModel);
}

/**
 * @brief ���ݵ�ǰ��radiobuttonѡ��������model
 */
void SARibbonCustomizeWidget::updateModel()
{
    updateModel(ui->radioButtonAllCategory->isChecked() ? ShowAllCategory : ShowMainCategory);
    if (d_ptr->mRibbonWindow) {
        SARibbonBar* bar = d_ptr->mRibbonWindow->ribbonBar();
        if (bar) {
            ui->comboBoxActionProportion->clear();
            if (bar->isTwoRowStyle()) {
                ui->comboBoxActionProportion->addItem(tr("large"), SARibbonPannelItem::Large);
                ui->comboBoxActionProportion->addItem(tr("small"), SARibbonPannelItem::Small);
            } else {
                ui->comboBoxActionProportion->addItem(tr("large"), SARibbonPannelItem::Large);
                ui->comboBoxActionProportion->addItem(tr("medium"), SARibbonPannelItem::Medium);
                ui->comboBoxActionProportion->addItem(tr("small"), SARibbonPannelItem::Small);
            }
        }
    }
}

/**
 * @brief ����model
 */
void SARibbonCustomizeWidget::updateModel(RibbonTreeShowType type)
{
    d_ptr->mShowType = type;
    d_ptr->updateModel();
}

/**
 * @brief Ӧ�������趨
 * @return Ӧ�óɹ�����true
 * @note �����趨��һ��Ӧ�óɹ����᷵��true
 */
bool SARibbonCustomizeWidget::applys()
{
    simplify();
    return (sa_customize_datas_apply(d_ptr->mCustomizeDatas, d_ptr->mRibbonWindow) > 0);
}

/**
 * @brief ת��Ϊxml
 *
 * �˺�������дelement������дdocument������ݣ���������Ҫдdocument��
 * ��Ҫ�ڴ˺���ǰ����QXmlStreamWriter::writeStartDocument(),�ڴ˺��������QXmlStreamWriter::writeEndDocument()
 *
 * @note ע�⣬�ڴ���QXmlStreamWriter֮ǰ����Ҫ���ñ���Ϊutf-8:xml->setCodec("utf-8");
 * @note ����QXmlStreamWriter��QString��Ϊioʱ���ǲ�֧�ֱ���ģ��������޷���֤�Զ�����̲����������ַ���
 * ��ˣ�QXmlStreamWriter��Ӧ��ͨ��QString���й��죬�����Ҫ�õ�string��Ҳ��Ҫͨ��QByteArray���죬�磺
 * @code
 * SARibbonCustomizeDialog dlg(this);//thisΪSARibbonMainWindow�Ĵ���
 * dlg.setupActionsManager(m_actMgr);
 * if (SARibbonCustomizeDialog::Accepted == dlg.exec()) {
 *    dlg.applys();
 *    QByteArray str;
 *    QXmlStreamWriter xml(&str);//QXmlStreamWriter������ͨ��QString���죬�������Ļ��쳣
 *    xml.setAutoFormatting(true);
 *    xml.setAutoFormattingIndent(2);
 *    xml.setCodec("utf-8");//��writeStartDocument֮ǰָ������
 *    xml.writeStartDocument();
 *    bool isok = dlg.toXml(&xml);
 *    xml.writeEndDocument();
 *    if (isok) {
 *        QFile f("customize.xml");
 *        if (f.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate)) {
 *            QTextStream s(&f);
 *            s.setCodec("utf-8");//ָ���������
 *            s << str;
 *            s.flush();
 *        }
 *        m_edit->append("write xml:");//m_edit�Ķ���Ϊ��QTextEdit *m_edit;
 *        m_edit->append(str);
 *    }
 * }
 * @endcode
 * @return ��������쳣������false,���û���Զ�������Ҳ�᷵��false
 * @see sa_customize_datas_to_xml
 */
bool SARibbonCustomizeWidget::toXml(QXmlStreamWriter* xml) const
{
    QList< SARibbonCustomizeData > res;

    res = d_ptr->mOldCustomizeDatas + d_ptr->mCustomizeDatas;
    res = SARibbonCustomizeData::simplify(res);
    return (sa_customize_datas_to_xml(xml, res));
}

/**
 * @brief ������д���ļ���
 * @param xmlpath
 * @return
 */
bool SARibbonCustomizeWidget::toXml(const QString& xmlpath) const
{
    QFile f(xmlpath);

    if (!f.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        return (false);
    }
    QXmlStreamWriter xml(&f);

    xml.setAutoFormatting(true);
    xml.setAutoFormattingIndent(2);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)  // QXmlStreamWriter always encodes XML in UTF-8.
    xml.setCodec("utf-8");                  //��writeStartDocument֮ǰָ������
#endif
    xml.writeStartDocument();
    bool isOK = toXml(&xml);

    xml.writeEndDocument();
    f.close();
    return (isOK);
}

/**
 * @brief ��xml�м���QList<SARibbonCustomizeData>
 *
 * ���ڻ��������ļ������ã��Ի�����ʾǰ������ô˺�������֤�������õ���ȷ��¼
 * @param xml
 * @return
 * @note �˺���Ҫ��@ref setupActionsManager ����֮�����
 */
void SARibbonCustomizeWidget::fromXml(QXmlStreamReader* xml)
{
    QList< SARibbonCustomizeData > cds = sa_customize_datas_from_xml(xml, d_ptr->mActionMgr);

    d_ptr->mOldCustomizeDatas = cds;
}

/**
 * @brief ��xml�м���QList<SARibbonCustomizeData>
 *
 * ���ڻ��������ļ������ã��Ի�����ʾǰ������ô˺�������֤�������õ���ȷ��¼
 * @param xmlpath
 * @note �˺���Ҫ��@ref setupActionsManager ����֮�����
 * @note �������������������Զ������ã��ٵ��ô˴���ʱ��Ҫ���ô˺�������ԭ�������ü��ؽ�����
 * �������¶���ʱ��Ѿɶ������棬���ڵ���applysʱ������ô˼��صĶ���
 */
void SARibbonCustomizeWidget::fromXml(const QString& xmlpath)
{
    QFile f(xmlpath);

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    f.seek(0);
    QXmlStreamReader xml(&f);

    fromXml(&xml);
}

/**
 * @brief Ӧ��xml����
 *
 * @note �ظ�����һ�������ļ��ᷢ���쳣��Ϊ�˱�������¼�������һ��ͨ��һ��������ֻ֤����һ�Σ��磺
 * @code
 * //ֻ�ܵ���һ��
 * static bool has_call = false;
 * if (!has_call) {
 *     QFile f("customize.xml");
 *     if (!f.open(QIODevice::ReadWrite|QIODevice::Text)) {
 *         return;
 *     }
 *     f.seek(0);
 *     QXmlStreamReader xml(&f);
 *     has_call = SARibbonCustomizeWidget::fromXml(&xml, this, m_actMgr);
 * }
 * @endcode
 * @param xml
 * @param w
 * @return �����趨��һ��Ӧ�óɹ����᷵��true
 * @see sa_customize_datas_from_xml sa_customize_datas_apply sa_apply_customize_from_xml_file
 */
bool SARibbonCustomizeWidget::fromXml(QXmlStreamReader* xml, SARibbonMainWindow* w, SARibbonActionsManager* mgr)
{
    //���ҵ�sa-ribbon-customize��ǩ
    QList< SARibbonCustomizeData > cds = sa_customize_datas_from_xml(xml, mgr);

    return (sa_customize_datas_apply(cds, w) > 0);
}

/**
 * @brief ������ж���
 *
 * ��ִ��applys���������Ҫ�������ã�Ӧ��clear������ᵼ���쳣
 */
void SARibbonCustomizeWidget::clear()
{
    d_ptr->mCustomizeDatas.clear();
}

/**
 * @brief ����
 */
void SARibbonCustomizeWidget::simplify()
{
    d_ptr->mCustomizeDatas = SARibbonCustomizeData::simplify(d_ptr->mCustomizeDatas);
}

/**
 * @brief ��ȡ��ǰ����ѡ�е�������
 * @return
 */
SARibbonPannelItem::RowProportion SARibbonCustomizeWidget::selectedRowProportion() const
{
    return (static_cast< SARibbonPannelItem::RowProportion >(ui->comboBoxActionProportion->currentData().toInt()));
}

/**
 * @brief ��ȡlistview��ѡ�е�action
 * @return ���û��ѡ��action������nullptr
 * @note ���Ҫ��ȡtreeviewѡ�е�action��ʹ��@ref itemToAction ����
 */
QAction* SARibbonCustomizeWidget::selectedAction() const
{
    QItemSelectionModel* m = ui->listViewSelect->selectionModel();

    if ((nullptr == m) || !m->hasSelection()) {
        return (nullptr);
    }
    QModelIndex i = m->currentIndex();

    return (d_ptr->mAcionModel->indexToAction(i));
}

/**
 * @brief ��itemת��Ϊaction
 * @param item
 * @return ���û��action��ת��������nullptr
 */
QAction* SARibbonCustomizeWidget::itemToAction(QStandardItem* item) const
{
    return (d_ptr->itemToAction(item));
}

/**
 * @brief ��ȡribbon treeѡ�е�item
 * @return
 */
QStandardItem* SARibbonCustomizeWidget::selectedItem() const
{
    QItemSelectionModel* m = ui->treeViewResult->selectionModel();

    if ((nullptr == m) || !m->hasSelection()) {
        return (nullptr);
    }
    QModelIndex i = m->currentIndex();

    return (d_ptr->mRibbonModel->itemFromIndex(i));
}

/**
 * @brief ��ȡѡ�е�ribbon tree ��level
 * @return -1Ϊѡ���쳣��0����ѡ����category 1����ѡ����pannel 2����ѡ����action
 */
int SARibbonCustomizeWidget::selectedRibbonLevel() const
{
    QStandardItem* item = selectedItem();

    if (item) {
        return (itemLevel(item));
    }
    return (-1);
}

/**
 * @brief ��ȡStandardItem ��level
 * @param item
 * @return
 */
int SARibbonCustomizeWidget::itemLevel(QStandardItem* item) const
{
    return (d_ptr->itemLevel(item));
}

/**
 * @brief ����ĳ��item��ѡ��
 * @param item
 */
void SARibbonCustomizeWidget::setSelectItem(QStandardItem* item, bool ensureVisible)
{
    QItemSelectionModel* m = ui->treeViewResult->selectionModel();

    if (nullptr == m) {
        return;
    }
    if (m) {
        m->clearSelection();
        m->select(item->index(), QItemSelectionModel::Select);
    }
    if (ensureVisible) {
        ui->treeViewResult->scrollTo(item->index());
    }
}

/**
 * @brief �ж�itemn�ܷ�Ķ������ԸĶ�����true
 * @param item
 * @return
 */
bool SARibbonCustomizeWidget::isItemCanCustomize(QStandardItem* item) const
{
    return (d_ptr->isItemCanCustomize(item));
}

bool SARibbonCustomizeWidget::isSelectedItemCanCustomize() const
{
    return (isItemCanCustomize(selectedItem()));
}

/**
 * @brief �ж�itemn�ܷ�Ķ������ԸĶ�����true
 * @param item
 * @return
 */
bool SARibbonCustomizeWidget::isCustomizeItem(QStandardItem* item) const
{
    return (d_ptr->isCustomizeItem(item));
}

bool SARibbonCustomizeWidget::isSelectedItemIsCustomize() const
{
    return (isCustomizeItem(selectedItem()));
}

void SARibbonCustomizeWidget::removeItem(QStandardItem* item)
{
    if (item->parent()) {
        item->parent()->removeRow(item->row());
    } else {
        d_ptr->mRibbonModel->removeRow(item->row());
    }
}

void SARibbonCustomizeWidget::onComboBoxActionIndexCurrentIndexChanged(int index)
{
    int tag = ui->comboBoxActionIndex->itemData(index).toInt();

    d_ptr->mAcionModel->setFilter(tag);
}

void SARibbonCustomizeWidget::onRadioButtonGroupButtonClicked(QAbstractButton* b)
{
    updateModel(b == ui->radioButtonAllCategory ? ShowAllCategory : ShowMainCategory);
}

void SARibbonCustomizeWidget::onPushButtonNewCategoryClicked()
{
    int row                = d_ptr->mRibbonModel->rowCount();
    QItemSelectionModel* m = ui->treeViewResult->selectionModel();

    if (m && m->hasSelection()) {
        QModelIndex i = m->currentIndex();
        while (i.parent().isValid()) {
            i = i.parent();
        }
        //��ȡѡ�е����item
        row = i.row() + 1;
    }
    QStandardItem* ni = new QStandardItem(tr("new category[customize]%1").arg(++(d_ptr->mCustomizeCategoryCount)));

    ni->setData(0, SARibbonCustomizeWidget::LevelRole);
    d_ptr->mRibbonModel->insertRow(row, ni);
    //����������Ϊѡ��
    setSelectItem(ni);
    //�Ѷ������붯���б���
    SARibbonCustomizeData d = SARibbonCustomizeData::makeAddCategoryCustomizeData(ni->text(),
                                                                                  ni->row(),
                                                                                  SARibbonCustomizeWidget::PrivateData::makeRandomObjName(
                                                                                          "category"));

    d_ptr->mCustomizeDatas.append(d);
    ni->setData(true, SARibbonCustomizeWidget::CanCustomizeRole);  //��CustomizeRole������CanCustomizeRole
    ni->setData(true, SARibbonCustomizeWidget::CustomizeRole);
    ni->setData(d.categoryObjNameValue, SARibbonCustomizeWidget::CustomizeObjNameRole);
}

void SARibbonCustomizeWidget::onPushButtonNewPannelClicked()
{
    QStandardItem* item = selectedItem();

    if (nullptr == item) {
        return;
    }
    int level = selectedRibbonLevel();

    QStandardItem* ni = new QStandardItem(tr("new pannel[customize]%1").arg(++(d_ptr->mCustomizePannelCount)));

    ni->setData(1, SARibbonCustomizeWidget::LevelRole);

    if (0 == level) {
        //˵����category,���뵽���
        item->appendRow(ni);
    } else if (1 == level) {
        //˵��ѡ�����pannel�����뵽��pannel֮��
        QStandardItem* categoryItem = item->parent();
        if (nullptr == categoryItem) {
            return;
        }
        categoryItem->insertRow(item->row() + 1, ni);
    } else {
        //�����Ͼ�ɾ���˳�
        delete ni;
        ni = nullptr;
        return;
    }
    //����category��object name
    QStandardItem* categoryItem = ni->parent();
    QString categoryObjName     = "";

    categoryObjName         = d_ptr->itemObjectName(categoryItem);
    SARibbonCustomizeData d = SARibbonCustomizeData::makeAddPannelCustomizeData(ni->text(),
                                                                                ni->row(),
                                                                                categoryObjName,
                                                                                SARibbonCustomizeWidget::PrivateData::makeRandomObjName(
                                                                                        "pannel"));

    d_ptr->mCustomizeDatas.append(d);
    ni->setData(true, SARibbonCustomizeWidget::CanCustomizeRole);  //��CustomizeRole������CanCustomizeRole
    ni->setData(true, SARibbonCustomizeWidget::CustomizeRole);
    ni->setData(d.pannelObjNameValue, SARibbonCustomizeWidget::CustomizeObjNameRole);
    setSelectItem(ni);
}

void SARibbonCustomizeWidget::onPushButtonRenameClicked()
{
    QStandardItem* item = selectedItem();

    if (nullptr == item) {
        return;
    }
    bool ok;
    QString text = "";

    text = QInputDialog::getText(this, tr("rename"), tr("name:"), QLineEdit::Normal, item->text(), &ok);

    if (!ok || text.isEmpty()) {
        return;
    }
    int level = itemLevel(item);

    if (0 == level) {
        //��Category��
        QString cateObjName     = d_ptr->itemObjectName(item);
        SARibbonCustomizeData d = SARibbonCustomizeData::makeRenameCategoryCustomizeData(text, cateObjName);
        d_ptr->mCustomizeDatas.append(d);
    } else if (1 == level) {
        QString cateObjName     = d_ptr->itemObjectName(item->parent());
        QString pannelObjName   = d_ptr->itemObjectName(item);
        SARibbonCustomizeData d = SARibbonCustomizeData::makeRenamePannelCustomizeData(text, cateObjName, pannelObjName);
        d_ptr->mCustomizeDatas.append(d);
    } else {
        // action ���������
        return;
    }
    item->setText(text);
}

void SARibbonCustomizeWidget::onPushButtonAddClicked()
{
    QAction* act        = selectedAction();
    QStandardItem* item = selectedItem();

    if ((nullptr == act) || (nullptr == item)) {
        return;
    }
    int level = itemLevel(item);

    if (0 == level) {
        //ѡ��category�����в���
        return;
    } else if (2 == level) {
        //ѡ��action����ӵ����action֮��,��item����Ϊpannel
        item = item->parent();
    }
    QString pannelObjName   = d_ptr->itemObjectName(item);
    QString categoryObjName = d_ptr->itemObjectName(item->parent());
    QString key             = d_ptr->mActionMgr->key(act);

    SARibbonCustomizeData d = SARibbonCustomizeData::makeAddActionCustomizeData(key,
                                                                                d_ptr->mActionMgr,
                                                                                selectedRowProportion(),
                                                                                categoryObjName,
                                                                                pannelObjName);

    d_ptr->mCustomizeDatas.append(d);

    QStandardItem* actItem = new QStandardItem(act->icon(), act->text());

    actItem->setData(2, SARibbonCustomizeWidget::LevelRole);
    actItem->setData(true, SARibbonCustomizeWidget::CanCustomizeRole);  //��CustomizeRole������CanCustomizeRole
    actItem->setData(true, SARibbonCustomizeWidget::CustomizeRole);
    actItem->setData(act->objectName(), SARibbonCustomizeWidget::CustomizeObjNameRole);
    actItem->setData(qintptr(act), SARibbonCustomizeWidget::PointerRole);  //��actionָ�봫��
    item->appendRow(actItem);
}

void SARibbonCustomizeWidget::onPushButtonDeleteClicked()
{
    QStandardItem* item = selectedItem();

    if (nullptr == item) {
        return;
    }
    if (!isItemCanCustomize(item)) {
        return;
    }
    int level = itemLevel(item);

    if (0 == level) {
        //ɾ��category
        SARibbonCustomizeData d = SARibbonCustomizeData::makeRemoveCategoryCustomizeData(d_ptr->itemObjectName(item));
        d_ptr->mCustomizeDatas.append(d);
    } else if (1 == level) {
        //ɾ��pannel
        QString catObjName      = d_ptr->itemObjectName(item->parent());
        QString pannelObjName   = d_ptr->itemObjectName(item);
        SARibbonCustomizeData d = SARibbonCustomizeData::makeRemovePannelCustomizeData(catObjName, pannelObjName);
        d_ptr->mCustomizeDatas.append(d);
    } else if (2 == level) {
        //ɾ��Action
        QString catObjName    = d_ptr->itemObjectName(item->parent()->parent());
        QString pannelObjName = d_ptr->itemObjectName(item->parent());
        QAction* act          = itemToAction(item);
        QString key           = d_ptr->mActionMgr->key(act);
        if (key.isEmpty() || catObjName.isEmpty() || pannelObjName.isEmpty()) {
            return;
        }

        SARibbonCustomizeData d = SARibbonCustomizeData::makeRemoveActionCustomizeData(catObjName, pannelObjName, key, d_ptr->mActionMgr);
        d_ptr->mCustomizeDatas.append(d);
    }
    //ִ��ɾ������
    removeItem(item);
    //ɾ��������ʶ��
    ui->pushButtonAdd->setEnabled(selectedAction() && isSelectedItemIsCustomize() && selectedRibbonLevel() > 0);
    ui->pushButtonDelete->setEnabled(isSelectedItemIsCustomize());
}

void SARibbonCustomizeWidget::onListViewSelectClicked(const QModelIndex& index)
{
    //ÿ�ε�����ж��Ƿ���Խ��в���������pushButtonAdd��pushButtonDelete����ʾ״̬
    //�����listview���ж�treeview��״̬
    Q_UNUSED(index);
    ui->pushButtonAdd->setEnabled(isSelectedItemCanCustomize() && selectedRibbonLevel() > 0);
    ui->pushButtonDelete->setEnabled(isSelectedItemCanCustomize());
}

void SARibbonCustomizeWidget::onTreeViewResultClicked(const QModelIndex& index)
{
    Q_UNUSED(index);
    //ÿ�ε�����ж��Ƿ���Խ��в���������pushButtonAdd��pushButtonDelete����ʾ״̬
    QStandardItem* item = selectedItem();

    if (nullptr == item) {
        return;
    }
    int level = itemLevel(item);

    ui->pushButtonAdd->setEnabled(selectedAction() && (level > 0) && isItemCanCustomize(item));
    ui->pushButtonDelete->setEnabled(isItemCanCustomize(item));  //��CustomizeRole������CanCustomizeRole
    ui->pushButtonRename->setEnabled(level != 2 || isItemCanCustomize(item));  // QAction ���ܸ��� �� ��CustomizeRole������CanCustomizeRole
}

void SARibbonCustomizeWidget::onToolButtonUpClicked()
{
    QStandardItem* item = selectedItem();

    if ((nullptr == item) || (0 == item->row())) {
        return;
    }
    int level = itemLevel(item);

    if (0 == level) {
        //�ƶ�category
        SARibbonCustomizeData d = SARibbonCustomizeData::makeChangeCategoryOrderCustomizeData(d_ptr->itemObjectName(item), -1);
        d_ptr->mCustomizeDatas.append(d);
        int r = item->row();
        item  = d_ptr->mRibbonModel->takeItem(r);
        d_ptr->mRibbonModel->removeRow(r);
        d_ptr->mRibbonModel->insertRow(r - 1, item);
    } else if (1 == level) {
        QStandardItem* paritem = item->parent();
        SARibbonCustomizeData d = SARibbonCustomizeData::makeChangePannelOrderCustomizeData(d_ptr->itemObjectName(paritem),
                                                                                            d_ptr->itemObjectName(item),
                                                                                            -1);
        d_ptr->mCustomizeDatas.append(d);
        int r = item->row();
        item  = paritem->takeChild(r);
        paritem->removeRow(r);
        paritem->insertRow(r - 1, item);
    } else if (2 == level) {
        QStandardItem* pannelItem   = item->parent();
        QStandardItem* categoryItem = pannelItem->parent();
        QAction* act                = itemToAction(item);
        if (!act) {
            return;
        }
        QString key             = d_ptr->mActionMgr->key(act);
        SARibbonCustomizeData d = SARibbonCustomizeData::makeChangeActionOrderCustomizeData(d_ptr->itemObjectName(categoryItem),
                                                                                            d_ptr->itemObjectName(pannelItem),
                                                                                            key,
                                                                                            d_ptr->mActionMgr,
                                                                                            -1);
        d_ptr->mCustomizeDatas.append(d);
        int r = item->row();
        item  = pannelItem->takeChild(r);
        pannelItem->removeRow(r);
        pannelItem->insertRow(r - 1, item);
    }
}

void SARibbonCustomizeWidget::onToolButtonDownClicked()
{
    QStandardItem* item = selectedItem();

    if (item == nullptr) {
        return;
    }
    int count = 0;

    if (item->parent()) {
        count = item->parent()->rowCount();
    } else {
        count = d_ptr->mRibbonModel->rowCount();
    }
    if ((nullptr == item) || ((count - 1) == item->row())) {
        return;
    }
    int level = itemLevel(item);

    if (0 == level) {
        //�ƶ�category
        SARibbonCustomizeData d = SARibbonCustomizeData::makeChangeCategoryOrderCustomizeData(d_ptr->itemObjectName(item), 1);
        d_ptr->mCustomizeDatas.append(d);
        int r = item->row();
        item  = d_ptr->mRibbonModel->takeItem(item->row());
        d_ptr->mRibbonModel->removeRow(r);
        d_ptr->mRibbonModel->insertRow(r + 1, item);
    } else if (1 == level) {
        QStandardItem* paritem = item->parent();
        SARibbonCustomizeData d = SARibbonCustomizeData::makeChangePannelOrderCustomizeData(d_ptr->itemObjectName(paritem),
                                                                                            d_ptr->itemObjectName(item),
                                                                                            1);
        d_ptr->mCustomizeDatas.append(d);
        int r = item->row();
        item  = paritem->takeChild(r);
        paritem->removeRow(r);
        paritem->insertRow(r + 1, item);
    } else if (2 == level) {
        QStandardItem* pannelItem   = item->parent();
        QStandardItem* categoryItem = pannelItem->parent();
        QAction* act                = itemToAction(item);
        if (!act) {
            return;
        }
        QString key             = d_ptr->mActionMgr->key(act);
        SARibbonCustomizeData d = SARibbonCustomizeData::makeChangeActionOrderCustomizeData(d_ptr->itemObjectName(categoryItem),
                                                                                            d_ptr->itemObjectName(pannelItem),
                                                                                            key,
                                                                                            d_ptr->mActionMgr,
                                                                                            -1);
        d_ptr->mCustomizeDatas.append(d);
        int r = item->row();
        item  = pannelItem->takeChild(r);
        pannelItem->removeRow(r);
        pannelItem->insertRow(r + 1, item);
    }
}

void SARibbonCustomizeWidget::onItemChanged(QStandardItem* item)
{
    if (item == nullptr) {
        return;
    }
    int level = itemLevel(item);

    if (0 == level) {
        if (item->isCheckable()) {
            QString objname = d_ptr->itemObjectName(item);
            SARibbonCustomizeData d = SARibbonCustomizeData::makeVisibleCategoryCustomizeData(objname, item->checkState() == Qt::Checked);
            d_ptr->mCustomizeDatas.append(d);
        }
    }
}

void SARibbonCustomizeWidget::onLineEditSearchActionTextEdited(const QString& text)
{
    d_ptr->mAcionModel->search(text);
}

void SARibbonCustomizeWidget::onPushButtonResetClicked()
{
    int btn = QMessageBox::warning(this,
                                   tr("Warning"),
                                   tr("Are you sure reset all customize setting?"),
                                   QMessageBox::Yes | QMessageBox::No,
                                   QMessageBox::No);

    if (btn == QMessageBox::Yes) {
        clear();
    }
}

/*** End of inlined file: SARibbonCustomizeWidget.cpp ***/

/*** Start of inlined file: SARibbonCustomizeDialog.cpp ***/
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>

/**
 * @brief The SARibbonCustomizeDialogUi class
 */
class SARibbonCustomizeDialogUi
{
public:
    SARibbonCustomizeWidget* customWidget;
    QVBoxLayout* verticalLayoutMain;
    QHBoxLayout* horizontalLayoutButtonGroup;
    QPushButton* pushButtonCancel;
    QPushButton* pushButtonOk;
    QSpacerItem* spacerItemleft;
    void setupUi(SARibbonMainWindow* ribbonWindow, QWidget* customizeDialog)
    {
        if (customizeDialog->objectName().isEmpty()) {
            customizeDialog->setObjectName(QStringLiteral("SARibbonCustomizeDialog"));
        }
        customizeDialog->resize(800, 600);
        verticalLayoutMain = new QVBoxLayout(customizeDialog);
        verticalLayoutMain->setObjectName(QStringLiteral("verticalLayoutMain"));

        customWidget = new SARibbonCustomizeWidget(ribbonWindow, customizeDialog);
        customWidget->setObjectName(QStringLiteral("customWidget"));
        verticalLayoutMain->addWidget(customWidget);

        horizontalLayoutButtonGroup = new QHBoxLayout();
        horizontalLayoutButtonGroup->setObjectName(QStringLiteral("horizontalLayoutButtonGroup"));

        spacerItemleft = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayoutButtonGroup->addItem(spacerItemleft);

        pushButtonCancel = new QPushButton(customizeDialog);
        pushButtonCancel->setObjectName(QStringLiteral("pushButtonCancel"));
        horizontalLayoutButtonGroup->addWidget(pushButtonCancel);

        pushButtonOk = new QPushButton(customizeDialog);
        pushButtonOk->setObjectName(QStringLiteral("pushButtonCancel"));
        horizontalLayoutButtonGroup->addWidget(pushButtonOk);
        verticalLayoutMain->addItem(horizontalLayoutButtonGroup);
        retranslateUi(customizeDialog);
    }

    void retranslateUi(QWidget* customizeDialog)
    {
        customizeDialog->setWindowTitle(QApplication::translate("SARibbonCustomizeDialog", "Customize Dialog", Q_NULLPTR));
        pushButtonCancel->setText(QApplication::translate("SARibbonCustomizeDialog", "Cancel", Q_NULLPTR));
        pushButtonOk->setText(QApplication::translate("SARibbonCustomizeDialog", "OK", Q_NULLPTR));
    }
};

////////////////////////////////////////////////////////////////////

SARibbonCustomizeDialog::SARibbonCustomizeDialog(SARibbonMainWindow* ribbonWindow, QWidget* p, Qt::WindowFlags f)
    : QDialog(p, f), ui(new SARibbonCustomizeDialogUi)
{
    ui->setupUi(ribbonWindow, this);
    initConnection();
}

/**
 * @brief ����action������
 *
 * ��ͬ@ref SARibbonCustomizeWidget::setupActionsManager
 * @param mgr
 */
void SARibbonCustomizeDialog::setupActionsManager(SARibbonActionsManager* mgr)
{
    ui->customWidget->setupActionsManager(mgr);
}

void SARibbonCustomizeDialog::initConnection()
{
    connect(ui->pushButtonOk, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &QDialog::reject);
}

/**
 * @brief ��ͬSARibbonCustomizeWidget::applys
 *
 * @ref SARibbonCustomizeWidget::applys
 * @return
 */
bool SARibbonCustomizeDialog::applys()
{
    return (ui->customWidget->applys());
}

/**
 * @brief ������ж���
 *
 * @ref SARibbonCustomizeWidget::clear
 */
void SARibbonCustomizeDialog::clear()
{
    ui->customWidget->clear();
}

/**
 * @brief ת��Ϊxml
 *
 * @ref SARibbonCustomizeWidget::toXml
 * @param xml
 * @return
 */
bool SARibbonCustomizeDialog::toXml(QXmlStreamWriter* xml) const
{
    return (ui->customWidget->toXml(xml));
}

/**
 * @brief ��ͬSARibbonCustomizeWidget::toXml
 * @ref SARibbonCustomizeWidget::toXml
 * @param xmlpath
 * @return
 */
bool SARibbonCustomizeDialog::toXml(const QString& xmlpath) const
{
    return (ui->customWidget->toXml(xmlpath));
}

/**
 * @brief ��ͬSARibbonCustomizeWidget::fromXml
 * @param xml
 */
void SARibbonCustomizeDialog::fromXml(QXmlStreamReader* xml)
{
    ui->customWidget->fromXml(xml);
}

/**
 * @brief ��ͬSARibbonCustomizeWidget::fromXml
 * @param xmlpath
 */
void SARibbonCustomizeDialog::fromXml(const QString& xmlpath)
{
    ui->customWidget->fromXml(xmlpath);
}

/**
 * @brief ����SARibbonCustomizeWidget����ָ��
 *
 * ͨ��SARibbonCustomizeWidget���ڿ��Բ������������
 *
 * @return SARibbonCustomizeWidgetָ�룬�ο�@ref SARibbonCustomizeWidget
 */
SARibbonCustomizeWidget* SARibbonCustomizeDialog::customizeWidget() const
{
    return (ui->customWidget);
}

/*** End of inlined file: SARibbonCustomizeDialog.cpp ***/

/*** Start of inlined file: SARibbonMainWindow.cpp ***/
#include <QWindowStateChangeEvent>
#include <QApplication>
#include <QDebug>
#include <QHash>
#include <QFile>

/**
 * @brief The SARibbonMainWindowPrivate class
 */
class SARibbonMainWindow::PrivateData
{
    SA_RIBBON_DECLARE_PUBLIC(SARibbonMainWindow)
public:
    PrivateData(SARibbonMainWindow* p);
    void init();

public:
    SARibbonMainWindow::RibbonTheme mCurrentRibbonTheme { SARibbonMainWindow::Office2013 };
    SARibbonBar* mRibbonBar { nullptr };
    SAWindowButtonGroup* mWindowButtonGroup { nullptr };
    SAFramelessHelper* mFramelessHelper { nullptr };
    bool mUseRibbon { true };
};

SARibbonMainWindow::PrivateData::PrivateData(SARibbonMainWindow* p) : q_ptr(p)
{
}

void SARibbonMainWindow::PrivateData::init()
{
}

//===================================================
// SARibbonMainWindow
//===================================================

SARibbonMainWindow::SARibbonMainWindow(QWidget* parent, bool useRibbon)
    : QMainWindow(parent), d_ptr(new SARibbonMainWindow::PrivateData(this))
{
    d_ptr->init();
    d_ptr->mUseRibbon = useRibbon;
    if (useRibbon) {
        setRibbonTheme(ribbonTheme());
        setMenuWidget(createRibbonBar());
        qDebug() << RibbonSubElementStyleOpt;
#ifdef Q_OS_UNIX
        //ĳЩϵͳ���FramelessWindowHint�쳣
        // FramelessHelper����������setWindowFlags(w->windowFlags()|Qt::FramelessWindowHint);��ʽ���ã���Ϊǿ��ȡ������
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#endif
    }
}

SARibbonMainWindow::~SARibbonMainWindow()
{
}

const SARibbonBar* SARibbonMainWindow::ribbonBar() const
{
    return (d_ptr->mRibbonBar);
}

/**
 * @brief ���useRibbonΪfalse���᷵��nullptr
 * @return
 */
SARibbonBar* SARibbonMainWindow::ribbonBar()
{
    return (d_ptr->mRibbonBar);
}

SAFramelessHelper* SARibbonMainWindow::framelessHelper()
{
    return (d_ptr->mFramelessHelper);
}

void SARibbonMainWindow::setRibbonTheme(SARibbonMainWindow::RibbonTheme theme)
{
    switch (theme) {
    case NormalTheme:
        loadTheme(":/theme/resource/default.qss");
        break;
    case Office2013:
        loadTheme(":/theme/resource/office2013.qss");
        break;
    default:
        loadTheme(":/theme/resource/default.qss");
        break;
    }
}

SARibbonMainWindow::RibbonTheme SARibbonMainWindow::ribbonTheme() const
{
    return (d_ptr->mCurrentRibbonTheme);
}

bool SARibbonMainWindow::isUseRibbon() const
{
    return (d_ptr->mUseRibbon);
}

/**
 * @brief �˺��������ڿ�����С��󻯺͹رհ�ť����ʾ
 */
void SARibbonMainWindow::updateWindowFlag(Qt::WindowFlags flags)
{
    if (isUseRibbon()) {
        d_ptr->mWindowButtonGroup->updateWindowFlag(flags);
    }
    repaint();
}

/**
 * @brief �˺������ص�flags������ Qt::WindowCloseButtonHint��Qt::WindowMaximizeButtonHint��Qt::WindowMinimizeButtonHint
 * ����
 * @return
 */
Qt::WindowFlags SARibbonMainWindow::windowButtonFlags() const
{
    if (isUseRibbon()) {
        return (d_ptr->mWindowButtonGroup->windowButtonFlags());
    }
    return (windowFlags());
}

void SARibbonMainWindow::setMenuWidget(QWidget* menubar)
{
    QMainWindow::setMenuWidget(menubar);
    SARibbonBar* bar = qobject_cast< SARibbonBar* >(menubar);

    if (bar) {
        d_ptr->mRibbonBar = bar;
        d_ptr->mRibbonBar->installEventFilter(this);
        //���ô���ı������߶�
        if (nullptr == d_ptr->mFramelessHelper) {
            d_ptr->mFramelessHelper = new SAFramelessHelper(this);
        }
        d_ptr->mFramelessHelper->setTitleHeight(d_ptr->mRibbonBar->titleBarHeight());
        //����window��ť
        if (nullptr == d_ptr->mWindowButtonGroup) {
            d_ptr->mWindowButtonGroup = new SAWindowButtonGroup(this);
        }
        QSize s = d_ptr->mWindowButtonGroup->sizeHint();
        s.setHeight(d_ptr->mRibbonBar->titleBarHeight());
        d_ptr->mWindowButtonGroup->setFixedSize(s);
        d_ptr->mWindowButtonGroup->setWindowStates(windowState());
        d_ptr->mUseRibbon = true;
        d_ptr->mWindowButtonGroup->show();
    } else {
        d_ptr->mRibbonBar = nullptr;
        d_ptr->mUseRibbon = false;
        if (d_ptr->mFramelessHelper) {
            delete d_ptr->mFramelessHelper;
            d_ptr->mFramelessHelper = nullptr;
        }
        if (d_ptr->mWindowButtonGroup) {
            d_ptr->mWindowButtonGroup->hide();
        }
    }
}

void SARibbonMainWindow::setMenuBar(QMenuBar* menuBar)
{
    QMainWindow::setMenuBar(menuBar);
    SARibbonBar* bar = qobject_cast< SARibbonBar* >(menuBar);

    if (bar) {
        d_ptr->mRibbonBar = bar;
        d_ptr->mRibbonBar->installEventFilter(this);
        //���ô���ı������߶�
        if (nullptr == d_ptr->mFramelessHelper) {
            d_ptr->mFramelessHelper = new SAFramelessHelper(this);
        }
        d_ptr->mFramelessHelper->setTitleHeight(d_ptr->mRibbonBar->titleBarHeight());
        //����window��ť
        if (nullptr == d_ptr->mWindowButtonGroup) {
            d_ptr->mWindowButtonGroup = new SAWindowButtonGroup(this);
        }
        QSize s = d_ptr->mWindowButtonGroup->sizeHint();
        s.setHeight(d_ptr->mRibbonBar->titleBarHeight());
        d_ptr->mWindowButtonGroup->setFixedSize(s);
        d_ptr->mWindowButtonGroup->setWindowStates(windowState());
        d_ptr->mUseRibbon = true;
        d_ptr->mWindowButtonGroup->show();
    } else {
        d_ptr->mRibbonBar = nullptr;
        d_ptr->mUseRibbon = false;
        if (d_ptr->mFramelessHelper) {
            delete d_ptr->mFramelessHelper;
            d_ptr->mFramelessHelper = nullptr;
        }
        if (d_ptr->mWindowButtonGroup) {
            d_ptr->mWindowButtonGroup->hide();
        }
    }
}

/**
 * @brief ����ribbonbar�Ĺ�������
 * @return
 */
SARibbonBar* SARibbonMainWindow::createRibbonBar()
{
    SARibbonBar* bar = new SARibbonBar(this);
    switch (ribbonTheme()) {
    case NormalTheme:
        break;
    case Office2013: {
        //������qss����Ҫ���margin��Ϣ�������ý�SARibbonTabBar��
        // office2013.qss��margin��Ϣ�������ã�em���ַ�M����Ӧ�Ŀ�ȵĳ���
        // margin-top: 0em;
        // margin-right: 0em;
        // margin-left: 0.2em;
        // margin-bottom: 0em;

        SARibbonTabBar* tab = bar->ribbonTabBar();
        if (!tab) {
            break;
        }
        QFontMetrics fm = tab->fontMetrics();
        int emWidth     = SA_FONTMETRICS_WIDTH(fm, "M");
        tab->setTabMargin(QMargins(0.2 * emWidth, 0, 0, 0));
    } break;
    default:
        break;
    }
    return bar;
}

void SARibbonMainWindow::resizeEvent(QResizeEvent* event)
{
    if (d_ptr->mRibbonBar) {
        if (d_ptr->mRibbonBar->size().width() != this->size().width()) {
            d_ptr->mRibbonBar->setFixedWidth(this->size().width());
        }
        if (d_ptr->mWindowButtonGroup) {
            d_ptr->mRibbonBar->setWindowButtonSize(d_ptr->mWindowButtonGroup->size());
        }
    }
    QMainWindow::resizeEvent(event);
}

bool SARibbonMainWindow::eventFilter(QObject* obj, QEvent* e)
{
    //���������Ϊ�˰�ribbonBar�ϵĶ������ݵ�mainwindow���ٴ��ݵ�frameless��
    //����ribbonbar���ڵ���frameless�����򣬵���frameless�޷�������Щ��Ϣ
    if (obj == d_ptr->mRibbonBar) {
        switch (e->type()) {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseMove:
        case QEvent::Leave:
        case QEvent::HoverMove:
        case QEvent::MouseButtonDblClick:
            QApplication::sendEvent(this, e);

        default:
            break;
        }
    }
    return (QMainWindow::eventFilter(obj, e));
}

bool SARibbonMainWindow::event(QEvent* e)
{
    if (e) {
        switch (e->type()) {
        case QEvent::WindowStateChange: {
            if (isUseRibbon()) {
                d_ptr->mWindowButtonGroup->setWindowStates(windowState());
            }
        } break;

        default:
            break;
        }
    }
    return (QMainWindow::event(e));
}

void SARibbonMainWindow::loadTheme(const QString& themeFile)
{
    QFile file(themeFile);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    setStyleSheet(file.readAll());
}

/*** End of inlined file: SARibbonMainWindow.cpp ***/

#ifdef _MSC_VER
#pragma warning(pop)
#pragma pop_macro("_CRT_SECURE_NO_WARNINGS")
#endif
