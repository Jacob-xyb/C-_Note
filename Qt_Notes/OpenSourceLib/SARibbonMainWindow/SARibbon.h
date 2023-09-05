#ifndef SA_RIBBON_H
#define SA_RIBBON_H
//����˺꣬��SA_RIBBON_EXPORT����Ϊ��
#ifndef SA_RIBBON_BAR_NO_EXPORT
#define SA_RIBBON_BAR_NO_EXPORT
#endif
//����˺꣬��SA_COLOR_WIDGETS_API����Ϊ��
#ifndef SA_COLOR_WIDGETS_NO_DLL
#define SA_COLOR_WIDGETS_NO_DLL
#endif

/*** Start of inlined file: SARibbonAmalgamTemplatePublicHeaders.h ***/
// Global

/*** Start of inlined file: SAColorWidgetsGlobal.h ***/
#ifndef SACOLORWIDGETSGLOBAL_H
#define SACOLORWIDGETSGLOBAL_H
#include <QScopedPointer>

/**
 * @def color-widgets�����ְ汾 MAJ.MIN.PAT
 */
#ifndef SA_COLOR_WIDGETS_VERSION_MAJ
#define SA_COLOR_WIDGETS_VERSION_MAJ 0
#endif
/**
 * @def color-widgets�����ְ汾 MAJ.MIN.PAT
 */
#ifndef SA_COLOR_WIDGETS_VERSION_MIN
#define SA_COLOR_WIDGETS_VERSION_MIN 1
#endif
/**
 * @def color-widgets�����ְ汾 MAJ.MIN.PAT
 */
#ifndef SA_COLOR_WIDGETS_VERSION_PAT
#define SA_COLOR_WIDGETS_VERSION_PAT 0
#endif

/**
 * @def   ģ��Q_DECLARE_PRIVATE��������ǰ������������Ϊһ���ڲ���
 */
#ifndef SA_COLOR_WIDGETS_DECLARE_PRIVATE
#define SA_COLOR_WIDGETS_DECLARE_PRIVATE(classname)                                                                    \
    class PrivateData;                                                                                                 \
    friend class classname::PrivateData;                                                                               \
    QScopedPointer< PrivateData > d_ptr;
#endif
/**
 * @def   ģ��Q_DECLARE_PUBLIC
 */
#ifndef SA_COLOR_WIDGETS_DECLARE_PUBLIC
#define SA_COLOR_WIDGETS_DECLARE_PUBLIC(classname)                                                                     \
    friend class classname;                                                                                            \
    classname* q_ptr { nullptr };
#endif

#ifndef SA_COLOR_WIDGETS_NO_DLL
#if defined(SA_COLOR_WIDGETS_MAKE_LIB)  // ����˺꽫����library
#ifndef SA_COLOR_WIDGETS_API
#define SA_COLOR_WIDGETS_API Q_DECL_EXPORT
#endif
#else
#ifndef SA_COLOR_WIDGETS_API
#define SA_COLOR_WIDGETS_API Q_DECL_IMPORT
#endif
#endif
#else
#ifndef SA_COLOR_WIDGETS_API
#define SA_COLOR_WIDGETS_API
#endif
#endif

#endif  // SACOLORWIDGETSGLOBAL_H

/*** End of inlined file: SAColorWidgetsGlobal.h ***/

/*** Start of inlined file: SARibbonGlobal.h ***/
#ifndef SARIBBONGLOBAL_H
#define SARIBBONGLOBAL_H
#include <qglobal.h>
#include <memory>

//! �汾��¼��
//!
//! 2023-05-28 -> 0.5.0
//! �����˴�ťģʽ�µ���ʾ������ȥ����ԭ��SARibbonToolButton��Lite��Normalģʽ����WordWrap������
//! ֧�������Զ��廻��
//! ������RibbonPannel�ı������ĸ߶ȼ��㷽��
//!
//! 0.5.1
//! ��ʹ��QString::simplified,���Ǽ򵥵Ľ����滻\n��simplified���������Ļ��в������ո�
//!
//! 0.5.2
//! SARibbonColorToolButton\SARibbonToolButton����&������������ʽδ����������
//! SARibbonStyleOption�������������
//! ԭ��SARibbonElementCreateDelegate�����ΪSARibbonElementFactory
//!

/**
 * @def ribbon�����ְ汾 {MAJ}.MIN.PAT
 */
#ifndef SA_RIBBON_BAR_VERSION_MAJ
#define SA_RIBBON_BAR_VERSION_MAJ 0
#endif
/**
 * @def ribbon�����ְ汾 MAJ.{MIN}.PAT
 */
#ifndef SA_RIBBON_BAR_VERSION_MIN
#define SA_RIBBON_BAR_VERSION_MIN 6
#endif
/**
 * @def ribbon�����ְ汾 MAJ.MIN.{PAT}
 */
#ifndef SA_RIBBON_BAR_VERSION_PAT
#define SA_RIBBON_BAR_VERSION_PAT 0
#endif

/**
 * @def ���ԣ����ڱ���Ƿ���Խ����Զ��壬���ڶ�̬���õ�@ref SARibbonCategory ��@ref SARibbonPannel
 * ֵΪbool����Ϊtrueʱ������ͨ��@ref SARibbonCustomizeWidget �ı����SARibbonCategory��SARibbonPannel�Ĳ��֣�
 * Ĭ�ϲ����д����ԣ������д�������Ϊtrueʱ�Ż���SARibbonCustomizeWidget������ʾΪ������
 */
#ifndef SA_RIBBON_BAR_PROP_CAN_CUSTOMIZE
#define SA_RIBBON_BAR_PROP_CAN_CUSTOMIZE "_sa_isCanCustomize"
#endif

#ifndef SA_RIBBON_BAR_NO_EXPORT
#if defined(SA_RIBBON_BAR_MAKE_LIB)  // ����˺꽫����library
#define SA_RIBBON_EXPORT Q_DECL_EXPORT
#else
#define SA_RIBBON_EXPORT Q_DECL_IMPORT
#endif
#endif

#ifndef SA_RIBBON_EXPORT
#define SA_RIBBON_EXPORT
#endif

/**
 * @def   ģ��Q_DECLARE_PRIVATE��������ǰ������������Ϊһ���ڲ���
 */
#ifndef SA_RIBBON_DECLARE_PRIVATE
#define SA_RIBBON_DECLARE_PRIVATE(classname)                                                                           \
    class PrivateData;                                                                                                 \
    friend class classname::PrivateData;                                                                               \
    std::unique_ptr< PrivateData > d_ptr;
#endif
/**
 * @def   ģ��Q_DECLARE_PUBLIC
 */
#ifndef SA_RIBBON_DECLARE_PUBLIC
#define SA_RIBBON_DECLARE_PUBLIC(classname)                                                                            \
    friend class classname;                                                                                            \
    classname* q_ptr { nullptr };
#endif

#endif  // SARIBBONGLOBAL_H

/*** End of inlined file: SARibbonGlobal.h ***/

// color widget

/*** Start of inlined file: SAColorMenu.h ***/
#ifndef SACOLORMENU_H
#define SACOLORMENU_H
#include <QMenu>

class QWidgetAction;
class SAColorPaletteGridWidget;
class SAColorGridWidget;
class SAColorToolButton;
/**
 * @brief ��׼��ɫ�˵�
 */
class SA_COLOR_WIDGETS_API SAColorMenu : public QMenu
{
    Q_OBJECT
    SA_COLOR_WIDGETS_DECLARE_PRIVATE(SAColorMenu)
public:
    explicit SAColorMenu(QWidget* parent = nullptr);
    explicit SAColorMenu(const QString& title, QWidget* parent = nullptr);
    ~SAColorMenu();
    //���ٰ�colorbtn
    void bindToColorToolButton(SAColorToolButton* btn);
    // ThemeColorsPalette��Ӧ��action
    QWidgetAction* getThemeColorsPaletteAction() const;
    // CustomColorsWidget��Ӧ��action
    QWidgetAction* getCustomColorsWidgetAction() const;
    // �Զ�����ɫaction
    QAction* getCustomColorAction() const;
    //��ȡThemeColorsPalette
    SAColorPaletteGridWidget* getColorPaletteGridWidget() const;
    //��ȡ�Զ�����ɫgrid
    SAColorGridWidget* getCustomColorsWidget() const;
    //��������ɫaction��Ĭ������ɫaction��û�е�
    void enableNoneColorAction(bool on = true);
    //��ȡNone Color Action,ע�⣬enableNoneColorAction(true),֮��Ų���nullptr
    QAction* getNoneColorAction() const;
public slots:
    //����һ�������ۺ�����Ϊ�����û��Զ��������actionҲ�ܹ���menu�����Ե��ô˲ۺ�����ʵ��selectedColor�ź��Լ�menu������
    void emitSelectedColor(const QColor& c);
signals:
    /**
     * @brief ѡ������ɫ�������ź�
     * @param c
     */
    void selectedColor(const QColor& c);
private slots:
    void onCustomColorActionTriggered(bool on);
    void onNoneColorActionTriggered(bool on);

private:
    void init(const QList< QColor >& themeCls);
};

#endif  // SACOLORMENU_H

/*** End of inlined file: SAColorMenu.h ***/

/*** Start of inlined file: SAColorGridWidget.h ***/
#ifndef SACOLORGRIDWIDGET_H
#define SACOLORGRIDWIDGET_H
#include <QWidget>
#include <functional>

class QAbstractButton;
class SAColorToolButton;
/**
 * @brief һ��grid��Color����
 *
 * һ�������������ɫgrid��
 *
 * ������������������
 *
 * ������������������
 *
 * ������������������
 */
class SA_COLOR_WIDGETS_API SAColorGridWidget : public QWidget
{
    Q_OBJECT
    SA_COLOR_WIDGETS_DECLARE_PRIVATE(SAColorGridWidget)
    Q_PROPERTY(int spacing READ getSpacing WRITE setSpacing)
public:
    using FunColorBtn = std::function< void(SAColorToolButton*) >;

public:
    SAColorGridWidget(QWidget* par = nullptr);
    ~SAColorGridWidget();
    //�����������������������������ƥ��,�������-1����0��˵�����޶���������������ֻ��һ��
    void setColumnCount(int c);
    int getColumnCount() const;
    //���õ�ǰ����ɫ�б�
    void setColorList(const QList< QColor >& cls);
    QList< QColor > getColorList() const;
    //���
    int getSpacing() const;
    void setSpacing(int v);
    //��ȡ��ɫ������
    int getColorCount() const;
    //ͼ��ĳߴ�
    void setColorIconSize(const QSize& s);
    QSize getColorIconSize() const;
    //������ɫ�Ƿ���checkable
    void setColorCheckable(bool on = true);
    bool isColorCheckable() const;
    //��ȡ��ǰѡ�е���ɫ
    QColor getCurrentCheckedColor() const;
    //��ȡindex���ڵ�colorbutton
    SAColorToolButton* getColorButton(int index) const;
    //��ֱ���
    void setVerticalSpacing(int v);
    int getVerticalSpacing() const;
    //ˮƽ���
    void setHorizontalSpacing(int v);
    int getHorizontalSpacing() const;
    //�����ǰѡ��״̬����ʱû����ɫ��ѡ�е�
    void clearCheckedState();
    //�����е�colorbtn���б�����������ͨ���˺�������tooltip���õȲ���
    void iterationColorBtns(FunColorBtn fn);
    //��������С�߶�
    void setRowMinimumHeight(int row, int minSize);
    //����ɫ�������
    void setHorizontalSpacerToRight(bool on = true);
private slots:
    void onButtonClicked(QAbstractButton* btn);
    void onButtonPressed(QAbstractButton* btn);
    void onButtonReleased(QAbstractButton* btn);
    void onButtonToggled(QAbstractButton* btn, bool on);

signals:
    /**
     * @brief ����checkģʽ��check����ɫ�������ź�
     * @param c
     * @param on
     */
    void colorClicked(const QColor& c);
    void colorPressed(const QColor& c);
    void colorReleased(const QColor& c);
    void colorToggled(const QColor& c, bool on);

public:
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;
};
namespace SA
{
/**
 * @brief ��ȡ��׼ɫ�б�һ��10����ɫ��
 * @return
 */
SA_COLOR_WIDGETS_API QList< QColor > getStandardColorList();
}
#endif  // SACOLORGRIDWIDGET_H

/*** End of inlined file: SAColorGridWidget.h ***/

/*** Start of inlined file: SAColorPaletteGridWidget.h ***/
#ifndef SACOLORPALETTEGRIDWIDGET_H
#define SACOLORPALETTEGRIDWIDGET_H
#include <QWidget>

class QMenu;
class SAColorToolButton;
/**
 * @brief ����office����ɫѡ�񴰿ڣ���һ�ű�׼ɫ��������һ����ɫ�壬��3��ǳɫ����2����ɫ
 */
class SA_COLOR_WIDGETS_API SAColorPaletteGridWidget : public QWidget
{
    Q_OBJECT
    SA_COLOR_WIDGETS_DECLARE_PRIVATE(SAColorPaletteGridWidget)
public:
    SAColorPaletteGridWidget(QWidget* par = nullptr);
    SAColorPaletteGridWidget(const QList< QColor >& cls, QWidget* par = nullptr);
    ~SAColorPaletteGridWidget();
    //���ô���ά����colorList
    void setColorList(const QList< QColor >& cls);
    QList< QColor > getColorList() const;
    //������ɫ��ǳ����factor��Ĭ��Ϊ{ 180, 160, 140, 75, 50 }
    void setFactor(const QList< int >& factor);
    QList< int > getFactor() const;
    //����iconsize
    void setColorIconSize(const QSize& s);
    QSize getColorIconSize() const;
    //������ɫ�Ƿ���checkable
    void setColorCheckable(bool on = true);
    bool isColorCheckable() const;
private slots:
    void onMainColorClicked(const QColor& c);
    void onPaletteColorClicked(const QColor& c);

private:
    void init();
signals:
    /**
     * @brief ����checkģʽ��check����ɫ�������ź�
     * @param c
     * @param on
     */
    void colorClicked(const QColor& c);
};

#endif  // SACOLORPALETTEGRIDWIDGET_H

/*** End of inlined file: SAColorPaletteGridWidget.h ***/

/*** Start of inlined file: SAColorToolButton.h ***/
#ifndef SACOLORTOOLBUTTON_H
#define SACOLORTOOLBUTTON_H
#include <QToolButton>

class QPaintEvent;
class QResizeEvent;
class QPainter;
class QStylePainter;
/**
 * @brief ����һ��ֻ��ʾ��ɫ��toolbutton
 *
 *
 * ��ToolButtonIconOnlyģʽ�£����û��setIcon,����ɫռ��������������ͼ��ʾ
 *
 * ��������������
 * ��color��
 * ��������������
 *
 * �����ToolButtonIconOnlyģʽ����ͼ�꣬ͼ����������ʾ��������ʾ��ɫ������ͼ��ʾ
 *
 * ��������������
 * ��icon ��
 * ��color��
 * ��������������
 *
 * ��ToolButtonTextBesideIcon��ToolButtonTextUnderIcon�£�setIconSize ����ָ����ɫ�Ĵ�С��
 * ��ֻ��ToolButtonTextBesideIcon��ToolButtonTextUnderIcon����Ч
 *
 * ���û������ͼ�꣬Ҳ����setIcon(QIcon()),iconSize��Ϊ��ɫ��Ĵ�С
 *
 * ����������������������
 * ��������      ��
 * ��������      ��
 * ����������������������
 *
 * �����ͼ�꣬��ɫ������ͼ���·���Ϊͼ��߶ȵ�1/4 Ϊͼ����һ�£����������ؼ��Ĵ�С�����Զ���С���
 *
 */
class SA_COLOR_WIDGETS_API SAColorToolButton : public QToolButton
{
    Q_OBJECT
    SA_COLOR_WIDGETS_DECLARE_PRIVATE(SAColorToolButton)
public:
    explicit SAColorToolButton(QWidget* parent = nullptr);
    ~SAColorToolButton();
    //��ȡ��ɫ
    QColor getColor() const;
    //����Margins
    void setMargins(const QMargins& mg);
    QMargins getMargins() const;
    //��������ɫ
    static void paintNoneColor(QPainter* p, const QRect& colorRect);
public slots:
    //������ɫ,�ᷢ��colorChanged�ź�
    void setColor(const QColor& c);

protected:
    //��ȡ�ؼ�������rectλ��
    virtual void calcRect(const QStyleOptionToolButton& opt, QRect& iconRect, QRect& textRect, QRect& colorRect);
    virtual void paintButton(QStylePainter* p, const QStyleOptionToolButton& opt);
    virtual void paintIcon(QStylePainter* p, const QRect& iconRect, const QStyleOptionToolButton& opt);
    virtual void paintText(QStylePainter* p, const QRect& textRect, const QStyleOptionToolButton& opt);
    virtual void paintColor(QStylePainter* p, const QRect& colorRect, const QColor& color, const QStyleOptionToolButton& opt);

protected:
    virtual void paintEvent(QPaintEvent* e) Q_DECL_OVERRIDE;
    virtual void resizeEvent(QResizeEvent* e) Q_DECL_OVERRIDE;
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;
private slots:
    void onButtonClicked(bool checked = false);
signals:
    /**
     * @brief ��ɫ���������Ӧ
     * @param color
     */
    void colorClicked(const QColor& color, bool checked = false);
    /**
     * @brief ��ɫ�ı��ź�
     * @param color
     */
    void colorChanged(const QColor& color);
};

#endif  // SACOLORTOOLBUTTON_H

/*** End of inlined file: SAColorToolButton.h ***/

// sa ribbon

/*** Start of inlined file: SAFramelessHelper.h ***/
#ifndef SAFRAMELESSHELPER_H
#define SAFRAMELESSHELPER_H

#include <QObject>

class QWidget;

class SA_RIBBON_EXPORT SAFramelessHelper : public QObject
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SAFramelessHelper)
    friend class SAPrivateFramelessWidgetData;

public:
    explicit SAFramelessHelper(QObject* parent);
    ~SAFramelessHelper();
    // �����
    void activateOn(QWidget* topLevelWidget);

    // �Ƴ�����
    void removeFrom(QWidget* topLevelWidget);

    // ���ô����ƶ�
    void setWidgetMovable(bool movable);

    // ���ô�������
    void setWidgetResizable(bool resizable);

    // ������Ƥ���ƶ�
    void setRubberBandOnMove(bool movable);

    // ������Ƥ������
    void setRubberBandOnResize(bool resizable);

    // ���ñ߿�Ŀ��
    void setBorderWidth(int width);

    // ���ñ������߶�
    void setTitleHeight(int height);
    bool widgetResizable();
    bool widgetMovable();
    bool rubberBandOnMove();
    bool rubberBandOnResisze();
    uint borderWidth();
    uint titleHeight();

protected:
    // �¼����ˣ������ƶ������ŵ�
    virtual bool eventFilter(QObject* obj, QEvent* event);
};

#endif  // FRAMELESSHELPER_H

/*** End of inlined file: SAFramelessHelper.h ***/

/*** Start of inlined file: SARibbonApplicationButton.h ***/
#ifndef SARIBBONAPPLICATIONBUTTON_H
#define SARIBBONAPPLICATIONBUTTON_H
#include <QToolButton>

/**
 * @brief The SARibbonApplicationButton class
 *
 * Ĭ�ϵ�plicationButton,����ͨ����ʽָ����һ����ApplicationButton
 */
class SA_RIBBON_EXPORT SARibbonApplicationButton : public QToolButton
{
    Q_OBJECT
public:
    SARibbonApplicationButton(QWidget* parent = nullptr);
    SARibbonApplicationButton(const QString& text, QWidget* parent = nullptr);
    SARibbonApplicationButton(const QIcon& icon, const QString& text, QWidget* parent = nullptr);
};

#endif  // SARIBBONAPPLICATIONBUTTON_H

/*** End of inlined file: SARibbonApplicationButton.h ***/

/*** Start of inlined file: SAWindowButtonGroup.h ***/
#ifndef SAWINDOWBUTTONGROUP_H
#define SAWINDOWBUTTONGROUP_H

#include <QWidget>
#include <QPushButton>

///
/// \brief ���ڵ������С����ť
///
class SA_RIBBON_EXPORT SAWindowButtonGroup : public QWidget
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SAWindowButtonGroup)
public:
    SAWindowButtonGroup(QWidget* parent);
    SAWindowButtonGroup(QWidget* parent, Qt::WindowFlags flags);
    ~SAWindowButtonGroup();
    void setupMinimizeButton(bool on);
    void setupMaximizeButton(bool on);
    void setupCloseButton(bool on);
    void updateWindowFlag();
    void updateWindowFlag(Qt::WindowFlags flags);

    //���ð�ť�Ŀ�ȱ���,���հ�ť��Ƚ����մ˱�����������
    void setButtonWidthStretch(int close = 4, int max = 3, int min = 3);

    //���ð�ť�����ű���
    void setIconScale(qreal iconscale = 0.5);

    //����Qt::WindowStates
    void setWindowStates(Qt::WindowStates s);

    //����ȡ��ť��״̬
    Qt::WindowFlags windowButtonFlags() const;

    virtual QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    virtual bool eventFilter(QObject* watched, QEvent* e) Q_DECL_OVERRIDE;
    virtual void parentResize();
    virtual void resizeEvent(QResizeEvent* e) Q_DECL_OVERRIDE;

protected slots:
    Q_SLOT void closeWindow();
    Q_SLOT void minimizeWindow();
    Q_SLOT void maximizeWindow();
};

/**
 * @brief The SAWindowToolButton class
 */
class SAWindowToolButton : public QPushButton
{
    Q_OBJECT
public:
    SAWindowToolButton(QWidget* p = nullptr);
};
#endif  // SAWINDOWBUTTONGROUP_H

/*** End of inlined file: SAWindowButtonGroup.h ***/

/*** Start of inlined file: SARibbonToolButton.h ***/
#ifndef SARIBBONTOOLBUTTON_H
#define SARIBBONTOOLBUTTON_H

#include <QToolButton>
#include <QDebug>
/**
 * @brief Ribbon�������õ�toolButton
 *
 * �������ͨtoolbutton����Ҫ���������������ã�@ref setButtonType �� @ref setLargeButtonType
 *
 * @note @sa setIconSize �������������ã�iconsize�Ǹ��ݵ�ǰ�ߴ綯̬������
 */
class SA_RIBBON_EXPORT SARibbonToolButton : public QToolButton
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonToolButton)
public:
    /**
     * @brief ��ť��ʽ
     */
    enum RibbonButtonType
    {
        LargeButton,
        SmallButton
    };
    Q_ENUM(RibbonButtonType)

public:
    SARibbonToolButton(QWidget* parent = Q_NULLPTR);
    SARibbonToolButton(QAction* defaultAction, QWidget* parent = Q_NULLPTR);
    ~SARibbonToolButton();
    //��ǰ�ť����ʽ����ť����ʽ�в�ͬ����Ⱦ��ʽ
    RibbonButtonType buttonType() const;
    void setButtonType(const RibbonButtonType& buttonType);
    //�Ƿ���С��ť
    bool isSmallRibbonButton() const;
    //�Ƿ��Ǵ�ť
    bool isLargeRibbonButton() const;
    //��С�ߴ���ʾ
    virtual QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    //��ȡ���
    int spacing() const;
    //���³ߴ�
    void updateRect();

public:
    //��liteģʽ���Ƿ��������ֻ���
    static void setEnableWordWrap(bool on);
    static bool isEnableWordWrap();

protected:
    virtual void paintEvent(QPaintEvent* e) Q_DECL_OVERRIDE;
    virtual void resizeEvent(QResizeEvent* e) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
    virtual void focusOutEvent(QFocusEvent* e) Q_DECL_OVERRIDE;
    virtual void leaveEvent(QEvent* e) Q_DECL_OVERRIDE;
    virtual bool hitButton(const QPoint& pos) const Q_DECL_OVERRIDE;
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;
    virtual bool event(QEvent* e) Q_DECL_OVERRIDE;
    //�¼��ı� - ��ҪΪ�˲�������ĸı�
    virtual void changeEvent(QEvent* e) Q_DECL_OVERRIDE;
    virtual void actionEvent(QActionEvent* e) Q_DECL_OVERRIDE;

protected:
    //���ư�ť
    virtual void paintButton(QPainter& p, const QStyleOptionToolButton& opt);
    //����ͼ��
    virtual void paintIcon(QPainter& p, const QStyleOptionToolButton& opt, const QRect& iconDrawRect);
    //�����ı�
    virtual void paintText(QPainter& p, const QStyleOptionToolButton& opt, const QRect& textDrawRect);
    //����Indicator
    virtual void paintIndicator(QPainter& p, const QStyleOptionToolButton& opt, const QRect& indicatorDrawRect);

private:
    static void drawArrow(const QStyle* style,
                          const QStyleOptionToolButton* toolbutton,
                          const QRect& rect,
                          QPainter* painter,
                          const QWidget* widget = 0);

protected:
};

namespace SA
{
QDebug operator<<(QDebug debug, const QStyleOptionToolButton& opt);
}
#endif  // SARIBBONTOOLBUTTON_H

/*** End of inlined file: SARibbonToolButton.h ***/

/*** Start of inlined file: SARibbonColorToolButton.h ***/
#ifndef SARIBBONCOLORTOOLBUTTON_H
#define SARIBBONCOLORTOOLBUTTON_H

class SAColorMenu;
/**
 * @brief Refer to the color setting button in the office, which can display the color below the icon(�ο�office����ɫ���ð�ť��������ʾ��ɫ��ͼ���·�)
 */
class SA_RIBBON_EXPORT SARibbonColorToolButton : public SARibbonToolButton
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonColorToolButton)
public:
    /**
     * @brief ��ɫ��ʽ
     */
    enum ColorStyle
    {
        ColorUnderIcon,  ///< ��ɫ��icon�·������Ҫ���������icon
        ColorFillToIcon  ///< ��ɫ��Ϊicon�����ģʽ����setColor���Զ�����һ����ɫicon�滻��ԭ����icon�����setIcon����û������
    };

public:
    SARibbonColorToolButton(QWidget* parent = Q_NULLPTR);
    SARibbonColorToolButton(QAction* defaultAction, QWidget* parent = Q_NULLPTR);
    ~SARibbonColorToolButton();
    //��ȡ��ɫ
    QColor getColor() const;
    //������ɫ��ʾ����
    void setColorStyle(ColorStyle s);
    ColorStyle colorStyle() const;
    //������׼����ɫ�˵�
    SAColorMenu* setupStandardColorMenu();
public slots:
    //������ɫ,�ᷢ��colorChanged�ź�
    void setColor(const QColor& c);
private slots:
    void onButtonClicked(bool checked = false);
signals:
    /**
     * @brief ��ɫ���������Ӧ
     * @param color
     */
    void colorClicked(const QColor& color, bool checked = false);
    /**
     * @brief ��ɫ�ı��ź�
     * @param color
     */
    void colorChanged(const QColor& color);

protected:
    void paintIcon(QPainter& p, const QStyleOptionToolButton& opt, const QRect& iconDrawRect);
};

#endif  // SARIBBONCOLORTOOLBUTTON_H

/*** End of inlined file: SARibbonColorToolButton.h ***/

/*** Start of inlined file: SARibbonLineWidgetContainer.h ***/
#ifndef SARIBBONLINEWIDGETCONTAINER_H
#define SARIBBONLINEWIDGETCONTAINER_H

#include <QtCore/qglobal.h>
#include <QWidget>
#include <QLabel>

/**
 * @brief һ�������������Ѵ��ڷ����м䣬ǰ����涼���������ı�����Ҫ���ڷ�����pannel�ϵ�С����
 *
 * ʵ������Ч����
 *
 * PrefixLabel|_Widget_|SuffixLabel
 *
 */
class SA_RIBBON_EXPORT SARibbonLineWidgetContainer : public QWidget
{
public:
    SARibbonLineWidgetContainer(QWidget* par = nullptr);

    //����widget,����������һ��nullptr
    void setWidget(QWidget* innerWidget);

    //����ǰ׺
    void setPrefix(const QString& str);

    //���ú�׺
    void setSuffix(const QString& str);

    //ǰ׺�ı���
    QLabel* labelPrefix() const;

    //��׺�ı���
    QLabel* labelSuffix() const;

private:
    //�����ı�
    QLabel* m_labelPrefix;
    QLabel* m_labelSuffix;
    QWidget* m_innerWidget;
};

#endif  // SARIBBONWIDGETCONTAINER_H

/*** End of inlined file: SARibbonLineWidgetContainer.h ***/

/*** Start of inlined file: SARibbonActionsManager.h ***/
#ifndef SARIBBONACTIONSMANAGER_H
#define SARIBBONACTIONSMANAGER_H

#include <QObject>
#include <QAbstractListModel>
#include <QAction>
#include <QMap>
#include <QString>
#include <QSet>
class SARibbonMainWindow;
class SARibbonCategory;

/**
 * @brief ���ڹ���SARibbon������Action
 *
 * SARibbonActionsManagerά����������һ����tag����ǩ����Ӧ��Action list��
 * һ�������н���SARibbonActionsManager�����action list��
 *
 * SARibbonActionsManager�ı�ǩ��Ӧһ��actions��ÿ����ǩ��Ӧ��action�����ظ����֣�
 * ��SARibbonActionsManagerά����action list��ֻ��һ��action�������ظ����֡�
 *
 * tag���ڶ�action list���飬ÿ��tag��ʵ������ͨ��@ref setTagName �������ã������Ա仯ʱ��Ҫ��ʱ����
 * setTagName�����µı�ǩ��Ӧ���ı���
 *
 * SARibbonActionsManagerĬ��Ԥ����6�����ñ�ǩ��@ref SARibbonActionsManager::ActionTag ���û��Զ����ǩ��Ҫ��
 * SARibbonActionsManager::UserDefineActionTagֵ�Ļ����Ͻ����ۼӡ�
 *
 * @ref filter ����ͬ@ref actions ������������ȡ��ǩ�����action list��@ref allActions ��������SARibbonActionsManager
 * ��������б�ǩ��
 *
 * ͨ��@ref autoRegisteActions �������Կ��ٵĽ���action�Ĺ����˺��������@ref SARibbonMainWindow �µ�������object��
 * ͬʱ����SARibbonMainWindow������@ref SARibbonPannel ��ӵ�action,������Category����tag������ʹ���û������ע��autoRegisteActions��������
 *
 *
 */
class SA_RIBBON_EXPORT SARibbonActionsManager : public QObject
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonActionsManager)
    friend class SARibbonActionsManagerModel;

public:
    /**
     * @brief ����action�ı�ǩ
     */
    enum ActionTag
    {
        UnknowActionTag              = 0,     ///< δ֪��tag
        CommonlyUsedActionTag        = 0x01,  ///< Ԥ��tag-��������
        NotInFunctionalAreaActionTag = 0x02,  ///< Ԥ��tag-���ڹ���������
        AutoCategoryDistinguishBeginTag = 0x1000,  ///< �Զ���Category���ֵı�ǩ��ʼ����@ref autoRegisteActions �������õ�
        AutoCategoryDistinguishEndTag = 0x2000,  ///< �Զ���Category���ֵı�ǩ��������@ref autoRegisteActions �������õ�
        NotInRibbonCategoryTag = 0x2001,  ///< ���ڹ������ı�ǩ@ref autoRegisteActions �������������category��action�Լ�SARibbonMainWindow�µ�action���������
        UserDefineActionTag    = 0x8000   ///< �Զ����ǩ�������û��Զ���tagҪ���ڴ�tag
    };
    SARibbonActionsManager(SARibbonMainWindow* p);
    ~SARibbonActionsManager();
    //����tag��Ӧ������
    void setTagName(int tag, const QString& name);

    //��ȡtag��Ӧ������
    QString tagName(int tag) const;

    //�Ƴ�tag��ע�⣬��������ǳ���ʱ
    void removeTag(int tag);

    //ע��action
    bool registeAction(QAction* act, int tag, const QString& key = QString(), bool enableEmit = true);

    //ȡ��action��ע��
    void unregisteAction(QAction* act, bool enableEmit = true);

    //���˵õ�actions��Ӧ�����ã�ʵ����һ��������
    QList< QAction* >& filter(int tag);

    //ͨ��tagɸѡ��ϵ��action
    QList< QAction* >& actions(int tag);
    const QList< QAction* > actions(int tag) const;

    //��ȡ���еı�ǩ
    QList< int > actionTags() const;

    //ͨ��key��ȡaction
    QAction* action(const QString& key) const;

    //ͨ��action�ҵ�key
    QString key(QAction* act) const;

    //�������й����action��
    int count() const;

    //�������й����actions
    QList< QAction* > allActions() const;

    //�Զ�����action,����tag��Ӧ��Categoryָ��
    QMap< int, SARibbonCategory* > autoRegisteActions(SARibbonMainWindow* w);

    //�Զ�����widget�µ�actions�������ص�action,���ؼ��ص���������Щ
    QSet< QAction* > autoRegisteWidgetActions(QWidget* w, int tag, bool enableEmit = false);

    //���ݱ������action
    QList< QAction* > search(const QString& text);

    //���
    void clear();

    //��ȡribbonwindow
    SARibbonMainWindow* ribbonWindow() const;

signals:

    /**
     * @brief ��ǩ�仯�������źţ��仯����������ɾ��
     */
    void actionTagChanged(int tag, bool isdelete);

private slots:
    void onActionDestroyed(QObject* o);
    void onCategoryTitleChanged(const QString& title);

private:
    void removeAction(QAction* act, bool enableEmit = true);
};

/**
 * @brief SARibbonActionsManager ��Ӧ��model
 */
class SA_RIBBON_EXPORT SARibbonActionsManagerModel : public QAbstractListModel
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonActionsManagerModel)
public:
    explicit SARibbonActionsManagerModel(QObject* p = nullptr);
    explicit SARibbonActionsManagerModel(SARibbonActionsManager* m, QObject* p = nullptr);
    ~SARibbonActionsManagerModel();
    virtual int rowCount(const QModelIndex& parent) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;
    void setFilter(int tag);
    void update();
    void setupActionsManager(SARibbonActionsManager* m);
    void uninstallActionsManager();
    QAction* indexToAction(QModelIndex index) const;
    void search(const QString& text);

private slots:
    void onActionTagChanged(int tag, bool isdelete);
};

#endif  // SARIBBONACTIONSMANAGER_H

/*** End of inlined file: SARibbonActionsManager.h ***/

/*** Start of inlined file: SARibbonDrawHelper.h ***/
#ifndef SARIBBONDRAWHELPER_H
#define SARIBBONDRAWHELPER_H
#include <QIcon>
#include <QStylePainter>
#include <QStyleOption>
#include <QPixmap>

/**
 * @def QFontMetrics::horizontalAdvance(str)/QFontMetrics::width(str) Ϊ�˼���5.11���µ�qt�汾������ļ��ݺ�
 */
#if (QT_VERSION >= QT_VERSION_CHECK(5, 11, 0))
#ifndef SA_FONTMETRICS_WIDTH
#define SA_FONTMETRICS_WIDTH(fm, str) fm.horizontalAdvance(str)
#endif
#else
#ifndef SA_FONTMETRICS_WIDTH
#define SA_FONTMETRICS_WIDTH(fm, str) fm.width(str)
#endif
#endif

///
/// \brief ��ͼ����
///
class SA_RIBBON_EXPORT SARibbonDrawHelper
{
public:
    SARibbonDrawHelper();
    static QPixmap iconToPixmap(const QIcon& icon, QWidget* widget, const QStyleOption* opt, const QSize& icoSize);
    static void drawIcon(const QIcon& icon, QPainter* painter, const QStyleOption* opt, int x, int y, int width, int height);
    static void drawIcon(const QIcon& icon, QPainter* painter, const QStyleOption* opt, const QRect& rect);
    static QSize iconActualSize(const QIcon& icon, const QStyleOption* opt, const QSize& iconSize);

    static void drawText(const QString& text, QStylePainter* painter, const QStyleOption* opt, Qt::Alignment al, int x, int y, int width, int height);
    static void drawText(const QString& text, QStylePainter* painter, const QStyleOption* opt, Qt::Alignment al, const QRect& rect);
};

#endif  // SARIBBONDRAWHELPER_H

/*** End of inlined file: SARibbonDrawHelper.h ***/

/*** Start of inlined file: SARibbonLineEdit.h ***/
#ifndef SARIBBONLINEEDIT_H
#define SARIBBONLINEEDIT_H

#include <QLineEdit>

/**
 * @brief The SARibbonLineEdit class
 */
class SA_RIBBON_EXPORT SARibbonLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    SARibbonLineEdit(QWidget* parent = Q_NULLPTR);
};

#endif  // SARIBBONLINEEDIT_H

/*** End of inlined file: SARibbonLineEdit.h ***/

/*** Start of inlined file: SARibbonCheckBox.h ***/
#ifndef SARIBBONCHECKBOX_H
#define SARIBBONCHECKBOX_H

#include <QCheckBox>

/**
 * @brief The SARibbonCheckBox class
 */
class SA_RIBBON_EXPORT SARibbonCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    SARibbonCheckBox(QWidget* parent = Q_NULLPTR);
};

#endif  // SARIBBONCHECKBOX_H

/*** End of inlined file: SARibbonCheckBox.h ***/

/*** Start of inlined file: SARibbonComboBox.h ***/
#ifndef SARIBBONCOMBOBOX_H
#define SARIBBONCOMBOBOX_H

#include <QComboBox>

/**
 * @brief QComboBox��Ribbon��ʾ��������ʾQIcon��windowTitle�����
 */
class SA_RIBBON_EXPORT SARibbonComboBox : public QComboBox
{
    Q_OBJECT
public:
    SARibbonComboBox(QWidget* parent = Q_NULLPTR);
};

#endif  // SARIBBONCOMBOBOX_H

/*** End of inlined file: SARibbonComboBox.h ***/

/*** Start of inlined file: SARibbonButtonGroupWidget.h ***/
#ifndef SARIBBONBUTTONGROUPWIDGET_H
#define SARIBBONBUTTONGROUPWIDGET_H

#include <QToolButton>
#include <QMenu>
#include <QFrame>

/**
 * @brief ���ڹ���һ��Action,������QToolBar
 */
class SA_RIBBON_EXPORT SARibbonButtonGroupWidget : public QFrame
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonButtonGroupWidget)
public:
    SARibbonButtonGroupWidget(QWidget* parent = Q_NULLPTR);
    ~SARibbonButtonGroupWidget() Q_DECL_OVERRIDE;

    //���ɲ����һ��action
    QAction* addAction(QAction* a);
    QAction* addAction(const QString& text, const QIcon& icon, QToolButton::ToolButtonPopupMode popMode = QToolButton::InstantPopup);
    QAction* addMenu(QMenu* menu, QToolButton::ToolButtonPopupMode popMode = QToolButton::InstantPopup);
    QAction* addSeparator();
    QAction* addWidget(QWidget* w);
    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

signals:

    /**
     * @brief �ο�QToolBar::actionTriggered���ź�
     * @param action
     */
    void actionTriggered(QAction* action);

protected:
    virtual void actionEvent(QActionEvent* e) Q_DECL_OVERRIDE;
};

#endif  // SARIBBONBUTTONGROUPWIDGET_H

/*** End of inlined file: SARibbonButtonGroupWidget.h ***/

/*** Start of inlined file: SARibbonStackedWidget.h ***/
#ifndef SARIBBONSTACKEDWIDGET_H
#define SARIBBONSTACKEDWIDGET_H
#include <QStackedWidget>

class QHideEvent;
class QResizeEvent;

/**
 * @brief ��qdialog���ܵ�stackwidget����������С��ʱstack����dialog����������
 */
class SA_RIBBON_EXPORT SARibbonStackedWidget : public QStackedWidget
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonStackedWidget)
public:
    SARibbonStackedWidget(QWidget* parent);
    ~SARibbonStackedWidget();
    void setPopupMode();
    bool isPopupMode() const;
    void setNormalMode();
    bool isNormalMode() const;
    void exec();

    //����stacked����Ĵ��ڻ�����stacked�Ĵ�С�仯���仯��С
    void setAutoResize(bool autoresize);
    bool isAutoResize() const;
    void moveWidget(int from, int to);

protected:
    //    void mouseReleaseEvent(QMouseEvent *e);
    void hideEvent(QHideEvent* e) override;

signals:
    /**
     * @brief hidWindow
     */
    void hidWindow();
};

#endif  // SARIBBONSTACKEDWIDGET_H

/*** End of inlined file: SARibbonStackedWidget.h ***/

/*** Start of inlined file: SARibbonSeparatorWidget.h ***/
#ifndef SARIBBONSEPARATORWIDGET_H
#define SARIBBONSEPARATORWIDGET_H

#include <QWidget>
#include <QStyleOption>

///
/// \brief ������ʾ�ָ���
///
class SA_RIBBON_EXPORT SARibbonSeparatorWidget : public QWidget
{
    Q_OBJECT
public:
    SARibbonSeparatorWidget(int height, QWidget* parent = nullptr);
    SARibbonSeparatorWidget(QWidget* parent = nullptr);
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;

    //���÷ָ��ߵ����¾���
    void setTopBottomMargins(int top, int bottom);

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

private:
    int m_topMargins;     ///< �������,Ĭ��4
    int m_bottomMargins;  ///< �ײ����,Ĭ��4
};

#endif  // SARIBBONSEPARATORWIDGET_H

/*** End of inlined file: SARibbonSeparatorWidget.h ***/

/*** Start of inlined file: SARibbonCtrlContainer.h ***/
#ifndef SARIBBONCTROLCONTAINER_H
#define SARIBBONCTROLCONTAINER_H

#include <QWidget>
#include <QScopedPointer>
class QStyleOption;

/**
 * @brief ����װ��һ��������������������᲼������SARibbonCtrlContainer������Ԥ���ռ���ʾicon����title
 *
 * ----------------------
 * |icon|text|  widget  |
 * ----------------------
 */
class SA_RIBBON_EXPORT SARibbonCtrlContainer : public QWidget
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonCtrlContainer)
public:
    SARibbonCtrlContainer(QWidget* parent = Q_NULLPTR);
    ~SARibbonCtrlContainer();

    void setEnableShowIcon(bool b);
    void setEnableShowTitle(bool b);
    //�ж��Ƿ������������
    bool hasContainerWidget() const;
    //ͼ��
    void setIcon(const QIcon& i);
    QIcon getIcon() const;
    //ͼ��
    void setText(const QString& t);
    QString getText() const;
    //���ô���
    void setContainerWidget(QWidget* w);
    QWidget* getContainerWidget();
    const QWidget* getContainerWidget() const;
};

#endif  // SARIBBONCTROLCONTAINER_H

/*** End of inlined file: SARibbonCtrlContainer.h ***/

/*** Start of inlined file: SARibbonQuickAccessBar.h ***/
#ifndef SARIBBONQUICKACCESSBAR_H
#define SARIBBONQUICKACCESSBAR_H

#include <QMenu>
#include <QToolButton>
class SARibbonToolButton;

///
/// \brief ribbon���϶����Ŀ�����Ӧ��
///
class SA_RIBBON_EXPORT SARibbonQuickAccessBar : public SARibbonCtrlContainer
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonQuickAccessBar)
public:
    SARibbonQuickAccessBar(QWidget* parent = 0);
    ~SARibbonQuickAccessBar();
    void addSeparator();
    void addAction(QAction* act);
    void addWidget(QWidget* w);
    void addMenu(QMenu* m, QToolButton::ToolButtonPopupMode popMode = QToolButton::InstantPopup);
};

#endif  // SARIBBONQUICKACCESSBAR_H

/*** End of inlined file: SARibbonQuickAccessBar.h ***/

/*** Start of inlined file: SARibbonTabBar.h ***/
#ifndef SARIBBONTABBAR_H
#define SARIBBONTABBAR_H

#include <QTabBar>
#include <QMargins>

/**
 * @brief The SARibbonTabBar class
 */
class SA_RIBBON_EXPORT SARibbonTabBar : public QTabBar
{
    Q_OBJECT
public:
    SARibbonTabBar(QWidget* parent = Q_NULLPTR);
    const QMargins& tabMargin() const;
    void setTabMargin(const QMargins& tabMargin);

private:
    QMargins m_tabMargin;
};

#endif  // SARIBBONTABBAR_H

/*** End of inlined file: SARibbonTabBar.h ***/

/*** Start of inlined file: SARibbonControlButton.h ***/
#ifndef SARIBBONCONTROLBUTTON_H
#define SARIBBONCONTROLBUTTON_H
#include <QToolButton>

/**
 * @brief ����SARibbonPannel��control button
 *
 * Ϊ�˷�ֹ�ⲿqss��Ӱ�죬�����̳�һ����
 */
class SA_RIBBON_EXPORT SARibbonControlButton : public QToolButton
{
    Q_OBJECT
public:
    SARibbonControlButton(QWidget* parent = 0);
};

#endif  // SARIBBONPANNELTOOLBUTTON_H

/*** End of inlined file: SARibbonControlButton.h ***/

/*** Start of inlined file: SARibbonMenu.h ***/
#ifndef SARIBBONMENU_H
#define SARIBBONMENU_H

#include <QMenu>

///
/// \brief ����ribbon��menu
/// ����ͨ��StyleSheet������ʽ����Ӱ��QMenu
///
class SA_RIBBON_EXPORT SARibbonMenu : public QMenu
{
    Q_OBJECT
public:
    explicit SARibbonMenu(QWidget* parent = Q_NULLPTR);
    explicit SARibbonMenu(const QString& title, QWidget* parent = Q_NULLPTR);
    QAction* addRibbonMenu(SARibbonMenu* menu);
    SARibbonMenu* addRibbonMenu(const QString& title);
    SARibbonMenu* addRibbonMenu(const QIcon& icon, const QString& title);
    QAction* addWidget(QWidget* w);
};

#endif  // SARIBBONMENU_H

/*** End of inlined file: SARibbonMenu.h ***/

/*** Start of inlined file: SARibbonPannelOptionButton.h ***/
#ifndef SARIBBONPANNELOPTIONBUTTON_H
#define SARIBBONPANNELOPTIONBUTTON_H
#include <QToolButton>

class QAction;

/**
 * @brief Pannel���½ǵĲ�����ť
 *
 * �˰�ť��һ��action������ʹ��@ref SARibbonPannel::addOptionAction �����������ɴ˰�ť��������˵
 * �û�������Ҫֱ�Ӳ������࣬����������ʽ���
 * ���һ��Ҫ���ش˰�ť������ͨ������@ref SARibbonElementCreateDelegate
 * �� @ref SARibbonElementCreateDelegate::createRibbonPannelOptionButton��ʵ���µ�OptionButton
 *
 */
class SA_RIBBON_EXPORT SARibbonPannelOptionButton : public QToolButton
{
    Q_OBJECT
public:
    SARibbonPannelOptionButton(QWidget* parent = Q_NULLPTR);
    //�б���setDefaultAction �˺���ֻ����action����Ӧ����������text��icon��
    void connectAction(QAction* action);
};

#endif  // SAROBBONPANNELOPTIONBUTTON_H

/*** End of inlined file: SARibbonPannelOptionButton.h ***/

/*** Start of inlined file: SARibbonPannelItem.h ***/
#ifndef SARIBBONPANNELITEM_H
#define SARIBBONPANNELITEM_H

#include <QWidgetItem>
#include <QAction>
#include <functional>
class SARibbonToolButton;
/**
 * @brief �Ƕ�pannel�����Ӵ��ڵĳ��󣬲ο�qt��toolbar
 *
 * �ο�qt��toolbar��pannel�����Ӵ������ݶ�ͨ��QAction���г��󣬰���gallery��Щ���ڣ�Ҳ��ͨ��QAction���г���
 * QAction���ջ�ת��ΪSARibbonPannelItem��ÿ��SARibbonPannelItem������һ��widget��SARibbonPannel�Ĳ���
 * �ͻ���SARibbonPannelItem
 *
 * �޴��ڵ�action�����ڲ�����һ��SARibbonToolButton��
 */
class SA_RIBBON_EXPORT SARibbonPannelItem : public QWidgetItem
{
public:
    /**
     * @brief �������е�ռ�ȣ�ribbon����large��media��small����ռ��
     */
    enum RowProportion
    {
        None,  ///< Ϊ����ռ�ȣ���ʱ�򽫻�����expandingDirections���жϣ��������Qt::Vertical���͵�ͬ��Large���������Small
        Large,   ///< ��ռ�ȣ�һ��widget�ĸ߶Ȼ��������pannel
        Medium,  ///< ��ռ�ȣ���@ref SARibbonPannel::pannelLayoutMode Ϊ @ref SARibbonPannel::ThreeRowMode ʱ�Ż������ã���Ҫͬһ������������Mediumʱ������������ռ������
        Small  ///< Сռ�ȣ�ռSARibbonPannel��һ�У�Medium�ڲ���������ʱҲ���ΪSmall���������ΪLarge
    };
    SARibbonPannelItem(QWidget* widget);
    bool isEmpty() const Q_DECL_OVERRIDE;

    short rowIndex;             ///< ��¼��ǰitem���ڵڼ��У�hideģʽ��Ϊ-1
    int columnIndex;            ///< ��¼��ǰitem���ڵڼ��У�hideģʽ��Ϊ-1
    QRect itemWillSetGeometry;  ///< �ڵ���SARibbonPannelLayout::updateGeomArray���������˴���ʵ�����õ�ʱ���QWidgetItem::setGeometry����Geometry
    QAction* action;            /// < ��¼action���ο�QToolBarLayoutItem
    bool customWidget;  ///< ����û�д��ڵ�action��ʵ��Ҳ����һ��SARibbonToolButton��������ʱҪdelete��
    SARibbonPannelItem::RowProportion rowProportion;  ///< �е�ռ�ȣ�ribbon����large��media��small����ռ��,��@ref RowProportion
};
#ifndef SARibbonPannelItemRowProportionPropertyName
#define SARibbonPannelItemRowProportionPropertyName "SARibbonPannelItem_RowProportion"
#endif
#endif  // SARIBBONPANNELITEM_H

/*** End of inlined file: SARibbonPannelItem.h ***/

/*** Start of inlined file: SARibbonPannelLayout.h ***/
#ifndef SARIBBONPANNELLAYOUT_H
#define SARIBBONPANNELLAYOUT_H

#include <QLayout>

class SARibbonPannel;

/**
 * @brief ���SARibbonPannel�Ĳ���
 *
 * SARibbonPannelLayoutʵ����һ���в��֣�ÿһ����2~3�У������ڶ�ռ����
 *
 * ���ĺ����� @ref SARibbonPannelLayout::createItem
 *
 * @note QLayout::contentsMargins ��������������,���Ҫ����contentsMargins��ʹ��@sa setPannelContentsMargins
 */
class SA_RIBBON_EXPORT SARibbonPannelLayout : public QLayout
{
    Q_OBJECT
    friend class SARibbonPannel;

public:
    SARibbonPannelLayout(QWidget* p = 0);
    ~SARibbonPannelLayout();
    virtual int indexOf(QAction* action) const;

    // SARibbonPannelLayout additem ��Ч
    void addItem(QLayoutItem* item) Q_DECL_OVERRIDE;

    // SARibbonPannel��Ҫͨ���˺��������action
    void insertAction(int index, QAction* act, SARibbonPannelItem::RowProportion rp = SARibbonPannelItem::None);

    //
    QLayoutItem* itemAt(int index) const Q_DECL_OVERRIDE;
    QLayoutItem* takeAt(int index) Q_DECL_OVERRIDE;
    int count() const Q_DECL_OVERRIDE;

    bool isEmpty() const Q_DECL_OVERRIDE;
    void invalidate() Q_DECL_OVERRIDE;
    Qt::Orientations expandingDirections() const Q_DECL_OVERRIDE;

    void setGeometry(const QRect& rect) Q_DECL_OVERRIDE;
    QSize minimumSize() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    //ͨ��action��ȡSARibbonPannelItem
    SARibbonPannelItem* pannelItem(QAction* action) const;

    //��ȡ���һ����ӵ�item
    SARibbonPannelItem* lastItem() const;

    //��ȡ������ɵĴ���
    QWidget* lastWidget() const;

    //�ƶ�����item
    void move(int from, int to);

    //�ж��Ƿ���Ҫ���²���
    bool isDirty() const;

    //�����ͼ��ĸ߶�
    static int calcLargeHeight(const QRect& setrect, const SARibbonPannel* pannel);

public:
    //ȫ�ֵ�contentsMargins
    static const QMargins& pannelContentsMargins();
    static void setPannelContentsMargins(const QMargins& m);

protected:
    //����action
    void layoutActions();

    //��actionת��Ϊitem�����ڴ�Action���˺����ᴴ��SARibbonToolButton,
    // rp���ڸ���Layout����ʲô���Ĵ��ڣ���ϸ��SARibbonPannelItem::RowProportion
    SARibbonPannelItem* createItem(QAction* action, SARibbonPannelItem::RowProportion rp = SARibbonPannelItem::None);
    void updateGeomArray(const QRect& setrect);

    //���¼�����չ���룬�˺���������updateGeomArray����֮�����
    void recalcExpandGeomArray(const QRect& setrect);

private:
    //���������е�����
    // QMap<int,QRect> columnsGeometry() const;
    //�������������㴰�ڵĿ�ȣ��Լ������
    void columnWidthInfo(int colindex, int& width, int& maximum) const;

private:
    QList< SARibbonPannelItem* > m_items;
    int m_columnCount;  ///< ��¼�ж�����
    bool m_expandFlag;  ///< ����Ƿ��ǻ���չ��
    QSize m_sizeHint;   ///< sizeHint���صĳߴ�
    bool m_dirty;       ///< ���ڱ���Ƿ���Ҫˢ��Ԫ�أ��ο�QToolBarLayoutԴ��
    int m_largeHeight;  ///< ��¼��ͼ��ĸ߶�
    /**
     * @brief ͳһ��contentsMargins���˲�����Ϊ��̬���������Խ���ȫ������
     */
    static QMargins s_contentsMargins;
};

#endif  // SARIBBONPANNELLAYOUT_H

/*** End of inlined file: SARibbonPannelLayout.h ***/

/*** Start of inlined file: SARibbonPannel.h ***/
#ifndef SARIBBONPANNEL_H
#define SARIBBONPANNEL_H

#include <QWidget>
#include <QLayout>

class SARibbonMenu;
class SARibbonGallery;
class QGridLayout;
class SARibbonPannelOptionButton;

/**
 * @brief pannelҳ���ڣ�pannel��ribbon��������ڳзſؼ�
 *
 * ribbon��pannel��Ϊ����ģʽ������ģʽ����officeΪ�����ribbonΪ3��ģʽ����WPSΪ����ġ������ɡ�����2��ģʽ��
 * SARibbon��ͨ��SARibbonBar��@ref SARibbonBar::RibbonStyle ��ָ��ģʽ(ͨ������@ref SARibbonBar::setRibbonStyle )
 *
 * ��pannel�У�����ͨ��@ref setExpanding ����ָ��pannelˮƽ��չ�����pannel����û����ˮƽ��չ�Ŀؼ����������ף���ˣ�
 * ������pannel������ˮƽ��չ�Ŀؼ��磨@ref SARibbonGallery ����ָ���������
 *
 * pannel�Ĳ���ͨ��@ref SARibbonPannelLayout ��ʵ�֣�������������֣�����ͨ���̳�@ref
 * SARibbonElementCreateDelegate::createRibbonPannel �������ش����Լ����ֵ�pannel���������̳ж�Ӧ���麯��
 */
class SA_RIBBON_EXPORT SARibbonPannel : public QWidget
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonPannel)
    friend class SARibbonCategory;
    friend class SARibbonCategoryPrivate;
    friend class SARibbonCustomizeWidgetPrivate;
    Q_PROPERTY(bool isCanCustomize READ isCanCustomize WRITE setCanCustomize)
    Q_PROPERTY(bool isExpanding READ isExpanding WRITE setExpanding)
    Q_PROPERTY(QString pannelName READ pannelName WRITE setPannelName)
public:
public:
    SARibbonPannel(QWidget* parent = nullptr);
    SARibbonPannel(const QString& name, QWidget* parent = nullptr);
    ~SARibbonPannel() Q_DECL_OVERRIDE;
    using QWidget::addAction;
    enum PannelLayoutMode
    {
        ThreeRowMode,  ///< ���в���ģʽ��office�������в���ģʽ��pannel�ܲ���3��Сtoolbutton��Ĭ��ģʽ
        TwoRowMode  ///< ���в���ģʽ��wps�ĺ�������ģʽ�������в���ģʽ��pannel�ܲ���2��Сtoolbutton
    };

    //��action�����������ý�action�У�action����Я����������
    static void setActionRowProportionProperty(QAction* action, SARibbonPannelItem::RowProportion rp);

    //��ȡaction��������
    static SARibbonPannelItem::RowProportion getActionRowProportionProperty(QAction* action);

    //����action������Ϊ�������Ծ�����ribbon pannel����ʾ��ʽ
    void setActionRowProportion(QAction* action, SARibbonPannelItem::RowProportion rp);

    //��action���뵽pannel
    SARibbonToolButton* addAction(QAction* action, SARibbonPannelItem::RowProportion rp);

    //��action���뵽pannel�����Դ�ͼ����ʾ
    SARibbonToolButton* addLargeAction(QAction* action);

    //��action���뵽pannel��������ģʽ�»�����ͼ����ʾ
    SARibbonToolButton* addMediumAction(QAction* action);

    //��action���뵽pannel������Сͼ����ʾ
    SARibbonToolButton* addSmallAction(QAction* action);

    //���ɲ����һ��action
    void addAction(QAction* act, QToolButton::ToolButtonPopupMode popMode, SARibbonPannelItem::RowProportion rp = SARibbonPannelItem::Large);

    QAction* addAction(const QString& text,
                       const QIcon& icon,
                       QToolButton::ToolButtonPopupMode popMode,
                       SARibbonPannelItem::RowProportion rp = SARibbonPannelItem::Large);

    //���menu
    SARibbonToolButton* addMenu(QMenu* menu,
                                SARibbonPannelItem::RowProportion rp,
                                QToolButton::ToolButtonPopupMode popMode = QToolButton::InstantPopup);

    //���action menu
    SARibbonToolButton* addActionMenu(QAction* action, QMenu* menu, SARibbonPannelItem::RowProportion rp);

    // action menu,action menu��һ�������menu,���ɵ������action��Ҳ�ɵ����˵�
    SARibbonToolButton* addLargeActionMenu(QAction* action, QMenu* menu);

    //�����ͨ��˵�
    SARibbonToolButton* addLargeMenu(QMenu* menu, QToolButton::ToolButtonPopupMode popMode = QToolButton::InstantPopup);

    //�����ͨС��ť�˵�
    SARibbonToolButton* addSmallMenu(QMenu* menu, QToolButton::ToolButtonPopupMode popMode = QToolButton::InstantPopup);

    //��Ӵ���
    QAction* addWidget(QWidget* w, SARibbonPannelItem::RowProportion rp);

    //��Ӵ���,ռ��ribbon��һ��
    QAction* addSmallWidget(QWidget* w);

    //��Ӵ���,ռ��ribbon��һ��
    QAction* addMediumWidget(QWidget* w);

    //��Ӵ��ڣ�ռ��������
    QAction* addLargeWidget(QWidget* w);

    //���һ��Gallery
    SARibbonGallery* addGallery();

    //��ӷָ���
    QAction* addSeparator(int top = 6, int bottom = 6);

    //��pannel�а�action��Ӧ��button��ȡ���������actionû�ж�Ӧ��button���ͷ���nullptr
    SARibbonToolButton* actionToRibbonToolButton(QAction* action);

    //��Ӳ���action�����Ҫȥ��������nullptrָ�뼴�ɣ�SARibbonPannel�����QAction������Ȩ���й���
    void addOptionAction(QAction* action);

    //�ж��Ƿ����OptionAction
    bool isHaveOptionAction() const;

    //��ȡ���е�buttons
    QList< SARibbonToolButton* > ribbonToolButtons() const;

    //��ȡPannelLayoutMode
    PannelLayoutMode pannelLayoutMode() const;

    //�ж��Ƿ�Ϊ2��ģʽ
    bool isTwoRow() const
    {
        return (TwoRowMode == pannelLayoutMode());
    }

    virtual QSize sizeHint() const Q_DECL_OVERRIDE;
    virtual QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    //��pannel����Ϊ��չģʽ����ʱ��Ŵ�ˮƽ����
    void setExpanding(bool isExpanding = true);

    //�Ƿ�����չģʽ
    bool isExpanding() const;

    //�������߶ȣ�����3��ģʽ����Ч
    int titleHeight() const;

    // optionActionButton�ĳߴ�
    virtual QSize optionActionButtonSize() const;

    // action��Ӧ�Ĳ���index���˲���һ�������ƶ�moveAction���������岻��
    int actionIndex(QAction* act) const;

    //�ƶ�action
    void moveAction(int from, int to);

    //�ж��Ƿ�����Զ���
    bool isCanCustomize() const;
    void setCanCustomize(bool b);

    //����
    QString pannelName() const;
    void setPannelName(const QString& title);

    //��ͼ��ĸ߶�
    int largeHeight() const;
    //��ȡ���ֶ�Ӧ��item
    const QList< SARibbonPannelItem* >& ribbonPannelItem() const;
    //ȫ�ֵı������߶�
    static int pannelTitleHeight();
    static void setPannelTitleHeight(int h);
signals:

    /**
     * @brief ��ͬ��QToolBar::actionTriggered
     * @param action
     */
    void actionTriggered(QAction* action);

protected:
    //����PannelLayoutMode���˺�������Ϊprotect���������
    void setPannelLayoutMode(PannelLayoutMode mode);
    void resetLayout(PannelLayoutMode newmode);
    void resetLargeToolButtonStyle();
    static QSize maxHightIconSize(const QSize& size, int h);
    virtual void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    virtual void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;
    virtual void actionEvent(QActionEvent* e) Q_DECL_OVERRIDE;
};

#endif  // SARIBBONPANNEL_H

/*** End of inlined file: SARibbonPannel.h ***/

/*** Start of inlined file: SARibbonCategory.h ***/
#ifndef SARIBBONCATEGORY_H
#define SARIBBONCATEGORY_H

#include <QWidget>

#include <QScopedPointer>
#include <QPushButton>
#include <QWheelEvent>

class QHBoxLayout;
class QWheelEvent;
class SARibbonBar;

/**
 * @brief һ��ribbon tabҳ
 * @note SARibbonCategory��windowTitleӰ��������SARibbonBar�ı�ǩ��ʾ��
 * ���Ҫ�ı�ǩ���֣�ֱ�ӵ���SARibbonCategory��setWindowTitle����
 */
class SA_RIBBON_EXPORT SARibbonCategory : public QWidget
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonCategory)
    friend class SARibbonBar;
    friend class SARibbonContextCategory;
    Q_PROPERTY(bool isCanCustomize READ isCanCustomize WRITE setCanCustomize)
    Q_PROPERTY(QString categoryName READ categoryName WRITE setCategoryName)
public:
    SARibbonCategory(QWidget* p = nullptr);
    ~SARibbonCategory();

    // category������
    QString categoryName() const;

    //����category���֣���ͬsetWindowTitle
    void setCategoryName(const QString& title);

    //����ģʽ
    SARibbonPannel::PannelLayoutMode ribbonPannelLayoutMode() const;

    //���pannel
    SARibbonPannel* addPannel(const QString& title);

    //���pannel
    void addPannel(SARibbonPannel* pannel);

    // qt designerר��
    Q_INVOKABLE void addPannel(QWidget* pannel);

    //����pannel
    SARibbonPannel* insertPannel(const QString& title, int index);

    //ͨ�����ֲ���pannel
    SARibbonPannel* pannelByName(const QString& title) const;

    //ͨ��ObjectName����pannel
    SARibbonPannel* pannelByObjectName(const QString& objname) const;

    //ͨ�������ҵ�pannel���������������Χ���᷵��nullptr
    SARibbonPannel* pannelByIndex(int index) const;

    //����pannel��index
    int pannelIndex(SARibbonPannel* p) const;

    //�ƶ�һ��Pannel��from index��to index
    void movePannel(int from, int to);

    //��pannel��Category���Ƴ����������٣���ʱpannel������Ȩ�黹������
    bool takePannel(SARibbonPannel* pannel);

    //�Ƴ�Pannel��Category��ֱ�ӻ���SARibbonPannel�ڴ�
    bool removePannel(SARibbonPannel* pannel);
    bool removePannel(int index);

    //���ñ���
    void setBackgroundBrush(const QBrush& brush);

    //�������е�Pannel
    QList< SARibbonPannel* > pannelList() const;

    //
    QSize sizeHint() const Q_DECL_OVERRIDE;

    //�����ContextCategory���˺�������true
    bool isContextCategory() const;

    // pannel�ĸ���
    int pannelCount() const;

    //�ж��Ƿ�����Զ���
    bool isCanCustomize() const;
    void setCanCustomize(bool b);

    //��ȡ��Ӧ��ribbonbar�����û�м���ribbonbar�Ĺ�����ֵΪnull
    SARibbonBar* ribbonBar() const;

    //ˢ��category�ĳߴ粼��
    void updateItemGeometry();
protected slots:
    void onLeftScrollButtonClicked();
    void onRightScrollButtonClicked();

protected:
    //�¼�����
    bool event(QEvent* e) Q_DECL_OVERRIDE;

    //
    void resizeEvent(QResizeEvent* e) Q_DECL_OVERRIDE;

    //����pannel��ģʽ
    void setRibbonPannelLayoutMode(SARibbonPannel::PannelLayoutMode m);
    bool eventFilter(QObject* watched, QEvent* event) Q_DECL_OVERRIDE;

    //��������¼�
    void wheelEvent(QWheelEvent* event) Q_DECL_OVERRIDE;

    //�������������ı�ǩ
    void markIsContextCategory(bool isContextCategory = true);

private:
    void setRibbonBar(SARibbonBar* bar);
};

/**
 * @brief SARibbonCategory�޷���ȫ��ʾʱ����ʾ�ĵ�����ť
 *
 * ���¶�����Ϊ�˷�ֹ���ⲿ����ʽӰ��,ͬʱ����ʹ��SARibbonCategoryScrollButton����ʽ����
 */
class SA_RIBBON_EXPORT SARibbonCategoryScrollButton : public QToolButton
{
    Q_OBJECT
public:
    SARibbonCategoryScrollButton(Qt::ArrowType arr, QWidget* p = nullptr);
};

#endif  // SARIBBONCATEGORY_H

/*** End of inlined file: SARibbonCategory.h ***/

/*** Start of inlined file: SARibbonCategoryLayout.h ***/
#ifndef SARIBBONCATEGORYLAYOUT_H
#define SARIBBONCATEGORYLAYOUT_H

#include <QLayout>
#include <QList>
#include <QMap>

class SARibbonPannel;
class SARibbonCategoryLayoutItem;
class SARibbonSeparatorWidget;

/**
 * @brief The SARibbonCategoryLayout class
 */
class SA_RIBBON_EXPORT SARibbonCategoryLayout : public QLayout
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonCategoryLayout)
public:
    SARibbonCategoryLayout(SARibbonCategory* parent);
    ~SARibbonCategoryLayout();

    SARibbonCategory* ribbonCategory();

    virtual void addItem(QLayoutItem* item) Q_DECL_OVERRIDE;
    virtual QLayoutItem* itemAt(int index) const Q_DECL_OVERRIDE;
    virtual QLayoutItem* takeAt(int index) Q_DECL_OVERRIDE;
    SARibbonCategoryLayoutItem* takePannelItem(int index);
    SARibbonCategoryLayoutItem* takePannel(SARibbonPannel* pannel);
    virtual int count() const Q_DECL_OVERRIDE;

    //׷��һ��pannel
    void addPannel(SARibbonPannel* pannel);

    //����һ��pannel
    void insertPannel(int index, SARibbonPannel* pannel);

    void setGeometry(const QRect& rect) Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSize() const Q_DECL_OVERRIDE;
    Qt::Orientations expandingDirections() const Q_DECL_OVERRIDE;
    void invalidate() Q_DECL_OVERRIDE;

    //���³ߴ�
    void updateGeometryArr();

    //ִ��λ�õ���
    void doLayout();

    //��������pannels
    QList< SARibbonPannel* > pannels() const;

private slots:
    void onLeftScrollButtonClicked();
    void onRightScrollButtonClicked();
};

/**
 * @brief SARibbonCategoryLayoutItem�����ڱ�ʶSARibbonCategoryLayout��item
 */
class SA_RIBBON_EXPORT SARibbonCategoryLayoutItem : public QWidgetItem
{
public:
    SARibbonCategoryLayoutItem(SARibbonPannel* w);
    SARibbonSeparatorWidget* separatorWidget;
    QRect mWillSetGeometry;           ///< pannel��Ҫ���õ�Geometry
    QRect mWillSetSeparatorGeometry;  ///< pannel��Ҫ���õ�Separator��Geometry
};
#endif  // SARIBBONCATEGORYLAYOUT_H

/*** End of inlined file: SARibbonCategoryLayout.h ***/

/*** Start of inlined file: SARibbonContextCategory.h ***/
#ifndef SARIBBONCONTEXTCATEGORY_H
#define SARIBBONCONTEXTCATEGORY_H

#include <QWidget>

/**
 * @brief ���������ı�ǩ����
 */
class SA_RIBBON_EXPORT SARibbonContextCategory : public QObject
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonContextCategory)
public:
    SARibbonContextCategory(QWidget* parent = 0);
    ~SARibbonContextCategory();
    //������Ŀ¼�������Ŀ¼
    SARibbonCategory* addCategoryPage(const QString& title);
    void addCategoryPage(SARibbonCategory* category);
    //��ȡ�����ı�ǩ�¹���ı�ǩ����
    int categoryCount() const;

    //����id
    void setId(const QVariant& id);
    QVariant id() const;

    //������������ɫ
    void setContextColor(const QColor color);
    QColor contextColor() const;

    //�����ı�ǩ������
    QString contextTitle() const;
    void setContextTitle(const QString& contextTitle);

    //��ȡ��Ӧ��tabҳ
    SARibbonCategory* categoryPage(int index);

    //��ȡ���е�SARibbonCategory*
    QList< SARibbonCategory* > categoryList() const;

    //�Ƴ�category
    bool takeCategory(SARibbonCategory* category);

    //�ж��������Ƿ�ά���˴�SARibbonCategory
    bool isHaveCategory(SARibbonCategory* category) const;
signals:
    /**
     * @brief ��ǩ����������
     * @param category
     */
    void categoryPageAdded(SARibbonCategory* category);

    /**
     * @brief ��ǩ���������Ƴ�
     * @param category
     */
    void categoryPageRemoved(SARibbonCategory* category);

    /**
     * @brief �����ĵı��ⷢ���ı�
     * @param title
     */
    void contextTitleChanged(const QString& title);

    /**
     * @brief �����ı�ǩά���ı�ǩҳ���ַ����˸ı�
     * @param category �����ı�������ı�ǩҳ
     * @param title ������
     */
    void categoryTitleChanged(SARibbonCategory* category, const QString& title);
private slots:
    void onCategoryTitleChanged(const QString& title);

protected:
    //��ȡ��������
    QWidget* parentWidget() const;
    virtual bool eventFilter(QObject* watched, QEvent* e) override;
};

#endif  // SARIBBONCONTEXTCATEGORY_H

/*** End of inlined file: SARibbonContextCategory.h ***/

/*** Start of inlined file: SARibbonGalleryItem.h ***/
#ifndef SARIBBONGALLERYITEM_H
#define SARIBBONGALLERYITEM_H

#include <QIcon>
#include <QVariant>
#include <QMap>
#include <QAction>
class SARibbonGalleryGroup;

///
/// \brief ����QStandardItem��GalleryItem
///
class SA_RIBBON_EXPORT SARibbonGalleryItem
{
public:
    SARibbonGalleryItem();
    SARibbonGalleryItem(const QString& text, const QIcon& icon);
    SARibbonGalleryItem(QAction* act);
    virtual ~SARibbonGalleryItem();
    //���ý�ɫ
    void setData(int role, const QVariant& data);
    virtual QVariant data(int role) const;

    //������������
    void setText(const QString& text);
    QString text() const;

    //����tooltip
    void setToolTip(const QString& text);
    QString toolTip() const;

    //����ͼ��
    void setIcon(const QIcon& ico);
    QIcon icon() const;

    //�����Ƿ�ɼ�
    bool isSelectable() const;
    void setSelectable(bool isSelectable);

    //�����Ƿ��ѡ
    bool isEnable() const;
    void setEnable(bool isEnable);

    //����item��flag
    void setFlags(Qt::ItemFlags flag);
    virtual Qt::ItemFlags flags() const;

    //����action
    void setAction(QAction* act);
    QAction* action();

    //���ֶ��뷽ʽ
    void setTextAlignment(Qt::Alignment a);
    Qt::Alignment getTextAlignment() const;

private:
    friend class SARibbonGalleryGroupModel;
    QMap< int, QVariant > m_datas;
    Qt::ItemFlags m_flags;
    QAction* m_action;
};

#endif  // SARIBBONGALLERYITEM_H

/*** End of inlined file: SARibbonGalleryItem.h ***/

/*** Start of inlined file: SARibbonGalleryGroup.h ***/
#ifndef SARIBBONGALLERYGROUP_H
#define SARIBBONGALLERYGROUP_H

#include <QList>
#include <QListView>
#include <QStyledItemDelegate>

///
/// \brief SARibbonGalleryGroup��Ӧ����ʾ����
///
class SA_RIBBON_EXPORT SARibbonGalleryGroupItemDelegate : public QStyledItemDelegate
{
public:
    SARibbonGalleryGroupItemDelegate(SARibbonGalleryGroup* group, QObject* parent = Q_NULLPTR);
    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;

    virtual QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;
    virtual void paintIconOnly(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    virtual void paintIconWithText(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    virtual void paintIconWithTextWordWrap(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

private:
    SARibbonGalleryGroup* m_group;
};

///
/// \brief SARibbonGalleryGroup��Ӧ��model
///
class SA_RIBBON_EXPORT SARibbonGalleryGroupModel : public QAbstractListModel
{
    Q_OBJECT
public:
    SARibbonGalleryGroupModel(QObject* parent = Q_NULLPTR);
    ~SARibbonGalleryGroupModel();
    virtual int rowCount(const QModelIndex& parent) const Q_DECL_OVERRIDE;
    virtual Qt::ItemFlags flags(const QModelIndex& index) const Q_DECL_OVERRIDE;
    virtual QVariant data(const QModelIndex& index, int role) const Q_DECL_OVERRIDE;
    virtual QModelIndex index(int row, int column, const QModelIndex& parent) const Q_DECL_OVERRIDE;
    virtual bool setData(const QModelIndex& index, const QVariant& value, int role) Q_DECL_OVERRIDE;
    void clear();
    SARibbonGalleryItem* at(int row) const;
    void insert(int row, SARibbonGalleryItem* item);
    SARibbonGalleryItem* take(int row);
    void append(SARibbonGalleryItem* item);

private:
    QList< SARibbonGalleryItem* > m_items;
};

/**
 * @brief Gallery����
 *
 * �鸺����ʾ����Gallery Item
 */
class SA_RIBBON_EXPORT SARibbonGalleryGroup : public QListView
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonGalleryGroup)
public:
    /**
     * @brief GalleryGroup��ʾ����ʽ
     */
    enum GalleryGroupStyle
    {
        IconWithText,          ///< ͼ�������
        IconWithWordWrapText,  ///< ͼ�������,���ֻỻ����ʾ����ģʽֻ���DisplayOneRow��Ч���������DisplayOneRow����ͬIconWithText
        IconOnly               ///< ֻ��ͼ��
    };

    /**
     * @brief ����Gallery��һ��pannel������ʾ��ͼ������
     */
    enum DisplayRow
    {
        DisplayOneRow   = 1,  ///< ��ʾ1�У�Ĭ��
        DisplayTwoRow   = 2,
        DisplayThreeRow = 3
    };

    SARibbonGalleryGroup(QWidget* w = 0);

    virtual ~SARibbonGalleryGroup();
    //���¼���grid�ߴ�
    void setRecalcGridSizeBlock(bool on = true);
    bool isRecalcGridSizeBlock() const;
    void recalcGridSize();
    void recalcGridSize(int galleryHeight);
    //������ʾ����ʽ
    void setGalleryGroupStyle(GalleryGroupStyle style);
    GalleryGroupStyle getGalleryGroupStyle() const;
    //���һ��item
    void addItem(const QString& text, const QIcon& icon);
    void addItem(SARibbonGalleryItem* item);
    //��һ��aciton��Ϊitem���
    void addActionItem(QAction* act);
    void addActionItemList(const QList< QAction* >& acts);

    //����һ��model�����model�ĸ�����SARibbonGalleryGroup�����Ҫ����model����Ҫ�ֶ�����model�ĸ���
    void setupGroupModel();
    SARibbonGalleryGroupModel* groupModel();
    // ����
    void setGroupTitle(const QString& title);
    QString getGroupTitle() const;
    void selectByIndex(int i);
    //������ʾ������
    void setDisplayRow(DisplayRow r);
    DisplayRow getDisplayRow() const;
    //����grid��С�Ŀ�ȣ�Ĭ��Ϊ0�������ƣ��������޶�grid�Ŀ��
    void setGridMinimumWidth(int w);
    int getGridMinimumWidth() const;
    //����grid���Ŀ�ȣ�Ĭ��Ϊ0�������ƣ��������޶�grid�Ŀ��
    void setGridMaximumWidth(int w);
    int getGridMaximumWidth() const;
    //��ȡSARibbonGalleryGroup�����actiongroup
    QActionGroup* getActionGroup() const;
private slots:
    void onItemClicked(const QModelIndex& index);
    void onItemEntered(const QModelIndex& index);
signals:
    void groupTitleChanged(const QString& title);
    /**
     * @brief ��ͬQActionGroup��triggered
     * ���м���SARibbonGalleryGroup��action���ᱻһ��QActionGroup����,����ͨ��@sa getActionGroup ��ȡ����Ӧ��actiongroup
     * @param action
     */
    void triggered(QAction* action);
    /**
     * @brief ��ͬQActionGroup��triggered
     * ���м���SARibbonGalleryGroup��action���ᱻһ��QActionGroup����,����ͨ��@sa getActionGroup ��ȡ����Ӧ��actiongroup
     * @note ��������Ҫͨ��QAbstractItemView::entered(const QModelIndex &index)������Ҫ��֤������setMouseTracking(true)
     * @param action
     */
    void hovered(QAction* action);
};

#endif  // SARIBBONGALLERYGROUP_H

/*** End of inlined file: SARibbonGalleryGroup.h ***/

/*** Start of inlined file: SARibbonGallery.h ***/
#ifndef SARIBBONGALLERY_H
#define SARIBBONGALLERY_H

#include <QFrame>

#include <QSizeGrip>
class QLabel;
class QVBoxLayout;
class SARibbonGalleryViewport;

/**
 * @brief Gallery�ؼ�
 *
 * Gallery�ؼ�����һ����ǰ�����@sa SARibbonGalleryGroup �͵����� @sa SARibbonGalleryViewport ���
 *
 * @sa SARibbonGalleryGroup �Ǽ̳�@sa QListView actionsͨ��iconչʾ��������ص����Կ��԰���QListView����
 *
 * @sa SARibbonGalleryViewport ��һ���ڲ��д�ֱ���ֵĴ��壬�ڵ�������ʱ���ѹ����SARibbonGalleryGroup��չʾ����
 *
 * ʾ�����£�
 * @code
 * SARibbonGallery* gallery = pannel1->addGallery();
 * QList< QAction* > galleryActions;
 * ...create many actions ...
 * SARibbonGalleryGroup* group1 = gallery->addCategoryActions(tr("Files"), galleryActions);
 * galleryActions.clear();
 * ...create many actions ...
 * gallery->addCategoryActions(tr("Apps"), galleryActions);
 * gallery->setCurrentViewGroup(group1);
 * @endcode
 */
class SA_RIBBON_EXPORT SARibbonGallery : public QFrame
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonGallery)
public:
    SARibbonGallery(QWidget* parent = 0);
    virtual ~SARibbonGallery();
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;
    //���һ��GalleryGroup
    SARibbonGalleryGroup* addGalleryGroup();
    //���һ��GalleryGroup
    void addGalleryGroup(SARibbonGalleryGroup* group);
    //�������һ��actions
    SARibbonGalleryGroup* addCategoryActions(const QString& title, QList< QAction* > actions);
    //���õ�ǰ��ʾ��SARibbonGalleryGroup
    void setCurrentViewGroup(SARibbonGalleryGroup* group);
    //��ȡ��ǰ��ʾ��SARibbonGalleryGroup
    SARibbonGalleryGroup* currentViewGroup() const;
    //��ȡ��������ָ��
    SARibbonGalleryViewport* getPopupViewPort() const;

public:
    //�������ұ��������ư�ť������ȣ�Ĭ��15��
    static void setGalleryButtonMaximumWidth(int w);
signals:
    /**
     * @brief ת�������SARibbonGalleryGroup::triggered
     * ���м���SARibbonGallery��action���ᱻһ��QActionGroup����,����ͨ��@sa getActionGroup ��ȡ����Ӧ��actiongroup
     * @param action
     */
    void triggered(QAction* action);
    /**
     * @brief ת�������SARibbonGalleryGroup::hovered
     * @note ��������Ҫȷ��SARibbonGalleryGroup::setMouseTracking(true)
     * @param action
     */
    void hovered(QAction* action);

public slots:
    //�Ϸ�ҳ
    virtual void pageUp();
    //�·�ҳ
    virtual void pageDown();
    //��ʾ���ഥ����Ĭ�ϵ����ڲ������SARibbonGalleryViewport���û������ش˺���ʵ���Զ���ĵ���
    virtual void showMoreDetail();
protected slots:
    void onItemClicked(const QModelIndex& index);
    virtual void onTriggered(QAction* action);

private:
    SARibbonGalleryViewport* ensureGetPopupViewPort();

protected:
    void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
};

///
/// \brief SARibbonGallery��Viewport class
///
class SARibbonGalleryViewport : public QWidget
{
    Q_OBJECT
public:
    SARibbonGalleryViewport(QWidget* parent);
    //��Ӵ��ڲ�������
    void addWidget(QWidget* w);
    //��Ӵ��ڣ�������
    void addWidget(QWidget* w, const QString& title);
    //ͨ��SARibbonGalleryGroup��ȡ��Ӧ�ı��⣬�û�����ͨ���˺�������QLabel������
    QLabel* getWidgetTitleLabel(QWidget* w);
    //�Ƴ�����
    void removeWidget(QWidget* w);
public slots:
    void widgetTitleChanged(QWidget* w, const QString& title);

private:
    QVBoxLayout* m_layout;
    QMap< QWidget*, QLabel* > _widgetToTitleLable;  ///< QWidget��lable�Ķ�Ӧ
};

#endif  // SARIBBONGALLERY_H

/*** End of inlined file: SARibbonGallery.h ***/

/*** Start of inlined file: SARibbonBar.h ***/
#ifndef SARIBBONBAR_H
#define SARIBBONBAR_H

#include <QMenuBar>
#include <QVariant>

#include <QScopedPointer>

class QAbstractButton;
class SARibbonElementFactory;
class SARibbonTabBar;
class SARibbonButtonGroupWidget;
class SARibbonQuickAccessBar;

/**
 * @brief SARibbonBar�̳���QMenuBar,��SARibbonMainWindow��ֱ���滻��ԭ����QMenuBar
 *
 * ͨ��setRibbonStyle��������ribbon�ķ��:
 *
 * @code
 * void setRibbonStyle(RibbonStyle v);
 * @endcode
 *
 * SARibbonBar�ο�office��wps���ṩ�����ַ���Ribbonģʽ,@ref SARibbonBar::RibbonStyle
 *
 * �����ribbonռ�õĿռ��㹻С��WpsLiteStyleTwoRowģʽ�ܱ�OfficeStyle��ʡ35%�ĸ߶ȿռ�
 *
 * �������ribbon?�ȿ���һ����ͳ��Menu/ToolBar��������ɵģ�
 *
 * @code
 * void MainWindow::MainWindow()
 * {
 *    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
 *    QToolBar *fileToolBar = addToolBar(tr("File"));
 *    //����action
 *    QAction *newAct = new QAction(newIcon, tr("&New"), this);
 *    fileMenu->addAction(newAct);
 *    fileToolBar->addAction(newAct);
 *
 *    QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
 *    fileMenu->addAction(openAct);
 *    fileToolBar->addAction(openAct);
 * }
 * @endcode
 *
 * ��ͳ��Menu/ToolBar��Ҫͨ��QMenu��addMenu��Ӳ˵�,ͨ��QMainWindow::addToolBar����QToolBar,
 * �ٰ�QAction���ý�QMenu��QToolBar��
 *
 * SARibbonBar�ʹ�ͳ�������ƣ���������ڴ�ͳ��Menu/ToolBar QMenu��QToolBar��ƽ���ģ�
 * Ribbon�������ԵĲ㼶��ϵ��SARibbonBar������ @ref SARibbonCategory��
 * SARibbonCategory������@ref SARibbonPannel ��SARibbonPannel������@ref SARibbonToolButton ��
 * SARibbonToolButton������QAction
 *
 * ��ˣ�����һ��ribbonֻ�����¼���������
 * @code
 * SARibbonCategory * SARibbonBar::addCategoryPage(const QString& title);
 * SARibbonPannel * SARibbonCategory::addPannel(const QString& title);
 * SARibbonToolButton * SARibbonPannel::addLargeAction(QAction *action);
 * SARibbonToolButton * SARibbonPannel::addSmallAction(QAction *action);
 * @endcode
 *
 * ������ɲ������£�
 *
 * @code
 * //��Ա����
 * SARibbonCategory* categoryMain;
 * SARibbonPannel* FilePannel;
 *
 * //����ui
 * void setupRibbonUi()
 * {
 *     ......
 *     //ribbonwindowΪSARibbonMainWindow
 *     SARibbonBar* ribbon = ribbonwindow->ribbonBar();
 *     ribbon->setRibbonStyle(SARibbonBar::WpsLiteStyle);
 *     //���һ��Main��ǩ
 *     categoryMain = ribbon->addCategoryPage(QStringLiteral("Main"));
 *     //Main��ǩ�����һ��File Pannel
 *     FilePannel = categoryMain->addPannel(QStringLiteral("FilePannel"));
 *     //��ʼΪFile Pannel���action
 *     FilePannel->addLargeAction(actionNew);
 *     FilePannel->addLargeAction(actionOpen);
 *     FilePannel->addLargeAction(actionSave);
 *     FilePannel->addSmallAction(actionImportMesh);
 *     FilePannel->addSmallAction(actionImportGeometry);
 * }
 * @endcode
 */
class SA_RIBBON_EXPORT SARibbonBar : public QMenuBar
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonBar)
    Q_PROPERTY(RibbonStyle ribbonStyle READ currentRibbonStyle WRITE setRibbonStyle)
    Q_PROPERTY(bool minimumMode READ isMinimumMode WRITE setMinimumMode)
    Q_PROPERTY(bool minimumModeButton READ haveShowMinimumModeButton WRITE showMinimumModeButton)
    Q_PROPERTY(QColor windowTitleTextColor READ windowTitleTextColor WRITE setWindowTitleTextColor)
    Q_PROPERTY(QColor tabBarBaseLineColor READ tabBarBaseLineColor WRITE setTabBarBaseLineColor)
    Q_PROPERTY(Qt::Alignment windowTitleAligment READ windowTitleAligment WRITE setWindowTitleAligment)
public:
    /**
     * @brief ����ribbon�ķ��,��һ�ֽڴ�����ʽ���ڶ��ֽڴ����Ƿ���2��
     */
    enum RibbonStyle
    {
        OfficeStyle        = 0x0000,  ///< ����office ��ribbon���
        WpsLiteStyle       = 0x0001,  ///< ����wps�Ľ��շ��
        OfficeStyleTwoRow  = 0x0100,  ///< ����office ��ribbon��� 2�й����� ���в���ģʽ��office�������в���ģʽ��pannel�ܲ���3��Сtoolbutton��Ĭ��ģʽ
        WpsLiteStyleTwoRow = 0x0101   ///< ����wps�Ľ��շ��  2�й�����
    };
    Q_ENUM(RibbonStyle)

    /**
     * @brief ���嵱ǰribbon ��״̬
     */
    enum RibbonMode
    {
        MinimumRibbonMode,  ///< ��Сģʽ
        NormalRibbonMode    ///< ����ģʽ
    };
    Q_ENUM(RibbonMode)

public:
    //�ж�RibbonStyle�Ƿ�Ϊ2��ģʽ
    static bool isTwoRowStyle(RibbonStyle s);

    //�ж��Ƿ���office��ʽ
    static bool isOfficeStyle(RibbonStyle s);

    //��ȡ�汾��Ϣ
    static QString versionString();

    //���캯��
    SARibbonBar(QWidget* parent = nullptr);
    ~SARibbonBar() Q_DECL_OVERRIDE;
    //��ȡapplicationButton
    QAbstractButton* applicationButton();

    //����applicationButton
    void setApplicationButton(QAbstractButton* btn);

    //��ȡtabbar
    SARibbonTabBar* ribbonTabBar();

    //���һ����ǩ
    SARibbonCategory* addCategoryPage(const QString& title);
    void addCategoryPage(SARibbonCategory* category);

    //Ϊ��֧��Qt designer,��ӵ�һ�����غ���
    Q_INVOKABLE void addCategoryPage(QWidget* category);

    //���һ��category��category��λ����index�������ǰcategory��������index�������뵽���
    SARibbonCategory* insertCategoryPage(const QString& title, int index);
    void insertCategoryPage(SARibbonCategory* category, int index);

    //ͨ�����ֲ���Category
    SARibbonCategory* categoryByName(const QString& title) const;

    //ͨ��ObjectName����Category
    SARibbonCategory* categoryByObjectName(const QString& objname) const;

    //ͨ�������ҵ�category���������������Χ���᷵��nullptr
    SARibbonCategory* categoryByIndex(int index) const;

    //����category,������ɾ������ȡ�ߣ�ֻ������
    void hideCategory(SARibbonCategory* category);

    //��ʾ�����ص�category
    void showCategory(SARibbonCategory* category);

    //�ж����category�Ƿ�����ʾ״̬��Ҳ����tabbar�����category
    bool isCategoryVisible(const SARibbonCategory* c) const;

    //��ȡcategory������
    int categoryIndex(const SARibbonCategory* c) const;

    //�ƶ�һ��Category��from index��to index
    void moveCategory(int from, int to);

    //��ȡ��ǰ��ʾ�����е�SARibbonCategory������δ��ʾ��SARibbonContextCategory��SARibbonCategoryҲһ������
    QList< SARibbonCategory* > categoryPages(bool getAll = true) const;

    //�Ƴ�SARibbonCategory
    void removeCategory(SARibbonCategory* category);

    //���һ�������ı�ǩ
    SARibbonContextCategory* addContextCategory(const QString& title, const QColor& color = QColor(), const QVariant& id = QVariant());
    void addContextCategory(SARibbonContextCategory* context);

    //��ʾһ�������ı�ǩ
    void showContextCategory(SARibbonContextCategory* context);

    //����һ�������ı�ǩ
    void hideContextCategory(SARibbonContextCategory* context);

    //�ж��������Ƿ�������ʾ״̬
    bool isContextCategoryVisible(SARibbonContextCategory* context);

    //���������ı�ǩ����ʾ������
    void setContextCategoryVisible(SARibbonContextCategory* context, bool visible);

    //��ȡ���е������ı�ǩ
    QList< SARibbonContextCategory* > contextCategoryList() const;

    //�Ƴ�ContextCategory
    void destroyContextCategory(SARibbonContextCategory* context);

    //����Ϊ����ģʽ
    void setMinimumMode(bool isHide);

    //��ǰRibbon�Ƿ�������ģʽ
    bool isMinimumMode() const;

    //������ʾ����ribbon��ť
    void showMinimumModeButton(bool isShow = true);

    //�Ƿ���ʾ����ribbon��ť
    bool haveShowMinimumModeButton() const;

    // ribbon tab�ĸ߶�
    int tabBarHeight() const;

    //�������ĸ߶�
    int titleBarHeight() const;

    //����tabbar�ұߵİ�ťȺ
    void activeRightButtonGroup();

    //�ҲఴťȺ
    SARibbonButtonGroupWidget* rightButtonGroup();

    //������Ӧ��
    SARibbonQuickAccessBar* quickAccessBar();

    //����ribbon�ķ��
    void setRibbonStyle(RibbonStyle v);

    //��ǰribbon�ķ��
    RibbonStyle currentRibbonStyle() const;

    //��ǰ��ģʽ
    RibbonMode currentRibbonState() const;

    //���õ�ǰribbon��index
    void setCurrentIndex(int index);

    //���ص�ǰ��tab����
    int currentIndex();

    //ȷ����ǩ��ʾ����
    void raiseCategory(SARibbonCategory* category);

    //�жϵ�ǰ����ʽ�Ƿ�Ϊ����
    bool isTwoRowStyle() const;

    //�жϵ�ǰ����ʽ�Ƿ�Ϊoffice��ʽ
    bool isOfficeStyle() const;

    //����saribbonbar��window button�ĳߴ�
    void setWindowButtonSize(const QSize& size);

    //����ribbon�Ĳ������ݣ��˺���������һЩ�ؼ��Գߴ�仯������ribbon����Ԫ�صĲ���
    void updateRibbonGeometry();
    // tabbar �ײ������һ���������˽ӿڶ���������ɫ
    void setTabBarBaseLineColor(const QColor& clr);
    QColor tabBarBaseLineColor() const;
    //���ñ�����ɫ
    void setWindowTitleTextColor(const QColor& clr);
    QColor windowTitleTextColor() const;
    //���ñ���Ķ��뷽ʽ
    void setWindowTitleAligment(Qt::Alignment al);
    Qt::Alignment windowTitleAligment() const;
    //���ð�ť������
    void setEnableWordWrap(bool on);
    bool isEnableWordWrap() const;
signals:

    /**
     * @brief Ӧ�ð�ť�����Ӧ - ���Ͻǵİ�ť��ͨ���������źŴ���Ӧ�ð�ť�����Ч��
     */
    void applicationButtonClicked();

    /**
     * @brief ��ǩҳ�仯�������ź�
     * @param index
     */
    void currentRibbonTabChanged(int index);

    /**
     * @brief ribbon��״̬�����˱仯�󴥷����ź�
     * @param nowState ���֮���ribbon״̬
     */
    void ribbonModeChanged(RibbonMode nowState);

    /**
     * @brief ribbon��״̬�����˱仯�󴥷����ź�
     * @param nowStyle ���֮���ribbon��ʽ
     */
    void ribbonStyleChanged(RibbonStyle nowStyle);

protected:
    bool eventFilter(QObject* obj, QEvent* e) override;

    //�����������tabbar�Ŀ�ȣ���Ҫ���wpsģʽ
    int calcMinTabBarWidth() const;

    //����currentRibbonStyle����mainBar�ĸ߶�
    virtual int mainBarHeight() const;
    //����
    void updateCategoryTitleToTabName();
protected slots:
    void onWindowTitleChanged(const QString& title);
    void onWindowIconChanged(const QIcon& i);
    void onCategoryWindowTitleChanged(const QString& title);
    void onStackWidgetHided();
    virtual void onCurrentRibbonTabChanged(int index);
    virtual void onCurrentRibbonTabClicked(int index);
    virtual void onCurrentRibbonTabDoubleClicked(int index);
    void onContextsCategoryPageAdded(SARibbonCategory* category);
    void onContextsCategoryCategoryNameChanged(SARibbonCategory* category, const QString& title);
    void onTabMoved(int from, int to);

private:
    int tabIndex(SARibbonCategory* obj);
    void resizeInOfficeStyle();
    void resizeInWpsLiteStyle();
    void paintInNormalStyle();
    void paintInWpsLiteStyle();
    void resizeStackedContainerWidget();

    //ˢ������ContextCategoryManagerData������ڵ���һ��Categoryɾ��ʱ����
    void updateContextCategoryManagerData();
    void updateRibbonElementGeometry();

protected:
    void paintEvent(QPaintEvent* e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent* e) Q_DECL_OVERRIDE;
    void moveEvent(QMoveEvent* event) Q_DECL_OVERRIDE;
    virtual void paintBackground(QPainter& painter);
    virtual void paintWindowTitle(QPainter& painter, const QString& title, const QRect& titleRegion);
    virtual void paintContextCategoryTab(QPainter& painter, const QString& title, QRect contextRect, const QColor& color);
};

#endif  // SARIBBONBAR_H

/*** End of inlined file: SARibbonBar.h ***/

/*** Start of inlined file: SARibbonStyleOption.h ***/
#ifndef SARIBBONSTYLEOPTION_H
#define SARIBBONSTYLEOPTION_H

#include <QDebug>
/**
 * @brief ������saribbon���гߴ������Ϣ��saribbon�Ľ��������ڴ���ĳߴ磬����������
 * ����ͨ�� @ref SARibbonElementCreateDelegate��ͨ��SARibbonElementManager�������� �� @ref setRibbonStyleOption ���������Լ���SARibbonStyleOption
 *
 * @sa SARibbonElementManager
 *
 * һ��SARibbonElementCreateDelegate::setRibbonStyleOption���������ribbonbar����֮ǰ����
 *
 * @note ���ඨ����ribbonbar��pannel�ĸ߶���Ϣ����ͨ��������ǰ�����һЩ������Ϣ
 *
 * @todo ��������ͨ�������ļ�����ribbon�ĳߴ粼��
 */
class SA_RIBBON_EXPORT SARibbonStyleOption
{
public:
    SARibbonStyleOption();
    virtual ~SARibbonStyleOption();

public:
    // ribbonBar�ĸ߶�
    virtual int ribbonBarHeight(SARibbonBar::RibbonStyle s) const;

    //�������ĸ߶ȣ�����wpsģʽ���˲���û����
    virtual int titleBarHeight() const;

    //��ǩ���߶�
    virtual int tabBarHeight() const;

    //�ڸı��˲��������Ҫ����ı������¼���
    virtual void recalc();

protected:
    //ͨ�����в�������pannel�ĸ߶�
    //    int calcPannelHeight(SARibbonPannel::PannelLayoutMode lm) const;
    //����ribbon�ĸ߶�
    int calcMainbarHeight(SARibbonBar::RibbonStyle s) const;

private:
    //��ʼ��
    void init();
    //����pannel�ĸ߶�
    void updateMainbarHeight();

private:
    int m_tabBarHeight;                        ///< ribbon tab �ĸ߶�
    int m_titleBarHeight;                      ///< �������߶�
    int m_ribbonbarHeightOfficeStyleThreeRow;  ///< office��ʽ��3�и߶�
    int m_ribbonbarHeightWPSStyleThreeRow;     ///< wps��ʽ3�еĸ߶�
    int m_ribbonbarHeightWPSStyleTwoRow;       ///< wps��ʽ2�еĸ߶�
    int m_ribbonbarHeightOfficeStyleTwoRow;    ///< office��ʽ2�еĸ߶�
};

SA_RIBBON_EXPORT QDebug operator<<(QDebug debug, const SARibbonStyleOption& c);
#endif  // SARIBBONSTYLEOPTION_H

/*** End of inlined file: SARibbonStyleOption.h ***/

/*** Start of inlined file: SARibbonElementFactory.h ***/
#ifndef SARIBBONELEMENTFACTORY_H
#define SARIBBONELEMENTFACTORY_H

#include <QColor>
#include <QMargins>
#include <QSize>
#include <QScopedPointer>

class QWidget;
class SARibbonBar;
class SARibbonTabBar;
class SARibbonApplicationButton;
class SARibbonCategory;
class SARibbonContextCategory;
class SARibbonPannel;
class SARibbonSeparatorWidget;
class SARibbonGallery;
class SARibbonGalleryGroup;
class SARibbonToolButton;
class SARibbonControlButton;
class SARibbonButtonGroupWidget;
class SARibbonStackedWidget;
class SARibbonQuickAccessBar;
class SARibbonPannelOptionButton;

///
/// \brief SARibbon����Ԫ�ش����Ĺ�����SARibbon�ڲ�������Ԫ�ض�ͨ��SARibbonElementFactory������
///
/// ����SARibbonBar��һ�����Ͽؼ����ܶ��Ӵ�����϶��ɣ���Щ�����Ĵ��������̳У���ô����Ҫ���������������
/// ��SARibbonCategory���������ش����createRibbonCategory,�������ص����ʵ��
///
class SA_RIBBON_EXPORT SARibbonElementFactory
{
public:
    SARibbonElementFactory();
    virtual ~SARibbonElementFactory();
    virtual SARibbonTabBar* createRibbonTabBar(QWidget* parent);
    virtual SARibbonApplicationButton* createRibbonApplicationButton(QWidget* parent);
    virtual SARibbonCategory* createRibbonCategory(QWidget* parent);
    virtual SARibbonContextCategory* createRibbonContextCategory(QWidget* parent);
    virtual SARibbonPannel* createRibbonPannel(QWidget* parent);
    virtual SARibbonSeparatorWidget* createRibbonSeparatorWidget(int value, QWidget* parent);
    virtual SARibbonSeparatorWidget* createRibbonSeparatorWidget(QWidget* parent);
    virtual SARibbonGallery* createRibbonGallery(QWidget* parent);
    virtual SARibbonGalleryGroup* createRibbonGalleryGroup(QWidget* parent);
    virtual SARibbonToolButton* createRibbonToolButton(QWidget* parent);
    virtual SARibbonStackedWidget* createRibbonStackedWidget(SARibbonBar* parent);

    //��������ribbon�İ�ť������
    virtual SARibbonControlButton* createHidePannelButton(SARibbonBar* parent);
    virtual SARibbonButtonGroupWidget* craeteButtonGroupWidget(QWidget* parent);
    virtual SARibbonQuickAccessBar* createQuickAccessBar(QWidget* parent);

    // SARibbonStyleOption���Խ��м̳У��˺�����������Ϊ�麯��
    SARibbonStyleOption& getRibbonStyleOption();
    void setRibbonStyleOption(SARibbonStyleOption* opt);

    //����SARibbonPannelOptionButton
    virtual SARibbonPannelOptionButton* createRibbonPannelOptionButton(SARibbonPannel* pannel);

private:
    QScopedPointer< SARibbonStyleOption > mStyleOption;
};

#endif  // SARIBBONELEMENTCREATEDELEGATE_H

/*** End of inlined file: SARibbonElementFactory.h ***/

/*** Start of inlined file: SARibbonElementManager.h ***/
#ifndef SARIBBONELEMENTMANAGER_H
#define SARIBBONELEMENTMANAGER_H

///
/// \brief ������һ��ȫ�ֵ��������ڹ���SARibbonElementCreateDelegate
///
class SA_RIBBON_EXPORT SARibbonElementManager
{
protected:
    SARibbonElementManager();

public:
    virtual ~SARibbonElementManager();
    static SARibbonElementManager* instance();
    SARibbonElementFactory* factory();
    void setupFactory(SARibbonElementFactory* fac);

private:
    QScopedPointer< SARibbonElementFactory > mFactory;
};
#ifndef RibbonSubElementMgr
#define RibbonSubElementMgr SARibbonElementManager::instance()
#endif
#ifndef RibbonSubElementDelegate
#define RibbonSubElementDelegate SARibbonElementManager::instance()->factory()
#endif
#ifndef RibbonSubElementStyleOpt
#define RibbonSubElementStyleOpt SARibbonElementManager::instance()->factory()->getRibbonStyleOption()
#endif
#endif  // SARIBBONELEMENTMANAGER_H

/*** End of inlined file: SARibbonElementManager.h ***/

/*** Start of inlined file: SARibbonCustomizeData.h ***/
#ifndef SARIBBONCUSTOMIZEDATA_H
#define SARIBBONCUSTOMIZEDATA_H

#include <QList>

class SARibbonMainWindow;

/**
 * @brief ��¼�����Զ��������������
 * @note ������������@ref SARibbonActionsManager Ҫ��SARibbonActionsManager֮��ʹ�ô���
 */
class SA_RIBBON_EXPORT SARibbonCustomizeData
{
public:
    enum ActionType
    {
        UnknowActionType = 0,           ///< δ֪����
        AddCategoryActionType,          ///< ���category����(1)
        AddPannelActionType,            ///< ���pannel����(2)
        AddActionActionType,            ///< ���action����(3)
        RemoveCategoryActionType,       ///< ɾ��category����(4)
        RemovePannelActionType,         ///< ɾ��pannel����(5)
        RemoveActionActionType,         ///< ɾ��action����(6)
        ChangeCategoryOrderActionType,  ///< �ı�category˳��Ĳ���(7)
        ChangePannelOrderActionType,    ///< �ı�pannel˳��Ĳ���(8)
        ChangeActionOrderActionType,    ///< �ı�action˳��Ĳ���(9)
        RenameCategoryActionType,       ///< ��category��������(10)
        RenamePannelActionType,         ///< ��Pannel��������(11)
        VisibleCategoryActionType       ///< ��categoryִ������/��ʾ����(12)
    };
    SARibbonCustomizeData();
    SARibbonCustomizeData(ActionType type, SARibbonActionsManager* mgr = nullptr);
    //��ȡCustomizeData��action type
    ActionType actionType() const;

    //����CustomizeData��action type
    void setActionType(ActionType a);

    //�ж��Ƿ���һ��������CustomizeData
    bool isValid() const;

    //Ӧ��SARibbonCustomizeData
    bool apply(SARibbonMainWindow* m) const;

    //��ȡactionmanagerָ��
    SARibbonActionsManager* actionManager();

    //����ActionsManager
    void setActionsManager(SARibbonActionsManager* mgr);

    //��ӦAddCategoryActionType
    static SARibbonCustomizeData makeAddCategoryCustomizeData(const QString& title, int index, const QString& objName);

    //��ӦAddPannelActionType
    static SARibbonCustomizeData makeAddPannelCustomizeData(const QString& title, int index, const QString& categoryobjName, const QString& objName);

    //��ӦAddActionActionType
    static SARibbonCustomizeData makeAddActionCustomizeData(const QString& key,
                                                            SARibbonActionsManager* mgr,
                                                            SARibbonPannelItem::RowProportion rp,
                                                            const QString& categoryObjName,
                                                            const QString& pannelObjName);

    //��ӦRenameCategoryActionType
    static SARibbonCustomizeData makeRenameCategoryCustomizeData(const QString& newname, const QString& categoryobjName);

    //��ӦRenamePannelActionType
    static SARibbonCustomizeData makeRenamePannelCustomizeData(const QString& newname,
                                                               const QString& categoryobjName,
                                                               const QString& pannelObjName);

    //��ӦRemoveCategoryActionType
    static SARibbonCustomizeData makeRemoveCategoryCustomizeData(const QString& categoryobjName);

    //��ӦChangeCategoryOrderActionType
    static SARibbonCustomizeData makeChangeCategoryOrderCustomizeData(const QString& categoryobjName, int moveindex);

    //��ӦChangePannelOrderActionType
    static SARibbonCustomizeData makeChangePannelOrderCustomizeData(const QString& categoryobjName,
                                                                    const QString& pannelObjName,
                                                                    int moveindex);

    //��ӦChangeActionOrderActionType
    static SARibbonCustomizeData makeChangeActionOrderCustomizeData(const QString& categoryobjName,
                                                                    const QString& pannelObjName,
                                                                    const QString& key,
                                                                    SARibbonActionsManager* mgr,
                                                                    int moveindex);

    //��ӦRemovePannelActionType
    static SARibbonCustomizeData makeRemovePannelCustomizeData(const QString& categoryobjName, const QString& pannelObjName);

    //��ӦRemoveActionActionType
    static SARibbonCustomizeData makeRemoveActionCustomizeData(const QString& categoryobjName,
                                                               const QString& pannelObjName,
                                                               const QString& key,
                                                               SARibbonActionsManager* mgr);

    //��ӦVisibleCategoryActionType
    static SARibbonCustomizeData makeVisibleCategoryCustomizeData(const QString& categoryobjName, bool isShow);

    //�ж��Ƿ�����Զ���,���ĳ��action���뱻�༭������ͨ���˺�������
    static bool isCanCustomize(QObject* obj);
    static void setCanCustomize(QObject* obj, bool canbe = true);

    //��QList<SARibbonCustomizeData>���м�
    static QList< SARibbonCustomizeData > simplify(const QList< SARibbonCustomizeData >& csd);

public:
    /**
     * @brief ��¼˳��Ĳ���
     *
     * ��actionType==AddCategoryActionTypeʱ���˲�����¼Category��insertλ��,
     * ��actionType==AddPannelActionTypeʱ���˲�����¼pannel��insertλ��,
     * ��actionType==AddActionActionTypeʱ���˲�����¼pannel��insertλ��
     */
    int indexValue;

    /**
     * @brief ��¼���⡢�����Ȳ���
     *
     * ��actionType==AddCategoryActionTypeʱ��keyΪcategory���⣬
     * ��actionType==AddPannelActionTypeʱ��keyΪpannel���⣬
     * ��actionType==AddActionActionTypeʱ��keyΪaction�Ĳ�ѯ���ݣ�����SARibbonActionsManager::action��ѯ
     */
    QString keyValue;

    /**
     * @brief ��¼categoryObjName�����ڶ�λCategory
     */
    QString categoryObjNameValue;

    /**
     * @brief ��¼pannelObjName��saribbon��Customize�����󲿷ֻ���objname
     */
    QString pannelObjNameValue;

    SARibbonPannelItem::RowProportion actionRowProportionValue;  ///< �е�ռ�ȣ�ribbon����large��media��small����ռ��,��@ref RowProportion
private:
    ActionType m_type;  ///< ������data��category����pannel�����action
    SARibbonActionsManager* m_actionsManagerPointer;
};
Q_DECLARE_METATYPE(SARibbonCustomizeData)

typedef QList< SARibbonCustomizeData > SARibbonCustomizeDataList;

#endif  // SARIBBONCUSTOMIZEDATA_H

/*** End of inlined file: SARibbonCustomizeData.h ***/

/*** Start of inlined file: SARibbonCustomizeWidget.h ***/
#ifndef SARIBBONCUSTOMIZEWIDGET_H
#define SARIBBONCUSTOMIZEWIDGET_H

#include <QWidget>

// SARibbonCustomizeWidget ����
class SARibbonCustomizeWidgetUi;
class SARibbonMainWindow;
class QStandardItemModel;
class QStandardItem;
class QAbstractButton;
//
class QXmlStreamWriter;
class QXmlStreamReader;

/**
 * @brief �Զ�����洰��
 *
 * @note SARibbon���Զ����ǻ��ڲ���ģ�����ڴ�������ǰ������@ref sa_apply_customize_from_xml_file ���ƺ���
 * ��ô�ڶԻ�������ǰΪ�˱�֤ͬ����Ҫ����@ref SARibbonCustomizeWidget::fromXml ͬ�������ļ��������ٴ��޸ĺ�������ļ���һ��
 */
class SA_RIBBON_EXPORT SARibbonCustomizeWidget : public QWidget
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonCustomizeWidget)
public:
    SARibbonCustomizeWidget(SARibbonMainWindow* ribbonWindow, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~SARibbonCustomizeWidget();

    /**
     * @brief ����ribbon������ʾ����
     */
    enum RibbonTreeShowType
    {
        ShowAllCategory,  ///< ��ʾ����Category������contextcategory
        ShowMainCategory  ///< ��ʾ��Ҫ��category��������������
    };

    /**
     * @brief QStandardItem��Ӧ��role
     */
    enum ItemRole
    {
        LevelRole            = Qt::UserRole + 1,  ///< �������ǲ㼶����0��category 1��pannel 2��item
        PointerRole          = Qt::UserRole + 2,  ///< �������Ǵ��ָ�롣����LevelRole������ת
        CanCustomizeRole     = Qt::UserRole + 3,  ///< �����item�ǿ����Զ����.bool
        CustomizeRole        = Qt::UserRole + 4,  ///< ����������Զ����item,bool,��Ҫ������Щ�Լ���ӵı�ǩ��pannel���д˽�ɫ����CanCustomizeRole
        CustomizeObjNameRole = Qt::UserRole + 5   ///< ��¼����ʱ���Զ������ݵ�obj�� QString
    };

    //����action������
    void setupActionsManager(SARibbonActionsManager* mgr);

    //�ж��û��Ƿ��иĶ�����
    bool isChanged() const;

    //��ȡmodel
    const QStandardItemModel* model() const;

    //���ݵ�ǰ��radiobuttonѡ��������model
    void updateModel();

    //����model
    void updateModel(RibbonTreeShowType type);

    //Ӧ�����е��趨
    bool applys();

    //ת��Ϊxml
    bool toXml(QXmlStreamWriter* xml) const;
    bool toXml(const QString& xmlpath) const;

    //��xml�м���QList<SARibbonCustomizeData>�����ڻ��������ļ������ã��Ի�����ʾǰ������ô˺�������֤�������õ���ȷ��¼
    void fromXml(QXmlStreamReader* xml);
    void fromXml(const QString& xmlpath);

    //Ӧ��xml���ã����Խ��customize_datas_from_xml��customize_datas_apply����
    static bool fromXml(QXmlStreamReader* xml, SARibbonMainWindow* w, SARibbonActionsManager* mgr);

    //������ж�������ִ��applys���������Ҫ�������ã�Ӧ��clear������ᵼ���쳣
    void clear();

protected:
    //��QList<SARibbonCustomizeData>���вü�,��һЩ�����ϲ�
    void simplify();

    SARibbonPannelItem::RowProportion selectedRowProportion() const;

    QAction* selectedAction() const;
    QAction* itemToAction(QStandardItem* item) const;

    QStandardItem* selectedItem() const;

    //��ȡѡ�е�ribbon tree ��level
    int selectedRibbonLevel() const;

    //����ѡ�е�item�ж�
    int itemLevel(QStandardItem* item) const;

    //����ĳ��item��ѡ��
    void setSelectItem(QStandardItem* item, bool ensureVisible = true);

    //�ж�itemn�ܷ�Ķ������ԸĶ�����true
    bool isItemCanCustomize(QStandardItem* item) const;
    bool isSelectedItemCanCustomize() const;

    //�ж�item�Ƿ����Զ����item
    bool isCustomizeItem(QStandardItem* item) const;
    bool isSelectedItemIsCustomize() const;

    //ɾ��һ��item
    void removeItem(QStandardItem* item);

private slots:
    void onComboBoxActionIndexCurrentIndexChanged(int index);
    void onRadioButtonGroupButtonClicked(QAbstractButton* b);
    void onPushButtonNewCategoryClicked();
    void onPushButtonNewPannelClicked();
    void onPushButtonRenameClicked();
    void onPushButtonAddClicked();
    void onPushButtonDeleteClicked();
    void onListViewSelectClicked(const QModelIndex& index);
    void onTreeViewResultClicked(const QModelIndex& index);
    void onToolButtonUpClicked();
    void onToolButtonDownClicked();
    void onItemChanged(QStandardItem* item);
    void onLineEditSearchActionTextEdited(const QString& text);
    void onPushButtonResetClicked();

private:
    void initConnection();

private:
    SARibbonCustomizeWidgetUi* ui;
};

/**
 * @brief ת��Ϊxml
 *
 * �˺�������дelement������дdocument������ݣ���������Ҫдdocument��
 * ��Ҫ�ڴ˺���ǰ����QXmlStreamWriter::writeStartDocument(),�ڴ˺��������QXmlStreamWriter::writeEndDocument()
 * @param xml QXmlStreamWriterָ��
 * @note ע�⣬�ڴ���QXmlStreamWriter֮ǰ����Ҫ���ñ���Ϊutf-8:xml->setCodec("utf-8");
 * @note ����QXmlStreamWriter��QString��Ϊioʱ���ǲ�֧�ֱ���ģ��������޷���֤�Զ�����̲����������ַ���
 * ��ˣ�QXmlStreamWriter��Ӧ��ͨ��QString���й��죬�����Ҫ�õ�string��Ҳ��Ҫͨ��QByteArray���죬�磺
 * @param cds ����QList<SARibbonCustomizeData>���ɵĲ���
 * @return ��������쳣������false,���û���Զ�������Ҳ�᷵��false
 */
bool SA_RIBBON_EXPORT sa_customize_datas_to_xml(QXmlStreamWriter* xml, const QList< SARibbonCustomizeData >& cds);

/**
 * @brief ͨ��xml��ȡQList<SARibbonCustomizeData>
 * @param xml
 * @return QList<SARibbonCustomizeData>
 */
QList< SARibbonCustomizeData > SA_RIBBON_EXPORT sa_customize_datas_from_xml(QXmlStreamReader* xml, SARibbonActionsManager* mgr);

/**
 * @brief Ӧ��QList<SARibbonCustomizeData>
 * @param cds
 * @param w SARibbonMainWindowָ��
 * @return �ɹ�Ӧ�õĸ���
 */
int SA_RIBBON_EXPORT sa_customize_datas_apply(const QList< SARibbonCustomizeData >& cds, SARibbonMainWindow* w);

/**
 * @brief ֱ�Ӽ���xml�Զ���ribbon�����ļ�����ribbon���Զ�����ʾ
 * @param filePath xml�����ļ�
 * @param w ������
 * @param mgr action������
 * @return �ɹ�����true
 * @note �ظ�����һ�������ļ��ᷢ���쳣��Ϊ�˱�������¼�������һ��ͨ��һ��������ֻ֤����һ�Σ��磺
 * @code
 * static bool has_call = false;
 * if (!has_call) {
 *     has_call = sa_apply_customize_from_xml_file("customize.xml", this, m_actMgr);
 * }
 * @endcode
 */
bool SA_RIBBON_EXPORT sa_apply_customize_from_xml_file(const QString& filePath, SARibbonMainWindow* w, SARibbonActionsManager* mgr);

#endif  // SARIBBONCUSTOMIZEWIDGET_H

/*** End of inlined file: SARibbonCustomizeWidget.h ***/

/*** Start of inlined file: SARibbonCustomizeDialog.h ***/
#ifndef SARIBBONCUSTOMIZEDIALOG_H
#define SARIBBONCUSTOMIZEDIALOG_H

#include <QDialog>

class SARibbonActionsManager;
class SARibbonCustomizeDialogUi;
class QXmlStreamWriter;

/**
 * @brief SARibbonCustomizeWidget�ĶԻ����װ
 *
 * �˹���������@ref SARibbonActionsManager ��SARibbonActionsManager������Ϊmianwindow�ĳ�Ա������
 * SARibbonActionsManager���Կ��ٰ�����QAction����ϸ��SARibbonActionsManager��˵��
 *
 * @note SARibbon���Զ����ǻ��ڲ���ģ�����ڴ�������ǰ������@ref sa_apply_customize_from_xml_file ���ƺ���
 * ��ô�ڶԻ�������ǰΪ�˱�֤ͬ����Ҫ����@ref SARibbonCustomizeDialog::fromXml ͬ�������ļ��������ٴ��޸ĺ�������ļ���һ��
 */
class SA_RIBBON_EXPORT SARibbonCustomizeDialog : public QDialog
{
    Q_OBJECT
public:
    SARibbonCustomizeDialog(SARibbonMainWindow* ribbonWindow, QWidget* p = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    //����action������
    void setupActionsManager(SARibbonActionsManager* mgr);

    //Ӧ�����е��趨
    bool applys();

    //������ж���
    void clear();

    //ת��Ϊxml
    bool toXml(QXmlStreamWriter* xml) const;
    bool toXml(const QString& xmlpath) const;

    //��xml�м���QList<SARibbonCustomizeData>�����ڻ��������ļ������ã��Ի�����ʾǰ������ô˺�������֤�������õ���ȷ��¼
    void fromXml(QXmlStreamReader* xml);
    void fromXml(const QString& xmlpath);

    //����SARibbonCustomizeWidget����ָ��
    SARibbonCustomizeWidget* customizeWidget() const;

private:
    void initConnection();

    SARibbonCustomizeDialogUi* ui;
};

#endif  // SARIBBONCUSTOMIZEDIALOG_H

/*** End of inlined file: SARibbonCustomizeDialog.h ***/

/*** Start of inlined file: SARibbonMainWindow.h ***/
#ifndef SARIBBONMAINWINDOW_H
#define SARIBBONMAINWINDOW_H

#include <QMainWindow>
class SARibbonBar;
class SAFramelessHelper;

/**
 * @brief ���Ҫʹ��SARibbonBar������ʹ�ô������QMainWindow
 *
 * ����ribbon�ķ��ʹ�ͳ��Toolbar������ϴ�
 * SARibbonBarʹ����Ҫ��ԭ�е�QMainWindow�滻ΪSARibbonMainWindow,
 * SARibbonMainWindow�Ǹ��ޱ߿��壬�̳���QMainWindow���乹�캯���Ĳ���useRibbon
 * ����ָ���Ƿ�ʹ��ribbon���Ĭ��Ϊtrue
 *
 * @code
 * SARibbonMainWindow(QWidget* parent = nullptr,bool useRibbon = true);
 * @endcode
 *
 * ����뻻�ط�ribbon���ֻ��Ҫ��useRibbon����Ϊfalse����,
 * ��Ա����isUseRibbon�����жϵ�ǰ�Ƿ�Ϊribbonģʽ����������ڼ��ݴ�ͳToolbar����ribbon���ʱ�ǳ����á�
 *
 * @code
 * bool isUseRibbon() const;
 * @endcode
 *
 * @ref SARibbonMainWindow �ṩ�˼��ֳ��õ�ribbon��ʽ����ʽ�ɼ�@ref RibbonTheme
 * ͨ��@ref setRibbonTheme �ɸı�ribbon����ʽ���û�Ҳ��ͨ��qss�Լ������Լ�����ʽ
 *
 */
class SA_RIBBON_EXPORT SARibbonMainWindow : public QMainWindow
{
    Q_OBJECT
    SA_RIBBON_DECLARE_PRIVATE(SARibbonMainWindow)
    Q_PROPERTY(RibbonTheme ribbonTheme READ ribbonTheme WRITE setRibbonTheme)
public:
    /**
     * @brief Ribbon���⣬����ͨ��qss����ribbon�����⣬���Ʒ����ɲο�Դ����office2013.qss
     *
     * ע�⣬������Щqss�ĳߴ磬��C++�������޷���ȡ�����������û��Զ����qss���⣬��Щ�ߴ�����Ҫ�ֶ����ý�ȥ��
     *
     * ����ribbon tab��margin��Ϣ����QTabBar���޷���ȡ���������Ӱ����SARibbonContextCategory�Ļ��ƣ�
     * ��ˣ�������qss����Ҫ���margin��Ϣ�������ý�SARibbonTabBar��
     */
    enum RibbonTheme
    {
        NormalTheme,  ///< ��ͨ����
        Office2013    ///< office2013����
    };
    Q_ENUM(RibbonTheme)
public:
    SARibbonMainWindow(QWidget* parent = nullptr, bool useRibbon = true);
    ~SARibbonMainWindow() Q_DECL_OVERRIDE;
    //����SARibbonBar
    const SARibbonBar* ribbonBar() const;
    SARibbonBar* ribbonBar();

    //����SAFramelessHelper
    SAFramelessHelper* framelessHelper();

    void setRibbonTheme(RibbonTheme theme);
    RibbonTheme ribbonTheme() const;

    //�жϵ�ǰ�Ƿ�ʹ��ribbonģʽ
    bool isUseRibbon() const;

    //�˺��������ڿ�����С��󻯺͹رհ�ť����ʾ
    void updateWindowFlag(Qt::WindowFlags flags);

    //��ȡϵͳ��ť��״̬
    Qt::WindowFlags windowButtonFlags() const;

    //��дsetMenuWidget
    void setMenuWidget(QWidget* menubar);

    //��дsetMenuBar
    void setMenuBar(QMenuBar* menuBar);

protected:
    //����ribbonbar�Ĺ�������
    SARibbonBar* createRibbonBar();
    void loadTheme(const QString& themeFile);
    virtual void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;
    virtual bool eventFilter(QObject* obj, QEvent* e) Q_DECL_OVERRIDE;
    virtual bool event(QEvent* e) Q_DECL_OVERRIDE;
};

#endif  // SARIBBONMAINWINDOW_H

/*** End of inlined file: SARibbonMainWindow.h ***/

/*** End of inlined file: SARibbonAmalgamTemplatePublicHeaders.h ***/

#endif
