#pragma once

#include <QWidget>

namespace TextEditor {
class TextEditorWidget;
}

namespace QNVim {
namespace Internal {

class NumbersColumn : public QWidget
{
    Q_OBJECT
    bool mNumber;
    TextEditor::TextEditorWidget *mEditor;

public:
    NumbersColumn();

    void setEditor(TextEditor::TextEditorWidget *);
    void setNumber(bool);

protected:
    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *, QEvent *);

private:
    void updateGeometry();
};

} // namespace Internal
} // namespace QNVim
