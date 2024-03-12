/*********************************************************************
 * \file   basewindow.h
 * \brief  ͨ���ޱ߿򴰿ڻ���
 * 
 * \author heqingrui
 * \date   December 2023
 *********************************************************************/
#ifndef QRCODE_BASEWINDOW_H_
#define QRCODE_BASEWINDOW_H_

#include <QDialog>
#include <QSystemTrayIcon>
#include <QPointer>
#include <QMouseEvent>
#include <QtCore/qt_windows.h>

class QProgressIndicator;
/**
 * ���϶����ɸı��С.
 */
class BaseWindow : public QDialog
{
    Q_OBJECT
public:
    explicit BaseWindow(QWidget *parent = nullptr);
    virtual ~BaseWindow();

    void setResizable(bool resizable = true);
    void setShowDropShadow(bool shadow = true);
    void setBorderWidth(int borderWidth);

protected:
    void setTitleBar(QWidget *titleBar);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual bool event(QEvent *event) override;
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

private:
    void handleMousePressEvent(QMouseEvent *event);
    void handleMouseDoubleClickEvent(QMouseEvent *event);
    void handleKeyPressEvent(QKeyEvent *event);

protected:
    QPointer<QWidget> m_titleBar;
    bool m_resizable = false;
    bool m_movable = true;
    bool m_useShadow = true;
    QPixmap m_dropShadow;
    int m_borderWidth = 5;
};

/**
 * ���϶������ɸı��С.
 */
class BaseDialog : public BaseWindow
{
    Q_OBJECT
public:
    explicit BaseDialog(QWidget *parent = nullptr);
    virtual ~BaseDialog();

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

/**
 * ���϶����ɸı��С����󻯣���С�����رյ�����
 */
class BaseMainWindow : public BaseWindow
{
    Q_OBJECT
public:
    explicit BaseMainWindow(const QString &title = QString(), QWidget *parent = nullptr);
    virtual ~BaseMainWindow();

public:
    void showTrayMessage(const QString &msg);
    void showLoading(bool bShow);

protected:
    void initTrayIcon(const QIcon &icon, QMenu *menu);
    void resetLoadingPosition();

protected slots:
    void on_btnMin_clicked();
    void on_btnMax_clicked(bool checked);
    void on_btnClose_clicked();
    void onSystemTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

protected:
    QPointer<QProgressIndicator> m_busyIcon = nullptr;
    QPointer<QSystemTrayIcon> m_trayIcon = nullptr;
};

#endif // QRCODE_BASEWINDOW_H_
