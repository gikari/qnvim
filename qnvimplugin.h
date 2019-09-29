#pragma once

#include "qnvim_global.h"
#include "numberscolumn.h"
#include <QColor>
#include <QPoint>
#include <QRect>
#include <QMutex>

#include <extensionsystem/iplugin.h>
#include <texteditor/plaintexteditorfactory.h>

class QPlainTextEdit;

namespace Core {
    class IEditor;
}

namespace ProjectExplorer {
    class Project;
}

namespace NeovimQt {
    class NeovimConnector;
    class InputConv;
}

namespace QNVim {
namespace Internal {

class QNVimPlugin : public ExtensionSystem::IPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "QNVim.json")

public:
    QNVimPlugin();
    ~QNVimPlugin();

    bool initialize(const QStringList &, QString *);
    bool initialize();
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

    bool eventFilter(QObject *, QEvent *);
    void toggleQNVim();

protected:
    QString filename(Core::IEditor * = nullptr) const;

    void fixSize(Core::IEditor * = nullptr);
    void syncCursorToVim(Core::IEditor * = nullptr);
    void syncSelectionToVim(Core::IEditor * = nullptr);
    void syncModifiedToVim(Core::IEditor * = nullptr);
    void syncToVim(Core::IEditor * = nullptr, std::function<void()> = nullptr);
    void syncCursorFromVim(const QVariantList &, const QVariantList &, QByteArray mode);
    void syncFromVim();

    void triggerCommand(const QByteArray &);

private:
    void editorOpened(Core::IEditor *);
    void editorAboutToClose(Core::IEditor *);

    void initializeBuffer(int);
    void handleNotification(const QByteArray &, const QVariantList &);
    void redraw(const QVariantList &);
    void updateCursorSize();

    bool mEnabled;

    QMutex mSyncMutex;

    QPlainTextEdit *mCMDLine;
    NumbersColumn *mNumbersColumn;
    NeovimQt::NeovimConnector *mNVim;
    NeovimQt::InputConv *mInputConv;
    unsigned mVimChanges;
    QMap<Core::IEditor *, int> mBuffers;
    QMap<int, Core::IEditor *> mEditors;
    QMap<int, bool> mChangedTicks;
    QMap<int, QString> mBufferType;

    QString mText;
    int mWidth, mHeight;
    QColor mForegroundColor, mBackgroundColor, mSpecialColor;
    QColor mCursorColor;
    bool mBusy, mMouse, mNumber, mRelativeNumber, mWrap;

    bool mCMDLineVisible;
    QString mCMDLineContent, mCMDLineDisplay;
    QString mMessageLineDisplay;
    int mCMDLinePos;
    QChar mCMDLineFirstc;
    QString mCMDLinePrompt;
    int mCMDLineIndent;

    QByteArray mUIMode, mMode;
    QPoint mCursor, mVCursor;

    int settingBufferFromVim;
    unsigned long long mSyncCounter;
};

class HelpEditorFactory : public TextEditor::PlainTextEditorFactory {
    Q_OBJECT

public:
    explicit HelpEditorFactory();
};

class TerminalEditorFactory : public TextEditor::PlainTextEditorFactory {
    Q_OBJECT

public:
    explicit TerminalEditorFactory();
};

} // namespace Internal
} // namespace QNVim
